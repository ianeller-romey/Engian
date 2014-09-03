
#include "testTestHelper_UtilVector.h"
#include "testTestHelper_UtilContainer.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilVector.h"
#include "utilList.h"


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

  unsigned const TestHelper_UtilVector::VectorIteratorImpl_Constructor0()
  {
    Util::Vector< double > vector;
    vector.PushBack( 1.1 );
    Util::Vector< double >::Iterator itB = vector.Begin(), itE = vector.End();
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< double >::VectorIteratorImpl, 
                                        "Vector< T >::VectorIteratorImpl::VectorIteratorImpl( T * const tArray )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::VectorIteratorImpl_AdvanceValue()
  {
    unsigned const number = 50;
    UnitTestSampleStruct structs[ number ];
    UnitTestSampleStruct::UpdateAnArray( structs, number );
    Util::Vector< UnitTestSampleStruct > vector;
    vector.PushBackRange( structs, number );
    Util::Vector< UnitTestSampleStruct >::Iterator itB = vector.Begin(), itE = vector.End();
    for( ; itB != itE; ++itB ) ;
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >::VectorIteratorImpl, 
                                        "void Vector< T >::VectorIteratorImpl::AdvanceValue()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::VectorIteratorImpl_GetValue()
  {
    unsigned const number = 50;
    UnitTestSampleStruct structs[ number ];
    UnitTestSampleStruct::UpdateAnArray( structs, number );
    Util::Vector< UnitTestSampleStruct > vector;
    vector.PushBackRange( structs, number );
    Util::Vector< UnitTestSampleStruct >::Iterator itB = vector.Begin(), itE = vector.End();
    for( unsigned i = 0; itB != itE; ++itB, ++i ) 
      RETURNLINEIFFAILED( itB.Get() == structs[ i ] );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >::VectorIteratorImpl, 
                                        "T const& Vector< T >::VectorIteratorImpl::GetValue() const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::VectorIteratorImpl_EqualTo()
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

      RETURNLINEIFFAILED( ( itB1 == itB2 ) == false );
      RETURNLINEIFFAILED( ( itE1 == itE2 ) == false );

      for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
        RETURNLINEIFFAILED( ( itB1 == itE1 ) == false );

      Util::Vector< bool >::Iterator itAlt( itB1 );
      RETURNLINEIFFAILED( itB1 == itAlt );

      for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
        RETURNLINEIFFAILED( itB1 == itAlt );

      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< bool >::VectorIteratorImpl, 
                                          "bool const Vector< T >::VectorIteratorImpl::operator==( IteratorImpl const& iterator ) const" ) );
    }

    {
      Util::Vector< int > vector;
      vector.PushBack( 100 );
      vector.PushBack( 100 );
      Util::Vector< int >::Iterator it1 = vector.Begin()++,
                                    it2 = vector.Begin();
      RETURNLINEIFFAILED( it1.Get() == it2.Get() );
      RETURNLINEIFFAILED( ( it1 == it2 ) == false );
    }
    return 0;
  }


  unsigned const TestHelper_UtilVector::VectorIteratorImpl_NotEqualTo()
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

    RETURNLINEIFFAILED( itB1 != itB2 );
    RETURNLINEIFFAILED( itE1 != itE2 );

    for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
      RETURNLINEIFFAILED( itB1 != itE1 );

    Util::Vector< bool >::Iterator itAlt( itB1 );
    RETURNLINEIFFAILED( ( itB1 != itAlt ) == false );

    for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
      RETURNLINEIFFAILED( ( itB1 != itAlt ) == false );

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< bool >::VectorIteratorImpl, 
                                        "bool const Vector< T >::VectorIteratorImpl::operator!=( IteratorImpl const& iterator ) const" ) );

    {
      Util::Vector< int > vector;
      vector.PushBack( 100 );
      vector.PushBack( 100 );
      Util::Vector< int >::Iterator it1 = vector.Begin()++,
                                    it2 = vector.Begin();
      RETURNLINEIFFAILED( it1.Get() == it2.Get() );
      RETURNLINEIFFAILED( it1 != it2 );
    }
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Constructor0()
  {
    Util::Vector< int > vector;
    RETURNLINEIFFAILED( CheckUtilVectorInit< int >( vector, Util::Vector< int >::c_defaultCapacity, 0 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< int >, "Vector< T >::Vector()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Constructor1()
  {
    unsigned const capacity = 200;
    Util::Vector< int > vector( capacity );
    RETURNLINEIFFAILED( CheckUtilVectorInit< int >( vector, capacity, 0 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< int >, "Vector< T >::Vector( unsigned const capacity )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Constructor2()
  {
    unsigned const size = 150;
    UnitTestSampleClass classes[ size ];
    UnitTestSampleClass::UpdateAnArray( classes, size );
    Util::Vector< UnitTestSampleClass > vector( classes, size );
      
    RETURNLINEIFFAILED( CheckUtilVectorInit< UnitTestSampleClass >( vector, size, size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< UnitTestSampleClass >( vector, classes, size ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleClass >, 
                        "Vector< T >::Vector( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Constructor3()
  {
    unsigned const size = 80;
    double doubles[ size ];
    for( unsigned i = 0; i < size; ++i )
      doubles[ i ] = (double)rand();
    Util::List< double > list( doubles, size );
    Util::Vector< double > vector( list );
            
    unsigned const listSize = TestHelper_UtilContainer::GetUtilContainerSize< double >( list );
    RETURNLINEIFFAILED( CheckUtilVectorInit< double >( vector, listSize, listSize ) == 0 );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstContainer< double >( vector, list ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< double >, "Vector< T >::Vector( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_CopyConstructor()
  {
    Util::Vector< float > vector1;
    for( int i = 1000; i >= 0; --i )
      vector1.PushBack( (float)i );
    Util::Vector< float > vector2( vector1 );
      
    RETURNLINEIFFAILED( CheckUtilVectorInit< float >( vector2, vector1.m_capacity, vector1.m_size ) == 0 );
    RETURNLINEIFFAILED( vector2.m_array != vector1.m_array );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstContainer< float >( vector2, vector1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< float >, "Vector< T >::Vector( Vector< T > const& vector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Begin()
  {
    unsigned const number = 25;
    Util::Vector< char > vector( number );
    for( unsigned i = 0; i < number; ++i )
      vector.PushBack( (char)i );

    {
      Util::Vector< char >::Iterator itB = vector.Begin();
      RETURNLINEIFFAILED( &( itB.Get() ) == vector.m_array );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< char >, "Iterator Vector< T >::Begin() const" ) );
    }
    RETURNLINEIFFAILED( vector.m_implementations == 0 );

    // check for exceptions when creating an iterator from an empty Vector< T >
    {
      Util::Vector< short > vector;
      Util::Vector< short >::Iterator itB = vector.Begin();
      itB.Get();
    }
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_End()
  {
    unsigned const number = 25;
    Util::Vector< char > vector( number );
    for( unsigned i = 0; i < number; ++i )
      vector.PushBack( (char)i );
    {
      Util::Vector< char >::Iterator itE = vector.End();
      //RETURNLINEIFFAILED( CheckIteratorImplementationIsNotEmpty< char >( itE ), 
      //             name, "did not create a VectorIteratorImpl instance" );
      RETURNLINEIFFAILED( &( itE.Get() ) == vector.m_array + vector.m_size );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< char >, "Iterator Vector< T >::End() const" ) );
    }
    RETURNLINEIFFAILED( vector.m_implementations == 0 );
      
    // check for exceptions when creating an iterator from an empty Vector< T >
    {
      Util::Vector< short > vector;
      Util::Vector< short >::Iterator itE = vector.End();
      itE.Get();
    }
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_PushFront()
  {
    unsigned const size = 40;
		UnitTestSampleStruct testStructs[ size ];
    UnitTestSampleStruct::UpdateAnArray( testStructs, size );
		Util::Vector< UnitTestSampleStruct > vector;
		for( int i = size - 1; i >= 0; --i )
			vector.PushFront( testStructs[ i ] );
			
    RETURNLINEIFFAILED( CheckUtilVectorInit< UnitTestSampleStruct >( vector, size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< UnitTestSampleStruct >( vector, testStructs, size ) == 0 );
		RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PushFront( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_PushBack()
  {
    unsigned const size = 40;
		UnitTestSampleStruct testStructs[ size ];
    UnitTestSampleStruct::UpdateAnArray( testStructs, size );
		Util::Vector< UnitTestSampleStruct > vector;
		for( unsigned i = 0; i < size; ++i )
			vector.PushBack( testStructs[ i ] );
						
    RETURNLINEIFFAILED( CheckUtilVectorInit< UnitTestSampleStruct >( vector, size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< UnitTestSampleStruct >( vector, testStructs, size ) == 0 );
		RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PushBack( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_PopFront()
  {
    unsigned const size = 60;
		UnitTestSampleStruct testStructs[ size ];
    UnitTestSampleStruct::UpdateAnArray( testStructs, size );
		Util::Vector< UnitTestSampleStruct > vector;
		for( unsigned i = 0; i < size; ++i )
			vector.PushBack( testStructs[ i ] );
			
		for( unsigned i = 0; i < size; ++i )
		{
			vector.PopFront();
        
      RETURNLINEIFFAILED( CheckUtilVectorInit< UnitTestSampleStruct >( vector, size - 1 - i ) == 0 );
      RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< UnitTestSampleStruct >( vector, testStructs + i + 1, size - 1 - i ) == 0 );
		}
		RETURNLINEIFFAILED( vector.IsEmpty() );

		// checking for exceptions
		vector.PopFront();

		RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PopFront()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_PopBack()
  {
    unsigned const size = 123;
		UnitTestSampleStruct testStructs[ size ];
    UnitTestSampleStruct::UpdateAnArray( testStructs, size );
		Util::Vector< UnitTestSampleStruct > vector;
		for( unsigned i = 0; i < size; ++i )
			vector.PushBack( testStructs[ i ] );
			
		for( unsigned i = 0; i < size; ++i )
		{
			vector.PopBack();

      RETURNLINEIFFAILED( CheckUtilVectorInit< UnitTestSampleStruct >( vector, size - 1 - i ) == 0 );
      RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< UnitTestSampleStruct >( vector, testStructs, size - 1 - i ) == 0 );
		}
		RETURNLINEIFFAILED( vector.IsEmpty() );

		// checking for exceptions
		vector.PopBack();

		RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< UnitTestSampleStruct >, "void Vector< T >::PopBack()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_PopFirst()
  {
    {
      unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
			Util::Vector< unsigned > vector( numbers, 15 );
      unsigned const* vArray;
      unsigned vSize;

      vector.PopFirst( 1 );
      vArray = vector.m_array;
      vSize = vector.m_size;
      RETURNLINEIFFAILED( vArray[ 0 ] == numbers[ 1 ] );
      RETURNLINEIFFAILED( vSize == 14 );
      RETURNLINEIFFAILED( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 13 ] );

      // do this twice, to make sure nothing changes after all the 1's are gone
      for( unsigned i = 0; i < 2; ++i )
      {
        vector.PopFirst( 1 );
        vArray = vector.m_array;
        vSize = vector.m_size;
        RETURNLINEIFFAILED( vArray[ 0 ] == numbers[ 1 ] );
        RETURNLINEIFFAILED( vSize == 13 );
        RETURNLINEIFFAILED( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 12 ] );
      }
      
      vector.PopFirst( 0 );
      vArray = vector.m_array;
      vSize = vector.m_size;
      RETURNLINEIFFAILED( vArray[ 0 ] == numbers[ 1 ] );
      RETURNLINEIFFAILED( vSize == 12 );
      RETURNLINEIFFAILED( vArray[ vSize - 1 ] == numbers[ 12 ] && vArray[ vSize - 2 ] == numbers[ 11 ] );
    }

    {
      Util::Vector< float > vector;
      vector.PopFirst( 1.1f );
      RETURNLINEIFFAILED( CheckUtilVectorInit< float >( vector, Util::Vector< float >::c_defaultCapacity, 0 ) == 0 );
    }

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< float >, "void Vector< T >::PopFirst( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_PopAll()
  {
    {
      unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
			Util::Vector< unsigned > vector( numbers, 15 );
      unsigned const* vArray;
      unsigned vSize;
        
      // do this twice, to make sure nothing changes after all the 1's are gone
      for( unsigned i = 0; i < 2; ++i )
      {
        vector.PopAll( 1 );
        vArray = vector.m_array;
        vSize = vector.m_size;
        RETURNLINEIFFAILED( vArray[ 0 ] == numbers[ 1 ] );
        RETURNLINEIFFAILED( vSize == 13 );
        RETURNLINEIFFAILED( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 12 ] );
      }

      vector.PopAll( 10 );
      vArray = vector.m_array;
      vSize = vector.m_size;
      RETURNLINEIFFAILED( vArray[ 0 ] == numbers[ 1 ] );
      RETURNLINEIFFAILED( vSize == 10 );
      RETURNLINEIFFAILED( vArray[ vSize - 1 ] == numbers[ 14 ] && vArray[ vSize - 2 ] == numbers[ 12 ] );
      
      vector.PopAll( 0 );
      vArray = vector.m_array;
      vSize = vector.m_size;
      RETURNLINEIFFAILED( vArray[ 0 ] == numbers[ 1 ] );
      RETURNLINEIFFAILED( vSize == 9 );
      RETURNLINEIFFAILED( vArray[ vSize - 1 ] == numbers[ 12 ] && vArray[ vSize - 2 ] == numbers[ 8 ] );
    }

    {
      Util::Vector< float > vector;
      vector.PopAll( 1.1f );
      RETURNLINEIFFAILED( CheckUtilVectorInit< float >( vector, Util::Vector< float >::c_defaultCapacity, 0 ) == 0 );
    }

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< unsigned >, "void Vector< T >::PopAll( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Contains()
  {
    Util::Vector< long > vector;
    vector.PushBack( 10000000 );
    vector.PushBack( 9999999999999999 );
    vector.PushBack( 12345678987654321 );
      
    RETURNLINEIFFAILED( vector.Contains( 10000000 ) );
    RETURNLINEIFFAILED( vector.Contains( 9999999999999999 ) );
    RETURNLINEIFFAILED( vector.Contains( 12345678987654321 ) );
    RETURNLINEIFFAILED( vector.Contains( 1 ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< long >, "bool const Vector< T >::Contains( T const& t ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_IsFull()
  {
    Util::Vector< Util::List< int > > vector;
    for( unsigned i = 0, j = vector.m_capacity; i < j; ++i )
    {
      Util::List< int > list;
      vector.PushBack( list );
    }

    RETURNLINEIFFAILED( vector.IsFull() );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< Util::List< int > >, "bool const Vector< T >::IsFull() const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_GetCapacity()
  {
    {
      Util::Vector< Util::List< int > > vector;
      RETURNLINEIFFAILED( vector.GetCapacity() == Util::Vector< Util::List< int > >::c_defaultCapacity );
      RETURNLINEIFFAILED( vector.m_capacity == vector.GetCapacity() );
    }

    {
      unsigned const number = 50;
      Util::Vector< Util::List< int > > vector( number );
      RETURNLINEIFFAILED( vector.GetCapacity() == number );
      RETURNLINEIFFAILED( vector.m_capacity == vector.GetCapacity() );

      // just enough to force a resize
      for( unsigned i = 0; i < number + 1; ++i )
      {
        Util::List< int > list;
        vector.PushBack( list );
      }
      RETURNLINEIFFAILED( vector.m_capacity == vector.GetCapacity() );
    }

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< Util::List< int > >, "unsigned const Vector< T >::GetCapacity() const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Clear()
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
      
    RETURNLINEIFFAILED( vector.m_array == 0 );
    RETURNLINEIFFAILED( vector.m_size == 0 );
    RETURNLINEIFFAILED( vector.m_capacity == 0 );
    RETURNLINEIFFAILED( vector.m_implementations == 0 );   
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< Util::List< UnitTestSampleStruct > >, "void Vector< T >::Clear()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_BasicAssignment0()
  {
    unsigned const number1 = 40, number2 = 200;
    Util::Vector< int > vector1, vector2( number2 );
    for( unsigned i = 0; i < number1; ++i )
      vector1.PushBack( i );
    for( unsigned i = 0; i < number2; ++i )
      vector2.PushBack( i );

    vector1 = vector2;
    RETURNLINEIFFAILED( CheckUtilVectorInit< int >( vector1, vector2.m_capacity, vector2.m_size ) == 0 );
    RETURNLINEIFFAILED( vector1.m_array != vector2.m_array );
    for( unsigned i = 0; i < number2; ++i )
      RETURNLINEIFFAILED( CheckUtilVectorAgainstContainer< int >( vector1, vector2 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< int >, "Vector< T >& Vector< T >::operator=( Vector< T > const& vector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_BasicAssignment1()
  {
    unsigned const number1 = 123, number2 = 500;
    Util::Vector< int > vector( number1 );
    Util::List< int > list;
    for( unsigned i = 0; i < number1; ++i )
      vector.PushBack( i );
    for( unsigned i = 0; i < number2; ++i )
      list.PushBack( i );
    vector = list;

    RETURNLINEIFFAILED( CheckUtilVectorInit< int >( vector, number2 ) == 0 );      
    RETURNLINEIFFAILED( CheckUtilVectorAgainstContainer< int >( vector, list ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< int >, 
                                        "Container< T >& Vector< T >::operator=( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_ArraySubscript()
  {
    unsigned const number = 1001;
    double doubles[ number ];
    for( unsigned i = 0; i < number; ++i )
      doubles[ i ] = (double)rand();
    Util::Vector< double > vector( doubles, number );

    for( unsigned i = 0; i < number; ++i )
    {
      RETURNLINEIFFAILED( vector[ i ] == vector.m_array[ i ] );
      RETURNLINEIFFAILED( vector[ i ] == doubles[ i ] );
    }

    unsigned const halfNumber = number / 2;
    vector[ halfNumber ] = 0.0;
    RETURNLINEIFFAILED( vector[ halfNumber ] == 0.0 );
    RETURNLINEIFFAILED( vector[ halfNumber ] == vector.m_array[ halfNumber ] );

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< double >, "T& Vector< T >::operator[]( int const index ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Addition()
  {
    unsigned char const number1 = 100, number2 = 200;
    Util::Vector< unsigned char > vector1, vector2;
    for( unsigned char i = 0; i < number1; ++i )
      vector1.PushBack( i );
    for( unsigned char i = 0; i < number2; ++i )
      vector2.PushBack( number1 + i );
    Util::Vector< unsigned char > vector3( vector1 + vector2 );

    RETURNLINEIFFAILED( CheckUtilVectorInit< unsigned char >( vector3, vector1.m_size + vector2.m_size ) == 0 );
    RETURNLINEIFFAILED( vector3.m_array != vector1.m_array && vector3.m_array != vector2.m_array );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< unsigned char >( vector3, vector1.m_array, number1 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilVectorAgainstArray< unsigned char >( vector3, number1, vector2.m_array, number2 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< unsigned char >, 
                                        "Vector< T > Vector< T >::operator+( Vector< T > const& vector ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_AdditionAssignment()
  {
    unsigned char const number1 = 100, number2 = 200;
    Util::Vector< unsigned char > vector1, vector2;
    for( unsigned char i = 0; i < number1; ++i )
      vector1.PushBack( i );
    for( unsigned char i = 0; i < number2; ++i )
      vector2.PushBack( number1 + i );
    vector1 += vector2;
      
    RETURNLINEIFFAILED( CheckUtilVectorInit< unsigned char >( vector1, number1 + number2 ) == 0 );
    RETURNLINEIFFAILED( vector1.m_array != vector2.m_array );

    for( unsigned i = 0; i < number1; ++i )
      RETURNLINEIFFAILED( vector1.m_array[ i ] == i );
    for( unsigned i = 0; i < number2; ++i )
      RETURNLINEIFFAILED( vector1.m_array[ i + number1 ] == vector2.m_array[ i ] );

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< unsigned char >, 
                                        "Vector< T >& Vector< T >::operator+=( Vector< T > const& vector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilVector::Vector_Indirection()
  {
    Util::Vector< float > vector;
    vector.PushBack( 1.1f );
    vector.PushBack( 2.2f );
    vector.PushBack( 3.3f );

    RETURNLINEIFFAILED( *vector == vector.m_array );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::Vector< float >, "T const* Vector< T >::operator*() const" ) );
    return 0;
  }
     

  template< typename T >
  unsigned const TestHelper_UtilVector::CheckUtilVectorInit( Util::Vector< T > const& vector, unsigned const capacity, unsigned const size )
  {
    RETURNLINEIFFAILED( vector.m_capacity == capacity );
    return CheckUtilVectorInit( vector, size );
  }
    
    
  template< typename T >
  unsigned const TestHelper_UtilVector::CheckUtilVectorInit( Util::Vector< T > const& vector, unsigned const size )
  {
    RETURNLINEIFFAILED( vector.m_size == size );
    RETURNLINEIFFAILED( vector.m_array != 0 );
    RETURNLINEIFFAILED( vector.m_implementations == 0 );
    return 0;
  }

    
  template< typename T >
  unsigned const TestHelper_UtilVector::CheckUtilVectorAgainstArray( Util::Vector< T > const& vector, 
                                                                     T const * const compareAgainst, 
                                                                     unsigned const compareAgainstLen )
  {      
    return CheckUtilVectorAgainstArray( vector, 0, compareAgainst, compareAgainstLen );
  }

    
  template< typename T >
  unsigned const TestHelper_UtilVector::CheckUtilVectorAgainstArray( Util::Vector< T > const& vector,
                                                                     unsigned const vectorStartPos,
                                                                     T const * const compareAgainst, 
                                                                     unsigned const compareAgainstLen )
  {      
    for( unsigned i = vectorStartPos, j = 0; j < compareAgainstLen; ++i, ++j )
      RETURNLINEIFFAILED( vector.m_array[ i ] == compareAgainst[ j ] );
    return 0;
  }
  
    
  template< typename T >
  unsigned const TestHelper_UtilVector::CheckUtilVectorAgainstContainer( Util::Vector< T > const& vector, 
                                                                          Util::Container< T > const& container )
  {    
    Util::Container< T >::Iterator itB = container.Begin(),
                                    itE = container.End();
    for( unsigned i = 0; itB != itE; ++itB, ++i )
      RETURNLINEIFFAILED( vector.m_array[ i ] == itB.Get() );
    return 0;
  }

}
