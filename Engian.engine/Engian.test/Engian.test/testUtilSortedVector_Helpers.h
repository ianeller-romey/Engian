
#include "utilSortedVector.h"


namespace Test
{  

  template< typename HELPER >
  struct UnitTestChassis_Helper_SortedVector
  {
    static char const * const CheckSortedVector( void* check, unsigned const capacity, unsigned const size )
    {
      Util::SortedVector< HELPER >* sVector = static_cast< Util::SortedVector< HELPER >* >( check );

      if( capacity == 0 )
      {
        if( sVector->m_capacity == 0 ) return "did not use c_defaultCapacity";
      }
      else
      {
        if( sVector->m_capacity != capacity ) return "did not use c_defaultCapacity";
      }
      if( sVector->m_size != size ) return "did not initialize m_size to 0";
      if( sVector->m_array == 0 ) return "did not initialize m_array";
      if( sVector->m_implementations != 0 ) return "incorrectly initialized m_implementations";
      for( unsigned i = 0, j = size - 1; i < j; ++i )
        if( sVector->m_array[ i ] > sVector->m_array[ i + 1 ] ) return "did not properly sort vector values";
      return 0;
    }

  };

}
