using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class TabItem_Locations : TabItem
    {
        #region MEMBER FIELDS

        ComboBox m_comboBox_locations;
        TextBlock m_textBlock_addLocation;
        Image_DisplayLocation m_image_displayLocation;
        private readonly ComboBoxItem
            c_comboBoxItem_newFloorAbove = new ComboBoxItem() { Content = "++" };

        readonly string[] c_validImageTypes = { ".png", ".bmp", ".jpg" };

        #endregion


        #region MEMBER CLASSES

        private class LocationComboBoxItem : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int Id { get; private set; }
            public string LocationName { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public LocationComboBoxItem(int id, string locationName)
            {
                Id = id;
                SetLocationName(locationName);
            }

            public void SetLocationName(string name)
            {
                LocationName = name;
                Content = LocationName;
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_Locations()
        {
            Header = "Locations";
            Content = CreateControls();

            AddNewLocation();

            GinTubBuilderManager.LocationAdded += GinTubBuilderManager_LocationAdded;
            GinTubBuilderManager.LocationModified += GinTubBuilderManager_LocationModified;
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            m_comboBox_locations = new ComboBox();
            m_comboBox_locations.Items.Add(c_comboBoxItem_newFloorAbove);
            m_comboBox_locations.SelectedItem = c_comboBoxItem_newFloorAbove;
            m_comboBox_locations.SelectionChanged += ComboBox_Locations_SelectionChanged;
            grid_main.SetGridRowColumn(m_comboBox_locations, 0, 0);

            m_textBlock_addLocation = 
                new TextBlock() 
                { 
                    Text = "++", 
                    FontSize = 100.0, 
                    HorizontalAlignment = HorizontalAlignment.Center, 
                    VerticalAlignment = VerticalAlignment.Center,
                    AllowDrop = true
                };
            m_textBlock_addLocation.Drop += TextBlock_AddLocation_Drop;
            grid_main.SetGridRowColumn(m_textBlock_addLocation, 1, 0);

            m_image_displayLocation = new Image_DisplayLocation();
            grid_main.SetGridRowColumn(m_image_displayLocation, 1, 0);

            return grid_main;
        }

        private void AddNewLocation()
        {
            m_image_displayLocation.Visibility = Visibility.Collapsed;
            m_textBlock_addLocation.Visibility = Visibility.Visible;
        }

        private void DisplayLocation(int id)
        {
            m_image_displayLocation.Visibility = Visibility.Visible;
            m_textBlock_addLocation.Visibility = Visibility.Collapsed;

            m_image_displayLocation.Focus();
            GinTubBuilderManager.GetLocation(id);
        }

        private void LocationAdded(int id, string name)
        {
            LocationComboBoxItem lItem = new LocationComboBoxItem(id, name);
            m_comboBox_locations.Items.Add(lItem);
            m_comboBox_locations.SelectedItem = lItem;
        }

        private void LocationModified(int id, string name)
        {
            LocationComboBoxItem lItem = m_comboBox_locations.Items.OfType<LocationComboBoxItem>().Single(l => l.Id == id);
            lItem.SetLocationName(name);
            if (m_comboBox_locations.SelectedItem == lItem) DisplayLocation(lItem.Id);
            else m_comboBox_locations.SelectedItem = lItem;
        }

        void TextBlock_AddLocation_Drop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                string file = files.First();
                if (c_validImageTypes.Contains(Path.GetExtension(file)))
                {
                    Window_TextEntry window = new Window_TextEntry("Location Name", "");
                    window.ShowDialog();
                    if (window.Accepted)
                        GinTubBuilderManager.AddLocation(window.Text, file);
                }
            }
        }

        private void ComboBox_Locations_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem item = null;
            if (sender == m_comboBox_locations && (item = m_comboBox_locations.SelectedItem as ComboBoxItem) != null)
            {
                if (item == c_comboBoxItem_newFloorAbove)
                    AddNewLocation();
                else
                {
                    LocationComboBoxItem lItem = item as LocationComboBoxItem;
                    DisplayLocation(lItem.Id);
                }

            }
        }

        void GinTubBuilderManager_LocationAdded(object sender, GinTubBuilderManager.LocationAddedEventArgs args)
        {
            LocationAdded(args.Id, args.Name);
        }

        void GinTubBuilderManager_LocationModified(object sender, GinTubBuilderManager.LocationModifiedEventArgs args)
        {
            LocationModified(args.Id, args.Name);
        }

        #endregion

        #endregion

    }
}
