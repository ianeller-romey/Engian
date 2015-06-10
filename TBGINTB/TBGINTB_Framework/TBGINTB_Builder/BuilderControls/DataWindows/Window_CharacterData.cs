using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Window_CharacterData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_CharacterData m_grid_character;

        #endregion


        #region MEMBER PROPERTIES

        public int? CharacterId { get { return m_grid_character.CharacterId; } }
        public string CharacterName { get { return m_grid_character.CharacterName; } }
        public string CharacterDescription { get { return m_grid_character.CharacterDescription; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_CharacterData(int? characterId, string characterName, string characterDescription)
        {
            Title = "Character Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(characterId, characterName, characterDescription);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? characterId, string characterName, string characterDescription)
        {
            m_grid_character = new Grid_CharacterData(characterId, characterName, characterDescription, true);
            return m_grid_character;
        }

        #endregion

        #endregion
    }
}
