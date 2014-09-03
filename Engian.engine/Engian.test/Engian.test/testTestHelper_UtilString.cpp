
#include "testTestHelper_UtilString.h"
#include "testTestHelper_UtilVector.h"
#include "testTestHelper_UtilContainer.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilString.h"
#include "utilList.h"


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

  unsigned const TestHelper_UtilString::String_Constructor0()
  {
    Util::String string;

    RETURNLINEIFFAILED( CheckUtilStringInit( string, Util::String::c_defaultCapacity, 0 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, "", 0 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String::String()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Constructor1()
  {
    unsigned const capacity = 200;
    Util::String string( capacity );
    RETURNLINEIFFAILED( CheckUtilStringInit( string, capacity, 0 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, "", 0 ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String::String( unsigned const capacity )" ) );
    return 0;         
  }


  unsigned const TestHelper_UtilString::String_Constructor2()
  {
    char const * const characters = "The quick brown fox jumps over the lazy dog.";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters );
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1 ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String::String( char const * const string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Constructor3()
  {
    char const character = 'I';
    Util::String string( character );
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string, 2, 2 ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, &character, 1 ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String::String( char const character )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Constructor4()
  {
    char characters[] = "abcdefghijklmnopqrstuvwxyz";
    unsigned const charactersLen = strlen( characters );
    Util::List< char > list( characters, charactersLen );
    Util::String string( list );
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string, TestHelper_UtilContainer::GetUtilContainerSize( list ) ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstContainer( string, list ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String::String( Container< char > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_CopyConstructor()
  {
    char const * const characters = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.";
    unsigned const charactersLen = strlen( characters );
    Util::String string1( characters ),
                  string2( string1 );

    RETURNLINEIFFAILED( CheckUtilStringInit( string2, string1.m_capacity, string1.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstContainer( string2, string1 ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String::String( String const& string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_PushBack()
  {
    char characters[] = "THIS IS A STRING THAT I'M QUITE HAPPY TO USE TO TEST MY DATA STRUCTURES!";
    unsigned const charactersLen = strlen( characters );
    Util::String string;
    for( unsigned i = 0; i < charactersLen; ++i )
      string.PushBack( characters[ i ] );
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1 ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters ) == 0 );      
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "void String::PushBack( char const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_PushBackRange0()
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

    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLenAll + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, 
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ),
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "void String::PushBackRange( char const * const string )" ) );
    return 0;
                   
  }


  unsigned const TestHelper_UtilString::String_PushBackRange1()
  {
    char characters[] = "this test string will be inserted several characters at a time";
    unsigned const charactersLen = strlen( characters );
    Util::String string;
    for( unsigned i = 0, incr = 5; i < charactersLen; i += incr )
      string.PushBackRange( characters + i, ( charactersLen - i < incr ) ? charactersLen - i : incr );
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "void String::PushBackRange( char const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_PushBackRange2()
  {
    char characters[] = "this test string is pretty much like every other test string";
    unsigned const charactersLen = strlen( characters );
    Util::String string1,
                  string2( characters );
    string1.PushBackRange( string2 );
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string1, string2.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string1, characters ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "void String::PushBackRange( String const& string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_PopBack()
  {
    char characters[] = "~!@#$%^&*()_+=-0987654321`";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters );

    for( int i = charactersLen; i > 0; --i )
    {
      string.PopBack();
      RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1, i - 1 ) == 0 );
                     
      RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters, i - 1 ) == 0 );
    }
    RETURNLINEIFFAILED( string.IsEmpty() );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "void String::PopBack()" ) );
                   
    // check for exceptions
    string.PopBack();
    return 0;
  }


  unsigned const TestHelper_UtilString::String_GetStrLen()
  {
    char characters[] = "this STRING will BE used TO test THE GetStrLen MEMBER function";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters );

    RETURNLINEIFFAILED( string.GetStrLen() == charactersLen );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "unsigned const String::GetStrLen() const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_BeginsWith()
  {
    char characters[] = "TestUtilString_String_BeginsWith0";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters ), stringAlt;
    Util::List< char > list;

    RETURNLINEIFFAILED( string.BeginsWith( "Test" ) );
    RETURNLINEIFFAILED( string.BeginsWith( "TestUtilString_String_BeginsWith0" ) );
    RETURNLINEIFFAILED( string.BeginsWith( "TestUtilVector" ) == false );
    RETURNLINEIFFAILED( string.BeginsWith( "TestUtilString_String_BeginsWith000" ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::BeginsWith( char const * const string ) const", true ) );

    RETURNLINEIFFAILED( string.BeginsWith( "Test", 3 ) );
    RETURNLINEIFFAILED( string.BeginsWith( "TestUtilString_String_BeginsWith0", charactersLen ) );
    RETURNLINEIFFAILED( string.BeginsWith( "TestUtilVector", 10 ) == false );
    RETURNLINEIFFAILED( string.BeginsWith( "TestUtilString_String_BeginsWith000", 34 ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::BeginsWith( char const * const string, unsigned strLen ) const", true ) );

    RETURNLINEIFFAILED( string.BeginsWith( 'T' ) );
    RETURNLINEIFFAILED( string.BeginsWith( 't' ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::BeginsWith( char const character ) const", true ) );

    stringAlt = "TestUtilString";
    RETURNLINEIFFAILED( string.BeginsWith( stringAlt ) );
    stringAlt = "TestUtilString_String_BeginsWith0";
    RETURNLINEIFFAILED( string.BeginsWith( stringAlt ) );
    stringAlt = "UnitTestArray";
    RETURNLINEIFFAILED( string.BeginsWith( stringAlt ) == false );
    stringAlt = "TestUtilString_String_BeginsWith000";
    RETURNLINEIFFAILED( string.BeginsWith( stringAlt ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::BeginsWith( String const& string ) const", true ) );

    list.Clear();
    for( unsigned i = 0, j = charactersLen / 2; i < j; ++i ) list.PushBack( characters[ i ] );
    RETURNLINEIFFAILED( string.BeginsWith( list ) );
    list.Clear();
    for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
    RETURNLINEIFFAILED( string.BeginsWith( list ) );
    list.Clear();
    for( unsigned i = 0; i < 5; ++i ) list.PushBack( (char)( rand() ) );
    RETURNLINEIFFAILED( string.BeginsWith( list ) == false );
    list.Clear();
    for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
    list.PushBack( '0' );
    RETURNLINEIFFAILED( string.BeginsWith( list ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::BeginsWith( Container< char > const& container ) const", true ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_EndsWith()
  {
    char characters[] = "TestUtilString_String_EndsWith0";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters ), stringAlt;
    Util::List< char > list;

    RETURNLINEIFFAILED( string.EndsWith( "EndsWith0" ) );
    RETURNLINEIFFAILED( string.EndsWith( "TestUtilString_String_EndsWith0" ) );
    RETURNLINEIFFAILED( string.EndsWith( "TestUtilVector" ) == false );
    RETURNLINEIFFAILED( string.EndsWith( "TestUtilString_String_EndsWith000" ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::EndsWith( char const * const string ) const", true ) );

    RETURNLINEIFFAILED( string.EndsWith( "With0With0With0", 5 ) );
    RETURNLINEIFFAILED( string.EndsWith( "TestUtilString_String_EndsWith0", charactersLen ) );
    RETURNLINEIFFAILED( string.EndsWith( "TestUtilVector", 10 ) == false );
    RETURNLINEIFFAILED( string.EndsWith( "TestUtilString_String_EndsWith000", 34 ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::EndsWith( char const * const string, unsigned strLen ) const", true ) );

    RETURNLINEIFFAILED( string.EndsWith( '0' ) );
    RETURNLINEIFFAILED( string.EndsWith( 't' ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::EndsWith( char const character ) const", true ) );

    stringAlt = "EndsWith0";
    RETURNLINEIFFAILED( string.EndsWith( stringAlt ) );
    stringAlt = "TestUtilString_String_EndsWith0";
    RETURNLINEIFFAILED( string.EndsWith( stringAlt ) );
    stringAlt = "UnitTestArray";
    RETURNLINEIFFAILED( string.EndsWith( stringAlt ) == false );
    stringAlt = "TestUtilString_String_EndsWith000";
    RETURNLINEIFFAILED( string.EndsWith( stringAlt ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::EndsWith( String const& string ) const", true ) );

    list.Clear();
    for( unsigned i = charactersLen / 2; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
    RETURNLINEIFFAILED( string.EndsWith( list ) );
    list.Clear();
    for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
    RETURNLINEIFFAILED( string.EndsWith( list ) );
    list.Clear();
    for( unsigned i = 0; i < 5; ++i ) list.PushBack( (char)( rand() ) );
    RETURNLINEIFFAILED( string.EndsWith( list ) == false );
    list.Clear();
    for( unsigned i = 0; i < charactersLen; ++i ) list.PushBack( characters[ i ] );
    list.PushBack( '0' );
    RETURNLINEIFFAILED( string.EndsWith( list ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::EndsWith( Container< char > const& container ) const", true ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_IsEmpty()
  {
    Util::String string;

    RETURNLINEIFFAILED( string.IsEmpty() );
    RETURNLINEIFFAILED( string.IsEmpty() && string.m_size == 1 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::IsEmpty() const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Clear()
  {
    char characters[] = "this is a test string that will simply be cleared";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters );

    string.Clear();
    RETURNLINEIFFAILED( string.IsEmpty() );
    RETURNLINEIFFAILED( string.m_size == 1 );
    RETURNLINEIFFAILED( string.m_array != 0 );
    RETURNLINEIFFAILED( string.m_array[ 0 ] == '\0' );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "void String::Clear()" ) );
  }


  unsigned const TestHelper_UtilString::String_BasicAssignment0()
  {
    char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned const charactersLen = strlen( characters );
    Util::String string;

    string = characters;
    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1, charactersLen + 1 ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters, charactersLen ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator=( char const * const string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_BasicAssignment1()
  {
    char character = 'z';
    Util::String string;

    string = character;
    RETURNLINEIFFAILED( CheckUtilStringInit( string, 2, 2 ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, &character, 1 ) == 0 );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator=( char const character )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_BasicAssignment2()
  {
    char characters[] = "123123123123123123123123456456456456456456456789789789789789789789";
    unsigned const charactersLen = strlen( characters );
    Util::String string1, string2( characters );

    string1 = string2;
    RETURNLINEIFFAILED( CheckUtilStringInit( string1, string2.m_size, string2.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string1, string2.m_array, string2.GetStrLen() ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator=( String const& string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_BasicAssignment3()
  {
    char characters[] = "C++, C#, F#, Lua, Python, Ruby, CSS, HTML, SQL";
    unsigned const charactersLen = strlen( characters );
    Util::String string;
    Util::List< char > list( characters, charactersLen );

    string = list;
    RETURNLINEIFFAILED( CheckUtilStringInit( string, 
                                              TestHelper_UtilContainer::GetUtilContainerSize( list ), 
                                              TestHelper_UtilContainer::GetUtilContainerSize( list ) ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstContainer( string, list ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "Container< char >& String::operator=( Container< char > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_EqualAndNotEqualTo0()
  {
    char characters[] = "TestUtilString_String_EqualTo0";
    Util::String string( characters );
      
    RETURNLINEIFFAILED( string == characters );
    RETURNLINEIFFAILED( ( string == "This is a non-equivalent string" ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::operator==( char const * const string ) const", true ) );
                         
    RETURNLINEIFFAILED( ( string != characters ) == false );
    RETURNLINEIFFAILED( string != "This is a non-equivalent string" );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::operator!=( char const * const string ) const", true ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_EqualAndNotEqualTo1()
  {
    char character = '^';
    Util::String string;
      
    string.Clear();
    string.PushBack( character );
    RETURNLINEIFFAILED( string == character );
    RETURNLINEIFFAILED( ( string == '1' ) == false );
    string = "^^^";
    RETURNLINEIFFAILED( ( string == character ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::operator==( char const character ) const", true ) );
                  
    string.Clear();
    string.PushBack( character );
    RETURNLINEIFFAILED( ( string != character ) == false );
    RETURNLINEIFFAILED( string != '1' );
    string = "^^^";
    RETURNLINEIFFAILED( string != character );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::operator!=( char const character ) const", true ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_EqualAndNotEqualTo2()
  {
    char characters[] = "TestUtilString_String_EqualTo0";
    unsigned const charactersLen = strlen( characters ),
                    charactersHalfLen = charactersLen / 2;
    Util::String string1( characters ), 
                  string2( string1 ), 
                  string3;

    string3.Clear();
    string3.PushBackRange( characters, charactersHalfLen );
    RETURNLINEIFFAILED( string1 == string2 );
    RETURNLINEIFFAILED( ( string1 == string3 ) == false );
    string3.PushBackRange( characters + charactersHalfLen, charactersLen - charactersHalfLen );
    string3.PushBackRange( "000", 3 );
    RETURNLINEIFFAILED( ( string1 == string3 ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::operator==( String const& string ) const", true ) );
                         
    string3.Clear();
    string3.PushBackRange( characters, charactersHalfLen );
    RETURNLINEIFFAILED( ( string1 != string2 ) == false );
    RETURNLINEIFFAILED( string1 != string3 );
    string3.PushBackRange( characters + charactersHalfLen, charactersLen - charactersHalfLen );
    string3.PushBackRange( "000", 3 );
    RETURNLINEIFFAILED( string1 != string3 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "bool const String::operator!=( String const& string ) const", true ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Addition0()
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
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string2, charactersLen1 + charactersLen2 + 1 ) == 0 );                   
    RETURNLINEIFFAILED( CheckUtilStringAgainstContainer( string2, vector ) );                   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String String::operator+( char const * const string ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Addition1()
  {
    char characters[] = "This is the first part of the string, which will end with a 1: ";
    char character = '1';
    unsigned const charactersLen = strlen( characters );
    Util::Vector< char > vector;
    vector.PushBackRange( characters, charactersLen );
    vector.PushBack( character );
    Util::String string1( characters ),
                  string2 = string1 + character;
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string2, charactersLen + 1 + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string2, 
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ), 
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String String::operator+( char const character ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Addition2()
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
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string3, charactersLen1 + charactersLen2 + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string3,
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ), 
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String String::operator+( String const& string ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_Addition3()
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
      
    RETURNLINEIFFAILED( CheckUtilStringInit( string2, charactersLen1 + charactersLen2 + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string2,
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ), 
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String String::operator+( Container< char > const& container ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_AdditionAssignment0()
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
    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen1 + charactersLen2 + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string,
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ), 
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator+=( char const * const string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_AdditionAssignment1()
  {
    char characters[] = "This is the first part of the string, which will end with a 1: ";
    char character = '1';
    unsigned const charactersLen = strlen( characters );
    Util::Vector< char > vector;
    vector.PushBackRange( characters, charactersLen );
    vector.PushBack( character );
    Util::String string( characters );

    string += character;
    RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1 + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string,
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ), 
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator+=( char const character )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_AdditionAssignment2()
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
    RETURNLINEIFFAILED( CheckUtilStringInit( string1, charactersLen1 + charactersLen2 + 1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string1,
                                                      TestHelper_UtilVector::GetUtilVectorArray( vector ), 
                                                      TestHelper_UtilContainer::GetUtilContainerSize( vector ) ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator+=( String const& string )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilString::String_BitwiseLeftShiftIntAndUint()
  {
    {
      int i = -100;
      char characters[] = "-100";
      unsigned const charactersLen = strlen( characters );
      Util::String string;
      string.Clear();

      string << i;
      RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1 ) == 0 );                     
      RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters, charactersLen ) == 0 );                     
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator<<( int const integer )", true ) );                     
    }
      
    {
      unsigned u = 2500;
      char characters[] = "2500";
      unsigned const charactersLen = strlen( characters );
      Util::String string;
      string.Clear();

      string << u;
      RETURNLINEIFFAILED( CheckUtilStringInit( string, charactersLen + 1 ) == 0 );                     
      RETURNLINEIFFAILED( CheckUtilStringAgainstArray( string, characters, charactersLen ) == 0 );                     
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::String, "String& String::operator<<( unsigned const uinteger )", true ) );
    }
    return 0;  
  }
     

  unsigned const TestHelper_UtilString::CheckUtilStringInit( Util::String const& string, unsigned const capacity, unsigned const size )
  {
    RETURNLINEIFFAILED( string.m_capacity == capacity );
    return CheckUtilStringInit( string, size );
  }
    
    
  unsigned const TestHelper_UtilString::CheckUtilStringInit( Util::String const& string, unsigned const size )
  {
    RETURNLINEIFFAILED( string.m_size == size );
    RETURNLINEIFFAILED( string.m_array != 0 );
    RETURNLINEIFFAILED( string.m_implementations == 0 );
    return 0;
  }
    

  unsigned const TestHelper_UtilString::CheckUtilStringAgainstArray( Util::String const& string, char const * const compareAgainst )
  {
    unsigned const compareAgainstLen = strlen( compareAgainst );
    return CheckUtilStringAgainstArray( string, compareAgainst, compareAgainstLen );
  }
  

  unsigned const TestHelper_UtilString::CheckUtilStringAgainstArray( Util::String const& string, 
                                                          char const * const compareAgainst, 
                                                          unsigned const compareAgainstLen )
  {    
    RETURNLINEIFFAILED( strncmp( string.m_array, compareAgainst, compareAgainstLen ) == 0 );
    RETURNLINEIFFAILED( string.m_array[ compareAgainstLen ] == '\0' );
    RETURNLINEIFFAILED( string.m_implementations == 0 );
    return 0;
  }
  

  unsigned const TestHelper_UtilString::CheckUtilStringAgainstContainer( Util::String const& string, Util::Container< char > const& container )
  {
    Util::Container< char >::Iterator itB = container.Begin(),
                                      itE = container.End();
    for( unsigned i = 0; itB != itE; ++itB, ++i )
      RETURNLINEIFFAILED( string.m_array[ i ] == itB.Get() );
    RETURNLINEIFFAILED( string.m_array[ container.GetSize() ] == '\0' );
    RETURNLINEIFFAILED( string.m_implementations == 0 );
    return 0;
  }

}
