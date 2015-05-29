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
        Button m_button_addParagraphState;
        StackPanel m_stackPanel_paragraphStates;

        #endregion


        #region MEMBER PROPERTIES

        public int RoomId { get; private set; }
        public int RoomStateId { get; private set; }
        private int SelectedParagraphId { get; set; }

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

            foreach (var block in m_stackPanel_paragraphs.Children.OfType<TextBlock_ParagraphText>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_paragraphStates.Children.OfType<Grid_ParagraphStateUnderParagraph>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphAdded -= GinTubBuilderManager_ParagraphAdded;
            GinTubBuilderManager.ParagraphStateAdded -= GinTubBuilderManager_ParagraphStateAdded;

            foreach (var block in m_stackPanel_paragraphs.Children.OfType<TextBlock_ParagraphText>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_paragraphStates.Children.OfType<Grid_ParagraphStateUnderParagraph>())
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

            ////////
            // Paragraphs
            m_stackPanel_paragraphs = new StackPanel() { Orientation = Orientation.Vertical };
            this.SetGridRowColumn(m_stackPanel_paragraphs, 0, 0);

            ////////
            // Add Paragraphs
            Button button_addParagraph = new Button() { Content = "Add Paragraph" };
            button_addParagraph.Click += Button_AddParagraph_Click;
            this.SetGridRowColumn(button_addParagraph, 1, 0);

            ////////
            // Add ParagraphState
            m_button_addParagraphState = new Button() { Content = "Add Paragraph State", IsEnabled = false };
            m_button_addParagraphState.Click += Button_AddParagraphState_Click;
            this.SetGridRowColumn(m_button_addParagraphState, 2, 0);

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
            this.SetGridRowColumn(scrollViewer_paragraphStates, 3, 0);
        }

        private void GinTubBuilderManager_ParagraphAdded(object sender, GinTubBuilderManager.ParagraphAddedEventArgs args)
        {
            if (!m_stackPanel_paragraphs.Children.OfType<TextBlock_ParagraphText>().Any(t => t.ParagraphId == args.Id))
            {
                TextBlock_ParagraphText textBlock = new TextBlock_ParagraphText(args.Id, args.Text);
                textBlock.MouseLeftButtonDown += TextBlock_MouseLeftButtonDown;
                textBlock.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_paragraphs.Children.Add(textBlock);
            }
            if(args.Id == SelectedParagraphId)
                AddParagraphState(args.Id, args.State, args.Text, args.RoomState.Value, args.Room);
        }

        private void GinTubBuilderManager_ParagraphStateAdded(object sender, GinTubBuilderManager.ParagraphStateAddedEventArgs args)
        {
            m_stackPanel_paragraphStates.Children.Add(new Grid_ParagraphStateUnderParagraph(args.Id, args.State, args.Text, args.RoomState.Value, args.Room));
        }

        private void AddParagraphState(int paragraphId, int paragraphState, string paragraphText, int roomStateId, int roomId)
        {
            Grid_ParagraphStateUnderParagraph grid_paragraphState = new Grid_ParagraphStateUnderParagraph(paragraphId, paragraphState, paragraphText, roomStateId, roomId);
            grid_paragraphState.SetActiveAndRegisterForGinTubEvents();
            m_stackPanel_paragraphStates.Children.Add(grid_paragraphState);
        }

        private void TextBlock_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            TextBlock_ParagraphText textBlock = sender as TextBlock_ParagraphText;
            if (textBlock != null)
            {
                m_stackPanel_paragraphStates.Children.Clear();

                SelectedParagraphId = textBlock.ParagraphId;
                GinTubBuilderManager.LoadAllParagraphStates(SelectedParagraphId);
            }
        }

        private void Button_AddParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_ParagraphData window = new Window_ParagraphData(null, null, string.Empty, RoomStateId, RoomId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddParagraph(null, window.ParagraphText, window.RoomId, window.RoomStateId);
        }

        private void Button_AddParagraphState_Click(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        #endregion

        #endregion

    }
}
