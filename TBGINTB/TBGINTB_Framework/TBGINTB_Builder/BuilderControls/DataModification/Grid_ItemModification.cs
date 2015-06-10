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
    public class Grid_ItemModification : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_ItemData m_grid_item;

        #endregion


        #region MEMBER PROPERTIES

        public int? ItemId { get { return m_grid_item.ItemId; } }
        public string ItemName { get { return m_grid_item.ItemName; } }
        public string ItemDescription { get { return m_grid_item.ItemDescription; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ItemModification(int? itemId, string itemName, string itemDescription)
        {
            CreateControls(itemId, itemName, itemDescription);
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_item.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_item.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? itemId, string itemName, string itemDescription)
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            Button button_modifyItem = new Button() { Content = "Modify Item" };
            button_modifyItem.Click += Button_ModifyItem_Click;
            this.SetGridRowColumn(button_modifyItem, 0, 0);

            m_grid_item = new Grid_ItemData(itemId, itemName, itemDescription, false);
            this.SetGridRowColumn(m_grid_item, 1, 0);
            m_grid_item.SetActiveAndRegisterForGinTubEvents();
        }

        private void Button_ModifyItem_Click(object sender, RoutedEventArgs e)
        {
            Window_ItemData window =
                new Window_ItemData(m_grid_item.ItemId, m_grid_item.ItemName, m_grid_item.ItemDescription);
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.ModifyItem(window.ItemId.Value, window.ItemName, window.ItemDescription);
        }

        #endregion

        #endregion
    }
}
