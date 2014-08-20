
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "objBase.h"

#include <vector>
#include <string>
#include <cstring>


namespace Test
{

  unsigned UnitTestChassis::UnitTestSampleStruct::s_numberOfDeletes = 0;
  unsigned UnitTestChassis::UnitTestSampleClass::s_numberOfDeletes = 0;
  std::vector< std::string > CalledTests;


  UnitTestChassis::UnitTestDictionaryPair::UnitTestDictionaryPair( char const * const (*function) ( char const * const ), char const * const name ) :
    Function( function ),
    Name( name ) // we can do this because we know that there will never be dynamically declared names
  {
  }


  UnitTestChassis::UnitTestSampleStruct::UnitTestSampleStruct() :
    m_int1( 0 ),
    m_int2( 0 ),
    m_int3( 0 ),
    m_referenceCount( new unsigned( 1 ) )
  {
    for( unsigned i = 0; i < 5; ++i )
      m_doubles[ i ] = 0.0;

  }

  UnitTestChassis::UnitTestSampleStruct::UnitTestSampleStruct( int int1, int int2, int int3, double* doubles ) :
    m_int1( int1 ),
    m_int2( int2 ),
    m_int3( int3 ),
    m_referenceCount( new unsigned( 1 ) )
  {
    if( doubles != 0 )
      for( unsigned i = 0; i < 5; ++i )
        m_doubles[ i ] = doubles[ i ];
    else
      for( unsigned i = 0; i < 5; ++i )
        m_doubles[ i ] = 0.0;
  }


  UnitTestChassis::UnitTestSampleStruct::UnitTestSampleStruct( UnitTestSampleStruct const& other ) :
    m_int1( other.m_int1 ),
    m_int2( other.m_int2 ),
    m_int3( other.m_int3 ),
    m_referenceCount( other.m_referenceCount )
  {
    memcpy( m_doubles, other.m_doubles, sizeof( double ) * 5 );
    ++( *m_referenceCount );
  }


  
  UnitTestChassis::UnitTestSampleStruct& UnitTestChassis::UnitTestSampleStruct::operator=( UnitTestSampleStruct const& other )
  {
    m_int1 = other.m_int1;
    m_int2 = other.m_int2;
    m_int3 = other.m_int3;
    m_referenceCount = other.m_referenceCount;
    memcpy( m_doubles, other.m_doubles, sizeof( double ) * 5 );
    ++( *m_referenceCount );
    return *this;
  }


  UnitTestChassis::UnitTestSampleStruct::~UnitTestSampleStruct()
  {
    if( --( *m_referenceCount ) <= 0 )
    {
      delete m_referenceCount;
      ++s_numberOfDeletes;
    }
  }


  bool const UnitTestChassis::UnitTestSampleStruct::operator==( UnitTestSampleStruct const& other ) const
  {
    if( m_int1 != other.m_int1 ||
      m_int2 != other.m_int2 ||
      m_int3 != other.m_int3 )
      return false;
    for( unsigned i = 0; i < 5; ++i )
      if( m_doubles[ i ] != other.m_doubles[ i ] )
        return false;
    return true;
  }


  bool const UnitTestChassis::UnitTestSampleStruct::operator!=( UnitTestSampleStruct const& other ) const
  {
    return !( *this == other );
  }


  UnitTestChassis::UnitTestSampleStruct* UnitTestChassis::UnitTestSampleStruct::CreateABunch( unsigned bunch )
  {
    UnitTestSampleStruct* aBunchOfStructs = new UnitTestSampleStruct[ bunch ];
    for( unsigned i = 0; i < bunch; ++i )
      aBunchOfStructs[ i ] = UnitTestSampleStruct( i, bunch - 1 - i, 0, 0 );
    return aBunchOfStructs;
  }


  UnitTestChassis::UnitTestSampleClass::UnitTestSampleClass() :
    m_string( 0 ),
    m_int( 0 ),
    m_referenceCount( new unsigned( 1 ) )
  {
  }


