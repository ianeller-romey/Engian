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


namespace TestManager
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        #region MEMBER FIELDS

        private static readonly string
            s_saveDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "TestManager"),
            s_generatedTestFileList = Path.Combine(s_saveDir, "GeneratedTestFileList.xml");

        TabItem_UpdateTestFileTab 
            tabItem_headerParser,
            tabItem_testFileUpdater;
        TabItem_TestMonger tabItem_testMonger;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public MainWindow()
        {
            InitializeComponent();

            if (!Directory.Exists(s_saveDir))
                Directory.CreateDirectory(s_saveDir);

            CreateControls();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            Height = 500;
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            tabItem_headerParser =
                new TabItem_GenerateTestFile(s_generatedTestFileList, this)
                {
                    Header = "Test File Generator"
                };
            tabItem_testFileUpdater =
                new TabItem_AddExistingTestFile(s_generatedTestFileList, this)
                {
                    Header = "Test File Updater"
                };
            tabItem_testMonger =
                new TabItem_TestMonger(s_generatedTestFileList, this)
                {
                    Header = "Test Monger"
                };

            tabItem_headerParser.UpdateTestFile += UpdateTestFileTabs;
            tabItem_testFileUpdater.UpdateTestFile += UpdateTestFileTabs;

            TabControl tabControl_Main = new TabControl();
            tabControl_Main.Items.Add(tabItem_headerParser);
            tabControl_Main.Items.Add(tabItem_testFileUpdater);
            tabControl_Main.Items.Add(tabItem_testMonger);

            Content = tabControl_Main;
        }

        private void UpdateTestFileTabs(object sender, RoutedEventArgs e)
        {
            tabItem_headerParser.GetListOfGeneratedTestFiles();
            tabItem_testFileUpdater.GetListOfGeneratedTestFiles();
            tabItem_testMonger.GetListOfTestUmbrellas();
        }

        #endregion

        #endregion

    }
}
