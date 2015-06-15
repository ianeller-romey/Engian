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
    public class Window_MessageChoiceData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_MessageChoiceData m_grid_messageChoice;

        #endregion


        #region MEMBER PROPERTIES

        public int? MessageChoiceId { get { return m_grid_messageChoice.MessageChoiceId; } }
        public string MessageChoiceName { get { return m_grid_messageChoice.MessageChoiceName; } }
        public string MessageChoiceText { get { return m_grid_messageChoice.MessageChoiceText; } }
        public int MessageId { get { return m_grid_messageChoice.MessageId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_MessageChoiceData(int? messageChoiceId, string messageChoiceName, string messageChoiceText, int messageId)
        {
            Title = "MessageChoice Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(messageChoiceId, messageChoiceName, messageChoiceText, messageId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? messageChoiceId, string messageChoiceName, string messageChoiceText, int messageId)
        {
            m_grid_messageChoice = new Grid_MessageChoiceData(messageChoiceId, messageChoiceName, messageChoiceText, messageId, true);
            return m_grid_messageChoice;
        }

        #endregion

        #endregion
    }
}
