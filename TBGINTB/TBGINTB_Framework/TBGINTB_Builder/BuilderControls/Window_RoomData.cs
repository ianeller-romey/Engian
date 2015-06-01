using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;


namespace TBGINTB_Builder.BuilderControls
{
    public class Window_RoomData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_RoomData m_grid_roomData;

        #endregion


        #region MEMBER PROPERTIES

        public int? RoomId { get { return m_grid_roomData.RoomId; } }
        public string RoomName { get { return m_grid_roomData.RoomName; } }
        public int RoomX { get { return m_grid_roomData.RoomX; } }
        public int RoomY { get { return m_grid_roomData.RoomY; } }
        public int RoomZ { get { return m_grid_roomData.RoomZ; } }
        public int AreaId { get { return m_grid_roomData.AreaId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_RoomData(int? roomId, string roomName, int roomX, int roomY, int roomZ, int areaId)
        {
            Title = "Room Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(roomId, roomName, roomX, roomY, roomZ, areaId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? roomId, string roomName, int roomX, int roomY, int roomZ, int areaId)
        {
            m_grid_roomData = new Grid_RoomData(roomId, roomName, roomX, roomY, roomZ, areaId, true);
            return m_grid_roomData;
        }

        #endregion

        #endregion

    }
}
