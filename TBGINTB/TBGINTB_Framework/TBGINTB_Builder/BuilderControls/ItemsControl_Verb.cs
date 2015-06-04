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
    public class ItemsControl_Verb : ItemsControl, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newVerb = new Button() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES

        public int VerbTypeId { get; private set; }

        #endregion


        #region MEMBER CLASSES

        public class ListBoxItem_Verb : ListBoxItem
        {
            #region MEMBER PROPERTIES

            public int VerbId { get; private set; }
            public string VerbName { get; private set; }
            public int VerbTypeId { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ListBoxItem_Verb(int verbId, string verbName, int verbTypeId)
            {
                VerbId = verbId;
                SetVerbName(verbName);
                SetVerbTypeId(verbTypeId);
            }

            public void SetVerbName(string verbName)
            {
                VerbName = verbName;
                Content = VerbName;
            }

            public void SetVerbTypeId(int verbTypeId)
            {
                VerbTypeId = verbTypeId;
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ItemsControl_Verb(int verbTypeId)
        {
            VerbTypeId = verbTypeId;

            c_button_newVerb.Click += ListBoxItem_NewVerb_Click;

            IsEnabled = false;
            IsEnabledChanged += ItemsControl_Verb_IsEnabledChanged;
            IsEnabled = true;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.VerbAdded += GinTubBuilderManager_VerbAdded;
            GinTubBuilderManager.VerbModified += GinTubBuilderManager_VerbModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.VerbAdded -= GinTubBuilderManager_VerbAdded;
            GinTubBuilderManager.VerbModified -= GinTubBuilderManager_VerbModified;
        }

        #endregion


        #region Private Functionality        

        void GinTubBuilderManager_VerbAdded(object sender, GinTubBuilderManager.VerbAddedEventArgs args)
        {
            if (args.VerbType == VerbTypeId && !Items.OfType<ListBoxItem_Verb>().Any(i => i.VerbId == args.Id))
                Items.Add(new ListBoxItem_Verb(args.Id, args.Name, args.VerbType));
        }

        void GinTubBuilderManager_VerbModified(object sender, GinTubBuilderManager.VerbModifiedEventArgs args)
        {
            if (args.VerbType == VerbTypeId)
            {
                ListBoxItem_Verb item = Items.OfType<ListBoxItem_Verb>().SingleOrDefault(i => i.VerbTypeId == args.Id);
                if (item != null)
                {
                    item.SetVerbName(args.Name);
                    item.SetVerbTypeId(args.VerbType);
                }
            }
        }

        private void NewVerbDialog()
        {
            Window_TextEntry window = new Window_TextEntry("Verb", "");
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddVerb(window.Text, VerbTypeId);
        }
        

        void ListBoxItem_NewVerb_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newVerb)
                NewVerbDialog();
        }

        void ItemsControl_Verb_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            ItemsControl_Verb control = sender as ItemsControl_Verb;
            if(sender != null && sender == this && e.Property == ItemsControl.IsEnabledProperty)
            {
                if ((bool)e.OldValue == true && (bool)e.NewValue == false)
                    Items.Remove(c_button_newVerb);
                else if ((bool)e.OldValue == false && (bool)e.NewValue == true)
                    Items.Insert(0, c_button_newVerb);
            }
        }

        #endregion

        #endregion
    }
}
