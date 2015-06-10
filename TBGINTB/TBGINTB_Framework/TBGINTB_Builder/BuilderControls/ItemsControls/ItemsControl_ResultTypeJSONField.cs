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
    public class ItemsControl_ResultTypeJSONProperty : ItemsControl, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newResultTypeJSONProperty = new Button() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES

        public int ResultTypeId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ItemsControl_ResultTypeJSONProperty(int resultTypeId)
        {
            ResultTypeId = resultTypeId;

            c_button_newResultTypeJSONProperty.Click += Button_NewResultTypeJSONProperty_Click;

            IsEnabled = false;
            IsEnabledChanged += ItemsControl_ResultTypeJSONProperty_IsEnabledChanged;
            IsEnabled = true;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ResultTypeJSONPropertyAdded += GinTubBuilderManager_ResultTypeJSONPropertyAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ResultTypeJSONPropertyAdded -= GinTubBuilderManager_ResultTypeJSONPropertyAdded;
        }

        #endregion


        #region Private Functionality        

        void GinTubBuilderManager_ResultTypeJSONPropertyAdded(object sender, GinTubBuilderManager.ResultTypeJSONPropertyAddedEventArgs args)
        {
            if (args.ResultType == ResultTypeId && !Items.OfType<Grid_ResultTypeJSONPropertyModification>().Any(i => i.ResultTypeJSONPropertyId == args.Id))
            {
                Grid_ResultTypeJSONPropertyModification grid = new Grid_ResultTypeJSONPropertyModification(args.Id, args.JSONProperty, args.ResultType);
                grid.SetActiveAndRegisterForGinTubEvents();
                Items.Add(grid);
                GinTubBuilderManager.LoadAllResultTypes();
            }
        }

        private void NewResultTypeJSONPropertyDialog()
        {
            Window_ResultTypeJSONPropertyData window = new Window_ResultTypeJSONPropertyData(null, null, ResultTypeId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddResultTypeJSONProperty(window.ResultTypeJSONPropertyJSONProperty, window.ResultTypeId);
        }
        

        void Button_NewResultTypeJSONProperty_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newResultTypeJSONProperty)
                NewResultTypeJSONPropertyDialog();
        }

        void ItemsControl_ResultTypeJSONProperty_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            ItemsControl_ResultTypeJSONProperty control = sender as ItemsControl_ResultTypeJSONProperty;
            if(sender != null && sender == this && e.Property == ItemsControl.IsEnabledProperty)
            {
                if ((bool)e.OldValue == true && (bool)e.NewValue == false)
                    Items.Remove(c_button_newResultTypeJSONProperty);
                else if ((bool)e.OldValue == false && (bool)e.NewValue == true)
                    Items.Insert(0, c_button_newResultTypeJSONProperty);
            }
        }

        #endregion

        #endregion
    }
}
