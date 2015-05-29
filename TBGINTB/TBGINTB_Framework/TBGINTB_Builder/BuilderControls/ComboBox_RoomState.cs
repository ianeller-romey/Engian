using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class ComboBox_RoomState : ComboBox, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly ComboBoxItem c_comboBoxItem_newRoomState = new ComboBoxItem() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER CLASSES
    
        public class ComboBoxItem_RoomState : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int RoomStateId { get; private set; }
            public int RoomState { get; private set; }
            public int LocationId { get; private set; }
            public DateTime? Time { get; private set; }
            public int RoomId { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ComboBoxItem_RoomState(int id, int state, int location, DateTime? time, int room)
            {
                RoomStateId = id;
                RoomState = state;
                LocationId = location;
                Time = time;
                RoomId = room;
            }

            public void SetRoomState(int state)
            {
                RoomState = state;
                SetContent();
            }

            public void SetLocation(int location)
            {
                LocationId = location;
                SetContent();
            }

            public void SetTime(DateTime? time)
            {
                Time = time;
                SetContent();
            }

            public void SetRoom(int room)
            {
                RoomId = room;
                SetContent();
            }

            #endregion


            #region Private Functionality

            private void SetContent()
            {
                Content = (Time.HasValue) 
                    ? string.Format("State {0} at {1:00}:{2:00}", RoomState, Time.Value.Hour, Time.Value.Minute)
                    : string.Format("State {0}", RoomState);
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBox_RoomState()
        {
            Items.Add(c_comboBoxItem_newRoomState);

            SelectionChanged += ComboBox_RoomState_SelectionChanged;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomStateAdded += GinTubBuilderManager_RoomStateAdded;
            GinTubBuilderManager.RoomStateModified += GinTubBuilderManager_RoomStateModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomStateAdded -= GinTubBuilderManager_RoomStateAdded;
            GinTubBuilderManager.RoomStateModified += GinTubBuilderManager_RoomStateModified;
        }

        #endregion


        #region Private Functionality

        private void GinTubBuilderManager_RoomStateAdded(object sender, GinTubBuilderManager.RoomStateAddedEventArgs args)
        {
            if (!Items.OfType<ComboBoxItem_RoomState>().Any(i => i.RoomStateId == args.Id))
                Items.Add(new ComboBoxItem_RoomState(args.Id, args.State, args.Location, args.Time, args.Room));
        }

        private void GinTubBuilderManager_RoomStateModified(object sender, GinTubBuilderManager.RoomStateModifiedEventArgs args)
        {
            ComboBoxItem_RoomState i = Items.OfType<ComboBoxItem_RoomState>().SingleOrDefault(l => l.RoomStateId == args.Id);
            if(i != null)
            {
                i.SetRoomState(args.State);
                i.SetLocation(args.Location);
                i.SetTime(args.Time);
                i.SetRoom(args.Room);
            }
        }

        private void NewLocationDialog()
        {
            Window_OpenFile window_openFile = new Window_OpenFile("Location File", string.Empty);
            window_openFile.ShowDialog();
            if (window_openFile.Accepted)
            {
                Window_TextEntry window_textEntry = new Window_TextEntry("Location Name", Path.GetFileNameWithoutExtension(window_openFile.FileName));
                window_textEntry.ShowDialog();
                if (window_textEntry.Accepted)
                    GinTubBuilderManager.AddLocation(window_textEntry.Text, window_openFile.FileName);
            }
        }

        private void ComboBox_RoomState_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem item = null;
            if ((item = SelectedItem as ComboBoxItem) != null)
            {
                if (item == c_comboBoxItem_newRoomState)
                    NewLocationDialog();
            }
        }

        #endregion

        #endregion
    }
}
