using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using GinTub.Repository.Entities;


namespace GinTub.Repository.Interface
{
    public interface IGinTubRepository
    {
        Guid? PlayerLogin(string userName, string domainName, string domain, string password);

        IEnumerable<VerbType> LoadAllVerbTypes();

        IEnumerable<Noun> LoadNounsForParagraphState(int paragraphStateId);

        Tuple<Area, IEnumerable<RoomState>> LoadGame(Guid playerId);
    }
}
