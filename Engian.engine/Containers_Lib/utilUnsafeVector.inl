
namespace Util
{

  
  template< typename T >
  UnsafeVector< T >::UnsafeVector() :
    Vector< T >()
  {
    TRACKTESTCALL( "UnsafeVector< T >::UnsafeVector()" );
  }

  
  template< typename T >
  UnsafeVector< T >::UnsafeVector( unsigned const capacity ) :
    Vector< T >( capacity )
  {
    TRACKTESTCALL( "UnsafeVector< T >::UnsafeVector( unsigned const capacity )" );
  }

    
  template< typename T >
  UnsafeVector< T >::UnsafeVector( T const * const tArray, unsigned const size ) :
    Container< T >(),
    Vector< T >( size )
  {
    TRACKTESTCALL( "UnsafeVector< T >::UnsafeVector( T const * const tArray, unsigned const size )" );
    PushBackRange( tArray, size );
  }

    
  template< typename T >
  UnsafeVector< T >::UnsafeVector( UnsafeVector< T > const& uVector ) :
    Container< T >(),
    Vector< T >( uVector.m_capacity )
  {
    TRACKTESTCALL( "UnsafeVector< T >::UnsafeVector( UnsafeVector< T > const& uVector )" );
    PushBackRange( uVector.m_array, uVector.m_size );
  }

    
  template< typename T >
  UnsafeVector< T >::UnsafeVector( Container< T > const& container ) :
    Container< T >(),
    Vector< T >( container.GetSize() )
  {
    TRACKTESTCALL( "UnsafeVector< T >::UnsafeVector( Container< T > const& container )" );
    Vector< T >::PushBackRange( container );
  }

    
  template< typename T >
  UnsafeVector< T >& UnsafeVector< T >::operator=( UnsafeVector< T > const& uVector )
  {
    TRACKTESTCALL( "UnsafeVector< T >& UnsafeVector< T >::operator=( UnsafeVector< T > const& uVector )" );
    Clear();

    m_capacity = uVector.GetCapacity();
    m_size = uVector.GetSize();
    m_array = new T[ m_capacity ];
    memcpy( m_array, *uVector, sizeof( T ) * m_size );

    return *this;
  }

    
  template< typename T >
  Container< T >& UnsafeVector< T >::operator=( Container< T > const& container )
  {
    TRACKTESTCALL( "Container< T >& UnsafeVector< T >::operator=( Container< T > const& container )" );
    Clear();

    m_capacity = container.GetSize();
    m_size = 0;
    m_array = new T[ m_capacity ];
    PushBackRange( container );

    return *this;
  }

    
  template< typename T >
  UnsafeVector< T >::~UnsafeVector()
  {
    TRACKTESTCALL( "UnsafeVector< T >::~UnsafeVector()" );
    Clear();
  }

    
  template< typename T >
  void UnsafeVector< T >::PushFront( T const& t )
  {
    TRACKTESTCALL( "void UnsafeVector< T >::PushFront( T const& t )" );
    CheckAndGrow();
    T* copyTo = m_array + 1;
    memmove( copyTo, m_array, sizeof( T ) * m_size );
    m_array[ 0 ] = t;
    ++m_size;
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void UnsafeVector< T >::PushBackRange( T const * const tArray, unsigned const size )
  {
    TRACKTESTCALL( "void UnsafeVector< T >::PushBackRange( T const * const tArray, unsigned const size )" );
    while( ( m_size + size ) >= m_capacity )
      Grow();
    T* copyTo = m_array + m_size;
    memcpy( copyTo, tArray, sizeof( T ) * size );
    m_size += size;
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void UnsafeVector< T >::PushBackRange( UnsafeVector< T > const& vector )
  {
    TRACKTESTCALL( "void UnsafeVector< T >::PushBackRange( UnsafeVector< T > const& vector )" );
    PushBackRange( *vector, vector.GetSize() );
  }

    
  template< typename T >
  void UnsafeVector< T >::Grow()
  {
    TRACKTESTCALL( "void UnsafeVector< T >::Grow()" );
    unsigned tempCapacity = ( m_capacity != 0 ) ? ( unsigned )( ( float )m_capacity * c_growMultiplier ) : c_defaultCapacity;
    T* tempArray = new T[ tempCapacity ];

    memcpy( tempArray, m_array, sizeof( T ) * m_size );

    delete [] m_array;
    m_array = tempArray;
    m_capacity = tempCapacity;
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void UnsafeVector< T >::ShiftAndPop( unsigned const startIndex )
  {
    TRACKTESTCALL( "void UnsafeVector< T >::ShiftAndPop( unsigned const startIndex )" );
    T* copyLoc = m_array + startIndex + 1;
    memmove( m_array, copyLoc, sizeof( T ) * ( m_size - 1 ) );
    m_array[ --m_size ].~T();
    InvalidateAllIteratorImplementations();
  }

}
