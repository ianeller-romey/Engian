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
    public class Grid_ParagraphTextStateData : Grid
    {
        #region MEMBER FIELDS

        TextBox m_textBox_paragraphTextStateText;
        TextBlock m_textBlock_paragraphTextStateState;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphTextStateId { get; private set; }
        public string ParagraphTextStateText { get; private set; }
        public int? ParagraphTextStateState { get; private set; }
        public int ParagraphId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_textBox_paragraphTextStateText,
                    m_textBlock_paragraphTextStateState
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphTextStateData(int? paragraphTextStateId, string paragraphTextStateText, int? paragraphTextStateState, int paragraphId, bool enableEditing)
        {
            ParagraphTextStateId = paragraphTextStateId;
            ParagraphTextStateText = paragraphTextStateText;
            ParagraphTextStateState = paragraphTextStateState;
            ParagraphId = paragraphId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphTextStateModified += GinTubBuilderManager_ParagraphTextStateModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphTextStateModified -= GinTubBuilderManager_ParagraphTextStateModified;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            
            ////////
            // Id Grid
            Grid grid_id = new Grid();
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_id, 0, 0);

            ////////
            // Id
            TextBlock textBlock_paragraphTextStateId =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ParagraphTextStateId.HasValue) ? ParagraphTextStateId.ToString() : "NewParagraphTextState"
                };
            Label label_paragraphTextStateId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_paragraphTextStateId, 0, 1);
            grid_id.SetGridRowColumn(label_paragraphTextStateId, 0, 0);

            ////////
            // Text Grid
            Grid grid_text = new Grid();
            grid_text.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_text.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(grid_text, 1, 0);

            ////////
            // Text
            m_textBox_paragraphTextStateText = new TextBox() { VerticalAlignment = VerticalAlignment.Center, Text = ParagraphTextStateText };
            m_textBox_paragraphTextStateText.TextChanged += TextBox_ParagraphTextStateText_TextChanged;
            Label label_paragraphTextStateText = new Label() { Content = "Text:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_text.SetGridRowColumn(m_textBox_paragraphTextStateText, 1, 0);
            grid_text.SetGridRowColumn(label_paragraphTextStateText, 0, 0);
            
            ////////
            // State Grid
            Grid grid_state = new Grid();
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_state, 2, 0);
            
            ////////
            // State
            m_textBlock_paragraphTextStateState = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            SetParagraphTextStateState(ParagraphTextStateState);
            Label label_paragraphTextStateState = new Label() { Content = "State:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_state.SetGridRowColumn(m_textBlock_paragraphTextStateState, 0, 1);
            grid_state.SetGridRowColumn(label_paragraphTextStateState, 0, 0);
        }

        void GinTubBuilderManager_ParagraphTextStateModified(object sender, GinTubBuilderManager.ParagraphTextStateModifiedEventArgs args)
        {
            if (ParagraphTextStateId == args.Id)
            {
                SetParagraphTextStateText(args.Text);
                SetParagraphTextStateState(args.State);
                ParagraphId = args.Paragraph;
            }
        }

        private void SetParagraphTextStateState(int? paragraphTextStateState)
        {
            m_textBlock_paragraphTextStateState.Text = (paragraphTextStateState.HasValue) ? paragraphTextStateState.ToString() : "NewState";
        }

        private void SetParagraphTextStateText(string paragraphTextStateText)
        {
            m_textBox_paragraphTextStateText.Text = paragraphTextStateText;
            if (!m_textBox_paragraphTextStateText.IsEnabled)
                TextBox_ParagraphTextStateText_TextChanged(m_textBox_paragraphTextStateText, new TextChangedEventArgs(TextBox.TextChangedEvent, UndoAction.Undo));
        }

        void TextBox_ParagraphTextStateText_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb != null && tb == m_textBox_paragraphTextStateText)
                ParagraphTextStateText = m_textBox_paragraphTextStateText.Text;
        }

        #endregion

        #endregion
    }
}
