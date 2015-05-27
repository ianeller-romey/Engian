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
    public class Grid_RoomStateUnderRoom : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_RoomStateData m_grid_roomState;

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomStateUnderRoom(int roomStateId, int roomState, int locationId, DateTime? time, int roomId)
        {
            CreateControls(roomStateId, roomState, locationId, time, roomId);
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

        private void CreateControls(int roomStateId, int roomState, int locationId, DateTime? time, int roomId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyRoomState = new Button() { Content = "Modify Room State" };
            button_modifyRoomState.Click += Button_ModifyRoomState_Click;
            this.SetGridRowColumn(button_modifyRoomState, 0, 0);

            m_grid_roomState = new Grid_RoomStateData(roomStateId, roomState, locationId, time, roomId, false);
            this.SetGridRowColumn(m_grid_roomState, 1, 0);
            m_grid_roomState.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyRoomState_Click(object sender, RoutedEventArgs e)
        {
            Window_RoomStateData window = 
                new Window_RoomStateData
                (
                    m_grid_roomState.RoomStateId,
                    m_grid_roomState.RoomState,
                    m_grid_roomState.LocationId,
                    m_grid_roomState.Time,                    
                    m_grid_roomState.RoomId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyRoomState(m_grid_roomState.RoomStateId.Value, m_grid_roomState.RoomId, m_grid_roomState.RoomState.Value, window.LocationId.Value, window.Time);
        }

        #endregion

        #endregion
    }
}
