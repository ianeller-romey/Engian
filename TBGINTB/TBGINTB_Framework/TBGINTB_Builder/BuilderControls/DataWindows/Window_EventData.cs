using System;
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
    public class Window_EventData : Window_AcceptCancel
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

        public Window_EventData(int? evntId, string evntName, string evntDescription)
        {
            Title = "Event Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(evntId, evntName, evntDescription);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? evntId, string evntName, string evntDescription)
        {
            m_grid_evnt = new Grid_EventData(evntId, evntName, evntDescription, true);
            return m_grid_evnt;
        }

        #endregion

        #endregion
    }
}
