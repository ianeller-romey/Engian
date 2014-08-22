
namespace Util
{

  DEBUG_FUNC_TRACK_CLASS_T_DEF( template< typename T >, Vector< T >::VectorIteratorImpl );


  template< typename T >
  Vector< T >::VectorIteratorImpl::VectorIteratorImpl( T * const tArray ) :
    IteratorImpl( true ),
    m_value( tArray )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::VectorIteratorImpl::VectorIteratorImpl( T * const tArray )" );
  }


  template< typename T >
  Vector< T >::VectorIteratorImpl::VectorIteratorImpl( VectorIteratorImpl const& other ) :
    IteratorImpl( true ),
    m_value( other.m_value )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::VectorIteratorImpl::VectorIteratorImpl( VectorIteratorImpl const& other )" );
  }


  template< typename T >
  Vector< T >::VectorIteratorImpl::~VectorIteratorImpl()
  {
    DEBUG_FUNC_TRACK( "Vector< T >::VectorIteratorImpl::~VectorIteratorImpl()" );
  }


  template< typename T >
  void Vector< T >::VectorIteratorImpl::AdvanceValue()
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::VectorIteratorImpl::AdvanceValue()" );
    m_value += 1;
  }


  template< typename T >
  T const& Vector< T >::VectorIteratorImpl::GetValue() const
  {
    DEBUG_FUNC_TRACK( "T const& Vector< T >::VectorIteratorImpl::GetValue() const" );
    return *m_value;
  }
  

  template< typename T >
  unsigned const  Vector< T >::c_defaultCapacity = 20;
  template< typename T >
  float const Vector< T >::c_growMultiplier = 2.0;

  
  template< typename T >
  Vector< T >::Vector() :
    Container< T >(),
    m_capacity( c_defaultCapacity ),
    m_array( new T[ c_defaultCapacity ] )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::Vector()" );
  }

  
  template< typename T >
  Vector< T >::Vector( unsigned const capacity ) :
    Container< T >(),
    m_capacity( capacity ),
    m_array( new T[ capacity ] )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::Vector( unsigned const capacity )" );
  }

    
  template< typename T >
  Vector< T >::Vector( T const * const tArray, unsigned const size ) :
    Container< T >(),
    m_capacity( size ),
    m_array( new T[ size ] )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::Vector( T const * const tArray, unsigned const size )" );
    PushBackRange( tArray, size );
  }

    
  template< typename T >
  Vector< T >::Vector( Vector< T > const& vector ) :
    Container< T >(),
    m_capacity( vector.m_capacity ),
    m_array( new T[ vector.m_capacity ] )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::Vector( Vector< T > const& vector )" );
    PushBackRange( vector.m_array, vector.m_size );
  }

    
  template< typename T >
  Vector< T >::Vector( Container< T > const& container ) :
    Container< T >(),
    m_capacity( container.GetSize() ),
    m_array( new T[ container.GetSize() ] )
  {
    DEBUG_FUNC_TRACK( "Vector< T >::Vector( Container< T > const& container )" );
    PushBackRange( container );
  }

    
  template< typename T >
  Vector< T >& Vector< T >::operator=( Vector< T > const& vector )
  {
    DEBUG_FUNC_TRACK( "Vector< T >& Vector< T >::operator=( Vector< T > const& vector )" );
    Clear();

    m_capacity = vector.GetCapacity();
    m_array = new T[ m_capacity ];
    PushBackRange( *vector, vector.GetSize() );

    return *this;
  }

    
  template< typename T >
  Container< T >& Vector< T >::operator=( Container< T > const& container )
  {
    DEBUG_FUNC_TRACK( "Container< T >& Vector< T >::operator=( Container< T > const& container )" );
    Clear();

    m_capacity = container.GetSize();
    m_array = new T[ m_capacity ];
    PushBackRange( container );

    return *this;
  }

    
  template< typename T >
  Vector< T >::~Vector()
  {
    DEBUG_FUNC_TRACK( "Vector< T >::~Vector()" );
    Clear();
  }

    
  template< typename T >
  T& Vector< T >::operator[]( int const index ) const
  {
    DEBUG_FUNC_TRACK( "T& Vector< T >::operator[]( int const index ) const" );
    return m_array[ index ];
  }

    
  template< typename T >
  Vector< T > Vector< T >::operator+( Vector< T > const& vector ) const
  {
    DEBUG_FUNC_TRACK( "Vector< T > Vector< T >::operator+( Vector< T > const& vector ) const" );
    Vector< T > newVector( *this );
    newVector.PushBackRange( *vector, vector.GetSize() );
    return newVector;
  }

    
  template< typename T >
  Vector< T >& Vector< T >::operator+=( Vector< T > const& vector )
  {
    DEBUG_FUNC_TRACK( "Vector< T >& Vector< T >::operator+=( Vector< T > const& vector )" );
    PushBackRange( *vector, vector.GetSize() );
    return *this;
  }

    
  template< typename T >
  T const* Vector< T >::operator*() const
  {
    DEBUG_FUNC_TRACK( "T const* Vector< T >::operator*() const" );
    return m_array;
  }

    
  template< typename T >
  void Vector< T >::PushFront( T const& t )
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::PushFront( T const& t )" );
    CheckAndGrow();

    for( unsigned i = m_size; i > 0; --i )
      m_array[ i ] = m_array[ i - 1 ];
    m_array[ 0 ] = t;
    ++m_size;
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void Vector< T >::PushBack( T const& t )
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::PushBack( T const& t )" );
    CheckAndGrow();
    m_array[ m_size++ ] = t;
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void Vector< T >::PopFront()
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::PopFront()" );
    if( IsEmpty() )
      return;

    ShiftAndPop( 0 );
  }

    
  template< typename T >
  void Vector< T >::PopBack()
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::PopBack()" );
    if( IsEmpty() )
      return;
    m_array[ --m_size ].~T();
    InvalidateAllIteratorImplementations();
  }
  

  template< typename T >
  void Vector< T >::PopFirst( T const& t )
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::PopFirst( T const& t )" );
    if( IsEmpty() )
      return;

    unsigned index = 0;
    if( !Search( index, t ) )
      return;

    ShiftAndPop( index );
  }
  

  template< typename T >
  void Vector< T >::PopAll( T const& t )
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::PopAll( T const& t )" );
    if( IsEmpty() )
      return;

    unsigned index = 0;
    while( Search( index, t ) )
      ShiftAndPop( index );
  }
  
    
  template< typename T >
  bool const Vector< T >::Contains( T const& t ) const
  {
    DEBUG_FUNC_TRACK( "bool const Vector< T >::Contains( T const& t ) const" );
    unsigned startIndex = 0;
    return Search( startIndex, t );
  }

    
  template< typename T >
  bool const Vector< T >::IsFull() const
  {
    DEBUG_FUNC_TRACK( "bool const Vector< T >::IsFull() const" );
    return m_size == m_capacity;
  }

    
  template< typename T >
  unsigned const Vector< T >::GetCapacity() const
  {
    DEBUG_FUNC_TRACK( "unsigned const Vector< T >::GetCapacity() const" );
    return m_capacity;
  }
  
      
  template< typename T >
  void Vector< T >::Clear()
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::Clear()" );
    if( m_array != 0 )
    {
      delete[] m_array;
      m_array = 0;
    }
    m_capacity = 0;
    m_size = 0;
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void Vector< T >::CheckAndGrow()
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::CheckAndGrow()" );
    if( m_size == m_capacity )
      Grow();
  }

    
  template< typename T >
  void Vector< T >::Grow()
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::Grow()" );
    unsigned tempCapacity = ( m_capacity != 0 ) ? ( unsigned )( ( float )m_capacity * c_growMultiplier ) : c_defaultCapacity;
    T* tempArray = new T[ tempCapacity ];

    for( unsigned i = 0; i < m_size; ++i )
      tempArray[ i ] = m_array[ i ];

    delete [] m_array;
    m_array = tempArray;
    m_capacity = tempCapacity;
    InvalidateAllIteratorImplementations();
  }

  
  template< typename T >
  bool const Vector< T >::Search( unsigned& startIndex, T const& t ) const
  {
    DEBUG_FUNC_TRACK( "bool const Vector< T >::Search( unsigned& startIndex, T const& t ) const" );
    for( unsigned i = startIndex; i < m_size; ++i )
      if( m_array[ i ] == t )
      {
        startIndex = i;
        return true;
      }
    return false;
  }


  template< typename T >
  void Vector< T >::ShiftAndPop( unsigned const startIndex )
  {
    DEBUG_FUNC_TRACK( "void Vector< T >::ShiftAndPop( unsigned const startIndex )" );
    for( unsigned i = startIndex; i < m_size - 1; ++i )
      m_array[ i ] = m_array[ i + 1 ];
    PopBack();
  }

}
