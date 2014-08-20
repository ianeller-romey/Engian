using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace CPPHeaderParser_Lib
{
    public class ClassDefinition : IEquatable<ClassDefinition>
    {
        public string Name { get; set; }
        public List<string> TemplateTypes { get; set; }
        public List<string> BaseClasses { get; set; }
        public List<FunctionDefinition> Functions { get; set; }
        public List<OperatorDefinition> Operators { get; set; }
        public List<ConstructorDefinition> Constructors { get; set; }
        public List<ClassDefinition> Classes { get; set; }

        public ClassDefinition()
        {
            TemplateTypes = new List<string>();
            BaseClasses = new List<string>();
            Functions = new List<FunctionDefinition>();
            Operators = new List<OperatorDefinition>();
            Constructors = new List<ConstructorDefinition>();
            Classes = new List<ClassDefinition>();
        }

        static public bool operator ==(ClassDefinition one, ClassDefinition two)
        {
            return one.Equals(two);
        }

        static public bool operator !=(ClassDefinition one, ClassDefinition two)
        {
            return !one.Equals(two);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            ClassDefinition other = obj as ClassDefinition;
            return (other == null) ? false : Equals(other);
        }

        public bool Equals(ClassDefinition other)
        {
            return
                other.Name == Name &&
                !other.TemplateTypes.Except(TemplateTypes).Any() &&
                !other.BaseClasses.Except(BaseClasses).Any() &&
                !other.Functions.Except(Functions).Any() &&
                !other.Operators.Except(Operators).Any() &&
                !other.Constructors.Except(Constructors).Any() &&
                !other.Classes.Except(Classes).Any();
        }

        public override int GetHashCode()
        {
            int
                nameHashCode = Name.GetHashCode(),
                templateTypesHashCode = TemplateTypes.GetHashCode(),
                baseClassesHashCode = BaseClasses.GetHashCode(),
                functionsHashCode = 1,
                operatorsHashCode = 1,
                constructorsHashCode = 1,
                classesHashCode = 1;
            foreach (FunctionDefinition f in Functions)
                functionsHashCode ^= f.GetHashCode();
            foreach (OperatorDefinition o in Operators)
                operatorsHashCode ^= o.GetHashCode();
            foreach (ConstructorDefinition c in Constructors)
                constructorsHashCode ^= c.GetHashCode();
            foreach (ClassDefinition c in Classes)
                classesHashCode ^= c.GetHashCode();
            return nameHashCode ^ templateTypesHashCode ^ baseClassesHashCode ^ functionsHashCode ^ operatorsHashCode ^ constructorsHashCode ^ classesHashCode;
        }

        public override string ToString()
        {
            string
                templateTypesString = (TemplateTypes.Any()) ? string.Format("template< typename {0} >\r\n", TemplateTypes.Aggregate((x, y) => string.Format("{0}, {1}", x, y))) : string.Empty,
                baseClassesString = (BaseClasses.Any()) ? BaseClasses.Aggregate((x, y) => string.Format("{0}, {1}", x, y)) : string.Empty,
                constructorsString = (Constructors.Any()) ? Constructors.Select(c => c.ToString()).Aggregate((x, y) => string.Format("{0}\r\n{1}", x, y)) : string.Empty,
                functionsString = (Functions.Any()) ? Functions.Select(f => f.ToString()).Aggregate((x, y) => string.Format("{0}\r\n{1}", x, y)) : string.Empty,
                operatorsString = (Operators.Any()) ? Operators.Select(o => o.ToString()).Aggregate((x, y) => string.Format("{0}\r\n{1}", x, y)) : string.Empty,
                classesString = (Classes.Any()) ? Classes.Select(c => c.Name).Aggregate((x, y) => string.Format("{0}\r\n{1}", x, y)) : string.Empty;
            return string.Format("{0}{1}{2}\r\n\r\nConstructors:\r\n{3}\r\n\r\nFunctions:\r\n{4}\r\n\r\nOperators:\r\n{5}\r\n\r\nClasses:\r\n{6}\r\n",
                                 templateTypesString,
                                 Name,
                                 baseClassesString,
                                 constructorsString,
                                 functionsString,
                                 operatorsString,
                                 classesString);

        }
    }
}
