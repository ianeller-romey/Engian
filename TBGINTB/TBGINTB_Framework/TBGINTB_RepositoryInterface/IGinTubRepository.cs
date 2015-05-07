using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GinTub.Repository.Interface
{
    public interface IGinTubRepository
    {
        RoomDataInitialLoad.RoomData GetRoomDataInitialLoad(Guid playerId, int area, int x, int y, int z, DateTime currentTime);
    }
}
