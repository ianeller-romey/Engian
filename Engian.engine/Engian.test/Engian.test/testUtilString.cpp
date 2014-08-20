
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "utilString.h"
#include "utilList.h"


namespace Test
{

  char const * const UnitTestChassis::TestUtilString_Helper_CheckStringAgainstArray( void* check, char const * const compareAgainst )
  {
    unsigned const compareAgainstLen = strlen( compareAgainst );
    return TestUtilString_Helper_CheckStringAgainstArray( check, compareAgainst, compareAgainstLen );
  }
  

  char const * const UnitTestChassis::TestUtilString_Helper_CheckStringAgainstArray( void* check, char const * const compareAgainst, unsigned const compareAgainstLen )
  {
    Util::String* string = static_cast< Util::String* >( check );
    
    if( string->m_capacity == 0 ) return "did not initialize m_capacity correctly";
    if( string->m_size != compareAgainstLen + 1 ) return "did not increase the string's m_size variable to the correct value";
    if( strncmp( string->m_array, compareAgainst, compareAgainstLen ) != 0 ) return "did not insert correct value";
    if( string->m_array[ compareAgainstLen ] != '\0' ) return "did not terminate string with a null character";
    if( string->m_implementations != 0 ) return "created unnecessary Iterators";
    return 0;
  }
  

