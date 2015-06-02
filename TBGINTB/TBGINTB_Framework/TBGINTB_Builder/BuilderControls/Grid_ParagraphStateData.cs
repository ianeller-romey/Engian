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
    public class Grid_ParagraphStateData : Grid
    {
        #region MEMBER FIELDS

        TextBox m_textBox_paragraphStateText;
        TextBlock m_textBlock_paragraphStateState;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphStateId { get; private set; }
        public string ParagraphStateText { get; private set; }
        public int? ParagraphStateState { get; private set; }
        public int ParagraphId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_textBox_paragraphStateText,
                    m_textBlock_paragraphStateState
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphStateData(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId, bool enableEditing)
        {
            ParagraphStateId = paragraphStateId;
            ParagraphStateText = paragraphStateText;
            ParagraphStateState = paragraphStateState;
            ParagraphId = paragraphId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
            if (!enableEditing)
                MouseLeftButtonDown += Grid_ParagraphStateData_MouseLeftButtonDown;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphStateModified += GinTubBuilderManager_ParagraphStateModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphStateModified -= GinTubBuilderManager_ParagraphStateModified;
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
            TextBlock textBlock_paragraphStateId =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ParagraphStateId.HasValue) ? ParagraphStateId.ToString() : "NewParagraphState"
                };
            Label label_paragraphStateId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_paragraphStateId, 0, 1);
            grid_id.SetGridRowColumn(label_paragraphStateId, 0, 0);

            ////////
            // Text Grid
            Grid grid_text = new Grid();
            grid_text.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_text.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(grid_text, 1, 0);

            ////////
            // Text
            m_textBox_paragraphStateText = new TextBox() { VerticalAlignment = VerticalAlignment.Center, Text = ParagraphStateText };
            m_textBox_paragraphStateText.TextChanged += TextBox_ParagraphStateText_TextChanged;
            Label label_paragraphStateText = new Label() { Content = "Text:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_text.SetGridRowColumn(m_textBox_paragraphStateText, 1, 0);
            grid_text.SetGridRowColumn(label_paragraphStateText, 0, 0);
            
            ////////
            // State Grid
            Grid grid_state = new Grid();
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_state, 2, 0);
            
            ////////
            // State
            m_textBlock_paragraphStateState = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            SetParagraphStateState(ParagraphStateState);
            Label label_paragraphStateState = new Label() { Content = "State:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_state.SetGridRowColumn(m_textBlock_paragraphStateState, 0, 1);
            grid_state.SetGridRowColumn(label_paragraphStateState, 0, 0);
        }

        void GinTubBuilderManager_ParagraphStateModified(object sender, GinTubBuilderManager.ParagraphStateModifiedEventArgs args)
        {
            if (ParagraphStateId == args.Id)
            {
                SetParagraphStateText(args.Text);
                SetParagraphStateState(args.State);
                ParagraphId = args.Paragraph;
            }
        }

        private void SetParagraphStateState(int? paragraphStateState)
        {
            m_textBlock_paragraphStateState.Text = (paragraphStateState.HasValue) ? paragraphStateState.ToString() : "NewState";
        }

        private void SetParagraphStateText(string paragraphStateText)
        {
            m_textBox_paragraphStateText.Text = paragraphStateText;
            if (!m_textBox_paragraphStateText.IsEnabled)
                TextBox_ParagraphStateText_TextChanged(m_textBox_paragraphStateText, new TextChangedEventArgs(TextBox.TextChangedEvent, UndoAction.Undo));
        }

        void TextBox_ParagraphStateText_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb != null && tb == m_textBox_paragraphStateText)
                ParagraphStateText = m_textBox_paragraphStateText.Text;
        }

        private void Grid_ParagraphStateData_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            if (ParagraphStateId.HasValue)
                GinTubBuilderManager.GetParagraphState(ParagraphStateId.Value);
        }

        #endregion

        #endregion
    }
}
