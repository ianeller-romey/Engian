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
    class ResultTypeJSONField
    {
        int m_id;
        string m_jsonField;
        int m_resultType;

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
        public string JSONField
        {
            get { return m_jsonField; }
            private set
            {
                if (m_jsonField != value)
                    m_jsonField = value;
            }
        }

        [DataMember]
        public int ResultType
        {
            get { return m_resultType; }
            private set
            {
                if (m_resultType != value)
                    m_resultType = value;
            }
        }
    }
}
