
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_UtilSortedVector.h"


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
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_BasicAssignment ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_Addition ),
    T_FUNC_ARR_DEF( TestUtilSortedVector_SortedVector_AdditionAssignment )
  };


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_Constructor0 );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_Constructor1 );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_Constructor2 );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_Constructor3 );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_CopyConstructor );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_PushFront );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_PushBack );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_PushBackRange0 );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_PushBackRange1 );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_Search );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilSortedVector_SortedVector_BasicAssignment( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_BasicAssignment );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_Addition );
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
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilSortedVector, SortedVector_AdditionAssignment );
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
