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
    public class Grid_CharacterModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_CharacterData m_grid_character;

        #endregion


        #region MEMBER PROPERTIES

        public int? CharactereId { get { return m_grid_character.CharacterId; } }
        public string CharacterName { get { return m_grid_character.CharacterName; } }
        public string CharacterDescription { get { return m_grid_character.CharacterDescription; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_CharacterModification(int? characterId, string characterName, string characterDescription)
        {
            CreateControls(characterId, characterName, characterDescription);
        }

        public void SetActiveAndRegisterForGinTubCharacters()
        {
            m_grid_character.SetActiveAndRegisterForGinTubCharacters();
        }

        public void SetInactiveAndUnregisterFromGinTubCharacters()
        {
            m_grid_character.SetInactiveAndUnregisterFromGinTubCharacters();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? characterId, string characterName, string characterDescription)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyCharacter = new Button() { Content = "Modify Character" };
            button_modifyCharacter.Click += Button_ModifyCharacter_Click;
            this.SetGridRowColumn(button_modifyCharacter, 0, 0);

            m_grid_character = new Grid_CharacterData(characterId, characterName, characterDescription, false);
            this.SetGridRowColumn(m_grid_character, 1, 0);
            m_grid_character.SetActiveAndRegisterForGinTubCharacters();
        }

        private void Button_ModifyCharacter_Click(object sender, RoutedEventArgs e)
        {
            Window_CharacterData window =
                new Window_CharacterData(m_grid_character.CharacterId, m_grid_character.CharacterName, m_grid_character.CharacterDescription);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyCharacter(window.CharacterId.Value, window.CharacterName, window.CharacterDescription);
        }

        #endregion

        #endregion
    }
}
