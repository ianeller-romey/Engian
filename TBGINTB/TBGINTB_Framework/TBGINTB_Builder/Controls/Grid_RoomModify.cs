using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib;

using IANWork;


namespace TBGINTB_Builder.Controls
{
    public class Grid_RoomModify : Grid
    {
        #region MEMBER FIELDS

        TextBlock
            m_textBlock_roomId,
            m_textBlock_roomX,
            m_textBlock_roomY,
            m_textBlock_roomZ;
        TextBox m_textBox_roomName;
        Button m_button_saveChanges;

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

            GinTubBuilderManager.RoomGet += GinTubBuilderManager_RoomGet;
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

            ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(100.0, GridUnitType.Star) });

            ////////
            // Id Grid
            Grid grid_id = new Grid();
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            Grid.SetColumnSpan(grid_id, 2);
            IW.SetGridRowColumn(this, grid_id, 0, 0);

            ////////
            // Id
            m_textBlock_roomId = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            IW.SetGridRowColumn(grid_id, m_textBlock_roomId, 0, 1);
            IW.SetGridRowColumn(grid_id, label_roomId, 0, 0);

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
            IW.SetGridRowColumn(this, grid_XYZ, 1, 0);

            ////////
            // X
            m_textBlock_roomX = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomX = new Label() { Content = "X:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            IW.SetGridRowColumn(grid_XYZ, m_textBlock_roomX, 0, 1);
            IW.SetGridRowColumn(grid_XYZ, label_roomX, 0, 0);

            ////////
            // Y
            m_textBlock_roomY = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomY = new Label() { Content = "Y:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            IW.SetGridRowColumn(grid_XYZ, m_textBlock_roomY, 0, 3);
            IW.SetGridRowColumn(grid_XYZ, label_roomY, 0, 2);

            ////////
            // Z
            m_textBlock_roomZ = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            Label label_roomZ = new Label() { Content = "Z:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            IW.SetGridRowColumn(grid_XYZ, m_textBlock_roomZ, 0, 5);
            IW.SetGridRowColumn(grid_XYZ, label_roomZ, 0, 4);

            ////////
            // Name           
            m_textBox_roomName = new TextBox() { VerticalAlignment = VerticalAlignment.Center };
            m_textBox_roomName.TextChanged += TextBox_RoomName_TextChanged;
            Label label_roomName = new Label() { Content = "Name: ", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            IW.SetGridRowColumn(this, m_textBox_roomName, 2, 1);
            IW.SetGridRowColumn(this, label_roomName, 2, 0);

            ////////
            // Save 
            m_button_saveChanges = new Button() { Content = "Save Changes" };
            m_button_saveChanges.Click += Button_SaveChanges_Click;
            Grid.SetColumnSpan(m_button_saveChanges, 3);
            IW.SetGridRowColumn(this, m_button_saveChanges, 3, 0);
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

        private void GinTubBuilderManager_RoomGet(object sender, GinTubBuilderManager.RoomGetEventArgs args)
        {
            SetValues(args.Area, args.Id, args.Name, args.X, args.Y, args.Z);
        }

        #endregion

        #endregion
    }
}
