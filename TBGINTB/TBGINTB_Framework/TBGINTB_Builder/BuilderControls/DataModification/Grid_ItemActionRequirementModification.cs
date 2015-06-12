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
    public class Grid_ItemActionRequirementModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_ItemActionRequirementData m_grid_actionItemActionRequirement;

        #endregion


        #region MEMBER PROPERTIES

        public int? ItemActionRequirementId { get { return m_grid_actionItemActionRequirement.ItemActionRequirementId; } }
        public int? ItemActionRequirementItem { get { return m_grid_actionItemActionRequirement.ItemActionRequirementItem; } }
        public int? ItemActionRequirementAction { get { return m_grid_actionItemActionRequirement.ItemActionRequirementAction; } }
        private int NounId { get; set; }
        private int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ItemActionRequirementModification(int? actionItemActionRequirementId, int itemActionRequirementItem, int itemActionRequirementAction, int nounId, int paragraphStateId)
        {
            NounId = nounId;
            ParagraphStateId = paragraphStateId;
            CreateControls(actionItemActionRequirementId, itemActionRequirementItem, itemActionRequirementAction);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_actionItemActionRequirement.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_actionItemActionRequirement.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? actionItemActionRequirementId, int itemActionRequirementItem, int itemActionRequirementAction)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyItemActionRequirement = new Button() { Content = "Modify ItemActionRequirement" };
            button_modifyItemActionRequirement.Click += Button_ModifyItemActionRequirement_Click;
            this.SetGridRowColumn(button_modifyItemActionRequirement, 0, 0);

            m_grid_actionItemActionRequirement = new Grid_ItemActionRequirementData(actionItemActionRequirementId, itemActionRequirementItem, itemActionRequirementAction, NounId, ParagraphStateId, false);
            this.SetGridRowColumn(m_grid_actionItemActionRequirement, 1, 0);
            m_grid_actionItemActionRequirement.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyItemActionRequirement_Click(object sender, RoutedEventArgs e)
        {
            Window_ItemActionRequirementData window =
                new Window_ItemActionRequirementData
                (
                    m_grid_actionItemActionRequirement.ItemActionRequirementId,
                    m_grid_actionItemActionRequirement.ItemActionRequirementItem,
                    m_grid_actionItemActionRequirement.ItemActionRequirementAction,
                    NounId,
                    ParagraphStateId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyItemActionRequirement
                (
                    window.ItemActionRequirementId.Value, 
                    window.ItemActionRequirementItem.Value, 
                    window.ItemActionRequirementAction.Value
                );
        }

        #endregion

        #endregion
    }
}
