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
    public class Window_EventActionRequirementData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_EventActionRequirementData m_grid_evntActionRequirement;

        #endregion


        #region MEMBER PROPERTIES

        public int? EventActionRequirementId { get { return m_grid_evntActionRequirement.EventActionRequirementId; } }
        public int? EventActionRequirementEvent { get { return m_grid_evntActionRequirement.EventActionRequirementEvent; } }
        public int? EventActionRequirementAction { get { return m_grid_evntActionRequirement.EventActionRequirementAction; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_EventActionRequirementData(int? evntActionRequirementId, int? evntActionRequirementEvent, int? evntActionRequirementAction, int nounId, int paragraphStateId)
        {
            Title = "EventActionRequirement Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(evntActionRequirementId, evntActionRequirementEvent, evntActionRequirementAction, nounId, paragraphStateId);
            m_grid_evntActionRequirement.SetActiveAndRegisterForGinTubEvents(); // needed for possible evnts, actions
            GinTubBuilderManager.LoadAllEvents();
            GinTubBuilderManager.LoadAllActionsForNoun(nounId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? evntActionRequirementId, int? evntActionRequirementEvent, int? evntActionRequirementAction, int nounId, int paragraphStateId)
        {
            m_grid_evntActionRequirement = new Grid_EventActionRequirementData(evntActionRequirementId, evntActionRequirementEvent, evntActionRequirementAction, nounId, paragraphStateId, true);
            return m_grid_evntActionRequirement;
        }

        #endregion

        #endregion
    }
}
