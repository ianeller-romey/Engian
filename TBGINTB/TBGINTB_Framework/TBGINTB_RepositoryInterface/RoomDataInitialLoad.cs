using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GinTub.Repository.RoomDataInitialLoad
{
    public class NounData
    {
        public int Id { get; set; }
        public string Text { get; set; }
    }

    public class ParagraphData
    {
        public int Id { get; set; }
        public int State { get; set; }
        public string Text { get; set; }
        public IEnumerable<NounData> Nouns { get; set; }
    }

    public class RoomData
    {
        public int Id { get; set; }
        public int State { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }
        public int Area { get; set; }
        public string Location { get; set; }
        public DateTime CurrentTime { get; set; }
        public DateTime? RefreshTime { get; set; }
        public IEnumerable<ParagraphData> Paragraphs { get; set; }
    }
}
