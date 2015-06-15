using System;
using System.Collections.Generic;
using System.IO;
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
    public class Grid_ActionResults : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newActionResult = new Button() { Content = "Add Result" };

        private StackPanel m_stackPanel_actionResults;

        #endregion


        #region MEMBER PROPERTIES

        public int ActionId { get; set; }
        public int NounId { get; set; }
        public int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ActionResults(int actionId, int nounId, int paragraphStateId)
        {
            ActionId = actionId;
            NounId = nounId;
            ParagraphStateId = paragraphStateId;

            CreateControls();

            c_button_newActionResult.Click += Button_NewActionResult_Click;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ActionResultAdded += GinTubBuilderManager_ActionResultAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ActionResultAdded -= GinTubBuilderManager_ActionResultAdded;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            this.SetGridRowColumn(c_button_newActionResult, 0, 0);

            m_stackPanel_actionResults = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_actionResults, 1, 0);
        }

        private void GinTubBuilderManager_ActionResultAdded(object sender, GinTubBuilderManager.ActionResultAddedEventArgs args)
        {
            if (ActionId == args.Action && !m_stackPanel_actionResults.Children.OfType<Grid_ActionResultModification>().Any(i => i.ActionResultId == args.Id))
            {
                Grid_ActionResultModification grid = new Grid_ActionResultModification(args.Id, args.Result, args.Action, NounId, ParagraphStateId);
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_actionResults.Children.Add(grid);
                GinTubBuilderManager.LoadAllResultsForActionResultType(args.Action);
                GinTubBuilderManager.LoadAllActionsForNoun(NounId);
            }
        }

        private void NewActionResultDialog()
        {
            Window_ResultTypeData window_resultType = new Window_ResultTypeData(null, null);
            window_resultType.ShowDialog();
            if (window_resultType.Accepted)
            {
                Window_ActionResultData window_actionResult = new Window_ActionResultData(null, null, ActionId, NounId, ParagraphStateId, window_resultType.ResultTypeId.Value);
                window_actionResult.ShowDialog();
                if (window_actionResult.Accepted)
                    GinTubBuilderManager.AddActionResult
                    (
                        window_actionResult.ActionResultResult.Value,
                        window_actionResult.ActionResultAction.Value
                    );
            }
        }
        
        private void Button_NewActionResult_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newActionResult)
                NewActionResultDialog();
        }

        #endregion

        #endregion
    }
}
