
#include "utilString.h"


namespace Test
{  

  struct TestHelper_UtilString
  {    

    static char const * const CheckStringAgainstArray( Util::String const& check, char const * const compareAgainst )
    {
      unsigned const compareAgainstLen = strlen( compareAgainst );
      return CheckStringAgainstArray( check, compareAgainst, compareAgainstLen );
    }
  

    static char const * const CheckStringAgainstArray( Util::String const& check, char const * const compareAgainst, unsigned const compareAgainstLen )
    {    
      if( strncmp( check.dbgGet_m_array(), compareAgainst, compareAgainstLen ) != 0 ) return "did not insert correct value";
      if( check.dbgGet_m_array()[ compareAgainstLen ] != '\0' ) return "did not terminate string with a null character";
      if( check.dbgGet_m_implementations() != 0 ) return "created unnecessary Iterators";
      return 0;
    }
  

    static char const * const CheckStringAgainstContainer( Util::String const& compareFrom, Util::Container< char > const& compareAgainst )
    {
      Util::Container< char >::Iterator itB = compareAgainst.Begin(),
                                        itE = compareAgainst.End();
      for( unsigned i = 0; itB != itE; ++itB, ++i )
        if( compareFrom.dbgGet_m_array()[ i ] != itB.Get() ) return "did not insert correct value";
      if( compareFrom.dbgGet_m_array()[ compareAgainst.GetSize() ] != '\0' ) return "did not terminate string with a null character";
      if( compareFrom.dbgGet_m_implementations() != 0 ) return "created unnecessary Iterators";
      return 0;
    }

  };

}
