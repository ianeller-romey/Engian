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
            List<string> generatedTestFunctionNames = new List<string>();

            ////////
            // generate test file
            using (StreamWriter writer = new StreamWriter(Path.Combine(generatedTestFileInfo.TestFilePath, generatedTestFileInfo.TestFileName)))
            {
                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileIncludesAndNamespace, generatedTestFileInfo.HeaderFileName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileDictionaryPairArrayDeclaration, generatedTestFileInfo.TestName));

                generatedTestFunctionNames = GenerateListOfFunctionTestNames(generatedTestFileInfo.TestName, classes);

                foreach (string functionTestName in generatedTestFunctionNames)
                    writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileDictionaryPairInstanceDeclaration, functionTestName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileDictionaryPairArrayCloser));

                foreach (string functionTestName in generatedTestFunctionNames)
                    writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileTestFunctionDeclaration, functionTestName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileGetAndRunTestsDeclaration, generatedTestFileInfo.TestName));

                writer.Write(string.Format(stringsUsedInTestFileGeneration.TestFileCloser));
            }

            ////////
            // save backup of chassis file
            File.Copy(chassisFile, string.Format("{0}.bak", chassisFile), true);

            ////////
            // update chassis file
            string newContentsForChassisFile = "\r\n";
            newContentsForChassisFile += string.Format(stringsUsedInTestFileGeneration.ChassisFileUnitTestsComment, generatedTestFileInfo.TestName);
            newContentsForChassisFile += string.Format(stringsUsedInTestFileGeneration.ChassisFileDictionaryPairArrayDeclaration, generatedTestFileInfo.TestName);
            foreach (string testFunctionName in generatedTestFunctionNames)
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

        private static List<string> GenerateListOfFunctionTestNames(string testName, IEnumerable<ClassDefinition> classes)
        {
            List<string> testFunctionNames = new List<string>();

            foreach (ClassDefinition classDef in classes)
            {
                testFunctionNames.AddRange(GenerateListOfFunctionTestNames(testName, classDef.Classes));

                List<string> functionNames = classDef.Constructors.Select(constructorDef => (constructorDef.IsCopy) ? "CopyConstructor" : "Constructor").ToList();
                testFunctionNames.AddRange(GenerateFunctionTestNamesAndCheckForMultiples(testName, classDef.Name, functionNames));

                functionNames = classDef.Functions.Select(functionDef => functionDef.Name).ToList();
                testFunctionNames.AddRange(GenerateFunctionTestNamesAndCheckForMultiples(testName, classDef.Name, functionNames));

                functionNames = classDef.Operators.Select(operatorDef => operatorDef.TypeName).ToList();
                testFunctionNames.AddRange(GenerateFunctionTestNamesAndCheckForMultiples(testName, classDef.Name, functionNames));
            }

            return testFunctionNames;
        }

        private static List<string> GenerateFunctionTestNamesAndCheckForMultiples(string testName, string className, IEnumerable<string> functionNames)
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
