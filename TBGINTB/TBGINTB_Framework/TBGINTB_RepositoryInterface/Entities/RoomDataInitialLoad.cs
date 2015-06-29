using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GinTub.Repository.Entities.LoadRoom
{
    public class Noun
    {
        public int Id { get; private set; }
        public string Text { get; private set; }
        public int ParagraphState { get; private set; }
    }

    public class ParagraphState
    {
        public int Id { get; private set; }
        public string Text { get; private set; }
        public int Order { get; private set; }
        public int RoomState { get; private set; }
        public Noun[] Nouns { get; set; }
    }

    public class RoomState
    {
        public int Id { get; private set; }
        public int State { get; private set; }
        public DateTime Time { get; private set; }
        public string Location { get; private set; }
        public int Room { get; private set; }
        public ParagraphState[] ParagraphStates { get; private set; }
    }
}
