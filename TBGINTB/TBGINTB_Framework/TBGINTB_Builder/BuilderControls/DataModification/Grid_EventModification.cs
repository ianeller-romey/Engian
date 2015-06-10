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
    public class Grid_EventModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_EventData m_grid_evnt;

        #endregion


        #region MEMBER PROPERTIES

        public int? EventId { get { return m_grid_evnt.EventId; } }
        public string EventName { get { return m_grid_evnt.EventName; } }
        public string EventDescription { get { return m_grid_evnt.EventDescription; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_EventModification(int? evntId, string evntName, string evntDescription)
        {
            CreateControls(evntId, evntName, evntDescription);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_evnt.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_evnt.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? evntId, string evntName, string evntDescription)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyEvent = new Button() { Content = "Modify Event" };
            button_modifyEvent.Click += Button_ModifyEvent_Click;
            this.SetGridRowColumn(button_modifyEvent, 0, 0);

            m_grid_evnt = new Grid_EventData(evntId, evntName, evntDescription, false);
            this.SetGridRowColumn(m_grid_evnt, 1, 0);
            m_grid_evnt.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyEvent_Click(object sender, RoutedEventArgs e)
        {
            Window_EventData window =
                new Window_EventData(m_grid_evnt.EventId, m_grid_evnt.EventName, m_grid_evnt.EventDescription);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyEvent(window.EventId.Value, window.EventName, window.EventDescription);
        }

        #endregion

        #endregion
    }
}
