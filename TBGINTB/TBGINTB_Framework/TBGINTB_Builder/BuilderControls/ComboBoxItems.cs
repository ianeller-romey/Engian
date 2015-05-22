using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class ComboBoxItem_Area : ComboBoxItem
    {
        #region MEMBER FIELDS

        private TextBox_AreaName m_textBox_areaName;

        #endregion


        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public string AreaName { get { return m_textBox_areaName.Text; } }

        #endregion


        #region MEMBER CLASSES

        private class TextBox_AreaName : TextBox
        {
            #region MEMBER METHODS

            #region Public Functionality

            public TextBox_AreaName(string text)
            {
                Margin = new Thickness() { Top = 0.0, Right = 5.0, Bottom = 0.0, Left = 2.0 };
                Text = text;
                List<UIElement> removedItems = new List<UIElement>();
                List<UIElement> addedItems = new List<UIElement>();
                addedItems.Add(this);
            }

            #endregion

            #endregion
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBoxItem_Area(int id, string name)
        {
            AreaId = id;
            m_textBox_areaName = new TextBox_AreaName(name);
            Content = m_textBox_areaName;

            m_textBox_areaName.TextChanged += TextBox_AreaName_TextChanged;
            m_textBox_areaName.GotFocus += (x, y) => { RaiseEvent(new RoutedEventArgs(ComboBoxItem.SelectedEvent, this)); };
        }

        public void SetAreaName(string name)
        {
            if (m_textBox_areaName.Text != name)
                m_textBox_areaName.Text = name;
        }

        #endregion


        #region Private Functionality

        void TextBox_AreaName_TextChanged(object sender, TextChangedEventArgs e)
        {
            GinTubBuilderManager.ModifyArea(AreaId, m_textBox_areaName.Text);
        }

        #endregion

        #endregion
    }

    public class ComboBoxItem_Z : ComboBoxItem
    {
        #region MEMBER PROPERTIES

        public int Z { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBoxItem_Z(int z)
        {
            Z = z;
            Content = Z;
        }

        #endregion

        #endregion
    }
    
    public class ComboBoxItem_Location : ComboBoxItem
    {
        #region MEMBER PROPERTIES

        public int LocationId { get; private set; }
        public string LocationName { get; private set; }
        public string LocationFile { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public ComboBoxItem_Location(int id, string locationName, string locationFile)
        {
            LocationId = id;
            LocationFile = locationFile;
            SetLocationName(locationName);
        }

        public void SetLocationName(string name)
        {
            LocationName = name;
            Content = LocationName;
        }

        #endregion

        #endregion
    }
}
