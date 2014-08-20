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

using CPPHeaderTestFileGenerator_Lib;

using TestMonger_Console;


namespace TestManager
{

    public class TabItem_TestMonger : TabItem
    {

        #region MEMBER FIELDS

        readonly string m_generatedXmlFile;
        List<string> m_testUmbrellas = new List<string>();

        TabControl m_tabControl_testLists;
        Window m_parent;

        #endregion
        

        #region MEMBER METHODS

        #region Public Functionality

        public TabItem_TestMonger(string generatedXmlFile, Window parent)
        {
            m_generatedXmlFile = generatedXmlFile;

            GetListOfTestUmbrellas();
            CreateControls();
        }

        #endregion


        #region Private Functionality

        private void CreateControls()
        {
            m_tabControl_testLists = new TabControl();
            foreach (string testUmbrella in m_testUmbrellas)
                AddTestUmbrella(testUmbrella);

            Content = m_tabControl_testLists;
        }

        private void AddTestUmbrella(string testUmbrella)
        {
            TabItem_TestUmbrella testList = new TabItem_TestUmbrella(testUmbrella, m_parent);
            m_tabControl_testLists.Items.Add(testList);
        }

        private void GetListOfTestUmbrellas()
        {
            m_testUmbrellas.Clear();
            m_testUmbrellas = TestMonger_Console.ProgramManager.GetListOfTestUmbrellasFromXML(m_generatedXmlFile);
        }

        #endregion

        #endregion

    }

}
