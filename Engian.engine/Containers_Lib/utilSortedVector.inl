
namespace Util
{
  
  template< typename T >
  SortedVector< T >::SortedVector() :
    Vector< T >(),
    SortedContainer< T >()
  {
  }

  
  template< typename T >
  SortedVector< T >::SortedVector( unsigned const capacity ) :
    Vector< T >( capacity ),
    SortedContainer< T >()
  {
  }

    
  template< typename T >
  SortedVector< T >::SortedVector( T const * const tArray, unsigned const size ) :
    Vector< T >( tArray, size ),
    SortedContainer< T >(),
  {
    QuickSort( m_array, 0, m_size - 1, m_greaterThanFunc, m_lessThanFunc );
  }

    
  template< typename T >
  SortedVector< T >::SortedVector( SortedVector const& sortedVector ) :
    // I can trust that this is already sorted
    Vector< T >( sortedVector.m_capacity )
  {
    for( unsigned i = 0; i < sortedVector.m_size; ++i )
      Vector< T >::PushBack( sortedVector[ i ] );
  }

    
  template< typename T >
  SortedVector< T >::~SortedVector()
  {
    Clear();
  }

    
  template< typename T >
  SortedVector< T >& SortedVector< T >::operator=( SortedVector< T > const& sortedVector )
  {
    Clear();

    m_capacity = sortedVector.GetSize();
    m_array = new T[ m_capacity ];
    for( unsigned i = 0, j = sortedVector.GetSize(); i < j; ++i )
      PushBack( sortedVector[ i ] );

    return *this;
  }

    
  template< typename T >
  SortedContainer< T >& SortedVector< T >::operator=( SortedContainer< T > const& sortedContainer )
  {
    Clear();

    m_capacity = sortedContainer.GetSize();
    m_array = new T[ m_capacity ];
    for( Iterator itB = sortedContainer.Begin(), itE = sortedContainer.End(); itB != itE; ++itB )
      PushBack( itB.Get() );

    return *this;
  }

    
  template< typename T >
  SortedVector< T > SortedVector< T >::operator+( SortedVector< T > const& sortedVector ) const
  {
    SortedVector< T > newSortedVector( *this );
    newSortedVector.PushBackRange( *sortedVector, sortedVector.GetSize() );
    return newSortedVector;
  }

    
  template< typename T >
  SortedVector< T >& SortedVector< T >::operator+=( SortedVector< T > const& sortedVector )
  {
    PushBackRange( *sortedVector, sortedVector.GetSize() );
    return *this;
  }

    
  template< typename T >
  void SortedVector< T >::PushFront( T const& t )
  {
    bool contains;
    ShiftAndPush( FindInsertionIndex( t, contains ), t );
  }

    
  template< typename T >
  void SortedVector< T >::PushBack( T const& t )
  {
    bool contains;
    ShiftAndPush( FindInsertionIndex( t, contains ), t );
  }

    
  template< typename T >
  void SortedVector< T >::PushBackRange( T const * const tArray, unsigned const size )
  {
    for( unsigned i = 0; i < size; ++i )
      Vector< T >::PushBack( tArray[ i ] );

    QuickSort( m_array, 0, m_size - 1 );
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void SortedVector< T >::PushBackRange( Container< T > const& container )
  {
    for( Container< T >::Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      Vector< T >::PushBack( *itB );

    QuickSort( m_array, 0, m_size - 1 );
    InvalidateAllIteratorImplementations();
  }

  
  template< typename T >
  bool const SortedVector< T >::Search( unsigned& startIndex, T const& t ) const
  {
    bool contains = false;
    unsigned containsIndex = FindInsertionIndex( t, contains );
    if( contains )
      startIndex = containsIndex;
    return contains;
  }


  template< typename T >
  void SortedVector< T >::ShiftAndPush( unsigned const startIndex, T const& t )
  {
    CheckAndGrow();
    for( unsigned i = m_size; i > startIndex; --i )
      m_array[ i ] = m_array[ i - 1 ];
    m_array[ startIndex ] = t;
    ++m_size;
    InvalidateAllIteratorImplementations();
  }

  
  template< typename T >
  unsigned const SortedVector< T >::FindInsertionIndex( T const& t, bool& contains ) const
  {
    contains = false;
    unsigned 
      max = m_size,
      min = 0,
      index = ( max - min ) / 2;
    while( max - min > 1 )
    {
      if( m_greaterThanFunc( m_array[ index ], t ) )
        max = index;
      else if( m_lessThanFunc( m_array[ index ], t ) )
        min = index;
      else if( m_equalityFunc( m_array[ index ], t ) )
      {
        contains = true;
        break;
      }
    }
    return index;
  }

  
  template< typename T >
  void SortedVector< T >::QuickSort(  T* const tArray, int left, int rght )
    {
      int i = left,
          j = rght;
      T mid = tArray[ ( i + j ) / 2 ],
        temp;
      do
      {
        // find element to the left greater than partition
        for ( ; m_lessThanFunc( tArray[ i ], mid ); ++i ) ;
        // find element to the right less than partition
        for ( ; m_greaterThanFunc( tArray[ j ], mid ); --j ) ;

        // we haven't crossed over, so swap
        if ( i <= j )
        {
          temp = tArray[ i ];
          tArray[ i ] = tArray[ j ];
          tArray[ j ] = temp;
          ++i; --j;
    }
    } while ( i <= j );

      // if there are still elements to the left, sort them
      if ( left < j )
        QuickSort( tArray, left, j );
      // if there are still elements to the right, sort them
      if ( i < rght )
        QuickSort( tArray, i, rght );
    }

}
