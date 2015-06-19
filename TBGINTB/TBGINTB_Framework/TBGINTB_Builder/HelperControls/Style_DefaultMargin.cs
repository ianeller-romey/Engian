using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;


namespace TBGINTB_Builder.HelperControls
{
    public class Style_DefaultMargin : Style
    {
        #region MEMBER FIELDS

        private static readonly Thickness s_thickness = new Thickness(2.5);

        private static readonly Style_DefaultMargin s_style_defaultMargin = new Style_DefaultMargin();

        #endregion


        #region MEMBER PROPERTIES

        public static Style_DefaultMargin Instance
        {
            get { return s_style_defaultMargin; }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality
        #endregion


        #region Private Functionality

        private Style_DefaultMargin()
        {
            Setters.Add(new Setter(Control.MarginProperty, s_thickness));
        }

        #endregion

        #endregion

    }
}
