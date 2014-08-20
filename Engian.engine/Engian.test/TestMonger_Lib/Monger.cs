using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;


namespace TestMonger
{

    public static class Monger
    {

        #region MEMBER FIELDS

        private static readonly Dictionary<string, object> s_DllImportAttributeProperties =
            new KeyValuePair<string, object>[] 
            { 
                new KeyValuePair<string, object>( "CharSet", CharSet.Ansi ),
                new KeyValuePair<string, object>( "CallingConvention", CallingConvention.StdCall )
            }.ToDictionary(kv => { return kv.Key; }, kv => { return kv.Value; });

        private static readonly string s_dynamicAssemblyName = "Monger";
        private static readonly AssemblyName s_assemblyName = new AssemblyName(string.Format("Tests_{0}_Asm", s_dynamicAssemblyName));
        private static readonly AssemblyBuilder s_assemblyBuilder = AppDomain.CurrentDomain.DefineDynamicAssembly(s_assemblyName, AssemblyBuilderAccess.RunAndSave);
        private static readonly ModuleBuilder s_moduleBuilder = s_assemblyBuilder.DefineDynamicModule(s_assemblyName.Name, s_assemblyName + ".dll");

        private static List<Test> s_tests = new List<Test>();

        #endregion


        #region MEMBER PROPERTIES

        public static List<Test> Tests { get { return s_tests; } }

        #endregion


        #region MEMBER CLASSES

        public class Test
        {
            #region MEMBER PROPERTIES

            public string TestName { get; private set; }
            public Type DynamicType { get; private set; }

            #endregion


            #region MEMBER METHODS

            #region Public Functionality

            public Test(string name, Type type)
            {
                TestName = name;
                DynamicType = type;
            }

            public string[] GetTests()
            {
                MethodInfo getTests = DynamicType.GetMethod(string.Format("GetTests_{0}", TestName));

                object[] parameters = new object[] { null, null };
                getTests.Invoke(null, parameters);

                string[] allTestsManaged;
                Monger.MarshalUnmanagedStringToManagedString((IntPtr)parameters[0], (int)parameters[1], out allTestsManaged);

                return allTestsManaged;
            }

            public string[] RunTests(string[] tests)
            {
                MethodInfo runTests = DynamicType.GetMethod(string.Format("RunTests_{0}", TestName));

                object[] parameters = new object[] { tests.ToArray(), tests.Length, null };
                runTests.Invoke(null, parameters);

                string[] allResultsManaged;
                Monger.MarshalUnmanagedStringToManagedString((IntPtr)parameters[2], tests.Length, out allResultsManaged);

                return allResultsManaged;
            }

            #endregion

            #endregion

        }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        //[DllImport("Engian.test.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        //public static extern void GetTests_TestName(out IntPtr arrayOfTestNames, out int numTests);
        //[DllImport("Engian.test.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        //public static extern void RunTests_TestName(string[] testsToRun, int numTests, out IntPtr allResults);

