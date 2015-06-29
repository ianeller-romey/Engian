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

            //Mapper.CreateMap<Repository.RoomDataInitialLoad.NounData, NounData>();
            //Mapper.CreateMap<Repository.RoomDataInitialLoad.ParagraphData, ParagraphData>();
            //Mapper.CreateMap<Repository.RoomDataInitialLoad.RoomData, RoomData>();
        }

        public RoomData RoomDataInitialLoad(Guid playerId, int area, int x, int y, int z, DateTime currentTime)
        {
            //return Mapper.Engine.Map<RoomData>(
            //    _repository.GetRoomDataInitialLoad(playerId, area, x, y, z, currentTime));
            return null;
        }
    }
}
