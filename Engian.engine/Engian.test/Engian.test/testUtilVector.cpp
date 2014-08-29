
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
      TEST_ASSERT( TestHelper_UtilVector::VectorIteratorImpl_Constructor0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::VectorIteratorImpl_AdvanceValue() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::VectorIteratorImpl_GetValue() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::VectorIteratorImpl_EqualTo() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::VectorIteratorImpl_NotEqualTo() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Constructor0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Constructor1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Constructor2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Constructor3() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_CopyConstructor() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Begin() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_End() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_PushFront() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_PushBack() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_PopFront() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_PopBack() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_PopFirst() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_PopAll() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Contains() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_IsFull() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_GetCapacity() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Clear() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_BasicAssignment0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_BasicAssignment1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_ArraySubscript() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Addition() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_AdditionAssignment() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilVector::Vector_Indirection() == 0, name, "" );
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
