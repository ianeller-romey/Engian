using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Window_ParagraphData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ParagraphData m_grid_paragraphData;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphId { get { return m_grid_paragraphData.ParagraphId; } }
        public int? ParagraphState { get { return m_grid_paragraphData.ParagraphState; } }
        public string ParagraphText { get { return m_grid_paragraphData.ParagraphText; } }
        public int? RoomStateId { get { return m_grid_paragraphData.RoomStateId; } }
        public int RoomId { get { return m_grid_paragraphData.RoomId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ParagraphData(int? paragraphId, int? paragraphState, string paragraphText, int? roomStateId, int roomId)
        {
            Title = "Paragraph Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(paragraphId, paragraphState, paragraphText, roomStateId, roomId);
            GinTubBuilderManager.LoadAllLocations();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? paragraphId, int? paragraphState, string paragraphText, int? roomStateId, int roomId)
        {
            m_grid_paragraphData = new Grid_ParagraphData(paragraphId, paragraphState, paragraphText, roomStateId, roomId, true);
            return m_grid_paragraphData;
        }

        #endregion

        #endregion
    }
}
