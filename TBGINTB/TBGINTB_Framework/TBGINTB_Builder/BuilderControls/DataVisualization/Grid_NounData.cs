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
    public class Grid_NounData : Grid
    {
        #region MEMBER FIELDS

        ComboBox_ParagraphStateNouns m_comboBox_text;

        #endregion


        #region MEMBER PROPERTIES

        public int? NounId { get; private set; }
        public string NounText { get; private set; }
        public int ParagraphStateId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_comboBox_text
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_NounData(int? nounId, string nounText, int paragraphStateId, bool enableEditing)
        {
            NounId = nounId;
            NounText = nounText;
            ParagraphStateId = paragraphStateId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.NounModified += GinTubBuilderManager_NounModified;

            GinTubBuilderManager.ParagraphStateAdded += GinTubBuilderManager_ParagraphStateAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.NounModified -= GinTubBuilderManager_NounModified;

            GinTubBuilderManager.ParagraphStateAdded += GinTubBuilderManager_ParagraphStateAdded;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
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
            TextBlock textBlock_id =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (NounId.HasValue) ? NounId.ToString() : "NewNoun"
                };
            Label label_id = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_id, 0, 1);
            grid_id.SetGridRowColumn(label_id, 0, 0);

            ////////
            // Text Grid
            Grid grid_text = new Grid();
            grid_text.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_text.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(grid_text, 1, 0);

            ////////
            // Text
            m_comboBox_text = new ComboBox_ParagraphStateNouns(ParagraphStateId);
            m_comboBox_text.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_text.SelectionChanged += ComboBox_Text_SelectionChanged;
            Label label_text = new Label() { Content = "Text:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_text.SetGridRowColumn(m_comboBox_text, 1, 0);
            grid_text.SetGridRowColumn(label_text, 0, 0);
        }

        void GinTubBuilderManager_NounModified(object sender, GinTubBuilderManager.NounModifiedEventArgs args)
        {
            if (NounId == args.Id)
            {
                SetNounText(args.Text);
                ParagraphStateId = args.ParagraphState;
            }
        }

        void GinTubBuilderManager_ParagraphStateAdded(object sender, GinTubBuilderManager.ParagraphStateAddedEventArgs args)
        {
            if (ParagraphStateId == args.Id)
                m_comboBox_text.SelectedItem = m_comboBox_text.Items.OfType<ComboBox_ParagraphStateNouns.ComboBoxItem_PossibleNoun>().SingleOrDefault(i => i.PossibleNounText == NounText);
        }

        private void SetNounText(string nounText)
        {
            NounText = nounText;
            m_comboBox_text.SelectedItem = m_comboBox_text.Items.OfType<ComboBox_ParagraphStateNouns.ComboBoxItem_PossibleNoun>().SingleOrDefault(n => n.PossibleNounText == nounText);
        }

        void ComboBox_Text_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_ParagraphStateNouns.ComboBoxItem_PossibleNoun item;
            if (m_comboBox_text.SelectedItem != null && (item = m_comboBox_text.SelectedItem as ComboBox_ParagraphStateNouns.ComboBoxItem_PossibleNoun) != null)
                NounText = item.PossibleNounText;
        }

        #endregion

        #endregion
    }
}
