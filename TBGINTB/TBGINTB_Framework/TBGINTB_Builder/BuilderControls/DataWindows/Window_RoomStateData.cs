using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Window_RoomStateData : Window_AcceptCancel
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

        public Window_RoomStateData(int? roomStateId, int? roomStateState, DateTime? roomStateTime, int? locationId, int roomId)
        {
            Title = "Room State Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(roomStateId, roomStateState, roomStateTime, locationId, roomId);
            m_grid_roomState.SetActiveAndRegisterForGinTubEvents(); // need for loading Location
            GinTubBuilderManager.LoadAllLocations();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? roomStateId, int? roomStateState, DateTime? roomStateTime, int? locationId, int roomId)
        {
            m_grid_roomState = new Grid_RoomStateData(roomStateId, roomStateState, roomStateTime, locationId, roomId, true);
            return m_grid_roomState;
        }

        #endregion

        #endregion
    }
}
