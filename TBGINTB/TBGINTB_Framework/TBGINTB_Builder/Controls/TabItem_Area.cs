using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib;

using IANWork;


namespace TBGINTB_Builder.Controls
{
    public class TabItem_Area : TabItem
    {
        #region MEMBER FIELDS

        private List<Grid_RoomsGrid> m_grid_rooms;
        private Grid m_grid_main;
        private Grid m_grid_sub;

        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public string AreaName { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_Area()
        {
            Content = CreateControls();
            AreaId = -1;
            SetAreaName("AREA");

            GinTubBuilderManager.AreaModified += GinTubBuilderManager_AreaModified;
            GinTubBuilderManager.AreaGet += GinTubBuilderManager_AreaGet;
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            m_grid_main = new Grid();
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });

            m_grid_sub = new Grid();
            m_grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(100.0, GridUnitType.Star) });
            m_grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            IW.SetGridRowColumn(m_grid_main, m_grid_sub, 1, 0);
            return m_grid_main;
        }

        private void GinTubBuilderManager_AreaModified(object sender, GinTubBuilderManager.AreaModifiedEventArgs args)
        {
            if (args.Id == AreaId)
                SetAreaName(args.Name);
        }

        private void GinTubBuilderManager_AreaGet(object sender, GinTubBuilderManager.AreaGetEventArgs args)
        {
            LoadArea(args.Id, args.Name, args.MaxX, args.MinX, args.MaxY, args.MinY, args.MinZ, args.MaxZ);
        }

        private void SetAreaName(string name)
        {
            AreaName = name;
            Header = AreaName;
        }

        private void LoadArea(int id, string name, int maxX, int minX, int maxY, int minY, int minZ, int maxZ)
        {
            AreaId = id;
            SetAreaName(name);

            m_grid_sub.Children.Clear();
            for (int z = minZ; z <= maxZ; ++z )
            {
                Grid_RoomsGrid grid = new Grid_RoomsGrid(AreaId, maxX, minX, maxY, minY, z);
                IW.SetGridRowColumn(m_grid_sub, grid, 0, 0);
            }

            GinTubBuilderManager.LoadAllRoomsInArea(AreaId);
        }

        #endregion

        #endregion
    }
}
