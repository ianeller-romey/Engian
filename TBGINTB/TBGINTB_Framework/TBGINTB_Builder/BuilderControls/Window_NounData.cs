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
    public class Window_NounData : Window_AcceptCancel
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

        public Window_NounData(int? nounId, string nounText, int paragraphStateId)
        {
            Title = "Noun Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(paragraphStateId, nounText, paragraphStateId);
            m_grid_noun.SetActiveAndRegisterForGinTubEvents(); // needed for possible nouns
            GinTubBuilderManager.LoadParagraphState(paragraphStateId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? nounId, string nounText, int paragraphStateId)
        {
            m_grid_noun = new Grid_NounData(paragraphStateId, nounText, paragraphStateId, true);
            return m_grid_noun;
        }

        #endregion

        #endregion
    }
}
