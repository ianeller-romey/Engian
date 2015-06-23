﻿using System;
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
    public class Window_ParagraphState : Window_AcceptCancel
    {
        #region MEMBER FIELDS

        UserControl_ParagraphState m_userControl_paragraphState;

        #endregion


        #region MEMBER PROPERTIES

        public int? ParagraphStateId { get { return m_userControl_paragraphState.ParagraphStateId; } }
        public string ParagraphStateText { get { return m_userControl_paragraphState.ParagraphStateText; } }
        public int? ParagraphStateState { get { return m_userControl_paragraphState.ParagraphStateState; } }
        public int ParagraphId { get { return m_userControl_paragraphState.ParagraphId; } }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_ParagraphState(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId)
        {
            Title = "Paragraph State Data";
            Width = 300;
            Height = 300;
            Content = CreateControls(paragraphId, paragraphStateText, paragraphStateState, paragraphId);
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls(int? paragraphStateId, string paragraphStateText, int? paragraphStateState, int paragraphId)
        {
            m_userControl_paragraphState = new UserControl_ParagraphState(paragraphId, paragraphStateText, paragraphStateState, paragraphId, true, false);
            return m_userControl_paragraphState;
        }

        #endregion

        #endregion
    }
}