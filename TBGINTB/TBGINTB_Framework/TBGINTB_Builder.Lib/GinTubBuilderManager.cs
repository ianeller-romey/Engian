﻿using System;
using System.Collections.Generic;
using System.Data.Entity.Core.Objects;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AutoMapper;

using TBGINTB_Builder.Lib.Exceptions;
using TBGINTB_Builder.Lib.Model.DbModel;
using TBGINTB_Builder.Lib.Repository;


namespace TBGINTB_Builder.Lib
{
    public static class GinTubBuilderManager
    {
        #region MEMBER FIELDS

        private static GinTubEntities m_entities = null;

        #endregion


        #region MEMBER EVENTS

        #region Areas

        public class AreaEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public AreaEventArgs(int id, string name)
            {
                Id = id;
                Name = name;
            }
        }


        public class AreaAddedEventArgs : AreaEventArgs
        {
            public AreaAddedEventArgs(int id, string name) :  base(id, name) {}
        }
        public delegate void AreaAddedEventHandler(object sender, AreaAddedEventArgs args);
        public static event AreaAddedEventHandler AreaAdded;
        private static void OnAreaAdded(Area area)
        {
            if (AreaAdded != null)
                AreaAdded(typeof(GinTubBuilderManager), new AreaAddedEventArgs(area.Id, area.Name));
        }


        public class AreaModifiedEventArgs : AreaEventArgs
        {
            public AreaModifiedEventArgs(int id, string name) : base(id, name) {}
        }
        public delegate void AreaModifiedEventHandler(object sender, AreaModifiedEventArgs args);
        public static event AreaModifiedEventHandler AreaModified;
        private static void OnAreaModified(Area area)
        {
            if (AreaModified != null)
                AreaModified(typeof(GinTubBuilderManager), new AreaModifiedEventArgs(area.Id, area.Name));
        }


        public class AreaGetEventArgs : AreaEventArgs
        {
            public int MaxX { get; set; }
            public int MinX { get; set; }
            public int MaxY { get; set; }
            public int MinY { get; set; }
            public int MaxZ { get; set; }
            public int MinZ { get; set; }
            public int NumRooms { get; set; }
            public AreaGetEventArgs(int id, string name, int maxX, int minX, int maxY, int minY, int maxZ, int minZ, int numRooms) :
                base(id, name)
            {
                MaxX = maxX;
                MinX = minX;
                MaxY = maxY;
                MinY = minY;
                MaxZ = maxZ;
                MinZ = minZ;
                NumRooms = numRooms;
            }
        }
        public delegate void AreaGetEventHandler(object sender, AreaGetEventArgs args);
        public static event AreaGetEventHandler AreaGet;
        private static void OnAreaGet(Area area)
        {
            if (AreaGet != null)
                AreaGet(typeof(GinTubBuilderManager), new AreaGetEventArgs(area.Id, area.Name, area.MaxX, area.MinX, area.MaxY, area.MinY, area.MaxZ, area.MinZ, area.NumRooms));
        }

        #endregion


        #region Locations

