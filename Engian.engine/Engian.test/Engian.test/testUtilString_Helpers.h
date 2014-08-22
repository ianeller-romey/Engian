
#include "utilString.h"


namespace Test
{  

  struct UnitTestChassis_Helper_String
  {    

    static char const * const TestUtilString_Helper_CheckStringAgainstArray( void* check, char const * const compareAgainst )
    {
      unsigned const compareAgainstLen = strlen( compareAgainst );
      return TestUtilString_Helper_CheckStringAgainstArray( check, compareAgainst, compareAgainstLen );
    }
  

    static char const * const TestUtilString_Helper_CheckStringAgainstArray( void* check, char const * const compareAgainst, unsigned const compareAgainstLen )
    {
      Util::String* string = static_cast< Util::String* >( check );
    
      if( string->dbgGet_m_capacity() == 0 ) return "did not initialize m_capacity correctly";
      if( string->dbgGet_m_size() != compareAgainstLen + 1 ) return "did not increase the string's m_size variable to the correct value";
      if( strncmp( string->dbgGet_m_array(), compareAgainst, compareAgainstLen ) != 0 ) return "did not insert correct value";
      if( string->dbgGet_m_array()[ compareAgainstLen ] != '\0' ) return "did not terminate string with a null character";
      if( string->dbgGet_m_implementations() != 0 ) return "created unnecessary Iterators";
      return 0;
    }
  

    static char const * const TestUtilString_Helper_CheckStringAgainstContainer( void* compareFrom, void* compareAgainst )
    {
      Util::String* string = static_cast< Util::String* >( compareFrom );
      Util::Container< char >* container = static_cast< Util::Container< char >* >( compareAgainst );
    
      if( string->dbgGet_m_capacity() == 0 ) return "did not initialize m_capacity correctly";
      if( string->dbgGet_m_size() != container->GetSize() + 1 ) return "did not increase the string's m_size variable to the correct value";
      Util::Container< char >::Iterator itB = container->Begin(),
                                        itE = container->End();
      for( unsigned i = 0; itB != itE; ++itB, ++i )
        if( string->dbgGet_m_array()[ i ] != itB.Get() ) return "did not insert correct value";
      if( string->dbgGet_m_array()[ container->GetSize() ] != '\0' ) return "did not terminate string with a null character";
      if( string->dbgGet_m_implementations() != 0 ) return "created unnecessary Iterators";
      return 0;
    }

  };

}
