
#ifndef TEST_UNITTESTHELPER_H
#define TEST_UNITTESTHELPER_H


namespace Util
{
  template< typename T > class SortedList;
}


namespace Test
{  

  class TestHelper_UtilSortedList
  {
    public:
      static unsigned const SortedList_Constructor0();
      static unsigned const SortedList_Constructor1();
      static unsigned const SortedList_Constructor2();
      static unsigned const SortedList_CopyConstructor();
      static unsigned const SortedList_PushFront();
      static unsigned const SortedList_PushBack();
      static unsigned const SortedList_PopFront();
      static unsigned const SortedList_PopBack();
      static unsigned const SortedList_PopFirst();
      static unsigned const SortedList_PopAll();
      static unsigned const SortedList_Contains();
      static unsigned const SortedList_Clear();
      static unsigned const SortedList_BasicAssignment0();
      static unsigned const SortedList_BasicAssignment1();
      static unsigned const SortedList_Addition();
      static unsigned const SortedList_AdditionAssignment();


    private:
      template< typename T >
      static unsigned const CheckUtilSortedList( Util::SortedList< T > const& sList );
      template< typename T >
      static unsigned const CheckEmptyUtilSortedList( Util::SortedList< T > const& sList );
      template< typename T >
      static unsigned const CheckUtilSortedListFrontAndBack( Util::SortedList< T > const& sList, unsigned const size, bool endCheck );

      template< typename T >
      static void WriteSortedList( Util::SortedList< T > const& sList );

  };

}

#endif
