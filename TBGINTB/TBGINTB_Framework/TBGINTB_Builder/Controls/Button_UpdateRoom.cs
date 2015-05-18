using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

using TBGINTB_Builder.Lib.Model;


namespace TBGINTB_Builder.Controls
{
    public class Button_UpdateRoom : Button_RoomGridsButton
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int RoomId { get; private set; }
        public string RoomName { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Button_UpdateRoom(int id, string name, int x, int y, int z)
        {
            RoomId = id;
            RoomName = name;
            RoomX = x;
            RoomY = y;
            RoomZ = z;

            Content = RoomName;
            ToolTip = RoomName;
            FontSize = 9.0;
            Background = Brushes.DarkGray;
        }

        #endregion


        #region Private Functionality
        #endregion

        #endregion
    }
}
