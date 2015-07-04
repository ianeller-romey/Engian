using System;
using System.Collections.Generic;
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

        public Tuple<Area, IEnumerable<RoomState>> 
            LoadGame(Guid playerId)
        {
            Area area;
            IEnumerable<RoomState> roomStates;
            IEnumerable<ParagraphState> paragraphStates;
            IEnumerable<Noun> nouns;
            using (var entities = new GinTubEntities())
            {
                var areaResults = entities.LoadGame(playerId);
                area = TypeAdapter.Adapt<Area>(areaResults.Single());

                var roomStateResults = areaResults.GetNextResult<LoadRoomStatesForRoom_Result>();
                roomStates = roomStateResults.Select(x => TypeAdapter.Adapt<RoomState>(x)).ToList();

                var paragraphStateResults = roomStateResults.GetNextResult<LoadParagraphStatesForRoom_Result>();
                paragraphStates = paragraphStateResults.Select(x => TypeAdapter.Adapt<ParagraphState>(x)).ToList();

                var nounResults = paragraphStateResults.GetNextResult<LoadNounsForRoom_Result>();
                nouns = nounResults.Select(x => TypeAdapter.Adapt<Noun>(x)).ToList();

                foreach (var roomState in roomStates)
                {
                    roomState.ParagraphStates = paragraphStates.Where(x => x.RoomState == roomState.Id).ToArray();
                    foreach (var paragraphState in paragraphStates)
                        paragraphState.Nouns = nouns.Where(x => x.ParagraphState == paragraphState.Id).ToArray();
                }
            }
            return new Tuple<Area, IEnumerable<RoomState>>(area, roomStates);
        }

        public IEnumerable<RoomState> LoadRoom(Guid playerId)
        {
            return null;
        }
    }
}
