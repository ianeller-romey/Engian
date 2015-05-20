using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class TabItem_Area : TabItem
    {
        #region MEMBER FIELDS

        private Grid_RoomsOnFloor m_grid_roomsOnFloor;
        private Grid_RoomModify m_grid_roomModify;
        private Grid m_grid_main;
        private Grid m_grid_sub;
        private ComboBox m_comboBox_z;
        private readonly ComboBoxItem
            c_comboBoxItem_newFloorAbove = new ComboBoxItem() { Content = "++" },
            c_comboBoxItem_newFloorBelow = new ComboBoxItem() { Content = "--" };

        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public string AreaName { get; private set; }

        #endregion


        #region MEMBER CLASSES

        private class ZComboBoxItem : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int Z { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ZComboBoxItem(int z)
            {
                Z = z;
                Content = Z;
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_Area()
        {
            Content = CreateControls();
            AreaId = -1;
            SetAreaName("...");
            
            GinTubBuilderManager.AreaModified += GinTubBuilderManager_AreaModified;
            GinTubBuilderManager.AreaGet += GinTubBuilderManager_AreaGet;
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            m_grid_main = new Grid();
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            Label label_z = new Label() { Content = "Floor: ", FontWeight = FontWeights.Bold };

            m_comboBox_z = new ComboBox();
            m_comboBox_z.SelectionChanged += ComboBox_Z_SelectionChanged;

            StackPanel stackPanel_z = new StackPanel() { Orientation = Orientation.Horizontal };
            stackPanel_z.Children.Add(label_z);
            stackPanel_z.Children.Add(m_comboBox_z);
            m_grid_main.SetGridRowColumn(stackPanel_z, 0, 0);

            m_grid_sub = new Grid();
            m_grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(60.0, GridUnitType.Star) });
            m_grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(5.0, GridUnitType.Pixel) });
            m_grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(40.0, GridUnitType.Star) });
            m_grid_main.SetGridRowColumn(m_grid_sub, 1, 0);

            Rectangle rectangle_roomsOnFloor = new Rectangle() { Fill = Brushes.Lavender };
            m_grid_sub.SetGridRowColumn(rectangle_roomsOnFloor, 0, 0);

            GridSplitter gridSplitter = new GridSplitter() { Width = 5, HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch, Background = Brushes.Black };
            m_grid_sub.SetGridRowColumn(gridSplitter, 0, 1);

            m_grid_roomModify = new Grid_RoomModify();
            m_grid_sub.SetGridRowColumn(m_grid_roomModify, 0, 2);

            return m_grid_main;
        }

        private void GinTubBuilderManager_AreaModified(object sender, GinTubBuilderManager.AreaModifiedEventArgs args)
        {
            if (args.Id == AreaId)
                SetAreaName(args.Name);
        }

        private void GinTubBuilderManager_AreaGet(object sender, GinTubBuilderManager.AreaGetEventArgs args)
        {
            LoadArea(args.Id, args.Name, args.MaxX, args.MinX, args.MaxY, args.MinY, args.MinZ, args.MaxZ);
        }

        private void SetAreaName(string name)
        {
            AreaName = name;
            Header = AreaName;
        }

        private void LoadArea(int id, string name, int maxX, int minX, int maxY, int minY, int minZ, int maxZ)
        {
            AreaId = id;
            SetAreaName(name);

            m_grid_sub.Children.Remove(m_grid_roomsOnFloor);
            m_grid_roomsOnFloor = null;

            m_comboBox_z.Items.Clear();
            m_comboBox_z.Items.Add(c_comboBoxItem_newFloorAbove);
            m_comboBox_z.Items.Add(c_comboBoxItem_newFloorBelow);
            if(minZ < 0)
            {
                for (int z = minZ; z < 0; ++z)
                    AddFloorBelow();
                for (int z = 0; z <= maxZ; ++z)
                    AddFloorAbove();
            }
            else
            {
                for (int z = minZ; z <= maxZ; ++z)
                    AddFloorAbove();
            }
            m_comboBox_z.SelectedItem = m_comboBox_z.Items[m_comboBox_z.Items.Count - 2];

            m_grid_roomsOnFloor = new Grid_RoomsOnFloor(AreaId, maxX, maxY, minZ);
            m_grid_sub.SetGridRowColumn(m_grid_roomsOnFloor, 0, 0);
        }

        private void AddFloorAbove()
        {
            ZComboBoxItem item = m_comboBox_z.Items[1] as ZComboBoxItem;
            int newFloor = (item == null) ? 0 : item.Z + 1;
            item = new ZComboBoxItem(newFloor);
            m_comboBox_z.Items.Insert(1, item);
            m_comboBox_z.SelectedItem = item;
        }

        private void AddFloorBelow()
        {
            ZComboBoxItem item = m_comboBox_z.Items[m_comboBox_z.Items.Count - 2] as ZComboBoxItem;
            int newFloor = (item == null) ? -1 : item.Z - 1;
            item = new ZComboBoxItem(newFloor);
            m_comboBox_z.Items.Insert(m_comboBox_z.Items.Count - 1, item);
            m_comboBox_z.SelectedItem = item;
        }

        void ComboBox_Z_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem item = null;
            if(sender == m_comboBox_z && (item = m_comboBox_z.SelectedItem as ComboBoxItem) != null)
            {
                if (item == c_comboBoxItem_newFloorAbove)
                    AddFloorAbove();
                else if (item == c_comboBoxItem_newFloorBelow)
                    AddFloorBelow();
                else
                {
                    ZComboBoxItem zItem = item as ZComboBoxItem;
                    if (item != null && m_grid_roomsOnFloor != null)
                        m_grid_roomsOnFloor.SetFloor(zItem.Z);
                }

            }
        }

        #endregion

        #endregion
    }
}
