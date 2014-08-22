
namespace Util
{

  DEBUG_FUNC_TRACK_CLASS_T_DEF( template< typename T >, Container< T > );


  DEBUG_FUNC_TRACK_CLASS_T_DEF( template< typename T >, Container< T >::Iterator );


  DEBUG_FUNC_TRACK_CLASS_T_DEF( template< typename T >, Container< T >::IteratorImpl );


  DEBUG_FUNC_TRACK_CLASS_T_DEF( template< typename T >, Container< T >::IteratorImplNode );


  template< typename T >
  char const * const Container< T >::IteratorImpl::c_exception_invalidatedContainer = "Parent container invalidated";


  template< typename T >
  Container< T >::IteratorImpl::IteratorImpl( bool valid ) :
    m_valid( valid )
  {
    DEBUG_FUNC_TRACK( "Container< T >::IteratorImpl::IteratorImpl( bool valid )" );
  }


  template< typename T >
  Container< T >::IteratorImpl::~IteratorImpl()
  {
    DEBUG_FUNC_TRACK( "Container< T >::IteratorImpl::~IteratorImpl()" );
  }


  template< typename T >
  void Container< T >::IteratorImpl::CheckValid() const
  {
    DEBUG_FUNC_TRACK( "void Container< T >::IteratorImpl::CheckValid() const" );

    if( !m_valid )
      throw c_exception_invalidatedContainer;
  }


  template< typename T >
  T const& Container< T >::IteratorImpl::Get()
  {
    DEBUG_FUNC_TRACK( "T const& Container< T >::IteratorImpl::Get()" );

    if( !m_valid )
      throw c_exception_invalidatedContainer;

    return GetValue();
  }


  template< typename T >
  void Container< T >::IteratorImpl::Invalidate()
  {
    DEBUG_FUNC_TRACK( "void Container< T >::IteratorImpl::Invalidate()" );

    m_valid = false;
  }


  template< typename T >
  Container< T >::IteratorImplNode::IteratorImplNode( IteratorImpl* implementation, IteratorImplNode* next ) :
    m_implementation( implementation ),
    m_next( next )
  {
    DEBUG_FUNC_TRACK( "Container< T >::IteratorImplNode::IteratorImplNode( IteratorImpl* implementation, IteratorImplNode* next )" );
  }

  template< typename T >
  Container< T >::Iterator::Iterator( Iterator const& iterator ) :
    m_implementation( iterator.m_implementation->Clone() ),
    m_parentsIterators( iterator.m_parentsIterators )
  {
    DEBUG_FUNC_TRACK( "Container< T >::Iterator::Iterator( Iterator const& iterator )" );

    IteratorImplNode* itImplNode = new IteratorImplNode( m_implementation, *m_parentsIterators );
    *m_parentsIterators = itImplNode;
  }
  
  
  template< typename T >
  Container< T >::Iterator::~Iterator()
  {
    DEBUG_FUNC_TRACK( "Container< T >::Iterator::~Iterator()" );

    RemoveFromParentList();
  }


  template< typename T >
  bool Container< T >::Iterator::operator==( Iterator const& iterator ) const
  {
    DEBUG_FUNC_TRACK( "bool Container< T >::Iterator::operator==( Iterator const& iterator ) const" );

    return ( *m_implementation ) == *( iterator.m_implementation );
  }
  
  
  template< typename T >
  bool Container< T >::Iterator::operator!=( Iterator const& iterator ) const
  {
    DEBUG_FUNC_TRACK( "bool Container< T >::Iterator::operator!=( Iterator const& iterator ) const" );

    return ( *m_implementation ) != *( iterator.m_implementation );
  }


  template< typename T >
  T const& Container< T >::Iterator::operator*() const
  {
    DEBUG_FUNC_TRACK( "T const& Container< T >::Iterator::operator*() const" );

    return m_implementation->Get();
  }
  

  template< typename T >
  T const& Container< T >::Iterator::Get() const
  {
    DEBUG_FUNC_TRACK( "T const& Container< T >::Iterator::Get() const" );

    return m_implementation->Get();
  }


  template< typename T >
  Container< T >::Iterator::Iterator( IteratorImpl* implementation, IteratorImplNode** parentList ) :
    m_implementation( implementation ),
    m_parentsIterators( parentList )
  {
    DEBUG_FUNC_TRACK( "Container< T >::Iterator::Iterator( IteratorImpl* implementation, IteratorImplNode** parentList )" );
  }
  
