using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ResultModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_ResultData m_grid_result;

        #endregion


        #region MEMBER PROPERTIES

        public int? ResultId { get { return m_grid_result.ResultId; } }
        public string ResultName { get { return m_grid_result.ResultName; } }
        public string ResultJSONData { get { return m_grid_result.ResultJSONData; } }
        public int ResultTypeId { get { return m_grid_result.ResultTypeId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ResultModification(int? resultId, string resultName, string resultJSONData, int resultTypeId)
        {
            CreateControls(resultId, resultName, resultJSONData, resultTypeId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_result.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_result.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? resultId, string resultName, string resultJSONData, int resultTypeId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyResult = new Button() { Content = "Modify Result" };
            button_modifyResult.Click += Button_ModifyParagraph_Click;
            this.SetGridRowColumn(button_modifyResult, 0, 0);

            m_grid_result = new Grid_ResultData(resultId, resultName, resultJSONData, resultTypeId, false);
            this.SetGridRowColumn(m_grid_result, 1, 0);
            m_grid_result.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyParagraph_Click(object sender, RoutedEventArgs e)
        {
            Window_ResultData window =
                new Window_ResultData(m_grid_result.ResultId, m_grid_result.ResultName, m_grid_result.ResultJSONData, m_grid_result.ResultTypeId);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyResult(window.ResultId.Value, window.ResultName, window.ResultJSONData, window.ResultTypeId);
        }

        #endregion

        #endregion
    }
}
