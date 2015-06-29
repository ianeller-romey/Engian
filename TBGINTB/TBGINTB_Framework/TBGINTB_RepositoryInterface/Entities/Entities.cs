using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GinTub.Repository.Entities
{
    public class Noun
    {
        public int Id { get; set; }
        public string Text { get; set; }
        public int ParagraphState { get; set; }
    }

    public class ParagraphState
    {
        public int Id { get; set; }
        public string Text { get; set; }
        public int Order { get; set; }
        public int RoomState { get; set; }
        public Noun[] Nouns { get; set; }
    }

    public class RoomState
    {
        public int Id { get; set; }
        public int State { get; set; }
        public DateTime Time { get; set; }
        public string Location { get; set; }
        public int Room { get; set; }
        public ParagraphState[] ParagraphStates { get; set; }
    }

    public class Area
    {
        public int Id { get; set; }
        public string Name { get; set; }
    }
}
