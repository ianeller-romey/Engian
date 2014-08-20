﻿using System;
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
            TabItem 
                tabItem_headerParser =
                    new TabItem_GenerateTestFile(s_generatedTestFileList, this)
                    {
                        Header = "Test File Generator"
                    },
                tabItem_testMonger =
                    new TabItem_TestMonger(s_generatedTestFileList, this)
                    {
                        Header = "Test Monger"
                    };
            TabControl tabControl_Main = new TabControl();
            tabControl_Main.Items.Add(tabItem_headerParser);
            tabControl_Main.Items.Add(tabItem_testMonger);

            Content = tabControl_Main;
        }

        #endregion

        #endregion

    }
}
