using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.Core.Objects;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

using AutoMapper;

using TBGINTB_Builder.Lib.Exceptions;
using TBGINTB_Builder.Lib.Repository;

using Db = TBGINTB_Builder.Lib.Model.DbModel;
using Xml = TBGINTB_Builder.Lib.Model.XmlModel;


namespace TBGINTB_Builder.Lib
{
    public static partial class GinTubBuilderManager
    {

        #region MEMBER METHODS

        #region Public Functionality

        public static void ExportToXml(string fileName)
        {
            Xml.GinTub ginTub = ExportGinTubToXml();
            ginTub.ExportDate = DateTime.Now;

            XmlSerializer serializer = new XmlSerializer(typeof(Xml.GinTub));
            using(TextWriter textWriter = new StreamWriter(fileName))
            {
                serializer.Serialize(textWriter, ginTub);
            }
        }

        public static void ImportFromXml(string fileName, string backupFile)
        {
            if (backupFile.Any(c => Path.GetInvalidPathChars().Contains(c)) || 
                backupFile.Any(c => char.IsWhiteSpace(c)) ||
                backupFile.Contains('\''))
                throw new ArgumentException("Incorrectly formatted or potentially dangerous file name provided.", "backupFile");
            Xml.GinTub ginTub;

            XmlSerializer serializer = new XmlSerializer(typeof(Xml.GinTub));
            using(TextReader textReader = new StreamReader(fileName))
            {
                ginTub = serializer.Deserialize(textReader) as Xml.GinTub;
            }
            if (ginTub == null)
                throw new GinTubXmlException("Deserialize");

            try
            {
                m_entities.Database.ExecuteSqlCommand
                (
                    TransactionalBehavior.DoNotEnsureTransaction, 
                    "EXEC [dev].[dev_ClearDatabase] @backupfile = N'" + backupFile + "'"
                );
            }
            catch (Exception e)
            {
                throw new GinTubDatabaseException("dev_ClearDatabase", e);
            }

            ImportGinTubFromXml(ginTub);
        }

        #endregion


        #region Private Functionality

        private static void InitializeDbModelToXmlModelMap()
        {
            Mapper.CreateMap<Db.Area, Xml.Area>();

            Mapper.CreateMap<Db.Location, Xml.Location>();

            Mapper.CreateMap<Db.Room, Xml.Room>();

            Mapper.CreateMap<Db.RoomState, Xml.RoomState>();

            Mapper.CreateMap<Db.Paragraph, Xml.Paragraph>();

            Mapper.CreateMap<Db.ParagraphState, Xml.ParagraphState>();

            Mapper.CreateMap<Db.Noun, Xml.Noun>();

            Mapper.CreateMap<Db.VerbType, Xml.VerbType>();

            Mapper.CreateMap<Db.Verb, Xml.Verb>();

            Mapper.CreateMap<Db.Action, Xml.Action>();

            Mapper.CreateMap<Db.ResultType, Xml.ResultType>();

            Mapper.CreateMap<Db.ResultTypeJSONProperty, Xml.ResultTypeJSONProperty>();

            Mapper.CreateMap<Db.Result, Xml.Result>();

            Mapper.CreateMap<Db.ActionResult, Xml.ActionResult>();

            Mapper.CreateMap<Db.Item, Xml.Item>();

            Mapper.CreateMap<Db.Event, Xml.Event>();

            Mapper.CreateMap<Db.Character, Xml.Character>();

            Mapper.CreateMap<Db.ItemActionRequirement, Xml.ItemActionRequirement>();

            Mapper.CreateMap<Db.EventActionRequirement, Xml.EventActionRequirement>();

            Mapper.CreateMap<Db.CharacterActionRequirement, Xml.CharacterActionRequirement>();

            Mapper.CreateMap<Db.Message, Xml.Message>();

            Mapper.CreateMap<Db.MessageChoice, Xml.MessageChoice>();

            Mapper.CreateMap<Db.MessageChoiceResult, Xml.MessageChoiceResult>();
        }

