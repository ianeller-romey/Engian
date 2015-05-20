﻿using System;
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
    public class Grid_RoomsOnFloor : Grid
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
        public int RoomsMaxX { get; private set; }
        public int RoomsMaxY { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_RoomsOnFloor(int areaId, int maxX, int maxY, int z)
        {
            AreaId = areaId;
            RoomsMaxX = maxX;
            RoomsMaxY = maxY;
            CreateControls(RoomsMaxX, RoomsMaxY);

            GinTubBuilderManager.RoomAdded += GinTubBuilderManager_RoomAdded;

            SetFloor(z);
        }

        public void SetFloor(int z)
        {
            RoomsZ = z;
            foreach (var button in Children.OfType<Button_RoomOnFloor>())
            {
                button.HasNoRoom();
                button.SetFloor(RoomsZ);
            }
            GinTubBuilderManager.LoadAllRoomsInAreaOnFloor(AreaId, RoomsZ);
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int maxX, int maxY)
        {
            for (int x = 0, xx = maxX + c_defaultRowsColsModifier; x < xx; ++x)
                AddColumn(false);
            for (int y = 0, yy = maxY + c_defaultRowsColsModifier; y < yy; ++y)
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

            Button_RoomOnFloor button = new Button_RoomOnFloor(AreaId, column, row, RoomsZ);
            IW.SetGridRowColumn(this, button, row, column);
        }

        private void AddRoom(int x, int y)
        {
            for(int xPlusModifier = x + c_defaultRowsColsModifier; RoomsMaxX + c_defaultRowsColsModifier < xPlusModifier; RoomsMaxX = RoomsMaxX + 1)
                AddColumn(true);
            for (int yPlusModifier = y + c_defaultRowsColsModifier; RoomsMaxY + c_defaultRowsColsModifier < yPlusModifier; RoomsMaxY = RoomsMaxY + 1)
                AddRow(true);
        }

        private void GinTubBuilderManager_RoomAdded(object sender, GinTubBuilderManager.RoomAddedEventArgs args)
        {
            if (args.Area == AreaId && args.Z == RoomsZ)
                AddRoom(args.X, args.Y);
        }

        #endregion

        #endregion
    }
}