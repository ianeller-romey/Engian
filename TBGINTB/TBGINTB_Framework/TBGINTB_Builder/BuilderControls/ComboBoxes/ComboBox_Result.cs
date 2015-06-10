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
    public class ComboBox_Result : ComboBox, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        private readonly ComboBoxItem c_comboBoxItem_newResult = new ComboBoxItem() { Content = "++" };

        #endregion


        #region MEMBER PROPERTIES
        #endregion


        #region MEMBER CLASSES
    
        public class ComboBoxItem_Result : ComboBoxItem
        {
            #region MEMBER PROPERTIES

            public int ResultId { get; private set; }
            public string ResultName { get; private set; }
            public int ResultTypeId { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public ComboBoxItem_Result(int resultId, string resultName, int resultTypeId)
            {
                ResultId = resultId;
                SetResultName(resultName);
                SetResultTypeId(resultTypeId);
            }

            public void SetResultName(string resultName)
            {
                ResultName = resultName;
                Content = ResultName;
            }

            public void SetResultTypeId(int resultTypeId)
            {
                ResultTypeId = resultTypeId;
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBox_Result()
        {
            Items.Add(c_comboBoxItem_newResult);

            SelectionChanged += ComboBox_Result_SelectionChanged;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ResultAdded += GinTubBuilderManager_ResultAdded;
            GinTubBuilderManager.ResultModified += GinTubBuilderManager_ResultModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ResultAdded -= GinTubBuilderManager_ResultAdded;
            GinTubBuilderManager.ResultModified -= GinTubBuilderManager_ResultModified;
        }

        #endregion


        #region Private Functionality

        private void GinTubBuilderManager_ResultAdded(object sender, GinTubBuilderManager.ResultAddedEventArgs args)
        {
            if (!Items.OfType<ComboBoxItem_Result>().Any(i => i.ResultId == args.Id))
                Items.Add(new ComboBoxItem_Result(args.Id, args.Name, args.ResultType));
        }

        private void GinTubBuilderManager_ResultModified(object sender, GinTubBuilderManager.ResultModifiedEventArgs args)
        {
            ComboBoxItem_Result item = Items.OfType<ComboBoxItem_Result>().SingleOrDefault(i => i.ResultId == args.Id);
            if (item != null)
            {
                item.SetResultName(args.Name);
                item.SetResultTypeId(args.ResultType);
            }
        }

        private void NewResultDialog()
        {
            Window_ResultTypeData window_resultType = new Window_ResultTypeData(null, null);
            window_resultType.ShowDialog();
            if (window_resultType.Accepted)
            {
                Window_ResultData window_result = new Window_ResultData(null, null, null, window_resultType.ResultTypeId.Value);
                window_result.ShowDialog();
                if (window_result.Accepted)
                    GinTubBuilderManager.AddResult(window_result.Name, window_result.ResultJSONData, window_resultType.ResultTypeId.Value);
            }
        }

        private void ComboBox_Result_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem item = null;
            if ((item = SelectedItem as ComboBoxItem) != null)
            {
                if (item == c_comboBoxItem_newResult)
                    NewResultDialog();
            }
        }

        #endregion

        #endregion
    }
}
