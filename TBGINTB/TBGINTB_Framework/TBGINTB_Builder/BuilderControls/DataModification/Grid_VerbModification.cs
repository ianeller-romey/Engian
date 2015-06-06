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
    public class Grid_VerbModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_VerbData m_grid_verb;

        #endregion


        #region MEMBER PROPERTIES

        public int? VerbId { get { return m_grid_verb.VerbId; } }
        public string VerbName { get { return m_grid_verb.VerbName; } }
        public int VerbTypeId { get { return m_grid_verb.VerbTypeId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_VerbModification(int? verbId, string verbName, int verbTypeId)
        {
            CreateControls(verbId, verbName, verbTypeId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_verb.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_verb.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? verbId, string verbName, int verbTypeId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyVerb = new Button() { Content = "Modify Verb" };
            button_modifyVerb.Click += Button_ModifyParagraph_Click;
            this.SetGridRowColumn(button_modifyVerb, 0, 0);

            m_grid_verb = new Grid_VerbData(verbId, verbName, verbTypeId, false);
            this.SetGridRowColumn(m_grid_verb, 1, 0);
            m_grid_verb.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_VerbData window =
                new Window_VerbData(m_grid_verb.VerbId, m_grid_verb.VerbName, m_grid_verb.VerbTypeId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyVerb(window.VerbId.Value, window.VerbName, window.VerbTypeId);
        }

        #endregion

        #endregion
    }
}
