using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
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

using CPPHeaderTestFileGenerator_Lib;


namespace TestManager
{

    public class TabItem_GenerateTestFile : TabItem
    {

        #region MEMBER FIELDS

        readonly string m_generatedXmlFile;
        List<GeneratedTestFileInfo> m_generatedTestFiles = new List<GeneratedTestFileInfo>();

        ListView m_listView_parsedHeaders;
        TextBox m_textBox_headerToParse;
        Button m_button_findHeaderToParse;
        Button m_button_generateTestFile;

        Window m_parent;

        #endregion


        #region MEMBER CLASSES

        private class Style_DefaultMarginStyle : Style
        {

            #region MEMBER FIELDS

            public static Style_DefaultMarginStyle Style = new Style_DefaultMarginStyle(new Thickness(2.5));

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public Style_DefaultMarginStyle(Thickness defaultThickness)
            {
                Setters.Add(new Setter(MarginProperty, defaultThickness));
            }

            #endregion

            #endregion

        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_GenerateTestFile(string generatedXmlFile, Window parent)
        {
            m_generatedXmlFile = generatedXmlFile;
            GetListOfGeneratedTestFiles();

            m_parent = parent;
            CreateControls();
        }

        #endregion


        #region Private Functionality

        private void GenerateTestFile(string headerFile, string testName, string testFile, string chassisFile)
        {
            ProcessStartInfo processStartInfo =
                new ProcessStartInfo
                (
                    "CPPHeaderTestFileGenerator_Console.exe", 
                    string.Format
                    (
                        "-generatedxmlfile \"{0}\" -headerfile \"{1}\" -testname \"{2}\" -testfile \"{3}\" -chassisfile \"{4}\"", 
                        m_generatedXmlFile,
                        headerFile,
                        testName,
                        testFile,
                        chassisFile
                    )
                );
            Process testFileGenerator = Process.Start(processStartInfo);
            testFileGenerator.WaitForExit();
        }

        private void GetListOfGeneratedTestFiles()
        {
            m_generatedTestFiles.Clear();
            m_generatedTestFiles = CPPHeaderTestFileGenerator_Console.ProgramManager.GetListOfGeneratedFilesFromXML(m_generatedXmlFile);
        }

        private void CreateControls()
        {
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            ////////
            // listview of parsed headers
            m_listView_parsedHeaders = new ListView() { Style = Style_DefaultMarginStyle.Style };
            m_listView_parsedHeaders.ItemsSource = m_generatedTestFiles;
            Grid.SetRow(m_listView_parsedHeaders, 0);
            grid_main.Children.Add(m_listView_parsedHeaders);

            ////////
            // parse header interface
            Grid grid_sub = new Grid();
            grid_sub.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_sub.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(100.0, GridUnitType.Star) });
            grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });

            m_textBox_headerToParse = new TextBox() { Style = Style_DefaultMarginStyle.Style };
            Grid.SetRow(m_textBox_headerToParse, 0);
            Grid.SetColumn(m_textBox_headerToParse, 0);
            grid_sub.Children.Add(m_textBox_headerToParse);

            m_button_findHeaderToParse = new Button() { Content = ". . .", Style = Style_DefaultMarginStyle.Style };
            m_button_findHeaderToParse.Click += Button_FindHeaderToParse_Click;
            Grid.SetRow(m_button_findHeaderToParse, 0);
            Grid.SetColumn(m_button_findHeaderToParse, 1);
            grid_sub.Children.Add(m_button_findHeaderToParse);

            m_button_generateTestFile = new Button() { Content = "Generate Test File", Style = Style_DefaultMarginStyle.Style };
            m_button_generateTestFile.Click += Button_GenerateTestFile_Click;
            Grid.SetRow(m_button_generateTestFile, 1);
            Grid.SetColumnSpan(m_button_generateTestFile, 2);
            grid_sub.Children.Add(m_button_generateTestFile);

            Grid.SetRow(grid_sub, 1);
            grid_main.Children.Add(grid_sub);

            ////////
            // fin
            Content = grid_main;
        }

        void Button_GenerateTestFile_Click(object sender, RoutedEventArgs e)
        {
            string headerFile = m_textBox_headerToParse.Text;
            if (!string.IsNullOrEmpty(headerFile))
            {
                string testName = Path.GetFileNameWithoutExtension(headerFile);
                Window_TextBox win = new Window_TextBox(string.Format("Test{0}", char.ToUpper(testName.First()) + testName.Substring(1)), "Test Name", m_parent);
                win.ShowDialog();
                if (win.Accepted)
                {
                    testName = win.Text;
                    string testFile = SelectTestFile(testName, "Test File to Generate");
                    if (!string.IsNullOrWhiteSpace(testFile))
                    {
                        string chassisFile = SelectHeaderFile("Unit Test Chassis Header");
                        if (!string.IsNullOrWhiteSpace(chassisFile))
                        {
                            GenerateTestFile(headerFile, testName, testFile, chassisFile);
                            GetListOfGeneratedTestFiles();
                            m_listView_parsedHeaders.ItemsSource = m_generatedTestFiles;
                        }
                    }
                }
            }
        }

        private void Button_FindHeaderToParse_Click(object sender, RoutedEventArgs e)
        {
            string header = SelectHeaderFile("Header to Parse");
            if (!string.IsNullOrWhiteSpace(header))
                m_textBox_headerToParse.Text = header;
        }

        private string SelectHeaderFile(string headerType)
        {
            Microsoft.Win32.OpenFileDialog openFileDialog =
                new Microsoft.Win32.OpenFileDialog()
                {
                    CheckFileExists = true,
                    CheckPathExists = true,
                    DefaultExt = ".h",
                    Filter = "Headers (*.h)|*.h",
                    Title = headerType,
                    Multiselect = false
                };
            bool? success = false;
            return ((success = openFileDialog.ShowDialog(m_parent)) != null && success != false) ? openFileDialog.FileName : string.Empty;
        }

        private string SelectTestFile(string testName, string testFileDescription)
        {
            string testFileName = char.ToLower(testName.First()) + testName.Substring(1) + ".cpp";
            Microsoft.Win32.OpenFileDialog openFileDialog =
                new Microsoft.Win32.OpenFileDialog()
                {
                    CheckPathExists = true,
                    CheckFileExists = false,
                    DefaultExt = ".cpp",
                    FileName = testFileName,
                    Filter = "Source (*.cpp)|*.cpp",
                    Title = testFileDescription,
                    Multiselect = false
                };
            bool? success = false;
            return ((success = openFileDialog.ShowDialog(m_parent)) != null && success != false) ? openFileDialog.FileName : string.Empty;
        }

        #endregion

        #endregion

    }

}
