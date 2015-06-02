using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ParagraphStateUnderParagraph : Grid, IRegisterGinTubEventsOnlyWhenActive
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

        public Grid_ParagraphStateUnderParagraph(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId)
        {
           CreateControls(paragraphStateId, paragraphStateText, paragraphStateState, paragraphId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_paragraphState.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_paragraphState.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyParagraph = new Button() { Content = "Modify Paragraph State" };
            button_modifyParagraph.Click += Button_ModifyParagraph_Click;
            this.SetGridRowColumn(button_modifyParagraph, 0, 0);

            m_grid_paragraphState = new Grid_ParagraphStateData(paragraphStateId, paragraphStateText, paragraphStateState, paragraphId, false);
            this.SetGridRowColumn(m_grid_paragraphState, 1, 0);
            m_grid_paragraphState.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_ParagraphStateData window = 
                new Window_ParagraphStateData
                (
                    m_grid_paragraphState.ParagraphStateId,
                    m_grid_paragraphState.ParagraphStateText,
                    m_grid_paragraphState.ParagraphStateState,
                    m_grid_paragraphState.ParagraphId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyParagraphState
                (
                    window.ParagraphStateId.Value,
                    window.ParagraphStateText,
                    window.ParagraphStateState.Value,
                    window.ParagraphId
                );
        }

        #endregion

        #endregion
    }
}
