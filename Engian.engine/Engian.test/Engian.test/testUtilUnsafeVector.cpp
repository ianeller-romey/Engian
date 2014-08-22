
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "utilUnsafeVector.h"
#include "utilList.h"

#include "testUtilVector_Helpers.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilUnsafeVector[] = {
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_Constructor3 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_PushFront ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_PushBackRange0 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_PushBackRange1 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilUnsafeVector_UnsafeVector_BasicAssignment1 )
  };


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor0( char const * const name )
  {
    try
    {
      Util::UnsafeVector< int > uVector;

      TEST_ASSERT( TestHelper_Vector< int >::CheckVectorInit( uVector, Util::UnsafeVector< int >::dbgGet_c_defaultCapacity(), 0 ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::UnsafeVector< int >, "UnsafeVector< T >::UnsafeVector()" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor1( char const * const name )
  {
    try
    {
      unsigned const capacity = 200;
      Util::UnsafeVector< int > uVector( capacity );
      TEST_ASSERT( uVector.m_capacity == capacity, name, "did not initialize m_capacity correctly" );
      TEST_ASSERT( uVector.m_size == 0, name, "did not initialize m_size to 0" );
      TEST_ASSERT( uVector.m_array != 0, name, "did not initialize m_array" );
      TEST_ASSERT( uVector.m_implementations == 0, name, "incorrectly initialized m_implementations" );
      TEST_ASSERT( DEBUG_FUNC_CHECK( "UnsafeVector< T >::UnsafeVector( unsigned const capacity )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor2( char const * const name )
  {
    try
    {
      unsigned const number = 150;
      int numbers[ number ];
      Util::UnsafeVector< int > uVector( numbers, number );
      TEST_ASSERT( uVector.m_capacity != 0, name, "did not initialize m_capacity correctly" );
      TEST_ASSERT( uVector.m_size == number, name, "did not initialize m_size correctly" );
      TEST_ASSERT( uVector.m_array != 0, name, "did not initialize m_array" );
      TEST_ASSERT( uVector.m_implementations == 0, name, "incorrectly initialized m_implementations" );

      for( unsigned i = 0; i < number; ++i )
        TEST_ASSERT( uVector.m_array[ i ] == numbers[ i ], name, "did not initialize m_array with the correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "UnsafeVector< T >::UnsafeVector( T const * const tArray, unsigned const size )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_Constructor3( char const * const name )
  {
    try
    {
      unsigned const number = 80;
      double numbers[ number ];
      Util::List< double > list( numbers, number );
      Util::UnsafeVector< double > uVector( list );
      TEST_ASSERT( uVector.m_capacity == number, name, "did not initialize m_capacity correctly" );
      TEST_ASSERT( uVector.m_size == number, name, "did not initialize m_size to 0" );
      TEST_ASSERT( uVector.m_array != 0, name, "did not initialize m_array" );
      TEST_ASSERT( uVector.m_implementations == 0, name, "incorrectly initialized m_implementations" );

      for( unsigned i = 0; i < number; ++i )
        TEST_ASSERT( uVector.m_array[ i ] == numbers[ i ], name, "did not initialize m_array with the correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "UnsafeVector< T >::UnsafeVector( Container< T > const& container )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_CopyConstructor( char const * const name )
  {
    try
    {
      Util::UnsafeVector< float > uVector1;
      for( int i = 1000; i >= 0; --i )
        uVector1.PushBack( (float)i );
      Util::UnsafeVector< float > uVector2( uVector1 );
      TEST_ASSERT( uVector2.m_capacity == uVector1.m_capacity, name, "did not initialize m_capacity correctly" );
      TEST_ASSERT( uVector2.m_size == uVector1.m_size, name, "did not initialize m_size correctly" );
      TEST_ASSERT( uVector2.m_array != 0 && uVector2.m_array != uVector1.m_array, name, "did not initialize m_array correctly" );
      TEST_ASSERT( uVector2.m_implementations == 0, name, "incorrectly initialized m_implementations" );

      for( unsigned i = 0; i < uVector1.m_size; ++i )
        TEST_ASSERT( uVector2.m_array[ i ] == uVector1.m_array[ i ], name, "did not initialize m_array with the correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "UnsafeVector< T >::UnsafeVector( UnsafeVector< T > const& uVector )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_PushFront( char const * const name )
  {
    try
    {
      unsigned const number = 40;
      unsigned short numbers[ number ];
      Util::UnsafeVector< short > uVector1;
      for( unsigned i = 0; i < number; ++i )
      {
        numbers[ i ] = (unsigned short)( rand() );
        uVector1.PushFront( numbers[ i ] );
      }
      
      TEST_ASSERT( uVector1.m_size == number, name, "did not increase the uVector's m_size variable to the correct value" );

      for( unsigned i = 0; i < number; ++i )
        TEST_ASSERT( uVector1.m_array[ number - 1 - i ] == numbers[ i ], name, "did not insert correct value" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "void UnsafeVector< T >::PushFront( T const& t )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_PushBackRange0( char const * const name )
  {
    try
    {
      unsigned const number = 388;
      double numbers[ number ];
      for( unsigned i = 0; i < number; ++i )
        numbers[ i ] = (double)rand();
      Util::UnsafeVector< double > uVector( number );
      uVector.PushBackRange( numbers, number );

      TEST_ASSERT( uVector.m_capacity != 0, name, "did not correctly assign m_capacity" );
      TEST_ASSERT( uVector.m_size == number, name, "did not correctly increment m_size" );
      TEST_ASSERT( uVector.m_array != 0, name, "did not correctly allocate m_array" );
      TEST_ASSERT( uVector.m_implementations == 0, name, "created unnecessary Iterators" );

      for( unsigned i = 0; i < number; ++i )
        TEST_ASSERT( uVector.m_array[ i ] == numbers[ i ], name, "did not insert correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "void UnsafeVector< T >::PushBackRange( T const * const tArray, unsigned const size )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_PushBackRange1( char const * const name )
  {
    try
    {
      unsigned const number = 388;
      char numbers[ number ];
      for( unsigned i = 0; i < number; ++i )
        numbers[ i ] = 0 - (char)rand();
      Util::UnsafeVector< char > uVector1( numbers, number ),
                                 uVector2;
      uVector2.PushBackRange( uVector1 );

      TEST_ASSERT( uVector2.m_capacity != 0, name, "did not correctly assign m_capacity" );
      TEST_ASSERT( uVector2.m_size == number, name, "did not correctly increment m_size" );
      TEST_ASSERT( uVector2.m_array != 0, name, "did not correctly allocate m_array" );
      TEST_ASSERT( uVector2.m_implementations == 0, name, "created unnecessary Iterators" );

      for( unsigned i = 0; i < number; ++i )
        TEST_ASSERT( uVector2.m_array[ i ] == numbers[ i ], name, "did not insert correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "void UnsafeVector< T >::PushBackRange( UnsafeVector< T > const& vector )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_BasicAssignment0( char const * const name )
  {
    try
    {
      unsigned const number1 = 40, number2 = 200;
      Util::UnsafeVector< int > uVector1, uVector2( number2 );
      for( unsigned i = 0; i < number1; ++i )
        uVector1.PushBack( i );
      for( unsigned i = 0; i < number2; ++i )
        uVector2.PushBack( i );

      uVector1 = uVector2;
      TEST_ASSERT( uVector1.m_capacity == uVector2.m_capacity, name, "did not appropriately assign m_capacity" );
      TEST_ASSERT( uVector1.m_size == uVector2.m_size, name, "did not appropriately assign m_size" );
      TEST_ASSERT( uVector1.m_array != uVector2.m_array, name, "assigned m_array, when it should have copied the values" );
      TEST_ASSERT( uVector1.m_implementations == 0, name, "did not clear list of implementations" );

      for( unsigned i = 0; i < number2; ++i )
        TEST_ASSERT( uVector1.m_array[ i ] == uVector2.m_array[ i ], name, "did not correctly copy values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "UnsafeVector< T >& UnsafeVector< T >::operator=( UnsafeVector< T > const& uVector )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilUnsafeVector_UnsafeVector_BasicAssignment1( char const * const name )
  {
    try
    {      
      unsigned const number1 = 123, number2 = 500;
      Util::UnsafeVector< int > uVector1( number1 );
      Util::List< int > list1;
      for( unsigned i = 0; i < number1; ++i )
        uVector1.PushBack( i );
      for( unsigned i = 0; i < number2; ++i )
        list1.PushBack( i );

      uVector1 = list1;
      TEST_ASSERT( uVector1.m_size == list1.m_size, name, "did not appropriately assign m_size" );
      TEST_ASSERT( uVector1.m_implementations == 0, name, "did not clear list of implementations" );
      
      Util::UnsafeVector< int >::Iterator itVB = uVector1.Begin(),
                                    itVE = uVector1.End();
      Util::List< int >::Iterator itLB = list1.Begin(),
                                  itLE = list1.End();
      for( ; itVB != itVE && itLB != itLE; ++itVB, ++itLB )
        TEST_ASSERT( itVB.Get() == itLB.Get(), name, "did not correctly copy values" );

      TEST_ASSERT( itVB == itVE && itLB == itLE, name, "UnsafeVector< T > and List< T > iterators appear to have been pointing to instances of different sizes, when they should have the same size after assignment" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( "Container< T >& UnsafeVector< T >::operator=( Container< T > const& container )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilUnsafeVector
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilUnsafeVector
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilUnsafeVector, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
