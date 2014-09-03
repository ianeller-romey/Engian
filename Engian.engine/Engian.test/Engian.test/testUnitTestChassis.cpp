
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "objBase.h"

#include <cstring>


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair::UnitTestDictionaryPair( char const * const (*function) ( char const * const ), char const * const name ) :
    Function( function ),
    Name( name ) // we can do this because we know that there will never be dynamically declared names
  {
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


  void UnitTestChassis::Reset()
  {
  }

}

#endif
