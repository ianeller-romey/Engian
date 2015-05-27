using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;


namespace TBGINTB_Builder.Lib.Model
{
    [DataContract]
    class Paragraph
    {
        int m_id;
        string m_text;
        int m_room;
        int m_roomState;
        int m_state;

        [DataMember]
        public int Id
        {
            get { return m_id; }
            private set
            {
                if (m_id != value)
                    m_id = value;
            }
        }

        [DataMember]
        public string Text
        {
            get { return m_text; }
            private set
            {
                if (m_text != value)
                    m_text = value;
            }
        }

        [DataMember]
        public int Room
        {
            get { return m_room; }
            private set
            {
                if (m_room != value)
                    m_room = value;
            }
        }

        [DataMember]
        public int RoomState
        {
            get { return m_roomState; }
            private set
            {
                if (m_roomState != value)
                    m_roomState = value;
            }
        }

        [DataMember]
        public int State
        {
            get { return m_state; }
            private set
            {
                if (m_state != value)
                    m_state = value;
            }
        }
    }
}
