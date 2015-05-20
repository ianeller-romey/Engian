using System;
using System.Collections.Generic;
using System.Data.Entity.Core.Objects;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AutoMapper;

using TBGINTB_Builder.Lib.Exceptions;
using TBGINTB_Builder.Lib.Model;
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

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public static void Initialize()
        {
            Mapper.CreateMap<dev_GetArea_Result, Area>();
            Mapper.CreateMap<dev_GetAllAreas_Result, Area>();
            Mapper.CreateMap<dev_GetRoom_Result, Room>();
            Mapper.CreateMap<dev_GetAllRoomsInArea_Result, Room>();
            Mapper.CreateMap<dev_GetAllRoomsInAreaOnFloor_Result, Room>();
            m_entities = new GinTubEntities();
            m_entities.Configuration.AutoDetectChangesEnabled = false;
        }

        #region Areas

        public static void AddArea(string name)
        {
            int id = InsertArea(name);
            Area area = SelectArea(id);
            OnAreaAdded(area);
        }

        public static void ModifyArea(int id, string name)
        {
            UpdateArea(id, name);
            Area area = SelectArea(id);
            OnAreaModified(area);
        }

        public static void GetArea(int id)
        {
            Area area = SelectArea(id);
            OnAreaGet(area);
        }

        public static void LoadAllAreas()
        {
            List<Area> areas = SelectAllAreas();
            foreach (var area in areas)
                OnAreaAdded(area);
        }

        #endregion


        #region Rooms

        public static void AddRoom(string name, int x, int y, int z, int area)
        {
            int id = InsertRoom(name, x, y, z, area);
            Room room = SelectRoom(id);
            OnRoomAdded(room);
        }

        public static void ModifyRoom(int id, string name, int x, int y, int z, int area)
        {
            UpdateRoom(id, name, x, y, z, area);
            Room room = SelectRoom(id);
            OnRoomModified(room);
        }

        public static void GetRoom(int id)
        {
            Room room = SelectRoom(id);
            OnRoomGet(room);
        }

        public static void LoadAllRoomsInArea(int area)
        {
            List<Room> Rooms = SelectAllRoomsInArea(area);
            foreach (var room in Rooms)
                OnRoomAdded(room);
        }

        public static void LoadAllRoomsInAreaOnFloor(int area, int z)
        {
            List<Room> Rooms = SelectAllRoomsInAreaOnFloor(area, z);
            foreach (var room in Rooms)
                OnRoomAdded(room);
        }

        public static void GetAllRoomsInArea(int id)
        {
            List<Room> Rooms = SelectAllRoomsInArea(id);
            foreach (var room in Rooms)
                OnRoomGet(room);
        }

        public static void GetAllRoomsInAreaOnFloor(int area, int z)
        {
            List<Room> Rooms = SelectAllRoomsInAreaOnFloor(area, z);
            foreach (var room in Rooms)
                OnRoomGet(room);
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

        #endregion

        #endregion

    }
}
