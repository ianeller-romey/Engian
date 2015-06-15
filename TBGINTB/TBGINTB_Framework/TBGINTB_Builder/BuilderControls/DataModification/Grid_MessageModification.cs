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
    public class Grid_MessageModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_MessageData m_grid_message;

        #endregion


        #region MEMBER PROPERTIES

        public int? MessageId { get { return m_grid_message.MessageId; } }
        public string MessageName { get { return m_grid_message.MessageName; } }
        public string MessageText { get { return m_grid_message.MessageText; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_MessageModification(int? messageId, string messageName, string messageText)
        {
            CreateControls(messageId, messageName, messageText);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_message.SetActiveAndRegisterForGinTubMessages();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_message.SetInactiveAndUnregisterFromGinTubMessages();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? messageId, string messageName, string messageText)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyMessage = new Button() { Content = "Modify Message" };
            button_modifyMessage.Click += Button_ModifyMessage_Click;
            this.SetGridRowColumn(button_modifyMessage, 0, 0);

            m_grid_message = new Grid_MessageData(messageId, messageName, messageText, false);
            this.SetGridRowColumn(m_grid_message, 1, 0);
            m_grid_message.SetActiveAndRegisterForGinTubMessages();
        }

        private void Button_ModifyMessage_Click(object sender, RoutedEventArgs e)
        {
            Window_MessageData window =
                new Window_MessageData(m_grid_message.MessageId, m_grid_message.MessageName, m_grid_message.MessageText);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyMessage(window.MessageId.Value, window.MessageName, window.MessageText);
        }

        #endregion

        #endregion
    }
}
