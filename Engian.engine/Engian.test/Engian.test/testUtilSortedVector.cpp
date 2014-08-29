
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "utilSortedVector.h"
#include "utilString.h"

#include "testUnitTestHelper.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilSortedVector[] = {
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_PushFront ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_PushBack ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_PushBackRange0 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_PushBackRange1 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Search ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_ShiftAndPush ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_FindInsertionIndex ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_QuickSort ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Addition ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_AdditionAssignment )
  };


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor0( char const * const name )
  {
    try
    {      
      Util::SortedVector< int > sVector;
      
      TEST_ASSERT( UnitTestHelper::CheckUtilVectorInit< int >( sVector, UnitTestHelper::GetUtilVectorDefaultCapacity< int >(), 0 ) == 0 );
      TEST_ASSERT( UnitTestHelper::CheckUtilSortedVector< int >( sVector ) == 0 );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "SortedVector< T >::SortedVector()" ) );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor1( char const * const name )
  {
    try
    {
      unsigned const number = 1111;
      Util::SortedVector< int > sVector( number );

      TEST_ASSERT( UnitTestHelper::CheckUtilVectorInit< int >( sVector, number, 0 ) == 0 );
      TEST_ASSERT( UnitTestHelper::CheckUtilSortedVector< int >( sVector ) == 0 );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "SortedVector< T >::SortedVector()" ) );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor2( char const * const name )
  {
    try
    {
      UnitTestSampleClass classes[] = { UnitTestSampleClass( "test1", 1, UnitTestSampleStruct( 1, 1, 1, 0 ) ),
                                        UnitTestSampleClass( "test3", 3, UnitTestSampleStruct( 3, 3, 3, 0 ) ),
                                        UnitTestSampleClass( "test5", 5, UnitTestSampleStruct( 5, 5, 5, 0 ) ),
                                        UnitTestSampleClass( "test0", 0, UnitTestSampleStruct( 0, 0, 0, 0 ) ),
                                        UnitTestSampleClass( "test6", 6, UnitTestSampleStruct( 6, 6, 6, 0 ) ) };
      unsigned const size = sizeof( classes ) / sizeof( UnitTestSampleClass );
      Util::SortedVector< UnitTestSampleClass > sVector( classes, size );

      TEST_ASSERT( UnitTestHelper::CheckUtilVectorInit< UnitTestSampleClass >( sVector, size, size ) == 0 );
      TEST_ASSERT( UnitTestHelper::CheckUtilSortedVector< UnitTestSampleClass >( sVector ) == 0 );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< UnitTestSampleClass >, "SortedVector< T >::SortedVector( T const * const tArray, unsigned const size )" ) );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor3( char const * const name )
  {
    try
    {
      char characters[] = "a907gyadkjafa;dt4q938qapioucvhasd8uafu(_&*GY_(Q*Y_C(&GQW)*R!@#)+F)KX()*FGEQW()G&+E()FU*+_";
      unsigned const charactersLen = strlen( characters );
      Util::String string( characters );
      Util::SortedVector< char > sVector( string );
      
      TEST_ASSERT( UnitTestHelper::CheckUtilVectorInit< char >( sVector, 
                                                                UnitTestHelper::GetUtilContainerSize< char >( string ), 
                                                                UnitTestHelper::GetUtilContainerSize< char >( string ) ) == 0 );
      TEST_ASSERT( UnitTestHelper::CheckUtilSortedVector< char >( sVector ) == 0 );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< char >, "TestUtilSortedVector_SortedVector_Constructor3" ) );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_CopyConstructor" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_PushFront( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_PushFront" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_PushBack( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_PushBack" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_PushBackRange0( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_PushBackRange0" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_PushBackRange1( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_PushBackRange1" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Search( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_Search" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_ShiftAndPush( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_ShiftAndPush" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_FindInsertionIndex( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_FindInsertionIndex" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_QuickSort( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_QuickSort" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_BasicAssignment0( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_BasicAssignment0" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_BasicAssignment1( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_BasicAssignment1" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Addition( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_Addition" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_AdditionAssignment( char const * const name )
  {
    try
    {
      TEST_ASSERT( DFT_FUNC_CHECK( Util::SortedVector< int >, "TestUtilSortedVector_SortedVector_AdditionAssignment" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilSortedVector
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilSortedVector );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilSortedVector, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilSortedVector
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilSortedVector );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilSortedVector, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
