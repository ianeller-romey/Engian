
#ifndef TEST_UNITTESTHELPER_H
#define TEST_UNITTESTHELPER_H


namespace Util
{
  template< typename T > class Container;
  class String;
}


namespace Test
{  

  class TestHelper_UtilString
  {
    public:
      static char const * const CheckUtilStringAgainstArray( Util::String const& string, char const * const compareAgainst );
      static char const * const CheckUtilStringAgainstArray( Util::String const& string, 
                                                             char const * const compareAgainst, 
                                                             unsigned const compareAgainstLen );
      static char const * const CheckUtilStringAgainstContainer( Util::String const& string, Util::Container< char > const& container );

  };

}

#endif
