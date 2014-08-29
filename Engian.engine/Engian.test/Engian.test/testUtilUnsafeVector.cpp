
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "utilUnsafeVector.h"
#include "utilList.h"

#include "testUnitTestHelper.h"


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

      TEST_ASSERT( CheckUtilVectorInit< int >( uVector, GetUtilVectorDefaultCapacity< int >(), 0 ) == 0 );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "UnsafeVector< T >::UnsafeVector()" ) );
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

      TEST_ASSERT( CheckUtilVectorInit< int >( uVector, capacity, 0 ) == 0 );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "UnsafeVector< T >::UnsafeVector( unsigned const capacity )" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const size = 150;
      int numbers[ size ];
      for( unsigned i = 0; i < size; ++i )
        numbers[ i ] = rand();
      Util::UnsafeVector< int > uVector( numbers, size );
      
      TEST_ASSERT( CheckUtilVectorInit< int >( uVector, size, size ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstArray< int >( uVector, numbers, size ) == 0 );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< int > , "UnsafeVector< T >::UnsafeVector( T const * const tArray, unsigned const size )" ), 
                      name, "Appropriate function was not called" );
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
      unsigned const size = 80;
      double doubles[ size ];
      for( unsigned i = 0; i < size; ++i )
        doubles[ i ] = (double)rand();
      Util::List< double > list( doubles, size );
      Util::UnsafeVector< double > uVector( list );
            
      unsigned const listSize = GetUtilContainerSize< double >( list );
      TEST_ASSERT( CheckUtilVectorInit< double >( uVector, listSize, listSize ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstContainer< double >( uVector, list ) == 0 );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< double >, "UnsafeVector< T >::UnsafeVector( Container< T > const& container )" ), 
                   name, "Appropriate function was not called" );
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
      
      TEST_ASSERT( CheckUtilVectorInit< float >( uVector2, 
                                                                 GetUtilVectorCapacity< float >( uVector1 ), 
                                                                 GetUtilContainerSize< float >( uVector1 ) ) == 0 );
      TEST_ASSERT( GetUtilVectorArray< float >( uVector2 ) != 
                   GetUtilVectorArray< float >( uVector1 ), 
                   name, "did not initialize m_array correctly" );
      TEST_ASSERT( CheckUtilVectorAgainstContainer< float >( uVector2, uVector1 ) == 0 );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< float >, "UnsafeVector< T >::UnsafeVector( UnsafeVector< T > const& uVector )" ), 
                   name, "Appropriate function was not called" );
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
      Util::UnsafeVector< unsigned short > uVector;
      for( unsigned i = 0; i < number; ++i )
      {
        numbers[ i ] = (unsigned short)( rand() );
        uVector.PushFront( numbers[ i ] );
      }
      
      TEST_ASSERT( CheckUtilVectorInit< unsigned short >( uVector, number ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstArray< unsigned short >( uVector, numbers, number ) == 0 );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< unsigned short >, "void UnsafeVector< T >::PushFront( T const& t )" ) );
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
      
      TEST_ASSERT( CheckUtilVectorInit< double >( uVector, number ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstArray< double >( uVector, numbers, number ) == 0 );
      
      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< double >, "void UnsafeVector< T >::PushBackRange( T const * const tArray, unsigned const size )" ) );
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
      
      TEST_ASSERT( CheckUtilVectorInit< char >( uVector2, GetUtilContainerSize< char >( uVector1 ) ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstContainer< char >( uVector2, uVector1 ) == 0 );
      
      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< char >, "void UnsafeVector< T >::PushBackRange( UnsafeVector< T > const& vector )" ) );
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
      TEST_ASSERT( CheckUtilVectorInit< int >( uVector1, 
                                                               GetUtilVectorCapacity< int >( uVector2 ), 
                                                               GetUtilContainerSize< int >( uVector2 ) ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstContainer< int >( uVector1, uVector2 ) == 0 );
      
      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "UnsafeVector< T >& UnsafeVector< T >::operator=( UnsafeVector< T > const& uVector )" ) );
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

      TEST_ASSERT( CheckUtilVectorInit( uVector1, GetUtilContainerSize< int >( list1 ) ) == 0 );
      TEST_ASSERT( CheckUtilVectorAgainstContainer< int >( uVector1, list1 ) == 0 );
      
      TEST_ASSERT( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "Container< T >& UnsafeVector< T >::operator=( Container< T > const& container )" ) );
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
