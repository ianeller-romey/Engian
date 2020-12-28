
namespace Util
{
  
  template< typename T >
  SortedVector< T >::SortedVector() :
    Vector< T >(),
    Sorter< T >()
  {
    DFT_FUNC_TRACK( "SortedVector< T >::SortedVector()" );
  }

  
  template< typename T >
  SortedVector< T >::SortedVector( unsigned const capacity ) :
    Vector< T >( capacity ),
    Sorter< T >()
  {
    DFT_FUNC_TRACK( "SortedVector< T >::SortedVector( unsigned const capacity )" );
  }

    
  template< typename T >
  SortedVector< T >::SortedVector( T const * const tArray, unsigned const size ) :
    Vector< T >( tArray, size ),
    Sorter< T >()
  {
    DFT_FUNC_TRACK( "SortedVector< T >::SortedVector( T const * const tArray, unsigned const size )" );
    QuickSort( m_array, 0, m_size - 1 );
  }

    
  template< typename T >
  SortedVector< T >::SortedVector( SortedVector const& sortedVector ) :
    // I can trust that this is already sorted
    Vector< T >( sortedVector.m_capacity )
  {
    DFT_FUNC_TRACK( "SortedVector< T >::SortedVector( SortedVector const& sortedVector )" );
    m_size = sortedVector.m_size;
    for( unsigned i = 0; i < m_size; ++i )
    {
      m_array[ i ] = sortedVector.m_array[ i ];
    }
  }

    
  template< typename T >
  SortedVector< T >::SortedVector( Container< T > const& container ) :
    Vector< T >( container.GetSize() )
  {
    DFT_FUNC_TRACK( "SortedVector< T >::SortedVector( Container< T > const& container )" );
    PushBackRange( container );
  }

    
  template< typename T >
  SortedVector< T >::~SortedVector()
  {
    DFT_FUNC_TRACK( "SortedVector< T >::~SortedVector()" );
    Clear();
  }

    
  template< typename T >
  SortedVector< T >& SortedVector< T >::operator=( SortedVector< T > const& sortedVector )
  {
    DFT_FUNC_TRACK( "SortedVector< T >& SortedVector< T >::operator=( SortedVector< T > const& sortedVector )" );
    Clear();

    // it's already sorted, so we don't need to worry about finding insertion indices
    m_capacity = sortedVector.m_capacity;
    m_size = sortedVector.m_size;
    m_array = new T[ m_capacity ];
    for( unsigned i = 0; i < m_size; ++i )
    {
      m_array[ i ] = sortedVector.m_array[ i ];
    }

    return *this;
  }

    
  template< typename T >
  SortedVector< T > SortedVector< T >::operator+( SortedVector< T > const& sortedVector ) const
  {
    DFT_FUNC_TRACK( "SortedVector< T > SortedVector< T >::operator+( SortedVector< T > const& sortedVector ) const" );
    SortedVector< T > newSortedVector( *this );
    newSortedVector.PushBackRange( *sortedVector, sortedVector.GetSize() );
    return newSortedVector;
  }

    
  template< typename T >
  SortedVector< T >& SortedVector< T >::operator+=( SortedVector< T > const& sortedVector )
  {
    DFT_FUNC_TRACK( "SortedVector< T >& SortedVector< T >::operator+=( SortedVector< T > const& sortedVector )" );
    PushBackRange( *sortedVector, sortedVector.GetSize() );
    return *this;
  }

    
  template< typename T >
  void SortedVector< T >::PushFront( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedVector< T >::PushFront( T const& t )" );
    bool contains;
    ShiftAndPush( FindInsertionIndex( t, contains ), t );
  }

    
  template< typename T >
  void SortedVector< T >::PushBack( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedVector< T >::PushBack( T const& t )" );
    bool contains;
    ShiftAndPush( FindInsertionIndex( t, contains ), t );
  }

    
  template< typename T >
  void SortedVector< T >::PushBackRange( T const * const tArray, unsigned const size )
  {
    DFT_FUNC_TRACK( "void SortedVector< T >::PushBackRange( T const * const tArray, unsigned const size )" );
    for( unsigned i = 0; i < size; ++i )
      Vector< T >::PushBack( tArray[ i ] );

    QuickSort( m_array, 0, m_size - 1 );
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void SortedVector< T >::PushBackRange( Container< T > const& container )
  {
    DFT_FUNC_TRACK( "void SortedVector< T >::PushBackRange( Container< T > const& container )" );
    for( Container< T >::Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      Vector< T >::PushBack( *itB );

    QuickSort( m_array, 0, m_size - 1 );
    InvalidateAllIteratorImplementations();
  }

  
  template< typename T >
  bool const SortedVector< T >::Search( unsigned& startIndex, T const& t ) const
  {
    DFT_FUNC_TRACK( "bool const SortedVector< T >::Search( unsigned& startIndex, T const& t ) const" );
    bool contains = false;
    unsigned containsIndex = FindInsertionIndex( t, contains );
    if( contains )
      startIndex = containsIndex;
    return contains;
  }


  template< typename T >
  void SortedVector< T >::ShiftAndPush( unsigned pushIndex, T const& t )
  {
    DFT_FUNC_TRACK( "void SortedVector< T >::ShiftAndPush( unsigned const startIndex, T const& t )" );
    CheckAndGrow();    
    
    if( pushIndex != 0 && m_greaterThanFunc( m_array[ pushIndex ], t ) )
    {
      --pushIndex;
    }
    else if ( m_lessThanFunc( m_array[ pushIndex ], t ) )
    {
      // we don't need to worry about stepping out of bounds, because the call to CheckAndGrow
      // will prevent that possibility
      ++pushIndex;
    }

    for( unsigned i = m_size; i > pushIndex; --i )
      m_array[ i ] = m_array[ i - 1 ];

    m_array[ pushIndex ] = t;
    ++m_size;

    InvalidateAllIteratorImplementations();
  }

  
  template< typename T >
  unsigned const SortedVector< T >::FindInsertionIndex( T const& t, bool& contains ) const
  {
    DFT_FUNC_TRACK( "unsigned const SortedVector< T >::FindInsertionIndex( T const& t, bool& contains ) const" );
    contains = false;
    unsigned 
      max = ( m_size == 0 ) ? 0 : m_size - 1,
      min = 0,
      index = GetMidpoint( max, min );

    // since we're already sorted, let's start by checking if we can just
    // by default insert at the end or beginning
    if( m_lessThanFunc( m_array[ max ], t ) )
    {
      index = max;
      return index;
    }
    else if( m_greaterThanFunc( m_array[ min ], t ) )
    {
      index = min;
      return index;
    }

    // iterative binary search
    do
    {
      if( m_greaterThanFunc( m_array[ index ], t ) )
      {
        max = index - 1;
      }
      else if ( m_lessThanFunc( m_array[ index ], t ) )
      {
        min = index + 1;
      }
      else if( m_equalityFunc( m_array[ index ], t ) )
      {
        contains = true;
        return index;
      }
      index = GetMidpoint( max, min );
    } while( max != min );

    if( m_equalityFunc( m_array[ index ], t ) )
    {
      contains = true;
    }
    return index;
  }

  
  template< typename T >
  void SortedVector< T >::QuickSort(  T* const tArray, int left, int rght )
  {
    DFT_FUNC_TRACK( "void SortedVector< T >::QuickSort(  T* const tArray, int left, int rght )" );
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
      if ( i < j )
      {
        temp = tArray[ i ];
        tArray[ i ] = tArray[ j ];
        tArray[ j ] = temp;
        ++i; --j;
      }
      else if( i == j )
      {
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


  template< typename T >
  unsigned const SortedVector< T >::GetMidpoint( unsigned max, unsigned min ) const
  {
    return min + (unsigned)roundf( ( ( (float)max - (float)min ) / 2.0f ) );
  }

}
