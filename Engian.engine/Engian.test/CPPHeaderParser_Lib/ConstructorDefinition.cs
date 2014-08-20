using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    public class ConstructorDefinition : IEquatable<ConstructorDefinition>
    {
        public string Class { get; set; }
        public bool IsCopy { get; set; }
        public List<ParameterDefinition> Parameters { get; set; }

        public ConstructorDefinition()
        {
            Parameters = new List<ParameterDefinition>();
        }

        static public bool operator ==(ConstructorDefinition one, ConstructorDefinition two)
        {
            return one.Equals(two);
        }

        static public bool operator !=(ConstructorDefinition one, ConstructorDefinition two)
        {
            return !one.Equals(two);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            ConstructorDefinition other = obj as ConstructorDefinition;
            return (other == null) ? false : Equals(other);
        }

        public bool Equals(ConstructorDefinition other)
        {
            return
                other.Class == Class &&
                other.IsCopy == IsCopy &&
                !other.Parameters.Except(Parameters).Any();
        }

        public override int GetHashCode()
        {
            int
                classHashCode = Class.GetHashCode(),
                isCopyHashCode = IsCopy.GetHashCode(),
                parametersHashCode = 1;
            foreach (ParameterDefinition p in Parameters)
                parametersHashCode ^= p.GetHashCode();
            return classHashCode ^ isCopyHashCode ^ parametersHashCode;
        }

        public override string ToString()
        {
            return string.Format("{0}( {1} );",
                                 Class,
                                 (Parameters.Any())
                                 ? Parameters.Select(p => p.ToString()).Aggregate((x, y) => string.Format("{0}, {1}", x, y))
                                 : string.Empty);
        }
    }
}