        public class LocationEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public string LocationFile { get; set; }
            public LocationEventArgs(int id, string name, string locationFile)
            {
                Id = id;
                Name = name;
                LocationFile = locationFile;
            }
        }


        public class LocationAddedEventArgs : LocationEventArgs
        {
            public LocationAddedEventArgs(int id, string name, string locationFile) : base(id, name, locationFile) { }
        }
        public delegate void LocationAddedEventHandler(object sender, LocationAddedEventArgs args);
        public static event LocationAddedEventHandler LocationAdded;
        private static void OnLocationAdded(Location Location)
        {
            if (LocationAdded != null)
                LocationAdded(typeof(GinTubBuilderManager), new LocationAddedEventArgs(Location.Id, Location.Name, Location.LocationFile));
        }


        public class LocationModifiedEventArgs : LocationEventArgs
        {
            public LocationModifiedEventArgs(int id, string name, string locationFile) : base(id, name, locationFile) { }
        }
        public delegate void LocationModifiedEventHandler(object sender, LocationModifiedEventArgs args);
        public static event LocationModifiedEventHandler LocationModified;
        private static void OnLocationModified(Location Location)
        {
            if (LocationModified != null)
                LocationModified(typeof(GinTubBuilderManager), new LocationModifiedEventArgs(Location.Id, Location.Name, Location.LocationFile));
        }


        public class LocationGetEventArgs : LocationEventArgs
        {
            public LocationGetEventArgs(int id, string name, string locationFile) : base(id, name, locationFile) { }
        }
        public delegate void LocationGetEventHandler(object sender, LocationGetEventArgs args);
        public static event LocationGetEventHandler LocationGet;
        private static void OnLocationGet(Location Location)
        {
            if (LocationGet != null)
                LocationGet(typeof(GinTubBuilderManager), new LocationGetEventArgs(Location.Id, Location.Name, Location.LocationFile));
        }

        #endregion


        #region Rooms

        public class RoomEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public int X { get; set; }
            public int Y { get; set; }
            public int Z { get; set; }
            public int Area { get; set; }
            public RoomEventArgs(int id, string name, int x, int y, int z, int area)
            {
                Id = id;
                Name = name;
                X = x;
                Y = y;
                Z = z;
                Area = area;
            }
        }


        public class RoomAddedEventArgs : RoomEventArgs
        {
            public RoomAddedEventArgs(int id, string name, int x, int y, int z, int area) : base(id, name, x, y, z, area) {}
        }
        public delegate void RoomAddedEventHandler(object sender, RoomAddedEventArgs args);
        public static event RoomAddedEventHandler RoomAdded;
        private static void OnRoomAdded(Room room)
        {
            if (RoomAdded != null)
                RoomAdded(typeof(GinTubBuilderManager), new RoomAddedEventArgs(room.Id, room.Name, room.X, room.Y, room.Z, room.Area));
        }


        public class RoomModifiedEventArgs : RoomEventArgs
        {
            public RoomModifiedEventArgs(int id, string name, int x, int y, int z, int area) : base(id, name, x, y, z, area) {}
        }
        public delegate void RoomModifiedEventHandler(object sender, RoomModifiedEventArgs args);
        public static event RoomModifiedEventHandler RoomModified;
        private static void OnRoomModified(Room room)
        {
            if (RoomModified != null)
                RoomModified(typeof(GinTubBuilderManager), new RoomModifiedEventArgs(room.Id, room.Name, room.X, room.Y, room.Z, room.Area));
        }


        public class RoomGetEventArgs : RoomEventArgs
        {
            public RoomGetEventArgs(int id, string name, int x, int y, int z, int area) : base(id, name, x, y, z, area) {}
        }
        public delegate void RoomGetEventHandler(object sender, RoomGetEventArgs args);
        public static event RoomGetEventHandler RoomGet;
        private static void OnRoomGet(Room room)
        {
            if (RoomGet != null)
                RoomGet(typeof(GinTubBuilderManager), new RoomGetEventArgs(room.Id, room.Name, room.X, room.Y, room.Z, room.Area));
        }

        #endregion


        #region RoomStates

        public class RoomStateEventArgs : EventArgs
        {
            public int Id { get; set; }
            public int State { get; set; }
            public DateTime? Time { get; set; }
            public int Location { get; set; }
            public int Room { get; set; }
            public RoomStateEventArgs(int id, int state, DateTime time, int location, int room)
            {
                Id = id;
                State = state;
                Time = time;
                Location = location;
                Room = room;
            }
        }


        public class RoomStateAddedEventArgs : RoomStateEventArgs
        {
            public RoomStateAddedEventArgs(int id, int state, DateTime time, int location, int room) : 
                base(id, state, time, location, room) { }
        }
        public delegate void RoomStateAddedEventHandler(object sender, RoomStateAddedEventArgs args);
        public static event RoomStateAddedEventHandler RoomStateAdded;
        private static void OnRoomStateAdded(RoomState roomState)
        {
            if (RoomStateAdded != null)
                RoomStateAdded(typeof(GinTubBuilderManager),
                    new RoomStateAddedEventArgs(roomState.Id, roomState.State, roomState.Time, roomState.Location, roomState.Room));
        }


        public class RoomStateModifiedEventArgs : RoomStateEventArgs
        {
            public RoomStateModifiedEventArgs(int id, int state, DateTime time, int location, int room) :
                base(id, state, time, location, room) { }
        }
        public delegate void RoomStateModifiedEventHandler(object sender, RoomStateModifiedEventArgs args);
        public static event RoomStateModifiedEventHandler RoomStateModified;
        private static void OnRoomStateModified(RoomState roomState)
        {
            if (RoomStateModified != null)
                RoomStateModified(typeof(GinTubBuilderManager),
                    new RoomStateModifiedEventArgs(roomState.Id, roomState.State, roomState.Time, roomState.Location, roomState.Room));
        }


        public class RoomStateGetEventArgs : RoomStateEventArgs
        {
            public RoomStateGetEventArgs(int id, int state, DateTime time, int location, int room) :
                base(id, state, time, location, room) { }
        }
        public delegate void RoomStateGetEventHandler(object sender, RoomStateGetEventArgs args);
        public static event RoomStateGetEventHandler RoomStateGet;
        private static void OnRoomStateGet(RoomState roomState)
        {
            if (RoomStateGet != null)
                RoomStateGet(typeof(GinTubBuilderManager),
                    new RoomStateGetEventArgs(roomState.Id, roomState.State, roomState.Time, roomState.Location, roomState.Room));
        }

        #endregion


        #region Paragraphs

        public class ParagraphEventArgs : EventArgs
        {
            public int Id { get; set; }
            public int Order { get; set; }
            public int Room { get; set; }
            public int? RoomState { get; set; }
            public ParagraphEventArgs(int id, int order, int room, int? roomState)
            {
                Id = id;
                Order = order;
                Room = room;
                RoomState = roomState;
            }
        }


        public class ParagraphAddedEventArgs : ParagraphEventArgs
        {
            public ParagraphAddedEventArgs(int id, int order, int room, int? roomState) :
                base(id, order, room, roomState) { }
        }
        public delegate void ParagraphAddedEventHandler(object sender, ParagraphAddedEventArgs args);
        public static event ParagraphAddedEventHandler ParagraphAdded;
        private static void OnParagraphAdded(Paragraph paragraph)
        {
            if (ParagraphAdded != null)
                ParagraphAdded(typeof(GinTubBuilderManager),
                    new ParagraphAddedEventArgs(paragraph.Id, paragraph.Order, paragraph.Room, paragraph.RoomState));
        }


        public class ParagraphModifiedEventArgs : ParagraphEventArgs
        {
            public ParagraphModifiedEventArgs(int id, int order, int room, int? roomState) :
                base(id, order, room, roomState) { }
        }
        public delegate void ParagraphModifiedEventHandler(object sender, ParagraphModifiedEventArgs args);
        public static event ParagraphModifiedEventHandler ParagraphModified;
        private static void OnParagraphModified(Paragraph paragraph)
        {
            if (ParagraphModified != null)
                ParagraphModified(typeof(GinTubBuilderManager),
                    new ParagraphModifiedEventArgs(paragraph.Id, paragraph.Order, paragraph.Room, paragraph.RoomState));
        }


        public class ParagraphGetEventArgs : ParagraphEventArgs
        {
            public ParagraphGetEventArgs(int id, int order, int room, int? roomState) :
                base(id, order, room, roomState) { }
        }
        public delegate void ParagraphGetEventHandler(object sender, ParagraphGetEventArgs args);
        public static event ParagraphGetEventHandler ParagraphGet;
        private static void OnParagraphGet(Paragraph paragraph)
        {
            if (ParagraphGet != null)
                ParagraphGet(typeof(GinTubBuilderManager),
                    new ParagraphGetEventArgs(paragraph.Id, paragraph.Order, paragraph.Room, paragraph.RoomState));
        }

        #endregion


        #region ParagraphTextStates

        public class ParagraphTextStateEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Text { get; set; }
            public int State { get; set; }
            public int Paragraph { get; set; }
            public ParagraphTextStateEventArgs(int id, string text, int state, int paragraphTextState)
            {
                Id = id;
                Text = text;
                State = state;
                Paragraph = paragraphTextState;
            }
        }


        public class ParagraphTextStateAddedEventArgs : ParagraphTextStateEventArgs
        {
            public ParagraphTextStateAddedEventArgs(int id, string text, int state, int paragraphTextState) :
                base(id, text, state, paragraphTextState) { }
        }
        public delegate void ParagraphTextStateAddedEventHandler(object sender, ParagraphTextStateAddedEventArgs args);
        public static event ParagraphTextStateAddedEventHandler ParagraphTextStateAdded;
        private static void OnParagraphTextStateAdded(ParagraphTextState paragraphTextState)
        {
            if (ParagraphTextStateAdded != null)
                ParagraphTextStateAdded(typeof(GinTubBuilderManager),
                    new ParagraphTextStateAddedEventArgs(paragraphTextState.Id, paragraphTextState.Text, paragraphTextState.State, paragraphTextState.Paragraph));
        }


        public class ParagraphTextStateModifiedEventArgs : ParagraphTextStateEventArgs
        {
            public ParagraphTextStateModifiedEventArgs(int id, string text, int state, int paragraphTextState) :
                base(id, text, state, paragraphTextState) { }
        }
        public delegate void ParagraphTextStateModifiedEventHandler(object sender, ParagraphTextStateModifiedEventArgs args);
        public static event ParagraphTextStateModifiedEventHandler ParagraphTextStateModified;
        private static void OnParagraphTextStateModified(ParagraphTextState paragraphTextState)
        {
            if (ParagraphTextStateModified != null)
                ParagraphTextStateModified(typeof(GinTubBuilderManager),
                    new ParagraphTextStateModifiedEventArgs(paragraphTextState.Id, paragraphTextState.Text, paragraphTextState.State, paragraphTextState.Paragraph));
        }


        public class ParagraphTextStateGetEventArgs : ParagraphTextStateEventArgs
        {
            public ParagraphTextStateGetEventArgs(int id, string text, int state, int paragraphTextState) :
                base(id, text, state, paragraphTextState) { }
        }
        public delegate void ParagraphTextStateGetEventHandler(object sender, ParagraphTextStateGetEventArgs args);
        public static event ParagraphTextStateGetEventHandler ParagraphTextStateGet;
        private static void OnParagraphTextStateGet(ParagraphTextState paragraphTextState)
        {
            if (ParagraphTextStateGet != null)
                ParagraphTextStateGet(typeof(GinTubBuilderManager),
                    new ParagraphTextStateGetEventArgs(paragraphTextState.Id, paragraphTextState.Text, paragraphTextState.State, paragraphTextState.Paragraph));
        }

        #endregion

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public static void Initialize()
        {
            Mapper.CreateMap<dev_GetArea_Result, Area>();
            Mapper.CreateMap<dev_GetAllAreas_Result, Area>();

            Mapper.CreateMap<dev_GetLocation_Result, Location>();
            Mapper.CreateMap<dev_GetAllLocations_Result, Location>();

            Mapper.CreateMap<dev_GetRoom_Result, Room>();
            Mapper.CreateMap<dev_GetAllRoomsInArea_Result, Room>();
            Mapper.CreateMap<dev_GetAllRoomsInAreaOnFloor_Result, Room>();

            Mapper.CreateMap<dev_GetRoomState_Result, RoomState>();
            Mapper.CreateMap<dev_GetAllRoomStatesForRoom_Result, RoomState>();

            Mapper.CreateMap<dev_GetParagraph_Result, Paragraph>();
            Mapper.CreateMap<dev_GetAllParagraphsForRoomAndRoomState_Result, Paragraph>();

            Mapper.CreateMap<dev_GetParagraphTextState_Result, ParagraphTextState>();
            Mapper.CreateMap<dev_GetAllParagraphTextStatesForParagraph_Result, ParagraphTextState>();

            m_entities = new GinTubEntities();
            m_entities.Configuration.AutoDetectChangesEnabled = false;
        }

        #region Areas

        public static void AddArea(string areaName)
        {
            int id = InsertArea(areaName);
            Area area = SelectArea(id);
            OnAreaAdded(area);
        }

        public static void ModifyArea(int areaId, string areaName)
        {
            UpdateArea(areaId, areaName);
            Area area = SelectArea(areaId);
            OnAreaModified(area);
        }

        public static void GetArea(int areaId)
        {
            Area area = SelectArea(areaId);
            OnAreaGet(area);
        }

        public static void LoadAllAreas()
        {
            List<Area> areas = SelectAllAreas();
            foreach (var area in areas)
                OnAreaAdded(area);
        }

        #endregion


        #region Locations

        public static void AddLocation(string locationName, string locationFile)
        {
            int id = InsertLocation(locationName, locationFile);
            Location location = SelectLocation(id);
            OnLocationAdded(location);
        }

        public static void ModifyLocation(int locationId, string locationName, string locationFile)
        {
            UpdateLocation(locationId, locationName, locationFile);
            Location location = SelectLocation(locationId);
            OnLocationModified(location);
        }

        public static void GetLocation(int locationId)
        {
            Location location = SelectLocation(locationId);
            OnLocationGet(location);
        }

        public static void LoadAllLocations()
        {
            List<Location> locations = SelectAllLocations();
            foreach (var location in locations)
                OnLocationAdded(location);
        }

        public static void GetAllLocations()
        {
            List<Location> locations = SelectAllLocations();
            foreach (var location in locations)
                OnLocationGet(location);
        }

        #endregion


        #region Rooms

        public static void AddRoom(string roomName, int roomX, int roomY, int roomZ, int areaId)
        {
            int id = InsertRoom(roomName, roomX, roomY, roomZ, areaId);
            Room room = SelectRoom(id);
            OnRoomAdded(room);
        }

        public static void ModifyRoom(int roomId, string roomName, int roomX, int roomY, int roomZ, int areaId)
        {
            UpdateRoom(roomId, roomName, roomX, roomY, roomZ, areaId);
            Room room = SelectRoom(roomId);
            OnRoomModified(room);
        }

        public static void GetRoom(int roomId)
        {
            Room room = SelectRoom(roomId);
            OnRoomGet(room);
        }

        public static void LoadAllRoomsInArea(int areaId)
        {
            List<Room> rooms = SelectAllRoomsInArea(areaId);
            foreach (var room in rooms)
                OnRoomAdded(room);
        }

        public static void LoadAllRoomsInAreaOnFloor(int areaId, int z)
        {
            List<Room> rooms = SelectAllRoomsInAreaOnFloor(areaId, z);
            foreach (var room in rooms)
                OnRoomAdded(room);
        }

        public static void GetAllRoomsInArea(int areaId)
        {
            List<Room> rooms = SelectAllRoomsInArea(areaId);
            foreach (var room in rooms)
                OnRoomGet(room);
        }

        public static void GetAllRoomsInAreaOnFloor(int areaId, int z)
        {
            List<Room> rooms = SelectAllRoomsInAreaOnFloor(areaId, z);
            foreach (var room in rooms)
                OnRoomGet(room);
        }

        #endregion


        #region RoomStates

        public static void AddRoomState(DateTime? roomStateTime, int locationId, int roomId)
        {
            int id = InsertRoomState(roomStateTime, locationId, roomId);
            RoomState roomState = SelectRoomState(id);
            OnRoomStateAdded(roomState);
        }

        public static void ModifyRoomState(int roomStateId, int roomStateState, DateTime? roomStateTime, int locationId, int roomId)
        {
            UpdateRoomState(roomStateId, roomStateState, roomStateTime, locationId, roomId);
            RoomState roomState = SelectRoomState(roomStateId);
            OnRoomStateModified(roomState);
        }

        public static void GetRoomState(int roomStateId)
        {
            RoomState roomState = SelectRoomState(roomStateId);
            OnRoomStateGet(roomState);
        }

        public static void LoadAllRoomStatesForRoom(int roomId)
        {
            List<RoomState> roomStates = SelectAllRoomStatesForRoom(roomId);
            foreach (var roomState in roomStates)
                OnRoomStateAdded(roomState);
        }

        public static void GetAllRoomStatesForRoom(int roomId)
        {
            List<RoomState> roomStates = SelectAllRoomStatesForRoom(roomId);
            foreach (var roomState in roomStates)
                OnRoomStateGet(roomState);
        }

        #endregion


        #region Paragraphs

        public static void AddParagraph(int paragraphOrder, int roomId, int? roomStateId)
        {
            int id = InsertParagraph(paragraphOrder, roomId, roomStateId);
            Paragraph paragraph = SelectParagraph(id);
            OnParagraphAdded(paragraph);
        }

        public static void ModifyParagraph(int paragraphId, int paragraphOrder, int roomId, int? roomStateId)
        {
            UpdateParagraph(paragraphId, paragraphOrder, roomId, roomStateId);
            Paragraph paragraph = SelectParagraph(paragraphId);
            OnParagraphModified(paragraph);
        }

        public static void GetParagraph(int paragraphId)
        {
            Paragraph paragraph = SelectParagraph(paragraphId);
            OnParagraphGet(paragraph);
        }

        public static void LoadAllParagraphsForRoomAndRoomState(int roomId, int? roomStateId)
        {
            List<Paragraph> paragraphs = SelectAllParagraphsForRoomAndRoomState(roomId, roomStateId);
            foreach (var paragraph in paragraphs)
                OnParagraphAdded(paragraph);
        }

        public static void GetAllParagraphsForRoomAndRoomState(int roomId, int? roomStateId)
        {
            List<Paragraph> paragraphs = SelectAllParagraphsForRoomAndRoomState(roomId, roomStateId);
            foreach (var paragraph in paragraphs)
                OnParagraphGet(paragraph);
        }

        #endregion


        #region ParagraphTextStates

        public static void AddParagraphTextState(string paragraphTextStateText, int paragraphId)
        {
            int id = InsertParagraphTextState(paragraphTextStateText, paragraphId);
            ParagraphTextState paragraphTextState = SelectParagraphTextState(id);
            OnParagraphTextStateAdded(paragraphTextState);
        }

        public static void ModifyParagraphTextState(int paragraphTextStateId, string paragraphTextStateText, int paragraphTextStateState, int paragraphId)
        {
            UpdateParagraphTextState(paragraphTextStateId, paragraphTextStateText, paragraphTextStateState, paragraphId);
            ParagraphTextState paragraphTextState = SelectParagraphTextState(paragraphTextStateId);
            OnParagraphTextStateModified(paragraphTextState);
        }

        public static void GetParagraphTextState(int paragraphTextStateId)
        {
            ParagraphTextState paragraphTextState = SelectParagraphTextState(paragraphTextStateId);
            OnParagraphTextStateGet(paragraphTextState);
        }

        public static void LoadAllParagraphTextStatesForParagraph(int paragraph)
        {
            List<ParagraphTextState> paragraphTextStates = SelectAllParagraphTextStatesForParagraph(paragraph);
            foreach (var paragraphTextState in paragraphTextStates)
                OnParagraphTextStateAdded(paragraphTextState);
        }

        public static void GetAllParagraphTextStatesForParagraph(int paragraph)
        {
            List<ParagraphTextState> paragraphTextStates = SelectAllParagraphTextStatesForParagraph(paragraph);
            foreach (var paragraphTextState in paragraphTextStates)
                OnParagraphTextStateGet(paragraphTextState);
        }

        #endregion

        #endregion


        #region Private Functionality

        #region Areas

        private static int InsertArea(string name)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddArea(name);
            }
            catch(Exception e)
            {
                throw new GinTubDatabaseException("dev_AddArea", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddArea", new Exception("No [Id] was returned after [Area] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateArea(int id, string name)
        {
            try
            {
                m_entities.dev_UpdateArea(id, name);
            }
            catch(Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateArea", e);
            }
        }

        private static Area SelectArea(int id)
        {
            ObjectResult<dev_GetArea_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetArea(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetArea", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetArea", new Exception(string.Format("No [Areas] record found with [Id] = {0}.", id)));

            Area area = Mapper.Map<Area>(databaseResult.Single());
            return area;
        }

        private static List<Area> SelectAllAreas()
        {
            ObjectResult<dev_GetAllAreas_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllAreas();
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllAreas", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllAreas", new Exception("No [Areas] records found."));

            List<Area> areas = databaseResult.Select(r => Mapper.Map<Area>(r)).ToList();
            return areas;
        }

        #endregion


        #region Locations

        private static int InsertLocation(string name, string locationFile)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddLocation(name, locationFile);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddLocation", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddLocation", new Exception("No [Id] was returned after [Location] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateLocation(int id, string name, string locationFile)
        {
            try
            {
                m_entities.dev_UpdateLocation(id, name, locationFile);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateLocation", e);
            }
        }

        private static Location SelectLocation(int id)
        {
            ObjectResult<dev_GetLocation_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetLocation(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetLocation", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetLocation", new Exception(string.Format("No [Locations] record found with [Id] = {0}.", id)));

            Location location = Mapper.Map<Location>(databaseResult.Single());
            return location;
        }

        private static List<Location> SelectAllLocations()
        {
            ObjectResult<dev_GetAllLocations_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllLocations();
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllLocations", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllLocations", new Exception("No [Locations] records found."));

            List<Location> locations = databaseResult.Select(r => Mapper.Map<Location>(r)).ToList();
            return locations;
        }

        #endregion


        #region Rooms

        private static int InsertRoom(string name, int x, int y, int z, int area)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddRoom(name, x, y, z, area);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddRoom", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddRoom", new Exception("No [Id] was returned after [Room] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateRoom(int id, string name, int x, int y, int z, int area)
        {
            try
            {
                m_entities.dev_UpdateRoom(id, name, x, y, z, area);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateRoom", e);
            }
        }

        private static Room SelectRoom(int id)
        {
            ObjectResult<dev_GetRoom_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetRoom(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetRoom", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetRoom", new Exception(string.Format("No [Rooms] record found with [Id] = {0}.", id)));

            Room room = Mapper.Map<Room>(databaseResult.Single());
            return room;
        }

        private static List<Room> SelectAllRoomsInArea(int area)
        {
            ObjectResult<dev_GetAllRoomsInArea_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllRoomsInArea(area);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllRoomsInArea", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllRoomsInArea", new Exception("No [Rooms] records found."));

            List<Room> rooms = databaseResult.Select(r => Mapper.Map<Room>(r)).ToList();
            return rooms;
        }

        private static List<Room> SelectAllRoomsInAreaOnFloor(int area, int z)
        {
            ObjectResult<dev_GetAllRoomsInAreaOnFloor_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllRoomsInAreaOnFloor(area, z);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllRoomsInAreaOnFloor", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllRoomsInAreaOnFloor", new Exception("No [Rooms] records found."));

            List<Room> rooms = databaseResult.Select(r => Mapper.Map<Room>(r)).ToList();
            return rooms;
        }

        #endregion


        #region RoomStates

        private static int InsertRoomState(DateTime? time, int location, int room)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddRoomState(time, location, room);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddRoomState", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddRoomState", new Exception("No [Id] was returned after [RoomState] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateRoomState(int id, int state, DateTime? time, int location, int room)
        {
            try
            {
                m_entities.dev_UpdateRoomState(id, state, time, location, room);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateRoomState", e);
            }
        }

        private static RoomState SelectRoomState(int id)
        {
            ObjectResult<dev_GetRoomState_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetRoomState(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetRoomState", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetRoomState", new Exception(string.Format("No [RoomStates] record found with [Id] = {0}.", id)));

            RoomState roomState = Mapper.Map<RoomState>(databaseResult.Single());
            return roomState;
        }

        private static List<RoomState> SelectAllRoomStatesForRoom(int room)
        {
            ObjectResult<dev_GetAllRoomStatesForRoom_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllRoomStatesForRoom(room);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllRoomStatesForRoom", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllRoomStatesForRoom", new Exception("No [RoomStates] records found."));

            List<RoomState> roomStates = databaseResult.Select(r => Mapper.Map<RoomState>(r)).ToList();
            return roomStates;
        }

        #endregion


        #region Paragraphs

        private static int InsertParagraph(int order, int room, int? roomState)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddParagraph(order, room, roomState);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddParagraph", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddParagraph", new Exception("No [Id] was returned after [Paragraph] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateParagraph(int id, int order, int room, int? roomState)
        {
            try
            {
                m_entities.dev_UpdateParagraph(id, order, room, roomState);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateParagraph", e);
            }
        }

        private static Paragraph SelectParagraph(int id)
        {
            ObjectResult<dev_GetParagraph_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetParagraph(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetParagraph", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetParagraph", new Exception(string.Format("No [Paragraphs] record found with [Id] = {0}.", id)));

            Paragraph paragraph = Mapper.Map<Paragraph>(databaseResult.Single());
            return paragraph;
        }

        private static List<Paragraph> SelectAllParagraphsForRoomAndRoomState(int room, int? roomState)
        {
            ObjectResult<dev_GetAllParagraphsForRoomAndRoomState_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllParagraphsForRoomAndRoomState(room, roomState);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllParagraphsForRoom", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllParagraphsForRoom", new Exception("No [Paragraphs] records found."));

            List<Paragraph> paragraphs = databaseResult.Select(r => Mapper.Map<Paragraph>(r)).ToList();
            return paragraphs;
        }

        #endregion


        #region ParagraphTextStates

        private static int InsertParagraphTextState(string text, int paragraph)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddParagraphTextState(text, paragraph);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddParagraphTextState", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddParagraphTextState", new Exception("No [Id] was returned after [ParagraphTextState] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateParagraphTextState(int id, string text, int state, int paragraph)
        {
            try
            {
                m_entities.dev_UpdateParagraphTextState(id, text, state, paragraph);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateParagraphTextState", e);
            }
        }

        private static ParagraphTextState SelectParagraphTextState(int id)
        {
            ObjectResult<dev_GetParagraphTextState_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetParagraphTextState(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetParagraphTextState", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetParagraphTextState", new Exception(string.Format("No [ParagraphTextStates] record found with [Id] = {0}.", id)));

            ParagraphTextState paragraphTextState = Mapper.Map<ParagraphTextState>(databaseResult.Single());
            return paragraphTextState;
        }

        private static List<ParagraphTextState> SelectAllParagraphTextStatesForParagraph(int paragraph)
        {
            ObjectResult<dev_GetAllParagraphTextStatesForParagraph_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllParagraphTextStatesForParagraph(paragraph);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllParagraphTextStatesForRoom", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllParagraphTextStatesForRoom", new Exception("No [ParagraphTextStates] records found."));

            List<ParagraphTextState> paragraphTextStates = databaseResult.Select(r => Mapper.Map<ParagraphTextState>(r)).ToList();
            return paragraphTextStates;
        }

        #endregion

        #endregion

        #endregion

    }
}
