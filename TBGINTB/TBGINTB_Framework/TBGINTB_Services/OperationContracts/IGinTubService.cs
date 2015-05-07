using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

using GinTub.Services;


namespace GinTub.Services.OperationContracts
{
    [ServiceContract]
    public interface IGinTubService
    {
        [OperationContract]
        DataContracts.RoomData GetRoomDataInitialLoad(Guid playerId, int area, int x, int y, int z, DateTime currentTime);
    }
}
