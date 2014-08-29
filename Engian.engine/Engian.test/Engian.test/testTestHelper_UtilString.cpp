
#include "testTestHelper_UtilString.h"

#include "utilString.h"


namespace Test
{
    
    char const * const TestHelper_UtilString::CheckUtilStringAgainstArray( Util::String const& string, char const * const compareAgainst )
    {
      unsigned const compareAgainstLen = strlen( compareAgainst );
      return CheckUtilStringAgainstArray( string, compareAgainst, compareAgainstLen );
    }
  

    char const * const TestHelper_UtilString::CheckUtilStringAgainstArray( Util::String const& string, 
                                                           char const * const compareAgainst, 
                                                           unsigned const compareAgainstLen )
    {    
      if( strncmp( string.m_array, compareAgainst, compareAgainstLen ) != 0 ) return "did not insert correct value";
      if( string.m_array[ compareAgainstLen ] != '\0' ) return "did not terminate string with a null character";
      if( string.m_implementations != 0 ) return "created unnecessary Iterators";
      return 0;
    }
  

    char const * const TestHelper_UtilString::CheckUtilStringAgainstContainer( Util::String const& string, Util::Container< char > const& container )
    {
      Util::Container< char >::Iterator itB = container.Begin(),
                                        itE = container.End();
      for( unsigned i = 0; itB != itE; ++itB, ++i )
        if( string.m_array[ i ] != itB.Get() ) return "did not insert correct value";
      if( string.m_array[ container.GetSize() ] != '\0' ) return "did not terminate string with a null character";
      if( string.m_implementations != 0 ) return "created unnecessary Iterators";
      return 0;
    }

}
