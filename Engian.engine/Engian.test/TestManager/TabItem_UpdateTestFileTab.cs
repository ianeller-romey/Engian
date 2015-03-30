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

    public abstract class TabItem_UpdateTestFileTab : TabItem
    {

        #region MEMBER FIELDS

        public static readonly RoutedEvent UpdatedTestFileEvent = EventManager.RegisterRoutedEvent("UpdatedTestFile", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(TabItem_UpdateTestFileTab));
        
        protected readonly string m_generatedXmlFile;
        protected List<GeneratedTestFileInfo> m_generatedTestFiles = new List<GeneratedTestFileInfo>();

        protected ListView m_listView_parsedHeaders;

        #endregion


        #region MEMBER EVENTS

        public event RoutedEventHandler UpdateTestFile
        {
            add { AddHandler(UpdatedTestFileEvent, value); }
            remove { RemoveHandler(UpdatedTestFileEvent, value); }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_UpdateTestFileTab(string generatedXmlFile)
        {
            m_generatedXmlFile = generatedXmlFile;
            GetListOfGeneratedTestFiles();
        }

        public void GetListOfGeneratedTestFiles()
        {
            m_generatedTestFiles.Clear();
            m_generatedTestFiles = CPPHeaderTestFileGenerator_Console.ProgramManager.GetListOfGeneratedFilesFromXML(m_generatedXmlFile);

            if (m_listView_parsedHeaders != null)
                m_listView_parsedHeaders.ItemsSource = m_generatedTestFiles;
        }

        #endregion

        #region Protected Functionality

        protected void RaiseUpdatedTestFileEvent()
        {
            RoutedEventArgs newEventArgs = new RoutedEventArgs(UpdatedTestFileEvent);
            RaiseEvent(newEventArgs);
        }

        #endregion

        #endregion

    }

}
