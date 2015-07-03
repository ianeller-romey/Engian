using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

using FastMapper;

using GinTub;
using GinTub.Services.DataContracts;


namespace GinTub.Services
{
    public class GinTubService : OperationContracts.IGinTubService
    {
        Repository.Interface.IGinTubRepository _repository;

        public GinTubService()
        {
            _repository = new Repository.GinTubRepository();
        }

        public AllData LoadNewGame(Guid playerId)
        {
            AllData data = new AllData();
            var result = _repository.LoadNewGame(playerId);
            data.Area = TypeAdapter.Adapt<AreaData>(result.Item1);
            data.RoomStates = result.Item2.Select(x => TypeAdapter.Adapt<RoomStateData>(x)).ToList();
            return data;
        }

        public AllData LoadRoom(Guid playerId, int area, int x, int y, int z)
        {
            AllData data = new AllData();
            var result = _repository.LoadRoom(playerId);
            return null;
        }
    }
}
