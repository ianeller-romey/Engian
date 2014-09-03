
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_UtilVector.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilVector[] = {
    T_FUNC_ARR_DEF( TestUtilVector_VectorIteratorImpl_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilVector_VectorIteratorImpl_AdvanceValue ),
    T_FUNC_ARR_DEF( TestUtilVector_VectorIteratorImpl_GetValue ),
    T_FUNC_ARR_DEF( TestUtilVector_VectorIteratorImpl_EqualTo ),
    T_FUNC_ARR_DEF( TestUtilVector_VectorIteratorImpl_NotEqualTo ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Begin ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_End ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_PushFront ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_PushBack ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_PopFront ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_PopBack ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_PopFirst ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_PopAll ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Contains ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_IsFull ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_GetCapacity ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Clear ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_ArraySubscript ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Addition ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_AdditionAssignment ),
    T_FUNC_ARR_DEF( TestUtilVector_Vector_Indirection )
  };


  char const * const UnitTestChassis::TestUtilVector_VectorIteratorImpl_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, VectorIteratorImpl_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_VectorIteratorImpl_AdvanceValue( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, VectorIteratorImpl_AdvanceValue );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_VectorIteratorImpl_GetValue( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, VectorIteratorImpl_GetValue );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_VectorIteratorImpl_EqualTo( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, VectorIteratorImpl_EqualTo );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_VectorIteratorImpl_NotEqualTo( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, VectorIteratorImpl_NotEqualTo );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }
  

  char const * const UnitTestChassis::TestUtilVector_Vector_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Constructor2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Constructor2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Constructor3( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Constructor3 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Begin( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Begin );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_End( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_End );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_PushFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_PushFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_PushBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_PushBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_PopFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_PopFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_PopBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_PopBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_PopFirst( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_PopFirst );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_PopAll( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_PopAll );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Contains( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Contains );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_IsFull( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_IsFull );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_GetCapacity( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_GetCapacity );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Clear( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Clear );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_BasicAssignment0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_BasicAssignment0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_BasicAssignment1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_BasicAssignment1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_ArraySubscript( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_ArraySubscript );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Addition( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Addition );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_AdditionAssignment( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_AdditionAssignment );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilVector_Vector_Indirection( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilVector, Vector_Indirection );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilVector
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilVector );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilVector, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilVector
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilVector );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilVector, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
