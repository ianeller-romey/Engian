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
    public class Grid_MessageChoiceResultModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_MessageChoiceResultData m_grid_messageChoiceMessageChoiceResult;

        #endregion


        #region MEMBER PROPERTIES

        public int? MessageChoiceResultId { get { return m_grid_messageChoiceMessageChoiceResult.MessageChoiceResultId; } }
        public int? MessageChoiceResultResult { get { return m_grid_messageChoiceMessageChoiceResult.MessageChoiceResultResult; } }
        public int? MessageChoiceResultMessageChoice { get { return m_grid_messageChoiceMessageChoiceResult.MessageChoiceResultMessageChoice; } }
        private int MessageId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_MessageChoiceResultModification(int? messageChoiceMessageChoiceResultId, int messageChoiceResultResult, int messageChoiceResultMessageChoice, int messageId)
        {
            MessageId = messageId;
            CreateControls(messageChoiceMessageChoiceResultId, messageChoiceResultResult, messageChoiceResultMessageChoice);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_messageChoiceMessageChoiceResult.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_messageChoiceMessageChoiceResult.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? messageChoiceMessageChoiceResultId, int messageChoiceResultResult, int messageChoiceResultMessageChoice)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyMessageChoiceResult = new Button() { Content = "Modify MessageChoiceResult" };
            button_modifyMessageChoiceResult.Click += Button_ModifyMessageChoiceResult_Click;
            this.SetGridRowColumn(button_modifyMessageChoiceResult, 0, 0);

            m_grid_messageChoiceMessageChoiceResult = new Grid_MessageChoiceResultData(messageChoiceMessageChoiceResultId, messageChoiceResultResult, messageChoiceResultMessageChoice, MessageId, false);
            this.SetGridRowColumn(m_grid_messageChoiceMessageChoiceResult, 1, 0);
            m_grid_messageChoiceMessageChoiceResult.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyMessageChoiceResult_Click(object sender, RoutedEventArgs e)
        {
            Window_MessageChoiceResultData window =
                new Window_MessageChoiceResultData
                (
                    m_grid_messageChoiceMessageChoiceResult.MessageChoiceResultId,
                    m_grid_messageChoiceMessageChoiceResult.MessageChoiceResultResult,
                    m_grid_messageChoiceMessageChoiceResult.MessageChoiceResultMessageChoice,
                    MessageId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyMessageChoiceResult
                (
                    window.MessageChoiceResultId.Value, 
                    window.MessageChoiceResultResult.Value, 
                    window.MessageChoiceResultMessageChoice.Value
                );
        }

        #endregion

        #endregion
    }
}
