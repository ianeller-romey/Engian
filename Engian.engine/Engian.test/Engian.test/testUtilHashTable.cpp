
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_UtilHashTable.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilHashTable[] = {
    T_FUNC_ARR_DEF( TestUtilHashTable_KeyedIterator_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilHashTable_KeyedIterator_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_KeyedIterator_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_KeyedIterator_Key ),
    T_FUNC_ARR_DEF( TestUtilHashTable_KeyedIterator_PrefixIncrement ),
    T_FUNC_ARR_DEF( TestUtilHashTable_KeyedIterator_BasicAssignment ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_Clone ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_Key ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_AdvanceValue ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_GetValue ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_GetKey ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_EqualTo ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_NotEqualTo ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTableIteratorImpl_BasicAssignment ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor4 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor5 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Constructor6 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Begin ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_End ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_KeyedBegin ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_KeyedEnd ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_PushFront ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_PushBack ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Push0 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Push1 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_PopFront ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_PopBack ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_PopFirst ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_PopAll ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Pop ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_GetKeys ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_GetCapacity ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Clear0 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Clear1 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_CheckAndGrow ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Grow ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Deallocate ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_CreateKeyedIteratorFromImplementation ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_ArraySubscript ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_Addition ),
    T_FUNC_ARR_DEF( TestUtilHashTable_HashTable_AdditionAssignment ),
  };

  char const * const UnitTestChassis::TestUtilHashTable_KeyedIterator_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, KeyedIterator_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_KeyedIterator_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, KeyedIterator_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_KeyedIterator_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, KeyedIterator_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_KeyedIterator_Key( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, KeyedIterator_Key );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_KeyedIterator_PrefixIncrement( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, KeyedIterator_PrefixIncrement );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_KeyedIterator_BasicAssignment( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, KeyedIterator_BasicAssignment );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_Clone( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_Clone );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_Key( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_Key );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_AdvanceValue( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_AdvanceValue );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_GetValue( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_GetValue );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_GetKey( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_GetKey );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_EqualTo( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_EqualTo );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_NotEqualTo( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_NotEqualTo );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTableIteratorImpl_BasicAssignment( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTableIteratorImpl_BasicAssignment );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor3( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor3 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor4( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor4 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor5( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor5 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Constructor6( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Constructor6 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Begin( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Begin );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_End( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_End );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_KeyedBegin( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_KeyedBegin );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_KeyedEnd( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_KeyedEnd );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_PushFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_PushFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_PushBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_PushBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Push0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Push0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Push1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Push1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_PopFront( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_PopFront );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_PopBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_PopBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_PopFirst( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_PopFirst );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_PopAll( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_PopAll );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Pop( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Pop );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_GetKeys( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_GetKeys );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_GetCapacity( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_GetCapacity );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Clear0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Clear0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Clear1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Clear1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_CheckAndGrow( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_CheckAndGrow );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Grow( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Grow );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Deallocate( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Deallocate );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_CreateKeyedIteratorFromImplementation( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_CreateKeyedIteratorFromImplementation );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_BasicAssignment0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_BasicAssignment0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_BasicAssignment1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_BasicAssignment1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_ArraySubscript( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_ArraySubscript );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_Addition( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_Addition );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilHashTable_HashTable_AdditionAssignment( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilHashTable, HashTable_AdditionAssignment );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilHashTable
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilHashTable );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilHashTable, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilHashTable
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilHashTable );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilHashTable, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
