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
    public class Window_RoomState : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_RoomStateData m_grid_roomStateData;

        #endregion


        #region MEMBER PROPERTIES

        public int? RoomStateId { get { return m_grid_roomStateData.RoomStateId; } }
        public int? RoomState { get { return m_grid_roomStateData.RoomState; } }
        public int? LocationId { get { return m_grid_roomStateData.LocationId; } }
        public DateTime Time { get { return m_grid_roomStateData.Time; } }
        public int RoomId { get { return m_grid_roomStateData.RoomId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_RoomState(int roomId)
        {
            Title = "New Room State";
            Width = 300;
            Height = 300;
            Content = CreateControls(roomId);

            GinTubBuilderManager.LoadAllLocations();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int roomId)
        {
            m_grid_roomStateData = new Grid_RoomStateData(null, null, null, new TimeSpan(00, 00, 00), roomId, true);
            return m_grid_roomStateData;
        }

        #endregion

        #endregion
    }
}
