
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_UtilList.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilList[] = {
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_AdvanceValue ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_GetValue ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_EqualTo ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_NotEqualTo ),
    T_FUNC_ARR_DEF( TestUtilList_List_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilList_List_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilList_List_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilList_List_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilList_List_Begin ),
    T_FUNC_ARR_DEF( TestUtilList_List_End ),
    T_FUNC_ARR_DEF( TestUtilList_List_PushFront ),
    T_FUNC_ARR_DEF( TestUtilList_List_PushBack ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopFront ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopBack ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopFirst ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopAll ),
    T_FUNC_ARR_DEF( TestUtilList_List_Contains ),
    T_FUNC_ARR_DEF( TestUtilList_List_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilList_List_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilList_List_Addition ),
    T_FUNC_ARR_DEF( TestUtilList_List_AdditionAssignment )
  };


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, ListIteratorImpl_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_AdvanceValue( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, ListIteratorImpl_AdvanceValue );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_GetValue( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, ListIteratorImpl_GetValue );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_EqualTo( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, ListIteratorImpl_EqualTo );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_NotEqualTo( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, ListIteratorImpl_NotEqualTo );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Constructor2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_Constructor2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Begin( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_Begin );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_End( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_End );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PushFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_PushFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PushBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_PushBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_PopFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_PopBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopFirst( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_PopFirst );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopAll( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_PopAll );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Contains( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_Contains );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_BasicAssignment0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_BasicAssignment0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_BasicAssignment1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_BasicAssignment1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Addition( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_Addition );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_AdditionAssignment( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilList, List_AdditionAssignment );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilList
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilList );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilList, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilList
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilList );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilList, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
