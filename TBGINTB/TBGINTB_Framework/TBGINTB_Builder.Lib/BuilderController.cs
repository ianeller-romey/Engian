using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AutoMapper;

using TBGINTB_Builder.Lib.Model;
using TBGINTB_Builder.Lib.Repository;


namespace TBGINTB_Builder.Lib
{
    public static class BuilderController
    {
        #region MEMBER FIELDS

        private static GinTubEntities m_entities = new GinTubEntities();
        public static List<Area> m_areas = new List<Area>();

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public static void Initialize()
        {
            Mapper.CreateMap<dev_GetAllAreas_Result, Area>();
            Mapper.CreateMap<dev_GetArea_Result, Area>();
            GetAllAreas();
        }

        #region Areas

        public static Area AddArea(string name)
        {
            return InsertArea(name);
        }

        public static Area RefreshArea(int id)
        {
            return GetArea(id);
        }

        #endregion

        #endregion


        #region Private Functionality

        #region Areas

        private static Area InsertArea(string name)
        {
            foreach (var result in m_entities.dev_AddArea(name))
                if (result.HasValue)
                {
                    return GetArea((int)result.Value);
                }
            throw new Exception("No new [Id] was returned after INSERT.");
        }

        private static Area GetArea(int id)
        {
            if (m_areas.Any(a => a.Id == id))
                m_areas.RemoveAll(a => a.Id == id);

            var area = Mapper.Map<Area>(m_entities.dev_GetArea(id));
            m_areas.Add(area);
            return area;
        }

        private static void GetAllAreas()
        {
            m_areas.Clear();
            foreach(var result in m_entities.dev_GetAllAreas())
                RefreshArea(result.Id);
        }

        #endregion

        #endregion

        #endregion

    }
}
