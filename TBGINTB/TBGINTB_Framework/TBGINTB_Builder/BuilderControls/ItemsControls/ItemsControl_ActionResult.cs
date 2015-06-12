using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class ItemsControl_ActionResult : ItemsControl, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newActionResult = new Button() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES

        public int ActionId { get; set; }
        public int NounId { get; set; }
        public int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ItemsControl_ActionResult(int actionId, int nounId, int paragraphStateId)
        {
            ActionId = actionId;
            NounId = nounId;
            ParagraphStateId = paragraphStateId;

            c_button_newActionResult.Click += Button_NewActionResult_Click;

            IsEnabled = false;
            IsEnabledChanged += ItemsControl_ActionResult_IsEnabledChanged;
            IsEnabled = true;
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

        void GinTubBuilderManager_ActionResultAdded(object sender, GinTubBuilderManager.ActionResultAddedEventArgs args)
        {
            if (ActionId == args.Action && !Items.OfType<Grid_ActionResultModification>().Any(i => i.ActionResultId == args.Id))
            {
                Grid_ActionResultModification grid = new Grid_ActionResultModification(args.Id, args.Result, args.Action, NounId, ParagraphStateId);
                grid.SetActiveAndRegisterForGinTubEvents();
                Items.Add(grid);
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
                Window_ActionResultData window_actionResult = new Window_ActionResultData(null, null, null, NounId, ParagraphStateId, window_resultType.ResultTypeId.Value);
                window_actionResult.ShowDialog();
                if (window_actionResult.Accepted)
                    GinTubBuilderManager.AddActionResult
                    (
                        window_actionResult.ActionResultResult.Value,
                        window_actionResult.ActionResultAction.Value
                    );
            }
        }
        

        void Button_NewActionResult_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newActionResult)
                NewActionResultDialog();
        }

        void ItemsControl_ActionResult_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            ItemsControl_ActionResult control = sender as ItemsControl_ActionResult;
            if(sender != null && sender == this && e.Property == ItemsControl.IsEnabledProperty)
            {
                if ((bool)e.OldValue == true && (bool)e.NewValue == false)
                    Items.Remove(c_button_newActionResult);
                else if ((bool)e.OldValue == false && (bool)e.NewValue == true)
                    Items.Insert(0, c_button_newActionResult);
            }
        }

        #endregion

        #endregion
    }
}
