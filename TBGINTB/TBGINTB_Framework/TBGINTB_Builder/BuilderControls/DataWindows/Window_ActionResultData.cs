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
    public class Window_ActionResultData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ActionResultData m_grid_actionResult;

        #endregion


        #region MEMBER PROPERTIES

        public int? ActionResultId { get { return m_grid_actionResult.ActionResultId; } }
        public int? ActionResultResult { get { return m_grid_actionResult.ActionResultResult; } }
        public int? ActionResultAction { get { return m_grid_actionResult.ActionResultAction; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ActionResultData(int? actionResultId, int? actionResultResult, int? actionResultAction, int nounId, int paragraphStateId, int resultTypeId)
        {
            Title = "ActionResult Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(actionResultId, actionResultResult, actionResultAction, nounId, paragraphStateId);
            m_grid_actionResult.SetActiveAndRegisterForGinTubEvents(); // needed for possible results, actions
            GinTubBuilderManager.LoadAllResultsForResultType(resultTypeId);
            GinTubBuilderManager.LoadAllActionsForNoun(nounId);
        }

        public Window_ActionResultData(int? actionResultId, int? actionResultResult, int? actionResultAction, int nounId, int paragraphStateId)
        {
            Title = "ActionResult Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(actionResultId, actionResultResult, actionResultAction, nounId, paragraphStateId);
            m_grid_actionResult.SetActiveAndRegisterForGinTubEvents(); // needed for possible results, actions
            if(actionResultAction.HasValue)
                GinTubBuilderManager.LoadAllResultsForAction(actionResultAction.Value);
            GinTubBuilderManager.LoadAllActionsForNoun(nounId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? actionResultId, int? actionResultResult, int? actionResultAction, int nounId, int paragraphStateId)
        {
            m_grid_actionResult = new Grid_ActionResultData(actionResultId, actionResultResult, actionResultAction, nounId, paragraphStateId, true);
            return m_grid_actionResult;
        }

        #endregion

        #endregion
    }
}
