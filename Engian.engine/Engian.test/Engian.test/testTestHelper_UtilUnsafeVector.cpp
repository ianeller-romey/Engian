
#include "testTestHelper_UtilUnsafeVector.h"
#include "testTestHelper_UtilContainer.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilUnsafeVector.h"
#include "utilList.h"


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_Constructor0()
  {
    Util::UnsafeVector< int > uVector;

    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< int >( uVector, Util::UnsafeVector< int >::c_defaultCapacity, 0 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "UnsafeVector< T >::UnsafeVector()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_Constructor1()
  {
    unsigned const capacity = 200;
    Util::UnsafeVector< int > uVector( capacity );

    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< int >( uVector, capacity, 0 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "UnsafeVector< T >::UnsafeVector( unsigned const capacity )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_Constructor2()
  {
    unsigned const size = 150;
    int numbers[ size ];
    for( unsigned i = 0; i < size; ++i )
      numbers[ i ] = rand();
    Util::UnsafeVector< int > uVector( numbers, size );
      
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< int >( uVector, size, size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstArray< int >( uVector, numbers, size ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< int > , "UnsafeVector< T >::UnsafeVector( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_Constructor3()
  {
    unsigned const size = 80;
    double doubles[ size ];
    for( unsigned i = 0; i < size; ++i )
      doubles[ i ] = (double)rand();
    Util::List< double > list( doubles, size );
    Util::UnsafeVector< double > uVector( list );
            
    unsigned const listSize = TestHelper_UtilContainer::GetUtilContainerSize< double >( list );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< double >( uVector, listSize, listSize ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstContainer< double >( uVector, list ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< double >, "UnsafeVector< T >::UnsafeVector( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_CopyConstructor()
  {
    Util::UnsafeVector< float > uVector1;
    for( int i = 1000; i >= 0; --i )
      uVector1.PushBack( (float)i );
    Util::UnsafeVector< float > uVector2( uVector1 );
      
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< float >( uVector2, uVector1.m_capacity, uVector1.m_size ) == 0 );
    RETURNLINEIFFAILED( uVector2.m_array != uVector1.m_array );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstContainer< float >( uVector2, uVector1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< float >, "UnsafeVector< T >::UnsafeVector( UnsafeVector< T > const& uVector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_PushFront()
  {
    unsigned const number = 40;
    unsigned short numbers[ number ];
    Util::UnsafeVector< unsigned short > uVector;
    for( int i = number - 1; i >= 0; --i )
    {
      numbers[ i ] = (unsigned short)( rand() );
      uVector.PushFront( numbers[ i ] );
    }
      
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< unsigned short >( uVector, number ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstArray< unsigned short >( uVector, numbers, number ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< unsigned short >, "void UnsafeVector< T >::PushFront( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_PushBackRange0()
  {
    unsigned const number = 388;
    double numbers[ number ];
    for( unsigned i = 0; i < number; ++i )
      numbers[ i ] = (double)rand();
    Util::UnsafeVector< double > uVector( number );
    uVector.PushBackRange( numbers, number );
      
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< double >( uVector, number ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstArray< double >( uVector, numbers, number ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< double >, 
                                        "void UnsafeVector< T >::PushBackRange( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_PushBackRange1()
  {
    unsigned const number = 388;
    char numbers[ number ];
    for( unsigned i = 0; i < number; ++i )
      numbers[ i ] = 0 - (char)rand();
    Util::UnsafeVector< char > uVector1( numbers, number ),
                                uVector2;
    uVector2.PushBackRange( uVector1 );
      
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< char >( uVector2, uVector1.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstContainer< char >( uVector2, uVector1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< char >, "void UnsafeVector< T >::PushBackRange( UnsafeVector< T > const& vector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_BasicAssignment0()
  {
    unsigned const number1 = 40, number2 = 200;
    Util::UnsafeVector< int > uVector1, uVector2( number2 );
    for( unsigned i = 0; i < number1; ++i )
      uVector1.PushBack( i );
    for( unsigned i = 0; i < number2; ++i )
      uVector2.PushBack( i );

    uVector1 = uVector2;
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit< int >( uVector1, uVector2.m_capacity, uVector2.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstContainer< int >( uVector1, uVector2 ) == 0 );
      
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< int >, 
                                        "UnsafeVector< T >& UnsafeVector< T >::operator=( UnsafeVector< T > const& uVector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilUnsafeVector::UnsafeVector_BasicAssignment1()
  {
    unsigned const number1 = 123, number2 = 500;
    Util::UnsafeVector< int > uVector1( number1 );
    Util::List< int > list1;
    for( unsigned i = 0; i < number1; ++i )
      uVector1.PushBack( i );
    for( unsigned i = 0; i < number2; ++i )
      list1.PushBack( i );
    uVector1 = list1;

    RETURNLINEIFFAILED( CheckUtilUnsafeVectorInit( uVector1, TestHelper_UtilContainer::GetUtilContainerSize< int >( list1 ) ) == 0 );
    RETURNLINEIFFAILED( CheckUtilUnsafeVectorAgainstContainer< int >( uVector1, list1 ) == 0 );
      
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::UnsafeVector< int >, "Container< T >& UnsafeVector< T >::operator=( Container< T > const& container )" ) );
    return 0;
  }


  template< typename T >
  static unsigned const TestHelper_UtilUnsafeVector::CheckUtilUnsafeVectorInit( Util::UnsafeVector< T > const& uVector, 
                                                                                unsigned const capacity,
                                                                                unsigned const size )
  {
    RETURNLINEIFFAILED( uVector.m_capacity == capacity );
    return CheckUtilUnsafeVectorInit( uVector, size );
  }
    
    
  template< typename T >
  static unsigned const TestHelper_UtilUnsafeVector::CheckUtilUnsafeVectorInit( Util::UnsafeVector< T > const& uVector, unsigned const size )
  {
    RETURNLINEIFFAILED( uVector.m_size == size );
    RETURNLINEIFFAILED( uVector.m_array != 0 );
    RETURNLINEIFFAILED( uVector.m_implementations == 0 );
    return 0;
  }

    
  template< typename T >
  static unsigned const TestHelper_UtilUnsafeVector::CheckUtilUnsafeVectorAgainstArray( Util::UnsafeVector< T > const& uVector, 
                                                                                        T const * const compareAgainst, 
                                                                                        unsigned const compareAgainstLen )
  {      
    for( unsigned i = 0; i < compareAgainstLen; ++i )
      RETURNLINEIFFAILED( uVector.m_array[ i ] == compareAgainst[ i ] );
    return 0;
  }
  
    
  template< typename T >
  static unsigned const TestHelper_UtilUnsafeVector::CheckUtilUnsafeVectorAgainstContainer( Util::UnsafeVector< T > const& uVector, 
                                                                                            Util::Container< T > const& container )
  {    
    Util::Container< T >::Iterator itB = container.Begin(),
                                    itE = container.End();
    for( unsigned i = 0; itB != itE; ++itB, ++i )
      RETURNLINEIFFAILED( uVector.m_array[ i ] == itB.Get() );
    return 0;
  }
  
}
