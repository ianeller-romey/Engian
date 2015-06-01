using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Window_ParagraphData : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        Grid_ParagraphData m_grid_paragraphData;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphId { get { return m_grid_paragraphData.ParagraphId; } }
        public int? ParagraphOrder { get { return m_grid_paragraphData.ParagraphOrder; } }
        public int RoomId { get { return m_grid_paragraphData.RoomId; } }
        public int? RoomStateId { get { return m_grid_paragraphData.RoomStateId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ParagraphData(int? paragraphId, int? paragraphOrder, int roomId, int? roomStateId)
        {
            Title = "Paragraph Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(paragraphId, paragraphOrder, roomId, roomStateId);
            GinTubBuilderManager.LoadAllLocations();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? paragraphId, int? paragraphOrder, int roomId, int? roomStateId)
        {
            m_grid_paragraphData = new Grid_ParagraphData(paragraphId, paragraphOrder, roomId, roomStateId, true);
            return m_grid_paragraphData;
        }

        #endregion

        #endregion
    }
}