        #region Export

        private static Xml.GinTub ExportGinTubToXml()
        {
            Xml.Item[] items = SelectAllItems().Select(i => Mapper.Map<Xml.Item>(i)).ToArray();

            Xml.Event[] events = SelectAllEvents().Select(e => Mapper.Map<Xml.Event>(e)).ToArray();

            Xml.Character[] characters = SelectAllCharacters().Select(c => Mapper.Map<Xml.Character>(c)).ToArray();

            Xml.ResultType[] resultTypes = SelectAllResultTypes().Select(rt => Mapper.Map<Xml.ResultType>(rt)).ToArray();
            for (int i = 0; i < resultTypes.Length; ++i)
                ExportResultTypeToXml(ref resultTypes[i]);

            Xml.VerbType[] verbTypes = SelectAllVerbTypes().Select(rt => Mapper.Map<Xml.VerbType>(rt)).ToArray();
            for (int i = 0; i < verbTypes.Length; ++i)
                ExportVerbTypeToXml(ref verbTypes[i]);

            Xml.Location[] locations = SelectAllLocations().Select(l => Mapper.Map<Xml.Location>(l)).ToArray();

            Xml.Message[] messages = SelectAllMessages().Select(a => Mapper.Map<Xml.Message>(a)).ToArray();
            for (int i = 0; i < messages.Length; ++i)
                ExportMessageToXml(ref messages[i]);

            Xml.Area[] areas = SelectAllAreas().Select(a => Mapper.Map<Xml.Area>(a)).ToArray();
            for (int i = 0; i < areas.Length; ++i)
                ExportAreaToXml(ref areas[i]);

            Xml.GinTub ginTub = new Xml.GinTub();
            ginTub.Items = items;
            ginTub.Events = events;
            ginTub.Characters = characters;
            ginTub.ResultTypes = resultTypes;
            ginTub.VerbTypes = verbTypes;
            ginTub.Locations = locations;
            ginTub.Messages = messages;
            ginTub.Areas = areas;
            return ginTub;
        }

        private static void ExportResultTypeToXml(ref Xml.ResultType resultType)
        {
            resultType.ResultTypeJSONProperties = SelectAllResultTypeJSONPropertiesForResultType(resultType.Id).
                Select(rtjp => Mapper.Map<Xml.ResultTypeJSONProperty>(rtjp)).ToArray();
            resultType.Results = SelectAllResultsForResultType(resultType.Id).
                Select(r => Mapper.Map<Xml.Result>(r)).ToArray();
        }

        private static void ExportVerbTypeToXml(ref Xml.VerbType verbType)
        {
            verbType.Verbs = SelectAllVerbsForVerbType(verbType.Id).
                Select(v => Mapper.Map<Xml.Verb>(v)).ToArray();
        }

        private static void ExportMessageToXml(ref Xml.Message message)
        {
            message.MessageChoices = SelectAllMessageChoicesForMessage(message.Id).
                Select(mc => Mapper.Map<Xml.MessageChoice>(mc)).ToArray();
            for (int i = 0; i < message.MessageChoices.Length; ++i)
                ExportMessageChoiceToXml(ref message.MessageChoices[i]);
        }

        private static void ExportMessageChoiceToXml(ref Xml.MessageChoice messageChoice)
        {
            messageChoice.MessageChoiceResults = SelectAllMessageChoiceResultsForMessageChoice(messageChoice.Id).
                Select(r => Mapper.Map<Xml.MessageChoiceResult>(r)).ToArray();
        }

        private static void ExportAreaToXml(ref Xml.Area area)
        {
            area.Rooms = SelectAllRoomsInArea(area.Id).
                Select(r => Mapper.Map<Xml.Room>(r)).ToArray();
            for (int i = 0; i < area.Rooms.Length; ++i)
                ExportRoomToXml(ref area.Rooms[i]);
        }

