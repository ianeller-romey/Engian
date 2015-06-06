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
    public class Grid_RoomStateModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_RoomStateData m_grid_roomState;

        #endregion


        #region MEMBER PROPERTIES

        public int? RoomStateId { get { return m_grid_roomState.RoomStateId; } }
        public int? RoomStateState { get { return m_grid_roomState.RoomStateState; } }
        public DateTime? RoomStateTime { get { return m_grid_roomState.RoomStateTime; } }
        public int? LocationId { get { return m_grid_roomState.LocationId; } }
        public int RoomId { get { return m_grid_roomState.RoomId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomStateModification(int roomStateId, int roomStateState, DateTime? roomStateTime, int locationId, int roomId)
        {
            CreateControls(roomStateId, roomStateState, roomStateTime, locationId, roomId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_roomState.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_roomState.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int roomStateId, int roomStateState, DateTime? roomStateTime, int locationId, int roomId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyRoomState = new Button() { Content = "Modify Room State" };
            button_modifyRoomState.Click += Button_ModifyRoomState_Click;
            this.SetGridRowColumn(button_modifyRoomState, 0, 0);

            m_grid_roomState = new Grid_RoomStateData(roomStateId, roomStateState, roomStateTime, locationId, roomId, false);
            this.SetGridRowColumn(m_grid_roomState, 1, 0);
            m_grid_roomState.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyRoomState_Click(object sender, RoutedEventArgs e)
        {
            Window_RoomStateData window = 
                new Window_RoomStateData
                (
                    m_grid_roomState.RoomStateId,
                    m_grid_roomState.RoomStateState,
                    m_grid_roomState.RoomStateTime,  
                    m_grid_roomState.LocationId,                  
                    m_grid_roomState.RoomId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyRoomState
                (
                    window.RoomStateId.Value,
                    window.RoomStateState.Value, 
                    window.RoomStateTime, 
                    window.LocationId.Value,
                    window.RoomId
                );
        }

        #endregion

        #endregion
    }
}
