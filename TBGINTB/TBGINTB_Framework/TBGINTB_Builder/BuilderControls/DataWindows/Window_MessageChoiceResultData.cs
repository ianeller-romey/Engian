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
    public class Window_MessageChoiceResultData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_MessageChoiceResultData m_grid_messageChoiceResult;

        #endregion


        #region MEMBER PROPERTIES

        public int? MessageChoiceResultId { get { return m_grid_messageChoiceResult.MessageChoiceResultId; } }
        public int? MessageChoiceResultResult { get { return m_grid_messageChoiceResult.MessageChoiceResultResult; } }
        public int? MessageChoiceResultMessageChoice { get { return m_grid_messageChoiceResult.MessageChoiceResultMessageChoice; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_MessageChoiceResultData(int? messageChoiceResultId, int? messageChoiceResultResult, int? messageChoiceResultMessageChoice, int messageId, int resultTypeId)
        {
            Title = "MessageChoiceResult Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(messageChoiceResultId, messageChoiceResultResult, messageChoiceResultMessageChoice, messageId);
            m_grid_messageChoiceResult.SetActiveAndRegisterForGinTubEvents(); // needed for possible results, messageChoices
            GinTubBuilderManager.LoadAllResultsForResultType(resultTypeId);
            GinTubBuilderManager.LoadAllMessageChoicesForMessage(messageId);
        }

        public Window_MessageChoiceResultData(int? messageChoiceResultId, int? messageChoiceResultResult, int? messageChoiceResultMessageChoice, int messageId)
        {
            Title = "MessageChoiceResult Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(messageChoiceResultId, messageChoiceResultResult, messageChoiceResultMessageChoice, messageId);
            m_grid_messageChoiceResult.SetActiveAndRegisterForGinTubEvents(); // needed for possible results, messageChoices
            if (messageChoiceResultMessageChoice.HasValue)
                GinTubBuilderManager.LoadAllResultsForMessageChoiceResultType(messageChoiceResultMessageChoice.Value);
            GinTubBuilderManager.LoadAllMessageChoicesForMessage(messageId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? messageChoiceResultId, int? messageChoiceResultResult, int? messageChoiceResultMessageChoice, int messageId)
        {
            m_grid_messageChoiceResult = new Grid_MessageChoiceResultData(messageChoiceResultId, messageChoiceResultResult, messageChoiceResultMessageChoice, messageId, true);
            return m_grid_messageChoiceResult;
        }

        #endregion

        #endregion
    }
}
