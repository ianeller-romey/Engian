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
    public class Grid_ActionData : Grid
    {
        #region MEMBER FIELDS

        ComboBox_VerbType m_comboBox_actionVerbType;
        ComboBox_Noun m_comboBox_actionNoun;

        #endregion


        #region MEMBER PROPERTIES

        public int? ActionId { get; private set; }
        public int? ActionVerbType { get; private set; }
        public int? ActionNoun { get; private set; }
        private int ParagraphStateId { get; set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_comboBox_actionVerbType,
                    m_comboBox_actionNoun
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ActionData(int? actionId, int? actionVerbType, int? actionNoun, int paragraphStateId, bool enableEditing)
        {
            ActionId = actionId;
            ActionVerbType = actionVerbType;
            ActionNoun = actionNoun;
            ParagraphStateId = paragraphStateId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;

            GinTubBuilderManager.VerbTypeAdded += GinTubBuilderManager_VerbTypeAdded;
            GinTubBuilderManager.NounAdded += GinTubBuilderManager_NounAdded;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ActionModified += GinTubBuilderManager_ActionModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ActionModified -= GinTubBuilderManager_ActionModified;
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
            TextBlock textBlock_nounId =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ActionId.HasValue) ? ActionId.ToString() : "NewAction"
                };
            Label label_nounId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_nounId, 0, 1);
            grid_id.SetGridRowColumn(label_nounId, 0, 0);

            ////////
            // VerbType Grid
            Grid grid_verbType = new Grid();
            grid_verbType.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_verbType.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(grid_verbType, 1, 0);

            ////////
            // VerbType
            m_comboBox_actionVerbType = new ComboBox_VerbType();
            m_comboBox_actionVerbType.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_actionVerbType.SelectionChanged += ComboBox_ActionVerbType_SelectionChanged;
            Label label_actionVerbType = new Label() { Content = "Verb Type:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_verbType.SetGridRowColumn(m_comboBox_actionVerbType, 1, 0);
            grid_verbType.SetGridRowColumn(label_actionVerbType, 0, 0);

            ////////
            // Noun Grid
            Grid grid_noun = new Grid();
            grid_noun.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_noun.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(grid_noun, 2, 0);

            ////////
            // Noun
            m_comboBox_actionNoun = new ComboBox_Noun(ParagraphStateId);
            m_comboBox_actionNoun.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_actionNoun.SelectionChanged += ComboBox_ActionNoun_SelectionChanged;
            Label label_actionNoun = new Label() { Content = "Noun:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_noun.SetGridRowColumn(m_comboBox_actionNoun, 1, 0);
            grid_noun.SetGridRowColumn(label_actionNoun, 0, 0);
        }

        void GinTubBuilderManager_ActionModified(object sender, GinTubBuilderManager.ActionModifiedEventArgs args)
        {
            if(ActionId == args.Id)
            {
                SetActionVerbType(args.VerbType);
                SetActionNoun(args.Noun);
            }
        }

        void GinTubBuilderManager_VerbTypeAdded(object sender, GinTubBuilderManager.VerbTypeAddedEventArgs args)
        {
            ResetActionVerbType(args.Id);
        }
        
        void GinTubBuilderManager_NounAdded(object sender, GinTubBuilderManager.NounAddedEventArgs args)
        {
            if (ParagraphStateId == args.ParagraphState)
                ResetActionNoun(args.Id);
        }

        private void SetActionVerbType(int actionVerbType)
        {
            ComboBox_VerbType.ComboBoxItem_VerbType item =
                m_comboBox_actionVerbType.Items.OfType<ComboBox_VerbType.ComboBoxItem_VerbType>().
                SingleOrDefault(i => i.VerbTypeId == actionVerbType);
            if (item != null)
                m_comboBox_actionVerbType.SelectedItem = item;
        }

        private void SetActionNoun(int actionNoun)
        {
            ComboBox_Noun.ComboBoxItem_Noun item = m_comboBox_actionNoun.Items.OfType<ComboBox_Noun.ComboBoxItem_Noun>().
                SingleOrDefault(i => i.NounId == actionNoun);
            if (item != null)
                m_comboBox_actionNoun.SelectedItem = item;
        }

        private void ResetActionVerbType(int actionVerbType)
        {
            ComboBox_VerbType.ComboBoxItem_VerbType item =
                m_comboBox_actionVerbType.Items.OfType<ComboBox_VerbType.ComboBoxItem_VerbType>().
                SingleOrDefault(i => ActionVerbType.HasValue && ActionVerbType.Value == actionVerbType && i.VerbTypeId == actionVerbType);
            if (item != null)
                m_comboBox_actionVerbType.SelectedItem = item;
        }

        private void ResetActionNoun(int actionNoun)
        {
            ComboBox_Noun.ComboBoxItem_Noun item = m_comboBox_actionNoun.Items.OfType<ComboBox_Noun.ComboBoxItem_Noun>().
                SingleOrDefault(i => ActionNoun.HasValue && ActionNoun.Value == actionNoun && i.NounId == actionNoun);
            if (item != null)
                m_comboBox_actionNoun.SelectedItem = item;
        }

        void ComboBox_ActionVerbType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_VerbType.ComboBoxItem_VerbType item;
            if (m_comboBox_actionVerbType.SelectedItem != null && (item = m_comboBox_actionVerbType.SelectedItem as ComboBox_VerbType.ComboBoxItem_VerbType) != null)
                ActionVerbType = item.VerbTypeId;
        }

        void ComboBox_ActionNoun_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_Noun.ComboBoxItem_Noun item;
            if (m_comboBox_actionNoun.SelectedItem != null && (item = m_comboBox_actionNoun.SelectedItem as ComboBox_Noun.ComboBoxItem_Noun) != null)
                ActionNoun = item.NounId;
        }

        #endregion

        #endregion
    }
}
