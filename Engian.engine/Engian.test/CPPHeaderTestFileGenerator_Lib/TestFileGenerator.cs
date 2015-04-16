using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CPPHeaderParser_Lib;


namespace CPPHeaderTestFileGenerator_Lib
{

    public static class TestFileGenerator
    {

        #region MEMBER CLASSES

        public class StringsUsedInTestFileGeneration
        {
            public string TestFileIncludesAndNamespace { get; set; }
            public string TestFileDictionaryPairArrayDeclaration { get; set; }
            public string TestFileDictionaryPairInstanceDeclaration { get; set; }
            public string TestFileDictionaryPairArrayCloser { get; set; }
            public string TestFileTestFunctionDeclaration { get; set; }
            public string TestFileGetAndRunTestsDeclaration { get; set; }
            public string TestFileCloser { get; set; }
            public string TestFileHelperDefines { get; set; }
            public string TestFileHelperNamespaceAndClassToBeTested { get; set; }
            public string TestFileHelperClassDeclaration { get; set; }
            public string TestFileHelperFunctionDeclaration { get; set; }
            public string TestFileHelperCloser { get; set; }
            public string ChassisFileUnitTestsComment { get; set; }
            public string ChassisFileDictionaryPairArrayDeclaration { get; set; }
            public string ChassisFileTestFunctionDeclaration { get; set; }
            public string ChassisFileUnitTestsCloser { get; set; }
            public string ChassisFileEndOfUnitTestFunctions { get; set; }
        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public static string UnescapeCodes(string src)
        {
            src = src.Replace("\\r", "\r");
            src = src.Replace("\\n", "\n");
            src = src.Replace("\\t", "\t");
            return src;
        }

        public static void GenerateTestFileAndUpdateChassisFile
        (
            GeneratedTestFileInfo generatedTestFileInfo,
            StringsUsedInTestFileGeneration stringsUsedInTestFileGeneration,
            List<ClassDefinition> classes,
            string chassisFile
        )
        {
            Dictionary<string, string>
                generatedTestFunctionNames = GenerateListOfTestFunctionAndHelperNames(generatedTestFileInfo.TestName, classes);
            string testHelperName = Path.GetFileNameWithoutExtension(generatedTestFileInfo.HeaderFileName);
            testHelperName =
                string.Format
                (
                    "TestHelper_{0}{1}",
                    char.ToUpper(testHelperName.First()),
                    new string(testHelperName.Skip(1).ToArray())
                );

            ////////
            // generate test file
            using (StreamWriter writer = new StreamWriter(Path.Combine(generatedTestFileInfo.TestFilePath, generatedTestFileInfo.TestFileName)))
            {
                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileIncludesAndNamespace, generatedTestFileInfo.HeaderFileName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileDictionaryPairArrayDeclaration, generatedTestFileInfo.TestName));
                
                foreach (string functionTestName in generatedTestFunctionNames.Keys)
                    writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileDictionaryPairInstanceDeclaration, functionTestName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileDictionaryPairArrayCloser));

