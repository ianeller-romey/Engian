
#include "utilSortedVector.h"


namespace Test
{  

  template< typename HELPER >
  struct TestHelper_UtilSortedVector
  {
    static char const * const CheckSortedVector( Util::SortedVector< HELPER > const& check )
    {
      for( unsigned i = 0, j < check.dbgGet_m_size() - 1; i < j; ++i )
        if( check.dbgGet_m_array()[ i ] > check.dbgGet_m_array()[ i + 1 ] ) return "did not properly sort vector values";
      return 0;
    }

  };

}
