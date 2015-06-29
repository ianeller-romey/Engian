using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using FastMapper;

using GinTub.Repository.Entities.Database;
using GinTub.Repository.Entities.LoadRoom;


namespace GinTub.Repository
{
    public class GinTubRepository : Interface.IGinTubRepository
    {
        public IEnumerable<RoomState> LoadNewGame(Guid playerId)
        {
            IEnumerable<RoomState> roomStates;
            IEnumerable<ParagraphState> paragraphStates;
            IEnumerable<Noun> nouns;
            using (GinTubEntities entities = new GinTubEntities())
            {
                var roomStateResults = entities.LoadNewGame(playerId);
                roomStates = roomStateResults.Select(x => TypeAdapter.Adapt<RoomState>(x)).ToList();

                var paragraphStateResults = roomStateResults.GetNextResult<LoadParagraphStatesForRoom_Result>();
                paragraphStates = paragraphStateResults.Select(x => TypeAdapter.Adapt<ParagraphState>(x)).ToList();

                var nounResults = paragraphStateResults.GetNextResult<LoadNounsForRoom_Result>();
                nouns = nounResults.Select(x => TypeAdapter.Adapt<Noun>(x)).ToList();

                foreach (var roomState in roomStates)
                {
                    TypeAdapter.Adapt<List<ParagraphState>, ParagraphState[]>
                    (
                        paragraphStates.Where(x => x.RoomState == roomState.Id).ToList(),
                        roomState.ParagraphStates
                    );
                    foreach (var paragraphState in paragraphStates)
                    {
                        TypeAdapter.Adapt<List<Noun>, Noun[]>
                        (
                            nouns.Where(x => x.ParagraphState == paragraphState.Id).ToList(),
                            paragraphState.Nouns
                        );
                    }
                }
            }
            return null;
        }

        public IEnumerable<RoomState> LoadRoom(Guid playerId)
        {
            return null;
        }
    }
}
