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
    public class Grid_NounsAndActions : Grid, IRegisterGinTubEventsOnlyWhenActive
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

        public Grid_NounsAndActions(int paragraphStateId)
        {
            ParagraphStateId = paragraphStateId;

            CreateControls();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.NounAdded += GinTubBuilderManager_NounAdded;
            GinTubBuilderManager.ActionAdded += GinTubBuilderManager_ActionAdded;

            foreach (var block in m_stackPanel_nouns.Children.OfType<Grid_NounData>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_actions.Children.OfType<Grid_ActionUnderNoun>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.NounAdded -= GinTubBuilderManager_NounAdded;
            GinTubBuilderManager.ActionAdded -= GinTubBuilderManager_ActionAdded;

            foreach (var block in m_stackPanel_nouns.Children.OfType<Grid_NounData>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_actions.Children.OfType<Grid_ActionUnderNoun>())
                grid.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            ////////
            // Add Noun
            Button button_addNoun = new Button() { Content = "Add Noun" };
            button_addNoun.Click += Button_AddNoun_Click;
            this.SetGridRowColumn(button_addNoun, 0, 0);

            ////////
            // Nouns
            m_button_modifyNoun = new Button() { Content = "Modify Noun", IsEnabled = false };
            m_button_modifyNoun.Click += Button_ModifyNoun_Click;
            this.SetGridRowColumn(m_button_modifyNoun, 1, 0);

            m_stackPanel_nouns = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_nouns, 2, 0);

            ////////
            // Add Action
            m_button_addAction = new Button() { Content = "Add Action", IsEnabled = false };
            m_button_addAction.Click += Button_AddAction_Click;
            this.SetGridRowColumn(m_button_addAction, 3, 0);

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
            this.SetGridRowColumn(scrollViewer_actions, 4, 0);
        }

        private void GinTubBuilderManager_NounAdded(object sender, GinTubBuilderManager.NounAddedEventArgs args)
        {
            if (!m_stackPanel_nouns.Children.OfType<Grid_NounData>().Any(t => t.NounId == args.Id))
            {
                Grid_NounData grid = new Grid_NounData(args.Id, args.Text, args.ParagraphState, false);
                grid.MouseLeftButtonDown += Grid_NounData_MouseLeftButtonDown;
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_nouns.Children.Add(grid);
                GinTubBuilderManager.LoadParagraphStateNounPossibilities(args.ParagraphState);
            }
        }

        void GinTubBuilderManager_ActionAdded(object sender, GinTubBuilderManager.ActionAddedEventArgs args)
        {
            if (!m_stackPanel_actions.Children.OfType<Grid_ActionData>().Any(a => a.ActionId == args.Id))
            {
                Grid_ActionUnderNoun grid = new Grid_ActionUnderNoun(args.Id, args.VerbType, args.Noun, ParagraphStateId);
                m_stackPanel_actions.Children.Add(grid);
                GinTubBuilderManager.LoadAllVerbTypes();
                GinTubBuilderManager.LoadAllNounsForParagraphState(ParagraphStateId);
            }
        }

        private void Button_AddNoun_Click(object sender, RoutedEventArgs e)
        {
            Window_NounData window = new Window_NounData(null, null, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddNoun(window.NounText, window.ParagraphStateId);
        }

        private void Button_ModifyNoun_Click(object sender, RoutedEventArgs e)
        {
            Grid_NounData grid = m_stackPanel_nouns.Children.OfType<Grid_NounData>().Single(g => g.NounId.Value == SelectedNounId);
            Window_NounData window = new Window_NounData(grid.NounId, grid.NounText, grid.ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyNoun(window.NounId.Value, window.NounText, window.ParagraphStateId);
        }

        private void Button_AddAction_Click(object sender, RoutedEventArgs e)
        {
            Window_ActionData window = new Window_ActionData(null, null, SelectedNounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddAction(window.ActionVerbType.Value, window.ActionNoun.Value);
        }

        private void Grid_NounData_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            Grid_NounData grid = sender as Grid_NounData;
            if (grid != null)
            {
                m_stackPanel_actions.Children.Clear();

                SelectedNounId = grid.NounId.Value;
                GinTubBuilderManager.LoadAllActionsForNoun(SelectedNounId);

                m_button_modifyNoun.IsEnabled = true;
                m_button_addAction.IsEnabled = true;
            }
        }

        #endregion

        #endregion

    }
}
