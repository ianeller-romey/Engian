using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib.Model;

using IANWork;


namespace TBGINTB_Builder.Controls
{
    public class Button_RoomGridsButton : Button
    {

        #region MEMBER PROPERTIES

        public int RoomX { get; protected set; }
        public int RoomY { get; protected set; }
        public int RoomZ { get; protected set; }

        #endregion

    }
}
