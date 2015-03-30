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

    public class TabItem_AddExistingTestFile : TabItem_UpdateTestFileTab
    {

        #region MEMBER FIELDS

        TextBox m_textBox_headerAlreadyParsed;
        TextBox m_textBox_existingTestFile;
        Button m_button_findHeaderAlreadyParsed;
        Button m_button_findExistingTestFile;
        Button m_button_updateListOfTestFiles;

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

        public TabItem_AddExistingTestFile(string generatedXmlFile, Window parent) :
            base(generatedXmlFile)
        {
            m_parent = parent;
            CreateControls();
        }

        #endregion


        #region Private Functionality

        private void GenerateTestFile(string headerFile, string testName, string testFile)
        {
            ProcessStartInfo processStartInfo =
                new ProcessStartInfo
                (
                    "CPPHeaderTestFileGenerator_Console.exe", 
                    string.Format
                    (
                        "-generatedxmlfile \"{0}\" -headerfile \"{1}\" -testname \"{2}\" -testfile \"{3}\"", 
                        m_generatedXmlFile,
                        headerFile,
                        testName,
                        testFile
                    )
                );
            Process testFileGenerator = Process.Start(processStartInfo);
            testFileGenerator.WaitForExit();
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
            grid_sub.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(100.0, GridUnitType.Star) });
            grid_sub.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });

            m_textBox_headerAlreadyParsed = new TextBox() { Style = Style_DefaultMarginStyle.Style };
            Grid.SetRow(m_textBox_headerAlreadyParsed, 0);
            Grid.SetColumn(m_textBox_headerAlreadyParsed, 0);
            grid_sub.Children.Add(m_textBox_headerAlreadyParsed);

            m_textBox_existingTestFile = new TextBox() { Style = Style_DefaultMarginStyle.Style };
            Grid.SetRow(m_textBox_existingTestFile, 1);
            Grid.SetColumn(m_textBox_existingTestFile, 0);
            grid_sub.Children.Add(m_textBox_existingTestFile);

            m_button_findHeaderAlreadyParsed = new Button() { Content = "Already Parsed Header", Style = Style_DefaultMarginStyle.Style };
            m_button_findHeaderAlreadyParsed.Click += Button_FindAlreadyParsedHeader_Click;
            Grid.SetRow(m_button_findHeaderAlreadyParsed, 0);
            Grid.SetColumn(m_button_findHeaderAlreadyParsed, 1);
            grid_sub.Children.Add(m_button_findHeaderAlreadyParsed);

            m_button_findExistingTestFile = new Button() { Content = "Existing Test File", Style = Style_DefaultMarginStyle.Style };
            m_button_findExistingTestFile.Click += Button_ExistingTestFile_Click;
            Grid.SetRow(m_button_findExistingTestFile, 1);
            Grid.SetColumn(m_button_findExistingTestFile, 1);
            grid_sub.Children.Add(m_button_findExistingTestFile);

            m_button_updateListOfTestFiles = new Button() { Content = "Update List of Test Files", Style = Style_DefaultMarginStyle.Style };
            m_button_updateListOfTestFiles.Click += Button_UpdateListOfTestFiles_Click;
            Grid.SetRow(m_button_updateListOfTestFiles, 2);
            Grid.SetColumnSpan(m_button_updateListOfTestFiles, 2);
            grid_sub.Children.Add(m_button_updateListOfTestFiles);

            Grid.SetRow(grid_sub, 1);
            grid_main.Children.Add(grid_sub);

            ////////
            // fin
            Content = grid_main;
        }

        void Button_UpdateListOfTestFiles_Click(object sender, RoutedEventArgs e)
        {
            string headerFile = m_textBox_headerAlreadyParsed.Text;
            string testFile = m_textBox_existingTestFile.Text;
            if (!string.IsNullOrEmpty(headerFile) && !string.IsNullOrEmpty(testFile))
            {
                string testName = Path.GetFileNameWithoutExtension(testFile);
                Window_TextBox win = new Window_TextBox(char.ToUpper(testName.First()) + testName.Substring(1), "Test Name", m_parent);
                win.ShowDialog();
                if (win.Accepted)
                {
                    testName = win.Text;
                    GenerateTestFile(headerFile, testName, testFile);
                    RaiseUpdatedTestFileEvent();
                    m_textBox_headerAlreadyParsed.Clear();
                    m_textBox_existingTestFile.Clear();
                }
            }
        }

        private void Button_FindAlreadyParsedHeader_Click(object sender, RoutedEventArgs e)
        {
            string header = SelectHeaderFile("Already Parsed Header");
            if (!string.IsNullOrWhiteSpace(header))
                m_textBox_headerAlreadyParsed.Text = header;
        }

        private void Button_ExistingTestFile_Click(object sender, RoutedEventArgs e)
        {
            string header = SelectTestFile("Existing Test File");
            if (!string.IsNullOrWhiteSpace(header))
                m_textBox_existingTestFile.Text = header;
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

        private string SelectTestFile(string testType)
        {
            Microsoft.Win32.OpenFileDialog openFileDialog =
                new Microsoft.Win32.OpenFileDialog()
                {
                    CheckFileExists = true,
                    CheckPathExists = true,
                    DefaultExt = ".cpp",
                    Filter = "Headers (*.cpp)|*.cpp",
                    Title = testType,
                    Multiselect = false
                };
            bool? success = false;
            return ((success = openFileDialog.ShowDialog(m_parent)) != null && success != false) ? openFileDialog.FileName : string.Empty;
        }

        #endregion

        #endregion

    }

}
