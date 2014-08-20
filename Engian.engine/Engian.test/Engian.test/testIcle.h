
//#define RUN_UNIT_TESTS_SPEED
//#define RUN_UNIT_TESTS_MANUAL
#ifdef RUN_UNIT_TESTS_MANUAL
  #define RUN_UNIT_TESTS
#endif

#ifndef TEST_ICLE_H
#define TEST_ICLE_H


#ifdef RUN_UNIT_TESTS
  
    // DLL defines
    #ifndef RUN_UNIT_TESTS_MANUAL
      #ifdef TESTICLE_EXPORTS
        #define TESTICLE_API __declspec(dllexport) 
      #else
        #define TESTICLE_API __declspec(dllimport) 
      #endif
    #else
      #define TESTICLE_API
    #endif  
  
    // Helper defines for classes being tested
    #define TESTCHASSISFRIEND friend class Test::UnitTestChassis;
    #ifndef RUN_UNIT_TESTS_SPEED
      #define TRACKTESTCALL( test ) Test::UnitTestChassis::TrackTestCall( test )
    #else
      #define TRACKTESTCALL( test )
    #endif

    // Helper defines for test chassis
    #define STRINGIFY( x ) #x
    #define TOSTRING( x ) STRINGIFY( x )
    #define TEST_ASSERT( value, testName, failedReason ) if( !( value ) ) return TestFailureText( testName, __FILE__, TOSTRING( __LINE__ ), failedReason )
    #define TEST_ASSERT_EX( value, testName, failedReason, executeIfFailed ) if( !( value ) ) { executeIfFailed; return TestFailureText( testName, __FILE__, TOSTRING( __LINE__ ), failedReason ); }
    #define TEST_EXCEPTION TestFailureText( name, __FILE__, TOSTRING( __LINE__ ), "Unknown reason" )
    #define TEST_NOT_IMPLEMENTED TestFailureText( name, __FILE__, TOSTRING( __LINE__ ), "Test not implemented" )
    #define T_FUNC_ARR_DEC( testName ) static UnitTestDictionaryPair UnitTestArray_ ## testName[]
    #define T_FUNC_ARR_DEF( testName ) UnitTestDictionaryPair( &UnitTestChassis:: ## testName, #testName )
    #define T_FUNC_ARR_SIZE( arrayName ) sizeof( arrayName ) / sizeof( UnitTestChassis::UnitTestDictionaryPair )

    namespace Test
    {  

      struct UnitTestChassis
      {
        public:
          struct UnitTestDictionaryPair
          {
            char const * const (*Function) ( char const * const );
            char const * const Name;

            UnitTestDictionaryPair( char const * const (*function) ( char const * const ), char const * const name );
          };

          struct UnitTestSampleStruct
          {
            mutable unsigned* m_referenceCount;
            static unsigned s_numberOfDeletes;

            int m_int1,
              m_int2,
              m_int3;
            double m_doubles[ 5 ];

            UnitTestSampleStruct();
            UnitTestSampleStruct( int int1, int int2, int int3, double* doubles );
            UnitTestSampleStruct( UnitTestSampleStruct const& other );
            UnitTestSampleStruct& operator=( UnitTestSampleStruct const& other );
            ~UnitTestSampleStruct();

            bool const operator==( UnitTestSampleStruct const& other ) const;
            bool const operator!=( UnitTestSampleStruct const& other ) const;

            static UnitTestSampleStruct* CreateABunch( unsigned bunch );
          };

          class UnitTestSampleClass
          {
            private:
              char* m_string;
              int m_int;
              UnitTestSampleStruct m_struct;


            public:
              UnitTestSampleClass();
              UnitTestSampleClass( char const * const string, int i, UnitTestSampleStruct utss );
              UnitTestSampleClass( UnitTestSampleClass const& other );
              UnitTestSampleClass& operator=( UnitTestSampleClass const& other );
              ~UnitTestSampleClass();

              bool const operator==( UnitTestSampleClass const& other ) const;
              bool const operator!=( UnitTestSampleClass const& other ) const;

              static UnitTestSampleClass* CreateABunch( unsigned bunch );

              mutable unsigned* m_referenceCount;
              static unsigned s_numberOfDeletes;

          };

/* BEGINNING OF UNIT TEST FUNCTIONS */

          /***
          **** UNIT TESTS: TestUtilVector
          ***/
          static char const * const TestUtilList_Helper_List( ... );
          T_FUNC_ARR_DEC( TestUtilVector );
          static char const * const TestUtilVector_VectorIteratorImpl_Constructor0( char const * const name );
          static char const * const TestUtilVector_VectorIteratorImpl_AdvanceValue( char const * const name );
          static char const * const TestUtilVector_VectorIteratorImpl_GetValue( char const * const name );
          static char const * const TestUtilVector_VectorIteratorImpl_EqualTo( char const * const name );
          static char const * const TestUtilVector_VectorIteratorImpl_NotEqualTo( char const * const name );
          static char const * const TestUtilVector_Vector_Constructor0( char const * const name );
          static char const * const TestUtilVector_Vector_Constructor1( char const * const name );
          static char const * const TestUtilVector_Vector_Constructor2( char const * const name );
          static char const * const TestUtilVector_Vector_Constructor3( char const * const name );
          static char const * const TestUtilVector_Vector_CopyConstructor( char const * const name );
          static char const * const TestUtilVector_Vector_Begin( char const * const name );
          static char const * const TestUtilVector_Vector_End( char const * const name );
          static char const * const TestUtilVector_Vector_PushFront( char const * const name );
          static char const * const TestUtilVector_Vector_PushBack( char const * const name );
          static char const * const TestUtilVector_Vector_PopFront( char const * const name );
          static char const * const TestUtilVector_Vector_PopBack( char const * const name );
          static char const * const TestUtilVector_Vector_PopFirst( char const * const name );
          static char const * const TestUtilVector_Vector_PopAll( char const * const name );
          static char const * const TestUtilVector_Vector_Contains( char const * const name );
          static char const * const TestUtilVector_Vector_IsFull( char const * const name );
          static char const * const TestUtilVector_Vector_GetCapacity( char const * const name );
          static char const * const TestUtilVector_Vector_Clear( char const * const name );
          static char const * const TestUtilVector_Vector_BasicAssignment0( char const * const name );
          static char const * const TestUtilVector_Vector_BasicAssignment1( char const * const name );
          static char const * const TestUtilVector_Vector_ArraySubscript( char const * const name );
          static char const * const TestUtilVector_Vector_Addition( char const * const name );
          static char const * const TestUtilVector_Vector_AdditionAssignment( char const * const name );
          static char const * const TestUtilVector_Vector_Indirection( char const * const name );
          /***/


          /***
          **** UNIT TESTS: TestUtilList
          ***/
          template< typename HELPER >
          static char const * const TestUtilList_Helper_CheckEmptyList( void* check );
          template< typename HELPER >
          static char const * const TestUtilList_Helper_CheckListFrontAndBack( void* check, unsigned const size, bool endCheck );
          template< typename HELPER >
          static char const * const TestUtilList_Helper_CheckListAgainstArray( void* compareFrom, HELPER* compareAgainst, unsigned const arraySize, int const incr );
          template< typename HELPER >
          static char const * const TestUtilList_Helper_CheckListAgainstContainer( void* compareFrom, void* compareAgainst );
          T_FUNC_ARR_DEC( TestUtilList );
          static char const * const TestUtilList_ListIteratorImpl_Constructor0( char const * const name );
          static char const * const TestUtilList_ListIteratorImpl_AdvanceValue( char const * const name );
          static char const * const TestUtilList_ListIteratorImpl_GetValue( char const * const name );
          static char const * const TestUtilList_ListIteratorImpl_EqualTo( char const * const name );
          static char const * const TestUtilList_ListIteratorImpl_NotEqualTo( char const * const name );
          static char const * const TestUtilList_List_Constructor0( char const * const name );
          static char const * const TestUtilList_List_Constructor1( char const * const name );
          static char const * const TestUtilList_List_Constructor2( char const * const name );
          static char const * const TestUtilList_List_CopyConstructor( char const * const name );
          static char const * const TestUtilList_List_Begin( char const * const name );
          static char const * const TestUtilList_List_End( char const * const name );
          static char const * const TestUtilList_List_PushFront( char const * const name );
          static char const * const TestUtilList_List_PushBack( char const * const name );
          static char const * const TestUtilList_List_PopFront( char const * const name );
          static char const * const TestUtilList_List_PopBack( char const * const name );
          static char const * const TestUtilList_List_PopFirst( char const * const name );
          static char const * const TestUtilList_List_PopAll( char const * const name );
          static char const * const TestUtilList_List_Contains( char const * const name );
          static char const * const TestUtilList_List_BasicAssignment0( char const * const name );
          static char const * const TestUtilList_List_BasicAssignment1( char const * const name );
          static char const * const TestUtilList_List_Addition( char const * const name );
          static char const * const TestUtilList_List_AdditionAssignment( char const * const name );
          /***/


          /***
          **** UNIT TESTS: TestUtilUnsafeVector
          ***/
          T_FUNC_ARR_DEC( TestUtilUnsafeVector );
          static char const * const TestUtilUnsafeVector_UnsafeVector_Constructor0( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_Constructor1( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_Constructor2( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_Constructor3( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_CopyConstructor( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_PushFront( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_PushBackRange0( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_PushBackRange1( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_BasicAssignment0( char const * const name );
          static char const * const TestUtilUnsafeVector_UnsafeVector_BasicAssignment1( char const * const name );
          /***/


          /***
          **** UNIT TESTS: TestUtilString
          ***/
          static char const * const TestUtilString_Helper_CheckStringAgainstArray( void* check, char const * const compareAgainst );
          static char const * const TestUtilString_Helper_CheckStringAgainstArray( void* check, char const * const compareAgainst, unsigned const compareAgainstLen );
          static char const * const TestUtilString_Helper_CheckStringAgainstContainer( void* compareFrom, void* compareAgainst );
          T_FUNC_ARR_DEC( TestUtilString );
          static char const * const TestUtilString_String_Constructor0( char const * const name );
          static char const * const TestUtilString_String_Constructor1( char const * const name );
          static char const * const TestUtilString_String_Constructor2( char const * const name );
          static char const * const TestUtilString_String_Constructor3( char const * const name );
          static char const * const TestUtilString_String_Constructor4( char const * const name );
          static char const * const TestUtilString_String_CopyConstructor( char const * const name );
          static char const * const TestUtilString_String_PushBack( char const * const name );
          static char const * const TestUtilString_String_PushBackRange0( char const * const name );
          static char const * const TestUtilString_String_PushBackRange1( char const * const name );
          static char const * const TestUtilString_String_PushBackRange2( char const * const name );
          static char const * const TestUtilString_String_PopBack( char const * const name );
          static char const * const TestUtilString_String_GetStrLen( char const * const name );
          static char const * const TestUtilString_String_BeginsWith( char const * const name );
          static char const * const TestUtilString_String_EndsWith( char const * const name );
          static char const * const TestUtilString_String_IsEmpty( char const * const name );
          static char const * const TestUtilString_String_Clear( char const * const name );
          static char const * const TestUtilString_String_BasicAssignment0( char const * const name );
          static char const * const TestUtilString_String_BasicAssignment1( char const * const name );
          static char const * const TestUtilString_String_BasicAssignment2( char const * const name );
          static char const * const TestUtilString_String_BasicAssignment3( char const * const name );
          static char const * const TestUtilString_String_EqualAndNotEqualTo0( char const * const name );
          static char const * const TestUtilString_String_EqualAndNotEqualTo1( char const * const name );
          static char const * const TestUtilString_String_EqualAndNotEqualTo2( char const * const name );
          static char const * const TestUtilString_String_Addition0( char const * const name );
          static char const * const TestUtilString_String_Addition1( char const * const name );
          static char const * const TestUtilString_String_Addition2( char const * const name );
          static char const * const TestUtilString_String_Addition3( char const * const name );
          static char const * const TestUtilString_String_AdditionAssignment0( char const * const name );
          static char const * const TestUtilString_String_AdditionAssignment1( char const * const name );
          static char const * const TestUtilString_String_AdditionAssignment2( char const * const name );
          static char const * const TestUtilString_String_BitwiseLeftShiftIntAndUint( char const * const name );
          /***/


          /***
          **** UNIT TESTS: TestUtilSortedVector
          ***/
          T_FUNC_ARR_DEC( TestUtilSortedVector );
          static char const * const TestUtilSortedVector_SortedVector_Constructor0( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_Constructor1( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_Constructor2( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_Constructor3( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_CopyConstructor( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_PushFront( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_PushBack( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_PushBackRange0( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_PushBackRange1( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_Search( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_ShiftAndPush( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_FindInsertionIndex( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_QuickSort( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_BasicAssignment0( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_BasicAssignment1( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_Addition( char const * const name );
          static char const * const TestUtilSortedVector_SortedVector_AdditionAssignment( char const * const name );
          /***/


          /***
          **** UNIT TESTS: TestUtilSortedList
          ***/
          T_FUNC_ARR_DEC( TestUtilSortedList );
          static char const * const TestUtilSortedList_SortedList_Constructor0( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Constructor1( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Constructor2( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Constructor3( char const * const name );
          static char const * const TestUtilSortedList_SortedList_CopyConstructor0( char const * const name );
          static char const * const TestUtilSortedList_SortedList_CopyConstructor1( char const * const name );
          static char const * const TestUtilSortedList_SortedList_PushFront( char const * const name );
          static char const * const TestUtilSortedList_SortedList_PushBack( char const * const name );
          static char const * const TestUtilSortedList_SortedList_PopFront( char const * const name );
          static char const * const TestUtilSortedList_SortedList_PopBack( char const * const name );
          static char const * const TestUtilSortedList_SortedList_PopFirst( char const * const name );
          static char const * const TestUtilSortedList_SortedList_PopAll( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Contains( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Clear( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Push( char const * const name );
          static char const * const TestUtilSortedList_SortedList_NewSortedListNodeTier( char const * const name );
          static char const * const TestUtilSortedList_SortedList_FindInsertionNodeInTier( char const * const name );
          static char const * const TestUtilSortedList_SortedList_GetBottomTier( char const * const name );
          static char const * const TestUtilSortedList_SortedList_GetNumberOfTiers( char const * const name );
          static char const * const TestUtilSortedList_SortedList_ClearTiers( char const * const name );
          static char const * const TestUtilSortedList_SortedList_FindNewFront( char const * const name );
          static char const * const TestUtilSortedList_SortedList_FindNewBack( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Search( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Pop( char const * const name );
          static char const * const TestUtilSortedList_SortedList_BasicAssignment0( char const * const name );
          static char const * const TestUtilSortedList_SortedList_BasicAssignment1( char const * const name );
          static char const * const TestUtilSortedList_SortedList_Addition( char const * const name );
          static char const * const TestUtilSortedList_SortedList_AdditionAssignment( char const * const name );
          /***/


          /***
          **** UNIT TESTS: TestUtilHashTable
          ***/
          T_FUNC_ARR_DEC( TestUtilHashTable );
          static char const * const TestUtilHashTable_KeyedIterator_CopyConstructor( char const * const name );
          static char const * const TestUtilHashTable_KeyedIterator_Constructor0( char const * const name );
          static char const * const TestUtilHashTable_KeyedIterator_Constructor1( char const * const name );
          static char const * const TestUtilHashTable_KeyedIterator_Key( char const * const name );
          static char const * const TestUtilHashTable_KeyedIterator_PrefixIncrement( char const * const name );
          static char const * const TestUtilHashTable_KeyedIterator_BasicAssignment( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_Constructor0( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_Constructor1( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_CopyConstructor( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_Key( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_AdvanceValue( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_GetValue( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_GetKey( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_EqualTo( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_NotEqualTo( char const * const name );
          static char const * const TestUtilHashTable_HashTableIteratorImpl_BasicAssignment( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor0( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor1( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor2( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor3( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor4( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor5( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Constructor6( char const * const name );
          static char const * const TestUtilHashTable_HashTable_CopyConstructor( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Begin( char const * const name );
          static char const * const TestUtilHashTable_HashTable_End( char const * const name );
          static char const * const TestUtilHashTable_HashTable_KeyedBegin( char const * const name );
          static char const * const TestUtilHashTable_HashTable_KeyedEnd( char const * const name );
          static char const * const TestUtilHashTable_HashTable_PushFront( char const * const name );
          static char const * const TestUtilHashTable_HashTable_PushBack( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Push0( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Push1( char const * const name );
          static char const * const TestUtilHashTable_HashTable_PopFront( char const * const name );
          static char const * const TestUtilHashTable_HashTable_PopBack( char const * const name );
          static char const * const TestUtilHashTable_HashTable_PopFirst( char const * const name );
          static char const * const TestUtilHashTable_HashTable_PopAll( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Pop( char const * const name );
          static char const * const TestUtilHashTable_HashTable_GetKeys( char const * const name );
          static char const * const TestUtilHashTable_HashTable_GetCapacity( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Clear0( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Clear1( char const * const name );
          static char const * const TestUtilHashTable_HashTable_CheckAndGrow( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Grow( char const * const name );
          static char const * const TestUtilHashTable_HashTable_CreateKeyedIteratorFromImplementation( char const * const name );
          static char const * const TestUtilHashTable_HashTable_BasicAssignment0( char const * const name );
          static char const * const TestUtilHashTable_HashTable_BasicAssignment1( char const * const name );
          static char const * const TestUtilHashTable_HashTable_ArraySubscript( char const * const name );
          static char const * const TestUtilHashTable_HashTable_Addition( char const * const name );
          static char const * const TestUtilHashTable_HashTable_AdditionAssignment( char const * const name );
          /***/

/* END OF UNIT TEST FUNCTIONS */

          ////////
          // helper functions

          // dll functions
          static void GetTests_UnitTests( UnitTestDictionaryPair const * const unitTestArray, int const numTests, char*** allTests );
          static void RunTests_UnitTests( UnitTestDictionaryPair const * const unitTestArray, int const numUnitTests, char** const testsToRun,  int const numTestsToRun, char*** allResults );
          
          static char* MarshalString( char const * const string );
          static char** MarshalArrayOfStrings( char const * const * const strings, unsigned numStrings );

          // test result functions
          static char const * const TestFailureText( char const * const testName, char const * const fileName, char const * const lineNumber, char const * const failedReason );
        
          static void TrackTestCall( char const * const testName );
          static bool const CheckTestCall( char const * const testName, bool clear = false );
          static void ClearTestCalls();
          static void Reset();

      };

    }

#else

// Helper defines for classes being tested
#define TRACKTESTCALL( test )
#define TESTCHASSISFRIEND

#endif

#endif
