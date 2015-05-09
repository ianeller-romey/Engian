using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using GinTub;


namespace GinTub.Repository
{
    public class GinTubRepository : Interface.IGinTubRepository
    {
        public RoomDataInitialLoad.RoomData GetRoomDataInitialLoad(Guid playerId, int area, int x, int y, int z, DateTime currentTime)
        {
            var paragraphList = new List<RoomDataInitialLoad.ParagraphData>();

            paragraphList.Add(new RoomDataInitialLoad.ParagraphData() {
                Id = 1,
                State = 1,
                Text = "You sit alone in your car.",
                Nouns = new List<RoomDataInitialLoad.NounData> {
                    new RoomDataInitialLoad.NounData() {
                        Id = 1,
                        Text = "car"
                    }
                },
            });
            paragraphList.Add(new RoomDataInitialLoad.ParagraphData() {
                Id = 2,
                State = 1,
                Text = "The toneless drone of rain against the roof suffocates your ears.",
            });
            paragraphList.Add(new RoomDataInitialLoad.ParagraphData() {
                Id = 3,
                State = 1,
                Text = "The laptop perched on your knees illuminates the interior.",
                Nouns = new List<RoomDataInitialLoad.NounData> {
                    new RoomDataInitialLoad.NounData() {
                        Id = 2,
                        Text = "laptop"
                    }
                },
            });
            paragraphList.Add(new RoomDataInitialLoad.ParagraphData() {
                Id = 4,
                State = 1,
                Text = "In the seat beside you rests a crumpled bag, decorated with the garish logo of a fast food provider, and a gray boxcutter.",
                Nouns = new List<RoomDataInitialLoad.NounData> {
                    new RoomDataInitialLoad.NounData() {
                        Id = 3,
                        Text = "bag"
                    },
                    new RoomDataInitialLoad.NounData(){
                        Id = 4,
                        Text = "box cutter"
                    }
                }
            });

            return new RoomDataInitialLoad.RoomData() {
                Id = 1,
                Area = 1,
                State = 1,
                Location = "http://capitalcitiesusa.org/wp-content/uploads/2012/07/01-Rainy-car-window.jpg",
                X = 0,
                Y = 0,
                Z = 0,
                CurrentTime = DateTime.Now,
                RefreshTime = null,
                Paragraphs = paragraphList
            };
        }
    }
}
