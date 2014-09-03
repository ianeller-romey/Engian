
#include "testIcle.h"
#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

void main()
{
  char const * output;

  Test::UnitTestChassis::TestUtilString_String_Constructor4("");
  Test::UnitTestChassis::TestUtilString_String_CopyConstructor("");
  Test::UnitTestChassis::TestUtilString_String_PopBack("");
  Test::UnitTestChassis::TestUtilString_String_Clear("");
  Test::UnitTestChassis::TestUtilString_String_BasicAssignment3("");
  Test::UnitTestChassis::TestUtilString_String_Addition0("");


  //output = Test::UnitTestChassis::TestUtilVector_Vector_Constructor0( "" );
  //output = Test::UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor0( "" );
  //output = Test::UnitTestChassis::TestUtilString_String_Constructor0( "" );
  //output = Test::UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor0( "" );
  //output = Test::UnitTestChassis::TestUtilList_List_PopFirst( "" );
  
  {
    unsigned const numTests = 28;
    char** allTests = new char*[ numTests ];
  
    unsigned const numTestsToRun = numTests;
    char** allTestsToRun = new char*[ numTestsToRun ];

    Test::UnitTestChassis::GetTests_UnitTests( Test::UnitTestChassis::UnitTestArray_TestUtilVector, numTests, &allTests );
    Test::UnitTestChassis::RunTests_UnitTests( Test::UnitTestChassis::UnitTestArray_TestUtilVector, numTests, allTests, numTestsToRun, &allTestsToRun );
    int i = 0;
  }

  /*
  char const * const output = Test::UnitTestChassis::TestUtilSortedVector_SortedVector_Constructor3( "" );
  
  {
    unsigned const numTests = 22;
    char** allTests = new char*[ numTests ];
  
    unsigned const numTestsToRun = numTests;
    char** allTestsToRun = new char*[ numTestsToRun ];

    Test::UnitTestChassis::GetTests_UnitTests( Test::UnitTestChassis::UnitTestArray_TestUtilList, numTests, &allTests );
    Test::UnitTestChassis::RunTests_UnitTests( Test::UnitTestChassis::UnitTestArray_TestUtilList, numTests, allTests, numTestsToRun, &allTestsToRun );
  }

  {
    unsigned const numTests = 31;
    char** allTests = new char*[ numTests ];
  
    unsigned const numTestsToRun = numTests;
    char** allTestsToRun = new char*[ numTestsToRun ];

    Test::UnitTestChassis::GetTests_UnitTests( Test::UnitTestChassis::UnitTestArray_TestUtilString, numTests, &allTests );
    Test::UnitTestChassis::RunTests_UnitTests( Test::UnitTestChassis::UnitTestArray_TestUtilString, numTests, allTests, numTestsToRun, &allTestsToRun );
  }
  */

}