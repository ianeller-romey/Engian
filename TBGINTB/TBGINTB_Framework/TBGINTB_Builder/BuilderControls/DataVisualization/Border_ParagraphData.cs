using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Border_ParagraphData : Border, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        Grid_ParagraphData m_grid_paragraph;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphId { get { return m_grid_paragraph.ParagraphId; } }
        public int? ParagraphOrder { get { return m_grid_paragraph.ParagraphOrder; } }
        public int RoomId { get { return m_grid_paragraph.RoomId; } }
        public int? RoomStateId { get { return m_grid_paragraph.RoomStateId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Border_ParagraphData(int? paragraphId, int? paragraphOrder, int roomId, int? roomStateId, bool enableEditing)
        {
            CreateControls( paragraphId,  paragraphOrder, roomId,  roomStateId, enableEditing);
            Style = Style_DefaultBorder.Instance;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            m_grid_paragraph.SetActiveAndRegisterForGinTubEvents();
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            m_grid_paragraph.SetInactiveAndUnregisterFromGinTubEvents();
        }

        #endregion


        #region Private Functionality

        private void CreateControls(int? paragraphId, int? paragraphOrder, int roomId, int? roomStateId, bool enableEditing)
        {
            m_grid_paragraph = new Grid_ParagraphData(paragraphId, paragraphOrder, roomId, roomStateId, enableEditing);
            Child = m_grid_paragraph;
        }

        #endregion

        #endregion
    }
}
