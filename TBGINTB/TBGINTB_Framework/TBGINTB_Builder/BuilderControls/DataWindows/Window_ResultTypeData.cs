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
    public class Window_ResultTypeData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ResultTypeData m_grid_resultType;

        #endregion


        #region MEMBER PROPERTIES

        public int? ResultTypeId { get { return m_grid_resultType.SelectedResultTypeId; } }
        public string ResultTypeName { get { return m_grid_resultType.SelectedResultTypeName; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ResultTypeData(int? resultTypeId, string resultTypeName)
        {
            Title = "ResultType Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(resultTypeId, resultTypeName);
            m_grid_resultType.SetActiveAndRegisterForGinTubEvents(); // needed for possible nouns
            GinTubBuilderManager.LoadAllResultTypes();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? resultTypeId, string resultTypeName)
        {
            m_grid_resultType = new Grid_ResultTypeData(true);
            return m_grid_resultType;
        }

        #endregion

        #endregion
    }
}
