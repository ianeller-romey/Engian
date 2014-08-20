using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using CPPHeaderTestFileGenerator_Lib;

using TestMonger;


namespace TestMonger_Console
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
            Dictionary<string, List<string>> foundArguments = new Dictionary<string, List<string>>();
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
                new CommandLineArgumentParser.CommandLineArgumentInfo("generatedxmlfile", "Followed by the full path of the \".xml\" file used to store data on generated test files; this parameter is necessary for all commands"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("gettestumbrellas", "Returns a list of all test umbrellas present in the provided \".xml\" file"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("gettestsunderumbrellas", "All the tests under all the umbrellas within the provided \".xml\" file will be returned"),
                new CommandLineArgumentParser.CommandLineArgumentInfo("runtestsunderumbrellas", "All the tests under all the umbrellas within the provided \".xml\" file will be run")
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

            if (parsedArguments.ContainsKey("help") || !parsedArguments.ContainsKey("generatedxmlfile"))
            {
                DisplayHelp();
                return;
            }

            string generatedXmlFile = parsedArguments["generatedxmlfile"].First();
            GeneratedTestFileList list = GeneratedTestFileList.Deserialize(generatedXmlFile);

            if (parsedArguments.ContainsKey("gettestumbrellas"))
                GetTestUmbrellas(list);
            else if (parsedArguments.ContainsKey("gettestsunderumbrellas"))
                GetTestsUnderUmbrellas(list);
            else if (parsedArguments.ContainsKey("runtestsunderumbrellas"))
                RunTestsUnderUmbrellas(list);
        }

        private static void DisplayHelp()
        {
            foreach (CommandLineArgumentParser.CommandLineArgumentInfo info in c_commandLineArguments)
                Console.WriteLine(string.Format("-{0}: {1}", info.Key, info.Description));
            Console.WriteLine();
        }

        private static void GetTestUmbrellas(GeneratedTestFileList list)
        {
            Console.Write('{');
            if (list.GeneratedTestFiles.Any())
                Console.Write(list.GeneratedTestFiles.Select(g => g.TestName).Aggregate((x, y) => string.Format("{0}, {1}", x, y)));
            Console.WriteLine('}');
            Console.WriteLine();
        }

        private static void GetTestsUnderUmbrellas(GeneratedTestFileList list)
        {
            foreach (string umbrella in list.GeneratedTestFiles.Select(gtf => gtf.TestName))
                Monger.CreateTest(umbrella);

            foreach (Monger.Test test in Monger.Tests)
            {
                Console.Write(string.Format("{0}:", test.TestName));
                Console.Write('{');
                Console.Write(test.GetTests().Aggregate((x, y) => string.Format("{0}, {1}", x, y)));
                Console.WriteLine('}');
                Console.WriteLine();
            }
        }

        private static void RunTestsUnderUmbrellas(GeneratedTestFileList list)
        {
            foreach (string umbrella in list.GeneratedTestFiles.Select(gtf => gtf.TestName))
                Monger.CreateTest(umbrella);

            foreach (Monger.Test test in Monger.Tests)
            {
                string[] output = test.RunTests(test.GetTests());
                Console.WriteLine(string.Format("{0}:", test.TestName));
                Console.WriteLine('{');
                foreach (string result in output)
                    Console.WriteLine(string.Format("[{0}]", result));
                Console.WriteLine('}');
                Console.WriteLine();
            }
        }

        #endregion

        #endregion

    }

    public static class ProgramManager
    {

        #region MEMBER METHODS

        #region Public Functionality

        public static List<string> GetListOfTestUmbrellasFromXML(string generatedXmlFile)
        {
            List<string> umbrellas = new List<string>();

            ProcessStartInfo processStartInfo =
                new ProcessStartInfo("TestMonger_Console.exe", string.Format("-generatedxmlfile \"{0}\" -gettestumbrellas", generatedXmlFile))
                {
                    UseShellExecute = false,
                    RedirectStandardOutput = true
                };
            Process testMonger = Process.Start(processStartInfo);
            string output = testMonger.StandardOutput.ReadToEnd();
            testMonger.WaitForExit();

            foreach (Match m in Regex.Matches(output, @"(?<=\{)[^}]+(?=\})", RegexOptions.Singleline))
                umbrellas.AddRange(m.Value.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Select(str => str.Trim()));

            return umbrellas;
        }

        public static Dictionary<string, List<string>> GetListOfTestsUnderUmbrellasFromXML(string generatedXmlFile)
        {
            Dictionary<string, List<string>> testsUnderUmbrellas = new Dictionary<string, List<string>>();

            ProcessStartInfo processStartInfo =
                new ProcessStartInfo("TestMonger_Console.exe", string.Format("-generatedxmlfile \"{0}\" -gettestsunderumbrellas", generatedXmlFile))
                {
                    UseShellExecute = false,
                    RedirectStandardOutput = true
                };
            Process testMonger = Process.Start(processStartInfo);
            string output = testMonger.StandardOutput.ReadToEnd();
            testMonger.WaitForExit();

            foreach (Match m in Regex.Matches(output, @"(?<umbrella>\w+):\{(?<tests>[^}]+)\}\r\n"))
                testsUnderUmbrellas.Add(m.Groups["umbrella"].Value, m.Groups["tests"].Value.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Select(str => str.Trim()).ToList());


            return testsUnderUmbrellas;
        }

        public static Dictionary<string, List<string>> RunListOfTestsUnderUmbrellasFromXML(string generatedXmlFile)
        {
            Dictionary<string, List<string>> testsUnderUmbrellas = new Dictionary<string, List<string>>();

            ProcessStartInfo processStartInfo =
                new ProcessStartInfo("TestMonger_Console.exe", string.Format("-generatedxmlfile \"{0}\" -runtestsunderumbrellas", generatedXmlFile))
                {
                    UseShellExecute = false,
                    RedirectStandardOutput = true
                };
            Process testMonger = Process.Start(processStartInfo);
            string output = testMonger.StandardOutput.ReadToEnd();
            testMonger.WaitForExit();

            foreach (Match m in Regex.Matches(output, @"(?<umbrella>\w+):\r\n\{(?<results>.+)\}(?=\r\n\r\n)", RegexOptions.Singleline))
                testsUnderUmbrellas.Add(m.Groups["umbrella"].Value, Regex.Matches(m.Groups["results"].Value, @"\[(?<result>TEST \{.+\}\r\nin FILE \{.+\}\r\nat LINE \{.+\}\r\nfailed:\r\n.+)\]\r\n").OfType<Match>().Select(mm => mm.Groups["result"].Value).ToList());

            return testsUnderUmbrellas;
        }

        #endregion

        #endregion

    }

}
