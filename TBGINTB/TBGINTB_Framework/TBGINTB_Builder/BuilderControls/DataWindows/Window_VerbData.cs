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
    public class Window_VerbData : Window_AcceptCancel
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

        public Window_VerbData(int? verbId, string verbName, int verbTypeId)
        {
            Title = "Verb Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(verbId, verbName, verbTypeId);
            m_grid_verb.SetActiveAndRegisterForGinTubEvents(); // needed for possible nouns
            GinTubBuilderManager.LoadAllVerbTypes();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? verbId, string verbName, int verbTypeId)
        {
            m_grid_verb = new Grid_VerbData(verbId, verbName, verbTypeId, true);
            return m_grid_verb;
        }

        #endregion

        #endregion
    }
}
