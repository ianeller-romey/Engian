using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_LocationData : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        ComboBox_Location m_comboBox_location;
        Image m_image_locationFile;

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_LocationData(bool enableEditing)
        {
            CreateControls();

            m_image_locationFile.AllowDrop = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.LocationModified += GinTubBuilderManager_LocationModifiedOrGet;
            GinTubBuilderManager.LocationGet += GinTubBuilderManager_LocationModifiedOrGet;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.LocationModified -= GinTubBuilderManager_LocationModifiedOrGet;
            GinTubBuilderManager.LocationGet -= GinTubBuilderManager_LocationModifiedOrGet;
        }
        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            m_comboBox_location = new ComboBox_Location();
            m_comboBox_location.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_location.SelectionChanged += ComboBox_LocationData_SelectionChanged;
            this.SetGridRowColumn(m_comboBox_location, 0, 0);

            m_image_locationFile = new Image();
            m_image_locationFile.Drop += Image_LocationFile_Drop;
            this.SetGridRowColumn(m_image_locationFile, 1, 0);
        }

        void GinTubBuilderManager_LocationModifiedOrGet(object sender, GinTubBuilderManager.LocationEventArgs args)
        {
            ComboBox_Location.ComboBoxItem_Location comboBoxItem = null;
            if ((comboBoxItem = m_comboBox_location.SelectedItem as ComboBox_Location.ComboBoxItem_Location) != null && comboBoxItem.LocationId == args.Id)
                SetLocationImage(args.LocationFile);
        }

        private void SetLocationImage(string locationFile)
        {
            m_image_locationFile.Source = (locationFile != null) ? new BitmapImage(new Uri(locationFile)) : null;
        }

        private void ComboBox_LocationData_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_Location comboBox = sender as ComboBox_Location;
            ComboBox_Location.ComboBoxItem_Location comboBoxItem = null;
            if (comboBox != null && (comboBoxItem = comboBox.SelectedItem as ComboBox_Location.ComboBoxItem_Location) != null)
                GinTubBuilderManager.GetLocation(comboBoxItem.LocationId);
            else
                SetLocationImage(null);
        }

        private void Image_LocationFile_Drop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                string file = files.First();
                if (ComboBox_Location.ValidFileTypes.Contains(Path.GetExtension(file)))
                {
                    ComboBox_Location.ComboBoxItem_Location comboBoxItem = null;
                    if ((comboBoxItem = m_comboBox_location.SelectedItem as ComboBox_Location.ComboBoxItem_Location) != null)
                        GinTubBuilderManager.ModifyLocation(comboBoxItem.LocationId, null, file);
                }
            }
        }

        #endregion

        #endregion
    }
}
