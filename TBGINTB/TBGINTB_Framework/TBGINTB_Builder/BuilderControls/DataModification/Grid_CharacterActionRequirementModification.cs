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
    public class Grid_CharacterActionRequirementModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_CharacterActionRequirementData m_grid_actionCharacterActionRequirement;

        #endregion


        #region MEMBER PROPERTIES

        public int? CharacterActionRequirementId { get { return m_grid_actionCharacterActionRequirement.CharacterActionRequirementId; } }
        public int? CharacterActionRequirementCharacter { get { return m_grid_actionCharacterActionRequirement.CharacterActionRequirementCharacter; } }
        public int? CharacterActionRequirementAction { get { return m_grid_actionCharacterActionRequirement.CharacterActionRequirementAction; } }
        private int NounId { get; set; }
        private int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_CharacterActionRequirementModification(int? actionCharacterActionRequirementId, int characterActionRequirementCharacter, int characterActionRequirementAction, int nounId, int paragraphStateId)
        {
            NounId = nounId;
            ParagraphStateId = paragraphStateId;
            CreateControls(actionCharacterActionRequirementId, characterActionRequirementCharacter, characterActionRequirementAction);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_actionCharacterActionRequirement.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_actionCharacterActionRequirement.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? actionCharacterActionRequirementId, int characterActionRequirementCharacter, int characterActionRequirementAction)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyCharacterActionRequirement = new Button() { Content = "Modify CharacterActionRequirement" };
            button_modifyCharacterActionRequirement.Click += Button_ModifyCharacterActionRequirement_Click;
            this.SetGridRowColumn(button_modifyCharacterActionRequirement, 0, 0);

            m_grid_actionCharacterActionRequirement = new Grid_CharacterActionRequirementData(actionCharacterActionRequirementId, characterActionRequirementCharacter, characterActionRequirementAction, NounId, ParagraphStateId, false);
            this.SetGridRowColumn(m_grid_actionCharacterActionRequirement, 1, 0);
            m_grid_actionCharacterActionRequirement.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyCharacterActionRequirement_Click(object sender, RoutedEventArgs e)
        {
            Window_CharacterActionRequirementData window =
                new Window_CharacterActionRequirementData
                (
                    m_grid_actionCharacterActionRequirement.CharacterActionRequirementId,
                    m_grid_actionCharacterActionRequirement.CharacterActionRequirementCharacter,
                    m_grid_actionCharacterActionRequirement.CharacterActionRequirementAction,
                    NounId,
                    ParagraphStateId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyCharacterActionRequirement
                (
                    window.CharacterActionRequirementId.Value, 
                    window.CharacterActionRequirementCharacter.Value, 
                    window.CharacterActionRequirementAction.Value
                );
        }

        #endregion

        #endregion
    }
}
