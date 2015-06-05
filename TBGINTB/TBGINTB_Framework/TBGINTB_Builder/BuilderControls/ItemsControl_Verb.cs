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
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.VerbAdded -= GinTubBuilderManager_VerbAdded;
        }

        #endregion


        #region Private Functionality        

        void GinTubBuilderManager_VerbAdded(object sender, GinTubBuilderManager.VerbAddedEventArgs args)
        {
            if (args.VerbType == VerbTypeId && !Items.OfType<Grid_VerbUnderVerbType>().Any(i => i.VerbId == args.Id))
            {
                Grid_VerbUnderVerbType grid = new Grid_VerbUnderVerbType(args.Id, args.Name, args.VerbType);
                grid.SetActiveAndRegisterForGinTubEvents();
                Items.Add(grid);
                GinTubBuilderManager.LoadAllVerbTypes();
            }
        }

        private void NewVerbDialog()
        {
            Window_VerbData window = new Window_VerbData(null, null, VerbTypeId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddVerb(window.VerbName, window.VerbTypeId);
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
