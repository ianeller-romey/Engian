
#include "testTestHelper_UtilSortedVector.h"
#include "testTestHelper_UtilContainer.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilSortedVector.h"
#include "utilList.h"
#include "utilString.h"

#include <cstdlib>
#include <cstring>


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

  unsigned const TestHelper_UtilSortedVector::SortedVector_Constructor0()
  {
    Util::SortedVector< int > sVector;
      
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< int >( sVector, Util::SortedVector< int >::c_defaultCapacity, 0 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< int >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< int >, "SortedVector< T >::SortedVector()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_Constructor1()
  {
    unsigned const number = 1111;
    Util::SortedVector< int > sVector( number );

    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< int >( sVector, number, 0 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< int >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< int >, "SortedVector< T >::SortedVector()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_Constructor2()
  {
    UnitTestSampleClass classes[] = { UnitTestSampleClass( "test1", 1, UnitTestSampleStruct( 1, 1, 1, 0 ) ),
                                      UnitTestSampleClass( "test3", 3, UnitTestSampleStruct( 3, 3, 3, 0 ) ),
                                      UnitTestSampleClass( "test5", 5, UnitTestSampleStruct( 5, 5, 5, 0 ) ),
                                      UnitTestSampleClass( "test0", 0, UnitTestSampleStruct( 0, 0, 0, 0 ) ),
                                      UnitTestSampleClass( "test6", 6, UnitTestSampleStruct( 6, 6, 6, 0 ) ) };
    unsigned const size = sizeof( classes ) / sizeof( UnitTestSampleClass );
    Util::SortedVector< UnitTestSampleClass > sVector( classes, size );

    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< UnitTestSampleClass >( sVector, size, size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< UnitTestSampleClass >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< UnitTestSampleClass >, 
                                        "SortedVector< T >::SortedVector( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_Constructor3()
  {
    char characters[] = "a907gyadkjafa;dt4q938qapioucvhasd8uafu(_&*GY_(Q*Y_C(&GQW)*R!@#)+F)KX()*FGEQW()G&+E()FU*+_";
    unsigned const charactersLen = strlen( characters );
    Util::String string( characters );
    Util::SortedVector< char > sVector( string );
      
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< char >( sVector, 
                                                           TestHelper_UtilContainer::GetUtilContainerSize< char >( string ), 
                                                           TestHelper_UtilContainer::GetUtilContainerSize< char >( string ) ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< char >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< char >, "SortedVector< T >::SortedVector( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_CopyConstructor()
  {
    unsigned const number = 123;
    double doubles[ number ];
    for( unsigned i = 0; i < number; ++i )
      doubles[ i ] = (double)rand();
    Util::SortedVector< double > sVector1( doubles, number ),
                                 sVector2( sVector1 );
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< double >( sVector2, sVector1.m_capacity, sVector1.m_size ) );
    RETURNLINEIFFAILED( CheckUtilSortedVector< double >( sVector2 ) );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< double >, "SortedVector< T >::SortedVector( SortedVector const& sortedVector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_PushFront()
  {
    unsigned const number = 10;
    char chars[ number ] = { 'z', 'a', 'q', 'h', 'l', 'i', 'o', 'b', 'n', '!' };
    Util::SortedVector< char > sVector( chars, number );

    sVector.PushFront( 127 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< char >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< char >, "void SortedVector< T >::PushFront( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_PushBack()
  {
    unsigned const number = 10;
    char chars[ number ] = { 'z', 'a', 'q', 'h', 'l', 'i', 'o', 'b', 'n', '!' };
    Util::SortedVector< char > sVector( chars, number );

    sVector.PushBack( 1 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< char >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< char >, "void SortedVector< T >::PushBack( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_PushBackRange0()
  {
    unsigned const number1 = 500, number2 = 200;
    long longs1[ number1 ], longs2[ number2 ];
    for( unsigned i = 0; i < number1; ++i )
      longs1[ i ] = (long)( rand() % number1 );
    for( unsigned i = 0; i < number2; ++i )
      longs2[ i ] = (long)( rand() % number2 );
    Util::SortedVector< long > sVector;

    sVector.PushBackRange( longs1, number1 );
    sVector.PushBackRange( longs2, number2 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< long >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< long >, 
                                        "void SortedVector< T >::PushBackRange( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_PushBackRange1()
  {
    unsigned const number = 500;
    unsigned char numbers[ number ];
    for( unsigned i = 0; i < number; ++i )
      numbers[ i ] = (unsigned char)( rand() % number );
    Util::List< unsigned char > list( numbers, number );
    Util::SortedVector< unsigned char > sVector;

    sVector.PushBackRange( list );
    RETURNLINEIFFAILED( CheckUtilSortedVector< unsigned char >( sVector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< unsigned char >, 
                                        "void SortedVector< T >::PushBackRange( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_Search()
  {
    UnitTestSampleClass classes[] = { UnitTestSampleClass( "test1", 1, UnitTestSampleStruct( 1, 1, 1, 0 ) ),
                                      UnitTestSampleClass( "test3", 3, UnitTestSampleStruct( 3, 3, 3, 0 ) ),
                                      UnitTestSampleClass( "test5", 5, UnitTestSampleStruct( 5, 5, 5, 0 ) ),
                                      UnitTestSampleClass( "test0", 0, UnitTestSampleStruct( 0, 0, 0, 0 ) ),
                                      UnitTestSampleClass( "test6", 6, UnitTestSampleStruct( 6, 6, 6, 0 ) ) };
    unsigned const size = sizeof( classes ) / sizeof( UnitTestSampleClass );
    Util::SortedVector< UnitTestSampleClass > sVector( classes, size );

    UnitTestSampleClass testFail( "testFail", 100, UnitTestSampleStruct( 100, 100, 100, 0 ) );
    RETURNLINEIFFAILED( sVector.Contains( classes[ size / 2 ] ) );
    RETURNLINEIFFAILED( ( sVector.Contains( testFail ) == false ) );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< UnitTestSampleClass >, 
                                        "bool const SortedVector< T >::Search( unsigned& startIndex, T const& t ) const" ) );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< UnitTestSampleClass >, 
                                        "unsigned const SortedVector< T >::FindInsertionIndex( T const& t, bool& contains ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_BasicAssignment0()
  {
    unsigned const number1 = 500, number2 = 200;
    float numbers1[ number1 ], numbers2[ number2 ];
    for( unsigned i = 0; i < number1; ++i )
      numbers1[ i ] = (float)rand();
    for( unsigned i = 0; i < number2; ++i )
      numbers2[ i ] = (float)rand();
    Util::SortedVector< float > sVector1( numbers1, number1 ),
                                sVector2( numbers2, number2 );

    sVector2 = sVector1;
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< float >( sVector2, sVector1.m_size, sVector1.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< float >( sVector2 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVectorAgainstArray< float >( sVector2, sVector1.m_array, sVector1.m_size ) == 0 )
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< float >, 
                                        "SortedVector< T >& SortedVector< T >::operator=( SortedVector< T > const& sortedVector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_BasicAssignment1()
  {
    unsigned const number1 = 500, number2 = 200;
    float numbers1[ number1 ], numbers2[ number2 ];
    for( unsigned i = 0; i < number1; ++i )
      numbers1[ i ] = (float)rand();
    for( unsigned i = 0; i < number2; ++i )
      numbers2[ i ] = (float)rand();
    Util::SortedVector< float > sVector1( numbers1, number1 ),
                                sVector2( numbers2, number2 );

    sVector2 = sVector1;
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< float >( sVector2, sVector1.m_size, sVector1.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< float >( sVector2 ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVectorAgainstArray< float >( sVector2, sVector1.m_array, sVector1.m_size ) == 0 )
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< float >, 
                                        "SortedVector< T >& SortedVector< T >::operator=( SortedVector< T > const& sortedVector )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_Addition()
  {
    unsigned const number = 999;
    int numbers1[ number ], numbers2[ number ];
    for( unsigned i = 0; i < number; ++i )
    {
      numbers1[ i ] = rand();
      numbers2[ i ] = rand();
    }
    Util::SortedVector< int > sVector1( numbers1, number ),
                               sVector2( numbers2, number ),
                               sVector3( sVector1 + sVector2 );
    
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< int >( sVector3, 
                                                            sVector1.m_size + sVector2.m_size, 
                                                            sVector1.m_size + sVector2.m_size ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< int >( sVector3 ) == 0 );
    for( unsigned i = 0; i < number; ++i )
    {
      RETURNLINEIFFAILED( sVector3.Contains( sVector1[ i ] ) );
      RETURNLINEIFFAILED( sVector3.Contains( sVector2[ i ] ) );
    }
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< int >, 
                                        "SortedVector< T > SortedVector< T >::operator+( SortedVector< T > const& sortedVector ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedVector::SortedVector_AdditionAssignment()
  {
    unsigned const number = 999;
    int numbers1[ number ], numbers2[ number ];
    for( unsigned i = 0; i < number; ++i )
    {
      numbers1[ i ] = rand();
      numbers2[ i ] = rand();
    }
    Util::SortedVector< int > sVector1( numbers1, number ),
                              sVector2( numbers2, number );
    
    unsigned const oldSize = sVector2.m_size;
    sVector2 += sVector1;
    RETURNLINEIFFAILED( CheckUtilSortedVectorInit< int >( sVector2, sVector1.m_size + oldSize ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedVector< int >( sVector2 ) == 0 );
    for( unsigned i = 0; i < number; ++i )
      RETURNLINEIFFAILED( sVector2.Contains( sVector1[ i ] ) );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedVector< int >, 
                                        "SortedVector< T >& SortedVector< T >::operator+=( SortedVector< T > const& sortedVector )" ) );
    return 0;
  }
     

  template< typename T >
  unsigned const TestHelper_UtilSortedVector::CheckUtilSortedVector( Util::SortedVector< T > const& sVector )
  {
    if( sVector.m_size == 0 ) 
      return 0;
    for( unsigned i = 0, j = sVector.m_size - 1; i < j; ++i )
      RETURNLINEIFFAILED( sVector.m_array[ i ] <= sVector.m_array[ i + 1 ] );
    return 0;
  }
     

  template< typename T >
  unsigned const TestHelper_UtilSortedVector::CheckUtilSortedVectorInit( Util::SortedVector< T > const& sVector, 
                                                                         unsigned const capacity, 
                                                                         unsigned const size )
  {
    RETURNLINEIFFAILED( sVector.m_capacity == capacity );
    return CheckUtilSortedVectorInit( sVector, size );
  }
    
    
  template< typename T >
  unsigned const TestHelper_UtilSortedVector::CheckUtilSortedVectorInit( Util::SortedVector< T > const& sVector, unsigned const size )
  {
    RETURNLINEIFFAILED( sVector.m_size == size );
    RETURNLINEIFFAILED( sVector.m_array != 0 );
    RETURNLINEIFFAILED( sVector.m_implementations == 0 );
    return 0;
  }

    
  template< typename T >
  unsigned const TestHelper_UtilSortedVector::CheckUtilSortedVectorAgainstArray( Util::SortedVector< T > const& sVector, 
                                                                                 T const * const compareAgainst, 
                                                                                 unsigned const compareAgainstLen )
  {      
    for( unsigned i = 0; i < compareAgainstLen; ++i )
      RETURNLINEIFFAILED( sVector.m_array[ i ] == compareAgainst[ i ] );
    return 0;
  }
  
    
  template< typename T >
  unsigned const TestHelper_UtilSortedVector::CheckUtilSortedVectorAgainstContainer( Util::SortedVector< T > const& sVector, 
                                                                                     Util::Container< T > const& container )
  {    
    Util::Container< T >::Iterator itB = container.Begin(),
                                    itE = container.End();
    for( unsigned i = 0; itB != itE; ++itB, ++i )
      RETURNLINEIFFAILED( sVector.m_array[ i ] == itB.Get() );
    return 0;
  }
  
}
