using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;


namespace TBGINTB_Builder.Lib.Model.DbModel
{
    [DataContract]
    class RoomPreview
    {
        int m_id;
        RoomPreviewParagraphState[] m_paragraphStates;

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
        public RoomPreviewParagraphState[] ParagraphStates
        {
            get { return m_paragraphStates; }
            private set
            {
                if (m_paragraphStates != value)
                    m_paragraphStates = value;
            }
        }
    }
}
