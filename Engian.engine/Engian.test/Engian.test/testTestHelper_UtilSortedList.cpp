
#include "testTestHelper_UtilSortedList.h"
#include "testTestHelper_UtilContainer.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilSortedList.h"
#include "utilString.h"

#include <iostream>
#include <fstream>


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

  void WriteSortedListString( std::ofstream& file, 
                              char const * const string1,
                              char const * const string2,
                              char const * const string3 )
  {
    file << string1;
    file << string2;
    file << string3;
  }


  char const * const UpdateSortedListNodeString( char * const string, int value )
  {
    unsigned numDigits = 0, n;
    for( n = value; n; n /= 10 ) 
      ++numDigits;

    n = value;   
    for( int i = 10; i >= 0; --i )
    {
      if( i > numDigits - 1 )
        string[ 4 + i ] = ' ';
      else
      {
        string[ 4 + i ] = ( i > numDigits - 1 ) ? ' ' : ( n % 10 ) + 48;
        n /= 10;
      }
    }
    return string;
  }

  
  unsigned const TestHelper_UtilSortedList::SortedList_Constructor0()
  {
    Util::SortedList< int > sList;
      
    RETURNLINEIFFAILED( CheckEmptyUtilSortedList< int >( sList ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "SortedList< T >::SortedList()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Constructor1()
  {
    {
      unsigned const number = 200;
      int numbers[ number ];
      numbers[ 0 ] = 5000;
      for( unsigned i = 1; i < number; ++i )
        numbers[ i ] = rand();
      Util::SortedList< int > sList( numbers, number );

      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, number, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, 
                                          "SortedList< T >::SortedList( T const * const tArray, unsigned const size )" ) );
      //WriteSortedList< int >( sList );
    }

    {
      UnitTestSampleClass classes[] = { UnitTestSampleClass( "test1", 1, UnitTestSampleStruct( 1, 1, 1, 0 ) ),
                                        UnitTestSampleClass( "test3", 3, UnitTestSampleStruct( 3, 3, 3, 0 ) ),
                                        UnitTestSampleClass( "test5", 5, UnitTestSampleStruct( 5, 5, 5, 0 ) ),
                                        UnitTestSampleClass( "test0", 0, UnitTestSampleStruct( 0, 0, 0, 0 ) ),
                                        UnitTestSampleClass( "test6", 6, UnitTestSampleStruct( 6, 6, 6, 0 ) ) };
      unsigned const size = sizeof( classes ) / sizeof( UnitTestSampleClass );
      Util::SortedList< UnitTestSampleClass > sList( classes, size );

      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, size, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< UnitTestSampleClass >, 
                                          "SortedList< T >::SortedList( T const * const tArray, unsigned const size )" ) );
    }
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Constructor2()
  {
    unsigned const number = 1000;
    char characters[ number ];
    for( unsigned i = 0; i < number; ++i )
      characters[ i ] = (char)rand();
    characters[ number - 1 ] = '\0';
    Util::String string( characters );
    Util::SortedList< char > sList( string );
      
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< char >( sList, 
                                                                 TestHelper_UtilContainer::GetUtilContainerSize< char >( string ), 
                                                                 true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< char >( sList ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< char >, "SortedList< T >::SortedList( Container< T > const& container )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_CopyConstructor()
  {
    unsigned const number = 100;
    double doubles[ number ];
    for( unsigned i = 0; i < number; ++i )
      doubles[ i ] = number - i;//(double)rand();
    //doubles[ 75 ] = 45;
    Util::SortedList< double > sList1( doubles, number ),
                               sList2( sList1 );
    {
      Util::SortedList< double >::Iterator itB = sList1.Begin(),
                                           itE = sList1.End();
      unsigned i = 0;
      while( itB != itE )
      {
        ++i;
        ++itB;
      }

      Util::SortedList< double >::SortedListNode *nodeFront = 
        sList1.GetBottomTier( static_cast< Util::SortedList< double >::SortedListNode* >( sList1.m_front ),
                              sList1.m_tiers,
                              0 ),
                                                  *nodeEnd = 
        static_cast< Util::SortedList< double >::SortedListNode* >( sList1.m_end );
      unsigned j = 0;
      while( nodeFront != nodeEnd )
      {
        ++j;
        nodeFront = static_cast< Util::SortedList< double >::SortedListNode* >( nodeFront->m_next );
      }
    }
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList2, sList1.m_size, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList2 ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< double >, "SortedList< T >::SortedList( SortedList< T > const& sortedList )" ) );
    WriteSortedList< double >( sList2 );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PushFront()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PushBack()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopFront()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopBack()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopFirst()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopAll()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Contains()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Clear()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_BasicAssignment0()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_BasicAssignment1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Addition()
  {
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_AdditionAssignment()
  {
    return 0;
  }
     

  template< typename T >
  unsigned const TestHelper_UtilSortedList::CheckUtilSortedList( Util::SortedList< T > const& sList )
  {
    if( sList.m_size == 0 ) 
      return 0;

    Util::SortedList< T >::SortedListNode* headNode = sList.m_head;
    RETURNLINEIFFAILED( headNode );
    while( headNode != sList.m_end )
    {
      Util::SortedList< T >::SortedListNode* node = static_cast< Util::SortedList< T >::SortedListNode* >( headNode->m_next );
      while( node->m_next != sList.m_end )
      {
        RETURNLINEIFFAILED( *( node->m_data ) <= *( node->m_next->m_data ) );
        for( Util::SortedList< T >::SortedListNode* node2 = node->m_nextTier; node2 != sList.m_end; node2 = node2->m_nextTier )
        {
          RETURNLINEIFFAILED( node2 );
          RETURNLINEIFFAILED( *( node2->m_data ) == *( node->m_data ) );
        }

        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
        RETURNLINEIFFAILED( node );
      }
      headNode = headNode->m_nextTier;
    }
    return 0;
  }

    
  template< typename T >
  unsigned const TestHelper_UtilSortedList::CheckEmptyUtilSortedList( Util::SortedList< T > const& sList )
  {
    RETURNLINEIFFAILED( sList.m_size == 0 );
    RETURNLINEIFFAILED( sList.m_tiers == 0 );
    RETURNLINEIFFAILED( sList.m_implementations == 0 );
    RETURNLINEIFFAILED( sList.m_end != 0 );
    RETURNLINEIFFAILED( sList.m_end->m_prev == 0 );
    RETURNLINEIFFAILED( sList.m_end->m_next == 0 );
    RETURNLINEIFFAILED( sList.m_end->m_data == 0 );
    RETURNLINEIFFAILED( sList.m_front != 0 );
    RETURNLINEIFFAILED( sList.m_front == sList.m_end );
    RETURNLINEIFFAILED( sList.m_back != 0 );
    RETURNLINEIFFAILED( sList.m_back == sList.m_end );
    return 0;
  }

    
  template< typename T >
  unsigned const TestHelper_UtilSortedList::CheckUtilSortedListFrontAndBack( Util::SortedList< T > const& sList, 
                                                                             unsigned const size, 
                                                                             bool endCheck )
  {
    RETURNLINEIFFAILED( sList.m_size == size );
    RETURNLINEIFFAILED( sList.m_implementations == 0 );
    RETURNLINEIFFAILED( sList.m_end != 0 );
    RETURNLINEIFFAILED( sList.m_end->m_prev == 0 );
    RETURNLINEIFFAILED( sList.m_end->m_next == 0 );
    RETURNLINEIFFAILED( sList.m_end->m_data == 0 );
    RETURNLINEIFFAILED( sList.m_front != 0 );
    RETURNLINEIFFAILED( sList.m_back != 0 );
    RETURNLINEIFFAILED( sList.m_head != 0 );
    RETURNLINEIFFAILED( sList.m_head->m_data == 0 );
    RETURNLINEIFFAILED( sList.m_head->m_prev == sList.m_end );

    Util::SortedList< T >::SortedListNode* node = sList.m_head;
    unsigned calculatedTiers = 0;
    while( node != sList.m_end )
    {
      RETURNLINEIFFAILED( node->m_prev == sList.m_end );
      ++calculatedTiers;
      node = node->m_nextTier;
    }
    RETURNLINEIFFAILED( calculatedTiers - 1 == sList.m_tiers );

    node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( sList.m_back );
    RETURNLINEIFFAILED( node );
    while( node != sList.m_end )
    {
      RETURNLINEIFFAILED( node->m_next == sList.m_end );
      node = node->m_nextTier;
    }

    if( endCheck )
    {
      RETURNLINEIFFAILED( sList.m_front != sList.m_end );
      RETURNLINEIFFAILED( sList.m_front->m_prev != sList.m_end );
      RETURNLINEIFFAILED( sList.m_back != sList.m_end );
      RETURNLINEIFFAILED( sList.m_back->m_next == sList.m_end ); 
    }
    return 0;
  }


  template< typename T >
  void TestHelper_UtilSortedList::WriteSortedList( Util::SortedList< T > const& sList )
  {
    Util::SortedList< T >::SortedListNode* headNode = sList.m_head;

    char top[] = ";---           ---";
    char mid[] = ";|--           --|";
    char bot[] = ";-----------------";
    char pre[] = ";<--           ---";
    char nxt[] = ";---           -->";
    char tr1[] = ";        |        ";
    char tr2[] = ";                 ";
    char tr3[] = ";        v        ";
    char spc[] = ";                 ";
    
    std::ofstream output( "C:\\Users\\elleri\\Documents\\TestManager\\sampleoutput.txt", std::ofstream::out );
    for( int i = sList.m_tiers; i >= 0; --i )
    {
      Util::SortedList< T >::SortedListNode* node = headNode;
      while( node != sList.m_end && node )
      {
        WriteSortedListString( output,
                               spc,
                               UpdateSortedListNodeString( top, (int)( node ) ),
                               spc );
        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
      }
      output << '\n';

      node = headNode;
      while( node != sList .m_end && node )
      {
        WriteSortedListString( output,
                               UpdateSortedListNodeString( pre, (int)( node->m_prev ) ),
                               UpdateSortedListNodeString( mid, (int)( node->m_data ) ),
                               UpdateSortedListNodeString( nxt, (int)( node->m_next ) ) );
        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
      }
      output << '\n';

      node = headNode;
      while( node != sList .m_end && node )
      {
        WriteSortedListString( output,
                               spc,
                               bot,
                               spc );
        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
      }
      output << '\n';

      node = headNode;
      while( node != sList .m_end && node )
      {
        WriteSortedListString( output,
                               spc,
                               tr1,
                               spc );
        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
      }
      output << '\n';

      node = headNode;
      while( node != sList .m_end && node )
      {
        WriteSortedListString( output,
                               spc,
                               UpdateSortedListNodeString( tr2, (int)( node->m_nextTier ) ),
                               spc );
        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
      }
      output << '\n';

      node = headNode;
      while( node != sList .m_end && node )
      {
        WriteSortedListString( output,
                               spc,
                               tr3,
                               spc );
        node = dynamic_cast< Util::SortedList< T >::SortedListNode* >( node->m_next );
      }
      output << '\n';

      headNode = headNode->m_nextTier;
    }
    output.close();
  }

}
