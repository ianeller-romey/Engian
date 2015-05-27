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
    public class Grid_RoomStateData : Grid
    {
        #region MEMBER FIELDS

        TextBlock m_textBlock_state;
        ComboBox_Location m_comboBox_location;
        ComboBox
            m_comboBox_hour,
            m_comboBox_minute;

        #endregion


        #region MEMBER PROPERTIES

        public int? RoomStateId { get; private set; }
        public int? RoomState { get; private set; }
        public int? LocationId { get; private set; }
        public DateTime? Time { get; private set; }
        public int RoomId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_comboBox_location,
                    m_comboBox_hour,
                    m_comboBox_minute
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomStateData(int? roomStateId, int? roomState, int? locationId, DateTime? time, int roomId, bool enableEditing)
        {
            RoomStateId = roomStateId;
            RoomState = roomState;
            LocationId = locationId;
            Time = time;
            RoomId = roomId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomStateModified += GinTubBuilderManager_RoomStateModified;

            GinTubBuilderManager.LocationAdded += GinTubBuilderManager_LocationAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomStateModified -= GinTubBuilderManager_RoomStateModified;

            GinTubBuilderManager.LocationAdded -= GinTubBuilderManager_LocationAdded;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            
            ////////
            // State Grid
            Grid grid_state = new Grid();
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_state, 0, 0);

            ////////
            // State
            m_textBlock_state = new TextBlock() { VerticalAlignment = VerticalAlignment.Center };
            SetRoomState(RoomState);
            Label label_roomState = new Label() { Content = "State:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_state.SetGridRowColumn(m_textBlock_state, 0, 1);
            grid_state.SetGridRowColumn(label_roomState, 0, 0);

            ////////
            // Location
            StackPanel stackPanel_location =
                new StackPanel()
                {
                    Orientation = Orientation.Horizontal,
                    HorizontalAlignment = HorizontalAlignment.Center
                };
            this.SetGridRowColumn(stackPanel_location, 1, 0);

            Label label_location = new Label() { Content = "Location: ", FontWeight = FontWeights.Bold };
            stackPanel_location.Children.Add(label_location);

            m_comboBox_location = new ComboBox_Location();
            m_comboBox_location.SetActiveAndRegisterForGinTubEvents(); // never unregister; we want updates no matter where we are
            m_comboBox_location.SelectionChanged += ComboBox_Location_SelectionChanged;
            stackPanel_location.Children.Add(m_comboBox_location);

            ////////
            // Time
            Grid grid_time = new Grid() { HorizontalAlignment = HorizontalAlignment.Center };
            grid_time.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_time.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_time.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_time.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_time.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_time, 2, 0);

            Label label_time = new Label() { Content = "Time: ", FontWeight = FontWeights.Bold };
            Grid.SetColumnSpan(label_time, 3);
            grid_time.SetGridRowColumn(label_time, 0, 0);

            m_comboBox_hour = new ComboBox();
            for (int i = 0; i <= 24; ++i)
                m_comboBox_hour.Items.Add(string.Format("{0:00}", i));
            grid_time.SetGridRowColumn(m_comboBox_hour, 1, 0);

            Label label_colon = new Label() { Content = " : " };
            grid_time.SetGridRowColumn(label_colon, 1, 1);

            m_comboBox_minute = new ComboBox();
            for (int i = 0; i < 60; ++i)
                m_comboBox_minute.Items.Add(string.Format("{0:00}", i));
            grid_time.SetGridRowColumn(m_comboBox_minute, 1, 2);

            SetTime(Time);
            m_comboBox_hour.SelectionChanged += ComboBox_Time_SelectionChanged;
            m_comboBox_minute.SelectionChanged += ComboBox_Time_SelectionChanged;
        }

        private void GinTubBuilderManager_RoomStateModified(object sender, GinTubBuilderManager.RoomStateModifiedEventArgs args)
        {
            if(RoomStateId == args.Id)
            {
                SetRoomState(args.State);
                LocationId = args.Location;
                SetTime(args.Time);
                RoomId = args.Room;

                GinTubBuilderManager.LoadAllLocations();
            }
        }

        private void GinTubBuilderManager_LocationAdded(object sender, GinTubBuilderManager.LocationAddedEventArgs args)
        {
            if (LocationId == args.Id)
                m_comboBox_location.SelectedItem = m_comboBox_location.Items.OfType<ComboBox_Location.ComboBoxItem_Location>().SingleOrDefault(i => i.LocationId == args.Id);
        }

        private void SetRoomState(int? state)
        {
            m_textBlock_state.Text = (RoomState.HasValue) ? RoomState.ToString() : "NewState";
        }

        private void SetTime(DateTime? time)
        {
            Time = time;
            if (Time != null)
            {
                m_comboBox_hour.SelectedItem = m_comboBox_hour.Items.OfType<string>().SingleOrDefault(h => int.Parse(h) == Time.Value.Hour);
                m_comboBox_minute.SelectedItem = m_comboBox_minute.Items.OfType<string>().SingleOrDefault(m => int.Parse(m) == Time.Value.Minute);
            }
            else
            {
                m_comboBox_hour.SelectedItem = null;
                m_comboBox_minute.SelectedItem = null;
            }
        }

        private void ComboBox_Location_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox_Location.ComboBoxItem_Location item;
            if (m_comboBox_location.SelectedItem != null && (item = m_comboBox_location.SelectedItem as ComboBox_Location.ComboBoxItem_Location) != null)
                LocationId = item.LocationId;
        }

        private void ComboBox_Time_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (m_comboBox_hour.SelectedItem != null && m_comboBox_minute.SelectedItem != null)
            {
                int
                    hour = int.Parse(m_comboBox_hour.SelectedItem.ToString()),
                    minute = int.Parse(m_comboBox_minute.SelectedItem.ToString());
                Time = new DateTime(1988, 8, 13, hour, minute, 0);
            }
        }

        #endregion

        #endregion
    }
}
