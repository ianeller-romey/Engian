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
    public class Window_ItemData : Window_AcceptCancel
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

        public Window_ItemData(int? itemId, string itemName, string itemDescription)
        {
            Title = "Item Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(itemId, itemName, itemDescription);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? itemId, string itemName, string itemDescription)
        {
            m_grid_item = new Grid_ItemData(itemId, itemName, itemDescription, true);
            return m_grid_item;
        }

        #endregion

        #endregion
    }
}
