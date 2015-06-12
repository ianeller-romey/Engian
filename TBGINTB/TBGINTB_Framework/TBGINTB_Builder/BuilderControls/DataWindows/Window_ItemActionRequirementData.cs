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
    public class Window_ItemActionRequirementData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ItemActionRequirementData m_grid_itemActionRequirement;

        #endregion


        #region MEMBER PROPERTIES

        public int? ItemActionRequirementId { get { return m_grid_itemActionRequirement.ItemActionRequirementId; } }
        public int? ItemActionRequirementItem { get { return m_grid_itemActionRequirement.ItemActionRequirementItem; } }
        public int? ItemActionRequirementAction { get { return m_grid_itemActionRequirement.ItemActionRequirementAction; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ItemActionRequirementData(int? itemActionRequirementId, int? itemActionRequirementItem, int? itemActionRequirementAction, int nounId, int paragraphStateId)
        {
            Title = "ItemActionRequirement Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(itemActionRequirementId, itemActionRequirementItem, itemActionRequirementAction, nounId, paragraphStateId);
            m_grid_itemActionRequirement.SetActiveAndRegisterForGinTubEvents(); // needed for possible items, actions
            GinTubBuilderManager.LoadAllItems();
            GinTubBuilderManager.LoadAllActionsForNoun(nounId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? itemActionRequirementId, int? itemActionRequirementItem, int? itemActionRequirementAction, int nounId, int paragraphStateId)
        {
            m_grid_itemActionRequirement = new Grid_ItemActionRequirementData(itemActionRequirementId, itemActionRequirementItem, itemActionRequirementAction, nounId, paragraphStateId, true);
            return m_grid_itemActionRequirement;
        }

        #endregion

        #endregion
    }
}