  UnitTestChassis::UnitTestSampleClass::UnitTestSampleClass( char const * const string, int i, UnitTestSampleStruct utss ) :
    m_int( i ),
    m_struct( utss ),
    m_referenceCount( new unsigned( 1 ) )
  {
    unsigned strLen = strlen( string ) + sizeof( char );
    m_string = new char[ strLen ];
    memcpy( m_string, string, strLen );
  }


  UnitTestChassis::UnitTestSampleClass::UnitTestSampleClass( UnitTestSampleClass const& other ) :
    m_string( 0 ),
    m_int( other.m_int ),
    m_struct( other.m_struct ),
    m_referenceCount( other.m_referenceCount )
  {
    unsigned strLen = strlen( other.m_string ) + sizeof( char );
    m_string = new char[ strLen ];
    memcpy( m_string, other.m_string, strLen );
    ++( *m_referenceCount );
  }


  UnitTestChassis::UnitTestSampleClass& UnitTestChassis::UnitTestSampleClass::operator=( UnitTestSampleClass const& other )
  {
    if( m_string != 0 )
      delete [] m_string;
    m_string = 0;
    m_int = other.m_int;
    m_struct = other.m_struct;
    m_referenceCount = other.m_referenceCount;

    unsigned strLen = strlen( other.m_string ) + sizeof( char );
    m_string = new char[ strLen ];
    memcpy( m_string, other.m_string, strLen );

    ++( *m_referenceCount );
    return *this;
  }


  UnitTestChassis::UnitTestSampleClass::~UnitTestSampleClass()
  {
    if( m_string != 0 )
      delete [] m_string;
    if( --( *m_referenceCount ) <= 0 )
    {
      ++s_numberOfDeletes;
      delete m_referenceCount;
    }
  }


  bool const UnitTestChassis::UnitTestSampleClass::operator==( UnitTestSampleClass const& other ) const
  {
    return strcmp( m_string, other.m_string ) == 0 && m_int == other.m_int && m_struct == other.m_struct;
  }


  bool const UnitTestChassis::UnitTestSampleClass::operator!=( UnitTestSampleClass const& other ) const
  {
    return !( *this == other );
  }


  UnitTestChassis::UnitTestSampleClass* UnitTestChassis::UnitTestSampleClass::CreateABunch( unsigned bunch )
  {
    UnitTestSampleClass* aBunchOfClasses = new UnitTestSampleClass[ bunch ];
    for( unsigned i = 0; i < bunch; ++i )
    {
      unsigned const strLen = 10 + 1;
      char strChar = (char)i;
      if( strChar == '\0' )
        ++strChar;
      char str[ strLen ];
      for( unsigned j = 0; j < strLen - 1 ; ++j )
        str[ j ] = strChar;
      str[ strLen - 1 ] = '\0';
      aBunchOfClasses[ i ] = UnitTestSampleClass( str, i, UnitTestSampleStruct( 0 - (int)i, i, 0, NULL ) );
    }
    return aBunchOfClasses;
  }
  

  void UnitTestChassis::GetTests_UnitTests( UnitTestDictionaryPair const * const unitTestArray, int const numTests, char*** allTests )
  {
    char const** const testNames = new char const*[ numTests ];
      
    for( unsigned i = 0; i < numTests; ++i )
      testNames[ i ] = unitTestArray[ i ].Name;
      
    *allTests = UnitTestChassis::MarshalArrayOfStrings( testNames, numTests );
    delete[] testNames;
  }


