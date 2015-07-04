using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using GinTubRepoEntities = GinTub.Repository.Entities;


namespace GinTub.Repository.Interface
{
    public interface IGinTubRepository
    {
        Guid? PlayerLogin(string userName, string domainName, string domain, string password);

        Tuple<GinTubRepoEntities.Area, IEnumerable<GinTubRepoEntities.RoomState>> LoadGame(Guid playerId);
        IEnumerable<GinTubRepoEntities.RoomState> LoadRoom(Guid playerId);
    }
}
