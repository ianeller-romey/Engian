
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_UtilUnsafeVector.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilUnsafeVector[] = {
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_PushFront ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_PushBackRange0 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_PushBackRange1 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_BasicAssignment1 )
  };


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_Constructor2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor3( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_Constructor3 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_PushFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_PushFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_PushBackRange0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_PushBackRange0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_PushBackRange1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_PushBackRange1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_BasicAssignment0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_BasicAssignment0 );
   }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_BasicAssignment1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilUnsafeVector, UnsafeVector_BasicAssignment1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilUnsafeVector
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilUnsafeVector
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
