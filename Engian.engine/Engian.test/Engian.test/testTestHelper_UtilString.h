
#ifndef TEST_TESTHELPER_UTILSTRING_H
#define TEST_TESTHELPER_UTILSTRING_H


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
      static unsigned const String_Constructor0();
      static unsigned const String_Constructor1();
      static unsigned const String_Constructor2();
      static unsigned const String_Constructor3();
      static unsigned const String_Constructor4();
      static unsigned const String_CopyConstructor();
      static unsigned const String_PushBack();
      static unsigned const String_PushBackRange0();
      static unsigned const String_PushBackRange1();
      static unsigned const String_PushBackRange2();
      static unsigned const String_PopBack();
      static unsigned const String_GetStrLen();
      static unsigned const String_BeginsWith();
      static unsigned const String_EndsWith();
      static unsigned const String_IsEmpty();
      static unsigned const String_Clear();
      static unsigned const String_BasicAssignment0();
      static unsigned const String_BasicAssignment1();
      static unsigned const String_BasicAssignment2();
      static unsigned const String_BasicAssignment3();
      static unsigned const String_EqualAndNotEqualTo0();
      static unsigned const String_EqualAndNotEqualTo1();
      static unsigned const String_EqualAndNotEqualTo2();
      static unsigned const String_Addition0();
      static unsigned const String_Addition1();
      static unsigned const String_Addition2();
      static unsigned const String_Addition3();
      static unsigned const String_AdditionAssignment0();
      static unsigned const String_AdditionAssignment1();
      static unsigned const String_AdditionAssignment2();
      static unsigned const String_BitwiseLeftShiftIntAndUint();

    private:
      static unsigned const CheckUtilStringInit( Util::String const& string, unsigned const capacity, unsigned const size );
      static unsigned const CheckUtilStringInit( Util::String const& string, unsigned const size );
      static unsigned const CheckUtilStringAgainstArray( Util::String const& string, char const * const compareAgainst );
      static unsigned const CheckUtilStringAgainstArray( Util::String const& string,
                                                         char const * const compareAgainst,
                                                         unsigned const compareAgainstLen );
      static unsigned const CheckUtilStringAgainstContainer( Util::String const& string, Util::Container< char > const& container );

  };

}

#endif
