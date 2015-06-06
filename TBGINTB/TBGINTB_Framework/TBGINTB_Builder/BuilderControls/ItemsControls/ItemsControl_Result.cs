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
    public class ItemsControl_Result : ItemsControl, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly Button c_button_newResult = new Button() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES

        public int ResultTypeId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ItemsControl_Result(int resultTypeId)
        {
            ResultTypeId = resultTypeId;

            c_button_newResult.Click += ListBoxItem_NewResult_Click;

            IsEnabled = false;
            IsEnabledChanged += ItemsControl_Result_IsEnabledChanged;
            IsEnabled = true;
        }
    
        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ResultAdded += GinTubBuilderManager_ResultAdded;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ResultAdded -= GinTubBuilderManager_ResultAdded;
        }

        #endregion


        #region Private Functionality        

        void GinTubBuilderManager_ResultAdded(object sender, GinTubBuilderManager.ResultAddedEventArgs args)
        {
            if (args.ResultType == ResultTypeId && !Items.OfType<Grid_ResultModification>().Any(i => i.ResultId == args.Id))
            {
                Grid_ResultModification grid = new Grid_ResultModification(args.Id, args.Name, args.JSONData, args.ResultType);
                grid.SetActiveAndRegisterForGinTubEvents();
                Items.Add(grid);
                GinTubBuilderManager.LoadAllResultTypes();
                GinTubBuilderManager.LoadAllResultTypeJSONPropertiesForResultType(args.ResultType);
            }
        }

        private void NewResultDialog()
        {
            Window_ResultData window = new Window_ResultData(null, null, null, ResultTypeId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddResult(window.ResultName, window.ResultJSONData, window.ResultTypeId);
        }
        

        void ListBoxItem_NewResult_Click(object sender, RoutedEventArgs e)
        {
            Button item = null;
            if ((item = sender as Button) != null && item == c_button_newResult)
                NewResultDialog();
        }

        void ItemsControl_Result_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            ItemsControl_Result control = sender as ItemsControl_Result;
            if(sender != null && sender == this && e.Property == ItemsControl.IsEnabledProperty)
            {
                if ((bool)e.OldValue == true && (bool)e.NewValue == false)
                    Items.Remove(c_button_newResult);
                else if ((bool)e.OldValue == false && (bool)e.NewValue == true)
                    Items.Insert(0, c_button_newResult);
            }
        }

        #endregion

        #endregion
    }
}
