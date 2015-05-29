using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.BuilderControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class TextBlock_ParagraphText : TextBlock, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int ParagraphId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TextBlock_ParagraphText(int paragraphId, string paragraphText)
        {
            ParagraphId = paragraphId;
            Text = paragraphText;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphModified += GinTubBuilderManager_ParagraphModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphModified -= GinTubBuilderManager_ParagraphModified;
        }

        #endregion


        #region Private Functionality

        private void GinTubBuilderManager_ParagraphModified(object sender, GinTubBuilderManager.ParagraphModifiedEventArgs args)
        {
            if (args.Id == ParagraphId)
                this.Text = args.Text;
        }

        #endregion

        #endregion

    }
}
