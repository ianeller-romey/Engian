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

    public class Window_TestResults : Window
    {

        #region MEMBER FIELDS

        List<string> m_testResults;

        ListBox m_listView_Tests;

        #endregion



        #region MEMBER METHODS

        #region Public Functionality

        public Window_TestResults(string testName, List<string> testResults, Window parent)
        {
            m_testResults = testResults;

            Title = testName;
            CreateControls();

            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterOwner;
            Owner = parent;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            if (m_testResults.Any())
            {
                m_listView_Tests =
                    new ListBox()
                    {
                        SelectionMode = SelectionMode.Extended,
                        Margin = new Thickness(2.5),
                        Background = Brushes.LightGray
                    };
                // Yeah, yeah, there's a better way to do this
                foreach(string result in m_testResults)
                {
                    m_listView_Tests.Items.Add(result);
                    m_listView_Tests.Items.Add(new Separator());
                }
                Content = m_listView_Tests;
            }
            else
            {
                TextBlock textBlock =
                    new TextBlock()
                    {
                        Text = "All Tests Successful!",
                        FontSize = 48,
                        FontWeight = FontWeights.Bold,
                        Foreground = Brushes.DarkGreen,
                        TextAlignment = System.Windows.TextAlignment.Center,
                        HorizontalAlignment = System.Windows.HorizontalAlignment.Center,
                        VerticalAlignment = System.Windows.VerticalAlignment.Center,
                        TextWrapping = TextWrapping.Wrap
                    };
                Width = Height = 300;
                ResizeMode = System.Windows.ResizeMode.NoResize;
                Content = textBlock;
            }
            Background = Brushes.LightGray;
        }

        #endregion

        #endregion

    }

}
