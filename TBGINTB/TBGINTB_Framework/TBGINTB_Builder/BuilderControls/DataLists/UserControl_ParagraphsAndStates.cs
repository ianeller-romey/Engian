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
    public class UserControl_ParagraphsAndStates : UserControl, IRegisterGinTubEventsOnlyWhenActive
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

        public UserControl_ParagraphsAndStates(int roomId, int roomStateId)
        {
            RoomId = roomId;
            RoomStateId = roomStateId;

            CreateControls();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphAdded += GinTubBuilderManager_ParagraphAdded;
            GinTubBuilderManager.ParagraphStateAdded += GinTubBuilderManager_ParagraphStateAdded;

            GinTubBuilderManager.ParagraphStateModified += GinTubBuilderManager_ParagraphStateModified;

            foreach (var block in m_stackPanel_paragraphs.Children.OfType<UserControl_Paragraph>())
                block.SetActiveAndRegisterForGinTubEvents();
            foreach (var grid in m_stackPanel_paragraphStates.Children.OfType<UserControl_ParagraphStateModification>())
                grid.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphAdded -= GinTubBuilderManager_ParagraphAdded;
            GinTubBuilderManager.ParagraphStateAdded -= GinTubBuilderManager_ParagraphStateAdded;

            GinTubBuilderManager.ParagraphStateModified -= GinTubBuilderManager_ParagraphStateModified;

            foreach (var block in m_stackPanel_paragraphs.Children.OfType<UserControl_Paragraph>())
                block.SetInactiveAndUnregisterFromGinTubEvents();
            foreach (var grid in m_stackPanel_paragraphStates.Children.OfType<UserControl_ParagraphStateModification>())
                grid.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(50.0, GridUnitType.Star) });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(50.0, GridUnitType.Star) });

            ////////
            // Add paragraph
            Button button_addParagraph = new Button() { Content = "New Paragraph ..." };
            button_addParagraph.Click += Button_AddParagraph_Click;
            grid_main.SetGridRowColumn(button_addParagraph, 0, 0);

            ////////
            // Paragraphs
            m_button_modifyParagraph = new Button() { Content = "Modify Paragraph", IsEnabled = false };
            m_button_modifyParagraph.Click += Button_ModifyParagraph_Click;
            grid_main.SetGridRowColumn(m_button_modifyParagraph, 1, 0);

            m_stackPanel_paragraphs = new StackPanel() { Orientation = Orientation.Vertical };
            ScrollViewer scrollViewer_paragraphs =
                new ScrollViewer()
                {
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            scrollViewer_paragraphs.Content = m_stackPanel_paragraphs;
            grid_main.SetGridRowColumn(scrollViewer_paragraphs, 2, 0);

            ////////
            // Add ParagraphState
            m_button_addParagraphState = new Button() { Content = "New Paragraph Text State ...", IsEnabled = false };
            m_button_addParagraphState.Click += Button_AddParagraphState_Click;
            grid_main.SetGridRowColumn(m_button_addParagraphState, 3, 0);

            ////////
            // Paragraph States
            m_stackPanel_paragraphStates = new StackPanel() { Orientation = Orientation.Vertical };
            ScrollViewer scrollViewer_paragraphStates =
                new ScrollViewer()
                {
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            scrollViewer_paragraphStates.Content = m_stackPanel_paragraphStates;
            grid_main.SetGridRowColumn(scrollViewer_paragraphStates, 4, 0);

            ////////
            // Fin
            Content = grid_main;
        }

        private void GinTubBuilderManager_ParagraphAdded(object sender, GinTubBuilderManager.ParagraphAddedEventArgs args)
        {
            if (!m_stackPanel_paragraphs.Children.OfType<UserControl_Bordered_Paragraph>().Any(t => t.ParagraphId == args.Id))
            {
                UserControl_Bordered_Paragraph border = new UserControl_Bordered_Paragraph(args.Id, args.Order, args.Room, args.RoomState, false);
                border.MouseLeftButtonDown += UserControl_Paragraph_MouseLeftButtonDown;
                border.SetActiveAndRegisterForGinTubEvents();
                m_stackPanel_paragraphs.Children.Add(border);

                GinTubBuilderManager.LoadParagraphStateForParagraphPreview(0, args.Id);
            }
        }

        private void GinTubBuilderManager_ParagraphStateAdded(object sender, GinTubBuilderManager.ParagraphStateAddedEventArgs args)
        {
            if (SelectedParagraphId == args.Paragraph && !m_stackPanel_paragraphStates.Children.OfType<UserControl_ParagraphStateModification>().Any(t => t.ParagraphStateId == args.Id))
            {
                UserControl_ParagraphStateModification grid = new UserControl_ParagraphStateModification(args.Id, args.Text, args.State, args.Paragraph);
                m_stackPanel_paragraphStates.Children.Add(grid);
            }

            if (args.State == 0)
                SetParagraphPreview(args.Text, args.Paragraph);
        }

        private void GinTubBuilderManager_ParagraphStateModified(object sender, GinTubBuilderManager.ParagraphStateModifiedEventArgs args)
        {
            if (args.State == 0)
                SetParagraphPreview(args.Text, args.Paragraph);
        }

        private void SetParagraphPreview(string paragraphStateText, int paragraphId)
        {
            UserControl_Bordered_Paragraph border = m_stackPanel_paragraphs.Children.OfType<UserControl_Bordered_Paragraph>().SingleOrDefault(gp => gp.ParagraphId == paragraphId);
            if (border != null)
                border.ToolTip = string.Format("{0} ...", paragraphStateText.Substring(0, Math.Max(Math.Min(75, paragraphStateText.Length - 5), 0)));
        }

        private void Button_AddParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_Paragraph window = new Window_Paragraph(null, null, RoomId, RoomStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddParagraph(window.ParagraphOrder.Value, window.RoomId, window.RoomStateId);
        }

        private void Button_ModifyParagraph_Click(object sender, RoutedEventArgs e)
        {
            UserControl_Paragraph grid = m_stackPanel_paragraphs.Children.OfType<UserControl_Paragraph>().Single(g => g.ParagraphId == SelectedParagraphId);
            Window_Paragraph window = new Window_Paragraph(grid.ParagraphId, grid.ParagraphOrder, grid.RoomId, grid.RoomStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyParagraph(window.ParagraphId.Value, window.ParagraphOrder.Value, window.RoomId, window.RoomStateId);
        }

        private void Button_AddParagraphState_Click(object sender, RoutedEventArgs e)
        {
            Window_ParagraphState window = new Window_ParagraphState(null, null, null, SelectedParagraphId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddParagraphState(window.ParagraphStateText, window.ParagraphId);
        }

        private void UserControl_Paragraph_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            UserControl_Bordered_Paragraph border = sender as UserControl_Bordered_Paragraph;
            if (border != null)
            {
                m_stackPanel_paragraphStates.Children.Clear();

                SelectedParagraphId = border.ParagraphId.Value;
                GinTubBuilderManager.GetParagraph(SelectedParagraphId);

                m_button_modifyParagraph.IsEnabled = true;
                m_button_addParagraphState.IsEnabled = true;
            }
        }

        #endregion

        #endregion

    }
}
