using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;


namespace TBGINTB_Builder.Lib.Model
{
    [DataContract]
    public class Area : ObservablePropertiesObject
    {
        int m_id;
        string m_name;
        int m_maxX, m_minX;
        int m_maxY, m_minY;
        int m_maxZ, m_minZ;
        int m_numRooms;
        ObservableCollection<Room> m_rooms = new ObservableCollection<Room>();

        [DataMember]
        public int Id 
        {
            get { return m_id; }
            private set
            {
                if (m_id != value)
                {
                    m_id = value;
                    NotifyPropertyChanged("Id");
                }
            }
        }

        [DataMember]
        public string Name
        {
            get { return m_name; }
            private set
            {
                if (m_name != value)
                {
                    m_name = value;
                    NotifyPropertyChanged("Name");
                }
            }
        }

        public int MaxX
        {
            get { return m_maxX; }
            private set
            {
                if (m_maxX != value)
                {
                    m_maxX = value;
                    NotifyPropertyChanged("MaxX");
                }
            }
        }

        public int MinX
        {
            get { return m_minX; }
            private set
            {
                if (m_minX != value)
                {
                    m_minX = value;
                    NotifyPropertyChanged("MinX");
                }
            }
        }

        public int MaxY
        {
            get { return m_maxY; }
            private set
            {
                if (m_maxY != value)
                {
                    m_maxY = value;
                    NotifyPropertyChanged("MaxY");
                }
            }
        }

        public int MinY
        {
            get { return m_minY; }
            private set
            {
                if (m_minY != value)
                {
                    m_minY = value;
                    NotifyPropertyChanged("MinY");
                }
            }
        }

        public int MaxZ
        {
            get { return m_maxZ; }
            private set
            {
                if (m_maxZ != value)
                {
                    m_maxZ = value;
                    NotifyPropertyChanged("MaxZ");
                }
            }
        }

        public int MinZ
        {
            get { return m_minZ; }
            private set
            {
                if (m_minZ != value)
                {
                    m_minZ = value;
                    NotifyPropertyChanged("MinZ");
                }
            }
        }

        public int NumRooms
        {
            get { return m_numRooms; }
            private set
            {
                if (m_numRooms != value)
                {
                    m_numRooms = value;
                    NotifyPropertyChanged("NumRooms");
                }
            }
        }

        [DataMember]
        public ObservableCollection<Room> Rooms
        {
            get { return m_rooms; }
        }

    }
}
