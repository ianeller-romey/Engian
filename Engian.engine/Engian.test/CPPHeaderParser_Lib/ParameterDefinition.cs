using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    public class ParameterDefinition : IValueType, IEquatable<ParameterDefinition>
    {
        public List<ParameterPointerDefinition> PointerDepth { get; set; }
        public bool IsReference { get; set; }
        public bool IsConst { get; set; }
        public string Type { get; set; }
        public string Name { get; set; }

        public ParameterDefinition()
        {
            PointerDepth = new List<ParameterPointerDefinition>();
        }

        static public bool operator ==(ParameterDefinition one, ParameterDefinition two)
        {
            return one.Equals(two);
        }

        static public bool operator !=(ParameterDefinition one, ParameterDefinition two)
        {
            return !one.Equals(two);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            ParameterDefinition other = obj as ParameterDefinition;
            return (other == null) ? false : Equals(other);
        }

        public bool Equals(ParameterDefinition other)
        {
            return
                other.Name == Name &&
                other.Type == Type &&
                other.IsConst == IsConst &&
                other.IsReference == IsReference &&
                !other.PointerDepth.Except(PointerDepth).Any();
        }

        public override int GetHashCode()
        {
            int
                pointerDepthHashCode = 1,
                isReferenceHashCode = IsReference.GetHashCode(),
                isConstHashCode = IsConst.GetHashCode(),
                typeHashCode = Type.GetHashCode(),
                nameHashCode = Name.GetHashCode();
            foreach (ParameterPointerDefinition p in PointerDepth)
                nameHashCode ^= p.GetHashCode();
            return pointerDepthHashCode ^ isReferenceHashCode ^ isConstHashCode ^ typeHashCode ^ nameHashCode;
        }

        public override string ToString()
        {
            return
                string.Format("{0}{1}{2} {3}",
                              Type,
                              (IsConst) ? " const" : string.Empty,
                              (IsReference)
                              ? "&"
                              : (PointerDepth.Count > 0)
                                ? PointerDepth.Select(p => p.ToString()).Aggregate((x, y) => string.Format("{0} {1}", x, y))
                                : string.Empty,
                            Name);
        }
    }
}
