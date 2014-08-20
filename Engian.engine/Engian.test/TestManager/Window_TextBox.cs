using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace TestManager
{

    public class Window_TextBox : Window
    {

        #region MEMBER FIELDS

        TextBox m_textBox;
        Window m_parent;

        #endregion


        #region MEMBER PROPERTIES

        public string Text { get; private set; }

        public bool Accepted { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_TextBox(string text, string title, Window parent)
        {
            m_parent = parent;

            CreateControls(text);

            Title = title;
            ResizeMode = System.Windows.ResizeMode.NoResize;
            Width = 200;
            Height = 150;
            Owner = m_parent;
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterOwner;
        }

        #endregion


        #region Private Functionality

        private void CreateControls(string text)
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            ////////
            // textbox
            m_textBox = new TextBox() { Text = text };
            Grid.SetRow(m_textBox, 0);
            grid_main.Children.Add(m_textBox);

            ////////
            // buttons
            Grid grid_buttons = new Grid();
            grid_buttons.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(50.0, GridUnitType.Star) });
            grid_buttons.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(50.0, GridUnitType.Star) });
            Grid.SetRow(grid_buttons, 1);
            grid_main.Children.Add(grid_buttons);

            Button
                button_accept = new Button() { Content = "Accept" },
                button_cancel = new Button() { Content = "Cancel" };
            button_accept.Click += (x, y) =>
                {
                    Accepted = true;
                    Text = m_textBox.Text;
                    Close();
                };
            button_cancel.Click += (x, y) =>
                {
                    Close();
                };
            Grid.SetColumn(button_accept, 0);
            grid_buttons.Children.Add(button_accept);
            Grid.SetColumn(button_cancel, 1);
            grid_buttons.Children.Add(button_cancel);

            ////////
            // fin
            Content = grid_main;
        }

        #endregion

        #endregion

    }

}
