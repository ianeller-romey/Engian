
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_UtilString.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilString[] = {
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Constructor4 ),
    T_FUNC_ARR_DEF( TestUtilString_String_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBack ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBackRange0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBackRange1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_PushBackRange2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_PopBack ),
    T_FUNC_ARR_DEF( TestUtilString_String_GetStrLen ),
    T_FUNC_ARR_DEF( TestUtilString_String_BeginsWith ),
    T_FUNC_ARR_DEF( TestUtilString_String_EndsWith ),
    T_FUNC_ARR_DEF( TestUtilString_String_IsEmpty ),
    T_FUNC_ARR_DEF( TestUtilString_String_Clear ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BasicAssignment3 ),
    T_FUNC_ARR_DEF( TestUtilString_String_EqualAndNotEqualTo0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_EqualAndNotEqualTo1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_EqualAndNotEqualTo2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_Addition3 ),
    T_FUNC_ARR_DEF( TestUtilString_String_AdditionAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilString_String_AdditionAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilString_String_AdditionAssignment2 ),
    T_FUNC_ARR_DEF( TestUtilString_String_BitwiseLeftShiftIntAndUint )
  };


  char const * const UnitTestChassis::TestUtilString_String_Constructor0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Constructor0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Constructor1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Constructor2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor3( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Constructor3 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Constructor4( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Constructor4 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_CopyConstructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_CopyConstructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_PushBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBackRange0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_PushBackRange0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBackRange1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_PushBackRange1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PushBackRange2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_PushBackRange2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_PopBack( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_PopBack );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_GetStrLen( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_GetStrLen );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BeginsWith( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_BeginsWith );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EndsWith( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_EndsWith );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_IsEmpty( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_IsEmpty );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Clear( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Clear );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_BasicAssignment0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_BasicAssignment1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_BasicAssignment2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BasicAssignment3( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_BasicAssignment3 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EqualAndNotEqualTo0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_EqualAndNotEqualTo0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EqualAndNotEqualTo1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_EqualAndNotEqualTo1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_EqualAndNotEqualTo2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_EqualAndNotEqualTo2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Addition0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Addition1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Addition2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_Addition3( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_Addition3 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_AdditionAssignment0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_AdditionAssignment0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_AdditionAssignment1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_AdditionAssignment1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_AdditionAssignment2( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_AdditionAssignment2 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilString_String_BitwiseLeftShiftIntAndUint( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_UtilString, String_BitwiseLeftShiftIntAndUint );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilString
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilString );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilString, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilString
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilString );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilString, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
