using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Border_NounData : Border, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_NounData m_grid_noun;

        #endregion


        #region MEMBER PROPERTIES

        public int? NounId { get { return m_grid_noun.NounId; } }
        public string NounText { get { return m_grid_noun.NounText; } }
        public int ParagraphStateId { get { return m_grid_noun.ParagraphStateId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Border_NounData(int? nounId, string nounText, int paragraphStateId, bool enableEditing)
        {
            CreateControls(nounId, nounText, paragraphStateId, enableEditing);
            Style = Style_DefaultBorder.Instance;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_noun.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_noun.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? nounId, string nounText, int paragraphStateId, bool enableEditing)
        {
            m_grid_noun = new Grid_NounData(nounId, nounText, paragraphStateId, enableEditing);
            Child = m_grid_noun;
        }

        #endregion

        #endregion
    }
}
