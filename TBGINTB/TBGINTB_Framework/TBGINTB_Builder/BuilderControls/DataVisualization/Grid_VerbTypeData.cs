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
    public class Grid_VerbTypeData : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        ComboBox_VerbType m_comboBox_verbType;
        ItemsControl_Verb m_itemsControl_verb;

        private bool m_enableEditing;

        #endregion


        #region MEMBER PROPERTIES

        public int? SelectedVerbTypeId { get; private set; }
        public string SelectedVerbTypeName { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_comboBox_verbType,
                    m_itemsControl_verb
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_VerbTypeData(bool enableEditing)
        {
            m_enableEditing = enableEditing;

            CreateControls();

            m_comboBox_verbType.IsEnabled = m_enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            //m_comboBox_verbType.SetActiveAndRegisterForGinTubEvents();
            //m_itemsControl_verb.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            //m_comboBox_verbType.SetInactiveAndUnregisterFromGinTubEvents();
            //m_itemsControl_verb.SetInactiveAndUnregisterFromGinTubEvents();
        }
        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(50.0, GridUnitType.Star) });
            ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(50.0, GridUnitType.Star) });

            m_comboBox_verbType = 
                new ComboBox_VerbType() 
                { 
                    VerticalAlignment = System.Windows.VerticalAlignment.Top 
                };
            m_comboBox_verbType.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_verbType.SelectionChanged += ComboBox_VerbTypeData_SelectionChanged;
            this.SetGridRowColumn(m_comboBox_verbType, 0, 0);
        }

        private void ComboBox_VerbTypeData_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_VerbType comboBox = sender as ComboBox_VerbType;
            ComboBox_VerbType.ComboBoxItem_VerbType comboBoxItem = null;
            if (comboBox != null && (comboBoxItem = comboBox.SelectedItem as ComboBox_VerbType.ComboBoxItem_VerbType) != null)
            {
                SelectedVerbTypeId = comboBoxItem.VerbTypeId;
                SelectedVerbTypeName = comboBoxItem.VerbTypeName;

                if (m_itemsControl_verb != null)
                    Children.Remove(m_itemsControl_verb);

                m_itemsControl_verb = new ItemsControl_Verb(SelectedVerbTypeId.Value);
                m_itemsControl_verb.IsEnabled = m_enableEditing;
                m_itemsControl_verb.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
                this.SetGridRowColumn(m_itemsControl_verb, 0, 1);

                GinTubBuilderManager.LoadAllVerbsForVerbType(SelectedVerbTypeId.Value);
            }
            else if (comboBoxItem == null)
            {
                SelectedVerbTypeId = null;
                SelectedVerbTypeName = null;
            }
        }

        #endregion

        #endregion
    }
}
