using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;


namespace TBGINTB_Builder.Lib.Model.XmlModel
{
    [XmlRoot("GinTub")]
    public class GinTub
    {
        DateTime m_exportDate;
        Item[] m_items;
        Event[] m_events;
        Character[] m_characters;
        ResultType[] m_resultTypes;
        VerbType[] m_verbTypes;
        Location[] m_locations;
        Message[] m_messages;
        Area[] m_areas;

        [XmlAttribute("ExportDate")]
        public DateTime ExportDate
        {
            get { return m_exportDate; }
            set
            {
                if (m_exportDate != value)
                    m_exportDate = value;
            }
        }
        
        [XmlArray("Items")]
        public Item[] Items
        {
            get { return m_items; }
            set
            {
                if (m_items != value)
                    m_items = value;
            }
        }

        [XmlArray("Events")]
        public Event[] Events
        {
            get { return m_events; }
            set
            {
                if (m_events != value)
                    m_events = value;
            }
        }

        [XmlArray("Characters")]
        public Character[] Characters
        {
            get { return m_characters; }
            set
            {
                if (m_characters != value)
                    m_characters = value;
            }
        }

        [XmlArray("ResultTypes")]
        public ResultType[] ResultTypes
        {
            get { return m_resultTypes; }
            set
            {
                if (m_resultTypes != value)
                    m_resultTypes = value;
            }
        }

        [XmlArray("VerbTypes")]
        public VerbType[] VerbTypes
        {
            get { return m_verbTypes; }
            set
            {
                if (m_verbTypes != value)
                    m_verbTypes = value;
            }
        }

        [XmlArray("Locations")]
        public Location[] Locations
        {
            get { return m_locations; }
            set
            {
                if (m_locations != value)
                    m_locations = value;
            }
        }

        [XmlArray("Messages")]
        public Message[] Messages
        {
            get { return m_messages; }
            set
            {
                if (m_messages != value)
                    m_messages = value;
            }
        }

        [XmlArray("Areas")]
        public Area[] Areas
        {
            get { return m_areas; }
            set
            {
                if (m_areas != value)
                    m_areas = value;
            }
        }
    }
}
