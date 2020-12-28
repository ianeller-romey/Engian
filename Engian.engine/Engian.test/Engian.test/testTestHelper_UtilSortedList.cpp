
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
    int numDigits = 0, n;
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

    WriteSortedList(sList2);

    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PushFront()
  {
    unsigned const numberOfClasses = 4;
    UnitTestSampleClass sampleClass1( "sampleClass", 100, UnitTestSampleStruct( 1, 2, 3, NULL ) ),
                        sampleClass2( "a", 1, UnitTestSampleStruct( 0, 0, 0, NULL ) ),
                        sampleClass3( "contrarian", 99, UnitTestSampleStruct(1, 2, 3, NULL) ),
                        sampleClass4( "big banana", 66, UnitTestSampleStruct( 0, 0, 1, NULL ) );

    Util::SortedList< UnitTestSampleClass > sList;
    sList.PushFront( sampleClass1 );
    sList.PushFront( sampleClass2 );
    sList.PushFront( sampleClass3 );
    sList.PushFront( sampleClass4 );

    Util::SortedList< UnitTestSampleClass >::Iterator  itB = sList.Begin(),
                                                       itE = sList.End();

    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, numberOfClasses, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );
    RETURNLINEIFFAILED( *itB == sampleClass2 );
    ++itB;
    RETURNLINEIFFAILED( *itB == sampleClass4 );
    ++itB;
    RETURNLINEIFFAILED( *itB == sampleClass3 );
    ++itB;
    RETURNLINEIFFAILED( *itB == sampleClass1 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< UnitTestSampleClass >, "void SortedList< T >::PushFront( T const& t )") );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PushBack()
  {
    unsigned const numberOfClasses = 4;
    UnitTestSampleClass sampleClass1( "sampleClassWithACoolName", 1000000, UnitTestSampleStruct( 1, 2, 3, NULL ) ),
                        sampleClass2( "anaconda", 1, UnitTestSampleStruct( 0, 0, 0, NULL ) ),
                        sampleClass3( "Coooooooooooooool beans", 999, UnitTestSampleStruct(1, 2, 3, NULL) ),
                        sampleClass4( "REALLY big banana", 50, UnitTestSampleStruct( 0, 0, 1, NULL ) );

    Util::SortedList< UnitTestSampleClass > sList;
    sList.PushBack( sampleClass1 );
    sList.PushBack( sampleClass2 );
    sList.PushBack( sampleClass3 );
    sList.PushBack( sampleClass4 );

    Util::SortedList< UnitTestSampleClass >::Iterator  itB = sList.Begin(),
                                                       itE = sList.End();

    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, numberOfClasses, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );
    RETURNLINEIFFAILED( *itB == sampleClass2 );
    ++itB;
    RETURNLINEIFFAILED( *itB == sampleClass4 );
    ++itB;
    RETURNLINEIFFAILED( *itB == sampleClass3 );
    ++itB;
    RETURNLINEIFFAILED( *itB == sampleClass1 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< UnitTestSampleClass >, "void SortedList< T >::PushBack( T const& t )") );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopFront()
  {
    int const arraySize = 12;
    int const negativeOneHundred = -100,
              negativeOne = -1,
              zero = 0,
              one = 1,
              fortyTwo = 42,
              fortyThree = 43,
              fortyFive = 45,
              oneHundred = 100,
              twoHundredFortyThree = 243,
              fiveThousand = 5000,
              eightThousand = 8000,
              eightThousandOne = 8001;
    int numbers[ arraySize ] = { fortyThree, eightThousand, twoHundredFortyThree, 
                                 one, fortyTwo, fortyFive, eightThousandOne, fiveThousand, zero, 
                                 negativeOne, oneHundred, negativeOneHundred };

    Util::SortedList< int > sList;
    for( auto i = 0; i < arraySize; ++i )
    {
      sList.Push( numbers[ i ] );
    }

    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, arraySize, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
    for( auto i = 0; i < arraySize - 1; ++i )
    {
      sList.PopFront();
      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, arraySize - i - 1, true ) == 0);
      RETURNLINEIFFAILED( CheckUtilSortedList< int >(sList) == 0 );
    }
    sList.PopFront();
    RETURNLINEIFFAILED( CheckEmptyUtilSortedList< int >( sList ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "void SortedList< T >::PopFront()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopBack()
  {
    int const arraySize = 100;
    int numbers[ arraySize ];
    for( auto i = 0; i < arraySize; ++i )
    {
      numbers[ i ] = rand();
    }

    Util::SortedList< int > sList;
    for( auto i = 0; i < arraySize; ++i )
    {
      sList.Push( numbers[ i ] );
    }

    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, arraySize, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
    for( auto i = 0; sList.GetSize() > 1; ++i )
    {
      sList.PopBack();
      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, arraySize - i - 1, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
    }
    sList.PopBack();
    RETURNLINEIFFAILED( CheckEmptyUtilSortedList< int >( sList ) == 0 );
    RETURNLINEIFFAILED(DFT_FUNC_CHECK( Util::SortedList< int >, "void SortedList< T >::PopBack()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopFirst()
  {
    int const arraySize = 12;
    double const negativeTwentyPointTwo = -20.2,
                 negativeOne = -1.0,
                 zero = 0.0,
                 elevenPointTwentyTwo = 11.22,
                 fortyTwo = 42.0,
                 fortyTwoPointOne = 42.1,
                 fortyTwoPointTwo = 42.2,
                 oneHundredPointNine = 100.9,
                 twoHundredFortyThreePointThreeHundredFortyTwo = 243.342,
                 fiveThousand = 5000.0;
    double numbers[ arraySize ] = { fortyTwo, fiveThousand, twoHundredFortyThreePointThreeHundredFortyTwo,
                                    elevenPointTwentyTwo, oneHundredPointNine, fiveThousand, fortyTwoPointOne,
                                    negativeTwentyPointTwo, negativeOne, fiveThousand, zero, fortyTwoPointTwo };

    Util::SortedList< double > sList;
    for( auto i = 0; i < arraySize; ++i )
    {
      sList.Push( numbers[ i ] );
    }

    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    // make sure to remove the value "fiveThousand" three times, 
    // and make sure the value is still present after the first two removals
    // also, make sure to remove another value, say "fortyTwoPointTwo", twice,
    // and make sure the size of the list doesn't change after the second removal
    sList.PopFirst( fiveThousand );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 1, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );
    RETURNLINEIFFAILED( sList.Contains( fiveThousand ) );

    sList.PopFirst( twoHundredFortyThreePointThreeHundredFortyTwo );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 2, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( fortyTwoPointOne );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 3, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( zero );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 4, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( fiveThousand );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 5, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );
    RETURNLINEIFFAILED( sList.Contains( fiveThousand ) );

    sList.PopFirst( fortyTwoPointTwo );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 6, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( fortyTwoPointTwo );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 6, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( oneHundredPointNine );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 7, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( negativeTwentyPointTwo );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 8, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( elevenPointTwentyTwo );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 9, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( fiveThousand );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 10, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );
    RETURNLINEIFFAILED( sList.Contains( fiveThousand ) == false );

    sList.PopFirst( negativeOne );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< double >( sList, arraySize - 11, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< double >( sList ) == 0 );

    sList.PopFirst( fortyTwo );
    RETURNLINEIFFAILED( CheckEmptyUtilSortedList< double >( sList ) == 0 );

    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< double >, "void SortedList< T >::PopFirst( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_PopAll()
  {
    int const arraySize = 10;
    unsigned const numberOfClasses = 7;
    UnitTestSampleClass sampleClass1( "sampleClass", 100, UnitTestSampleStruct( 1, 2, 3, NULL ) ),
                        sampleClass2( "a", 1, UnitTestSampleStruct( 0, 0, 0, NULL ) ),
                        sampleClass3( "contrarian", 99, UnitTestSampleStruct(1, 2, 3, NULL) ),
                        sampleClass4( "big banana", 66, UnitTestSampleStruct( 0, 0, 1, NULL ) ),
                        sampleClass5( "zigzagoon zigzagoon", 800000, UnitTestSampleStruct( 100, 200, 300, NULL ) ),
                        sampleClass6( "big banana", 100, UnitTestSampleStruct( 100, 100, 100, NULL ) ),
                        sampleClass7( "UNUSED", 0, UnitTestSampleStruct( 0, 0, 0, NULL ) );

    Util::SortedList< UnitTestSampleClass > sList;
    sList.PushFront( sampleClass1 );
    sList.PushFront( sampleClass2 );
    sList.PushFront( sampleClass3 );
    sList.PushFront( sampleClass4 );
    sList.PushFront( sampleClass5 );
    sList.PushFront( sampleClass6 );
    sList.PushFront( sampleClass5 );
    sList.PushFront( sampleClass4 );
    sList.PushFront( sampleClass4 );
    sList.PushFront( sampleClass4 );

    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, arraySize, true) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );

    sList.PopAll( sampleClass4 );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, arraySize - 4, true) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );

    sList.PopAll( sampleClass4 );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, arraySize - 4, true) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );

    sList.PopAll( sampleClass5 );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, arraySize - 4 - 2, true) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );

    sList.PopAll( sampleClass7 );
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< UnitTestSampleClass >( sList, arraySize - 4 - 2, true) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< UnitTestSampleClass >( sList ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< UnitTestSampleClass >, "void SortedList< T >::PopAll( T const& t )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Contains()
  {
    // does contain
    {
      auto const numbers = 10000;
      auto const contains = numbers / 3;
      Util::SortedList< int > sList;
      for( auto i = 0; i < numbers; ++i )
      {
        sList.Push( i );
      }

      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, numbers, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
      RETURNLINEIFFAILED( sList.Contains( contains ) );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "bool const SortedList< T >::Contains( T const& t ) const" ) );
    }

    // doesn't contain
    {
      auto const numbers = 10000;
      auto const contains = numbers + 1;
      Util::SortedList< int > sList;
      for( auto i = 0; i < numbers; ++i )
      {
        sList.Push( i );
      }

      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, numbers, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
      RETURNLINEIFFAILED( sList.Contains( contains ) == false );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "bool const SortedList< T >::Contains( T const& t ) const" ) );
    }

    // does contain with duplicate
    {
      auto const numbers = 10000;
      auto const contains = numbers / 3;
      Util::SortedList< int > sList;
      for( auto i = 0; i < numbers; ++i )
      {
        sList.Push( i );
      }
      sList.Push( contains );

      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, numbers, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
      RETURNLINEIFFAILED( sList.Contains( contains ) );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "bool const SortedList< T >::Contains( T const& t ) const" ) );
    }

    // doesn't contain after removal
    {
      auto const numbers = 10000;
      auto const contains = numbers / 3;
      Util::SortedList< int > sList;
      for( auto i = 0; i < numbers; ++i )
      {
        sList.Push( i );
      }
      sList.PopFirst( contains );

      RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList, numbers, true ) == 0 );
      RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList ) == 0 );
      RETURNLINEIFFAILED( sList.Contains( contains ) == false );
      RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "bool const SortedList< T >::Contains( T const& t ) const" ) );
    }
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Clear()
  {
    auto const numbers = 9999;
    Util::SortedList< float > sList;
    for( auto i = 0; i < numbers; ++i )
    {
      sList.Push( (float)rand() );
    }

    sList.Clear();

    RETURNLINEIFFAILED( CheckEmptyUtilSortedList< float >( sList ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< float >( sList ) == 0 );
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< float >, "void Container< T >::Clear()" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_BasicAssignment()
  {
    auto const firstArraySize = 500;
    int firstArray[ firstArraySize ] = {};
    for( auto i = 0; i < firstArraySize; ++i )
    {
      firstArray[ i ] = rand();
    }
    Util::SortedList< int > sList1( firstArray, firstArraySize );

    auto const secondArraySize = 999;
    int secondArray[ secondArraySize ] = {};
    for( auto i = 0; i < secondArraySize; ++i )
    {
      secondArray[ i ] = rand();
    }
    Util::SortedList< int > sList2( secondArray, secondArraySize );

    sList1 = sList2;
    auto itB = sList1.Begin(),
         itE = sList1.End();
    
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList1, secondArraySize, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList1 ) == 0 );
    for( int i = 0; itB != itE; ++i, ++itB )
    {
      RETURNLINEIFFAILED( *itB == secondArray[ i ] );
    }
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "SortedList< T >& SortedList< T >::operator=( SortedList< T > const& sortedList )" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_Addition()
  {
    auto const firstArraySize = 500,
               secondArraySize = 999;
    int allNumbers[ firstArraySize + secondArraySize ] = {};
    for( auto i = 0, j = firstArraySize + secondArraySize; i < j; ++i )
    {
      allNumbers[ i ] = rand();
    }
    Util::SortedList< int > sList1( allNumbers, firstArraySize ),
                            sList2( allNumbers + firstArraySize, secondArraySize );

    auto sList3 = sList1 + sList2;
    
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList3, secondArraySize, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList3 ) == 0 );
    for( auto i = 0, j = firstArraySize + secondArraySize; i < j; ++i )
    {
      RETURNLINEIFFAILED( sList3.Contains( allNumbers[ i ] ) );
    }
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "SortedList< T > SortedList< T >::operator+( SortedList< T > const& sortedList ) const" ) );
    return 0;
  }


  unsigned const TestHelper_UtilSortedList::SortedList_AdditionAssignment()
  {
    auto const firstArraySize = 500,
               secondArraySize = 999;
    int allNumbers[ firstArraySize + secondArraySize ] = {};
    for( auto i = 0, j = firstArraySize + secondArraySize; i < j; ++i )
    {
      allNumbers[ i ] = rand();
    }
    Util::SortedList< int > sList1( allNumbers, firstArraySize ),
                            sList2( allNumbers + firstArraySize, secondArraySize );

    sList1 += sList2;
    
    RETURNLINEIFFAILED( CheckUtilSortedListFrontAndBack< int >( sList1, secondArraySize, true ) == 0 );
    RETURNLINEIFFAILED( CheckUtilSortedList< int >( sList1 ) == 0 );
    for( auto i = 0, j = firstArraySize + secondArraySize; i < j; ++i )
    {
      RETURNLINEIFFAILED( sList1.Contains( allNumbers[ i ] ) );
    }
    RETURNLINEIFFAILED( DFT_FUNC_CHECK( Util::SortedList< int >, "SortedList< T >& SortedList< T >::operator+=( SortedList< T > const& sortedList )" ) );
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
    
    std::ofstream output( "C:\\Build\\Engian\\Engian.engine\\Engian.test\\sampleoutput.txt", std::ofstream::out );
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
