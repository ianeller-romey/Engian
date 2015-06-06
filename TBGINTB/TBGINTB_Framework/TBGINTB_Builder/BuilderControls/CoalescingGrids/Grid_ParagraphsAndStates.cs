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
    public class Grid_ParagraphsAndStates : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        StackPanel m_stackPanel_paragraphs;
        Button 
            m_button_modifyParagraph,
            m_button_addParagraphState;
        StackPanel m_stackPanel_paragraphStates;

        #endregion


        #region MEMBER PROPERTIES

        public int RoomId { get; private set; }
        public int RoomStateId { get; private set; }

        public int SelectedParagraphId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphsAndStates(int roomId, int roomStateId)
        {
            RoomId = roomId;
            RoomStateId = roomStateId;

            CreateControls();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphAdded += GinTubBuilderManager_ParagraphAdded;
            GinTubBuilderManager.ParagraphStateAdded += GinTubBuilderManager_ParagraphStateAdded;

            foreach (var block in m_stackPanel_paragraphs.Children.OfType<Grid_ParagraphData>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_paragraphStates.Children.OfType<Grid_ParagraphStateModification>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphAdded -= GinTubBuilderManager_ParagraphAdded;
            GinTubBuilderManager.ParagraphStateAdded -= GinTubBuilderManager_ParagraphStateAdded;

            foreach (var block in m_stackPanel_paragraphs.Children.OfType<Grid_ParagraphData>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_paragraphStates.Children.OfType<Grid_ParagraphStateModification>())
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
            // Add paragraph
            Button button_addParagraph = new Button() { Content = "Add Paragraph" };
            button_addParagraph.Click += Button_AddParagraph_Click;
            this.SetGridRowColumn(button_addParagraph, 0, 0);

            ////////
            // Paragraphs
            m_button_modifyParagraph = new Button() { Content = "Modify Paragraph", IsEnabled = false };
            m_button_modifyParagraph.Click += Button_ModifyParagraph_Click;
            this.SetGridRowColumn(m_button_modifyParagraph, 1, 0);

            m_stackPanel_paragraphs = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_paragraphs, 2, 0);

            ////////
            // Add ParagraphState
            m_button_addParagraphState = new Button() { Content = "Add Paragraph Text State", IsEnabled = false };
            m_button_addParagraphState.Click += Button_AddParagraphState_Click;
            this.SetGridRowColumn(m_button_addParagraphState, 3, 0);

            ////////
            // Paragraph States
            m_stackPanel_paragraphStates = new StackPanel() { Orientation = Orientation.Vertical };

            ScrollViewer scrollViewer_paragraphStates =
                new ScrollViewer()
                {
                    HorizontalScrollBarVisibility = ScrollBarVisibility.Hidden,
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            scrollViewer_paragraphStates.Content = m_stackPanel_paragraphStates;
            this.SetGridRowColumn(scrollViewer_paragraphStates, 4, 0);
        }

        private void GinTubBuilderManager_ParagraphAdded(object sender, GinTubBuilderManager.ParagraphAddedEventArgs args)
        {
            if (!m_stackPanel_paragraphs.Children.OfType<Grid_ParagraphData>().Any(t => t.ParagraphId == args.Id))
            {
                Grid_ParagraphData grid = new Grid_ParagraphData(args.Id, args.Order, args.Room, args.RoomState, false);
                grid.MouseLeftButtonDown += Grid_ParagraphData_MouseLeftButtonDown;
                grid.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_paragraphs.Children.Add(grid);
            }
        }

        void GinTubBuilderManager_ParagraphStateAdded(object sender, GinTubBuilderManager.ParagraphStateAddedEventArgs args)
        {
            if (!m_stackPanel_paragraphStates.Children.OfType<Grid_ParagraphStateModification>().Any(t => t.ParagraphStateId == args.Id))
            {
                Grid_ParagraphStateModification grid = new Grid_ParagraphStateModification(args.Id, args.Text, args.State, args.Paragraph);
                m_stackPanel_paragraphStates.Children.Add(grid);
            }
        }

        private void Button_AddParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_ParagraphData window = new Window_ParagraphData(null, null, RoomId, RoomStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddParagraph(window.ParagraphOrder.Value, window.RoomId, window.RoomStateId);
        }

        private void Button_ModifyParagraph_Click(object sender, RoutedEventArgs e)
        {
            Grid_ParagraphData grid = m_stackPanel_paragraphs.Children.OfType<Grid_ParagraphData>().Single(g => g.ParagraphId == SelectedParagraphId);
            Window_ParagraphData window = new Window_ParagraphData(grid.ParagraphId, grid.ParagraphOrder, grid.RoomId, grid.RoomStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyParagraph(window.ParagraphId.Value, window.ParagraphOrder.Value, window.RoomId, window.RoomStateId);
        }

        private void Button_AddParagraphState_Click(object sender, RoutedEventArgs e)
        {
            Window_ParagraphStateData window = new Window_ParagraphStateData(null, null, null, SelectedParagraphId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddParagraphState(window.ParagraphStateText, window.ParagraphId);
        }

        private void Grid_ParagraphData_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            Grid_ParagraphData grid = sender as Grid_ParagraphData;
            if (grid != null)
            {
                m_stackPanel_paragraphStates.Children.Clear();

                SelectedParagraphId = grid.ParagraphId.Value;
                GinTubBuilderManager.LoadAllParagraphStatesForParagraph(SelectedParagraphId);

                m_button_modifyParagraph.IsEnabled = true;
                m_button_addParagraphState.IsEnabled = true;
            }
        }

        #endregion

        #endregion

    }
}
