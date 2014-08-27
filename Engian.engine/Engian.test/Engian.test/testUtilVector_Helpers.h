
#include "utilVector.h"


namespace Test
{  

  template< typename HELPER >
  struct TestHelper_UtilVector
  {

    static char const * const CheckVectorInit( Util::Vector< HELPER > const& vector, 
                                               unsigned const capacity,
                                               unsigned const size )
    {
      if( vector.dbgGet_m_capacity() != capacity ) return "did not initialize m_capacity correctly";
      return CheckVectorInit( vector, size );
    }
    

    static char const * const CheckVectorInit( Util::Vector< HELPER > const& vector, 
                                               unsigned const size )
    {
      if( vector.dbgGet_m_size() != size ) return "did not increase m_size to the correct value";
      if( vector.dbgGet_m_array() == 0 ) return "did not initialize m_array";
      if( vector.dbgGet_m_implementations() != 0 ) return "created unnecessary Iterators";
      return 0;
    }


    static char const * const CheckVectorAgainstArray( Util::Vector< HELPER > const& vector, 
                                                       HELPER const * const compareAgainst, 
                                                       unsigned const compareAgainstLen )
    {      
      for( unsigned i = 0; i < compareAgainstLen; ++i )
        if( vector.dbgGet_m_array()[ i ] != compareAgainst[ i ] ) return "did not insert correct value";
      return 0;
    }
  

    static char const * const CheckVectorAgainstContainer( Util::Vector< HELPER > const& vector, 
                                                           Util::Container< HELPER > const& container )
    {    
      Util::Container< HELPER >::Iterator itB = container.Begin(),
                                          itE = container.End();
      for( unsigned i = 0; itB != itE; ++itB, ++i )
        if( vector.dbgGet_m_array()[ i ] != itB.Get() ) return "did not insert correct value";
      return 0;
    }

  };

}
