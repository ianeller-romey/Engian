using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Button_RoomOnFloor : Button
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; protected set; }
        public int RoomId { get; protected set; }
        public string RoomName { get; protected set; }
        public int RoomX { get; protected set; }
        public int RoomY { get; protected set; }
        public int RoomZ { get; protected set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Button_RoomOnFloor(int areaId, int x, int y, int z)
        {
            AreaId = areaId;
            RoomX = x;
            RoomY = y;
            RoomZ = z;

            FontSize = 9.0;

            RegisterGinTubHandlers();

            HasNoRoom();
        }

        public Button_RoomOnFloor(int areaId, int id, string name, int x, int y, int z)
        {
            AreaId = areaId;
            RoomX = x;
            RoomY = y;
            RoomZ = z;

            FontSize = 9.0;

            RegisterGinTubHandlers();

            HasRoom(id, name);
        }

        public void SetFloor(int z)
        {
            RoomZ = z;
        }

        public void HasRoom(int id, string name)
        {
            RoomId = id;
            RoomName = name;

            Content = RoomName;
            ToolTip = RoomName;
            Background = Brushes.LightBlue;

            RemoveClickHandlers();
            Click += Button_UpdateRoom_Click;
        }

        public void HasNoRoom()
        {
            RoomId = -1;
            RoomName = string.Empty;

            Content = RoomName;
            ToolTip = null;
            Background = Brushes.LightGray;

            RemoveClickHandlers();
            Click += Button_CreateRoom_Click;
        }

        #endregion


        #region Private Functionality

        private void Button_CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            Window_TextEntry window = new Window_TextEntry("Room Name", "");
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddRoom(window.Text, RoomX, RoomY, RoomZ, AreaId);
        }

        private void Button_UpdateRoom_Click(object sender, RoutedEventArgs e)
        {
            GinTubBuilderManager.GetRoom(RoomId);
        }

        private void RegisterGinTubHandlers()
        {
            GinTubBuilderManager.RoomAdded += GinTubBuilderManager_RoomAdded;
            GinTubBuilderManager.RoomModified += GinTubBuilderManager_RoomModified;
        }

        private void RemoveClickHandlers()
        {
            // Remove everything, in case we accidentallly call "HasRoom" or "HasNoRoom" twice
            Click -= Button_CreateRoom_Click;
            Click -= Button_UpdateRoom_Click;
        }

        private void GinTubBuilderManager_RoomAdded(object sender, GinTubBuilderManager.RoomAddedEventArgs args)
        {
            if (args.Area == AreaId && args.X == RoomX && args.Y == RoomY && args.Z == RoomZ)
                HasRoom(args.Id, args.Name);
        }

        private void GinTubBuilderManager_RoomModified(object sender, GinTubBuilderManager.RoomModifiedEventArgs args)
        {
            if (args.Area == AreaId && args.X == RoomX && args.Y == RoomY && args.Z == RoomZ)
                HasRoom(args.Id, args.Name);
        }

        #endregion

        #endregion

    }
}
