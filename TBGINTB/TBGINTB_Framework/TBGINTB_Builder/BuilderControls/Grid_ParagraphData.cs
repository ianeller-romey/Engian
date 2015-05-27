using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ParagraphData : Grid
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphId { get; private set; }
        public int? ParagraphState { get; private set; }
        public string ParagraphText { get; private set; }
        public int? RoomStateId { get; private set; }
        public int RoomId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphData(int? paragraphId, int? paragraphState, string paragraphText, int? roomStateId, int roomId)
        {

        }

        #endregion


        #region Private Functionality
        #endregion

        #endregion

    }
}
