using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib.Model;


namespace TBGINTB_Builder
{
    public class TabItem_Area : TabItem
    {
        #region MEMBER FIELDS

        private Area m_area;

        private List<Control_RoomsGrid> m_grid_rooms;

        private static RowDefinition s_grid_rooms_rowDefinition = new RowDefinition() { Height = new GridLength(50.0) };
        private static ColumnDefinition s_grid_rooms_columnDefinition = new ColumnDefinition() { Width = new GridLength(50.0) };

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_Area(Area area)
        {
            m_area = area;
            Content = CreateControls();
        }

        #endregion


        #region Private Functionality

        private FrameworkElement CreateControls()
        {
            m_grid_rooms = new List<Control_RoomsGrid>();
            return new Grid();
        }

        private Grid BuildAGrid(int minX, int maxX, int minY, int maxY)
        {
            Grid grid = new Grid() { ShowGridLines = true };
            for (int i = minX; i < maxX; ++i)
                grid.ColumnDefinitions.Add(s_grid_rooms_columnDefinition);
            for (int i = minY; i < maxY; ++i)
                grid.RowDefinitions.Add(s_grid_rooms_rowDefinition);
            return grid;
        }

        #endregion

        #endregion
    }
}
