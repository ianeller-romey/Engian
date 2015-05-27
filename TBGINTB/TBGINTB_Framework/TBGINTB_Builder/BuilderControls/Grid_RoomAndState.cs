using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_RoomAndState : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_RoomData m_grid_roomData;
        StackPanel m_stackPanel_roomStates;

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomAndState(int areaId, int roomId, string roomName, int roomX, int roomY, int roomZ)
        {
            CreateControls(areaId, roomId, roomName, roomX, roomY, roomZ);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomStateAdded += GinTubBuilderManager_RoomStateAdded;

            m_grid_roomData.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_roomStates.Children.OfType<Grid_RoomStateUnderRoom>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomStateAdded -= GinTubBuilderManager_RoomStateAdded;

            m_grid_roomData.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_roomStates.Children.OfType<Grid_RoomStateUnderRoom>())
                grid.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int areaId, int roomId, string roomName, int roomX, int roomY, int roomZ)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            ////////
            // Room
            Button button_modifyRoom = new Button() { Content = "Modify Room" };
            button_modifyRoom.Click += Button_ModifyRoom_Click;
            this.SetGridRowColumn(button_modifyRoom, 0, 0);

            m_grid_roomData = new Grid_RoomData(roomId, roomName, roomX, roomY, roomZ, areaId, false);
            this.SetGridRowColumn(m_grid_roomData, 1, 0);
            m_grid_roomData.SetActiveAndRegisterForGinTubEvents();

            ////////
            // RoomStates
            Button button_addRoomState = new Button() { Content = "Add Room State" };
            button_addRoomState.Click += Button_AddRoomState_Click;
            this.SetGridRowColumn(button_addRoomState, 2, 0);

            m_stackPanel_roomStates = new StackPanel() { Orientation = Orientation.Vertical };

            ScrollViewer scrollViewer_roomStates =
                new ScrollViewer()
                {
                    HorizontalScrollBarVisibility = ScrollBarVisibility.Hidden,
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            scrollViewer_roomStates.Content = m_stackPanel_roomStates;
            this.SetGridRowColumn(scrollViewer_roomStates, 3, 0);
        }

        private void AddRoomState(int roomStateId, int state, int locationId, DateTime? time, int roomId)
        {
            Grid_RoomStateUnderRoom grid_roomStateData = new Grid_RoomStateUnderRoom(roomStateId, state, locationId, time, roomId);
            grid_roomStateData.SetActiveAndRegisterForGinTubEvents();
            m_stackPanel_roomStates.Children.Add(grid_roomStateData);
            GinTubBuilderManager.LoadAllLocations();
        }

        private void GinTubBuilderManager_RoomStateAdded(object sender, GinTubBuilderManager.RoomStateAddedEventArgs args)
        {
            AddRoomState(args.Id, args.State, args.Location, args.Time, args.Room);
        }

        private void Button_ModifyRoom_Click(object sender, RoutedEventArgs e)
        {
            Window_RoomData window =
                new Window_RoomData
                (
                    m_grid_roomData.RoomId,
                    m_grid_roomData.RoomName,
                    m_grid_roomData.RoomX,
                    m_grid_roomData.RoomY,
                    m_grid_roomData.RoomZ,
                    m_grid_roomData.AreaId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyRoom
                (
                    window.RoomId.Value, 
                    window.RoomName, 
                    window.RoomX, 
                    window.RoomY, 
                    window.RoomZ, 
                    m_grid_roomData.AreaId
                );
        }

        void Button_AddRoomState_Click(object sender, RoutedEventArgs e)
        {
            Window_RoomStateData window = 
                new Window_RoomStateData(null, null, null, null, m_grid_roomData.RoomId.Value);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddRoomState(m_grid_roomData.RoomId.Value, window.LocationId.Value, window.Time);
        }

        #endregion

        #endregion
    }
}
