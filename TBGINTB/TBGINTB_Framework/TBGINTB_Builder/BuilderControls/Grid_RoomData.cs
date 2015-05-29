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
    public class Grid_RoomData : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        TextBox m_textBox_roomName;
        TextBlock
            m_textBlock_roomX,
            m_textBlock_roomY,
            m_textBlock_roomZ;

        #endregion


        #region MEMBER PROPERTIES

        public int? RoomId { get; private set; }
        public string RoomName { get; private set; }
        public int RoomX { get; private set; }
        public int RoomY { get; private set; }
        public int RoomZ { get; private set; }
        public int AreaId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_textBox_roomName
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomData(int? roomId, string roomName, int x, int y, int z, int areaId, bool enableEditing)
        {
            RoomId = roomId;
            RoomName = roomName;
            RoomX = x;
            RoomY = y;
            RoomZ = z;
            AreaId = areaId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomModified += GinTubBuilderManager_RoomModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomModified -= GinTubBuilderManager_RoomModified;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            ////////
            // Id Grid
            Grid grid_id = new Grid();
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_id, 0, 0);

            ////////
            // Id
            TextBlock textBlock_roomId = 
                new TextBlock() 
                { 
                    VerticalAlignment = VerticalAlignment.Center, 
                    Text = (RoomId.HasValue) ? RoomId.ToString() : "NewRoom"
                };
            Label label_roomId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_roomId, 0, 1);
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
            this.SetGridRowColumn(grid_XYZ, 1, 0);

            ////////
            // X
            m_textBlock_roomX = new TextBlock() { VerticalAlignment = VerticalAlignment.Center, Text = RoomX.ToString() };
            Label label_roomX = new Label() { Content = "X:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(m_textBlock_roomX, 0, 1);
            grid_XYZ.SetGridRowColumn(label_roomX, 0, 0);

            ////////
            // Y
            m_textBlock_roomY = new TextBlock() { VerticalAlignment = VerticalAlignment.Center, Text = RoomY.ToString() };
            Label label_roomY = new Label() { Content = "Y:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(m_textBlock_roomY, 0, 3);
            grid_XYZ.SetGridRowColumn(label_roomY, 0, 2);

            ////////
            // Z
            m_textBlock_roomZ = new TextBlock() { VerticalAlignment = VerticalAlignment.Center, Text = RoomZ.ToString() };
            Label label_roomZ = new Label() { Content = "Z:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(m_textBlock_roomZ, 0, 5);
            grid_XYZ.SetGridRowColumn(label_roomZ, 0, 4);

            ////////
            // Name Grid
            Grid grid_name = new Grid();
            grid_name.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_name.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_name, 2, 0);

            ////////
            // Name
            m_textBox_roomName = new TextBox() { VerticalAlignment = VerticalAlignment.Center, Text = RoomName };
            m_textBox_roomName.TextChanged += TextBox_RoomName_TextChanged;
            Label label_roomName = new Label() { Content = "Name: ", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_name.SetGridRowColumn(m_textBox_roomName, 0, 1);
            grid_name.SetGridRowColumn(label_roomName, 0, 0);

        }

        private void GinTubBuilderManager_RoomModified(object sender, GinTubBuilderManager.RoomModifiedEventArgs args)
        {
            if (args.Id == RoomId)
            {
                SetRoomX(args.X);
                SetRoomY(args.Y);
                SetRoomZ(args.Z);
                SetRoomName(args.Name);
                AreaId = args.Area;
            }
        }

        private void SetRoomX(int x)
        {
            RoomX = x;
            m_textBlock_roomX.Text = RoomX.ToString();
        }

        private void SetRoomY(int y)
        {
            RoomY = y;
            m_textBlock_roomY.Text = RoomY.ToString();
        }

        private void SetRoomZ(int z)
        {
            RoomZ = z;
            m_textBlock_roomZ.Text = RoomZ.ToString();
        }

        private void SetRoomName(string name)
        {
            m_textBox_roomName.Text = name;
            if (!m_textBox_roomName.IsEnabled)
                TextBox_RoomName_TextChanged(m_textBox_roomName, new TextChangedEventArgs(TextBox.TextChangedEvent, UndoAction.Undo));
        }

        private void TextBox_RoomName_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb != null && tb == m_textBox_roomName)
                RoomName = m_textBox_roomName.Text;
        }

        #endregion

        #endregion
    }
}
