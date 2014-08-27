
#include <new>


namespace Util
{

#ifdef USE_DFT_LIB
  template< typename T >
  Debug::FunctionTracker List< T >::ListNode::s_functionTracker;
  template< typename T >
  Debug::FunctionTracker List< T >::ListIteratorImpl::s_functionTracker;
#endif


  template< typename T >
  List< T >::ListNode::ListNode( ListNode* prev, ListNode* next, T* data ) :
    m_prev( prev ),
    m_next( next ),
    m_data( data )
  {
    DFT_FUNC_TRACK( "List< T >::ListNode::ListNode( ListNode* prev, ListNode* next, T* data )" );
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
    DFT_FUNC_TRACK( "List< T >::ListIteratorImpl::ListIteratorImpl( ListNode* const listNode )" );
  }


  template< typename T >
  List< T >::ListIteratorImpl::ListIteratorImpl( ListIteratorImpl const& other ) :
    IteratorImpl( true ),
    m_listNode( other.m_listNode )
  {
    DFT_FUNC_TRACK( "List< T >::ListIteratorImpl::ListIteratorImpl( ListIteratorImpl const& other )" );
  }


  template< typename T >
  List< T >::ListIteratorImpl::~ListIteratorImpl()
  {
    DFT_FUNC_TRACK( "List< T >::ListIteratorImpl::~ListIteratorImpl()" );
  }


  template< typename T >
  void List< T >::ListIteratorImpl::AdvanceValue()
  {
    DFT_FUNC_TRACK( "void List< T >::ListIteratorImpl::AdvanceValue()" );

    m_listNode = m_listNode->m_next;
  }


  template< typename T >
  T const& List< T >::ListIteratorImpl::GetValue() const
  {
    DFT_FUNC_TRACK( "T const& List< T >::ListIteratorImpl::GetValue() const" );

    return *( m_listNode->m_data );
  }
      

  template< typename T >
  List< T >::List() :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    DFT_FUNC_TRACK( "List< T >::List()" );
  }


  template< typename T >
  List< T >::List( T const * const tArray, unsigned const size ) :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    DFT_FUNC_TRACK( "List< T >::List( T const * const tArray, unsigned const size )" );

    PushBackRange( tArray, size );
  }


  template< typename T >
  List< T >::List( List< T > const& list ) :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    DFT_FUNC_TRACK( "List< T >::List( List< T > const& list )" );

    PushBackRange( list );
  }


  template< typename T >
  List< T >::List( Container< T > const& container ) :
    Container< T >(),
    m_end( new ListNode( 0, 0, 0 ) ), 
    m_front( m_end ),
    m_back( m_end )
  {
    DFT_FUNC_TRACK( "List< T >::List( Container< T > const& container )" );

    PushBackRange( container );
  }


  template< typename T >
  List< T >& List< T >::operator=( List< T > const& list )
  {
    DFT_FUNC_TRACK( "List< T >& List< T >::operator=( List< T > const& list )" );

    Clear();

    PushBackRange( list );
    return *this;
  }


  template< typename T >
  Container< T >& List< T >::operator=( Container< T > const& container )
  {
    DFT_FUNC_TRACK( "Container< T >& List< T >::operator=( Container< T > const& container )" );

    Clear();

    PushBackRange( container );
    return *this;
  }


  template< typename T >
  List< T >::~List()
  {
    DFT_FUNC_TRACK( "List< T >::~List()" );

    Clear();
    delete m_end;
  }


  template< typename T >
  List< T > List< T >::operator+( List< T > const& list ) const
  {
    DFT_FUNC_TRACK( "List< T > List< T >::operator+( List< T > const& list ) const" );

    List< T > newList( *this );
    newList.PushBackRange( list );
    return newList;
  }


  template< typename T >
  List< T >& List< T >::operator+=( List< T > const& list )
  {
    DFT_FUNC_TRACK( "List< T >& List< T >::operator+=( List< T > const& list )" );
      
    PushBackRange( list );
    return *this;
  }


  template< typename T >
  void List< T >::PushFront( T const& t )
  {
    DFT_FUNC_TRACK( "void List< T >::PushFront( T const& t )" );

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
    DFT_FUNC_TRACK( "void List< T >::PushBack( T const& t )" );

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
    DFT_FUNC_TRACK( "void List< T >::PopFront()" );

    if( IsEmpty() )
      return;

    ListNode* temp = m_front;
    Pop( temp );
  }


  template< typename T >
  void List< T >::PopBack()
  {
    DFT_FUNC_TRACK( "void List< T >::PopBack()" );

    if( IsEmpty() )
      return;

    ListNode* temp = m_back;
    Pop( temp );
  }


  template< typename T >
  void List< T >::PopFirst( T const& t )
  {
    DFT_FUNC_TRACK( "void List< T >::PopFirst( T const& t )" );

    if( IsEmpty() )
      return;

    ListNode const* temp = m_front;
    if( Search( &temp, t ) )
      Pop( temp );
  }


  template< typename T >
  void List< T >::PopAll( T const& t )
  {
    DFT_FUNC_TRACK( "void List< T >::PopAll( T const& t )" );

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
    DFT_FUNC_TRACK( "bool const List< T >::Contains( T const& t ) const" );

    ListNode const * temp = m_front;
    return Search( &temp, t );
  }

  
  template< typename T >
  bool const List< T >::Search( ListNode const** startIndex, T const& t ) const
  {
    DFT_FUNC_TRACK( "bool const List< T >::Search( ListNode const** startIndex, T const& t ) const" );

    while( ( *startIndex ) != m_end && *( ( *startIndex )->m_data ) != t )
      ( *startIndex ) = ( *startIndex )->m_next;

    return ( *startIndex ) != m_end;
  }


  template< typename T >
  void List< T >::Pop( ListNode const * const listNode )
  {
    DFT_FUNC_TRACK( "void List< T >::Pop( ListNode const * const listNode )" );

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
