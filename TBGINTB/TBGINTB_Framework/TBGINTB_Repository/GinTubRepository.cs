using System;
using System.Collections.Generic;
using System.Data.Objects;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using FastMapper;

using GinTub.Repository.Entities;
using GinTub.Repository.Entities.Database;


namespace GinTub.Repository
{
    public class GinTubRepository : Interface.IGinTubRepository
    {
        #region MEMBER METHODS

        #region Public Functionality

        public Guid? PlayerLogin(string userName, string domainName, string domain, string password)
        {
            Guid? playerId = null;
            using (var entities = new GinTubEntities())
            {
                var results = entities.PlayerLogin(userName, domainName, domain, password);
                playerId = results.OfType<Guid?>().SingleOrDefault();
            }
            return playerId;
        }

        public IEnumerable<VerbType> LoadAllVerbTypes()
        {
            IEnumerable<VerbType> verbTypes;
            using (var entities = new GinTubEntities())
            {
                var verbTypeResults = entities.LoadAllVerbTypes();
                verbTypes = verbTypeResults.Select(v => TypeAdapter.Adapt<VerbType>(v)).ToList();
            }
            return verbTypes;
        }

        public IEnumerable<Noun> LoadNounsForParagraphState(int paragraphStateId)
        {
            IEnumerable<Noun> nouns;
            using(var entities = new GinTubEntities())
            {
                var nounResults = entities.LoadNounsForParagraphState(paragraphStateId);
                nouns = nounResults.Select(n => TypeAdapter.Adapt<Noun>(n)).ToList();
            }
            return nouns;
        }

        public Tuple<Area, IEnumerable<RoomState>> 
            LoadGame(Guid playerId)
        {
            Area area;
            IEnumerable<RoomState> roomStates;
            using (var entities = new GinTubEntities())
            {
                var areaResults = entities.LoadGame(playerId);
                area = TypeAdapter.Adapt<Area>(areaResults.Single());

                var roomStateResults = areaResults.GetNextResult<LoadRoomStatesForRoom_Result>();
                roomStates = RoomStateResultsFromDB(roomStateResults);
            }
            return new Tuple<Area, IEnumerable<RoomState>>(area, roomStates);
        }

        #endregion


        #region Private Functionality

        public IEnumerable<RoomState> RoomStateResultsFromDB(ObjectResult<LoadRoomStatesForRoom_Result> roomStateResults)
        {
            IEnumerable<RoomState> roomStates = roomStateResults.Select(x => TypeAdapter.Adapt<RoomState>(x)).ToList();

            var paragraphStateResults = roomStateResults.GetNextResult<LoadParagraphStatesForRoom_Result>();
            IEnumerable<ParagraphState>  paragraphStates = paragraphStateResults.Select(x => TypeAdapter.Adapt<ParagraphState>(x)).ToList();

            var nounResults = paragraphStateResults.GetNextResult<LoadNounsForRoom_Result>();
            IEnumerable<Noun> nouns = nounResults.Select(x => TypeAdapter.Adapt<Noun>(x)).ToList();

            foreach (var roomState in roomStates)
            {
                roomState.ParagraphStates = paragraphStates.Where(x => x.RoomState == roomState.Id).ToArray();
                foreach (var paragraphState in paragraphStates)
                    paragraphState.Nouns = nouns.Where(x => x.ParagraphState == paragraphState.Id).ToArray();
            }

            return roomStates;
        }

        #endregion

        #endregion
    }
}
