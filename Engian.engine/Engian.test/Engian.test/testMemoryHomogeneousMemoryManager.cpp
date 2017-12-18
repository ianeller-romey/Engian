
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "testTestHelper_MemoryHomogeneousMemoryManager.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestMemoryHomogeneousMemoryManager[] = {
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Block_Constructor ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Block_IsBlockFull ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Block_IsObjectAvailable ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Block_ToggleObjectAvailability ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Block_GetObject ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Constructor ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Destructor ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Allocate0 ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Allocate1 ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_Free ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_ObjectsInUse ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_IsFull ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_Page_IsOnPage ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_PageNode_Constructor ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Constructor ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_INSTANCE ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Allocate0 ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Allocate1 ),
    T_FUNC_ARR_DEF( TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Free )
  };

  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Block_Constructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Block_Constructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Block_IsBlockFull( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Block_IsBlockFull );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Block_IsObjectAvailable( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Block_IsObjectAvailable );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Block_ToggleObjectAvailability( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Block_ToggleObjectAvailability );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Block_GetObject( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Block_GetObject );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Constructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_Constructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Destructor( char const * const name )
  {
      try
      {
          TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_Destructor );
      }
      catch ( ... )
      {
          return TEST_EXCEPTION;
      }
      return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Allocate0( char const * const name )
  {
      try
      {
          TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_Allocate0 );
      }
      catch ( ... )
      {
          return TEST_EXCEPTION;
      }
      return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Allocate1( char const * const name )
  {
      try
      {
          TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_Constructor );
      }
      catch ( ... )
      {
          return TEST_EXCEPTION;
      }
      return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_Free( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_Free );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_ObjectsInUse( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_ObjectsInUse );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_IsFull( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_IsFull );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_Page_IsOnPage( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, Page_IsOnPage );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_PageNode_Constructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, PageNode_Constructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Constructor( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, HomogeneousMemoryManager_Constructor );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_INSTANCE( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, HomogeneousMemoryManager_INSTANCE );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Allocate0( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, HomogeneousMemoryManager_Allocate0 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Allocate1( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, HomogeneousMemoryManager_Allocate1 );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestMemoryHomogeneousMemoryManager_HomogeneousMemoryManager_Free( char const * const name )
  {
    try
    {
      TEST_HELPER_FUNCTION_ASSERT( TestHelper_MemoryHomogeneousMemoryManager, HomogeneousMemoryManager_Free );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestMemoryHomogeneousMemoryManager
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestMemoryHomogeneousMemoryManager );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestMemoryHomogeneousMemoryManager, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestMemoryHomogeneousMemoryManager
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestMemoryHomogeneousMemoryManager );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestMemoryHomogeneousMemoryManager, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
