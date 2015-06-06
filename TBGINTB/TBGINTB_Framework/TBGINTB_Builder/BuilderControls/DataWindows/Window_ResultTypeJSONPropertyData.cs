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
    public class Window_ResultTypeJSONPropertyData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ResultTypeJSONPropertyData m_grid_resultTypeJSONProperty;

        #endregion


        #region MEMBER PROPERTIES

        public int? ResultTypeJSONPropertyId { get { return m_grid_resultTypeJSONProperty.ResultTypeJSONPropertyId; } }
        public string ResultTypeJSONPropertyJSONProperty { get { return m_grid_resultTypeJSONProperty.ResultTypeJSONPropertyJSONProperty; } }
        public int ResultTypeId { get { return m_grid_resultTypeJSONProperty.ResultTypeId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ResultTypeJSONPropertyData(int? resultTypeJSONPropertyId, string resultTypeJSONPropertyJSONProperty, int resultTypeId)
        {
            Title = "ResultTypeJSONProperty Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(resultTypeJSONPropertyId, resultTypeJSONPropertyJSONProperty, resultTypeId);
            m_grid_resultTypeJSONProperty.SetActiveAndRegisterForGinTubEvents(); // needed for result types
            GinTubBuilderManager.LoadAllResultTypes();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? resultTypeJSONPropertyId, string resultTypeJSONPropertyJSONProperty, int resultTypeId)
        {
            m_grid_resultTypeJSONProperty = new Grid_ResultTypeJSONPropertyData(resultTypeJSONPropertyId, resultTypeJSONPropertyJSONProperty, resultTypeId, true);
            return m_grid_resultTypeJSONProperty;
        }

        #endregion

        #endregion
    }
}
