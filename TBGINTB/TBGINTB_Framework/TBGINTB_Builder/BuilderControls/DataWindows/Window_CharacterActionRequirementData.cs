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
    public class Window_CharacterActionRequirementData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_CharacterActionRequirementData m_grid_characterActionRequirement;

        #endregion


        #region MEMBER PROPERTIES

        public int? CharacterActionRequirementId { get { return m_grid_characterActionRequirement.CharacterActionRequirementId; } }
        public int? CharacterActionRequirementCharacter { get { return m_grid_characterActionRequirement.CharacterActionRequirementCharacter; } }
        public int? CharacterActionRequirementAction { get { return m_grid_characterActionRequirement.CharacterActionRequirementAction; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_CharacterActionRequirementData(int? characterActionRequirementId, int? characterActionRequirementCharacter, int? characterActionRequirementAction, int nounId, int paragraphStateId)
        {
            Title = "CharacterActionRequirement Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(characterActionRequirementId, characterActionRequirementCharacter, characterActionRequirementAction, nounId, paragraphStateId);
            m_grid_characterActionRequirement.SetActiveAndRegisterForGinTubEvents(); // needed for possible characters, actions
            GinTubBuilderManager.LoadAllCharacters();
            GinTubBuilderManager.LoadAllActionsForNoun(nounId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? characterActionRequirementId, int? characterActionRequirementCharacter, int? characterActionRequirementAction, int nounId, int paragraphStateId)
        {
            m_grid_characterActionRequirement = new Grid_CharacterActionRequirementData(characterActionRequirementId, characterActionRequirementCharacter, characterActionRequirementAction, nounId, paragraphStateId, true);
            return m_grid_characterActionRequirement;
        }

        #endregion

        #endregion
    }
}