        private static void ExportRoomToXml(ref Xml.Room room)
        {
            room.Paragraphs = SelectAllParagraphsForRoomAndRoomState(room.Id, null).
                Select(p => Mapper.Map<Xml.Paragraph>(p)).ToArray();
            for (int i = 0; i < room.Paragraphs.Length; ++i)
                ExportParagraphToXml(ref room.Paragraphs[i]);
            room.RoomStates = SelectAllRoomStatesForRoom(room.Id).
                Select(rs => Mapper.Map<Xml.RoomState>(rs)).ToArray();
            foreach(var roomState in room.RoomStates)
            {
                roomState.Paragraphs = SelectAllParagraphsForRoomAndRoomState(room.Id, roomState.Id).
                    Select(p => Mapper.Map<Xml.Paragraph>(p)).ToArray();
                for (int i = 0; i < roomState.Paragraphs.Length; ++i)
                    ExportParagraphToXml(ref roomState.Paragraphs[i]);
            }
        }

        private static void ExportParagraphToXml(ref Xml.Paragraph paragraph)
        {
            paragraph.ParagraphStates = SelectAllParagraphStatesForParagraph(paragraph.Id).
                Select(ps => Mapper.Map<Xml.ParagraphState>(ps)).ToArray();
            for (int i = 0; i < paragraph.ParagraphStates.Length; ++i)
                ExportParagraphStateToXml(ref paragraph.ParagraphStates[i]);
        }

        private static void ExportParagraphStateToXml(ref Xml.ParagraphState paragraphState)
        {
            paragraphState.Nouns = SelectAllNounsForParagraphState(paragraphState.Id).
                Select(n => Mapper.Map<Xml.Noun>(n)).ToArray();
            for (int i = 0; i < paragraphState.Nouns.Length; ++i)
                ExportNounToXml(ref paragraphState.Nouns[i]);
        }

        private static void ExportNounToXml(ref Xml.Noun noun)
        {
            noun.Actions = SelectAllActionsForNoun(noun.Id).
                Select(a => Mapper.Map<Xml.Action>(a)).ToArray();
            for(int i = 0; i < noun.Actions.Length; ++i)
                ExportActionToXml(ref noun.Actions[i]);
        }

        private static void ExportActionToXml(ref Xml.Action action)
        {
            action.ActionResults = SelectAllActionResultsForAction(action.Id).
                Select(a => Mapper.Map<Xml.ActionResult>(a)).ToArray();
            action.ItemActionRequirements = SelectAllItemActionRequirementsForAction(action.Id).
                Select(i => Mapper.Map<Xml.ItemActionRequirement>(i)).ToArray();
            action.EventActionRequirements = SelectAllEventActionRequirementsForAction(action.Id).
                Select(e => Mapper.Map<Xml.EventActionRequirement>(e)).ToArray();
            action.CharacterActionRequirements = SelectAllCharacterActionRequirementsForAction(action.Id).
                Select(c => Mapper.Map<Xml.CharacterActionRequirement>(c)).ToArray();
        }

        #endregion


        #region Import

        private static void ImportGinTubFromXml(Xml.GinTub ginTub)
        {
            foreach(var item in ginTub.Items)
                InsertItem(item.Name, item.Description);
            foreach (var evnt in ginTub.Events)
                InsertEvent(evnt.Name, evnt.Description);
            foreach (var character in ginTub.Characters)
                InsertCharacter(character.Name, character.Description);
            foreach (var resultType in ginTub.ResultTypes)
                ImportResultTypeFromXml(resultType);
            foreach (var verbType in ginTub.VerbTypes)
                ImportVerbTypeFromXml(verbType);
            foreach (var location in ginTub.Locations)
                InsertLocation(location.Name, location.LocationFile);
            foreach (var message in ginTub.Messages)
                ImportMessageFromXml(message);
            foreach (var area in ginTub.Areas)
                ImportAreaFromXml(area);
        }

