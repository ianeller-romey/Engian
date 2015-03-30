using System;
using System.Collections.Generic;
using System.Configuration;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using CPPHeaderParser_Lib;
using CPPHeaderTestFileGenerator_Lib;


namespace CPPHeaderTestFileGenerator_Console
{

    static class CommandLineArgumentParser
    {
        #region MEMBER FIELDS

        public delegate void ParseFunction(IEnumerable<string> arguments);

        #endregion


        #region MEMBER CLASSES

        public class CommandLineArgumentInfo
        {

            #region MEMBER PROPERTIES

            public string Key { get; private set; }
            public string Description { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public CommandLineArgumentInfo(string key, string description)
            {
                Key = key;
                Description = description;
            }

            #endregion

            #endregion

        }

        #endregion


        #region MEMBER METHODS

        public static Dictionary<string, List<string>> ParseArguments(List<string> args, List<CommandLineArgumentInfo> argumentsToSearchFor)
        {
            Dictionary<string, List<string>> foundArguments = new Dictionary<string,List<string>>();
            foreach (CommandLineArgumentInfo argInfo in argumentsToSearchFor)
            {
                IEnumerable<string> argCheck = args.Where(arg => arg.First() == '-' || arg.First() == '/').Where(arg => argInfo.Key == arg.Substring(1));
                if (argCheck.Any())
                {
                    List<string> arguments = new List<string>();
                    for (int i = args.IndexOf(argCheck.First()) + 1; i < args.Count && args[i].First() != '-' && args[i].First() != '/'; ++i)
                        arguments.Add(args[i]);
                    foundArguments.Add(argInfo.Key, (arguments.Any()) ? arguments : null);
                }
            }
            return foundArguments;
        }

        #endregion

    }
    
    class Program
    {

        #region MEMBER FIELDS

