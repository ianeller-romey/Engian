
namespace Util
{

#ifdef USE_DFT_LIB
  template< typename T >
  DebugForTest::FunctionTracker Container< T >::s_functionTracker;
  template< typename T >
  DebugForTest::FunctionTracker Container< T >::Iterator::s_functionTracker;
  template< typename T >
  DebugForTest::FunctionTracker Container< T >::IteratorImpl::s_functionTracker;
  template< typename T >
  DebugForTest::FunctionTracker Container< T >::IteratorImplNode::s_functionTracker;
#endif


  template< typename T >
  char const * const Container< T >::IteratorImpl::c_exception_invalidatedContainer = "Parent container invalidated";


  template< typename T >
  Container< T >::IteratorImpl::IteratorImpl( bool valid ) :
    m_valid( valid )
  {
    DFT_FUNC_TRACK( "Container< T >::IteratorImpl::IteratorImpl( bool valid )" );
  }


  template< typename T >
  Container< T >::IteratorImpl::~IteratorImpl()
  {
    DFT_FUNC_TRACK( "Container< T >::IteratorImpl::~IteratorImpl()" );
  }


  template< typename T >
  void Container< T >::IteratorImpl::CheckValid() const
  {
    DFT_FUNC_TRACK( "void Container< T >::IteratorImpl::CheckValid() const" );

    if( !m_valid )
      throw c_exception_invalidatedContainer;
  }


  template< typename T >
  T const& Container< T >::IteratorImpl::Get()
  {
    DFT_FUNC_TRACK( "T const& Container< T >::IteratorImpl::Get()" );

    if( !m_valid )
      throw c_exception_invalidatedContainer;

    return GetValue();
  }


  template< typename T >
  void Container< T >::IteratorImpl::Invalidate()
  {
    DFT_FUNC_TRACK( "void Container< T >::IteratorImpl::Invalidate()" );

    m_valid = false;
  }


  template< typename T >
  Container< T >::IteratorImplNode::IteratorImplNode( IteratorImpl* implementation, IteratorImplNode* next ) :
    m_implementation( implementation ),
    m_next( next )
  {
    DFT_FUNC_TRACK( "Container< T >::IteratorImplNode::IteratorImplNode( IteratorImpl* implementation, IteratorImplNode* next )" );
  }

  template< typename T >
  Container< T >::Iterator::Iterator( Iterator const& iterator ) :
    m_implementation( iterator.m_implementation->Clone() ),
    m_parentsIterators( iterator.m_parentsIterators )
  {
    DFT_FUNC_TRACK( "Container< T >::Iterator::Iterator( Iterator const& iterator )" );

    IteratorImplNode* itImplNode = new IteratorImplNode( m_implementation, *m_parentsIterators );
    *m_parentsIterators = itImplNode;
  }
  
  
  template< typename T >
  Container< T >::Iterator::~Iterator()
  {
    DFT_FUNC_TRACK( "Container< T >::Iterator::~Iterator()" );

    RemoveFromParentList();
  }


  template< typename T >
  bool Container< T >::Iterator::operator==( Iterator const& iterator ) const
  {
    DFT_FUNC_TRACK( "bool Container< T >::Iterator::operator==( Iterator const& iterator ) const" );

    return ( *m_implementation ) == *( iterator.m_implementation );
  }
  
  
  template< typename T >
  bool Container< T >::Iterator::operator!=( Iterator const& iterator ) const
  {
    DFT_FUNC_TRACK( "bool Container< T >::Iterator::operator!=( Iterator const& iterator ) const" );

    return ( *m_implementation ) != *( iterator.m_implementation );
  }


  template< typename T >
  T const& Container< T >::Iterator::operator*() const
  {
    DFT_FUNC_TRACK( "T const& Container< T >::Iterator::operator*() const" );

    return m_implementation->Get();
  }
  

  template< typename T >
  T const& Container< T >::Iterator::Get() const
  {
    DFT_FUNC_TRACK( "T const& Container< T >::Iterator::Get() const" );

    return m_implementation->Get();
  }


