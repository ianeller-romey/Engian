using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    public class CPPParser
    {

        #region MEMBER FIELDS

        private static string
            m_regexClass = @"(?<template>template\s*<\s*(?<template_types>((typename)|(class))\s*[\w,\s]*\w)\s*>)*\s*class\s+(?<name>\w+)\s*(:\s*(?<base_classes>[a-zA-Z].+)\s*)*(?={)",
            m_regexConstructor = @"(?<!~){0}(\(\)|\((?<parameters>( [a-zA-Z0-9_<> \*&:,\r\n]+ ))\))",
            m_regexFunction = @"(?<is_virtual>virtual )*(?<return_value>(const )*[a-zA-Z_][a-zA-Z0-9_<>&\* ,]*( const)*) (?<name>[a-zA-Z_][a-zA-Z0-9_]*)(\(\)|\((?<parameters>( [a-zA-Z0-9_<> \*&:,\r\n]+ ))\))",
            m_regexOperator = @"(?<is_virtual>virtual )*(?<return_value>(const )*[a-zA-Z_][a-zA-Z0-9_<>&\* ,]*( const)*) operator\s*(?<type>[=\+\-\*/%!<>&\|\(\)\[\]~\^a-zA-Z0-9_]+)\s*(\(\)|\((?<parameters>( [a-zA-Z0-9_<> \*&:,\r\n]+ ))\))",
            m_regexPointer = @"(\*(?!\s*const))|(\*\s*const)";
        
        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public static List<ClassDefinition> Parse(string fileName)
        {
            List<ClassDefinition> classes = new List<ClassDefinition>();
            string fileContents = File.ReadAllText(fileName);

            foreach (Match m in Regex.Matches(fileContents, m_regexClass))
            {
                string classText = ParseClassText(fileContents, m.Value);

                ClassDefinition classDef = new ClassDefinition();
                GetClassIdentity(ref classDef, m);
                GetClassContents(ref classDef, classText);

                classes.Add(classDef);
            }

            // remove any duplicate entries (which would essentially be member classes)
            // from the list
            for (int i = 0; i < classes.Count; ++i)
            {
                for (int j = 0; j < classes.Count; ++j)
                {
                    if (j == i) continue;
                    if (IsThisClassAMemberClass(classes[i], classes[j]))
                    {
                        classes.RemoveAt(j);
                        --i;
                        break;
                    }
                }
            }
            return classes;
        }

        #endregion


        #region Private Functionality

        private static bool IsThisClassAMemberClass(ClassDefinition doesThisClassContainTheOtherOne, ClassDefinition isThisClassContainedByTheOtherOne)
        {
            if (doesThisClassContainTheOtherOne.Equals(isThisClassContainedByTheOtherOne))
                return true;
            foreach (ClassDefinition c in doesThisClassContainTheOtherOne.Classes)
                if (IsThisClassAMemberClass(c, isThisClassContainedByTheOtherOne))
                    return true;
            return false;
        }

        private static void GetClassContents(ref ClassDefinition classDef, string classText)
        {
            string unparsedClassText = classText;

            ////////
            // get member classes
            foreach (Match m in Regex.Matches(classText, m_regexClass))
            {
                string subClassText = ParseClassText(classText, m.Value);
                unparsedClassText = unparsedClassText.Replace(subClassText, string.Empty);

                ClassDefinition subClassDef = new ClassDefinition();
                GetClassIdentity(ref subClassDef, m);
                GetClassContents(ref subClassDef, subClassText);

                classDef.Classes.Add(subClassDef);
            }

            ////////
            // remove function bodies defined in header
            while (unparsedClassText.Count(x => x == '{') > 1 && unparsedClassText.Count(x => x == '}') > 1)
            {
                int
                    openBracket = unparsedClassText.IndexOf('{', 1),
                    closeBracket = unparsedClassText.IndexOf('}', openBracket);
                unparsedClassText = unparsedClassText.Replace(unparsedClassText.Substring(openBracket, closeBracket - openBracket + 1), ";");
            }

            ////////
            // parse functions
            foreach (Match m in Regex.Matches(unparsedClassText, m_regexFunction))
            {
                if (m.Groups["return_value"].Value == "return")
                    continue;
                FunctionDefinition funcDef = new FunctionDefinition();
                funcDef.IsVirtual = m.Groups["is_virtual"].Value != string.Empty;
                funcDef.Name = m.Groups["name"].Value;
                funcDef.Parameters = ParseParameters(m.Groups["parameters"].Value);
                funcDef.ReturnValue = ParseReturnValue(m.Groups["return_value"].Value);
                classDef.Functions.Add(funcDef);
            }

            ////////
            // parse operators
            foreach (Match m in Regex.Matches(unparsedClassText, m_regexOperator))
            {
                OperatorDefinition operatorDef = new OperatorDefinition();
                operatorDef.IsVirtual = m.Groups["is_virtual"].Value != string.Empty;
                operatorDef.Parameters = ParseParameters(m.Groups["parameters"].Value);
                operatorDef.ReturnValue = ParseReturnValue(m.Groups["return_value"].Value);
                string operatorType = m.Groups["type"].Value;
                // check for conversion operator
                if (!OperatorDefinition.OperatorTypeRepresentations.Values.Any(value => value == operatorType))
                    operatorDef.Type = OperatorDefinition.OperatorType.Conversion;
                // check for duplicate symbols
                else if (OperatorDefinition.OperatorTypeRepresentations.Values.Count(value => value == operatorType) > 1)
                {
                    if (operatorType == "+")
                        operatorDef.Type = (operatorDef.Parameters.Any()) ? OperatorDefinition.OperatorType.Addition : OperatorDefinition.OperatorType.UnaryPlus;
                    else if (operatorType == "-")
                        operatorDef.Type = (operatorDef.Parameters.Any()) ? OperatorDefinition.OperatorType.Subtraction : OperatorDefinition.OperatorType.UnaryMinus;
                    else if (operatorType == "*")
                        operatorDef.Type = (operatorDef.Parameters.Any()) ? OperatorDefinition.OperatorType.Multiplication : OperatorDefinition.OperatorType.Indirection;
                    else if (operatorType == "++")
                        operatorDef.Type = (operatorDef.Parameters.Any()) ? OperatorDefinition.OperatorType.PostfixIncrement : OperatorDefinition.OperatorType.PrefixIncrement;
                    else if (operatorType == "--")
                        operatorDef.Type = (operatorDef.Parameters.Any()) ? OperatorDefinition.OperatorType.PostfixDecrement : OperatorDefinition.OperatorType.PrefixDecrement;
                    else
                        throw new ArgumentException("Unintended duplicate operator symbol used", "operatorType");
                }
                else
                    operatorDef.Type = OperatorDefinition.OperatorTypeRepresentations.Single(kv => kv.Value == operatorType).Key;
                classDef.Operators.Add(operatorDef);
            }

            ////////
            // parse constructors
            foreach(Match m in Regex.Matches(unparsedClassText, string.Format(m_regexConstructor, classDef.Name), RegexOptions.Singleline))
            {
                ConstructorDefinition constDef = new ConstructorDefinition();
                constDef.Parameters = ParseParameters(m.Groups["parameters"].Value);
                if(constDef.Parameters.Count == 1)
                {
                    ParameterDefinition param = constDef.Parameters.Single();
                    constDef.IsCopy =
                        param.IsReference &&
                        param.IsConst;
                    if (classDef.TemplateTypes.Any() && param.Type.Contains('<') && param.Type.Contains('>'))
                    {
                        int
                            startOfTemplateTypes = param.Type.LastIndexOf('<') + 1,
                            endOfTemplateTypes = param.Type.LastIndexOf('>');
                        string[] paramTemplateTypes = param.Type.Substring(startOfTemplateTypes, endOfTemplateTypes - startOfTemplateTypes).Split(new char[] { ',', ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        constDef.IsCopy = constDef.IsCopy && !paramTemplateTypes.Except(classDef.TemplateTypes).Any();
                    }
                    else
                        constDef.IsCopy = constDef.IsCopy && param.Type == classDef.Name;

                }
                constDef.Class = classDef.Name;
                classDef.Constructors.Add(constDef);
            }
        }

        private static void GetClassIdentity(ref ClassDefinition classDef, Match classMatch)
        {
            classDef.Name = classMatch.Groups["name"].Value;
            if (classMatch.Groups["template"].Value != string.Empty)
            {
                List<string> templateTypes = classMatch.Groups["template_types"].Value.Split(new char[] { ',', ' ' }, StringSplitOptions.RemoveEmptyEntries).ToList();
                templateTypes.RemoveAll(str => str == "typename");
                templateTypes.RemoveAll(str => str == "class");
                classDef.TemplateTypes.AddRange(templateTypes);
            }
            if (classMatch.Groups["base_classes"].Value != string.Empty)
            {
                List<string> baseClasses = classMatch.Groups["base_classes"].Value.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Select(str => str.Trim()).ToList();
                classDef.BaseClasses.AddRange(baseClasses);
            }
        }

        private static string ParseClassText(string text, string classIdentity)
        {
            int
                startOfClass = text.IndexOf(classIdentity),
                endOfClass;
            startOfClass = text.IndexOf('{', startOfClass);
            int numberOfBrackets = 1;
            for (endOfClass = startOfClass + 1; numberOfBrackets > 0; ++endOfClass)
            {
                if (text[endOfClass] == '{') ++numberOfBrackets;
                else if (text[endOfClass] == '}') --numberOfBrackets;
            }

            return text.Substring(startOfClass, endOfClass - startOfClass);
        }

        private static List<ParameterDefinition> ParseParameters(string paramsText)
        {
            List<ParameterDefinition> paramDefs = new List<ParameterDefinition>();

            foreach (string paramText in paramsText.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries))
            {
                ParameterDefinition paramDefinition = ParseParameter(paramText.Trim());
                paramDefs.Add(paramDefinition);
            }

            return paramDefs;
        }

        private static ParameterDefinition ParseParameter(string paramText)
        {
            ParameterDefinition paramDef = new ParameterDefinition();

            GetValueIdentity(ref paramDef, ref paramText);            
            // if it's not a return value, we can assume that the parameter has a specific name
            string[] paramsDivided = paramText.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            paramDef.Type = paramsDivided.Take(paramsDivided.Length - 1).Aggregate((x, y) => x + y);
            paramDef.Name = paramsDivided.Last();

            return paramDef;
        }

        private static ReturnValueDefinition ParseReturnValue(string returnText)
        {
            ReturnValueDefinition returnDef = new ReturnValueDefinition();

            GetValueIdentity(ref returnDef, ref returnText);
            // if it is a return value, the name is just the same as the type
            returnDef.Type = returnText.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries).Aggregate((x, y) => x + y);

            return returnDef;
        }

        private static void GetValueIdentity<T>(ref T valueDef, ref string valueText) where T : IValueType
        {
            // pointer
            if (valueText.Contains('*'))
            {
                List<ParameterPointerDefinition> paramPointers = new List<ParameterPointerDefinition>();
                Match m;
                while ((m = Regex.Match(valueText, m_regexPointer)).Value != string.Empty)
                {
                    paramPointers.Add(new ParameterPointerDefinition() { IsConst = m.Value.Contains("const") });
                    valueText = valueText.Remove(m.Index, m.Length);
                }
                valueDef.PointerDepth = paramPointers;
            }
            // or reference?
            else if (valueText.Contains('&'))
            {
                valueDef.IsReference = true;
                valueText = valueText.Replace("&", string.Empty);
            }

            // const value?
            if (valueText.Contains("const"))
            {
                valueDef.IsConst = true;
                valueText = valueText.Replace("const", string.Empty);
            }
        }

        #endregion

        #endregion
    }
}
