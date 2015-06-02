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
    public class Window_ParagraphStateData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ParagraphStateData m_grid_paragraphState;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphStateId { get { return m_grid_paragraphState.ParagraphStateId; } }
        public string ParagraphStateText { get { return m_grid_paragraphState.ParagraphStateText; } }
        public int? ParagraphStateState { get { return m_grid_paragraphState.ParagraphStateState; } }
        public int ParagraphId { get { return m_grid_paragraphState.ParagraphId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ParagraphStateData(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId)
        {
            Title = "Paragraph State Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(paragraphId, paragraphStateText, paragraphStateState, paragraphId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId)
        {
            m_grid_paragraphState = new Grid_ParagraphStateData(paragraphId, paragraphStateText, paragraphStateState, paragraphId, true);
            return m_grid_paragraphState;
        }

        #endregion

        #endregion
    }
}
