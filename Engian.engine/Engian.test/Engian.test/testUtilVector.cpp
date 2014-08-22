
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "utilVector.h"
#include "utilList.h"

#include "testUtilVector_Helpers.h"


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
      Util::Vector< double > vector;
      vector.PushBack( 1.1 );
      Util::Vector< double >::Iterator itB = vector.Begin(), itE = vector.End();
      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< double >, "Vector< T >::VectorIteratorImpl::VectorIteratorImpl( T * const tArray )" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const number = 50;
      UnitTestSampleStruct* structs = UnitTestSampleStruct::CreateABunch( number );
      Util::Vector< UnitTestSampleStruct > vector;
      vector.PushBackRange( structs, number );
      Util::Vector< UnitTestSampleStruct >::Iterator itB = vector.Begin(), itE = vector.End();
      for( ; itB != itE; ++itB ) ;

      TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::VectorIteratorImpl::AdvanceValue()" ), 
                      name, "Appropriate function was not called", delete [] structs );

      delete [] structs;
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
      unsigned const number = 50;
      UnitTestSampleStruct* structs = UnitTestSampleStruct::CreateABunch( number );
      Util::Vector< UnitTestSampleStruct > vector;
      vector.PushBackRange( structs, number );
      Util::Vector< UnitTestSampleStruct >::Iterator itB = vector.Begin(), itE = vector.End();
      for( unsigned i = 0; itB != itE; ++itB, ++i ) 
        TEST_ASSERT_EX( itB.Get() == structs[ i ], name, "did not return the appropriate value", delete [] structs );

      TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "T const& Vector< T >::VectorIteratorImpl::GetValue() const" ), 
                      name, "Appropriate function was not called", delete [] structs );

      delete [] structs;
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
      {
        unsigned const number = 50;
        Util::Vector< bool > vector1, vector2;
        bool bools[ number ];
        vector1.PushBackRange( bools, number );
        vector2.PushBackRange( bools, number );
        Util::Vector< bool >::Iterator itB1 = vector1.Begin(), 
                                       itE1 = vector1.End(),
                                       itB2 = vector2.Begin(),
                                       itE2 = vector2.End();

        TEST_ASSERT( ( itB1 == itB2 ) == false, name, "returned true for two Iterators from separate Vector< T > instances" );
        TEST_ASSERT( ( itE1 == itE2 ) == false, name, "returned true for two Iterators from separate Vector< T > instances" );

        for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
          TEST_ASSERT( ( itB1 == itE1 ) == false, name, "returned true for non-equivalent Iterators from the same Vector< T > instance" );

        Util::Vector< bool >::Iterator itAlt( itB1 );
        TEST_ASSERT( itB1 == itAlt, name, "returned false for two equivalent Iterators from the same Vector< T > instance" );

        for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
          TEST_ASSERT( itB1 == itAlt, name, "returned false for two equivalent Iterators from the same Vector< T > instance" );

        TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< bool >, "bool const Vector< T >::VectorIteratorImpl::operator==( IteratorImpl const& iterator ) const" ), 
                     name, "Appropriate function was not called" );
      }

      {
        Util::Vector< int > vector;
        vector.PushBack( 100 );
        vector.PushBack( 100 );
        Util::Vector< int >::Iterator it1 = vector.Begin()++,
                                      it2 = vector.Begin();
        TEST_ASSERT( it1.Get() == it2.Get(), name, "test invalidated because Iterators being compared do not have the same value" );
        TEST_ASSERT( ( it1 == it2) == false, name, "returned true for unequivalent Iterators holding the same value" );
      }
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
      unsigned const number = 50;
      Util::Vector< bool > vector1, vector2;
      bool bools[ number ];
      vector1.PushBackRange( bools, number );
      vector2.PushBackRange( bools, number );
      Util::Vector< bool >::Iterator itB1 = vector1.Begin(), 
                                     itE1 = vector1.End(),
                                     itB2 = vector2.Begin(),
                                     itE2 = vector2.End();

      TEST_ASSERT( itB1 != itB2, name, "returned false for two Iterators from separate Vector< T > instances" );
      TEST_ASSERT( itE1 != itE2, name, "returned false for two Iterators from separate Vector< T > instances" );

      for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
        TEST_ASSERT( itB1 != itE1, name, "returned false for non-equivalent Iterators from the same Vector< T > instance" );

      Util::Vector< bool >::Iterator itAlt( itB1 );
      TEST_ASSERT( ( itB1 != itAlt ) == false, name, "returned true for two equivalent Iterators from the same Vector< T > instance" );

      for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
        TEST_ASSERT( ( itB1 != itAlt ) == false, name, "returned true for two equivalent Iterators from the same Vector< T > instance" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< bool >, "bool const Vector< T >::VectorIteratorImpl::operator!=( IteratorImpl const& iterator ) const" ), 
                   name, "Appropriate function was not called" );

      {
        Util::Vector< int > vector;
        vector.PushBack( 100 );
        vector.PushBack( 100 );
        Util::Vector< int >::Iterator it1 = vector.Begin()++,
                                      it2 = vector.Begin();
        TEST_ASSERT( it1.Get() == it2.Get(), name, "test invalidated because Iterators being compared do not have the same value" );
        TEST_ASSERT( it1 != it2, name, "returned false for unequivalent Iterators holding the same value" );
      }
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
      Util::Vector< int > vector;

      TEST_ASSERT( TestHelper_Vector< int >::CheckVectorInit( vector, Util::Vector< int >::dbgGet_c_defaultCapacity(), 0 ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< int >, "Vector< T >::Vector()" ), name, "Appropriate function was not called" );
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
      unsigned const capacity = 200;
      Util::Vector< int > vector( capacity );

      TEST_ASSERT( TestHelper_Vector< int >::CheckVectorInit( vector, capacity, 0 ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< int >, "Vector< T >::Vector( unsigned const capacity )" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const size = 150;
      UnitTestSampleClass* classes = UnitTestSampleClass::CreateABunch( size );
      Util::Vector< UnitTestSampleClass > vector( classes, size );
      
      TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleClass >::CheckVectorInit( vector, size, size ) == 0,
                      name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly", delete [] classes );
      TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleClass >::CheckVectorAgainstArray( vector, classes, size ) == 0,
                      name, "did not initialize with correct values", delete [] classes );

      TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleClass > , "Vector< T >::Vector( T const * const tArray, unsigned const size )" ), 
                      name, "Appropriate function was not called", delete [] classes );
      delete [] classes;
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
      unsigned const size = 80;
      double doubles[ size ];
      for( unsigned i = 0; i < size; ++i )
        doubles[ i ] = (double)rand();
      Util::List< double > list( doubles, size );
      Util::Vector< double > vector( list );
            
      TEST_ASSERT( TestHelper_Vector< double >::CheckVectorInit( vector, list.dbgGet_m_size(), list.dbgGet_m_size() ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );
      TEST_ASSERT( TestHelper_Vector< double >::CheckVectorAgainstContainer( vector, list ) == 0,
                   name, "did not initialize with correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< double >, "Vector< T >::Vector( Container< T > const& container )" ), 
                   name, "Appropriate function was not called" );
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
      Util::Vector< float > vector1;
      for( int i = 1000; i >= 0; --i )
        vector1.PushBack( (float)i );
      Util::Vector< float > vector2( vector1 );
      
      TEST_ASSERT( TestHelper_Vector< float >::CheckVectorInit( vector2, vector1.dbgGet_m_capacity(), vector1.dbgGet_m_size() ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );
      TEST_ASSERT( vector2.dbgGet_m_array() != vector1.dbgGet_m_array(), name, "did not initialize m_array correctly" );
      TEST_ASSERT( TestHelper_Vector< float >::CheckVectorAgainstContainer( vector2, vector1 ) == 0,
                   name, "did not initialize with correct values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< float >, "Vector< T >::Vector( Vector< T > const& vector )" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const number = 25;
      Util::Vector< char > vector( number );
      for( unsigned i = 0; i < number; ++i )
        vector.PushBack( (char)i );
      {
        Util::Vector< char >::Iterator itB = vector.Begin();
        TEST_ASSERT( itB.dbgGet_m_implementation() != 0, name, "did not create a VectorIteratorImpl instance" );
        TEST_ASSERT( &( itB.Get() ) == vector.dbgGet_m_array(), name, "returned an Iterator not pointing to the first element" );

        TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< char >, "Iterator Vector< T >::Begin() const" ), 
                     name, "Appropriate function was not called" );
      }
      TEST_ASSERT( vector.dbgGet_m_implementations() == 0, 
                   name, "Vector< T > did not have m_implementations reset to 0 after all Iterators left scope" );

      // check for exceptions when creating an iterator from an empty Vector< T >
      {
        Util::Vector< short > vector;
        Util::Vector< short >::Iterator itB = vector.Begin();
        itB.Get();
      }
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
      unsigned const number = 25;
      Util::Vector< char > vector( number );
      for( unsigned i = 0; i < number; ++i )
        vector.PushBack( (char)i );
      {
        Util::Vector< char >::Iterator itE = vector.End();
        TEST_ASSERT( itE.dbgGet_m_implementation() != 0, name, "did not create a VectorIteratorImpl instance" );
        TEST_ASSERT( &( itE.Get() ) == vector.dbgGet_m_array() + vector.dbgGet_m_size(), 
                     name, "returned an Iterator not pointing to the end element" );

        TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< char >, "Iterator Vector< T >::End() const" ), 
                     name, "Appropriate function was not called" );
      }
      TEST_ASSERT( vector.dbgGet_m_implementations() == 0, name, "Vector< T > did not have m_implementations reset to 0 after all Iterators left scope" );
      
      // check for exceptions when creating an iterator from an empty Vector< T >
      {
        Util::Vector< short > vector;
        Util::Vector< short >::Iterator itE = vector.End();
        itE.Get();
      }
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
      unsigned const size = 40;
			UnitTestSampleStruct* testStructs = UnitTestSampleStruct::CreateABunch( size );
			Util::Vector< UnitTestSampleStruct > vector;
			for( int i = size; i >= 0; --i )
				vector.PushFront( testStructs[ i ] );
			
      TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorInit( vector, size ) == 0,
                      name, "did not update m_capacity, m_size, m_array, or m_implementations correctly", delete [] testStructs );
      TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorAgainstArray( vector, testStructs, size ) == 0,
                      name, "did not insert correct values", delete [] testStructs );

			TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PushFront( T const& t )" ),
                      name, "Appropriate function was not called", delete [] testStructs );

			delete [] testStructs;
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
      unsigned const size = 40;
			UnitTestSampleStruct* testStructs = UnitTestSampleStruct::CreateABunch( size );
			Util::Vector< UnitTestSampleStruct > vector;
			for( unsigned i = 0; i < size; ++i )
				vector.PushBack( testStructs[ i ] );
						
      TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorInit( vector, size ) == 0,
                      name, "did not update m_capacity, m_size, m_array, or m_implementations correctly", delete [] testStructs );
      TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorAgainstArray( vector, testStructs, size ) == 0,
                      name, "did not insert correct values", delete [] testStructs );

			TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PushBack( T const& t )" ), 
                      name, "Appropriate function was not called", delete [] testStructs );

			delete [] testStructs;
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
      unsigned const size = 60;
			UnitTestSampleStruct* testStructs = UnitTestSampleStruct::CreateABunch( size );
			Util::Vector< UnitTestSampleStruct > vector;
			for( unsigned i = 0; i < size; ++i )
				vector.PushBack( testStructs[ i ] );
			
			for( unsigned i = 0; i < size; ++i )
			{
				vector.PopFront();
        
        TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorInit( vector, size ) == 0,
                        name, "did not update m_capacity, m_size, m_array, or m_implementations correctly", delete [] testStructs );
        TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorAgainstArray( vector, testStructs + i + 1, size - 1 - i ) == 0,
                        name, "stored values were not correct after", delete [] testStructs );
			}
			TEST_ASSERT_EX( vector.IsEmpty(), name, "Container< T >::IsEmpty() did not return true after", delete [] testStructs );

			TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PopFront()" ), 
                      name, "Appropriate function was not called", delete [] testStructs );

			// checking for exceptions
			vector.PopFront();

			delete [] testStructs;
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
      unsigned const size = 123;
			UnitTestSampleStruct* testStructs = UnitTestSampleStruct::CreateABunch( size );
			Util::Vector< UnitTestSampleStruct > vector;
			for( unsigned i = 0; i < size; ++i )
				vector.PushBack( testStructs[ i ] );
			
			for( unsigned i = 0; i < size; ++i )
			{
				vector.PopBack();

        TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorInit( vector, size - 1 - i ) == 0,
                        name, "did not update m_capacity, m_size, m_array, or m_implementations correctly", delete [] testStructs );
        TEST_ASSERT_EX( TestHelper_Vector< UnitTestSampleStruct >::CheckVectorAgainstArray( vector, testStructs, size - 1 - i ) == 0,
                        name, "stored values were not correct after", delete [] testStructs );
			}
			TEST_ASSERT_EX( vector.IsEmpty(), name, "Container< T >::IsEmpty() did not return true after", delete [] testStructs );

			TEST_ASSERT_EX( DEBUG_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PopBack()" ), 
                      name, "Appropriate function was not called", delete [] testStructs );

			// checking for exceptions
			vector.PopBack();

			delete [] testStructs;
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
      {
        unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
			  Util::Vector< unsigned > vector( numbers, 15 );
        unsigned* vArray;
        unsigned vSize;

        vector.PopFirst( 1 );
        vArray = vector.dbgGet_m_array();
        vSize = vector.dbgGet_m_size();
        TEST_ASSERT( vArray[ 0 ] == numbers[ 1 ], name, "did not shift front elements correctly" );
        TEST_ASSERT( vSize == 14, name, "did not decrement m_size correctly" );
        TEST_ASSERT( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 13 ], name, "did not shift back elements correctly" );

        // do this twice, to make sure nothing changes after all the 1's are gone
        for( unsigned i = 0; i < 2; ++i )
        {
          vector.PopFirst( 1 );
          vArray = vector.dbgGet_m_array();
          vSize = vector.dbgGet_m_size();
          TEST_ASSERT( vArray[ 0 ] == numbers[ 1 ], name, "did not shift front elements correctly" );
          TEST_ASSERT( vSize == 13, name, "did not decrement m_size correctly" );
          TEST_ASSERT( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 12 ], name, "did not shift back elements correctly" );
        }
      
        vector.PopFirst( 0 );
        vArray = vector.dbgGet_m_array();
        vSize = vector.dbgGet_m_size();
        TEST_ASSERT( vArray[ 0 ] == numbers[ 1 ], name, "did not shift front elements correctly" );
        TEST_ASSERT( vSize == 12, name, "did not decrement m_size correctly" );
        TEST_ASSERT( vArray[ vSize - 1 ] == numbers[ 12 ] && vArray[ vSize - 2 ] == numbers[ 11 ], name, "did not shift back elements correctly" );
      }

      {
        Util::Vector< float > vector;
        vector.PopFirst( 1.1f );
        TEST_ASSERT( vector.dbgGet_m_capacity() != 0, name, "deallocated m_array; m_array should only be deallocated by Vector< T >::Clear()" );
        TEST_ASSERT( vector.dbgGet_m_size() == 0, name, "altered the m_size of an empty Vector< T >" );
        TEST_ASSERT( vector.dbgGet_m_capacity() == Util::Vector< float >::dbgGet_c_defaultCapacity(), name, "altered the m_capacity of an empty Vector< T >" );
      }

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< float >, "void Vector< T >::PopFirst( T const& t )" ), 
                   name, "Appropriate function was not called" );
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
      {
        unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
			  Util::Vector< unsigned > vector( numbers, 15 );
        unsigned* vArray;
        unsigned vSize;
        
        // do this twice, to make sure nothing changes after all the 1's are gone
        for( unsigned i = 0; i < 2; ++i )
        {
          vector.PopAll( 1 );
          vArray = vector.dbgGet_m_array();
          vSize = vector.dbgGet_m_size();
          TEST_ASSERT( vArray[ 0 ] == numbers[ 1 ], name, "did not shift front elements correctly" );
          TEST_ASSERT( vSize == 13, name, "did not decrement m_size correctly" );
          TEST_ASSERT( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 12 ], name, "did not shift back elements correctly" );
        }

        vector.PopAll( 10 );
        vArray = vector.dbgGet_m_array();
        vSize = vector.dbgGet_m_size();
        TEST_ASSERT( vArray[ 0 ] == numbers[ 1 ], name, "did not shift front elements correctly" );
        TEST_ASSERT( vSize == 10, name, "did not decrement m_size correctly" );
        TEST_ASSERT( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 12 ], name, "did not shift back elements correctly" );
      
        vector.PopAll( 0 );
        vArray = vector.dbgGet_m_array();
        vSize = vector.dbgGet_m_size();
        TEST_ASSERT( vArray[ 0 ] == numbers[ 1 ], name, "did not shift front elements correctly" );
        TEST_ASSERT( vSize == 9, name, "did not decrement m_size correctly" );
        TEST_ASSERT( vArray[ vSize - 1 ] == numbers[ 12 ] && vArray[ vSize - 2 ] == numbers[ 8 ], name, "did not shift back elements correctly" );
      }

      {
        Util::Vector< float > vector;
        vector.PopAll( 1.1f );
        TEST_ASSERT( vector.dbgGet_m_array() != 0, name, "\"void Vector< T >::PopFirst( T const& t )\" deallocated m_array; m_array should only be deallocated by Vector< T >::Clear()" );
        TEST_ASSERT( vector.dbgGet_m_size() == 0, name, "altered the m_size of an empty Vector< T >" );
        TEST_ASSERT( vector.dbgGet_m_capacity() == Util::Vector< float >::dbgGet_c_defaultCapacity(), name, "altered the m_capacity of an empty Vector< T >" );
      }

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< unsigned >, "void Vector< T >::PopAll( T const& t )" ), 
                   name, "Appropriate function was not called" );
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
      Util::Vector< long > vector;
      vector.PushBack( 10000000 );
      vector.PushBack( 9999999999999999 );
      vector.PushBack( 12345678987654321 );
      
      TEST_ASSERT( vector.Contains( 10000000 ), name, "did not return true for a contained value" );
      TEST_ASSERT( vector.Contains( 9999999999999999 ), name, "did not return true for a contained value" );
      TEST_ASSERT( vector.Contains( 12345678987654321 ), name, "did not return true for a contained value" );
      TEST_ASSERT( vector.Contains( 1 ) == false, name, "did not return false for a value that was not contained" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< long >, "bool const Vector< T >::Contains( T const& t ) const" ), 
                   name, "Appropriate function was not called" );
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
      Util::Vector< Util::List< int > > vector;
      for( unsigned i = 0, j = vector.dbgGet_m_capacity(); i < j; ++i )
      {
        Util::List< int > list;
        vector.PushBack( list );
      }

      TEST_ASSERT( vector.IsFull(), name, "did not return true for full Vector< T >" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< Util::List< int > >, "bool const Vector< T >::IsFull() const" ), 
                   name, "Appropriate function was not called" );
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
      {
        Util::Vector< Util::List< int > > vector;
        TEST_ASSERT( vector.GetCapacity() == Util::Vector< Util::List< int > >::dbgGet_c_defaultCapacity(), 
                     name, "did not return the expected capacity value" );
        TEST_ASSERT( vector.dbgGet_m_capacity() == vector.GetCapacity(), name, "did not return the same value as m_capacity" );
      }

      {
        unsigned const number = 50;
        Util::Vector< Util::List< int > > vector( number );
        TEST_ASSERT( vector.GetCapacity() == number, name, "did not return the expected capacity value" );
        TEST_ASSERT( vector.dbgGet_m_capacity() == vector.GetCapacity(), name, "did not return the same value as m_capacity" );

        // just enough to force a resize
        for( unsigned i = 0; i < number + 1; ++i )
        {
          Util::List< int > list;
          vector.PushBack( list );
        }
        TEST_ASSERT( vector.dbgGet_m_capacity() == vector.GetCapacity(), name, "did not return the same value as m_capacity after resize" );
      }

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< Util::List< int > >, "unsigned const Vector< T >::GetCapacity() const" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const number = 100;
      Util::Vector< Util::List< UnitTestSampleStruct > > vector( number );
      for( unsigned i = 0; i < number; ++i )
      {
        Util::List< UnitTestSampleStruct > list;
        list.PushBack( UnitTestSampleStruct( i, i, i, 0 ) );
        vector.PushBack( list );
      }

      vector.Clear();
      
      TEST_ASSERT( vector.dbgGet_m_array() == 0, name, "did not set m_array to 0" );
      TEST_ASSERT( vector.dbgGet_m_size() == 0, name, "did not set m_size to 0" );
      TEST_ASSERT( vector.dbgGet_m_capacity() == 0, name, "did not set m_capacity to 0" );
      TEST_ASSERT( vector.dbgGet_m_implementations() == 0, name, "did not set m_implementations to 0" );
      TEST_ASSERT( UnitTestSampleStruct::s_numberOfDeletes == number, name, "did not correctly delete all elements" );
      
      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< Util::List< UnitTestSampleStruct > >, "void Vector< T >::Clear()" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const number1 = 40, number2 = 200;
      Util::Vector< int > vector1, vector2( number2 );
      for( unsigned i = 0; i < number1; ++i )
        vector1.PushBack( i );
      for( unsigned i = 0; i < number2; ++i )
        vector2.PushBack( i );

      vector1 = vector2;
      TEST_ASSERT( TestHelper_Vector< int >::CheckVectorInit( vector1, vector2.dbgGet_m_capacity(), vector2.dbgGet_m_size() ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );
      TEST_ASSERT( vector1.dbgGet_m_array() != vector2.dbgGet_m_array(), name, "assigned m_array, when it should have copied the values" );
      for( unsigned i = 0; i < number2; ++i )
        TEST_ASSERT( TestHelper_Vector< int >::CheckVectorAgainstContainer( vector1, vector2 ) == 0, name, "did not correctly copy values" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< int >, "Vector< T >& Vector< T >::operator=( Vector< T > const& vector )" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const number1 = 123, number2 = 500;
      Util::Vector< int > vector( number1 );
      Util::List< int > list;
      for( unsigned i = 0; i < number1; ++i )
        vector.PushBack( i );
      for( unsigned i = 0; i < number2; ++i )
        list.PushBack( i );
      vector = list;

      TEST_ASSERT( TestHelper_Vector< int >::CheckVectorInit( vector, number2 ) == 0, 
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );
      
      TEST_ASSERT( TestHelper_Vector< int >::CheckVectorAgainstContainer( vector, list ) == 0, name, "did not copy values correctly" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< int >, "Container< T >& Vector< T >::operator=( Container< T > const& container )" ), 
                   name, "Appropriate function was not called" );
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
      unsigned const number = 1001;
      double doubles[ number ];
      for( unsigned i = 0; i < number; ++i )
        doubles[ i ] = (double)rand();
      Util::Vector< double > vector( doubles, number );

      for( unsigned i = 0; i < number; ++i )
      {
        TEST_ASSERT( vector[ i ] == vector.dbgGet_m_array()[ i ], name, "did not return the correct value" );
        TEST_ASSERT( vector[ i ] == doubles[ i ], name, "did not return the correct value" );
      }

      unsigned const halfNumber = number / 2;
      vector[ halfNumber ] = 0.0;
      TEST_ASSERT( vector[ halfNumber ] == 0.0, name, "did not assign the correct value" );
      TEST_ASSERT( vector[ halfNumber ] == vector.dbgGet_m_array[ halfNumber ], name, "did not assign the correct value" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< double >, "T& Vector< T >::operator[]( int const index ) const" ), 
                   name, "Appropriate function was not called" );
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
      unsigned char const number1 = 100, number2 = 200;
      Util::Vector< unsigned char > vector1, vector2;
      for( unsigned char i = 0; i < number1; ++i )
        vector1.PushBack( i );
      for( unsigned char i = 0; i < number2; ++i )
        vector2.PushBack( number1 + i );
      Util::Vector< unsigned char > vector3( vector1 + vector2 );

      TEST_ASSERT( TestHelper_Vector< unsigned char >::CheckVectorInit( vector3, vector1.dbgGet_m_size() + vector2.dbgGet_m_size() ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );
      TEST_ASSERT( vector3.dbgGet_m_array() != vector1.dbgGet_m_array() && 
                   vector3.dbgGet_m_array() != vector2.dbgGet_m_array(), 
                   name, "did not correctly assign m_array" );

      TEST_ASSERT( TestHelper_Vector< unsigned char >::CheckVectorAgainstArray( vector3, vector1.dbgGet_m_array(), number1 ) == 0, 
                   name, "did not correctly assign values from first Vector< T >" );
      TEST_ASSERT( TestHelper_Vector< unsigned char >::CheckVectorAgainstArray( vector3, vector2.dbgGet_m_array(), number2 ) == 0, 
                   name, "did not correctly assign values from first Vector< T >" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< unsigned char >, "Vector< T > Vector< T >::operator+( Vector< T > const& vector ) const" ),
                   name, "Appropriate function was not called" );
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
      unsigned char const number1 = 100, number2 = 200;
      Util::Vector< unsigned char > vector1, vector2;
      for( unsigned char i = 0; i < number1; ++i )
        vector1.PushBack( i );
      for( unsigned char i = 0; i < number2; ++i )
        vector2.PushBack( number1 + i );
      vector1 += vector2;
      
      TEST_ASSERT( TestHelper_Vector< unsigned char >::CheckVectorInit( vector1, number1 + number2 ) == 0,
                   name, "did not initialize m_capacity, m_size, m_array, or m_implementations correctly" );
      TEST_ASSERT( vector1.dbgGet_m_array() != vector2.dbgGet_m_array(), name, "did not correctly assign m_array" );

      for( unsigned i = 0; i < number1; ++i )
        TEST_ASSERT( vector1.dbgGet_m_array[ i ] == i, name, "did not correctly assign values from first Vector< T >" );
      for( unsigned i = 0; i < number2; ++i )
        TEST_ASSERT( vector1.dbgGet_m_array[ i + number1 ] == vector2.dbgGet_m_array[ i ], name, "did not correctly assign values from second Vector< T >" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< unsigned char >, "Vector< T >& Vector< T >::operator+=( Vector< T > const& vector )" ), 
                   name, "Appropriate function was not called" );
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
      Util::Vector< float > vector;
      vector.PushBack( 1.1f );
      vector.PushBack( 2.2f );
      vector.PushBack( 3.3f );
      TEST_ASSERT( *vector == vector.dbgGet_m_array(), name, "did not return the correct value" );

      TEST_ASSERT( DEBUG_FUNC_CHECK( Util::Vector< float >, "T const* Vector< T >::operator*() const" ), 
                   name, "Appropriate function was not called" );
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
