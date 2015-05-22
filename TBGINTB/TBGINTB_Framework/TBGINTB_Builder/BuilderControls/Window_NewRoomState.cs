﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Window_NewRoomState : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        ComboBox m_comboBox_location;
        ComboBox m_comboBox_hour;
        ComboBox m_comboBox_minute;

        #endregion


        #region MEMBER PROPERTIES

        public int LocationId { get; private set; }
        public TimeSpan Time { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_NewRoomState(string roomName)
        {
            Title = string.Format("New Room State for {0}", roomName);
            Width = 300;
            Height = 300;
            Content = CreateControls();

            GinTubBuilderManager.LocationGet += GinTubBuilderManager_LocationGet;
            GinTubBuilderManager.GetAllLocations();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            ////////
            // Location
            StackPanel stackPanel_location = 
                new StackPanel() 
                { 
                    Orientation = Orientation.Horizontal, 
                    HorizontalAlignment = HorizontalAlignment.Center 
                };
            grid_main.SetGridRowColumn(stackPanel_location, 0, 0);

            Label label_location = new Label() { Content = "Location: ", FontWeight = FontWeights.Bold };
            stackPanel_location.Children.Add(label_location);

            m_comboBox_location = new ComboBox();
            m_comboBox_location.SelectionChanged += ComboBox_Location_SelectionChanged;
            stackPanel_location.Children.Add(m_comboBox_location);

            ////////
            // Time
            Grid grid_time = new Grid() { HorizontalAlignment = HorizontalAlignment.Center};
            grid_time.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_time.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_time.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_time.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_time.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_main.SetGridRowColumn(grid_time, 1, 0);

            Label label_time = new Label() { Content = "Time: ", FontWeight = FontWeights.Bold };
            Grid.SetColumnSpan(label_time, 3);
            grid_time.SetGridRowColumn(label_time, 0, 0);

            m_comboBox_hour = new ComboBox();
            for (int i = 0; i <= 24; ++i)
                m_comboBox_hour.Items.Add(string.Format("{0:00}", i));
            m_comboBox_hour.SelectionChanged += ComboBox_Time_SelectionChanged;
            grid_time.SetGridRowColumn(m_comboBox_hour, 1, 0);

            Label label_colon = new Label() { Content = " : " };
            grid_time.SetGridRowColumn(label_colon, 1, 1);

            m_comboBox_minute = new ComboBox();
            for (int i = 0; i < 60; ++i)
                m_comboBox_minute.Items.Add(string.Format("{0:00}", i));
            grid_time.SetGridRowColumn(m_comboBox_minute, 1, 2);

            return grid_main;
        }

        private void GinTubBuilderManager_LocationGet(object sender, GinTubBuilderManager.LocationGetEventArgs args)
        {
            m_comboBox_location.Items.Add(new ComboBoxItem_Location(args.Id, args.Name, args.LocationFile));
        }

        void ComboBox_Location_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem_Location item;
            if(m_comboBox_location.SelectedItem != null && (item = m_comboBox_location.SelectedItem as ComboBoxItem_Location) != null)
                LocationId = item.LocationId;
        }

        private void ComboBox_Time_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(m_comboBox_hour.SelectedItem != null && m_comboBox_minute.SelectedItem != null)
            {
                int 
                    hour = int.Parse(m_comboBox_hour.SelectedItem.ToString()),
                    minute = int.Parse(m_comboBox_minute.SelectedItem.ToString());
                Time = new TimeSpan(hour, minute, 0);
            }
        }

        #endregion

        #endregion
    }
}
