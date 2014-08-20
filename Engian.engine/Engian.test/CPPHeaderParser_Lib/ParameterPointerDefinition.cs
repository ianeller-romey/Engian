using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    public class ParameterPointerDefinition : IEquatable<ParameterPointerDefinition>
    {
        public bool IsConst { get; set; }

        static public bool operator ==(ParameterPointerDefinition one, ParameterPointerDefinition two)
        {
            return one.Equals(two);
        }

        static public bool operator !=(ParameterPointerDefinition one, ParameterPointerDefinition two)
        {
            return !one.Equals(two);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            ParameterPointerDefinition other = obj as ParameterPointerDefinition;
            return (other == null) ? false : Equals(other);
        }

        public bool Equals(ParameterPointerDefinition other)
        {
            return other.IsConst == IsConst;
        }

        public override int GetHashCode()
        {
            int isConstHashCode = IsConst.GetHashCode();
            return isConstHashCode;
        }

        public override string ToString()
        {
            return string.Format("* {0}", (IsConst) ? " const" : string.Empty);
        }
    }
}
