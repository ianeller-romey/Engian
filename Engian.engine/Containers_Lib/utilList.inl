
#include <new>


namespace Util
{

  template< typename T >
  List< T >::ListNode::ListNode( ListNode* prev, ListNode* next, T* data ) :
    m_prev( prev ),
    m_next( next ),
    m_data( data )
  {
  }


  template< typename T >
  List< T >::ListNode::~ListNode()
  {
  }


  template< typename T >
  List< T >::ListIteratorImpl::ListIteratorImpl( ListNode* const listNode ) :
    IteratorImpl( true ),
    m_listNode( listNode )
  {
    TRACKTESTCALL( "List< T >::ListIteratorImpl::ListIteratorImpl( ListNode* const listNode )" );
  }


  template< typename T >
  List< T >::ListIteratorImpl::~ListIteratorImpl()
  {
    TRACKTESTCALL( "List< T >::ListIteratorImpl::~ListIteratorImpl()" );
  }


  template< typename T >
  void List< T >::ListIteratorImpl::AdvanceValue()
  {
    TRACKTESTCALL( "void List< T >::ListIteratorImpl::AdvanceValue()" );

    m_listNode = m_listNode->m_next;
  }


  template< typename T >
  T const& List< T >::ListIteratorImpl::GetValue() const
  {
    TRACKTESTCALL( "T const& List< T >::ListIteratorImpl::GetValue() const" );

    return *( m_listNode->m_data );
  }
      

  template< typename T >
  List< T >::List() :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    TRACKTESTCALL( "List< T >::List()" );
  }


  template< typename T >
  List< T >::List( T const * const tArray, unsigned const size ) :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    TRACKTESTCALL( "List< T >::List( T const * const tArray, unsigned const size )" );

    PushBackRange( tArray, size );
  }


  template< typename T >
  List< T >::List( List< T > const& list ) :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    TRACKTESTCALL( "List< T >::List( List< T > const& list )" );

    PushBackRange( list );
  }


  template< typename T >
  List< T >::List( Container< T > const& container ) :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    TRACKTESTCALL( "List< T >::List( Container< T > const& container )" );

    PushBackRange( container );
  }


  template< typename T >
  List< T >& List< T >::operator=( List< T > const& list )
  {
    TRACKTESTCALL( "List< T >& List< T >::operator=( List< T > const& list )" );

    Clear();

    PushBackRange( list );
    return *this;
  }


  template< typename T >
  Container< T >& List< T >::operator=( Container< T > const& container )
  {
    TRACKTESTCALL( "Container< T >& List< T >::operator=( Container< T > const& container )" );

    Clear();

    PushBackRange( container );
    return *this;
  }


  template< typename T >
  List< T >::~List()
  {
    TRACKTESTCALL( "List< T >::~List()" );

    Clear();
    delete m_end;
  }


  template< typename T >
  List< T > List< T >::operator+( List< T > const& list ) const
  {
    TRACKTESTCALL( "List< T > List< T >::operator+( List< T > const& list ) const" );

    List< T > newList( *this );
    newList.PushBackRange( list );
    return newList;
  }


  template< typename T >
  List< T >& List< T >::operator+=( List< T > const& list )
  {
    TRACKTESTCALL( "List< T >& List< T >::operator+=( List< T > const& list )" );

    PushBackRange( list );
    return *this;
  }


  template< typename T >
  void List< T >::PushFront( T const& t )
  {
    TRACKTESTCALL( "void List< T >::PushFront( T const& t )" );

    char* memLoc = new char[ sizeof( ListNode ) + sizeof( T ) ];

    T* newT = new( memLoc + sizeof( ListNode ) ) T( t );
    ListNode* listNode = new( memLoc ) ListNode( m_end, m_front, newT );

    if( m_front != m_end )
      m_front->m_prev = listNode;
    m_front = listNode;
    if( m_back == m_end )
      m_back = m_front;
    ++m_size;
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void List< T >::PushBack( T const& t )
  {
    TRACKTESTCALL( "void List< T >::PushBack( T const& t )" );

    char* memLoc = new char[ sizeof( ListNode ) + sizeof( T ) ];
    
    T* newT = new( memLoc + sizeof( ListNode ) ) T( t );
    ListNode* listNode = new( memLoc ) ListNode( m_back, m_end, newT );

    if( m_back != m_end )
      m_back->m_next = listNode;
    m_back = listNode;
    if( m_front == m_end )
      m_front = m_back;
    ++m_size;
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void List< T >::PopFront()
  {
    TRACKTESTCALL( "void List< T >::PopFront()" );

    if( IsEmpty() )
      return;

    ListNode* temp = m_front;
    Pop( temp );
  }


  template< typename T >
  void List< T >::PopBack()
  {
    TRACKTESTCALL( "void List< T >::PopBack()" );

    if( IsEmpty() )
      return;

    ListNode* temp = m_back;
    Pop( temp );
  }


  template< typename T >
  void List< T >::PopFirst( T const& t )
  {
    TRACKTESTCALL( "void List< T >::PopFirst( T const& t )" );

    if( IsEmpty() )
      return;

    ListNode const* temp = m_front;
    if( Search( &temp, t ) )
      Pop( temp );
  }


  template< typename T >
  void List< T >::PopAll( T const& t )
  {
    TRACKTESTCALL( "void List< T >::PopAll( T const& t )" );

    if( IsEmpty() )
      return;

    ListNode const* temp = m_front;
    while( Search( &temp, t ) )
    {
      // this allows us to save our place in the list, since we know that there won't ever be
      // an equivalent T value behind us
      ListNode const* tempTemp = temp;
      temp = temp->m_next;
      Pop( tempTemp );
    }
  }


  template< typename T >
  bool const List< T >::Contains( T const& t ) const
  {
    TRACKTESTCALL( "bool const List< T >::Contains( T const& t ) const" );

    ListNode const * temp = m_front;
    return Search( &temp, t );
  }

  
  template< typename T >
  bool const List< T >::Search( ListNode const** startIndex, T const& t ) const
  {
    TRACKTESTCALL( "bool const List< T >::Search( ListNode const** startIndex, T const& t ) const" );

    while( ( *startIndex ) != m_end && *( ( *startIndex )->m_data ) != t )
      ( *startIndex ) = ( *startIndex )->m_next;

    return ( *startIndex ) != m_end;
  }


  template< typename T >
  void List< T >::Pop( ListNode const * const listNode )
  {
    TRACKTESTCALL( "void List< T >::Pop( ListNode const * const listNode )" );

    if( listNode->m_prev != m_end )
      listNode->m_prev->m_next = listNode->m_next;
    if( listNode->m_next != m_end )
      listNode->m_next->m_prev = listNode->m_prev;
    if( listNode == m_front )
      m_front = listNode->m_next;
    if( listNode == m_back )
      m_back = listNode->m_prev;

    listNode->m_data->~T();
    delete listNode;
    --m_size;

    if( IsEmpty() )
      m_front = m_back = m_end;

    InvalidateAllIteratorImplementations();
  }

}
