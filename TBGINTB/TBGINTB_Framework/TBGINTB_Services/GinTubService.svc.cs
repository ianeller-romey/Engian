﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Text.RegularExpressions;

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

        public VerbUseData LoadAllVerbTypes()
        {
            var result = _repository.LoadAllVerbTypes();
            return new VerbUseData()
                {
                    VerbTypes = result.Select(v => TypeAdapter.Adapt<VerbTypeData>(v)).ToList()
                };
        }

        public MessageData LoadNounsForParagraphState(int paragraphStateId)
        {
            var result = _repository.LoadNounsForParagraphState(paragraphStateId);
            return new MessageData()
            {
                Id = -1,
                Text =
                    string.Format
                    (
                        "Your eyes are caught by the {0}.",
                        result.Select(n => n.Text).Aggregate((x, y) => string.Format("{0}, {1}", x, y))
                    ),
                MessageChoices = new List<MessageChoiceData> { new MessageChoiceData() { Id = -1, Text = "..." } }
            };
        }

        public PlayData LoadGame(Guid playerId)
        {
            var result = _repository.LoadGame(playerId);
            return new PlayData()
                {
                    Area = TypeAdapter.Adapt<AreaData>(result.Item1),
                    RoomStates = result.Item2.Select(x => TypeAdapter.Adapt<RoomStateData>(x)).ToList(),
                };
        }
    }
}
