
#include "testTestHelper_UtilList.h"
#include "testTestHelper_UtilContainer.h"
#include "testTestHelper_UtilVector.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilList.h"
#include "utilVector.h"


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{
    
  unsigned const TestHelper_UtilList::ListIteratorImpl_Constructor0()
  {
    Util::List< double > list;
    list.PushBack( 1.1 );
    Util::List< double >::Iterator itB = list.Begin(), itE = list.End();

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< double >, "List< T >::ListIteratorImpl::ListIteratorImpl( ListNode* const listNode )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::ListIteratorImpl_AdvanceValue()
  {
    unsigned const number = 50;
    UnitTestSampleStruct structs[ number ];
    UnitTestSampleStruct::UpdateAnArray( structs, number );
    Util::List< UnitTestSampleStruct > list;
    list.PushBackRange( structs, number );
    Util::List< UnitTestSampleStruct >::Iterator itB = list.Begin(), itE = list.End();
    for( ; itB != itE; ++itB ) ;
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< UnitTestSampleStruct >, "void List< T >::ListIteratorImpl::AdvanceValue()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::ListIteratorImpl_GetValue()
  {
    unsigned const number = 50;
    UnitTestSampleStruct structs[ number ];
    UnitTestSampleStruct::UpdateAnArray( structs, number );
    Util::List< UnitTestSampleStruct > list;
    list.PushBackRange( structs, number );
    Util::List< UnitTestSampleStruct >::Iterator itB = list.Begin(), itE = list.End();
    for( unsigned i = 0; itB != itE; ++itB, ++i ) 
      RETURNLINEIFFAILED( itB.Get() == structs[ i ] );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< UnitTestSampleStruct >, "T const& List< T >::ListIteratorImpl::GetValue() const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::ListIteratorImpl_EqualTo()
  {
    {
      unsigned const number = 50;
      Util::List< bool > list1, list2;
      bool bools[ number ];
      list1.PushBackRange( bools, number );
      list2.PushBackRange( bools, number );
      Util::List< bool >::Iterator itB1 = list1.Begin(), 
                                    itE1 = list1.End(),
                                    itB2 = list2.Begin(),
                                    itE2 = list2.End();

      RETURNLINEIFFAILED( itB1 == itB2 );
      RETURNLINEIFFAILED( itE1 == itE2 );
      for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
        RETURNLINEIFFAILED( itB1 == itE1 );
      Util::List< bool >::Iterator itAlt( itB1 );
      RETURNLINEIFFAILED( itB1 == itAlt );
      for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
        RETURNLINEIFFAILED( itB1 == itAlt )
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< bool >, "bool const List< T >::ListIteratorImpl::operator==( IteratorImpl const& iterator ) const" ) );
      return 0;
    }

    {
      Util::List< int > list;
      list.PushBack( 100 );
      list.PushBack( 100 );
      Util::List< int >::Iterator it1 = list.Begin()++,
                                  it2 = list.Begin();
      RETURNLINEIFFAILED( it1.Get() == it2.Get() );
      RETURNLINEIFFAILED( ( it1 == it2 ) == false );
    }
    return 0;
  }


  unsigned const TestHelper_UtilList::ListIteratorImpl_NotEqualTo()
  {
    unsigned const number = 50;
    Util::List< bool > list1, list2;
    bool bools[ number ];
    list1.PushBackRange( bools, number );
    list2.PushBackRange( bools, number );
    Util::List< bool >::Iterator itB1 = list1.Begin(), 
                                  itE1 = list1.End(),
                                  itB2 = list2.Begin(),
                                  itE2 = list2.End();

    RETURNLINEIFFAILED( itB1 != itB2 );
    RETURNLINEIFFAILED( itE1 != itE2 );
    for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
      RETURNLINEIFFAILED( itB1 != itE1 );
    Util::List< bool >::Iterator itAlt( itB1 );
    RETURNLINEIFFAILED( ( itB1 != itAlt ) == false );
    for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
      RETURNLINEIFFAILED( ( itB1 != itAlt ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< bool >, 
                                        "bool const List< T >::ListIteratorImpl::operator!=( IteratorImpl const& iterator ) const" ) );

    {
      Util::List< int > list;
      list.PushBack( 100 );
      list.PushBack( 100 );
      Util::List< int >::Iterator it1 = list.Begin()++,
                                  it2 = list.Begin();
      RETURNLINEIFFAILED( it1.Get() == it2.Get() );
      RETURNLINEIFFAILED( it1 != it2 );
    }
    return 0;
  }


  unsigned const TestHelper_UtilList::List_Constructor0()
  {
    Util::List< Util::Vector< int > > list;

    RETURNLINEIFFAILED( CheckEmptyUtilList< Util::Vector< int > >( list ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< Util::Vector< int > >, "List< T >::List()" ) );
    return 0;                   
  }


  unsigned const TestHelper_UtilList::List_Constructor1()
  {
    unsigned const number = 10;
    char chars[ 10 ] = { 'a', 'b', 'c', 'd', 'e', 1, 2, 3, 4, 5 };
    Util::List< char > list( chars, number );

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< char >( list, number, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstArray< char >( list, chars, number, 1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< char >, "List< T >::List( T const * const tArray, unsigned const size )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_Constructor2()
  {
    unsigned const size = 80;
    double doubles[ size ];
    for( unsigned i = 0; i < size; ++i ) 
      doubles[ i ] = (double)rand();
    Util::Vector< double > vector( doubles, size );
    Util::List< double > list( vector );

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< double >( list, size, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstArray< double >( list, doubles, size, 1 ) == 0);
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< double >, "List< T >::List( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_CopyConstructor()
  {
    Util::List< float > list1;
    for( int i = 1000; i >= 0; --i )
      list1.PushBack( (float)i );
    Util::List< float > list2( list1 );

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< float >( list2, list1.GetSize(), true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstContainer< float >( list2, list1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< float >, "List< T >::List( List< T > const& list )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_Begin()
  {
    unsigned const number = 25;
    Util::List< char > list;
    for( unsigned i = 0; i < number; ++i )
      list.PushBack( (char)i );

    {
      Util::List< char >::Iterator itB = list.Begin();
      RETURNLINEIFFAILED( &( itB.Get() ) == list.m_front->m_data );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< char >, "Iterator List< T >::Begin() const" ) );
                     
    }
    RETURNLINEIFFAILED( list.m_implementations == 0 );
      
    // check for exceptions when creating an iterator from an empty List< T >
    {
      Util::List< short > list;
      Util::List< short >::Iterator itB = list.Begin();
      itB.Get();
    }

    return 0;
  }


  unsigned const TestHelper_UtilList::List_End()
  {
    unsigned const number = 25;
    Util::List< char > list;
    for( unsigned i = 0; i < number; ++i )
      list.PushBack( (char)i );
    {
      //RETURNLINEIFFAILED( CheckUtilListIteratorAgainstEnd( list ) );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< char >, "Iterator const List< T >::End() const" ) );
                     
    }
    RETURNLINEIFFAILED( list.m_implementations == 0 ); 
                   

    // check for exceptions when creating an iterator from an empty List< T >
    {
      Util::List< short > list;
      Util::List< short >::Iterator itE = list.End();
      itE.Get();
    }
  }


  unsigned const TestHelper_UtilList::List_PushFront()
  {
    unsigned const number = 40;
    UnitTestSampleStruct testStructs[ number ]; 
    UnitTestSampleStruct::UpdateAnArray( testStructs, number );
    Util::List< UnitTestSampleStruct > list;
    for( unsigned i = 0; i < number; ++i )
      list.PushFront( testStructs[ i ] );

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< UnitTestSampleStruct >( list, number, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstArray< UnitTestSampleStruct >( list, testStructs + number - 1, number, -1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< UnitTestSampleStruct >, "void List< T >::PushFront( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_PushBack()
  {
    unsigned const number = 40;
    UnitTestSampleClass testClasses[ number ];
    UnitTestSampleClass::UpdateAnArray( testClasses, number );
    Util::List< UnitTestSampleClass > list;
    for( unsigned i = 0; i < number; ++i )
      list.PushBack( testClasses[ i ] );

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< UnitTestSampleClass >( list, number, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstArray< UnitTestSampleClass >( list, testClasses, number, 1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< UnitTestSampleClass >, "void List< T >::PushBack( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_PopFront()
  {
    unsigned const number = 60;
    UnitTestSampleStruct testStructs[ number ];
    UnitTestSampleStruct::UpdateAnArray( testStructs, number );
    Util::List< UnitTestSampleStruct > list;
    for( unsigned i = 0; i < number; ++i )
      list.PushBack( testStructs[ i ] );
      
    for( unsigned i = 0; i < number; ++i )
    {
      list.PopFront();
      RETURNLINEIFFAILED( CheckUtilListFrontAndBack< UnitTestSampleStruct >( list, number - 1 - i, i != number - 1 ) == 0 );
      RETURNLINEIFFAILED( CheckUtilListAgainstArray< UnitTestSampleStruct >( list, testStructs + 1 + i, number - 1 - i, 1 ) == 0 );
    }
    RETURNLINEIFFAILED( list.IsEmpty() );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< UnitTestSampleStruct >, "void List< T >::PopFront()" ) );

    // checking for exceptions
    list.PopFront();

    return 0;
  }


  unsigned const TestHelper_UtilList::List_PopBack()
  {
    unsigned const number = 123;
    UnitTestSampleClass testClasses[ number ];
    UnitTestSampleClass::UpdateAnArray( testClasses, number );
    Util::List< UnitTestSampleClass > list;
    for( unsigned i = 0; i < number; ++i )
      list.PushBack( testClasses[ i ] );
      
    for( unsigned i = 0; i < number; ++i )
    {
      list.PopBack();
      RETURNLINEIFFAILED( CheckUtilListFrontAndBack< UnitTestSampleClass >( list, number - 1 - i, i != number - 1 ) == 0 );     
      RETURNLINEIFFAILED( CheckUtilListAgainstArray< UnitTestSampleClass >( list, testClasses, number - 1 - i, 1 ) == 0 );
    }
    RETURNLINEIFFAILED( list.IsEmpty() );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< UnitTestSampleClass >, "void List< T >::PopBack()" ) );

    // checking for exceptions
    list.PopBack();

    delete [] testClasses;
  }


  unsigned const TestHelper_UtilList::List_PopFirst()
  {
    {
      unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
      Util::Vector< unsigned > vector( numbers, 15 );
      Util::List< unsigned > list( vector );

      list.PopFirst( 1 );
      vector.PopFirst( 1 );
      RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned >( list, 14, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned >( list, 
                                                                  TestHelper_UtilVector::GetUtilVectorArray< unsigned >( vector ), 
                                                                  14, 
                                                                  1 ) == 0 );                     

      // do this twice, to make sure nothing changes after all the 1's are gone
      for( unsigned i = 0; i < 2; ++i )
      {
        list.PopFirst( 1 );
        vector.PopFirst( 1 );
        RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned >( list, 13, true ) == 0 );  
        RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned >( list, 
                                                                    TestHelper_UtilVector::GetUtilVectorArray< unsigned >( vector ), 
                                                                    13, 
                                                                    1 ) == 0 );                       
      }
      
      list.PopFirst( 0 );
      vector.PopFirst( 0 );
      RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned >( list, 12, true ) == 0 );  
      RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned >( list, 
                                                                  TestHelper_UtilVector::GetUtilVectorArray< unsigned >( vector ), 
                                                                  12, 
                                                                  1 ) == 0 );                     
    }
      
    // checking for exceptions
    {
      Util::List< float > list;
      list.PopFirst( 1.1f );
      RETURNLINEIFFAILED( CheckEmptyUtilList< float >( list ) == 0 );
    }

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< unsigned >, "void List< T >::PopFirst( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_PopAll()
  {
    {
      unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
      Util::Vector< unsigned > vector( numbers, 15 );
      Util::List< unsigned > list( vector );
        
      // do this twice, to make sure nothing changes after all the 1's are gone
      for( unsigned i = 0; i < 2; ++i )
      {
        list.PopAll( 1 );
        vector.PopAll( 1 );
        RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned >( list, 13, true ) == 0 );  
        RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned >( list, 
                                                                    TestHelper_UtilVector::GetUtilVectorArray< unsigned >( vector ), 
                                                                    13, 
                                                                    1 ) == 0 );
      }

      list.PopAll( 10 );
      vector.PopAll( 10 );
      RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned >( list, 10, true ) == 0 );  
      RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned >( list,
                                                                  TestHelper_UtilVector::GetUtilVectorArray< unsigned >( vector ), 
                                                                  10, 
                                                                  1 ) == 0 );
      
      list.PopAll( 0 );
      vector.PopAll( 0 );
      RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned >( list, 9, true ) == 0 );  
      RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned >( list,
                                                                  TestHelper_UtilVector::GetUtilVectorArray< unsigned >( vector ), 
                                                                  9, 
                                                                  1 ) == 0 );
    }

    // checking for exceptions
    {
      Util::List< float > list;
      list.PopAll( 1.1f );
      RETURNLINEIFFAILED( CheckEmptyUtilList< float >( list ) == 0 );
    }

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< unsigned >, "void List< T >::PopAll( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_Contains()
  {
    Util::List< long > list;
    list.PushBack( 10000000 );
    list.PushBack( 9999999999999999 );
    list.PushBack( 12345678987654321 );
      
    RETURNLINEIFFAILED( list.Contains( 10000000 ) );
    RETURNLINEIFFAILED( list.Contains( 9999999999999999 ) );
    RETURNLINEIFFAILED( list.Contains( 12345678987654321 ) );
    RETURNLINEIFFAILED( list.Contains( 1 ) == false );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< long >, "bool const List< T >::Contains( T const& t ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_BasicAssignment0()
  {
    unsigned const number1 = 40, number2 = 200;
    Util::List< int > list1, list2;
    for( unsigned i = 0; i < number1; ++i )
      list1.PushBack( i );
    for( unsigned i = 0; i < number2; ++i )
      list2.PushBack( i );

    list1 = list2;
    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< int >( list1, number2, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstContainer< int >( list1, list2 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< int >, "List< T >& List< T >::operator=( List< T > const& list )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_BasicAssignment1()
  {
    unsigned const number1 = 123, number2 = 500;
    Util::List< int > list;
    Util::Vector< int > vector;
    for( unsigned i = 0; i < number1; ++i )
      list.PushBack( i );
    for( unsigned i = 0; i < number2; ++i )
      vector.PushBack( i );

    list = vector;
    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< int >( list, number2, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstContainer< int >( list, vector ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< int >, 
                                        "Container< T >& List< T >::operator=( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_Addition()
  {
    unsigned char const number1 = 100, number2 = 200;
    unsigned char numbers[ number1 + number2 ];
    for( unsigned i = 0; i < number1 + number2; ++i )
      numbers[ i ] = (unsigned char)( rand() );
    Util::List< unsigned char > list1, list2;
    for( unsigned char i = 0; i < number1; ++i )
      list1.PushBack( numbers[ i ] );
    for( unsigned char i = 0; i < number2; ++i )
      list2.PushBack( numbers[ number1 + i ] );
    Util::List< unsigned char > list3( list1 + list2 );

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned char >( list3, list1.m_size + list2.m_size, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned char >( list3, numbers, number1 + number2, 1 ) == 0 );    
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< unsigned char >, 
                                        "List< T > List< T >::operator+( List< T > const& list ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilList::List_AdditionAssignment()
  {
    unsigned char const number1 = 100, number2 = 200;
    unsigned char numbers[ number1 + number2 ];
    for( unsigned i = 0; i < number1 + number2; ++i )
      numbers[ i ] = (unsigned char)( rand() );
    Util::List< unsigned char > list1, list2;
    for( unsigned char i = 0; i < number1; ++i )
      list1.PushBack( numbers[ i ] );
    for( unsigned char i = 0; i < number2; ++i )
      list2.PushBack( numbers[ number1 + i ] );
    list1 += list2;

    RETURNLINEIFFAILED( CheckUtilListFrontAndBack< unsigned char >( list1, number1 + number2, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilListAgainstArray< unsigned char >( list1, numbers, number1 + number2, 1 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::List< unsigned char >, 
                                        "List< T >& List< T >::operator+=( List< T > const& list )" ) );
    return 0;
  }

    
  template< typename T >
  unsigned const TestHelper_UtilList::CheckEmptyUtilList( Util::List< T > const& list )
  {
    RETURNLINEIFFAILED( list.m_size == 0 );
    RETURNLINEIFFAILED( list.m_implementations == 0 );
    RETURNLINEIFFAILED( list.m_end != 0 );
    RETURNLINEIFFAILED( list.m_end->m_prev == 0 );
    RETURNLINEIFFAILED( list.m_end->m_next == 0 );
    RETURNLINEIFFAILED( list.m_end->m_data == 0 );
    RETURNLINEIFFAILED( list.m_front != 0 );
    RETURNLINEIFFAILED( list.m_front == list.m_end );
    RETURNLINEIFFAILED( list.m_back != 0 );
    RETURNLINEIFFAILED( list.m_back == list.m_end );
    return 0;
  }

    
  template< typename T >
  unsigned const TestHelper_UtilList::CheckUtilListFrontAndBack( Util::List< T > const& list, unsigned const size, bool endCheck )
  {
    RETURNLINEIFFAILED( list.m_size == size );
    RETURNLINEIFFAILED( list.m_implementations == 0 );
    RETURNLINEIFFAILED( list.m_end != 0 );
    RETURNLINEIFFAILED( list.m_end->m_prev == 0 );
    RETURNLINEIFFAILED( list.m_end->m_next == 0 );
    RETURNLINEIFFAILED( list.m_end->m_data == 0 );
    RETURNLINEIFFAILED( list.m_front != 0 );
    RETURNLINEIFFAILED( list.m_back != 0 );
    if( endCheck )
    {
      RETURNLINEIFFAILED( list.m_front != list.m_end );
      RETURNLINEIFFAILED( list.m_front->m_prev == list.m_end );
      RETURNLINEIFFAILED( list.m_back != list.m_end );
      RETURNLINEIFFAILED( list.m_back->m_next == list.m_end ); 
    }
    return 0;
  }
  
    
  template< typename T >
  unsigned const TestHelper_UtilList::CheckUtilListAgainstArray( Util::List< T > const& list, 
                                                                      T const* compareAgainst, 
                                                                      unsigned const arraySize, 
                                                                      int const incr )
  {
    int i = 0;
    Util::List< T >::ListNode* node = list.m_front;
    for( ; node != list.m_end && abs( i ) < arraySize; node = node->m_next, i += incr )
    {
      if( node->m_prev != list.m_end )
      {
        RETURNLINEIFFAILED( *( node->m_prev->m_data ) == compareAgainst[ i - incr ] );
      }
      else
      {
        RETURNLINEIFFAILED( ( i == 0 ) == false );
      }

      if( node->m_next != list.m_end )
      {
        RETURNLINEIFFAILED( *( node->m_next->m_data ) == compareAgainst[ i + incr ] );
      }
      else
      {
        RETURNLINEIFFAILED( abs( i ) == arraySize - 1 );
      }

      RETURNLINEIFFAILED( *( node->m_data ) == compareAgainst[ i ] );
    }

    return 0;
  }

  
  template< typename T >
  unsigned const TestHelper_UtilList::CheckUtilListAgainstContainer( Util::List< T > const& list, Util::Container< T > const& container )
  {
    unsigned i = 0;
    Util::List< T >::ListNode *node = list.m_front;
    Util::Container< T >::Iterator itB = container.Begin(), itE = container.End();
    T prevData;
    for( ; node != 0 && itB != itE; node = node->m_next, ++itB, ++i )
    {
      if( node->m_prev != list.m_end )
      {
        RETURNLINEIFFAILED( *( node->m_prev->m_data ) == prevData );
      }
      else
      {
        RETURNLINEIFFAILED( i == 0 );
      }

      if( node->m_next != list.m_end )
      {
        RETURNLINEIFFAILED( *( node->m_next->m_data ) == ( Util::Container< T >::Iterator( itB )++ ).Get() );
      }
      else
      {
        RETURNLINEIFFAILED( i == TestHelper_UtilContainer::GetUtilContainerSize< T >( container ) - 1 );
      }

      RETURNLINEIFFAILED( *( node->m_data ) == itB.Get() );

      prevData = itB.Get();
    }

    return 0;
  }

}
