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
    public class Window_MessageData : Window_AcceptCancel
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

        public Window_MessageData(int? messageId, string messageName, string messageText)
        {
            Title = "Message Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(messageId, messageName, messageText);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? messageId, string messageName, string messageText)
        {
            m_grid_message = new Grid_MessageData(messageId, messageName, messageText, true);
            return m_grid_message;
        }

        #endregion

        #endregion
    }
}
