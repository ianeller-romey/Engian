
#ifndef TEST_TESTHELPER_UTILLIST_H
#define TEST_TESTHELPER_UTILLIST_H


namespace Util
{
  template< typename T > class Container;
  template< typename T > class List;
}


namespace Test
{  

  class TestHelper_UtilList
  {
    public:
      static unsigned const ListIteratorImpl_Constructor0();
      static unsigned const ListIteratorImpl_AdvanceValue();
      static unsigned const ListIteratorImpl_GetValue();
      static unsigned const ListIteratorImpl_EqualTo();
      static unsigned const ListIteratorImpl_NotEqualTo();
      static unsigned const List_Constructor0();
      static unsigned const List_Constructor1();
      static unsigned const List_Constructor2();
      static unsigned const List_CopyConstructor();
      static unsigned const List_Begin();
      static unsigned const List_End();
      static unsigned const List_PushFront();
      static unsigned const List_PushBack();
      static unsigned const List_PopFront();
      static unsigned const List_PopBack();
      static unsigned const List_PopFirst();
      static unsigned const List_PopAll();
      static unsigned const List_Contains();
      static unsigned const List_BasicAssignment0();
      static unsigned const List_BasicAssignment1();
      static unsigned const List_Addition();
      static unsigned const List_AdditionAssignment();

    private:
      template< typename T >
      static bool const CheckEmptyUtilList( Util::List< T > const& list );
      template< typename T >
      static bool const CheckUtilListFrontAndBack( Util::List< T > const& list, unsigned const size, bool endCheck );
      template< typename T >
      static bool const CheckUtilListAgainstArray( Util::List< T > const& list, 
                                                           T const* compareAgainst, 
                                                           unsigned const arraySize, 
                                                           int const incr );
      template< typename T >
      static bool const CheckUtilListAgainstContainer( Util::List< T > const& list, Util::Container< T > const& container );

  };

}

#endif
