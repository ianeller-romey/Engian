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

        Grid_ParagraphData m_grid_paragraph;

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphStateUnderParagraph(int paragraphId, int paragraphState, string paragraphText, int roomStateId, int roomId)
        {
            CreateControls(paragraphId, paragraphState, paragraphText, roomStateId, roomId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_paragraph.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_paragraph.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int paragraphId, int paragraphState, string paragraphText, int roomStateId, int roomId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyParagraph = new Button() { Content = "Modify Paragraph" };
            button_modifyParagraph.Click += Button_ModifyParagraph_Click;
            this.SetGridRowColumn(button_modifyParagraph, 0, 0);

            m_grid_paragraph = new Grid_ParagraphData(paragraphId, paragraphState, paragraphText, roomStateId, roomId, false);
            this.SetGridRowColumn(m_grid_paragraph, 1, 0);
            m_grid_paragraph.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_ParagraphData window = 
                new Window_ParagraphData
                (
                    m_grid_paragraph.ParagraphId,
                    m_grid_paragraph.ParagraphState,
                    m_grid_paragraph.ParagraphText,
                    m_grid_paragraph.RoomStateId,
                    m_grid_paragraph.RoomId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyParagraph
                (
                    window.ParagraphId.Value,
                    window.ParagraphText,
                    window.RoomId,
                    window.RoomStateId.Value,
                    window.ParagraphState.Value
                );
        }

        #endregion

        #endregion
    }
}
