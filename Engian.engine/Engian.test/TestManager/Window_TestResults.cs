using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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

        ListView m_listView_Tests;

        #endregion


        #region MEMBER CLASSES

        private class TestFailure
        {

            #region MEMBER FIELDS

            static Regex s_regex = new Regex(@"TEST\s+\{(?<test_name>.+)\}\r\nin\s+FILE\s+\{(?<file_name>.+)\}\r\nat\s+LINE\s+\{(?<line_number>\d+)\}\r\nfailed:\r\n(?<message>.+)");

            #endregion


            #region MEMBER PROPERTIES

            public string Test { get; set; }

            public string File { get; set; }

            public int Line { get; set; }

            public string Message { get; set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public TestFailure(string failureMessage)
            {
                Match m = s_regex.Match(failureMessage);
                if (m != null)
                {
                    Test = m.Groups["test_name"].Value;
                    File = m.Groups["file_name"].Value;
                    Line = int.Parse(m.Groups["line_number"].Value);
                    Message = m.Groups["message"].Value;
                }
            }

            #endregion

            #endregion

        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_TestResults(string testName, List<string> testResults, Window parent)
        {
            m_testResults = testResults;

            Title = testName;
            CreateControls();

            Owner = parent;
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterOwner;
            Width = 650;
            Height = 500;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            if (m_testResults.Any())
            {
                List<TestFailure> testFailures = m_testResults.Select(tr => new TestFailure(tr)).ToList();

                GridView gridView = new GridView();
                gridView.Columns.Add(new GridViewColumn() { Header = "Test", DisplayMemberBinding=new Binding("Test") });
                gridView.Columns.Add(new GridViewColumn() { Header = "File", DisplayMemberBinding = new Binding("File"), Width = 150 });
                gridView.Columns.Add(new GridViewColumn() { Header = "Line", DisplayMemberBinding = new Binding("Line") });
                gridView.Columns.Add(new GridViewColumn() { Header = "Message", DisplayMemberBinding = new Binding("Message") });
                m_listView_Tests = new ListView()
                    {
                        SelectionMode = SelectionMode.Single,
                        Margin = new Thickness(2.5),
                        Background = Brushes.LightGray,
                        View = gridView,
                        ItemsSource = testFailures
                    };
                m_listView_Tests.MouseDoubleClick += (x, y) =>
                    {
                        TestFailure failureToOpen = null;
                        if((failureToOpen = m_listView_Tests.SelectedItem as TestFailure) != null)
                        {
                            Process process = new Process();
                            ProcessStartInfo startInfo = new ProcessStartInfo("devenv.exe", string.Format("/edit \"{0}\" /command \"edit.goto {1}\"", failureToOpen.File, failureToOpen.Line));
                            process.StartInfo = startInfo;
                            process.Start();
                        }
                    };
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
