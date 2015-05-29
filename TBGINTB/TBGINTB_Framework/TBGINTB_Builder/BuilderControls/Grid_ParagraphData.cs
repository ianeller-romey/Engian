using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.BuilderControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ParagraphData : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        TextBlock m_textBlock_paragraphState;
        TextBox m_textBox_paragraphText;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphId { get; private set; }
        public int? ParagraphState { get; private set; }
        public string ParagraphText { get; private set; }
        public int? RoomStateId { get; private set; }
        public int RoomId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_textBox_paragraphText
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphData(int? paragraphId, int? paragraphState, string paragraphText, int? roomStateId, int roomId, bool enableEditing)
        {
            ParagraphId = paragraphId;
            ParagraphState = paragraphState;
            ParagraphText = paragraphText;
            RoomStateId = roomStateId;
            RoomId = roomId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphModified += GinTubBuilderManager_ParagraphModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphModified -= GinTubBuilderManager_ParagraphModified;
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
            TextBlock textBlock_paragraphId =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ParagraphId.HasValue) ? ParagraphId.ToString() : "NewParagraph"
                };
            Label label_paragraphId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_paragraphId, 0, 1);
            grid_id.SetGridRowColumn(label_paragraphId, 0, 0);

            ////////
            // State Grid
            Grid grid_state = new Grid();
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_state, 1, 0);

            ////////
            // State
            m_textBlock_paragraphState =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ParagraphState.HasValue) ? ParagraphState.ToString() : "NewState"
                };
            Label label_paragraphState = new Label() { Content = "State:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_state.SetGridRowColumn(m_textBlock_paragraphState, 0, 1);
            grid_state.SetGridRowColumn(label_paragraphState, 0, 0);

            ////////
            // Text
            m_textBox_paragraphText = new TextBox() { VerticalAlignment = VerticalAlignment.Center, Text = ParagraphText };
            m_textBox_paragraphText.TextChanged += TextBox_ParagraphText_TextChanged;
            this.SetGridRowColumn(m_textBox_paragraphText, 2, 0);
        }

        private void GinTubBuilderManager_ParagraphModified(object sender, GinTubBuilderManager.ParagraphModifiedEventArgs args)
        {
            if (args.Id == ParagraphId)
            {
                SetParagraphState(args.State);
                SetParagraphText(args.Text);
                RoomStateId = args.RoomState;
                RoomId = args.Room;
            }
        }

        private void SetParagraphState(int state)
        {
            ParagraphState = state;
            m_textBlock_paragraphState.Text = ParagraphState.ToString();
        }

        private void SetParagraphText(string text)
        {
            m_textBox_paragraphText.Text = text;
            if (!m_textBox_paragraphText.IsEnabled)
                TextBox_ParagraphText_TextChanged(m_textBox_paragraphText, new TextChangedEventArgs(TextBox.TextChangedEvent, UndoAction.Undo));
        }

        void TextBox_ParagraphText_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb != null && tb == m_textBox_paragraphText)
                ParagraphText = m_textBox_paragraphText.Text;
        }

        #endregion

        #endregion

    }
}
