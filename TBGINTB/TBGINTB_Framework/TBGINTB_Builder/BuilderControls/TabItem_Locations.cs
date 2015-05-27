﻿using System;
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

        Grid_LocationData m_grid_locationData;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_Locations()
        {
            Header = "Locations";
            Content = CreateControls();
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_locationData.SetActiveAndRegisterForGinTubEvents();

            GinTubBuilderManager.LoadAllLocations();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_locationData.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            m_grid_locationData = new Grid_LocationData(true);

            return m_grid_locationData;
        }

        #endregion

        #endregion

    }
}
