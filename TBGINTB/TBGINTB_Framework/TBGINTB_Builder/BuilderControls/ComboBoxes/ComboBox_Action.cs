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
    public class ComboBox_Action : ComboBox, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly ComboBoxItem c_comboBoxItem_newAction = new ComboBoxItem() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES

        public int NounId { get; private set; }
        public int ParagraphStateId { get; private set; }

        #endregion


        #region MEMBER CLASSES
    
        public class ComboBoxItem_Action : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int ActionId { get; private set; }
            public int ActionVerbType { get; private set; }
            public int ActionNoun { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ComboBoxItem_Action(int actionId, int actionVerbType, int actionNoun)
            {
                ActionId = actionId;
                SetActionVerbType(actionVerbType);
                SetActionNoun(actionNoun);
            }

            public void SetActionVerbType(int actionVerbType)
            {
                ActionVerbType = actionVerbType;
                Content = string.Format("{0} - {1}", ActionVerbType, ActionNoun);
            }

            public void SetActionNoun(int actionNoun)
            {
                ActionNoun = actionNoun;
                Content = string.Format("{0} - {1}", ActionVerbType, ActionNoun);
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBox_Action(int nounId, int paragraphStateId)
        {
            NounId = nounId;
            ParagraphStateId = paragraphStateId;

            Items.Add(c_comboBoxItem_newAction);

            SelectionChanged += ComboBox_Action_SelectionChanged;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ActionAdded += GinTubBuilderManager_ActionAdded;
            GinTubBuilderManager.ActionModified += GinTubBuilderManager_ActionModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ActionAdded -= GinTubBuilderManager_ActionAdded;
            GinTubBuilderManager.ActionModified -= GinTubBuilderManager_ActionModified;
        }

        #endregion


        #region Private Functionality

        void GinTubBuilderManager_ActionAdded(object sender, GinTubBuilderManager.ActionAddedEventArgs args)
        {
            if (NounId == args.Id)
            {
                if (!Items.OfType<ComboBoxItem_Action>().Any(i => i.ActionId == args.Id))
                    Items.Add(new ComboBoxItem_Action(args.Id, args.Noun, args.VerbType));
            }
        }

        void GinTubBuilderManager_ActionModified(object sender, GinTubBuilderManager.ActionModifiedEventArgs args)
        {
            if (NounId == args.Id)
            {
                ComboBoxItem_Action item = Items.OfType<ComboBoxItem_Action>().SingleOrDefault(i => i.ActionId == args.Id);
                if (item != null)
                {
                    item.SetActionVerbType(args.VerbType);
                    item.SetActionNoun(args.Noun);
                }
            }
        }

        private void NewActionDialog()
        {
            Window_ActionData window = new Window_ActionData(null, null, NounId, ParagraphStateId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddAction(window.ActionVerbType.Value, window.ActionNoun.Value);
        }

        private void ComboBox_Action_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem item = null;
            if ((item = SelectedItem as ComboBoxItem) != null)
            {
                if (item == c_comboBoxItem_newAction)
                    NewActionDialog();
            }
        }

        #endregion

        #endregion
    }
}
