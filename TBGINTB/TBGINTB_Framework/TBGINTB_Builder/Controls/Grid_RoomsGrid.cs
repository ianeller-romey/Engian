using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

using TBGINTB_Builder.Lib;

using IANWork;


namespace TBGINTB_Builder.Controls
{
    public class Grid_RoomsGrid : Grid
    {
        #region MEMBER FIELDS

        private const int c_defaultRowsCols = 10;
        private const int c_defaultRowsColsModifier = c_defaultRowsCols / 2;
        private const double c_defaultRowColWH = 40.0;
        private static readonly GridLength s_defaultRowColGridLength = new GridLength(c_defaultRowColWH, GridUnitType.Pixel);

        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public int RoomsZ { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomsGrid(int areaId, int maxX, int minX, int maxY, int minY, int z)
        {
            AreaId = areaId;
            RoomsZ = z;

            CreateControls(maxX, minX, maxY, minY);

            GinTubBuilderManager.RoomAdded += GinTubBuilderManager_RoomAdded;
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int maxX, int minX, int maxY, int minY)
        {
            for (int x = minX - c_defaultRowsColsModifier, xx = maxX + c_defaultRowsColsModifier; x < xx; ++x)
                AddColumn(false);
            for (int y = minY - c_defaultRowsColsModifier, yy = maxY + c_defaultRowsColsModifier; y < yy; ++y)
                AddRow(true);
        }

        private void AddRow(bool addCell)
        {
            RowDefinitions.Add(new RowDefinition() { Height = s_defaultRowColGridLength });
            if (addCell)
            {
                for (int i = 0; i < ColumnDefinitions.Count; ++i)
                    AddCell(RowDefinitions.Count - 1, i);
            }
        }

        private void AddColumn(bool addCell)
        {
            ColumnDefinitions.Add(new ColumnDefinition() { Width = s_defaultRowColGridLength });
            if (addCell)
            {
                for (int i = 0; i < RowDefinitions.Count; ++i)
                    AddCell(i, ColumnDefinitions.Count - 1);
            }
        }

        private void AddCell(int row, int column)
        {
            Rectangle rect = new Rectangle() { Stroke = Brushes.Black, StrokeThickness = 1.0 };
            IW.SetGridRowColumn(this, rect, row, column);

            Button_CreateRoom button = new Button_CreateRoom(AreaId, column, row, RoomsZ);
            IW.SetGridRowColumn(this, button, row, column);
        }

        private void AddRoom(int id, string name, int x, int y)
        {
            Button_CreateRoom button_createRoom = Children.OfType<Button_CreateRoom>().SingleOrDefault(b => b.AreaId == AreaId && b.RoomX == x && b.RoomY == y && b.RoomZ == RoomsZ);
            if (button_createRoom != null)
                Children.Remove(button_createRoom);

            Button_UpdateRoom button_updateRoom = new Button_UpdateRoom(id, name, x, y, RoomsZ);
            IW.SetGridRowColumn(this, button_updateRoom, y, x);
        }

        private void GinTubBuilderManager_RoomAdded(object sender, GinTubBuilderManager.RoomAddedEventArgs args)
        {
            if (args.Area == AreaId && args.Z == RoomsZ)
                AddRoom(args.Id, args.Name, args.X, args.Y);
        }

        #endregion

        #endregion
    }
}
