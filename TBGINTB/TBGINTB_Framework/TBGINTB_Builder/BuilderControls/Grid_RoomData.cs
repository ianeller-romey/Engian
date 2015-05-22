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

        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public int? RoomId { get; private set; }
        public string RoomName { get; private set; }
        public int RoomX { get; private set; }
        public int RoomY { get; private set; }
        public int RoomZ { get; private set; }

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
            TextBlock textBlock_roomX = new TextBlock() { VerticalAlignment = VerticalAlignment.Center, Text = RoomX.ToString() };
            Label label_roomX = new Label() { Content = "X:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(textBlock_roomX, 0, 1);
            grid_XYZ.SetGridRowColumn(label_roomX, 0, 0);

            ////////
            // Y
            TextBlock textBlock_roomY = new TextBlock() { VerticalAlignment = VerticalAlignment.Center, Text = RoomY.ToString() };
            Label label_roomY = new Label() { Content = "Y:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(textBlock_roomY, 0, 3);
            grid_XYZ.SetGridRowColumn(label_roomY, 0, 2);

            ////////
            // Z
            TextBlock textBlock_roomZ = new TextBlock() { VerticalAlignment = VerticalAlignment.Center, Text = RoomZ.ToString() };
            Label label_roomZ = new Label() { Content = "Z:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_XYZ.SetGridRowColumn(textBlock_roomZ, 0, 5);
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
                m_textBox_roomName.Text = args.Name;
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
