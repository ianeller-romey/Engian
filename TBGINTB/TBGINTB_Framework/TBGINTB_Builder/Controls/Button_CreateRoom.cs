using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib;

using IANWork;


namespace TBGINTB_Builder.Controls
{
    public class Button_CreateRoom : Button_RoomGridsButton
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }

        #endregion


        #region MEMBER EVENTS
        /*
        public class CreateRoomEventArgs : RoutedEventArgs
        {
            public int Name { get; private set;}
            public int X { get; private set; } 
            public int Y { get; private set; }
            public int Z { get; private set; }
            public int Area { get; private set; }
        }
        public delegate void CreateRoomEventHandler(object sender, CreateRoomEventArgs e);
        public static readonly RoutedEvent CreateRoomEvent = EventManager.RegisterRoutedEvent(
            "CreateRoom", RoutingStrategy.Bubble, typeof(CreateRoomEventHandler), typeof(Button_CreateRoom));
        public event CreateRoomEventHandler CreateRoom
        {
            add { AddHandler(CreateRoomEvent, value); }
            remove { RemoveHandler(CreateRoomEvent, value); }
        }
        */
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Button_CreateRoom(int areaId, int x, int y, int z)
        {
            AreaId = areaId;
            RoomX = x;
            RoomY = y;
            RoomZ = z;
            Click += Button_CreateRoom_Click;
        }

        #endregion


        #region Private Functionality

        private void Button_CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            Window_TextBoxEntry window = new Window_TextBoxEntry("Room Name", "");
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddRoom(window.Text, RoomX, RoomY, RoomZ, AreaId);
        }

        #endregion

        #endregion
    }
}
