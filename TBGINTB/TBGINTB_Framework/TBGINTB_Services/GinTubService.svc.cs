using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
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

        public PlayerLogin PlayerLogin(string emailAddress, string password)
        {
            // I know, catching Exceptions is not "best practice" for data validation,
            // but this is an easy way to avoid Regex (for now)
            try
            {
                var m = new MailAddress(emailAddress);
            }
            catch (FormatException)
            {
                return null;
            }

            // If we've made it past the validation, it's safe to brute-force parse the email address
            string userName, domainName, domain;

            int atIndex = emailAddress.IndexOf('@');

            userName = emailAddress.Substring(0, atIndex);

            emailAddress = emailAddress.Remove(0, atIndex + 1);

            int periodIndex = emailAddress.LastIndexOf('.');

            domainName = emailAddress.Substring(0, periodIndex);

            emailAddress = emailAddress.Remove(0, periodIndex + 1);

            domain = emailAddress;

            Guid? playerId = _repository.PlayerLogin(userName, domainName, domain, password);
            return new PlayerLogin() { PlayerId = playerId };
        }

        public AllData LoadGame(Guid playerId)
        {
            AllData data = new AllData();
            var result = _repository.LoadGame(playerId);
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
