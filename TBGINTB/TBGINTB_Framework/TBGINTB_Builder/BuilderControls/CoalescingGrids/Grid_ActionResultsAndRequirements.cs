using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.BuilderControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ActionResultsAndRequirements : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        StackPanel m_stackPanel_actionResults;
        Button 
            m_button_modifyActionResult,
            m_button_addRequirement;
        StackPanel m_stackPanel_requirements;

        #endregion


        #region MEMBER PROPERTIES

        public int ActionId { get; private set; }
        public int NounId { get; private set; }
        public int ParagraphStateId { get; private set; }

        public int SelectedActionResultId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ActionResultsAndRequirements(int actionId, int nounId, int paragraphStateId)
        {
            ActionId = actionId;
            NounId = nounId;
            ParagraphStateId = paragraphStateId;

            CreateControls();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ActionResultAdded += GinTubBuilderManager_ActionResultAdded;
            //GinTubBuilderManager.RequirementAdded += GinTubBuilderManager_RequirementAdded;

            foreach (var block in m_stackPanel_actionResults.Children.OfType<Grid_ActionResultData>())
                block.SetActiveAndRegisterForGinTubEvents();
            //foreach (var grid in m_stackPanel_requirements.Children.OfType<Grid_RequirementModification>())
            //    grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ActionResultAdded -= GinTubBuilderManager_ActionResultAdded;
            //GinTubBuilderManager.RequirementAdded -= GinTubBuilderManager_RequirementAdded;

            foreach (var block in m_stackPanel_actionResults.Children.OfType<Grid_ActionResultData>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            //foreach (var grid in m_stackPanel_requirements.Children.OfType<Grid_RequirementModification>())
            //    grid.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            ////////
            // Add ActionResult
            Button button_addActionResult = new Button() { Content = "Add ActionResult" };
            button_addActionResult.Click += Button_AddActionResult_Click;
            this.SetGridRowColumn(button_addActionResult, 0, 0);

            ////////
            // ActionResults
            m_button_modifyActionResult = new Button() { Content = "Modify ActionResult", IsEnabled = false };
            m_button_modifyActionResult.Click += Button_ModifyActionResult_Click;
            this.SetGridRowColumn(m_button_modifyActionResult, 1, 0);

            m_stackPanel_actionResults = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_actionResults, 2, 0);

            ////////
            // Add Requirement
            m_button_addRequirement = new Button() { Content = "Add Requirement", IsEnabled = false };
            m_button_addRequirement.Click += Button_AddRequirement_Click;
            this.SetGridRowColumn(m_button_addRequirement, 3, 0);

            ////////
            // Requirements
            m_stackPanel_requirements = new StackPanel() { Orientation = Orientation.Vertical };

            ScrollViewer scrollViewer_requirements =
                new ScrollViewer()
                {
                    HorizontalScrollBarVisibility = ScrollBarVisibility.Hidden,
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            scrollViewer_requirements.Content = m_stackPanel_requirements;
            this.SetGridRowColumn(scrollViewer_requirements, 4, 0);
        }

        private void GinTubBuilderManager_ActionResultAdded(object sender, GinTubBuilderManager.ActionResultAddedEventArgs args)
        {
            if (!m_stackPanel_actionResults.Children.OfType<Grid_ActionResultData>().Any(t => t.ActionResultId == args.Id))
            {
                Grid_ActionResultData grid = new Grid_ActionResultData(args.Id, args.Result, args.Action, NounId, ParagraphStateId, false);
                grid.MouseLeftButtonDown += Grid_ActionResultData_MouseLeftButtonDown;
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_actionResults.Children.Add(grid);
                GinTubBuilderManager.LoadAllResultsForAction(args.Action);
                GinTubBuilderManager.LoadAllActionsForNoun(NounId);
            }
        }

        /*void GinTubBuilderManager_RequirementAdded(object sender, GinTubBuilderManager.RequirementAddedEventArgs args)
        {
            if (!m_stackPanel_requirements.Children.OfType<Grid_RequirementData>().Any(a => a.RequirementId == args.Id))
            {
                Grid_RequirementModification grid = new Grid_RequirementModification(args.Id, args.VerbType, args.ActionResult, ParagraphStateId);
                m_stackPanel_requirements.Children.Add(grid);
                GinTubBuilderManager.LoadAllVerbTypes();
                GinTubBuilderManager.LoadAllActionResultsForParagraphState(ParagraphStateId);
            }
        }*/

        private void Button_AddActionResult_Click(object sender, RoutedEventArgs e)
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

        private void Button_ModifyActionResult_Click(object sender, RoutedEventArgs e)
        {
            Grid_ActionResultData grid = m_stackPanel_actionResults.Children.OfType<Grid_ActionResultData>().Single(g => g.ActionResultId.Value == SelectedActionResultId);
            Window_ActionResultData window = new Window_ActionResultData(grid.ActionResultId, grid.ActionResultResult, grid.ActionResultAction, NounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyActionResult
                (
                    window.ActionResultId.Value, 
                    window.ActionResultResult.Value, 
                    window.ActionResultAction.Value
                );
        }

        private void Button_AddRequirement_Click(object sender, RoutedEventArgs e)
        {
            //Window_RequirementData window = new Window_RequirementData(null, null, SelectedActionResultId, ParagraphStateId);
            //window.ShowDialog();
            //if (window.Accepted)
            //    GinTubBuilderManager.AddRequirement(window.RequirementVerbType.Value, window.RequirementActionResult.Value);
        }

        private void Grid_ActionResultData_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            Grid_ActionResultData grid = sender as Grid_ActionResultData;
            if (grid != null)
            {
                m_stackPanel_requirements.Children.Clear();

                SelectedActionResultId = grid.ActionResultId.Value;
                //GinTubBuilderManager.LoadAllRequirementsForActionResult(SelectedActionResultId);

                m_button_modifyActionResult.IsEnabled = true;
                m_button_addRequirement.IsEnabled = true;
            }
        }

        #endregion

        #endregion

    }
}
