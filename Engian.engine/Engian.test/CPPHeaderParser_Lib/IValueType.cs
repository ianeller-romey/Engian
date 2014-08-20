using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPPHeaderParser_Lib
{
    interface IValueType
    {
        List<ParameterPointerDefinition> PointerDepth { get; set; }
        bool IsReference { get; set; }
        bool IsConst { get; set; }
        string Type { get; set; }
    }
}
