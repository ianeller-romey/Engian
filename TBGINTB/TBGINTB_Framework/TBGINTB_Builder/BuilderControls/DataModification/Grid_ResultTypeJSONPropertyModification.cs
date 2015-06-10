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
    public class Grid_ResultTypeJSONPropertyModification : Grid, IRegisterGinTubEventsOnlyWhenActive
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

        public Grid_ResultTypeJSONPropertyModification(int? resultTypeJSONPropertyId, string resultTypeJSONPropertyJSONProperty, int resultTypeId)
        {
            CreateControls(resultTypeJSONPropertyId, resultTypeJSONPropertyJSONProperty, resultTypeId);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_resultTypeJSONProperty.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_resultTypeJSONProperty.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? resultTypeJSONPropertyId, string resultTypeJSONPropertyJSONProperty, int resultTypeId)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyResultTypeJSONProperty = new Button() { Content = "Modify ResultTypeJSONProperty" };
            button_modifyResultTypeJSONProperty.Click += Button_ModifyResultTypeJSONProperty_Click;
            this.SetGridRowColumn(button_modifyResultTypeJSONProperty, 0, 0);

            m_grid_resultTypeJSONProperty = new Grid_ResultTypeJSONPropertyData(resultTypeJSONPropertyId, resultTypeJSONPropertyJSONProperty, resultTypeId, false);
            this.SetGridRowColumn(m_grid_resultTypeJSONProperty, 1, 0);
            m_grid_resultTypeJSONProperty.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyResultTypeJSONProperty_Click(object sender, RoutedEventArgs e)
        {
            Window_ResultTypeJSONPropertyData window =
                new Window_ResultTypeJSONPropertyData
                (
                    m_grid_resultTypeJSONProperty.ResultTypeJSONPropertyId, 
                    m_grid_resultTypeJSONProperty.ResultTypeJSONPropertyJSONProperty, 
                    m_grid_resultTypeJSONProperty.ResultTypeId
                );
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyResultTypeJSONProperty
                (
                    window.ResultTypeJSONPropertyId.Value, 
                    window.ResultTypeJSONPropertyJSONProperty, 
                    window.ResultTypeId
                );
        }

        #endregion

        #endregion
    }
}
