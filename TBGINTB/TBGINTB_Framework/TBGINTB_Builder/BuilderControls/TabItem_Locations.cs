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
    public class TabItem_Locations : TabItem, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        ComboBox m_comboBox_locations;
        TextBlock m_textBlock_addLocation;
        Image_DisplayLocation m_image_displayLocation;
        private readonly ComboBoxItem
            c_comboBoxItem_newLocation = new ComboBoxItem() { Content = "++" };

        readonly string[] c_validImageTypes = { ".png", ".bmp", ".jpg" };

        #endregion


        #region MEMBER CLASSES

        private class ComboBoxItem_Location : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int Id { get; private set; }
            public string LocationName { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ComboBoxItem_Location(int id, string locationName)
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

            DisplayAddingControl();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.LocationAdded += GinTubBuilderManager_LocationAdded;
            GinTubBuilderManager.LocationModified += GinTubBuilderManager_LocationModified;

            m_image_displayLocation.SetActiveAndRegisterForGinTubEvents();

            GinTubBuilderManager.LoadAllLocations();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.LocationAdded -= GinTubBuilderManager_LocationAdded;
            GinTubBuilderManager.LocationModified -= GinTubBuilderManager_LocationModified;

            m_image_displayLocation.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            m_comboBox_locations = new ComboBox();
            m_comboBox_locations.Items.Add(c_comboBoxItem_newLocation);
            m_comboBox_locations.SelectedItem = null;
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

        private void DisplayAddingControl()
        {
            m_image_displayLocation.Visibility = Visibility.Collapsed;
            m_textBlock_addLocation.Visibility = Visibility.Visible;
        }

        private void DisplayLocation(int id)
        {
            m_image_displayLocation.Visibility = Visibility.Visible;
            m_textBlock_addLocation.Visibility = Visibility.Collapsed;

            GinTubBuilderManager.GetLocation(id);
        }

        private void AddedLocation(int id, string name)
        {
            if (m_comboBox_locations.Items.OfType<ComboBoxItem_Location>().Any(l => l.Id == id))
                return;

            object prevItem = m_comboBox_locations.SelectedItem;
            ComboBoxItem_Location lItem = new ComboBoxItem_Location(id, name);
            m_comboBox_locations.Items.Add(lItem);
            m_comboBox_locations.SelectedItem = (prevItem == c_comboBoxItem_newLocation) ? lItem : prevItem;
        }

        private void ModifiedLocation(int id, string name)
        {
            ComboBoxItem_Location lItem = m_comboBox_locations.Items.OfType<ComboBoxItem_Location>().Single(l => l.Id == id);
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
                if (item == c_comboBoxItem_newLocation)
                    DisplayAddingControl();
                else
                {
                    ComboBoxItem_Location lItem = item as ComboBoxItem_Location;
                    DisplayLocation(lItem.Id);
                }

            }
        }

        void GinTubBuilderManager_LocationAdded(object sender, GinTubBuilderManager.LocationAddedEventArgs args)
        {
            AddedLocation(args.Id, args.Name);
        }

        void GinTubBuilderManager_LocationModified(object sender, GinTubBuilderManager.LocationModifiedEventArgs args)
        {
            ModifiedLocation(args.Id, args.Name);
        }

        #endregion

        #endregion

    }
}
