using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class ComboBox_Location : ComboBox, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly ComboBoxItem
            c_comboBoxItem_newLocation = new ComboBoxItem() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER CLASSES       
    
        public class ComboBoxItem_Location : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int LocationId { get; private set; }
            public string LocationName { get; private set; }
            public string LocationFile { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ComboBoxItem_Location(int id, string locationName, string locationFile)
            {
                LocationId = id;
                LocationFile = locationFile;
                SetLocationName(locationName);
            }

            public void SetLocationName(string name)
            {
                LocationName = name;
                Content = LocationName;
            }

            public void SetLocationFile(string file)
            {
                LocationFile = file;
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBox_Location()
        {
            Items.Add(c_comboBoxItem_newLocation);

            SelectionChanged += ComboBox_Location_SelectionChanged;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.LocationAdded += GinTubBuilderManager_LocationAdded;
            GinTubBuilderManager.LocationModified += GinTubBuilderManager_LocationModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.LocationAdded -= GinTubBuilderManager_LocationAdded;
            GinTubBuilderManager.LocationModified += GinTubBuilderManager_LocationModified;
        }

        #endregion


        #region Private Functionality

        void GinTubBuilderManager_LocationAdded(object sender, GinTubBuilderManager.LocationAddedEventArgs args)
        {
            if (!Items.OfType<ComboBoxItem_Location>().Any(i => i.LocationId == args.Id))
                Items.Add(new ComboBoxItem_Location(args.Id, args.Name, args.LocationFile));
        }

        void GinTubBuilderManager_LocationModified(object sender, GinTubBuilderManager.LocationModifiedEventArgs args)
        {
            ComboBoxItem_Location i = Items.OfType<ComboBoxItem_Location>().SingleOrDefault(l => l.LocationId == args.Id);
            if(i != null)
            {
                i.SetLocationName(args.Name);
                i.SetLocationFile(args.LocationFile);
            }
        }

        void ComboBox_Location_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem item = null;
            if ((item = SelectedItem as ComboBoxItem) != null)
            {
                if (item == c_comboBoxItem_newLocation)
                    NewLocationDialog();
            }
        }

        #endregion

        #endregion
    }
}
