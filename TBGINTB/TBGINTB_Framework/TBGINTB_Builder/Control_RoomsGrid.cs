using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib.Model;


namespace TBGINTB_Builder
{
    public class Control_RoomsGrid : Grid
    {
        #region MEMBER FIELDS

        ObservableCollection<Room> m_rooms;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Control_RoomsGrid(ObservableCollection<Room> rooms)
        {
            m_rooms = rooms;
        }

        #endregion


        #region Private Functionality
        #endregion

        #endregion
    }
}
