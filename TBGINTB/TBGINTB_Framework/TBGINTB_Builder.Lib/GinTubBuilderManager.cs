using System;
using System.Collections.Generic;
using System.Data.Entity.Core.Objects;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AutoMapper;

using TBGINTB_Builder.Lib.Exceptions;
using TBGINTB_Builder.Lib.Model.DbModel;
using TBGINTB_Builder.Lib.Repository;

using Db = TBGINTB_Builder.Lib.Model.DbModel;


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
        private static void OnLocationAdded(Location location)
        {
            if (LocationAdded != null)
                LocationAdded(typeof(GinTubBuilderManager), new LocationAddedEventArgs(location.Id, location.Name, location.LocationFile));
        }


        public class LocationModifiedEventArgs : LocationEventArgs
        {
            public LocationModifiedEventArgs(int id, string name, string locationFile) : base(id, name, locationFile) { }
        }
        public delegate void LocationModifiedEventHandler(object sender, LocationModifiedEventArgs args);
        public static event LocationModifiedEventHandler LocationModified;
        private static void OnLocationModified(Location location)
        {
            if (LocationModified != null)
                LocationModified(typeof(GinTubBuilderManager), new LocationModifiedEventArgs(location.Id, location.Name, location.LocationFile));
        }


        public class LocationGetEventArgs : LocationEventArgs
        {
            public LocationGetEventArgs(int id, string name, string locationFile) : base(id, name, locationFile) { }
        }
        public delegate void LocationGetEventHandler(object sender, LocationGetEventArgs args);
        public static event LocationGetEventHandler LocationGet;
        private static void OnLocationGet(Location location)
        {
            if (LocationGet != null)
                LocationGet(typeof(GinTubBuilderManager), new LocationGetEventArgs(location.Id, location.Name, location.LocationFile));
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


        #region ParagraphStates

        public class ParagraphStateEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Text { get; set; }
            public int State { get; set; }
            public int Paragraph { get; set; }
            public ParagraphStateEventArgs(int id, string text, int state, int paragraphState)
            {
                Id = id;
                Text = text;
                State = state;
                Paragraph = paragraphState;
            }
        }


        public class ParagraphStateAddedEventArgs : ParagraphStateEventArgs
        {
            public ParagraphStateAddedEventArgs(int id, string text, int state, int paragraphState) :
                base(id, text, state, paragraphState) { }
        }
        public delegate void ParagraphStateAddedEventHandler(object sender, ParagraphStateAddedEventArgs args);
        public static event ParagraphStateAddedEventHandler ParagraphStateAdded;
        private static void OnParagraphStateAdded(ParagraphState paragraphState)
        {
            if (ParagraphStateAdded != null)
                ParagraphStateAdded(typeof(GinTubBuilderManager),
                    new ParagraphStateAddedEventArgs(paragraphState.Id, paragraphState.Text, paragraphState.State, paragraphState.Paragraph));
        }


        public class ParagraphStateModifiedEventArgs : ParagraphStateEventArgs
        {
            public ParagraphStateModifiedEventArgs(int id, string text, int state, int paragraphState) :
                base(id, text, state, paragraphState) { }
        }
        public delegate void ParagraphStateModifiedEventHandler(object sender, ParagraphStateModifiedEventArgs args);
        public static event ParagraphStateModifiedEventHandler ParagraphStateModified;
        private static void OnParagraphStateModified(ParagraphState paragraphState)
        {
            if (ParagraphStateModified != null)
                ParagraphStateModified(typeof(GinTubBuilderManager),
                    new ParagraphStateModifiedEventArgs(paragraphState.Id, paragraphState.Text, paragraphState.State, paragraphState.Paragraph));
        }


        public class ParagraphStateGetEventArgs : ParagraphStateEventArgs
        {
            public ParagraphStateGetEventArgs(int id, string text, int state, int paragraphState) :
                base(id, text, state, paragraphState) { }
        }
        public delegate void ParagraphStateGetEventHandler(object sender, ParagraphStateGetEventArgs args);
        public static event ParagraphStateGetEventHandler ParagraphStateGet;
        private static void OnParagraphStateGet(ParagraphState paragraphState)
        {
            if (ParagraphStateGet != null)
                ParagraphStateGet(typeof(GinTubBuilderManager),
                    new ParagraphStateGetEventArgs(paragraphState.Id, paragraphState.Text, paragraphState.State, paragraphState.Paragraph));
        }

        #endregion


        #region Nouns

        public class NounEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Text { get; set; }
            public int ParagraphState { get; set; }
            public NounEventArgs(int id, string text, int paragraphState)
            {
                Id = id;
                Text = text;
                ParagraphState = paragraphState;
            }
        }


        public class NounAddedEventArgs : NounEventArgs
        {
            public NounAddedEventArgs(int id, string text, int paragraphState) :
                base(id, text, paragraphState) { }
        }
        public delegate void NounAddedEventHandler(object sender, NounAddedEventArgs args);
        public static event NounAddedEventHandler NounAdded;
        private static void OnNounAdded(Noun noun)
        {
            if (NounAdded != null)
                NounAdded(typeof(GinTubBuilderManager),
                    new NounAddedEventArgs(noun.Id, noun.Text, noun.ParagraphState));
        }


        public class NounModifiedEventArgs : NounEventArgs
        {
            public NounModifiedEventArgs(int id, string text, int paragraphState) :
                base(id, text, paragraphState) { }
        }
        public delegate void NounModifiedEventHandler(object sender, NounModifiedEventArgs args);
        public static event NounModifiedEventHandler NounModified;
        private static void OnNounModified(Noun noun)
        {
            if (NounModified != null)
                NounModified(typeof(GinTubBuilderManager),
                    new NounModifiedEventArgs(noun.Id, noun.Text, noun.ParagraphState));
        }


        public class NounGetEventArgs : NounEventArgs
        {
            public NounGetEventArgs(int id, string text, int paragraphState) :
                base(id, text, paragraphState) { }
        }
        public delegate void NounGetEventHandler(object sender, NounGetEventArgs args);
        public static event NounGetEventHandler NounGet;
        private static void OnNounGet(Noun noun)
        {
            if (NounGet != null)
                NounGet(typeof(GinTubBuilderManager),
                    new NounGetEventArgs(noun.Id, noun.Text, noun.ParagraphState));
        }

        #endregion


        #region VerbTypes

        public class VerbTypeEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public VerbTypeEventArgs(int id, string name)
            {
                Id = id;
                Name = name;
            }
        }


        public class VerbTypeAddedEventArgs : VerbTypeEventArgs
        {
            public VerbTypeAddedEventArgs(int id, string name) : base(id, name) { }
        }
        public delegate void VerbTypeAddedEventHandler(object sender, VerbTypeAddedEventArgs args);
        public static event VerbTypeAddedEventHandler VerbTypeAdded;
        private static void OnVerbTypeAdded(VerbType verbType)
        {
            if (VerbTypeAdded != null)
                VerbTypeAdded(typeof(GinTubBuilderManager), new VerbTypeAddedEventArgs(verbType.Id, verbType.Name));
        }


        public class VerbTypeModifiedEventArgs : VerbTypeEventArgs
        {
            public VerbTypeModifiedEventArgs(int id, string name) : base(id, name) { }
        }
        public delegate void VerbTypeModifiedEventHandler(object sender, VerbTypeModifiedEventArgs args);
        public static event VerbTypeModifiedEventHandler VerbTypeModified;
        private static void OnVerbTypeModified(VerbType verbType)
        {
            if (VerbTypeModified != null)
                VerbTypeModified(typeof(GinTubBuilderManager), new VerbTypeModifiedEventArgs(verbType.Id, verbType.Name));
        }


        public class VerbTypeGetEventArgs : VerbTypeEventArgs
        {
            public VerbTypeGetEventArgs(int id, string name) : base(id, name) { }
        }
        public delegate void VerbTypeGetEventHandler(object sender, VerbTypeGetEventArgs args);
        public static event VerbTypeGetEventHandler VerbTypeGet;
        private static void OnVerbTypeGet(VerbType verbType)
        {
            if (VerbTypeGet != null)
                VerbTypeGet(typeof(GinTubBuilderManager), new VerbTypeGetEventArgs(verbType.Id, verbType.Name));
        }

        #endregion


        #region Verbs

        public class VerbEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public int VerbType { get; set; }
            public VerbEventArgs(int id, string name, int verbType)
            {
                Id = id;
                Name = name;
                VerbType = verbType;
            }
        }


        public class VerbAddedEventArgs : VerbEventArgs
        {
            public VerbAddedEventArgs(int id, string name, int verbType) : base(id, name, verbType) { }
        }
        public delegate void VerbAddedEventHandler(object sender, VerbAddedEventArgs args);
        public static event VerbAddedEventHandler VerbAdded;
        private static void OnVerbAdded(Verb verb)
        {
            if (VerbAdded != null)
                VerbAdded(typeof(GinTubBuilderManager), new VerbAddedEventArgs(verb.Id, verb.Name, verb.VerbType));
        }


        public class VerbModifiedEventArgs : VerbEventArgs
        {
            public VerbModifiedEventArgs(int id, string name, int verbType) : base(id, name, verbType) { }
        }
        public delegate void VerbModifiedEventHandler(object sender, VerbModifiedEventArgs args);
        public static event VerbModifiedEventHandler VerbModified;
        private static void OnVerbModified(Verb verb)
        {
            if (VerbModified != null)
                VerbModified(typeof(GinTubBuilderManager), new VerbModifiedEventArgs(verb.Id, verb.Name, verb.VerbType));
        }


        public class VerbGetEventArgs : VerbEventArgs
        {
            public VerbGetEventArgs(int id, string name, int verbType) : base(id, name, verbType) { }
        }
        public delegate void VerbGetEventHandler(object sender, VerbGetEventArgs args);
        public static event VerbGetEventHandler VerbGet;
        private static void OnVerbGet(Verb verb)
        {
            if (VerbGet != null)
                VerbGet(typeof(GinTubBuilderManager), new VerbGetEventArgs(verb.Id, verb.Name, verb.VerbType));
        }

        #endregion


        #region Actions

        public class ActionEventArgs : EventArgs
        {
            public int Id { get; set; }
            public int VerbType { get; set; }
            public int Noun { get; set; }
            public ActionEventArgs(int id, int verbType, int noun)
            {
                Id = id;
                VerbType = verbType;
                Noun = noun;
            }
        }


        public class ActionAddedEventArgs : ActionEventArgs
        {
            public ActionAddedEventArgs(int id, int verbType, int noun) : base(id, verbType, noun) { }
        }
        public delegate void ActionAddedEventHandler(object sender, ActionAddedEventArgs args);
        public static event ActionAddedEventHandler ActionAdded;
        private static void OnActionAdded(Db.Action action)
        {
            if (ActionAdded != null)
                ActionAdded(typeof(GinTubBuilderManager), new ActionAddedEventArgs(action.Id, action.VerbType, action.Noun));
        }


        public class ActionModifiedEventArgs : ActionEventArgs
        {
            public ActionModifiedEventArgs(int id, int verbType, int noun) : base(id, verbType, noun) { }
        }
        public delegate void ActionModifiedEventHandler(object sender, ActionModifiedEventArgs args);
        public static event ActionModifiedEventHandler ActionModified;
        private static void OnActionModified(Db.Action action)
        {
            if (ActionModified != null)
                ActionModified(typeof(GinTubBuilderManager), new ActionModifiedEventArgs(action.Id, action.VerbType, action.Noun));
        }


        public class ActionGetEventArgs : ActionEventArgs
        {
            public ActionGetEventArgs(int id, int verbType, int noun) : base(id, verbType, noun) { }
        }
        public delegate void ActionGetEventHandler(object sender, ActionGetEventArgs args);
        public static event ActionGetEventHandler ActionGet;
        private static void OnActionGet(Db.Action action)
        {
            if (ActionGet != null)
                ActionGet(typeof(GinTubBuilderManager), new ActionGetEventArgs(action.Id, action.VerbType, action.Noun));
        }

        #endregion


        #region ResultTypes

        public class ResultTypeEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public ResultTypeEventArgs(int id, string name)
            {
                Id = id;
                Name = name;
            }
        }


        public class ResultTypeAddedEventArgs : ResultTypeEventArgs
        {
            public ResultTypeAddedEventArgs(int id, string name) : base(id, name) { }
        }
        public delegate void ResultTypeAddedEventHandler(object sender, ResultTypeAddedEventArgs args);
        public static event ResultTypeAddedEventHandler ResultTypeAdded;
        private static void OnResultTypeAdded(ResultType resultType)
        {
            if (ResultTypeAdded != null)
                ResultTypeAdded(typeof(GinTubBuilderManager), new ResultTypeAddedEventArgs(resultType.Id, resultType.Name));
        }


        public class ResultTypeModifiedEventArgs : ResultTypeEventArgs
        {
            public ResultTypeModifiedEventArgs(int id, string name) : base(id, name) { }
        }
        public delegate void ResultTypeModifiedEventHandler(object sender, ResultTypeModifiedEventArgs args);
        public static event ResultTypeModifiedEventHandler ResultTypeModified;
        private static void OnResultTypeModified(ResultType resultType)
        {
            if (ResultTypeModified != null)
                ResultTypeModified(typeof(GinTubBuilderManager), new ResultTypeModifiedEventArgs(resultType.Id, resultType.Name));
        }


        public class ResultTypeGetEventArgs : ResultTypeEventArgs
        {
            public ResultTypeGetEventArgs(int id, string name) : base(id, name) { }
        }
        public delegate void ResultTypeGetEventHandler(object sender, ResultTypeGetEventArgs args);
        public static event ResultTypeGetEventHandler ResultTypeGet;
        private static void OnResultTypeGet(ResultType resultType)
        {
            if (ResultTypeGet != null)
                ResultTypeGet(typeof(GinTubBuilderManager), new ResultTypeGetEventArgs(resultType.Id, resultType.Name));
        }

        #endregion


        #region ResultTypeJSONFields

        public class ResultTypeJSONFieldEventArgs : EventArgs
        {
            public int Id { get; set; }
            public string JSONField { get; set; }
            public int ResultType { get; set; }
            public ResultTypeJSONFieldEventArgs(int id, string jsonField, int resultType)
            {
                Id = id;
                JSONField = jsonField;
                ResultType = resultType;
            }
        }


        public class ResultTypeJSONFieldAddedEventArgs : ResultTypeJSONFieldEventArgs
        {
            public ResultTypeJSONFieldAddedEventArgs(int id, string jsonField, int resultType) :
                base(id, jsonField, resultType) { }
        }
        public delegate void ResultTypeJSONFieldAddedEventHandler(object sender, ResultTypeJSONFieldAddedEventArgs args);
        public static event ResultTypeJSONFieldAddedEventHandler ResultTypeJSONFieldAdded;
        private static void OnResultTypeJSONFieldAdded(ResultTypeJSONField resultTypeJSONField)
        {
            if (ResultTypeJSONFieldAdded != null)
                ResultTypeJSONFieldAdded
                (
                    typeof(GinTubBuilderManager), 
                    new ResultTypeJSONFieldAddedEventArgs
                    (
                        resultTypeJSONField.Id, 
                        resultTypeJSONField.JSONField, 
                        resultTypeJSONField.ResultType
                    )
                );
        }


        public class ResultTypeJSONFieldModifiedEventArgs : ResultTypeJSONFieldEventArgs
        {
            public ResultTypeJSONFieldModifiedEventArgs(int id, string name, int ResultTypeJSONFieldType) : base(id, name, ResultTypeJSONFieldType) { }
        }
        public delegate void ResultTypeJSONFieldModifiedEventHandler(object sender, ResultTypeJSONFieldModifiedEventArgs args);
        public static event ResultTypeJSONFieldModifiedEventHandler ResultTypeJSONFieldModified;
        private static void OnResultTypeJSONFieldModified(ResultTypeJSONField resultTypeJSONField)
        {
            if (ResultTypeJSONFieldModified != null)
                ResultTypeJSONFieldModified
                (
                    typeof(GinTubBuilderManager),
                    new ResultTypeJSONFieldModifiedEventArgs
                    (
                        resultTypeJSONField.Id,
                        resultTypeJSONField.JSONField,
                        resultTypeJSONField.ResultType
                    )
                );
        }


        public class ResultTypeJSONFieldGetEventArgs : ResultTypeJSONFieldEventArgs
        {
            public ResultTypeJSONFieldGetEventArgs(int id, string name, int ResultTypeJSONFieldType) : base(id, name, ResultTypeJSONFieldType) { }
        }
        public delegate void ResultTypeJSONFieldGetEventHandler(object sender, ResultTypeJSONFieldGetEventArgs args);
        public static event ResultTypeJSONFieldGetEventHandler ResultTypeJSONFieldGet;
        private static void OnResultTypeJSONFieldGet(ResultTypeJSONField resultTypeJSONField)
        {
            if (ResultTypeJSONFieldGet != null)
                ResultTypeJSONFieldGet
                (
                    typeof(GinTubBuilderManager),
                    new ResultTypeJSONFieldGetEventArgs
                    (
                        resultTypeJSONField.Id,
                        resultTypeJSONField.JSONField,
                        resultTypeJSONField.ResultType
                    )
                );
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

            Mapper.CreateMap<dev_GetParagraphState_Result, ParagraphState>();
            Mapper.CreateMap<dev_GetAllParagraphStatesForParagraph_Result, ParagraphState>();

            Mapper.CreateMap<dev_GetNoun_Result, Noun>();
            Mapper.CreateMap<dev_GetAllNounsForParagraphState_Result, Noun>();

            Mapper.CreateMap<dev_GetVerbType_Result, VerbType>();
            Mapper.CreateMap<dev_GetAllVerbTypes_Result, VerbType>();

            Mapper.CreateMap<dev_GetVerb_Result, Verb>();
            Mapper.CreateMap<dev_GetAllVerbsForVerbType_Result, Verb>();

            Mapper.CreateMap<dev_GetAction_Result, Db.Action>();
            Mapper.CreateMap<dev_GetAllActionsForNoun_Result, Db.Action>();

            Mapper.CreateMap<dev_GetResultType_Result, ResultType>();
            Mapper.CreateMap<dev_GetAllResultTypes_Result, ResultType>();

            Mapper.CreateMap<dev_GetResultTypeJSONField_Result, ResultTypeJSONField>();
            Mapper.CreateMap<dev_GetAllResultTypeJSONFieldsForResultType_Result, ResultTypeJSONField>();

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


        #region ParagraphStates

        public static void AddParagraphState(string paragraphStateText, int paragraphId)
        {
            int id = InsertParagraphState(paragraphStateText, paragraphId);
            ParagraphState paragraphState = SelectParagraphState(id);
            OnParagraphStateAdded(paragraphState);
        }

        public static void ModifyParagraphState(int paragraphStateId, string paragraphStateText, int paragraphStateState, int paragraphId)
        {
            UpdateParagraphState(paragraphStateId, paragraphStateText, paragraphStateState, paragraphId);
            ParagraphState paragraphState = SelectParagraphState(paragraphStateId);
            OnParagraphStateModified(paragraphState);
        }

        public static void GetParagraphState(int paragraphStateId)
        {
            ParagraphState paragraphState = SelectParagraphState(paragraphStateId);
            OnParagraphStateGet(paragraphState);
        }

        public static void LoadAllParagraphStatesForParagraph(int paragraphId)
        {
            List<ParagraphState> paragraphStates = SelectAllParagraphStatesForParagraph(paragraphId);
            foreach (var paragraphState in paragraphStates)
                OnParagraphStateAdded(paragraphState);
        }

        public static void GetAllParagraphStatesForParagraph(int paragraphId)
        {
            List<ParagraphState> paragraphStates = SelectAllParagraphStatesForParagraph(paragraphId);
            foreach (var paragraphState in paragraphStates)
                OnParagraphStateGet(paragraphState);
        }

        public static void LoadParagraphStateNounPossibilities(int paragraphStateId)
        {
            ParagraphState paragraphState = SelectParagraphState(paragraphStateId);
            OnParagraphStateAdded(paragraphState);
        }

        #endregion


        #region Nouns

        public static void AddNoun(string nounText, int paragraphStateId)
        {
            int id = InsertNoun(nounText, paragraphStateId);
            Noun noun = SelectNoun(id);
            OnNounAdded(noun);
        }

        public static void ModifyNoun(int nounId, string nounText, int paragraphStateId)
        {
            UpdateNoun(nounId, nounText, paragraphStateId);
            Noun noun = SelectNoun(nounId);
            OnNounModified(noun);
        }

        public static void GetNoun(int nounId)
        {
            Noun noun = SelectNoun(nounId);
            OnNounGet(noun);
        }

        public static void LoadAllNounsForParagraphState(int paragraphStateId)
        {
            List<Noun> nouns = SelectAllNounsForParagraphState(paragraphStateId);
            foreach (var noun in nouns)
                OnNounAdded(noun);
        }

        public static void GetAllNounsForParagraph(int paragraphStateId)
        {
            List<Noun> nouns = SelectAllNounsForParagraphState(paragraphStateId);
            foreach (var noun in nouns)
                OnNounGet(noun);
        }

        #endregion


        #region VerbTypes

        public static void AddVerbType(string verbTypeName)
        {
            int id = InsertVerbType(verbTypeName);
            VerbType verbType = SelectVerbType(id);
            OnVerbTypeAdded(verbType);
        }

        public static void ModifyVerbType(int verbTypeId, string verbTypeName)
        {
            UpdateVerbType(verbTypeId, verbTypeName);
            VerbType verbType = SelectVerbType(verbTypeId);
            OnVerbTypeModified(verbType);
        }

        public static void GetVerbType(int verbTypeId)
        {
            VerbType verbType = SelectVerbType(verbTypeId);
            OnVerbTypeGet(verbType);
        }

        public static void LoadAllVerbTypes()
        {
            List<VerbType> verbTypes = SelectAllVerbTypes();
            foreach (var verbType in verbTypes)
                OnVerbTypeAdded(verbType);
        }

        public static void GetAllVerbTypes()
        {
            List<VerbType> verbTypes = SelectAllVerbTypes();
            foreach (var verbType in verbTypes)
                OnVerbTypeGet(verbType);
        }

        #endregion


        #region Verbs

        public static void AddVerb(string verbName, int verbTypeId)
        {
            int id = InsertVerb(verbName, verbTypeId);
            Verb verb = SelectVerb(id);
            OnVerbAdded(verb);
        }

        public static void ModifyVerb(int verbId, string verbName, int verbTypeId)
        {
            UpdateVerb(verbId, verbName, verbTypeId);
            Verb verb = SelectVerb(verbId);
            OnVerbModified(verb);
        }

        public static void GetVerb(int verbId)
        {
            Verb verb = SelectVerb(verbId);
            OnVerbGet(verb);
        }

        public static void LoadAllVerbsForVerbType(int verbTypeId)
        {
            List<Verb> verbs = SelectAllVerbsForVerbType(verbTypeId);
            foreach (var verb in verbs)
                OnVerbAdded(verb);
        }

        public static void GetAllVerbsForVerbType(int verbTypeId)
        {
            List<Verb> verbs = SelectAllVerbsForVerbType(verbTypeId);
            foreach (var verb in verbs)
                OnVerbGet(verb);
        }

        #endregion


        #region Actions

        public static void AddAction(int actionVerbType, int actionNoun)
        {
            int id = InsertAction(actionVerbType, actionNoun);
            Db.Action action = SelectAction(id);
            OnActionAdded(action);
        }

        public static void ModifyAction(int actionId, int actionVerbType, int actionNoun)
        {
            UpdateAction(actionId, actionVerbType, actionNoun);
            Db.Action action = SelectAction(actionId);
            OnActionModified(action);
        }

        public static void GetAction(int actionId)
        {
            Db.Action action = SelectAction(actionId);
            OnActionGet(action);
        }

        public static void LoadAllActionsForNoun(int nounId)
        {
            List<Db.Action> actions = SelectAllActionsForNoun(nounId);
            foreach (var action in actions)
                OnActionAdded(action);
        }

        public static void GetAllActionsForNoun(int nounId)
        {
            List<Db.Action> actions = SelectAllActionsForNoun(nounId);
            foreach (var action in actions)
                OnActionGet(action);
        }

        #endregion


        #region ResultTypes

        public static void AddResultType(string resultTypeName)
        {
            int id = InsertResultType(resultTypeName);
            ResultType resultType = SelectResultType(id);
            OnResultTypeAdded(resultType);
        }

        public static void ModifyResultType(int resultTypeId, string resultTypeName)
        {
            UpdateResultType(resultTypeId, resultTypeName);
            ResultType resultType = SelectResultType(resultTypeId);
            OnResultTypeModified(resultType);
        }

        public static void GetResultType(int resultTypeId)
        {
            ResultType resultType = SelectResultType(resultTypeId);
            OnResultTypeGet(resultType);
        }

        public static void LoadAllResultTypes()
        {
            List<ResultType> resultTypes = SelectAllResultTypes();
            foreach (var resultType in resultTypes)
                OnResultTypeAdded(resultType);
        }

        public static void GetAllResultTypes()
        {
            List<ResultType> resultTypes = SelectAllResultTypes();
            foreach (var resultType in resultTypes)
                OnResultTypeGet(resultType);
        }

        #endregion


        #region ResultTypeJSONFields

        public static void AddResultTypeJSONField(string resultTypeJSONFieldJSONField, int resultTypeJSONFieldResultTypeId)
        {
            int id = InsertResultTypeJSONField(resultTypeJSONFieldJSONField, resultTypeJSONFieldResultTypeId);
            ResultTypeJSONField resultTypeJSONField = SelectResultTypeJSONField(id);
            OnResultTypeJSONFieldAdded(resultTypeJSONField);
        }

        public static void ModifyResultTypeJSONField(int resultTypeJSONFieldId, string resultTypeJSONFieldJSONField, int resultTypeJSONFieldResultTypeId)
        {
            UpdateResultTypeJSONField(resultTypeJSONFieldId, resultTypeJSONFieldJSONField, resultTypeJSONFieldResultTypeId);
            ResultTypeJSONField resultTypeJSONField = SelectResultTypeJSONField(resultTypeJSONFieldId);
            OnResultTypeJSONFieldModified(resultTypeJSONField);
        }

        public static void GetResultTypeJSONField(int resultTypeJSONFieldId)
        {
            ResultTypeJSONField resultTypeJSONField = SelectResultTypeJSONField(resultTypeJSONFieldId);
            OnResultTypeJSONFieldGet(resultTypeJSONField);
        }

        public static void LoadAllResultTypeJSONFieldsForResultType(int resultTypeId)
        {
            List<ResultTypeJSONField> resultTypeJSONFields = SelectAllResultTypeJSONFieldsForResultType(resultTypeId);
            foreach (var resultTypeJSONField in resultTypeJSONFields)
                OnResultTypeJSONFieldAdded(resultTypeJSONField);
        }

        public static void GetAllResultTypeJSONFieldsForResultType(int resultTypeId)
        {
            List<ResultTypeJSONField> resultTypeJSONFields = SelectAllResultTypeJSONFieldsForResultType(resultTypeId);
            foreach (var resultTypeJSONField in resultTypeJSONFields)
                OnResultTypeJSONFieldGet(resultTypeJSONField);
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


        #region ParagraphStates

        private static int InsertParagraphState(string text, int paragraph)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddParagraphState(text, paragraph);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddParagraphState", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddParagraphState", new Exception("No [Id] was returned after [ParagraphState] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateParagraphState(int id, string text, int state, int paragraph)
        {
            try
            {
                m_entities.dev_UpdateParagraphState(id, text, state, paragraph);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateParagraphState", e);
            }
        }

        private static ParagraphState SelectParagraphState(int id)
        {
            ObjectResult<dev_GetParagraphState_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetParagraphState(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetParagraphState", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetParagraphState", new Exception(string.Format("No [ParagraphStates] record found with [Id] = {0}.", id)));

            ParagraphState paragraphState = Mapper.Map<ParagraphState>(databaseResult.Single());
            return paragraphState;
        }

        private static List<ParagraphState> SelectAllParagraphStatesForParagraph(int paragraph)
        {
            ObjectResult<dev_GetAllParagraphStatesForParagraph_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllParagraphStatesForParagraph(paragraph);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllParagraphStatesForRoom", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllParagraphStatesForRoom", new Exception("No [ParagraphStates] records found."));

            List<ParagraphState> paragraphStates = databaseResult.Select(r => Mapper.Map<ParagraphState>(r)).ToList();
            return paragraphStates;
        }

        #endregion


        #region Nouns

        private static int InsertNoun(string text, int paragraphState)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddNoun(text, paragraphState);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddNoun", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddNoun", new Exception("No [Id] was returned after [Noun] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateNoun(int id, string text, int paragraphState)
        {
            try
            {
                m_entities.dev_UpdateNoun(id, text, paragraphState);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateNoun", e);
            }
        }

        private static Noun SelectNoun(int id)
        {
            ObjectResult<dev_GetNoun_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetNoun(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetNoun", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetNoun", new Exception(string.Format("No [Nouns] record found with [Id] = {0}.", id)));

            Noun noun = Mapper.Map<Noun>(databaseResult.Single());
            return noun;
        }

        private static List<Noun> SelectAllNounsForParagraphState(int paragraphState)
        {
            ObjectResult<dev_GetAllNounsForParagraphState_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllNounsForParagraphState(paragraphState);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllNounsForRoom", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllNounsForRoom", new Exception("No [Nouns] records found."));

            List<Noun> nouns = databaseResult.Select(r => Mapper.Map<Noun>(r)).ToList();
            return nouns;
        }

        #endregion


        #region VerbTypes

        private static int InsertVerbType(string name)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddVerbType(name);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddVerbType", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddVerbType", new Exception("No [Id] was returned after [VerbType] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateVerbType(int id, string name)
        {
            try
            {
                m_entities.dev_UpdateVerbType(id, name);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateVerbType", e);
            }
        }

        private static VerbType SelectVerbType(int id)
        {
            ObjectResult<dev_GetVerbType_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetVerbType(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetVerbType", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetVerbType", new Exception(string.Format("No [VerbTypes] record found with [Id] = {0}.", id)));

            VerbType verbType = Mapper.Map<VerbType>(databaseResult.Single());
            return verbType;
        }

        private static List<VerbType> SelectAllVerbTypes()
        {
            ObjectResult<dev_GetAllVerbTypes_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllVerbTypes();
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllVerbTypes", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllVerbTypes", new Exception("No [VerbTypes] records found."));

            List<VerbType> verbTypes = databaseResult.Select(r => Mapper.Map<VerbType>(r)).ToList();
            return verbTypes;
        }

        #endregion


        #region Verbs

        private static int InsertVerb(string name, int verbType)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddVerb(name, verbType);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddVerb", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddVerb", new Exception("No [Id] was returned after [Verb] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateVerb(int id, string name, int verbType)
        {
            try
            {
                m_entities.dev_UpdateVerb(id, name, verbType);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateVerb", e);
            }
        }

        private static Verb SelectVerb(int id)
        {
            ObjectResult<dev_GetVerb_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetVerb(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetVerb", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetVerb", new Exception(string.Format("No [Verbs] record found with [Id] = {0}.", id)));

            Verb verb = Mapper.Map<Verb>(databaseResult.Single());
            return verb;
        }

        private static List<Verb> SelectAllVerbsForVerbType(int verbType)
        {
            ObjectResult<dev_GetAllVerbsForVerbType_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllVerbsForVerbType(verbType);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllVerbs", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllVerbs", new Exception("No [Verbs] records found."));

            List<Verb> verbs = databaseResult.Select(r => Mapper.Map<Verb>(r)).ToList();
            return verbs;
        }

        #endregion


        #region Actions

        private static int InsertAction(int verbType, int noun)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddAction(verbType, noun);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddAction", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddAction", new Exception("No [Id] was returned after [Action] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateAction(int id, int verbType, int noun)
        {
            try
            {
                m_entities.dev_UpdateAction(id, verbType, noun);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateAction", e);
            }
        }

        private static Db.Action SelectAction(int id)
        {
            ObjectResult<dev_GetAction_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAction(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAction", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAction", new Exception(string.Format("No [Actions] record found with [Id] = {0}.", id)));

            Db.Action action = Mapper.Map<Db.Action>(databaseResult.Single());
            return action;
        }

        private static List<Db.Action> SelectAllActionsForNoun(int noun)
        {
            ObjectResult<dev_GetAllActionsForNoun_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllActionsForNoun(noun);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllActions", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllActions", new Exception("No [Actions] records found."));

            List<Db.Action> actions = databaseResult.Select(r => Mapper.Map<Db.Action>(r)).ToList();
            return actions;
        }

        #endregion


        #region ResultTypes

        private static int InsertResultType(string name)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddResultType(name);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddResultType", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddResultType", new Exception("No [Id] was returned after [ResultType] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateResultType(int id, string name)
        {
            try
            {
                m_entities.dev_UpdateResultType(id, name);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateResultType", e);
            }
        }

        private static ResultType SelectResultType(int id)
        {
            ObjectResult<dev_GetResultType_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetResultType(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetResultType", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetResultType", new Exception(string.Format("No [ResultTypes] record found with [Id] = {0}.", id)));

            ResultType resultType = Mapper.Map<ResultType>(databaseResult.Single());
            return resultType;
        }

        private static List<ResultType> SelectAllResultTypes()
        {
            ObjectResult<dev_GetAllResultTypes_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllResultTypes();
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllResultTypes", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllResultTypes", new Exception("No [ResultTypes] records found."));

            List<ResultType> resultTypes = databaseResult.Select(r => Mapper.Map<ResultType>(r)).ToList();
            return resultTypes;
        }

        #endregion


        #region ResultTypeJSONFields

        private static int InsertResultTypeJSONField(string jsonField, int resultType)
        {
            ObjectResult<decimal?> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_AddResultTypeJSONField(jsonField, resultType);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_AddResultTypeJSONField", e);
            }
            var result = databaseResult.FirstOrDefault();
            if (!result.HasValue)
                throw new GinTubDatabaseException("dev_AddResultTypeJSONField", new Exception("No [Id] was returned after [ResultTypeJSONField] INSERT."));

            return (int)result.Value;
        }

        private static void UpdateResultTypeJSONField(int id, string jsonField, int resultType)
        {
            try
            {
                m_entities.dev_UpdateResultTypeJSONField(id, jsonField, resultType);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_UpdateResultTypeJSONField", e);
            }
        }

        private static ResultTypeJSONField SelectResultTypeJSONField(int id)
        {
            ObjectResult<dev_GetResultTypeJSONField_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetResultTypeJSONField(id);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetResultTypeJSONField", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetResultTypeJSONField", new Exception(string.Format("No [ResultTypeJSONFields] record found with [Id] = {0}.", id)));

            ResultTypeJSONField resultTypeJSONField = Mapper.Map<ResultTypeJSONField>(databaseResult.Single());
            return resultTypeJSONField;
        }

        private static List<ResultTypeJSONField> SelectAllResultTypeJSONFieldsForResultType(int resultType)
        {
            ObjectResult<dev_GetAllResultTypeJSONFieldsForResultType_Result> databaseResult = null;
            try
            {
                databaseResult = m_entities.dev_GetAllResultTypeJSONFieldsForResultType(resultType);
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_GetAllResultTypeJSONFields", e);
            }
            if (databaseResult == null)
                throw new GinTubDatabaseException("dev_GetAllResultTypeJSONFields", new Exception("No [ResultTypeJSONFields] records found."));

            List<ResultTypeJSONField> resultTypeJSONFields = databaseResult.Select(r => Mapper.Map<ResultTypeJSONField>(r)).ToList();
            return resultTypeJSONFields;
        }

        #endregion

        #endregion

        #endregion

    }
}