  template< typename T >
  Container< T >::Iterator::Iterator( IteratorImpl* implementation, IteratorImplNode** parentList ) :
    m_implementation( implementation ),
    m_parentsIterators( parentList )
  {
    DFT_FUNC_TRACK( "Container< T >::Iterator::Iterator( IteratorImpl* implementation, IteratorImplNode** parentList )" );
  }
  
  template< typename T >
  void Container< T >::Iterator::CheckValid()
  {
    DFT_FUNC_TRACK( "void Container< T >::Iterator::CheckValid()" );

    m_implementation->CheckValid();
  }

  
  template< typename T >
  void Container< T >::Iterator::RemoveFromParentList()
  {
    DFT_FUNC_TRACK( "void Container< T >::Iterator::RemoveFromParentList()" );

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
    DFT_FUNC_TRACK( "Container< T >::Container()" );
  }
    

  template< typename T >
  Container< T >::~Container()
  {
    DFT_FUNC_TRACK( "Container< T >::~Container()" );

    Clear();
  }
    

  template< typename T >
  Container< T >& Container< T >::operator=( Container< T > const& container )
  {
    DFT_FUNC_TRACK( "Container< T >& Container< T >::operator=( Container< T > const& container )" );

    Clear();
    PushBackRange( container );
    return *this;
  }
    

  template< typename T >
  bool const Container< T >::operator==( Container< T > const& container ) const
  {
    DFT_FUNC_TRACK( "bool const Container< T >::operator==( Container< T > const& container ) const" );

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
    DFT_FUNC_TRACK( "bool const Container< T >::operator!=( Container< T > const& container ) const" );

    return !( ( *this ) == container );
  }
    

  template< typename T >
  Container< T >& Container< T >::operator+=( Container< T > const& container )
  {
    DFT_FUNC_TRACK( "Container< T >& Container< T >::operator+=( Container< T > const& container )" );

    Iterator itB = container.Begin(),
             itE = container.End();
    for( ; itB != itE; ++itB )
      PushBack( itB.Get() );

    return *this;
  }

    
  template< typename T >
  void Container< T >::PushBackRange( T const * const tArray, unsigned const size )
  {
    DFT_FUNC_TRACK( "void Container< T >::PushBackRange( T const * const tArray, unsigned const size )" );

    for( unsigned i = 0; i < size; ++i )
      PushBack( tArray[ i ] );
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  void Container< T >::PushBackRange( Container< T > const& container )
  {
    DFT_FUNC_TRACK( "void Container< T >::PushBackRange( Container< T > const& container )" );

    for( Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      PushBack( *itB );
    InvalidateAllIteratorImplementations();
  }

    
  template< typename T >
  bool const Container< T >::Contains( T const& t ) const
  {
    DFT_FUNC_TRACK( "bool const Container< T >::Contains( T const& t ) const" );

    for( Iterator itB = Begin(), itE = End(); itB != itE; ++itB )
      if( ( *itB ) == t )
        return true;
    return false;
  }

    
  template< typename T >
  bool const Container< T >::IsEmpty() const
  {
    DFT_FUNC_TRACK( "bool const Container< T >::IsEmpty() const" );

    return m_size == 0;
  }

    
  template< typename T >
  unsigned const Container< T >::GetSize() const
  {
    DFT_FUNC_TRACK( "unsigned const Container< T >::GetSize() const" );

    return m_size;
  }

    
  template< typename T >
  void Container< T >::Clear()
  {
    DFT_FUNC_TRACK( "void Container< T >::Clear()" );

    while( !IsEmpty() )
      PopBack();
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void Container< T >::InvalidateAllIteratorImplementations()
  {    
    DFT_FUNC_TRACK( "void Container< T >::InvalidateAllIteratorImplementations()" );

    for( IteratorImplNode* node = m_implementations; node != 0; node = node->m_next )
      node->m_implementation->Invalidate();
  }

}
