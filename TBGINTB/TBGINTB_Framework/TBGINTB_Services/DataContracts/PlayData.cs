using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;


namespace GinTub.Services.DataContracts
{

    [DataContract]
    public class NounData
    {
        [DataMember] 
        public int Id { get; set; }
        [DataMember] 
        public string Text { get; set; }
    }

    [DataContract]
    public class ParagraphStateData
    {
        [DataMember] 
        public int Id { get; set; }
        [DataMember] 
        public string Text { get; set; }
        [DataMember] 
        public int Order { get; set; }
        [DataMember] 
        public IEnumerable<NounData> Nouns { get; set; }
    }

    [DataContract]
    public class RoomStateData
    {
        [DataMember]
        public int Id { get; set; }
        [DataMember]
        public int State { get; set; }
        [DataMember]
        public DateTime Time { get; set; }
        [DataMember]
        public string Location { get; set; }
        [DataMember]
        public int Room { get; set; }
        [DataMember]
        public IEnumerable<ParagraphStateData> ParagraphStates { get; set; }
    }

    [DataContract]
    public class AreaData
    {
        [DataMember]
        public int Id { get; set; }
        [DataMember]
        public string Name { get; set; }
    }

    [DataContract]
    public class PlayData
    {
        [DataMember]
        public AreaData Area { get; set; }
        [DataMember]
        public IEnumerable<RoomStateData> RoomStates { get; set; }
    }
}