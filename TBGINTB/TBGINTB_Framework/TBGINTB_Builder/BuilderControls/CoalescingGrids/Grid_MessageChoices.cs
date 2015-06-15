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
    public class Grid_MessageChoices : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newMessageChoice = new Button() { Content = "Add Message Choice" };

        private StackPanel m_stackPanel_messageChoices;

        #endregion


        #region MEMBER PROPERTIES

        public int MessageId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_MessageChoices(int messageId)
        {
            MessageId = messageId;

            CreateControls();

            c_button_newMessageChoice.Click += Button_NewMessageChoice_Click;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.MessageChoiceAdded += GinTubBuilderManager_MessageChoiceAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.MessageChoiceAdded -= GinTubBuilderManager_MessageChoiceAdded;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            this.SetGridRowColumn(c_button_newMessageChoice, 0, 0);

            m_stackPanel_messageChoices = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_messageChoices, 1, 0);
        }

        private void GinTubBuilderManager_MessageChoiceAdded(object sender, GinTubBuilderManager.MessageChoiceAddedEventArgs args)
        {
            if (MessageId == args.Message && !m_stackPanel_messageChoices.Children.OfType<Grid_MessageChoiceModification>().Any(i => i.MessageChoiceId == args.Id))
            {
                Grid_MessageChoiceModification grid = new Grid_MessageChoiceModification(args.Id, args.Name, args.Text, args.Message);
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_messageChoices.Children.Add(grid);
                GinTubBuilderManager.LoadAllMessages();
            }
        }

        private void NewMessageChoiceDialog()
        {
            Window_MessageChoiceData window = new Window_MessageChoiceData(null, null, null, MessageId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddMessageChoice
                (
                    window.MessageChoiceName,
                    window.MessageChoiceText,
                    window.MessageId
                );
        }
        
        private void Button_NewMessageChoice_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newMessageChoice)
                NewMessageChoiceDialog();
        }

        #endregion

        #endregion
    }
}
