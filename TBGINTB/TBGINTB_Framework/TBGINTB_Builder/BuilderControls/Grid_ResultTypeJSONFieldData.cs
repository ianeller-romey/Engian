using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ResultTypeJSONFieldData : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        TextBox m_textBox_jsonField;
        ComboBox_ResultType m_comboBox_resultType;

        #endregion


        #region MEMBER PROPERTIES

        public int? ResultTypeJSONFieldId { get; private set; }
        public string ResultTypeJSONFieldJSONField { get; private set; }
        public int ResultTypeId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_textBox_jsonField,
                    m_comboBox_resultType
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ResultTypeJSONFieldData(int? resultTypeJSONFieldId, string resultTypeJSONFieldJSONField, int resultTypeId, bool enableEditing)
        {
            ResultTypeJSONFieldId = resultTypeJSONFieldId;
            ResultTypeJSONFieldJSONField = resultTypeJSONFieldJSONField;
            ResultTypeId = resultTypeId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ResultTypeJSONFieldModified += GinTubBuilderManager_ResultTypeJSONFieldModified;

            GinTubBuilderManager.ResultTypeAdded += GinTubBuilderManager_ResultTypeAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ResultTypeJSONFieldModified -= GinTubBuilderManager_ResultTypeJSONFieldModified;

            GinTubBuilderManager.ResultTypeAdded -= GinTubBuilderManager_ResultTypeAdded;
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
            TextBlock textBlock_resultTypeJSONFieldId =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ResultTypeJSONFieldId.HasValue) ? ResultTypeJSONFieldId.ToString() : "NewResultTypeJSONField"
                };
            Label label_resultTypeJSONFieldId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_resultTypeJSONFieldId, 0, 1);
            grid_id.SetGridRowColumn(label_resultTypeJSONFieldId, 0, 0);

            ////////
            // Field Grid
            Grid grid_field = new Grid();
            grid_field.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_field.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(grid_field, 1, 0);

            ////////
            // Field
            m_textBox_jsonField = new TextBox() { VerticalAlignment = VerticalAlignment.Center, Text = ResultTypeJSONFieldJSONField };
            m_textBox_jsonField.TextChanged += TextBox_ResultTypeJSONFieldJSONField_TextChanged;
            Label label_resultTypeJSONFieldJSONField = new Label() { Content = "Field:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_field.SetGridRowColumn(m_textBox_jsonField, 1, 0);
            grid_field.SetGridRowColumn(label_resultTypeJSONFieldJSONField, 0, 0);

            ////////
            // ResultTypeJSONFieldTypeId Grid
            Grid grid_resultType = new Grid();
            grid_resultType.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_resultType.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_resultType, 2, 0);

            ////////
            // ResultTypeJSONFieldTypeId
            m_comboBox_resultType = new ComboBox_ResultType();
            m_comboBox_resultType.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_resultType.SelectionChanged += ComboBox_ResultType_SelectionChanged;
            SetResultTypeId(ResultTypeId);
            Label label_resultType = new Label() { Content = "Result Type:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_resultType.SetGridRowColumn(m_comboBox_resultType, 0, 1);
            grid_resultType.SetGridRowColumn(label_resultType, 0, 0);
        }

        void GinTubBuilderManager_ResultTypeJSONFieldModified(object sender, GinTubBuilderManager.ResultTypeJSONFieldModifiedEventArgs args)
        {
            if (ResultTypeJSONFieldId == args.Id)
            {
                SetResultTypeJSONFieldJSONField(args.JSONField);
                SetResultTypeId(args.ResultType);
            }
        }

        void GinTubBuilderManager_ResultTypeAdded(object sender, GinTubBuilderManager.ResultTypeAddedEventArgs args)
        {
            if (ResultTypeId == args.Id)
                m_comboBox_resultType.SelectedItem = m_comboBox_resultType.Items.OfType<ComboBox_ResultType.ComboBoxItem_ResultType>().SingleOrDefault(r => r.ResultTypeId == ResultTypeId);
        }

        private void SetResultTypeJSONFieldJSONField(string resultTypeJSONFieldJSONField)
        {
            m_textBox_jsonField.Text = resultTypeJSONFieldJSONField;
            if (!m_textBox_jsonField.IsEnabled)
                TextBox_ResultTypeJSONFieldJSONField_TextChanged(m_textBox_jsonField, new TextChangedEventArgs(TextBox.TextChangedEvent, UndoAction.Undo));
        }

        private void SetResultTypeId(int resultTypeJSONFieldTypeId)
        {
            ResultTypeId = resultTypeJSONFieldTypeId;
            m_comboBox_resultType.SelectedItem = m_comboBox_resultType.Items.OfType<ComboBox_ResultType.ComboBoxItem_ResultType>().SingleOrDefault(r => r.ResultTypeId == ResultTypeId);
        }

        void TextBox_ResultTypeJSONFieldJSONField_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb != null && tb == m_textBox_jsonField)
                ResultTypeJSONFieldJSONField = m_textBox_jsonField.Text;
        }

        private void ComboBox_ResultType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_ResultType comboBox = sender as ComboBox_ResultType;
            ComboBox_ResultType.ComboBoxItem_ResultType comboBoxItem = null;
            if (comboBox != null && (comboBoxItem = comboBox.SelectedItem as ComboBox_ResultType.ComboBoxItem_ResultType) != null)
                ResultTypeId = comboBoxItem.ResultTypeId;
        }

        #endregion

        #endregion
    }
}
