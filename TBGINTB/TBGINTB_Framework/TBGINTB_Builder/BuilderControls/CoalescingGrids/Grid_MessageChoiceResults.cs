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
    public class Grid_MessageChoiceResults : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newMessageChoiceResult = new Button() { Content = "Add Result" };

        private StackPanel m_stackPanel_messageChoiceResults;

        #endregion


        #region MEMBER PROPERTIES

        public int MessageChoiceId { get; set; }
        public int MessageId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_MessageChoiceResults(int messageChoiceId, int messageId)
        {
            MessageChoiceId = messageChoiceId;
            MessageId = messageId;

            CreateControls();

            c_button_newMessageChoiceResult.Click += Button_NewMessageChoiceResult_Click;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.MessageChoiceResultAdded += GinTubBuilderManager_MessageChoiceResultAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.MessageChoiceResultAdded -= GinTubBuilderManager_MessageChoiceResultAdded;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            this.SetGridRowColumn(c_button_newMessageChoiceResult, 0, 0);

            m_stackPanel_messageChoiceResults = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_messageChoiceResults, 1, 0);
        }

        private void GinTubBuilderManager_MessageChoiceResultAdded(object sender, GinTubBuilderManager.MessageChoiceResultAddedEventArgs args)
        {
            if (MessageChoiceId == args.MessageChoice && !m_stackPanel_messageChoiceResults.Children.OfType<Grid_MessageChoiceResultModification>().Any(i => i.MessageChoiceResultId == args.Id))
            {
                Grid_MessageChoiceResultModification grid = new Grid_MessageChoiceResultModification(args.Id, args.Result, args.MessageChoice, MessageId);
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_messageChoiceResults.Children.Add(grid);
                GinTubBuilderManager.LoadAllResultsForMessageChoiceResultType(args.MessageChoice);
                GinTubBuilderManager.LoadAllMessageChoicesForMessage(MessageId);
            }
        }

        private void NewMessageChoiceResultDialog()
        {
            Window_ResultTypeData window_resultType = new Window_ResultTypeData(null, null);
            window_resultType.ShowDialog();
            if (window_resultType.Accepted)
            {
                Window_MessageChoiceResultData window_messageChoiceResult = new Window_MessageChoiceResultData(null, null, MessageChoiceId, MessageId, window_resultType.ResultTypeId.Value);
                window_messageChoiceResult.ShowDialog();
                if (window_messageChoiceResult.Accepted)
                    GinTubBuilderManager.AddMessageChoiceResult
                    (
                        window_messageChoiceResult.MessageChoiceResultResult.Value,
                        window_messageChoiceResult.MessageChoiceResultMessageChoice.Value
                    );
            }
        }
        
        private void Button_NewMessageChoiceResult_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newMessageChoiceResult)
                NewMessageChoiceResultDialog();
        }

        #endregion

        #endregion
    }
}
