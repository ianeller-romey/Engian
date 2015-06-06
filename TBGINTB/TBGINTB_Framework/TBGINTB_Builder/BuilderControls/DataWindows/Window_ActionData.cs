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
    public class Window_ActionData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ActionData m_grid_action;

        #endregion


        #region MEMBER PROPERTIES

        public int? ActionId { get { return m_grid_action.ActionId; } }
        public int? ActionVerbType { get { return m_grid_action.ActionVerbType; } }
        public int? ActionNoun { get { return m_grid_action.ActionNoun; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ActionData(int? actionId, int? actionVerbType, int? actionNoun, int paragraphStateId)
        {
            Title = "Action Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(actionId, actionVerbType, actionNoun, paragraphStateId);
            m_grid_action.SetActiveAndRegisterForGinTubEvents(); // needed for possible nouns
            GinTubBuilderManager.LoadAllVerbTypes();
            GinTubBuilderManager.LoadAllNounsForParagraphState(paragraphStateId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? actionId, int? actionVerbType, int? actionNoun, int paragraphStateId)
        {
            m_grid_action = new Grid_ActionData(actionId, actionVerbType, actionNoun, paragraphStateId, true);
            return m_grid_action;
        }

        #endregion

        #endregion
    }
}
