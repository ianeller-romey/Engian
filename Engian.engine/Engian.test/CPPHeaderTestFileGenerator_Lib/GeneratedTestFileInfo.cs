
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace CPPHeaderTestFileGenerator_Lib
{

    [XmlType("GeneratedTestFile")]
    public class GeneratedTestFileInfo
    {

        #region MEMBER PROPERTIES

        [XmlAttribute("HeaderFileName", DataType = "string")]
        public string HeaderFileName { get; set; }

        [XmlAttribute("HeaderFilePath", DataType = "string")]
        public string HeaderFilePath { get; set; }

        [XmlAttribute("TestName", DataType = "string")]
        public string TestName { get; set; }

        [XmlAttribute("TestFileName", DataType = "string")]
        public string TestFileName { get; set; }

        [XmlAttribute("TestFilePath", DataType = "string")]
        public string TestFilePath { get; set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public GeneratedTestFileInfo()
        {
        }

        public GeneratedTestFileInfo(string headerFileName, string headerFilePath, string testName, string testFileName, string testFilePath)
        {
            HeaderFileName = headerFileName;
            HeaderFilePath = headerFilePath;
            TestName = testName;
            TestFileName = testFileName;
            TestFilePath = testFilePath;
        }

        public override string ToString()
        {
            return this.GetType().GetProperties().Select(prop => string.Format("{0}='{1}'", prop.Name, prop.GetValue(this))).Aggregate((x, y) => string.Format("{0}, {1}", x, y));
        }

        #endregion


        #region Private Functionality

        #endregion

        #endregion

    }

    [XmlRoot("GeneratedTestFileList")]
    [XmlInclude(typeof(GeneratedTestFileInfo))]
    public class GeneratedTestFileList
    {

        #region MEMBER FIELDS

        [XmlArray("GeneratedTestFiles")]
        [XmlArrayItem("GeneratedTestFile")]
        public ObservableCollection<GeneratedTestFileInfo> GeneratedTestFiles = new ObservableCollection<GeneratedTestFileInfo>();

        private static readonly XmlSerializer s_serializer = new XmlSerializer(typeof(GeneratedTestFileList), new Type[] { typeof(GeneratedTestFileList) });

        #endregion


        #region MEMBER METHODS

        #region Private Functionality

        public static GeneratedTestFileList Deserialize(string fileName)
        {
            GeneratedTestFileList GeneratedTestFileList = null;
            if (File.Exists(fileName))
            {
                using (FileStream file = new FileStream(fileName, FileMode.Open))
                {
                    GeneratedTestFileList = (GeneratedTestFileList)s_serializer.Deserialize(file);
                }
            }
            else
                GeneratedTestFileList = new GeneratedTestFileList();
            return GeneratedTestFileList;
        }

        public static void Serialize(GeneratedTestFileList GeneratedTestFileList, string fileName)
        {
            using (FileStream file = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                s_serializer.Serialize(file, GeneratedTestFileList);
            }
        }

        #endregion


        #region Private Functionality

        private GeneratedTestFileList()
        {
        }

        #endregion

        #endregion

    }

}
