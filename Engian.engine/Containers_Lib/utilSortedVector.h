
#ifndef UTIL_SORTEDVECTOR_H
#define UTIL_SORTEDVECTOR_H

#include "debugForTestDefines.h"

#include "utilSortedContainer.h"
#include "utilVector.h"


namespace Util
{

  template< typename T >
  class SortedVector : public SortedContainer< T >, public Vector< T >
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEF
      DFT_UTILSORTEDVECTOR_FRIEND

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
      virtual SortedContainer< T >& operator=( SortedContainer< T > const& sortedContainer );

      virtual SortedVector< T > operator+( SortedVector< T > const& vector ) const;
      virtual SortedVector< T >& operator+=( SortedVector< T > const& vector );
      
      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void PushBackRange( T const * const tArray, unsigned const size );
      virtual void PushBackRange( Container< T > const& container );


    protected:
      virtual bool const Search( unsigned& startIndex, T const& t ) const;

      void ShiftAndPush( unsigned const pushIndex, T const& t );

      unsigned const FindInsertionIndex( T const& t, bool& contains ) const;
      void QuickSort(  T* const tArray, int left, int rght );
  };

}

#include "utilSortedVector.inl"

#endif