        private static void ImportResultTypeFromXml(Xml.ResultType resultType)
        {
            int resultTypeId = InsertResultType(resultType.Name);
            foreach (var resultTypeJSONProperty in resultType.ResultTypeJSONProperties)
                InsertResultTypeJSONProperty(resultTypeJSONProperty.JSONProperty, resultTypeId);
            foreach (var result in resultType.Results)
                InsertResult(result.Name, result.JSONData, resultTypeId);
        }

        private static void ImportVerbTypeFromXml(Xml.VerbType verbType)
        {
            int verbTypeId = InsertVerbType(verbType.Name);
            foreach (var verb in verbType.Verbs)
                InsertVerb(verb.Name, verbTypeId);
        }

        private static void ImportMessageFromXml(Xml.Message message)
        {
            int messageId = InsertMessage(message.Name, message.Text);
            foreach (var messageChoice in message.MessageChoices)
                ImportMessageChoiceFromXml(messageChoice, messageId);
        }

        private static void ImportMessageChoiceFromXml(Xml.MessageChoice messageChoice, int messageId)
        {
            int messageChoiceId = InsertMessageChoice(messageChoice.Name, messageChoice.Text, messageId);
            foreach (var messageChoiceResult in messageChoice.MessageChoiceResults)
                InsertMessageChoiceResult(messageChoiceResult.Result, messageChoiceId);
        }

        private static void ImportAreaFromXml(Xml.Area area)
        {
            int areaId = InsertArea(area.Name);
            foreach (var room in area.Rooms)
                ImportRoomFromXml(room, areaId);
        }

        private static void ImportRoomFromXml(Xml.Room room, int areaId)
        {
            int roomId = InsertRoom(room.Name, room.X, room.Y, room.Z, areaId);
            foreach (var paragraph in room.Paragraphs)
                ImportParagraphFromXml(paragraph, roomId, null);
            foreach(var roomState in room.RoomStates)
            {
                int roomStateId = InsertRoomState(roomState.Time, roomState.Location, roomId);
                foreach (var paragraph in roomState.Paragraphs)
                    ImportParagraphFromXml(paragraph, roomId, roomStateId);
            }
        }

        private static void ImportParagraphFromXml(Xml.Paragraph paragraph, int roomId, int? roomStateId)
        {
            int paragraphId = InsertParagraph(paragraph.Order, roomId, roomStateId);
            foreach (var paragraphState in paragraph.ParagraphStates)
                ImportParagraphStateFromXml(paragraphState, paragraphId);
        }

        private static void ImportParagraphStateFromXml(Xml.ParagraphState paragraphState, int paragraphId)
        {
            int paragraphStateId = InsertParagraphState(paragraphState.Text, paragraphId);
            foreach (var noun in paragraphState.Nouns)
                ImportNounFromXml(noun, paragraphStateId);
        }

        private static void ImportNounFromXml(Xml.Noun noun, int paragraphStateId)
        {
            int nounId = InsertNoun(noun.Text, paragraphStateId);
            foreach (var action in noun.Actions)
                ImportActionFromXml(action, nounId);
        }

        private static void ImportActionFromXml(Xml.Action action, int nounId)
        {
            int actionId = InsertAction(action.VerbType, nounId);
            foreach (var actionResult in action.ActionResults)
                InsertActionResult(actionResult.Result, actionId);
            foreach (var requirement in action.ItemActionRequirements)
                InsertItemActionRequirement(requirement.Item, actionId);
            foreach (var requirement in action.EventActionRequirements)
                InsertEventActionRequirement(requirement.Event, actionId);
            foreach (var requirement in action.EventActionRequirements)
                InsertEventActionRequirement(requirement.Event, actionId);
        }

        #endregion

        #endregion

        #endregion

    }
}