  template< typename T >
  void Container< T >::Iterator::CheckValid()
  {
    DEBUG_FUNC_TRACK( "void Container< T >::Iterator::CheckValid()" );

    m_implementation->CheckValid();
  }

  
  template< typename T >
  void Container< T >::Iterator::RemoveFromParentList()
  {
    DEBUG_FUNC_TRACK( "void Container< T >::Iterator::RemoveFromParentList()" );

    IteratorImplNode* node = *m_parentsIterators;
    // if we're the very first node
    if( node->m_implementation == m_implementation )
    {
      *m_parentsIterators = node->m_next;

      delete node->m_implementation;
      delete node;
    }
    else
    {
      // no error checking during search; 
      // we're going to assume that we're in this list no matter what
      while( node->m_next->m_implementation != m_implementation )
        node = node->m_next;

      IteratorImplNode* temp = node->m_next;
      node->m_next = node->m_next->m_next;

      delete temp->m_implementation;
      delete temp;
    }
  }
    

  template< typename T >
  Container< T >::Container() :
    m_size( 0 ),
    m_implementations( 0 )
  {
    DEBUG_FUNC_TRACK( "Container< T >::Container()" );
  }
    

  template< typename T >
  Container< T >::~Container()
  {
    DEBUG_FUNC_TRACK( "Container< T >::~Container()" );

    Clear();
  }
    

  template< typename T >
  Container< T >& Container< T >::operator=( Container< T > const& container )
  {
    DEBUG_FUNC_TRACK( "Container< T >& Container< T >::operator=( Container< T > const& container )" );

    Clear();
    PushBackRange( container );
    return *this;
  }
    

  template< typename T >
  bool const Container< T >::operator==( Container< T > const& container ) const
  {
    DEBUG_FUNC_TRACK( "bool const Container< T >::operator==( Container< T > const& container ) const" );

    if( m_size != container.GetSize() )
      return false;

    Iterator itB1 = Begin(), 
             itB2 = container.Begin(), 
             itE1 = End(), 
             itE2 = container.End();
    for( ; itB1 != itE1 && itB2 != itE2; ++itB1, ++itB2 )
      if( itB1.Get() != itB2.Get() )
        return false;

    if( itB1 != itE1 || itB2 != itE2 )
      return false;

    return true;
  }
    

  template< typename T >
  bool const Container< T >::operator!=( Container< T > const& container ) const
  {
    DEBUG_FUNC_TRACK( "bool const Container< T >::operator!=( Container< T > const& container ) const" );

    return !( ( *this ) == container );
  }
    

  template< typename T >
  Container< T >& Container< T >::operator+=( Container< T > const& container )
  {
    DEBUG_FUNC_TRACK( "Container< T >& Container< T >::operator+=( Container< T > const& container )" );

    Iterator itB = container.Begin(),
             itE = container.End();
    for( ; itB != itE; ++itB )
      PushBack( itB.Get() );

    return *this;
  }

    
  template< typename T >
  void Container< T >::PushBackRange( T const * const tArray, unsigned const size )
  {
    DEBUG_FUNC_TRACK( "void Container< T >::PushBackRange( T const * const tArray, unsigned const size )" );

    for( unsigned i = 0; i < size; ++i )
      PushBack( tArray[ i ] );
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void Container< T >::PushBackRange( Container< T > const& container )
  {
    DEBUG_FUNC_TRACK( "void Container< T >::PushBackRange( Container< T > const& container )" );

    for( Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      PushBack( *itB );
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  bool const Container< T >::Contains( T const& t ) const
  {
    DEBUG_FUNC_TRACK( "bool const Container< T >::Contains( T const& t ) const" );

    for( Iterator itB = Begin(), itE = End(); itB != itE; ++itB )
      if( ( *itB ) == t )
        return true;
    return false;
  }

    
  template< typename T >
  bool const Container< T >::IsEmpty() const
  {
    DEBUG_FUNC_TRACK( "bool const Container< T >::IsEmpty() const" );

    return m_size == 0;
  }

    
  template< typename T >
  unsigned const Container< T >::GetSize() const
  {
    DEBUG_FUNC_TRACK( "unsigned const Container< T >::GetSize() const" );

    return m_size;
  }

    
  template< typename T >
  void Container< T >::Clear()
  {
    DEBUG_FUNC_TRACK( "void Container< T >::Clear()" );

    while( !IsEmpty() )
      PopBack();
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void Container< T >::InvalidateAllIteratorImplementations()
  {    
    DEBUG_FUNC_TRACK( "void Container< T >::InvalidateAllIteratorImplementations()" );

    for( IteratorImplNode* node = m_implementations; node != 0; node = node->m_next )
      node->m_implementation->Invalidate();
  }

}
