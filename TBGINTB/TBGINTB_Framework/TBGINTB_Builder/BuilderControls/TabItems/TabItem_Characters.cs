using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class TabItem_Characters : TabItem, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid m_grid_main;
        ComboBox_Character m_comboBox_character;
        Grid_CharacterModification m_grid_character;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_Characters()
        {
            Header = "Characters";
            Content = CreateControls();

            GinTubBuilderManager.LoadAllCharacters();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            if (m_grid_character != null)
                m_grid_character.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            if (m_grid_character != null)
                m_grid_character.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            m_grid_main = new Grid();
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            m_comboBox_character = new ComboBox_Character();
            m_comboBox_character.SetActiveAndRegisterForGinTubEvents();
            m_comboBox_character.SelectionChanged += ComboBox_Event_SelectionChanged;
            m_grid_main.SetGridRowColumn(m_comboBox_character, 0, 0);

            return m_grid_main;
        }

        private void ComboBox_Event_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_Character comboBox = sender as ComboBox_Character;
            ComboBox_Character.ComboBoxItem_Character comboBoxItem;
            if (comboBox.SelectedItem != null && (comboBoxItem = comboBox.SelectedItem as ComboBox_Character.ComboBoxItem_Character) != null)
            {
                if (m_grid_character != null)
                    m_grid_main.Children.Remove(m_grid_character);
                m_grid_character = new Grid_CharacterModification(comboBoxItem.CharacterId, comboBoxItem.CharacterName, comboBoxItem.CharacterDescription);
                m_grid_character.SetActiveAndRegisterForGinTubEvents();
                m_grid_main.SetGridRowColumn(m_grid_character, 1, 0);
            }
        }

        #endregion

        #endregion

    }
}
