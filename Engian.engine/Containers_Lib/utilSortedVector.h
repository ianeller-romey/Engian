
#ifndef UTIL_SORTEDVECTOR_H
#define UTIL_SORTEDVECTOR_H

#include "debugForTestDefines.h"

#include "utilSorter.h"
#include "utilVector.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilSortedVector;
}
#define TESTHELPER_UTILSORTEDVECTOR_FRIEND friend class Test::TestHelper_UtilSortedVector
#else
#define TESTHELPER_UTILSORTEDVECTOR_FRIEND
#endif


namespace Util
{

  template< typename T >
  class SortedVector : public Sorter< T >, public Vector< T >
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEF;
      TESTHELPER_UTILSORTEDVECTOR_FRIEND;

      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );

      SortedVector();
      SortedVector( unsigned const capacity );
      SortedVector( T const * const tArray, unsigned const size );
      SortedVector( SortedVector< T > const& sortedVector );
      SortedVector( Container< T > const& container );
      virtual ~SortedVector();
      virtual SortedVector< T >& operator=( SortedVector< T > const& sortedVector );

      virtual SortedVector< T > operator+( SortedVector< T > const& vector ) const;
      virtual SortedVector< T >& operator+=( SortedVector< T > const& vector );
      
      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void PushBackRange( T const * const tArray, unsigned const size );
      virtual void PushBackRange( Container< T > const& container );


    protected:
      virtual bool const Search( unsigned& startIndex, T const& t ) const;

      void ShiftAndPush( unsigned pushIndex, T const& t );

      unsigned const FindInsertionIndex( T const& t, bool& contains ) const;
      void QuickSort(  T* const tArray, int left, int rght );


    private:
      unsigned const GetMidpoint( unsigned max, unsigned min ) const;

  };

}

#include "utilSortedVector.inl"

#endif
