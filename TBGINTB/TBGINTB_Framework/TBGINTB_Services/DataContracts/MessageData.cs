using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;


namespace GinTub.Services.DataContracts
{

    [DataContract]
    public class MessageChoiceData
    {
        [DataMember] 
        public int Id { get; set; }
        [DataMember]
        public string Text { get; set; }
    }

    [DataContract]
    public class MessageData
    {
        [DataMember]
        public int Id { get; set; }
        [DataMember]
        public string Text { get; set; }
        [DataMember]
        public IEnumerable<MessageChoiceData> MessageChoices { get; set; }
    }

}