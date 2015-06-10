using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.BuilderControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Grid_ParagraphData : Grid, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        TextBox m_textBox_order;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphId { get; private set; }
        public int? ParagraphOrder { get; private set; }
        public int RoomId { get; private set; }
        public int? RoomStateId { get; private set; }

        public List<UIElement> EditingControls
        {
            get
            {
                return new List<UIElement>
                {
                    m_textBox_order
                };
            }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Grid_ParagraphData(int? paragraphId, int? paragraphOrder, int roomId, int? roomStateId, bool enableEditing)
        {
            ParagraphId = paragraphId;
            ParagraphOrder = paragraphOrder;
            RoomStateId = roomStateId;
            RoomId = roomId;

            CreateControls();

            foreach (var e in EditingControls)
                e.IsEnabled = enableEditing;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.ParagraphModified += GinTubBuilderManager_ParagraphModified;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.ParagraphModified -= GinTubBuilderManager_ParagraphModified;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            ////////
            // Id Grid
            Grid grid_id = new Grid();
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_id.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_id, 0, 0);

            ////////
            // Id
            TextBlock textBlock_paragraphId =
                new TextBlock()
                {
                    VerticalAlignment = VerticalAlignment.Center,
                    Text = (ParagraphId.HasValue) ? ParagraphId.ToString() : "NewParagraph"
                };
            Label label_paragraphId = new Label() { Content = "Id:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_id.SetGridRowColumn(textBlock_paragraphId, 0, 1);
            grid_id.SetGridRowColumn(label_paragraphId, 0, 0);

            ////////
            // State Grid
            Grid grid_state = new Grid();
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid_state.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            this.SetGridRowColumn(grid_state, 1, 0);

            ////////
            // State
            m_textBox_order = new TextBox() { VerticalAlignment = VerticalAlignment.Center };
            m_textBox_order.TextChanged += TextBox_ParagraphOrder_TextChanged;
            m_textBox_order.Text = (ParagraphOrder.HasValue) ? ParagraphOrder.ToString() : "0";
            Label label_paragraphOrder = new Label() { Content = "Order:", FontWeight = FontWeights.Bold, VerticalAlignment = VerticalAlignment.Center };
            grid_state.SetGridRowColumn(m_textBox_order, 0, 1);
            grid_state.SetGridRowColumn(label_paragraphOrder, 0, 0);
        }

        private void GinTubBuilderManager_ParagraphModified(object sender, GinTubBuilderManager.ParagraphModifiedEventArgs args)
        {
            if (args.Id == ParagraphId)
            {
                SetParagraphOrder(args.Order);
                RoomStateId = args.RoomState;
                RoomId = args.Room;
            }
        }

        private void SetParagraphOrder(int order)
        {
            ParagraphOrder = order;
            m_textBox_order.Text = ParagraphOrder.ToString();
        }

        void TextBox_ParagraphOrder_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            int newOrder = 0;
            if (tb != null && tb == m_textBox_order && int.TryParse(m_textBox_order.Text, out newOrder))
                ParagraphOrder = newOrder;
        }

        #endregion

        #endregion

    }
}
