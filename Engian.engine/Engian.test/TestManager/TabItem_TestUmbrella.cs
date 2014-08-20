using System;
using System.Collections.Generic;
using System.IO;
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

using CPPHeaderTestFileGenerator_Lib;

using TestMonger_Console;


namespace TestManager
{

    public class TabItem_TestUmbrella : TabItem
    {

        #region MEMBER FIELDS

        delegate List<string> Delegate_TestFunction(string fileName);

        string m_testUmbrella;

        ListBox m_listBox_Tests;
        Window m_parent;

        #endregion



        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_TestUmbrella(string testUmbrella, Window parent)
        {
            m_testUmbrella = testUmbrella;
            m_parent = parent;

            Header = m_testUmbrella;
            CreateControls();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            Grid grid = new Grid();
            grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            m_listBox_Tests =
                new ListBox()
                {
                    SelectionMode = SelectionMode.Extended,
                    Margin = new Thickness(2.5)
                };
            m_listBox_Tests.ItemsSource = InvokeTestFunctionWithTempFile(GetTests);
            Grid.SetRow(m_listBox_Tests, 0);

            Button button_RunSelected =
                new Button()
                {
                    Content = "Run Selected",
                    FontSize = 36,
                    Margin = new Thickness(2.5)
                };
            button_RunSelected.Click += button_RunSelected_Click;
            Grid.SetRow(button_RunSelected, 1);

            grid.Children.Add(m_listBox_Tests);
            grid.Children.Add(button_RunSelected);

            Content = grid;
        }

        private List<string> InvokeTestFunctionWithTempFile(Delegate_TestFunction testFunction)
        {
            string tempFile = Path.Combine(Path.GetTempPath(), string.Format("temp{0}.xml", m_testUmbrella));
            if (File.Exists(tempFile))
                File.Delete(tempFile);

            GeneratedTestFileList tempList = GeneratedTestFileList.Deserialize(tempFile);
            GeneratedTestFileInfo tempInfo = new GeneratedTestFileInfo(string.Empty, string.Empty, m_testUmbrella, string.Empty, string.Empty);
            tempList.GeneratedTestFiles.Add(tempInfo);
            GeneratedTestFileList.Serialize(tempList, tempFile);

            List<string> forReturn = testFunction(tempFile);

            File.Delete(tempFile);

            return forReturn;
        }

        private List<string> GetTests(string fileName)
        {
            return TestMonger_Console.ProgramManager.GetListOfTestsUnderUmbrellasFromXML(fileName)[m_testUmbrella];
        }

        private List<string> RunTests(string fileName)
        {
            return TestMonger_Console.ProgramManager.RunListOfTestsUnderUmbrellasFromXML(fileName)[m_testUmbrella];
        }

        void button_RunSelected_Click(object sender, RoutedEventArgs e)
        {
            string[] testsToRun = m_listBox_Tests.SelectedItems.OfType<string>().ToArray();
            if (testsToRun.Any())
            {
                List<string> testResults = InvokeTestFunctionWithTempFile(RunTests);
                Window win = new Window_TestResults(m_testUmbrella, testResults, m_parent);
                win.Show();
            }
        }

        #endregion

        #endregion

    }

}
