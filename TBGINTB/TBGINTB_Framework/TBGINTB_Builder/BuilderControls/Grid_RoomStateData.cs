using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_RoomStateData : Grid
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int RoomStateId { get; private set; }
        public int RoomId { get; private set; }
        public int RoomState { get; private set; }
        public int LocationId { get; private set; }
        public TimeSpan Time { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomStateData()
        {
            
        }

        #endregion

        #endregion
    }
}
