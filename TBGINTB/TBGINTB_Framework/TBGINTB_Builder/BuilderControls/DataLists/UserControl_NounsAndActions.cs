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
    public class UserControl_NounsAndActions : UserControl, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        StackPanel m_stackPanel_nouns;
        Button 
            m_button_modifyNoun,
            m_button_addAction;
        StackPanel m_stackPanel_actions;

        #endregion


        #region MEMBER PROPERTIES

        public int ParagraphStateId { get; private set; }

        public int SelectedNounId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public UserControl_NounsAndActions(int paragraphStateId)
        {
            ParagraphStateId = paragraphStateId;

            CreateControls();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.NounAdded += GinTubBuilderManager_NounAdded;
            GinTubBuilderManager.ActionAdded += GinTubBuilderManager_ActionAdded;

            foreach (var block in m_stackPanel_nouns.Children.OfType<UserControl_Noun>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_actions.Children.OfType<UserControl_ActionModification>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.NounAdded -= GinTubBuilderManager_NounAdded;
            GinTubBuilderManager.ActionAdded -= GinTubBuilderManager_ActionAdded;

            foreach (var block in m_stackPanel_nouns.Children.OfType<UserControl_Noun>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_actions.Children.OfType<UserControl_ActionModification>())
                grid.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            ////////
            // Add Noun
            Button button_addNoun = new Button() { Content = "New Noun ..." };
            button_addNoun.Click += Button_AddNoun_Click;
            grid_main.SetGridRowColumn(button_addNoun, 0, 0);

            ////////
            // Nouns
            m_button_modifyNoun = new Button() { Content = "Modify Noun", IsEnabled = false };
            m_button_modifyNoun.Click += Button_ModifyNoun_Click;
            grid_main.SetGridRowColumn(m_button_modifyNoun, 1, 0);

            m_stackPanel_nouns = new StackPanel() { Orientation = Orientation.Vertical };
            grid_main.SetGridRowColumn(m_stackPanel_nouns, 2, 0);

            ////////
            // Add Action
            m_button_addAction = new Button() { Content = "New Action ...", IsEnabled = false };
            m_button_addAction.Click += Button_AddAction_Click;
            grid_main.SetGridRowColumn(m_button_addAction, 3, 0);

            ////////
            // Paragraph States
            m_stackPanel_actions = new StackPanel() { Orientation = Orientation.Vertical };

            ScrollViewer scrollViewer_actions =
                new ScrollViewer()
                {
                    HorizontalScrollBarVisibility = ScrollBarVisibility.Hidden,
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            scrollViewer_actions.Content = m_stackPanel_actions;
            grid_main.SetGridRowColumn(scrollViewer_actions, 4, 0);

            ////////
            // Fin
            Content = grid_main;
        }

        private void GinTubBuilderManager_NounAdded(object sender, GinTubBuilderManager.NounAddedEventArgs args)
        {
            if (ParagraphStateId == args.ParagraphState && !m_stackPanel_nouns.Children.OfType<UserControl_Bordered_Noun>().Any(t => t.NounId == args.Id))
            {
                UserControl_Bordered_Noun border = new UserControl_Bordered_Noun(args.Id, args.Text, args.ParagraphState, false);
                border.MouseLeftButtonDown += UserControl_NounData_MouseLeftButtonDown;
                border.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_nouns.Children.Add(border);
                GinTubBuilderManager.LoadParagraphStateNounPossibilities(args.ParagraphState);
            }
        }

        private void GinTubBuilderManager_ActionAdded(object sender, GinTubBuilderManager.ActionAddedEventArgs args)
        {
            if (!m_stackPanel_actions.Children.OfType<UserControl_ActionModification>().Any(a => a.ActionId == args.Id))
            {
                UserControl_ActionModification grid = new UserControl_ActionModification(args.Id, args.VerbType, args.Noun, ParagraphStateId);
                m_stackPanel_actions.Children.Add(grid);
                GinTubBuilderManager.LoadAllVerbTypes();
                GinTubBuilderManager.LoadAllNounsForParagraphState(ParagraphStateId);
            }
        }

        private void Button_AddNoun_Click(object sender, RoutedEventArgs e)
        {
            Window_Noun window = new Window_Noun(null, null, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddNoun(window.NounText, window.ParagraphStateId);
        }

        private void Button_ModifyNoun_Click(object sender, RoutedEventArgs e)
        {
            UserControl_Noun grid = m_stackPanel_nouns.Children.OfType<UserControl_Noun>().Single(g => g.NounId.Value == SelectedNounId);
            Window_Noun window = new Window_Noun(grid.NounId, grid.NounText, grid.ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyNoun(window.NounId.Value, window.NounText, window.ParagraphStateId);
        }

        private void Button_AddAction_Click(object sender, RoutedEventArgs e)
        {
            Window_Action window = new Window_Action(null, null, SelectedNounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddAction(window.ActionVerbType.Value, window.ActionNoun.Value);
        }

        private void UserControl_NounData_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            UserControl_Bordered_Noun border = sender as UserControl_Bordered_Noun;
            if (border != null)
            {
                m_stackPanel_actions.Children.Clear();

                SelectedNounId = border.NounId.Value;
                GinTubBuilderManager.GetNoun(SelectedNounId);

                m_button_modifyNoun.IsEnabled = true;
                m_button_addAction.IsEnabled = true;
            }
        }

        #endregion

        #endregion

    }
}