  char const * const UnitTestChassis::TestUtilString_Helper_CheckStringAgainstContainer( void* compareFrom, void* compareAgainst )
  {
    Util::String* string = static_cast< Util::String* >( compareFrom );
    Util::Container< char >* container = static_cast< Util::Container< char >* >( compareAgainst );
    
    if( string->m_capacity == 0 ) return "did not initialize m_capacity correctly";
    if( string->m_size != container->GetSize() + 1 ) return "did not increase the string's m_size variable to the correct value";
    Util::Container< char >::Iterator itB = container->Begin(),
                                      itE = container->End();
    for( unsigned i = 0; itB != itE; ++itB, ++i )
      if( string->m_array[ i ] != itB.Get() ) return "did not insert correct value";
    if( string->m_array[ container->GetSize() ] != '\0' ) return "did not terminate string with a null character";
    if( string->m_implementations != 0 ) return "created unnecessary Iterators";
    return 0;
  }


  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilString[] = {
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor4 ),
    T_FUNC_ARR_DEF( TestUtilString_String_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBack ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBackRange0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBackRange1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBackRange2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_PopBack ),
    T_FUNC_ARR_DEF( TestUtilString_String_GetStrLen ),
    T_FUNC_ARR_DEF( TestUtilString_String_BeginsWith ),
    T_FUNC_ARR_DEF( TestUtilString_String_EndsWith ),
    T_FUNC_ARR_DEF( TestUtilString_String_IsEmpty ),
    T_FUNC_ARR_DEF( TestUtilString_String_Clear ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment3 ),
    T_FUNC_ARR_DEF( TestUtilString_String_EqualAndNotEqualTo0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_EqualAndNotEqualTo1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_EqualAndNotEqualTo2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition3 ),
    T_FUNC_ARR_DEF( TestUtilString_String_AdditionAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_AdditionAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_AdditionAssignment2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BitwiseLeftShiftIntAndUint )
  };

  char const * const UnitTestChassis::TestUtilString_String_Constructor0( char const * const name )
  {
    try
    {
      Util::String string;
      TEST_ASSERT( string.m_capacity == Util::String::c_defaultCapacity, name, "did not initialize m_capacity to c_defaultCapacity" );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, "", 0 ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String::String()" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor1( char const * const name )
  {
    try
    {
      unsigned const capacity = 200;
      Util::String string( capacity );
      TEST_ASSERT( string.m_capacity == capacity, name, "did not initialize m_capacity correctly" );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, "", 0 ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String::String( unsigned const capacity )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor2( char const * const name )
  {
    try
    {
      char const * const characters = "The quick brown fox jumps over the lazy dog.";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String::String( char const * const string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor3( char const * const name )
  {
    try
    {
      char const character = 'I';
      Util::String string( character );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, &character, 1 ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String::String( char const character )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor4( char const * const name )
  {
    try
    {
      char characters[] = "abcdefghijklmnopqrstuvwxyz";
      unsigned const charactersLen = strlen( characters );
      Util::List< char > list( characters, charactersLen );
      Util::String string( list );
      Util::Container< char >* containerPtr = dynamic_cast< Util::Container< char >* >( &list );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstContainer( &string, containerPtr ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String::String( Container< char > const& container )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_CopyConstructor( char const * const name )
  {
    try
    {
      char const * const characters = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.";
      unsigned const charactersLen = strlen( characters );
      Util::String string1( characters ),
                   string2( string1 );
      TEST_ASSERT( string2.m_capacity == string1.m_capacity, name, "did not initialize m_capacity correctly" );
      TEST_ASSERT( string2.m_size == string1.m_size, name, "did not initialize m_size correctly" );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string2, string1.m_array ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String::String( String const& string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBack( char const * const name )
  {
    try
    {
      char characters[] = "THIS IS A STRING THAT I'M QUITE HAPPY TO USE TO TEST MY DATA STRUCTURES!";
      unsigned const charactersLen = strlen( characters );
      Util::String string;
      for( unsigned i = 0; i < charactersLen; ++i )
        string.PushBack( characters[ i ] );
      
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "void String::PushBack( char const& t )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBackRange0( char const * const name )
  {
    try
    {
      char characters1[] = "THIS IS THE BEGINNING,",
           characters2[] = "AND THIS IS THE MIDDLE,",
           characters3[] = "AND THIS IS THE END,",
           characters4[] = "OF A TEST STRING.";
      unsigned const charactersLen1 = strlen( characters1 ),
                     charactersLen2 = strlen( characters2 ),
                     charactersLen3 = strlen( characters3 ),
                     charactersLen4 = strlen( characters4 ),
                     charactersLenAll = charactersLen1 + charactersLen2 + charactersLen3 + charactersLen4;
      Util::String string;
      string.PushBackRange( characters1 );
      string.PushBackRange( characters2 );
      string.PushBackRange( characters3 );
      string.PushBackRange( characters4 );

      Util::Vector< char > vector( charactersLenAll );
      vector.PushBackRange( characters1, charactersLen1 );
      vector.PushBackRange( characters2, charactersLen2 );
      vector.PushBackRange( characters3, charactersLen3 );
      vector.PushBackRange( characters4, charactersLen4 );
      
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, vector.m_array, vector.m_size ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "void String::PushBackRange( char const * const string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBackRange1( char const * const name )
  {
    try
    {
      char characters[] = "this test string will be inserted several characters at a time";
      unsigned const charactersLen = strlen( characters );
      Util::String string;
      for( unsigned i = 0, incr = 5; i < charactersLen; i += incr )
        string.PushBackRange( characters + i, ( charactersLen - i < incr ) ? charactersLen - i : incr );
      
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "void String::PushBackRange( char const * const tArray, unsigned const size )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBackRange2( char const * const name )
  {
    try
    {
      char characters[] = "this test string is pretty much like every other test string";
      unsigned const charactersLen = strlen( characters );
      Util::String string1,
                   string2( characters );
      string1.PushBackRange( string2 );
      
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string1, characters ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "void String::PushBackRange( String const& string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PopBack( char const * const name )
  {
    try
    {
      char characters[] = "~!@#$%^&*()_+=-0987654321`";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters );
      for( int i = charactersLen; i > 0; --i )
      {
        string.PopBack();
        TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters, i - 1 ) == 0, name, "did not update values correctly" );
      }
      TEST_ASSERT( string.IsEmpty(), name, "returned false for .IsEmpty() after removing all elements" );
      TEST_ASSERT( CheckTestCall( "void String::PopBack()" ), name, "Appropriate function was not called" );

      // check for exceptions
      string.PopBack();
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_GetStrLen( char const * const name )
  {
    try
    {
      char characters[] = "this STRING will BE used TO test THE GetStrLen MEMBER function";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters );
      TEST_ASSERT( string.GetStrLen() == charactersLen, name, "did not return correct string length" );
      TEST_ASSERT( CheckTestCall( "unsigned const String::GetStrLen() const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BeginsWith( char const * const name )
  {
    try
    {
      char characters[] = "TestUtilString_String_BeginsWith0";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters ), stringAlt;
      Util::List< char > list;

      TEST_ASSERT( string.BeginsWith( "Test" ), name, "did not return true for correct string" );
      TEST_ASSERT( string.BeginsWith( "TestUtilString_String_BeginsWith0" ), name, "did not return true for correct string" );
      TEST_ASSERT( string.BeginsWith( "TestUtilVector" ) == false, name, "returned true for incorrect string" );
      TEST_ASSERT( string.BeginsWith( "TestUtilString_String_BeginsWith000" ) == false, name, "returned true for longer string" );
      TEST_ASSERT( CheckTestCall( "bool const String::BeginsWith( char const * const string ) const", true ), name, "Appropriate function not called" );

      TEST_ASSERT( string.BeginsWith( "Test", 3 ), name, "did not return true for correct string" );
      TEST_ASSERT( string.BeginsWith( "TestUtilString_String_BeginsWith0", charactersLen ), name, "did not return true for correct string" );
      TEST_ASSERT( string.BeginsWith( "TestUtilVector", 10 ) == false, name, "returned true for incorrect string" );
      TEST_ASSERT( string.BeginsWith( "TestUtilString_String_BeginsWith000", 34 ) == false, name, "returned true for longer string" );
      TEST_ASSERT( CheckTestCall( "bool const String::BeginsWith( char const * const string, unsigned strLen ) const", true ), name, "Appropriate function not called" );

      TEST_ASSERT( string.BeginsWith( 'T' ), name, "did not return true for correct character" );
      TEST_ASSERT( string.BeginsWith( 't' ) == false, name, "returned true for incorrect character" );
      TEST_ASSERT( CheckTestCall( "bool const String::BeginsWith( char const character ) const", true ), name, "Appropriate function not called" );

      stringAlt = "TestUtilString";
      TEST_ASSERT( string.BeginsWith( stringAlt ), name, "did not return true for correct String" );
      stringAlt = "TestUtilString_String_BeginsWith0";
      TEST_ASSERT( string.BeginsWith( stringAlt ), name, "did not return true for correct String" );
      stringAlt = "UnitTestArray";
      TEST_ASSERT( string.BeginsWith( stringAlt ) == false, name, "returned true for incorrect String" );
      stringAlt = "TestUtilString_String_BeginsWith000";
      TEST_ASSERT( string.BeginsWith( stringAlt ) == false, name, "returned true for longer String" );
      TEST_ASSERT( CheckTestCall( "bool const String::BeginsWith( String const& string ) const", true ), name, "Appropriate function not called" );

      list.Clear();
      for( unsigned i = 0, j = charactersLen / 2; i < j; ++i ) list.PushBack( characters[ i ] );
      TEST_ASSERT( string.BeginsWith( list ), name, "did not return true for correct Container< char >" );
      list.Clear();
      for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
      TEST_ASSERT( string.BeginsWith( list ), name, "did not return true for correct Container< char >" );
      list.Clear();
      for( unsigned i = 0; i < 5; ++i ) list.PushBack( (char)( rand() ) );
      TEST_ASSERT( string.BeginsWith( list ) == false, name, "returned true for incorrect Container< char >" );
      list.Clear();
      for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
      list.PushBack( '0' );
      TEST_ASSERT( string.BeginsWith( list ) == false, name, "returned true for longer Container< char >" );
      TEST_ASSERT( CheckTestCall( "bool const String::BeginsWith( Container< char > const& container ) const", true ), name, "Appropriate function not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EndsWith( char const * const name )
  {
    try
    {
      char characters[] = "TestUtilString_String_EndsWith0";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters ), stringAlt;
      Util::List< char > list;

      TEST_ASSERT( string.EndsWith( "EndsWith0" ), name, "did not return true for correct string" );
      TEST_ASSERT( string.EndsWith( "TestUtilString_String_EndsWith0" ), name, "did not return true for correct string" );
      TEST_ASSERT( string.EndsWith( "TestUtilVector" ) == false, name, "returned true for incorrect string" );
      TEST_ASSERT( string.EndsWith( "TestUtilString_String_EndsWith000" ) == false, name, "returned true for longer string" );
      TEST_ASSERT( CheckTestCall( "bool const String::EndsWith( char const * const string ) const", true ), name, "Appropriate function not called" );

      TEST_ASSERT( string.EndsWith( "With0With0With0", 5 ), name, "did not return true for correct string" );
      TEST_ASSERT( string.EndsWith( "TestUtilString_String_EndsWith0", charactersLen ), name, "did not return true for correct string" );
      TEST_ASSERT( string.EndsWith( "TestUtilVector", 10 ) == false, name, "returned true for incorrect string" );
      TEST_ASSERT( string.EndsWith( "TestUtilString_String_EndsWith000", 34 ) == false, name, "returned true for longer string" );
      TEST_ASSERT( CheckTestCall( "bool const String::EndsWith( char const * const string, unsigned strLen ) const", true ), name, "Appropriate function not called" );

      TEST_ASSERT( string.EndsWith( '0' ), name, "did not return true for correct character" );
      TEST_ASSERT( string.EndsWith( 't' ) == false, name, "returned true for incorrect character" );
      TEST_ASSERT( CheckTestCall( "bool const String::EndsWith( char const character ) const", true ), name, "Appropriate function not called" );

      stringAlt = "EndsWith0";
      TEST_ASSERT( string.EndsWith( stringAlt ), name, "did not return true for correct String" );
      stringAlt = "TestUtilString_String_EndsWith0";
      TEST_ASSERT( string.EndsWith( stringAlt ), name, "did not return true for correct String" );
      stringAlt = "UnitTestArray";
      TEST_ASSERT( string.EndsWith( stringAlt ) == false, name, "returned true for incorrect String" );
      stringAlt = "TestUtilString_String_EndsWith000";
      TEST_ASSERT( string.EndsWith( stringAlt ) == false, name, "returned true for longer String" );
      TEST_ASSERT( CheckTestCall( "bool const String::EndsWith( String const& string ) const", true ), name, "Appropriate function not called" );

      list.Clear();
      for( unsigned i = charactersLen / 2; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
      TEST_ASSERT( string.EndsWith( list ), name, "did not return true for correct Container< char >" );
      list.Clear();
      for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
      TEST_ASSERT( string.EndsWith( list ), name, "did not return true for correct Container< char >" );
      list.Clear();
      for( unsigned i = 0; i < 5; ++i ) list.PushBack( (char)( rand() ) );
      TEST_ASSERT( string.EndsWith( list ) == false, name, "returned true for incorrect Container< char >" );
      list.Clear();
      for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
      list.PushBack( '0' );
      TEST_ASSERT( string.EndsWith( list ) == false, name, "returned true for longer Container< char >" );
      TEST_ASSERT( CheckTestCall( "bool const String::EndsWith( Container< char > const& container ) const", true ), name, "Appropriate function not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_IsEmpty( char const * const name )
  {
    try
    {
      Util::String string;
      TEST_ASSERT( string.IsEmpty(), name, "did not return true for empty String" );
      TEST_ASSERT( string.IsEmpty() && string.m_size == 1, name, "returned true when m_size did not equal 1" );
      TEST_ASSERT( CheckTestCall( "bool const String::IsEmpty() const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Clear( char const * const name )
  {
    try
    {
      char characters[] = "this is a test string that will simply be cleared";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters );

      string.Clear();
      TEST_ASSERT( string.IsEmpty(), name, "did not return true for .IsEmpty() after" );
      TEST_ASSERT( string.m_size == 1, name, "did not correctly decrement m_size" );
      TEST_ASSERT( string.m_array != 0, name, "incorrectly deallocated m_array" );
      TEST_ASSERT( string.m_array[ 0 ] == '\0', name, "did not revert string to an empty, null-terminated string" );
      TEST_ASSERT( CheckTestCall( "void String::Clear()" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment0( char const * const name )
  {
    try
    {
      char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      unsigned const charactersLen = strlen( characters );
      Util::String string;

      string = characters;
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters, charactersLen ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String& String::operator=( char const * const string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment1( char const * const name )
  {
    try
    {
      char character = 'z';
      Util::String string;

      string = character;
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, &character, 1 ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String& String::operator=( char const character )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment2( char const * const name )
  {
    try
    {
      char characters[] = "123123123123123123123123456456456456456456456789789789789789789789";
      unsigned const charactersLen = strlen( characters );
      Util::String string1, string2( characters );

      string1 = string2;
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string1, string2.m_array, string2.GetStrLen() ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "String& String::operator=( String const& string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment3( char const * const name )
  {
    try
    {
      char characters[] = "C++, C#, F#, Lua, Python, Ruby, CSS, HTML, SQL";
      unsigned const charactersLen = strlen( characters );
      Util::String string;
      Util::List< char > list( characters, charactersLen );

      string = list;
      Util::Container< char >* containerPtr = dynamic_cast< Util::Container< char >* >( &list );
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstContainer( &string, containerPtr ) == 0, name, "did not initialize values correctly" );
      TEST_ASSERT( CheckTestCall( "Container< char >& String::operator=( Container< char > const& container )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EqualAndNotEqualTo0( char const * const name )
  {
    try
    {
      char characters[] = "TestUtilString_String_EqualTo0";
      Util::String string( characters );
      
      TEST_ASSERT( string == characters, name, "returned false when checking for equality of equivalent string" );
      TEST_ASSERT( ( string == "This is a non-equivalent string" ) == false, name, "returned true when checking for equality of non-equivalent string" );
      TEST_ASSERT( CheckTestCall( "bool const String::operator==( char const * const string ) const", true ), name, "Appropriate function was not called" );
      
      TEST_ASSERT( ( string != characters ) == false, name, "returned true when checking for inequality of equivalent string" );
      TEST_ASSERT( string != "This is a non-equivalent string", name, "returned false when checking for inequality of non-equivalent string" );
      TEST_ASSERT( CheckTestCall( "bool const String::operator!=( char const * const string ) const", true ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EqualAndNotEqualTo1( char const * const name )
  {
    try
    {
      char character = '^';
      Util::String string;
      
      string.Clear();
      string.PushBack( character );
      TEST_ASSERT( string == character, name, "returned false when checking for equality of equivalent character" );
      TEST_ASSERT( ( string == '1' ) == false, name, "returned true when checking for equality of non-equivalent character" );
      string = "^^^";
      TEST_ASSERT( ( string == character ) == false, name, "returned true when when checking for equality of a longer string beginning with an equivalent character" );
      TEST_ASSERT( CheckTestCall( "bool const String::operator==( char const character ) const", true ), name, "Appropriate function was not called" );
      
      string.Clear();
      string.PushBack( character );
      TEST_ASSERT( ( string != character ) == false, name, "returned true when checking for inequality of equivalent character" );
      TEST_ASSERT( string != '1', name, "returned false when checking for inequality of non-equivalent character" );
      string = "^^^";
      TEST_ASSERT( string != character, name, "returned false when when checking for inequality of a longer string beginning with an equivalent character" );
      TEST_ASSERT( CheckTestCall( "bool const String::operator!=( char const character ) const", true ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EqualAndNotEqualTo2( char const * const name )
  {
    try
    {
      char characters[] = "TestUtilString_String_EqualTo0";
      unsigned const charactersLen = strlen( characters ),
                     charactersHalfLen = charactersLen / 2;
      Util::String string1( characters ), 
                   string2( string1 ), 
                   string3;

      string3.Clear();
      string3.PushBackRange( characters, charactersHalfLen );
      TEST_ASSERT( string1 == string2, name, "returned false when checking for equality of equivalent string" );
      TEST_ASSERT( ( string1 == string3 ) == false, name, "returned true when checking for equality of non-equivalent string" );
      string3.PushBackRange( characters + charactersHalfLen, charactersLen - charactersHalfLen );
      string3.PushBackRange( "000", 3 );
      TEST_ASSERT( ( string1 == string3 ) == false, name, "returned true when checking for equality of longer string" );
      TEST_ASSERT( CheckTestCall( "bool const String::operator==( String const& string ) const", true ), name, "Appropriate function was not called" );
      
      string3.Clear();
      string3.PushBackRange( characters, charactersHalfLen );
      TEST_ASSERT( ( string1 != string2 ) == false, name, "returned true when checking for inequality of equivalent string" );
      TEST_ASSERT( string1 != string3, name, "returned false when checking for inequality of non-equivalent string" );
      string3.PushBackRange( characters + charactersHalfLen, charactersLen - charactersHalfLen );
      string3.PushBackRange( "000", 3 );
      TEST_ASSERT( string1 != string3, name, "returned false when checking for inequality of longer string" );
      TEST_ASSERT( CheckTestCall( "bool const String::operator!=( String const& string ) const", true ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition0( char const * const name )
  {
    try
    {
      char characters1[] = "This is the first part of the string,",
           characters2[] = "and this is the second part of the string";
      unsigned const charactersLen1 = strlen( characters1 ),
                     charactersLen2 = strlen( characters2 );
      Util::Vector< char > vector;
      vector.PushBackRange( characters1, charactersLen1 );
      vector.PushBackRange( characters2, charactersLen2 );
      Util::String string1( characters1 ),
                   string2 = string1 + characters2;

      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string2, vector.m_array, vector.m_size ), name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String String::operator+( char const * const string ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition1( char const * const name )
  {
    try
    {
      char characters[] = "This is the first part of the string, which will end with a 1: ";
      char character = '1';
      unsigned const charactersLen = strlen( characters );
      Util::Vector< char > vector;
      vector.PushBackRange( characters, charactersLen );
      vector.PushBack( character );
      Util::String string1( characters ),
                   string2 = string1 + character;

      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string2, vector.m_array, vector.m_size ) == 0, name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String String::operator+( char const character ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition2( char const * const name )
  {
    try
    {
      char characters1[] = "This is the first part of the string,",
           characters2[] = "and this is the second part of the string";
      unsigned const charactersLen1 = strlen( characters1 ),
                     charactersLen2 = strlen( characters2 );
      Util::Vector< char > vector;
      vector.PushBackRange( characters1, charactersLen1 );
      vector.PushBackRange( characters2, charactersLen2 );
      Util::String string1( characters1 ),
                   string2( characters2 ),
                   string3( string1 + string2 );

      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string3, vector.m_array, vector.m_size ) == 0, name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String String::operator+( String const& string ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition3( char const * const name )
  {
    try
    {
      char characters1[] = "This is the first part of the string,",
           characters2[] = "and this is the second part of the string";
      unsigned const charactersLen1 = strlen( characters1 ),
                     charactersLen2 = strlen( characters2 );
      Util::Vector< char > vector;
      vector.PushBackRange( characters1, charactersLen1 );
      vector.PushBackRange( characters2, charactersLen2 );
      Util::List< char > list( characters2, charactersLen2 );
      Util::String string1( characters1 ),
                   string2( string1 + list );

      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string2, vector.m_array, vector.m_size ) == 0, name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String String::operator+( String const& string ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_AdditionAssignment0( char const * const name )
  {
    try
    {
      char characters1[] = "This is the first part of the string,",
           characters2[] = "and this is the second part of the string";
      unsigned const charactersLen1 = strlen( characters1 ),
                     charactersLen2 = strlen( characters2 );
      Util::Vector< char > vector;
      vector.PushBackRange( characters1, charactersLen1 );
      vector.PushBackRange( characters2, charactersLen2 );
      Util::String string( characters1 );

      string += characters2;
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, vector.m_array, vector.m_size ) == 0, name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String& String::operator+=( char const * const string )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_AdditionAssignment1( char const * const name )
  {
    try
    {
      char characters[] = "This is the first part of the string, which will end with a 1: ";
      char character = '1';
      unsigned const charactersLen = strlen( characters );
      Util::Vector< char > vector;
      vector.PushBackRange( characters, charactersLen );
      vector.PushBack( character );
      Util::String string( characters );

      string += character;
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, vector.m_array, vector.m_size ) == 0, name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String String::operator+( char const character ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_AdditionAssignment2( char const * const name )
  {
    try
    {
      char characters1[] = "This is the first part of the string,",
           characters2[] = "and this is the second part of the string";
      unsigned const charactersLen1 = strlen( characters1 ),
                     charactersLen2 = strlen( characters2 );
      Util::Vector< char > vector;
      vector.PushBackRange( characters1, charactersLen1 );
      vector.PushBackRange( characters2, charactersLen2 );
      Util::String string1( characters1 ),
                   string2( characters2 );

      string1 += string2;
      TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string1, vector.m_array, vector.m_size ) == 0, name, "did not insert values correctly" );
      TEST_ASSERT( CheckTestCall( "String String::operator+( String const& string ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BitwiseLeftShiftIntAndUint( char const * const name )
  {
    try
    {
      {
        int i = 100;
        char characters[] = "100";
        unsigned const charactersLen = strlen( characters );
        Util::String string;
        string.Clear();
        string << i;
        TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters, charactersLen ) == 0, name, "did not insert values correctly" );
        TEST_ASSERT( CheckTestCall( "String& String::operator<<( int const integer )", true ), name, "Appropriate function was not called" );
      }
      
      {
        unsigned u = 2500;
        char characters[] = "2500";
        unsigned const charactersLen = strlen( characters );
        Util::String string;
        string.Clear();
        string << u;
        TEST_ASSERT( TestUtilString_Helper_CheckStringAgainstArray( &string, characters, charactersLen ) == 0, name, "did not insert values correctly" );
        TEST_ASSERT( CheckTestCall( "String& String::operator<<( unsigned const uinteger )", true ), name, "Appropriate function was not called" );
      }

    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilString
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilString );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilString, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilString
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilString );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilString, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
