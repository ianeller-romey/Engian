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
    public class Grid_ActionModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_ActionData m_grid_action;

        #endregion


        #region MEMBER PROPERTIES

        public int? ActionId { get { return m_grid_action.ActionId; } }
        public int? ActionVerbType { get { return m_grid_action.ActionVerbType; } }
        public int? ActionNoun { get { return m_grid_action.ActionNoun; } }
        private int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ActionModification(int? actionId, int? actionVerbType, int? actionNoun, int paragraphStateId)
        {
            ParagraphStateId = paragraphStateId;
            CreateControls(actionId, actionVerbType, actionNoun);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_action.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_action.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? actionId, int? actionVerbType, int? actionNoun)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyAction = new Button() { Content = "Modify Action" };
            button_modifyAction.Click += Button_ModifyAction_Click;
            this.SetGridRowColumn(button_modifyAction, 0, 0);

            m_grid_action = new Grid_ActionData(actionId, actionVerbType, actionNoun, ParagraphStateId, false);
            this.SetGridRowColumn(m_grid_action, 1, 0);
            m_grid_action.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyAction_Click(object sender, RoutedEventArgs e)
        {
            Window_ActionData window =
                new Window_ActionData(m_grid_action.ActionId, m_grid_action.ActionVerbType, m_grid_action.ActionNoun, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyAction(window.ActionId.Value, window.ActionVerbType.Value, window.ActionNoun.Value);
        }

        #endregion

        #endregion
    }
}
