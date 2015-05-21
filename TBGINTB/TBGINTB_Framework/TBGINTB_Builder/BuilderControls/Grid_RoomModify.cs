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
    public class Grid_RoomModify : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        TextBlock
            m_textBlock_roomId,
            m_textBlock_roomX,
            m_textBlock_roomY,
            m_textBlock_roomZ;
        TextBox m_textBox_roomName;
        Button m_button_saveChanges;
        StackPanel m_stackPanel_roomStates;

        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public int RoomId { get; private set; }
        public string RoomName { get; private set; }
        public int RoomX { get; private set; }
        public int RoomY { get; private set; }
        public int RoomZ { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomModify()
        {
            CreateControls();
        }

        public void ResetValues()
        {
            AreaId = int.MinValue;

            RoomId = int.MinValue;
            m_textBlock_roomId.Text = string.Empty;

            RoomName = string.Empty;
            m_textBox_roomName.Text = string.Empty;

            RoomX = int.MinValue;
            m_textBlock_roomX.Text = string.Empty;

            RoomY = int.MinValue;
            m_textBlock_roomY.Text = string.Empty;

            RoomZ = int.MinValue;
            m_textBlock_roomZ.Text = string.Empty;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomGet += GinTubBuilderManager_RoomGet;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomGet -= GinTubBuilderManager_RoomGet;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(100.0, GridUnitType.Star) });

            ////////
            // Id Grid
            Grid grid_id = new Grid();
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            Grid.SetColumnSpan(grid_id, 2);
            this.SetGridRowColumn(grid_id, 0, 0);

            ////////
            // Id
            m_textBlock_roomId = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(m_textBlock_roomId, 0, 1);
            grid_id.SetGridRowColumn(label_roomId, 0, 0);

            ////////
            // XYZ Grid
            Grid grid_XYZ = new Grid();
            grid_XYZ.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_XYZ.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_XYZ.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_XYZ.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_XYZ.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_XYZ.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            Grid.SetColumnSpan(grid_XYZ, 2);
            this.SetGridRowColumn(grid_XYZ, 1, 0);

            ////////
            // X
            m_textBlock_roomX = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomX = new Label() { Content = "X:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(m_textBlock_roomX, 0, 1);
            grid_XYZ.SetGridRowColumn(label_roomX, 0, 0);

            ////////
            // Y
            m_textBlock_roomY = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomY = new Label() { Content = "Y:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(m_textBlock_roomY, 0, 3);
            grid_XYZ.SetGridRowColumn(label_roomY, 0, 2);

            ////////
            // Z
            m_textBlock_roomZ = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomZ = new Label() { Content = "Z:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(m_textBlock_roomZ, 0, 5);
            grid_XYZ.SetGridRowColumn(label_roomZ, 0, 4);

            ////////
            // Name           
            m_textBox_roomName = new TextBox() { VerticalAlignment = VerticalAlignment.Center };
            m_textBox_roomName.TextChanged += TextBox_RoomName_TextChanged;
            Label label_roomName = new Label() { Content = "Name: ", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            this.SetGridRowColumn(m_textBox_roomName, 2, 1);
            this.SetGridRowColumn(label_roomName, 2, 0);

            ////////
            // Save 
            m_button_saveChanges = new Button() { Content = "Save Changes" };
            m_button_saveChanges.Click += Button_SaveChanges_Click;
            Grid.SetColumnSpan(m_button_saveChanges, 3);
            this.SetGridRowColumn(m_button_saveChanges, 3, 0);

            ////////
            // RoomStates
            Label label_roomStates = new Label() { Content = "Room States:", FontWeight = FontWeights.Bold };
            this.SetGridRowColumn(label_roomStates, 4, 0);

            Button button_addRoomState = new Button() { Content = "Add Room State" };
            button_addRoomState.Click += Button_AddRoomState_Click;
            Grid.SetColumnSpan(button_addRoomState, 2);
            this.SetGridRowColumn(button_addRoomState, 5, 0);

            ScrollViewer scrollViewer_roomStates =
                new ScrollViewer()
                {
                    HorizontalScrollBarVisibility = ScrollBarVisibility.Hidden,
                    VerticalScrollBarVisibility = ScrollBarVisibility.Visible
                };
            Grid.SetColumnSpan(scrollViewer_roomStates, 2);
            this.SetGridRowColumn(scrollViewer_roomStates, 6, 0);
        }

        private void SetValues(int areaId, int roomId, string name, int x, int y, int z)
        {
            AreaId = areaId;

            RoomId = roomId;
            m_textBlock_roomId.Text = RoomId.ToString();

            RoomName = name;
            m_textBox_roomName.Text = name;

            RoomX = x;
            m_textBlock_roomX.Text = x.ToString();

            RoomY = y;
            m_textBlock_roomY.Text = y.ToString();

            RoomZ = z;
            m_textBlock_roomZ.Text = z.ToString();
        }

        void TextBox_RoomName_TextChanged(object sender, TextChangedEventArgs e)
        {
            RoomName = m_textBox_roomName.Text;
        }

        private void Button_SaveChanges_Click(object sender, RoutedEventArgs e)
        {
            GinTubBuilderManager.ModifyRoom(RoomId, RoomName, RoomX, RoomY, RoomZ, AreaId);
        }

        void Button_AddRoomState_Click(object sender, RoutedEventArgs e)
        {
            Window_NewRoomState window = new Window_NewRoomState(RoomName);
            window.ShowDialog();
        }

        private void GinTubBuilderManager_RoomGet(object sender, GinTubBuilderManager.RoomGetEventArgs args)
        {
            SetValues(args.Area, args.Id, args.Name, args.X, args.Y, args.Z);
        }

        #endregion

        #endregion
    }
}
