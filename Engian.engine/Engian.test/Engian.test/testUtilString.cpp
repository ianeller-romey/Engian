
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
      TEST_ASSERT( TestHelper_UtilString::String_Constructor0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Constructor1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Constructor2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Constructor3() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Constructor4() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_CopyConstructor() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_PushBack() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_PushBackRange0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_PushBackRange1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_PushBackRange2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_PopBack() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_GetStrLen() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_BeginsWith() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_EndsWith() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_IsEmpty() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Clear() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_BasicAssignment0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_BasicAssignment1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_BasicAssignment2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_BasicAssignment3() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_EqualAndNotEqualTo0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_EqualAndNotEqualTo1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_EqualAndNotEqualTo2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Addition0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Addition1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Addition2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_Addition3() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_AdditionAssignment0() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_AdditionAssignment1() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_AdditionAssignment2() == 0, name, "" );
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
      TEST_ASSERT( TestHelper_UtilString::String_BitwiseLeftShiftIntAndUint() == 0, name, "" );
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