  void UnitTestChassis::RunTests_UnitTests
  (
    UnitTestDictionaryPair const * const unitTestArray,
    int const numUnitTests,
    char** const testsToRun, 
    int const numTestsToRun,
    char*** allResults
  )
  {
    char const** const testResults = new char const*[ numTestsToRun ];

    for( unsigned i = 0; i < numTestsToRun; ++i )
    {
      for( unsigned j = 0; j < numUnitTests; ++j )
      {
        if( strcmp( unitTestArray[ j ].Name, testsToRun[ i ] ) == 0 )
        {
          char const * const (*func) ( char const * const ) = unitTestArray[ j ].Function;
          UnitTestChassis::Reset();
          testResults[ i ] = func( testsToRun[ i ] );
        }
      }
    }

    *allResults = UnitTestChassis::MarshalArrayOfStrings( testResults, numTestsToRun );

    for( unsigned i = 0; i < numTestsToRun; ++i )
      if( testResults[ i ] != 0 )
        delete [] testResults[ i ];
    delete [] testResults;
  }


  char* UnitTestChassis::MarshalString( char const * const string )
  {
    if( string == 0 )
      return 0;

    unsigned strLen = strlen( string ) + sizeof( char );
    char* forReturn = ( char* )::CoTaskMemAlloc( strLen );
    memcpy( forReturn, string, strLen );

    return forReturn;
  }


  char** UnitTestChassis::MarshalArrayOfStrings( char const * const * const strings, unsigned numStrings )
  {
    if( strings == 0 )
      return 0;

    char** forReturn = ( char** )::CoTaskMemAlloc( sizeof( char* ) * numStrings );
    memset( forReturn, 0, sizeof( char* ) * numStrings );

    for( unsigned i = 0; i < numStrings; ++i )
      forReturn[ i ] = MarshalString( strings[ i ] );

    return forReturn;
  }


  char const * const UnitTestChassis::TestFailureText( char const * const testName, char const * const fileName, char const * const lineNumber, char const * const failedReason )
  {
    char const 
      * const str1 = "TEST {",
      * const str2 = "}\r\nin FILE {",
      * const str3 = "}\r\nat LINE {",
      * const str4 = "}\r\nfailed:\r\n";
    char * const string = new char[ strlen( str1 ) + strlen( testName ) + 
                    strlen( str2 ) + strlen( fileName ) + 
                    strlen( str3 ) + strlen( lineNumber ) +
                    strlen( str4 ) + strlen( failedReason ) + 1 ];
    int incr = 0, len = strlen( str1 );
    memcpy( string + incr, str1, len );

    incr += len;
    len = strlen( testName );
    memcpy( string + incr, testName, len );

    incr += len;
    len = strlen( str2 );
    memcpy( string + incr, str2, len );
        
    incr += len;
    len = strlen( fileName );
    memcpy( string + incr, fileName, len );

    incr += len;
    len = strlen( str3 );
    memcpy( string + incr, str3, len );
        
    incr += len;
    len = strlen( lineNumber );
    memcpy( string + incr, lineNumber, len );
        
    incr += len;
    len = strlen( str4 );
    memcpy( string + incr, str4, len );
        
    incr += len;
    len = strlen( failedReason );
    memcpy( string + incr, failedReason, len );
        
    incr += len;
    len = 1;
    memcpy( string + incr, "\0", len );

    return string;
  }


  void UnitTestChassis::TrackTestCall( char const * const testName )
  {
    std::string testNameStr( testName );
    CalledTests.push_back( testNameStr );
  }


  bool const UnitTestChassis::CheckTestCall( char const * const testName, bool clear )
  {
    bool const success = std::find( CalledTests.begin(), CalledTests.end(), std::string( testName ) ) != CalledTests.end();
    if( clear )
      ClearTestCalls();
    return success;
  }


  void UnitTestChassis::ClearTestCalls()
  {
    CalledTests.clear();
    // this is just an abitrary starting point, but it seems pretty reasonable
    CalledTests.reserve( 150 );
  }


  void UnitTestChassis::Reset()
  {
    UnitTestSampleStruct::s_numberOfDeletes = 0;
    UnitTestSampleClass::s_numberOfDeletes = 0;
    ClearTestCalls();
  }

}

#endif