        static readonly List<CommandLineArgumentParser.CommandLineArgumentInfo> c_commandLineArguments =
            new CommandLineArgumentParser.CommandLineArgumentInfo[]
            {
                new CommandLineArgumentParser.CommandLineArgumentInfo("help", "Displays all accepted command line arguments and their expected usage"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("generatedxmlfile", "Followed by the full path of the \".xml\" file used to store data on generated test files"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("headerfile", "Followed by the full path of the \".h\" file to be parsed"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("testname", "Followed by the name used to refer to the series of tests that will be generated for the provided header file"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("testfile", "Followed by the full path of the \".cpp\" file that will be generated"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("chassisfile", "Followed by the full path of the \".h\" file that contains the definition of the UnitTestChassis class used during testing")
            }.ToList();

        #endregion


        #region MEMBER METHODS

        #region Private Functionality

        static void Main(string[] args)
        {
            if (!args.Any())
            {
                DisplayHelp();
                return;
            }

            Dictionary<string, List<string>> parsedArguments = CommandLineArgumentParser.ParseArguments(args.ToList(), c_commandLineArguments);

            if (parsedArguments.ContainsKey("help")) 
                DisplayHelp();
            else if (parsedArguments.ContainsKey("generatedxmlfile") && !parsedArguments.ContainsKey("headerfile")) 
                DisplayParsedHeaders(parsedArguments["generatedxmlfile"].First());
            else if (parsedArguments.ContainsKey("headerfile") &&
                parsedArguments.ContainsKey("testname") &&
                parsedArguments.ContainsKey("testfile") &&
                parsedArguments.ContainsKey("generatedxmlfile"))
            {
                string chassisFile = (parsedArguments.ContainsKey("chassisfile")) ? parsedArguments["chassisfile"].FirstOrDefault() : null;
                ParseHeader
                (
                    parsedArguments["headerfile"].FirstOrDefault(),
                    parsedArguments["testname"].FirstOrDefault(),
                    parsedArguments["testfile"].FirstOrDefault(),
                    parsedArguments["generatedxmlfile"].FirstOrDefault(),
                    chassisFile
                );
            }
        }

        private static void DisplayHelp()
        {
            foreach (CommandLineArgumentParser.CommandLineArgumentInfo info in c_commandLineArguments)
                Console.WriteLine(string.Format("-{0}: {1}", info.Key, info.Description));
            Console.WriteLine();
        }

        private static void DisplayParsedHeaders(string generatedXmlFile)
        {
            // in case I add more properties, let's just use reflection to display all the values
            Type generatedTestFileInfoType = typeof(GeneratedTestFileInfo);
            PropertyInfo[] generatedtestFileInfoProperties = generatedTestFileInfoType.GetProperties();

            GeneratedTestFileList list = GeneratedTestFileList.Deserialize(generatedXmlFile);
            foreach (GeneratedTestFileInfo info in list.GeneratedTestFiles)
            {
                Console.Write('{');
                foreach (PropertyInfo prop in generatedtestFileInfoProperties)
                    Console.WriteLine(string.Format("{0}: {1}", prop.Name, prop.GetValue(info)));
                Console.Write('}');
                Console.WriteLine();
            }
        }

        private static void ParseHeader(string headerFile, string testName, string testFile, string generatedXmlFile, string chassisFile)
        {
            GeneratedTestFileInfo info =
                new GeneratedTestFileInfo
                (
                    Path.GetFileName(headerFile),
                    Path.GetDirectoryName(headerFile),
                    testName,
                    Path.GetFileName(testFile),
                    Path.GetDirectoryName(testFile)
                );

            if (!string.IsNullOrEmpty(chassisFile))
            {
                TestFileGenerator.StringsUsedInTestFileGeneration strings = new TestFileGenerator.StringsUsedInTestFileGeneration();
                {
                    Type stringsType = strings.GetType();
                    foreach (PropertyInfo property in stringsType.GetProperties())
                        property.SetValue(strings, TestFileGenerator.UnescapeCodes(ConfigurationManager.AppSettings[string.Format("{0}_{1}", stringsType.Name, property.Name)]));
                }
                List<ClassDefinition> classes = CPPParser.Parse(headerFile);
                TestFileGenerator.GenerateTestFileAndUpdateChassisFile(info, strings, classes, chassisFile);
            }

            GeneratedTestFileList list = GeneratedTestFileList.Deserialize(generatedXmlFile);
            list.GeneratedTestFiles.Add(info);
            GeneratedTestFileList.Serialize(list, generatedXmlFile);
        }

        #endregion

        #endregion

    }

    public static class ProgramManager
    {

        #region MEMBER METHODS

        #region Public Functionality

        public static List<GeneratedTestFileInfo> GetListOfGeneratedFilesFromXML(string generatedXmlFile)
        {
            List<GeneratedTestFileInfo> generatedTestFiles = new List<GeneratedTestFileInfo>();

            ProcessStartInfo processStartInfo =
                new ProcessStartInfo("CPPHeaderTestFileGenerator_Console.exe", string.Format("-generatedxmlfile \"{0}\"", generatedXmlFile))
                {
                    UseShellExecute = false,
                    RedirectStandardOutput = true
                };
            Process testFileGenerator = Process.Start(processStartInfo);
            string output = testFileGenerator.StandardOutput.ReadToEnd();
            testFileGenerator.WaitForExit();

            Type generatedTestFileInfoType = typeof(GeneratedTestFileInfo);
            PropertyInfo[] generatedtestFileInfoProperties = generatedTestFileInfoType.GetProperties();
            foreach (Match m in Regex.Matches(output, @"(?<=\{)[^}]+(?=\})", RegexOptions.Singleline))
            {
                GeneratedTestFileInfo info = new GeneratedTestFileInfo();
                foreach (Match mm in Regex.Matches(m.Value, @"(?<property>\w+): (?<value>.+)"))
                {
                    string
                        property = mm.Groups["property"].Value.Trim(),
                        value = mm.Groups["value"].Value.Trim();
                    PropertyInfo prop = generatedtestFileInfoProperties.Single(p => p.Name == property);
                    prop.SetValue(info, value);
                }
                generatedTestFiles.Add(info);
            }

            return generatedTestFiles;
        }

        #endregion

        #endregion

    }

}