        public static void CreateTest(string name)
        {
            TypeBuilder typeBuilder = s_moduleBuilder.DefineType(name, TypeAttributes.Public | TypeAttributes.Class);
            
            ////////
            // define DllImport attribute (unnecessary thanks to call to TypeBuilder.DefinePInvokeMethod)
            /*
            Type type_DllImportAttribute = typeof(DllImportAttribute);
            ConstructorInfo ctorInfo_DllImportAttribute = type_DllImportAttribute.GetConstructor(new Type[] { typeof(string) });
            List<FieldInfo> fieldInfo_DllImportAttribute = type_DllImportAttribute.GetFields().Where(field => s_DllImportAttributeProperties.Keys.Contains(field.Name)).ToList();
            List<object> fieldValues_DllImportAttribute = new object[fieldInfo_DllImportAttribute.Count].ToList();
            foreach (string key in s_DllImportAttributeProperties.Keys)
                fieldValues_DllImportAttribute[fieldInfo_DllImportAttribute.IndexOf(fieldInfo_DllImportAttribute.Single(prop => prop.Name == key))] = s_DllImportAttributeProperties[key];
            
            CustomAttributeBuilder customAttributeBuilder = 
                new CustomAttributeBuilder
                (
                    ctorInfo_DllImportAttribute, 
                    new object[] { "Engian.test.dll" },
                    fieldInfo_DllImportAttribute.ToArray(),
                    fieldValues_DllImportAttribute.ToArray()
                );
             */

            ////////
            // define GetTests_TestName method
            MethodBuilder getTests_methodBuilder = 
                typeBuilder.DefinePInvokeMethod
                (
                    string.Format("GetTests_{0}", name),
                    "Engian.test.dll",
                    MethodAttributes.Public | MethodAttributes.Static | MethodAttributes.PinvokeImpl,
                    CallingConventions.Standard,
                    typeof(void),
                    new Type[] { typeof(IntPtr).MakeByRefType(), typeof(int).MakeByRefType() },
                    CallingConvention.StdCall,
                    CharSet.Ansi
                );
            getTests_methodBuilder.DefineParameter(1, ParameterAttributes.Out, "arrayOfTestNames");
            getTests_methodBuilder.DefineParameter(2, ParameterAttributes.Out, "numTests");
            getTests_methodBuilder.SetImplementationFlags(getTests_methodBuilder.GetMethodImplementationFlags() | MethodImplAttributes.PreserveSig);
            
            ////////
            // define RunTests_TestName method
            MethodBuilder runTests_methodBuilder =
                typeBuilder.DefinePInvokeMethod
                (
                    string.Format("RunTests_{0}", name),
                    "Engian.test.dll",
                    MethodAttributes.Public | MethodAttributes.Static | MethodAttributes.PinvokeImpl,
                    CallingConventions.Standard,
                    typeof(void),
                    new Type[] { typeof(string[]), typeof(int), typeof(IntPtr).MakeByRefType() },
                    CallingConvention.StdCall,
                    CharSet.Ansi
                );
            runTests_methodBuilder.DefineParameter(1, ParameterAttributes.None, "testsToRun");
            runTests_methodBuilder.DefineParameter(2, ParameterAttributes.None, "numTests");
            runTests_methodBuilder.DefineParameter(3, ParameterAttributes.Out, "allResults");
            runTests_methodBuilder.SetImplementationFlags(getTests_methodBuilder.GetMethodImplementationFlags() | MethodImplAttributes.PreserveSig);

            Type t = typeBuilder.CreateType();
            s_tests.Add(new Test(name, t));
            
            ////////
            // test
            //s_assemblyBuilder.Save(s_assemblyName.Name + ".dll");
            /*
            MethodInfo m1 = t.GetMethod(string.Format("GetTests_{0}", name));
                        
            object[] parameters1 = new object[] { null, null };
            m1.Invoke(null, parameters1);

            string[] allTestsManaged;
            Monger.MarshalUnmanagedStringToManagedString((IntPtr)parameters1[0], (int)parameters1[1], out allTestsManaged);

            MethodInfo m2 = t.GetMethod(string.Format("RunTests_{0}", name));

            object[] parameters2 = new object[] { allTestsManaged, allTestsManaged.Length, null };
            m2.Invoke(null, parameters2);

            string[] allResultsManaged;
            Monger.MarshalUnmanagedStringToManagedString((IntPtr)parameters2[2], allTestsManaged.Length, out allResultsManaged);
             */
        }

        public static void MarshalUnmanagedStringToManagedString
        (
          IntPtr unmanagedStrings,
          int numUnmanagedStrings,
          out string[] managedStrings
        )
        {
            IntPtr[] intPtrArray = new IntPtr[numUnmanagedStrings];
            managedStrings = new string[numUnmanagedStrings];

            Marshal.Copy(unmanagedStrings, intPtrArray, 0, numUnmanagedStrings);

            for (int i = 0; i < numUnmanagedStrings; i++)
            {
                managedStrings[i] = Marshal.PtrToStringAnsi(intPtrArray[i]);
                Marshal.FreeCoTaskMem(intPtrArray[i]);
            }

            Marshal.FreeCoTaskMem(unmanagedStrings);
        }

        #endregion

        #endregion

    }

}
