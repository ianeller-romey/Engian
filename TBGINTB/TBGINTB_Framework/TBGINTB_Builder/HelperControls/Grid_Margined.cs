using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;


namespace TBGINTB_Builder.HelperControls
{
    public class Grid_Margined : Grid
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_Margined()
        {
            Style = Style_DefaultMargin.Instance;
        }

        #endregion


        #region Private Functionality
        #endregion

        #endregion

    }
}
