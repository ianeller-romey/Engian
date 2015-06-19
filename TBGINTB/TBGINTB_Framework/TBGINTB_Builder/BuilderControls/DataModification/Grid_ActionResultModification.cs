using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ActionResultModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_ActionResultData m_grid_actionResult;

        #endregion


        #region MEMBER PROPERTIES

        public int? ActionResultId { get { return m_grid_actionResult.ActionResultId; } }
        public int? ActionResultResult { get { return m_grid_actionResult.ActionResultResult; } }
        public int? ActionResultAction { get { return m_grid_actionResult.ActionResultAction; } }
        private int NounId { get; set; }
        private int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ActionResultModification(int? actionResultId, int actionResultResult, int actionResultAction, int nounId, int paragraphStateId)
        {
            NounId = nounId;
            ParagraphStateId = paragraphStateId;
            CreateControls(actionResultId, actionResultResult, actionResultAction);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_actionResult.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_actionResult.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? actionResultId, int actionResultResult, int actionResultAction)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyActionResult = new Button() { Content = "Modify ActionResult" };
            button_modifyActionResult.Click += Button_ModifyActionResult_Click;
            this.SetGridRowColumn(button_modifyActionResult, 0, 0);

            m_grid_actionResult = new Grid_ActionResultData(actionResultId, actionResultResult, actionResultAction, NounId, ParagraphStateId, false);
            Border border_actionResult = new Border() { Style = Style_DefaultBorder.Instance };
            border_actionResult.Child = m_grid_actionResult;
            this.SetGridRowColumn(border_actionResult, 1, 0);
            m_grid_actionResult.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyActionResult_Click(object sender, RoutedEventArgs e)
        {
            Window_ActionResultData window =
                new Window_ActionResultData
                (
                    m_grid_actionResult.ActionResultId,
                    m_grid_actionResult.ActionResultResult,
                    m_grid_actionResult.ActionResultAction,
                    NounId,
                    ParagraphStateId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyActionResult
                (
                    window.ActionResultId.Value, 
                    window.ActionResultResult.Value, 
                    window.ActionResultAction.Value
                );
        }

        #endregion

        #endregion
    }
}
