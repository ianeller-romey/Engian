﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using GinTubRepoEntities = GinTub.Repository.Entities;


namespace GinTub.Repository.Interface
{
    public interface IGinTubRepository
    {
        IEnumerable<GinTubRepoEntities.LoadRoom.RoomState> LoadNewGame(Guid playerId);
        IEnumerable<GinTubRepoEntities.LoadRoom.RoomState> LoadRoom(Guid playerId);
    }
}
