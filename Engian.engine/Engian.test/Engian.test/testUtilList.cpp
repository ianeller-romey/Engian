
#include "testIcle.h"

#ifdef RUN_UNIT_TESTS

#include "utilList.h"
#include "utilUnsafeVector.h"

#include "testUtilList_Helpers.h"


namespace Test
{

  UnitTestChassis::UnitTestDictionaryPair UnitTestChassis::UnitTestArray_TestUtilList[] = {
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_AdvanceValue ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_GetValue ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_EqualTo ),
    T_FUNC_ARR_DEF( TestUtilList_ListIteratorImpl_NotEqualTo ),
    T_FUNC_ARR_DEF( TestUtilList_List_Constructor0 ),
    T_FUNC_ARR_DEF( TestUtilList_List_Constructor1 ),
    T_FUNC_ARR_DEF( TestUtilList_List_Constructor2 ),
    T_FUNC_ARR_DEF( TestUtilList_List_CopyConstructor ),
    T_FUNC_ARR_DEF( TestUtilList_List_Begin ),
    T_FUNC_ARR_DEF( TestUtilList_List_End ),
    T_FUNC_ARR_DEF( TestUtilList_List_PushFront ),
    T_FUNC_ARR_DEF( TestUtilList_List_PushBack ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopFront ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopBack ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopFirst ),
    T_FUNC_ARR_DEF( TestUtilList_List_PopAll ),
    T_FUNC_ARR_DEF( TestUtilList_List_Contains ),
    T_FUNC_ARR_DEF( TestUtilList_List_BasicAssignment0 ),
    T_FUNC_ARR_DEF( TestUtilList_List_BasicAssignment1 ),
    T_FUNC_ARR_DEF( TestUtilList_List_Addition ),
    T_FUNC_ARR_DEF( TestUtilList_List_AdditionAssignment )
  };


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_Constructor0( char const * const name )
  {
    try
    {
      Util::List< double > list;
      list.PushBack( 1.1 );
      Util::List< double >::Iterator itB = list.Begin(), itE = list.End();

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< double >, "List< T >::ListIteratorImpl::ListIteratorImpl( ListNode* const listNode )" ), 
                   name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_AdvanceValue( char const * const name )
  {
    try
    {
      unsigned const number = 50;
      UnitTestSampleStruct* structs = UnitTestSampleStruct::CreateABunch( number );
      Util::List< UnitTestSampleStruct > list;
      list.PushBackRange( structs, number );
      Util::List< UnitTestSampleStruct >::Iterator itB = list.Begin(), itE = list.End();
      for( ; itB != itE; ++itB ) ;
        TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< UnitTestSampleStruct >, "void List< T >::ListIteratorImpl::AdvanceValue()" ), 
                        name, "Appropriate function was not called", delete [] structs );
      delete [] structs;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_GetValue( char const * const name )
  {
    try
    {
      unsigned const number = 50;
      UnitTestSampleStruct* structs = UnitTestSampleStruct::CreateABunch( number );
      Util::List< UnitTestSampleStruct > list;
      list.PushBackRange( structs, number );
      Util::List< UnitTestSampleStruct >::Iterator itB = list.Begin(), itE = list.End();
      for( unsigned i = 0; itB != itE; ++itB, ++i ) 
        TEST_ASSERT_EX( itB.Get() == structs[ i ], name, "did not return the appropriate value", delete [] structs );
      TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< UnitTestSampleStruct >, "T const& List< T >::ListIteratorImpl::GetValue() const" ), 
                      name, "Appropriate function was not called", delete [] structs );
      delete [] structs;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_EqualTo( char const * const name )
  {
    try
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

        TEST_ASSERT( ( itB1 == itB2 ) == false, name, "returned true for two Iterators from separate List< T > instances" );
        TEST_ASSERT( ( itE1 == itE2 ) == false, name, "returned true for two Iterators from separate List< T > instances" );
        for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
          TEST_ASSERT( ( itB1 == itE1 ) == false, name, "returned true for non-equivalent Iterators from the same List< T > instance" );
        Util::List< bool >::Iterator itAlt( itB1 );
        TEST_ASSERT( itB1 == itAlt, name, "returned false for two equivalent Iterators from the same List< T > instance" );
        for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
          TEST_ASSERT( itB1 == itAlt, name, "returned false for two equivalent Iterators from the same List< T > instance" );
        TEST_ASSERT( DFT_FUNC_CHECK( Util::List< bool >, "bool const List< T >::ListIteratorImpl::operator==( IteratorImpl const& iterator ) const" ), 
                     name, "Appropriate function was not called", delete [] structs );
      }

      {
        Util::List< int > list;
        list.PushBack( 100 );
        list.PushBack( 100 );
        Util::List< int >::Iterator it1 = list.Begin()++,
                                    it2 = list.Begin();
        TEST_ASSERT( it1.Get() == it2.Get(), name, "Test invalidated because Iterators being compared do not have the same value" );
        TEST_ASSERT( ( it1 == it2 ) == false, name, "returned true for unequivalent Iterators holding the same value" );
      }
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_ListIteratorImpl_NotEqualTo( char const * const name )
  {
    try
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

      TEST_ASSERT( itB1 != itB2, name, "returned false for two Iterators from separate List< T > instances" );
      TEST_ASSERT( itE1 != itE2, name, "returned false for two Iterators from separate List< T > instances" );
      for( unsigned i = 0; i < number / 2; ++i, ++itB1 )
        TEST_ASSERT( itB1 != itE1, name, "returned false for non-equivalent Iterators from the same List< T > instance" );
      Util::List< bool >::Iterator itAlt( itB1 );
      TEST_ASSERT( ( itB1 != itAlt ) == false, name, "returned true for two equivalent Iterators from the same List< T > instance" );
      for( unsigned i = number / 2; i < number; ++i, ++itB1, ++itAlt )
        TEST_ASSERT( ( itB1 != itAlt ) == false, name, "returned true for two equivalent Iterators from the same List< T > instance" );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< bool >, "bool const List< T >::ListIteratorImpl::operator!=( IteratorImpl const& iterator ) const" ), 
                   name, "Appropriate function was not called", delete [] structs );

      {
        Util::List< int > list;
        list.PushBack( 100 );
        list.PushBack( 100 );
        Util::List< int >::Iterator it1 = list.Begin()++,
                                    it2 = list.Begin();
        TEST_ASSERT( it1.Get() == it2.Get(), name, "Test invalidated because Iterators being compared do not have the same value" );
        TEST_ASSERT( it1 != it2, name, "returned false for unequivalent Iterators holding the same value" );
      }
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Constructor0( char const * const name )
  {
    try
    {
      Util::List< Util::Vector< int > > list;

      TEST_ASSERT( UnitTestChassis_Helper_List< Util::Vector< int > >::CheckEmptyList( &list ) == 0, name, "did not properly initialize list" );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T >::List()" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Constructor1( char const * const name )
  {
    try
    {
      unsigned const number = 10;
      char chars[ 10 ] = { 'a', 'b', 'c', 'd', 'e', 1, 2, 3, 4, 5 };
      Util::List< char > list( chars, number );

      TEST_ASSERT( UnitTestChassis_Helper_List< char >::CheckListFrontAndBack( &list, number, true ) == 0, name, "did not correctly initialize m_front or m_back" );
      TEST_ASSERT( UnitTestChassis_Helper_List< char >::CheckListAgainstArray( &list, chars, number, 1 ) == 0, name, "failed a list check" );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T >::List( T const * const tArray, unsigned const size )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Constructor2( char const * const name )
  {
    try
    {
      unsigned const size = 80;
      double* doubles = new double[ size ];
      Util::Vector< double > vector( doubles, size );
      Util::List< double > list( vector );

      TEST_ASSERT_EX( UnitTestChassis_Helper_List< double >::CheckListFrontAndBack( &list, vector.m_size, true ) == 0, name, "did not correctly initialize m_front or m_back", delete [] doubles );
      TEST_ASSERT_EX( UnitTestChassis_Helper_List< double >::CheckListAgainstArray( &list, vector.m_array, vector.m_size, 1 ) == 0, name, "failed a list check", delete [] doubles );

      TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T >::List( Container< T > const& container )" ), name, "Appropriate function was not called", delete [] doubles );
      delete [] doubles;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_CopyConstructor( char const * const name )
  {
    try
    {
      Util::List< float > list1;
      for( int i = 1000; i >= 0; --i )
        list1.PushBack( (float)i );
      Util::List< float > list2( list1 );

      TEST_ASSERT( UnitTestChassis_Helper_List< float >::CheckListFrontAndBack( &list2, list1.m_size, true ) == 0, name, "did not correctly initialize m_front or m_back" );
      Util::Container< float >* containerPtr = &list1;
      TEST_ASSERT( UnitTestChassis_Helper_List< float >::CheckListAgainstContainer( &list2, containerPtr ) == 0, name, "failed a list check" );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T >::List( List< T > const& list )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Begin( char const * const name )
  {
    try
    {
      unsigned const number = 25;
      Util::List< char > list;
      for( unsigned i = 0; i < number; ++i )
        list.PushBack( (char)i );
      {
        Util::List< char >::Iterator itB = list.Begin();
        TEST_ASSERT( itB.dbgGet_m_implementation() != 0, name, "did not create a ListIteratorImpl instance" );
        TEST_ASSERT( &( itB.Get() ) == list.dbgGet_m_front()->m_data, name, "returned an Iterator not pointing to the first element" );
        TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "Iterator List< T >::Begin() const" ), name, "Appropriate function was not called" );
      }
      TEST_ASSERT( list.m_implementations == 0, name, "List< T > did not have m_implementations reset to 0 after all Iterators left scope" );

      // check for exceptions when creating an iterator from an empty List< T >
      {
        Util::List< short > list;
        Util::List< short >::Iterator itB = list.Begin();
        itB.Get();
      }
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_End( char const * const name )
  {
    try
    {
      unsigned const number = 25;
      Util::List< char > list;
      for( unsigned i = 0; i < number; ++i )
        list.PushBack( (char)i );
      {
        Util::List< char >::Iterator itE = list.End();
        Util::List< char >::ListIteratorImpl* itImpl = dynamic_cast< Util::List< char >::ListIteratorImpl* >( itE.m_implementation );
        TEST_ASSERT( itImpl != 0, name, "did not create a ListIteratorImpl instance" );
        TEST_ASSERT( itImpl->m_listNode == list.m_end, name, "returned an Iterator not pointing to m_end" );
        TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "Iterator const List< T >::End() const" ), name, "Appropriate function was not called" );
      }
      TEST_ASSERT( list.m_implementations == 0, name, "List< T > did not have m_implementations reset to 0 after all Iterators left scope" );

      // check for exceptions when creating an iterator from an empty List< T >
      {
        Util::List< short > list;
        Util::List< short >::Iterator itE = list.End();
        itE.Get();
      }
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PushFront( char const * const name )
  {
    try
    {
      unsigned const number = 40;
      UnitTestSampleStruct* testStructs = UnitTestSampleStruct::CreateABunch( number );
      Util::List< UnitTestSampleStruct > list;
      for( unsigned i = 0; i < number; ++i )
        list.PushFront( testStructs[ i ] );

      TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleStruct >::CheckListFrontAndBack( &list, number, true ) == 0, name, "did not correctly update m_front or m_back", delete [] testStructs );
      TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleStruct >::CheckListAgainstArray( &list, testStructs + number - 1, number, -1 ) == 0, name, "failed a list check", delete [] testStructs );

      TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "void List< T >::PushFront( T const& t )" ), name, "Appropriate function was not called", delete [] testStructs );
      delete [] testStructs;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PushBack( char const * const name )
  {
    try
    {
      unsigned const number = 40;
      UnitTestSampleClass* testClasses = UnitTestSampleClass::CreateABunch( number );
      Util::List< UnitTestSampleClass > list;
      for( unsigned i = 0; i < number; ++i )
        list.PushBack( testClasses[ i ] );

      TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleClass >::CheckListFrontAndBack( &list, number, true ) == 0, name, "did not correctly update m_front or m_back", delete [] testClasses );
      TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleClass >::CheckListAgainstArray( &list, testClasses, number, 1 ) == 0, name, "failed a list check", delete [] testClasses );

      TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "void List< T >::PushBack( T const& t )" ), name, "Appropriate function was not called", delete [] testClasses );
      delete [] testClasses;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopFront( char const * const name )
  {
    try
    {
      unsigned const number = 60;
      UnitTestSampleStruct* testStructs = UnitTestSampleStruct::CreateABunch( number );
      Util::List< UnitTestSampleStruct > list;
      for( unsigned i = 0; i < number; ++i )
        list.PushBack( testStructs[ i ] );
      
      for( unsigned i = 0; i < number; ++i )
      {
        list.PopFront();
        TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleStruct >::CheckListFrontAndBack( &list, number - 1 - i, i != number - 1 ) == 0, name, "did not correctly update m_front or m_back", delete [] testStructs );
        TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleStruct >::CheckListAgainstArray( &list, testStructs + 1 + i, number - 1 - i, 1 ) == 0, name, "failed a list check", delete [] testStructs );
      }
      TEST_ASSERT_EX( list.IsEmpty(), name, "Container< T >::IsEmpty() did not return true after", delete [] testStructs );
      TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "void List< T >::PopFront()" ), name, "Appropriate function was not called", delete [] testStructs );

      // checking for exceptions
      list.PopFront();

      delete [] testStructs;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopBack( char const * const name )
  {
    try
    {
      unsigned const number = 123;
      UnitTestSampleClass* testClasses = UnitTestSampleClass::CreateABunch( number );
      Util::List< UnitTestSampleClass > list;
      for( unsigned i = 0; i < number; ++i )
        list.PushBack( testClasses[ i ] );
      
      for( unsigned i = 0; i < number; ++i )
      {
        list.PopBack();
        TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleClass >::CheckListFrontAndBack( &list, number - 1 - i, i != number - 1 ) == 0, name, "did not decrease the list's m_size variable to the correct value", delete [] testClasses );        
        TEST_ASSERT_EX( UnitTestChassis_Helper_List< UnitTestSampleClass >::CheckListAgainstArray( &list, testClasses, number - 1 - i, 1 ) == 0, name, "failed a list check", delete [] testClasses );
      }
      TEST_ASSERT_EX( list.IsEmpty(), name, "Container< T >::IsEmpty() did not return true after", delete [] testClasses );
      TEST_ASSERT_EX( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "void List< T >::PopBack()" ), name, "Appropriate function was not called", delete [] testClasses );

      // checking for exceptions
      list.PopBack();

      delete [] testClasses;
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopFirst( char const * const name )
  {
    try
    {
      {
        unsigned numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11, 1, 0 };
        Util::Vector< unsigned > vector( numbers, 15 );
        Util::List< unsigned > list( vector );

        list.PopFirst( 1 );
        vector.PopFirst( 1 );
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListFrontAndBack( &list, 14, true ) == 0, name, "did not decrement m_size correctly" );
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListAgainstArray( &list, vector.m_array, 14, 1 ) == 0, name, "failed a list check" );

        // do this twice, to make sure nothing changes after all the 1's are gone
        for( unsigned i = 0; i < 2; ++i )
        {
          list.PopFirst( 1 );
          vector.PopFirst( 1 );
          TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListFrontAndBack( &list, 13, true ) == 0, name, "did not decrement m_size correctly" );  
          TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListAgainstArray( &list, vector.m_array, 13, 1 ) == 0, name, "failed a list check" );
        }
      
        list.PopFirst( 0 );
        vector.PopFirst( 0 );
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListFrontAndBack( &list, 12, true ) == 0, name, "did not decrement m_size correctly" );  
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListAgainstArray( &list, vector.m_array, 12, 1 ) == 0, name, "failed a list check" );
      }
      
      // checking for exceptions
      {
        Util::List< float > list;
        list.PopFirst( 1.1f );
        TEST_ASSERT( UnitTestChassis_Helper_List< float >::CheckEmptyList( &list ) == 0, name, "altered an empty List< T >" );
      }

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "void List< T >::PopFirst( T const& t )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_PopAll( char const * const name )
  {
    try
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
          TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListFrontAndBack( &list, 13, true ) == 0, name, "did not decrement m_size correctly" );  
          TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListAgainstArray( &list, vector.m_array, 13, 1 ) == 0, name, "failed a list check" );
        }

        list.PopAll( 10 );
        vector.PopAll( 10 );
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListFrontAndBack( &list, 10, true ) == 0, name, "did not decrement m_size correctly" );  
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListAgainstArray( &list, vector.m_array, 10, 1 ) == 0, name, "failed a list check" );
      
        list.PopAll( 0 );
        vector.PopAll( 0 );
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListFrontAndBack( &list, 9, true ) == 0, name, "did not decrement m_size correctly" );  
        TEST_ASSERT( UnitTestChassis_Helper_List< unsigned >::CheckListAgainstArray( &list, vector.m_array, 9, 1 ) == 0, name, "failed a list check" );
      }

      // checking for exceptions
      {
        Util::List< float > list;
        list.PopAll( 1.1f );
        TEST_ASSERT( UnitTestChassis_Helper_List< float >::CheckEmptyList( &list ) == 0, name, "altered an empty List< T >" );
      }

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "void List< T >::PopAll( T const& t )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Contains( char const * const name )
  {
    try
    {
      Util::List< long > list;
      list.PushBack( 10000000 );
      list.PushBack( 9999999999999999 );
      list.PushBack( 12345678987654321 );
      
      TEST_ASSERT( list.Contains( 10000000 ), name, "did not return true for a contained value" );
      TEST_ASSERT( list.Contains( 9999999999999999 ), name, "did not return true for a contained value" );
      TEST_ASSERT( list.Contains( 12345678987654321 ), name, "did not return true for a contained value" );
      TEST_ASSERT( list.Contains( 1 ) == false, name, "did not return false for a value that was not contained" );
      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "bool const List< T >::Contains( T const& t ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_BasicAssignment0( char const * const name )
  {
    try
    {
      unsigned const number1 = 40, number2 = 200;
      Util::List< int > list1, list2;
      for( unsigned i = 0; i < number1; ++i )
        list1.PushBack( i );
      for( unsigned i = 0; i < number2; ++i )
        list2.PushBack( i );

      list1 = list2;
      TEST_ASSERT( UnitTestChassis_Helper_List< int >::CheckListFrontAndBack( &list1, number2, true ) == 0, name, "did not appropriately assign m_size" );
      Util::Container< int >* containerPtr = dynamic_cast< Util::Container< int >* >( &list2 );
      TEST_ASSERT( UnitTestChassis_Helper_List< int >::CheckListAgainstContainer( &list1, containerPtr ) == 0, name, "failed a list check" );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T >& List< T >::operator=( List< T > const& list )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_BasicAssignment1( char const * const name )
  {
    try
    {
      unsigned const number1 = 123, number2 = 500;
      Util::List< int > list;
      Util::Vector< int > vector;
      for( unsigned i = 0; i < number1; ++i )
        list.PushBack( i );
      for( unsigned i = 0; i < number2; ++i )
        vector.PushBack( i );

      list = vector;
      TEST_ASSERT( UnitTestChassis_Helper_List< int >::CheckListFrontAndBack( &list, number2, true ) == 0, name, "did not appropriately assign m_size" );
      Util::Container< int >* containerPtr = dynamic_cast< Util::Container< int >* >( &vector );
      TEST_ASSERT( UnitTestChassis_Helper_List< int >::CheckListAgainstContainer( &list, containerPtr ) == 0, name, "failed a list check" );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "Container< T >& List< T >::operator=( Container< T > const& container )" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_Addition( char const * const name )
  {
    try
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

      TEST_ASSERT( UnitTestChassis_Helper_List<  unsigned char  >::CheckListFrontAndBack( &list3, list1.m_size + list2.m_size, true ) == 0, name, "did not correctly assign m_size" );
      TEST_ASSERT( UnitTestChassis_Helper_List<  unsigned char  >::CheckListAgainstArray( &list3, numbers, number1 + number2, 1 ) == 0, name, "failed a list check" );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T > List< T >::operator+( List< T > const& list ) const" ), name, "Appropriate function was not called" );
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  char const * const UnitTestChassis::TestUtilList_List_AdditionAssignment( char const * const name )
  {
    try
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

      TEST_ASSERT( UnitTestChassis_Helper_List< unsigned char >::CheckListFrontAndBack( &list1, number1 + number2, true ) == 0, name, "did not correctly assign m_size" );
      TEST_ASSERT( UnitTestChassis_Helper_List< unsigned char >::CheckListAgainstArray( &list1, numbers, number1 + number2, 1 ) == 0, name, "failed a list check" );

      TEST_ASSERT( DFT_FUNC_CHECK( Util::List< BARFBARFBAAARF >, "List< T >& List< T >::operator+=( List< T > const& list )" ), name, "Appropriate function was not called" );
    
    }
    catch( ... )
    {
      return TEST_EXCEPTION;
    }
    return 0;
  }


  extern "C"
  {

    TESTICLE_API void __stdcall GetTests_TestUtilList
    (
      /* out */ char*** allTests,
      /* out */ int* numTests
    )
    {
      *numTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilList );
      UnitTestChassis::GetTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilList, *numTests, allTests );
    }


    TESTICLE_API void __stdcall RunTests_TestUtilList
    (
      char** testsToRun,  
      int numTests,
      /* out */  char*** allResults
    )
    {
      int numUnitTests = T_FUNC_ARR_SIZE( UnitTestChassis::UnitTestArray_TestUtilList );
      char const** const testResults = new char const*[ numTests ];

      UnitTestChassis::RunTests_UnitTests( UnitTestChassis::UnitTestArray_TestUtilList, numUnitTests, testsToRun, numTests, allResults );
    }

  }

}

#endif
