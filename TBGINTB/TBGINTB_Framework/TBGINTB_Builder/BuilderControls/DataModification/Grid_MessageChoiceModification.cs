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
    public class Grid_MessageChoiceModification : Grid, IRegisterGinTubEventsOnlyWhenActive
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

        public Grid_MessageChoiceModification(int? messageChoiceId, string messageChoiceName, string messageChoiceText, int messageId)
        {
            CreateControls(messageChoiceId, messageChoiceName, messageChoiceText, messageId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_messageChoice.SetActiveAndRegisterForGinTubMessageChoices();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_messageChoice.SetInactiveAndUnregisterFromGinTubMessageChoices();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? messageChoiceId, string messageChoiceName, string messageChoiceText, int messageId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyMessageChoice = new Button() { Content = "Modify MessageChoice" };
            button_modifyMessageChoice.Click += Button_ModifyMessageChoice_Click;
            this.SetGridRowColumn(button_modifyMessageChoice, 0, 0);

            m_grid_messageChoice = new Grid_MessageChoiceData(messageChoiceId, messageChoiceName, messageChoiceText, messageId, false);
            this.SetGridRowColumn(m_grid_messageChoice, 1, 0);
            m_grid_messageChoice.SetActiveAndRegisterForGinTubMessageChoices();
        }

        private void Button_ModifyMessageChoice_Click(object sender, RoutedEventArgs e)
        {
            Window_MessageChoiceData window =
                new Window_MessageChoiceData
                (
                    m_grid_messageChoice.MessageChoiceId,
                    m_grid_messageChoice.MessageChoiceName, 
                    m_grid_messageChoice.MessageChoiceText,
                    m_grid_messageChoice.MessageId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyMessageChoice
                (
                    window.MessageChoiceId.Value, 
                    window.MessageChoiceName, 
                    window.MessageChoiceText,
                    window.MessageId
                );
        }

        #endregion

        #endregion
    }
}
