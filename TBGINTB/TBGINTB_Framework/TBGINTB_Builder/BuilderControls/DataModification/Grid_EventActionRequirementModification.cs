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
    public class Grid_EventActionRequirementModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_EventActionRequirementData m_grid_actionEventActionRequirement;

        #endregion


        #region MEMBER PROPERTIES

        public int? EventActionRequirementId { get { return m_grid_actionEventActionRequirement.EventActionRequirementId; } }
        public int? EventActionRequirementEvent { get { return m_grid_actionEventActionRequirement.EventActionRequirementEvent; } }
        public int? EventActionRequirementAction { get { return m_grid_actionEventActionRequirement.EventActionRequirementAction; } }
        private int NounId { get; set; }
        private int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_EventActionRequirementModification(int? actionEventActionRequirementId, int evntActionRequirementEvent, int evntActionRequirementAction, int nounId, int paragraphStateId)
        {
            NounId = nounId;
            ParagraphStateId = paragraphStateId;
            CreateControls(actionEventActionRequirementId, evntActionRequirementEvent, evntActionRequirementAction);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_actionEventActionRequirement.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_actionEventActionRequirement.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? actionEventActionRequirementId, int evntActionRequirementEvent, int evntActionRequirementAction)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyEventActionRequirement = new Button() { Content = "Modify EventActionRequirement" };
            button_modifyEventActionRequirement.Click += Button_ModifyEventActionRequirement_Click;
            this.SetGridRowColumn(button_modifyEventActionRequirement, 0, 0);

            m_grid_actionEventActionRequirement = new Grid_EventActionRequirementData(actionEventActionRequirementId, evntActionRequirementEvent, evntActionRequirementAction, NounId, ParagraphStateId, false);
            this.SetGridRowColumn(m_grid_actionEventActionRequirement, 1, 0);
            m_grid_actionEventActionRequirement.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyEventActionRequirement_Click(object sender, RoutedEventArgs e)
        {
            Window_EventActionRequirementData window =
                new Window_EventActionRequirementData
                (
                    m_grid_actionEventActionRequirement.EventActionRequirementId,
                    m_grid_actionEventActionRequirement.EventActionRequirementEvent,
                    m_grid_actionEventActionRequirement.EventActionRequirementAction,
                    NounId,
                    ParagraphStateId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyEventActionRequirement
                (
                    window.EventActionRequirementId.Value, 
                    window.EventActionRequirementEvent.Value, 
                    window.EventActionRequirementAction.Value
                );
        }

        #endregion

        #endregion
    }
}
