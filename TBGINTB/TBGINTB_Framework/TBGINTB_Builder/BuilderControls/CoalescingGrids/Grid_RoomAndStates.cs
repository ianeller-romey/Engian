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
    public class Grid_RoomAndStates : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_RoomData m_grid_rooms;
        StackPanel m_stackPanel_roomStates;

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomAndStates(int roomId, string roomName, int roomX, int roomY, int roomZ, int areaId)
        {
            CreateControls(roomId, roomName, roomX, roomY, roomZ, areaId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomStateAdded += GinTubBuilderManager_RoomStateAdded;

            m_grid_rooms.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_roomStates.Children.OfType<Grid_RoomStateModification>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomStateAdded -= GinTubBuilderManager_RoomStateAdded;

            m_grid_rooms.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_roomStates.Children.OfType<Grid_RoomStateModification>())
                grid.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int roomId, string roomName, int roomX, int roomY, int roomZ, int areaId)
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

            m_grid_rooms = new Grid_RoomData(roomId, roomName, roomX, roomY, roomZ, areaId, false);
            this.SetGridRowColumn(m_grid_rooms, 1, 0);
            m_grid_rooms.SetActiveAndRegisterForGinTubEvents();

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

        private void AddRoomState(int roomStateId, int roomStateState, DateTime? roomStateTime, int locationId, int roomId)
        {
            Grid_RoomStateModification grid = new Grid_RoomStateModification(roomStateId, roomStateState, roomStateTime, locationId, roomId);
            m_stackPanel_roomStates.Children.Add(grid);
            GinTubBuilderManager.LoadAllLocations();
        }

        private void GinTubBuilderManager_RoomStateAdded(object sender, GinTubBuilderManager.RoomStateAddedEventArgs args)
        {
            AddRoomState(args.Id, args.State, args.Time, args.Location, args.Room);
        }

        private void Button_ModifyRoom_Click(object sender, RoutedEventArgs e)
        {
            Window_RoomData window =
                new Window_RoomData
                (
                    m_grid_rooms.RoomId,
                    m_grid_rooms.RoomName,
                    m_grid_rooms.RoomX,
                    m_grid_rooms.RoomY,
                    m_grid_rooms.RoomZ,
                    m_grid_rooms.AreaId
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
                    m_grid_rooms.AreaId
                );
        }

        void Button_AddRoomState_Click(object sender, RoutedEventArgs e)
        {
            Window_RoomStateData window = 
                new Window_RoomStateData(null, null, null, null, m_grid_rooms.RoomId.Value);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddRoomState(window.RoomStateTime, window.LocationId.Value, m_grid_rooms.RoomId.Value);
        }

        #endregion

        #endregion
    }
}
