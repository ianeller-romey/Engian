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
    public class Grid_ActionRequirements : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button
            c_button_newItemActionRequirement = new Button() { Content = "Add Item Req." },
            c_button_newEventActionRequirement = new Button() { Content = "Add Event Req." },
            c_button_newCharacterActionRequirement = new Button() { Content = "Add Character Req." };

        private StackPanel
            m_stackPanel_itemActionRequirements,
            m_stackPanel_evntActionRequirements,
            m_stackPanel_characterActionRequirements;

        #endregion


        #region MEMBER PROPERTIES

        public int ActionId { get; set; }
        public int NounId { get; set; }
        public int ParagraphStateId { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ActionRequirements(int actionId, int nounId, int paragraphStateId)
        {
            ActionId = actionId;
            NounId = nounId;
            ParagraphStateId = paragraphStateId;

            CreateControls();

            c_button_newItemActionRequirement.Click += Button_NewItemActionRequirement_Click;
            c_button_newEventActionRequirement.Click += Button_NewEventActionRequirement_Click;
            c_button_newCharacterActionRequirement.Click += Button_NewCharacterActionRequirement_Click;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ItemActionRequirementAdded += GinTubBuilderManager_ItemActionRequirementAdded;
            GinTubBuilderManager.EventActionRequirementAdded += GinTubBuilderManager_EventActionRequirementAdded;
            GinTubBuilderManager.CharacterActionRequirementAdded += GinTubBuilderManager_CharacterActionRequirementAdded;

            foreach (var block in m_stackPanel_itemActionRequirements.Children.OfType<Grid_ItemActionRequirementModification>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var block in m_stackPanel_evntActionRequirements.Children.OfType<Grid_EventActionRequirementModification>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var block in m_stackPanel_characterActionRequirements.Children.OfType<Grid_CharacterActionRequirementModification>())
                block.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ItemActionRequirementAdded -= GinTubBuilderManager_ItemActionRequirementAdded;
            GinTubBuilderManager.EventActionRequirementAdded -= GinTubBuilderManager_EventActionRequirementAdded;
            GinTubBuilderManager.CharacterActionRequirementAdded -= GinTubBuilderManager_CharacterActionRequirementAdded;

            foreach (var block in m_stackPanel_itemActionRequirements.Children.OfType<Grid_ItemActionRequirementModification>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var block in m_stackPanel_evntActionRequirements.Children.OfType<Grid_EventActionRequirementModification>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var block in m_stackPanel_characterActionRequirements.Children.OfType<Grid_CharacterActionRequirementModification>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            ////////
            // Item Action Requirements
            Grid grid_itemActionRequirements = new Grid();
            grid_itemActionRequirements.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_itemActionRequirements.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            grid_itemActionRequirements.SetGridRowColumn(c_button_newItemActionRequirement, 0, 0);

            m_stackPanel_itemActionRequirements = new StackPanel() { Orientation = Orientation.Vertical };
            grid_itemActionRequirements.SetGridRowColumn(m_stackPanel_itemActionRequirements, 1, 0);

            TabItem tabItem_itemActionRequirements = new TabItem() { Header = "Item Reqs" };
            tabItem_itemActionRequirements.Content = grid_itemActionRequirements;

            ////////
            // Event Action Requirements
            Grid grid_evntActionRequirements = new Grid();
            grid_evntActionRequirements.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_evntActionRequirements.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            grid_evntActionRequirements.SetGridRowColumn(c_button_newEventActionRequirement, 0, 0);

            m_stackPanel_evntActionRequirements = new StackPanel() { Orientation = Orientation.Vertical };
            grid_evntActionRequirements.SetGridRowColumn(m_stackPanel_evntActionRequirements, 1, 0);

            TabItem tabItem_evntActionRequirements = new TabItem() { Header = "Event Reqs" };
            tabItem_evntActionRequirements.Content = grid_evntActionRequirements;

            ////////
            // Character Action Requirements
            Grid grid_characterActionRequirements = new Grid();
            grid_characterActionRequirements.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_characterActionRequirements.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            grid_characterActionRequirements.SetGridRowColumn(c_button_newCharacterActionRequirement, 0, 0);

            m_stackPanel_characterActionRequirements = new StackPanel() { Orientation = Orientation.Vertical };
            grid_characterActionRequirements.SetGridRowColumn(m_stackPanel_characterActionRequirements, 1, 0);

            TabItem tabItem_characterActionRequirements = new TabItem() { Header = "Character Reqs" };
            tabItem_characterActionRequirements.Content = grid_characterActionRequirements;

            ////////
            // Fin
            TabControl tabControl_main = new TabControl();
            tabControl_main.Items.Add(tabItem_itemActionRequirements);
            tabControl_main.Items.Add(tabItem_evntActionRequirements);
            tabControl_main.Items.Add(tabItem_characterActionRequirements);

            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            this.SetGridRowColumn(tabControl_main, 0, 0);
        }

        private void GinTubBuilderManager_ItemActionRequirementAdded(object sender, GinTubBuilderManager.ItemActionRequirementAddedEventArgs args)
        {
            if (ActionId == args.Action && !m_stackPanel_itemActionRequirements.Children.OfType<Grid_ItemActionRequirementModification>().Any(i => i.ItemActionRequirementId == args.Id))
            {
                Grid_ItemActionRequirementModification grid = new Grid_ItemActionRequirementModification(args.Id, args.Item, args.Action, NounId, ParagraphStateId);
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_itemActionRequirements.Children.Add(grid);
                GinTubBuilderManager.LoadAllItems();
                GinTubBuilderManager.LoadAllActionsForNoun(NounId);
            }
        }

        private void GinTubBuilderManager_EventActionRequirementAdded(object sender, GinTubBuilderManager.EventActionRequirementAddedEventArgs args)
        {
            if (ActionId == args.Action && !m_stackPanel_evntActionRequirements.Children.OfType<Grid_EventActionRequirementModification>().Any(i => i.EventActionRequirementId == args.Id))
            {
                Grid_EventActionRequirementModification grid = new Grid_EventActionRequirementModification(args.Id, args.Event, args.Action, NounId, ParagraphStateId);
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_evntActionRequirements.Children.Add(grid);
                GinTubBuilderManager.LoadAllEvents();
                GinTubBuilderManager.LoadAllActionsForNoun(NounId);
            }
        }

        private void GinTubBuilderManager_CharacterActionRequirementAdded(object sender, GinTubBuilderManager.CharacterActionRequirementAddedEventArgs args)
        {
            if (ActionId == args.Action && !m_stackPanel_characterActionRequirements.Children.OfType<Grid_CharacterActionRequirementModification>().Any(i => i.CharacterActionRequirementId == args.Id))
            {
                Grid_CharacterActionRequirementModification grid = new Grid_CharacterActionRequirementModification(args.Id, args.Character, args.Action, NounId, ParagraphStateId);
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_characterActionRequirements.Children.Add(grid);
                GinTubBuilderManager.LoadAllCharacters();
                GinTubBuilderManager.LoadAllActionsForNoun(NounId);
            }
        }

        private void NewItemActionRequirementDialog()
        {
            Window_ItemActionRequirementData window = new Window_ItemActionRequirementData(null, null, null, NounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddItemActionRequirement
                (
                    window.ItemActionRequirementItem.Value,
                    window.ItemActionRequirementAction.Value
                );
        }

        private void NewEventActionRequirementDialog()
        {
            Window_EventActionRequirementData window = new Window_EventActionRequirementData(null, null, null, NounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddEventActionRequirement
                (
                    window.EventActionRequirementEvent.Value,
                    window.EventActionRequirementAction.Value
                );
        }

        private void NewCharacterActionRequirementDialog()
        {
            Window_CharacterActionRequirementData window = new Window_CharacterActionRequirementData(null, null, null, NounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddCharacterActionRequirement
                (
                    window.CharacterActionRequirementCharacter.Value,
                    window.CharacterActionRequirementAction.Value
                );
        }

        private void Button_NewItemActionRequirement_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newItemActionRequirement)
                NewItemActionRequirementDialog();
        }

        private void Button_NewEventActionRequirement_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newEventActionRequirement)
                NewEventActionRequirementDialog();
        }

        private void Button_NewCharacterActionRequirement_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newCharacterActionRequirement)
                NewCharacterActionRequirementDialog();
        }

        #endregion

        #endregion
    }
}
