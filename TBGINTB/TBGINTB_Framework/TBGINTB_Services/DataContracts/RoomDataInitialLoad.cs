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
    public class ParagraphData
    {
        [DataMember] 
        public int Id { get; set; }
        [DataMember] 
        public int State { get; set; }
        [DataMember] 
        public string Text { get; set; }
        [DataMember] 
        public IEnumerable<NounData> Nouns { get; set; }
    }

    [DataContract]
    public class RoomData
    {
        [DataMember] 
        public int Id { get; set; }
        [DataMember] 
        public int State { get; set; }
        [DataMember] 
        public int X { get; set; }
        [DataMember] 
        public int Y { get; set; }
        [DataMember] 
        public int Z { get; set; }
        [DataMember] 
        public int Area { get; set; }
        [DataMember] 
        public string Location { get; set; }
        [DataMember] 
        public DateTime CurrentTime { get; set; }
        [DataMember] 
        public DateTime? RefreshTime { get; set; }
        [DataMember] 
        public IEnumerable<ParagraphData> Paragraphs { get; set; }
    }
}