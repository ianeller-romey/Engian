using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    public class FunctionDefinition : IEquatable<FunctionDefinition>
    {
        public string Name { get; set; }
        public bool IsVirtual { get; set; }
        public List<ParameterDefinition> Parameters { get; set; }
        public ReturnValueDefinition ReturnValue { get; set; }

        public FunctionDefinition()
        {
            Parameters = new List<ParameterDefinition>();
        }

        static public bool operator ==(FunctionDefinition one, FunctionDefinition two)
        {
            return one.Equals(two);
        }

        static public bool operator !=(FunctionDefinition one, FunctionDefinition two)
        {
            return !one.Equals(two);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            FunctionDefinition other = obj as FunctionDefinition;
            return (other == null) ? false : Equals(other);
        }

        public bool Equals(FunctionDefinition other)
        {
            return
                other.Name == Name &&
                other.IsVirtual == IsVirtual &&
                !other.Parameters.Except(Parameters).Any() &&
                other.ReturnValue == ReturnValue;
        }

        public override int GetHashCode()
        {
            int
                nameHashCode = Name.GetHashCode(),
                isVirtualHashCode = IsVirtual.GetHashCode(),
                parametersHashCode = 1,
                returnValueHashCode = ReturnValue.GetHashCode();
            foreach (ParameterDefinition p in Parameters)
                parametersHashCode ^= p.GetHashCode();
            return nameHashCode ^ isVirtualHashCode ^ parametersHashCode ^ returnValueHashCode;
        }

        public override string ToString()
        {
            return string.Format("{0}{1} {2}( {3} );",
                                 (IsVirtual) ? "virtual " : string.Empty,
                                 ReturnValue.ToString(),
                                 Name,
                                 (Parameters.Any())
                                 ? Parameters.Select(p => p.ToString()).Aggregate((x, y) => string.Format("{0}, {1}", x, y))
                                 : string.Empty);
        }
    }
}
