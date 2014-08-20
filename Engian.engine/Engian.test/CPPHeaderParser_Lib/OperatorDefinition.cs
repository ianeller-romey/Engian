using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    public class OperatorDefinition : IEquatable<OperatorDefinition>
    {
        public enum OperatorType 
        { 
            BasicAssignment, 
            Addition,
            Subtraction,
            UnaryPlus,
            UnaryMinus,
            Multiplication,
            Division,
            Modulo,
            PrefixIncrement,
            PostfixIncrement,
            PrefixDecrement,
            PostfixDecrement,
            EqualTo,
            NotEqualTo,
            GreaterThan,
            LessThan,
            GreaterThanOrEqualTo,
            LessThanOrEqualTo,
            LogicalNOT,
            LogicalAND,
            LogicalOR,
            BitwiseNOT,
            BitwiseAND,
            BitwiseOR,
            BitwiseXOR,
            BitwiseLeftShift,
            BitwiseRightShift,
            AdditionAssignment,
            SubtractionAssignment,
            MultiplicationAssignment,
            DivisionAssignment,
            ModuloAssignment,
            BitwiseANDAssignment,
            BitwiseORAssignment,
            BitwiseXORAssignment,
            BitwiseLeftShiftAssignment,
            BitwiseRightShiftAssignment,
            ArraySubscript,
            Indirection,
            Reference,
            StructureDereference,
            MemberPointedToByBOfObjectPointedToByA,
            FunctionCall,
            Comma,
            Conversion,
            AllocateStorage,
            AllocateStorageArray,
            DeallocateStorage,
            DeallocateStorageArray
        };
        public static readonly Dictionary<OperatorType, string> OperatorTypeRepresentations =
            new KeyValuePair<OperatorType, string>[]
            {
                new KeyValuePair<OperatorType, string>(OperatorType.BasicAssignment, "="),
                new KeyValuePair<OperatorType, string>(OperatorType.Addition, "+"),
                new KeyValuePair<OperatorType, string>(OperatorType.Subtraction, "-"),
                new KeyValuePair<OperatorType, string>(OperatorType.UnaryPlus, "+"),
                new KeyValuePair<OperatorType, string>(OperatorType.UnaryMinus, "-"),
                new KeyValuePair<OperatorType, string>(OperatorType.Multiplication, "*"),
                new KeyValuePair<OperatorType, string>(OperatorType.Division, "/"),
                new KeyValuePair<OperatorType, string>(OperatorType.Modulo, "%"),
                new KeyValuePair<OperatorType, string>(OperatorType.PrefixIncrement, "++"),
                new KeyValuePair<OperatorType, string>(OperatorType.PostfixIncrement, "++"),
                new KeyValuePair<OperatorType, string>(OperatorType.PrefixDecrement, "--"),
                new KeyValuePair<OperatorType, string>(OperatorType.PostfixDecrement, "--"),
                new KeyValuePair<OperatorType, string>(OperatorType.EqualTo, "=="),
                new KeyValuePair<OperatorType, string>(OperatorType.NotEqualTo, "!="),
                new KeyValuePair<OperatorType, string>(OperatorType.GreaterThan, ">"),
                new KeyValuePair<OperatorType, string>(OperatorType.LessThan, "<"),
                new KeyValuePair<OperatorType, string>(OperatorType.GreaterThanOrEqualTo, ">="),
                new KeyValuePair<OperatorType, string>(OperatorType.LessThanOrEqualTo, "<="),
                new KeyValuePair<OperatorType, string>(OperatorType.LogicalNOT, "!"),
                new KeyValuePair<OperatorType, string>(OperatorType.LogicalAND, "&&"),
                new KeyValuePair<OperatorType, string>(OperatorType.LogicalOR, "||"),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseNOT, "~"),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseAND, "&"),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseOR, "|"),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseXOR, "^"),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseLeftShift, "<<"),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseRightShift, ">>"),
                new KeyValuePair<OperatorType, string>(OperatorType.AdditionAssignment, "+="),
                new KeyValuePair<OperatorType, string>(OperatorType.SubtractionAssignment, "-="),
                new KeyValuePair<OperatorType, string>(OperatorType.MultiplicationAssignment, "*="),
                new KeyValuePair<OperatorType, string>(OperatorType.DivisionAssignment, "/="),
                new KeyValuePair<OperatorType, string>(OperatorType.ModuloAssignment, "%="),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseANDAssignment, "&="),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseORAssignment, "|="),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseXORAssignment, "^="),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseLeftShiftAssignment, "<<="),
                new KeyValuePair<OperatorType, string>(OperatorType.BitwiseRightShiftAssignment, ">>="),
                new KeyValuePair<OperatorType, string>(OperatorType.ArraySubscript, "[]"),
                new KeyValuePair<OperatorType, string>(OperatorType.Indirection, "*"),
                new KeyValuePair<OperatorType, string>(OperatorType.Reference, "&"),
                new KeyValuePair<OperatorType, string>(OperatorType.StructureDereference, "->"),
                new KeyValuePair<OperatorType, string>(OperatorType.MemberPointedToByBOfObjectPointedToByA, "->*"),
                new KeyValuePair<OperatorType, string>(OperatorType.FunctionCall, "()"),
                new KeyValuePair<OperatorType, string>(OperatorType.Comma, ","),
                new KeyValuePair<OperatorType, string>(OperatorType.Conversion, "conversion"),
                new KeyValuePair<OperatorType, string>(OperatorType.AllocateStorage, "new"),
                new KeyValuePair<OperatorType, string>(OperatorType.AllocateStorageArray, "new[]"),
                new KeyValuePair<OperatorType, string>(OperatorType.DeallocateStorage, "delete"),
                new KeyValuePair<OperatorType, string>(OperatorType.DeallocateStorageArray, "delete[]")
            }.ToDictionary(kv => { return kv.Key; }, kv => { return kv.Value; });

        public OperatorType Type { get; set; }
        public string TypeName { get { return (Type != null) ? Enum.GetName(typeof(OperatorType), Type) : string.Empty; } }
        public bool IsVirtual { get; set; }
        public List<ParameterDefinition> Parameters { get; set; }
        public ReturnValueDefinition ReturnValue { get; set; }

        public OperatorDefinition()
        {
            Parameters = new List<ParameterDefinition>();
        }

        static public bool operator ==(OperatorDefinition one, OperatorDefinition two)
        {
            return one.Equals(two);
        }

        static public bool operator !=(OperatorDefinition one, OperatorDefinition two)
        {
            return !one.Equals(two);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            OperatorDefinition other = obj as OperatorDefinition;
            return (other == null) ? false : Equals(other);
        }

        public bool Equals(OperatorDefinition other)
        {
            return
                other.Type == Type &&
                other.IsVirtual == IsVirtual &&
                !other.Parameters.Except(Parameters).Any() &&
                other.ReturnValue == ReturnValue;
        }

        public override int GetHashCode()
        {
            int
                nameHashCode = Type.GetHashCode(),
                isVirtualHashCode = IsVirtual.GetHashCode(),
                parametersHashCode = 1,
                returnValueHashCode = ReturnValue.GetHashCode();
            foreach (ParameterDefinition p in Parameters)
                parametersHashCode ^= p.GetHashCode();
            return nameHashCode ^ isVirtualHashCode ^ parametersHashCode ^ returnValueHashCode;
        }

        public override string ToString()
        {
            return string.Format("{0}{1} operator{2}( {3} );",
                                 (IsVirtual) ? "virtual " : string.Empty,
                                 ReturnValue.ToString(),
                                 OperatorTypeRepresentations[Type],
                                 (Parameters.Any())
                                 ? Parameters.Select(p => p.ToString()).Aggregate((x, y) => string.Format("{0}, {1}", x, y))
                                 : string.Empty);
        }
    }
}
