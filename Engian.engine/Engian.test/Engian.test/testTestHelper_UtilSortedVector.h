
#ifndef TEST_TESTHELPER_UTILSORTEDVECTOR_H
#define TEST_TESTHELPER_UTILSORTEDVECTOR_H


namespace Util
{
  template< typename T > class Container;
  template< typename T > class SortedVector;
}


namespace Test
{  

  class TestHelper_UtilSortedVector
  {
    public:
      static unsigned const SortedVector_Constructor0();
      static unsigned const SortedVector_Constructor1();
      static unsigned const SortedVector_Constructor2();
      static unsigned const SortedVector_Constructor3();
      static unsigned const SortedVector_CopyConstructor();
      static unsigned const SortedVector_PushFront();
      static unsigned const SortedVector_PushBack();
      static unsigned const SortedVector_PushBackRange0();
      static unsigned const SortedVector_PushBackRange1();
      static unsigned const SortedVector_Search();
      static unsigned const SortedVector_BasicAssignment0();
      static unsigned const SortedVector_BasicAssignment1();
      static unsigned const SortedVector_Addition();
      static unsigned const SortedVector_AdditionAssignment();

    private:
      template< typename T >
      static unsigned const CheckUtilSortedVector( Util::SortedVector< T > const& sVector );   
      template< typename T >
      static unsigned const CheckUtilSortedVectorInit( Util::SortedVector< T > const& sVector, unsigned const capacity, unsigned const size );   
      template< typename T >
      static unsigned const CheckUtilSortedVectorInit( Util::SortedVector< T > const& sVector, unsigned const size );    
      template< typename T >
      static unsigned const CheckUtilSortedVectorAgainstArray( Util::SortedVector< T > const& sVector, 
                                                               T const * const compareAgainst, 
                                                               unsigned const compareAgainstLen ); 
      template< typename T >
      static unsigned const CheckUtilSortedVectorAgainstContainer( Util::SortedVector< T > const& sVector, Util::Container< T > const& container );
  };

}

#endif
