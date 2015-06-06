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
    public class Window_ResultData : Window_AcceptCancel
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

        public Window_ResultData(int? resultId, string resultName, string resultJSONData, int resultTypeId)
        {
            Title = "Result Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(resultId, resultName, resultJSONData, resultTypeId);
            m_grid_result.SetActiveAndRegisterForGinTubEvents(); // needed for possible nouns
            GinTubBuilderManager.LoadAllResultTypes();
            GinTubBuilderManager.LoadAllResultTypeJSONPropertiesForResultType(resultTypeId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? resultId, string resultName, string resultJSONData, int resultTypeId)
        {
            m_grid_result = new Grid_ResultData(resultId, resultName, resultJSONData, resultTypeId, true);
            return m_grid_result;
        }

        #endregion

        #endregion
    }
}