                foreach (string functionTestName in generatedTestFunctionNames.Keys)
                    writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileTestFunctionDeclaration, functionTestName, testHelperName, generatedTestFunctionNames[functionTestName]));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileGetAndRunTestsDeclaration, generatedTestFileInfo.TestName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileCloser));
            }

            ////////
            // generate test file helper header
            using(StreamWriter writer = new StreamWriter(Path.Combine(generatedTestFileInfo.TestFilePath, string.Format("test{0}.h", testHelperName))))
            {
                writer.Write(string.Format("#ifndef TEST_TESTHELPER_{0}_H\r\n#define TEST_TESTHELPER_{0}_H\r\n\r\n", Path.GetFileNameWithoutExtension(generatedTestFileInfo.HeaderFileName).ToUpper()));

                writer.Write("namespace ClassNamespace\r\n{\r\n  class ClassName;\r\n}\r\n");

                writer.Write("\r\n\r\n");

                writer.Write(string.Format("namespace Test\r\n{{\r\n\r\n  class {0}\r\n  {{\r\n    public:\r\n\r\n", testHelperName));

                foreach (string testFunctionHelperName in generatedTestFunctionNames.Values)
                    writer.Write(string.Format("      static unsigned const {0}( char const * const name );\r\n", testFunctionHelperName));

                writer.Write("  };\r\n\r\n}\r\n\r\n#endif\r\n");
            }

            ////////
            // generate test file cpp
            using (StreamWriter writer = new StreamWriter(Path.Combine(generatedTestFileInfo.TestFilePath, string.Format("test{0}.cpp", testHelperName))))
            {
                writer.Write(string.Format("\r\n#include \"test{0}.h\"\r\n\r\n#include \"{1}\"\r\n\r\n\r\n", testHelperName, generatedTestFileInfo.HeaderFileName));

                writer.Write("#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;\r\n\r\n\r\n");

                writer.Write("namespace Test\r\n{\r\n");

                foreach (string testFunctionHelperName in generatedTestFunctionNames.Values)
                    writer.Write(string.Format("\r\n  unsigned const {0}::{1}()\r\n  {{\r\n    return 0;\r\n  }}\r\n\r\n", testHelperName, testFunctionHelperName));

                writer.Write("}\r\n");
            }

            ////////
            // save backup of chassis file
            File.Copy(chassisFile, string.Format("{0}.bak", chassisFile), true);

            ////////
            // update chassis file
            string newContentsForChassisFile = "\r\n";
            newContentsForChassisFile += string.Format(stringsUsedInTestFileGeneration.ChassisFileUnitTestsComment, generatedTestFileInfo.TestName);
            newContentsForChassisFile += string.Format(stringsUsedInTestFileGeneration.ChassisFileDictionaryPairArrayDeclaration, generatedTestFileInfo.TestName);
            foreach (string testFunctionName in generatedTestFunctionNames.Keys)
                newContentsForChassisFile += string.Format(stringsUsedInTestFileGeneration.ChassisFileTestFunctionDeclaration, testFunctionName);
            newContentsForChassisFile += string.Format(stringsUsedInTestFileGeneration.ChassisFileUnitTestsCloser);

            string chassisFileContents = string.Empty;
            using(StreamReader reader = new StreamReader(chassisFile))
            {
                chassisFileContents = reader.ReadToEnd();
            }

            chassisFileContents = chassisFileContents.Insert(chassisFileContents.IndexOf(stringsUsedInTestFileGeneration.ChassisFileEndOfUnitTestFunctions), newContentsForChassisFile);

            using (StreamWriter writer = new StreamWriter(chassisFile, false))
            {
                writer.Write(chassisFileContents);
            }
        }

        #endregion


        #region Private Functionality

        private static Dictionary<string, string> GenerateListOfTestFunctionAndHelperNames(string testName, IEnumerable<ClassDefinition> classes)
        {
            Dictionary<string, string> testFunctionNames = new Dictionary<string, string>();

            foreach (ClassDefinition classDef in classes)
            {
                Dictionary<string, string> subTestFunctionNames = GenerateListOfTestFunctionAndHelperNames(testName, classDef.Classes);
                foreach (string subKey in subTestFunctionNames.Keys)
                    testFunctionNames.Add(subKey, subTestFunctionNames[subKey]);

                List<string> functionNames = classDef.Constructors.Select(constructorDef => (constructorDef.IsCopy) ? "CopyConstructor" : "Constructor").ToList();
                foreach (string testFunctionName in GenerateTestFunctionNamesAndCheckForMultiples(testName, classDef.Name, functionNames).ToList())
                    testFunctionNames.Add(testFunctionName, GenerateTestFunctionHelperName(testFunctionName));

                functionNames = classDef.Functions.Select(functionDef => functionDef.Name).ToList();
                foreach (string testFunctionName in GenerateTestFunctionNamesAndCheckForMultiples(testName, classDef.Name, functionNames).ToList())
                    testFunctionNames.Add(testFunctionName, GenerateTestFunctionHelperName(testFunctionName));

                functionNames = classDef.Operators.Select(operatorDef => operatorDef.TypeName).ToList();
                foreach (string testFunctionName in GenerateTestFunctionNamesAndCheckForMultiples(testName, classDef.Name, functionNames).ToList())
                    testFunctionNames.Add(testFunctionName, GenerateTestFunctionHelperName(testFunctionName));
            }

            return testFunctionNames;
        }

        private static string GenerateTestFunctionHelperName(string generatedTestFunction)
        {
            return new string(generatedTestFunction.Skip(generatedTestFunction.IndexOf('_') + 1).ToArray());
        }

        private static List<string> GenerateTestFunctionNamesAndCheckForMultiples(string testName, string className, IEnumerable<string> functionNames)
        {
            List<string> testFunctionNames = new List<string>();

            foreach (string functionName in functionNames.Distinct())
            {
                int numFunctionsByThatName = functionNames.Count(f => f == functionName);
                if (numFunctionsByThatName > 1)
                {
                    for (int i = 0; i < numFunctionsByThatName; ++i)
                        testFunctionNames.Add(string.Format("{0}_{1}_{2}{3}", testName, className, functionName, i));
                }
                else
                    testFunctionNames.Add(string.Format("{0}_{1}_{2}", testName, className, functionName));
            }

            return testFunctionNames;
        }

        #endregion

        #endregion

    }

}
