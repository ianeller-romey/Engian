
#include <cstdlib>
#include <cmath>


namespace Util
{

  template< typename T >
  float const SortedList< T >::c_logBase = 50.0;


  template< typename T >
  SortedList< T >::SortedListNode::SortedListNode( ListNode* prev, 
                                                   ListNode* next, 
                                                   T* data, 
                                                   SortedListNode* nextTier ) :
    ListNode( prev, next, data ),
    m_nextTier( nextTier )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedListNode::SortedListNode( ListNode* prev, ListNode* next, T* data, SortedListNode* nextTier )" );
  }
      

  template< typename T >
  SortedList< T >::SortedList() :
    Container< T >(),
    SortedContainer< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList()" );
  }


  template< typename T >
  SortedList< T >::SortedList( T const * const tArray, unsigned const size ) :
    Container< T >(),
    SortedContainer< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList( T const * const tArray, unsigned const size )" );
    PushBackRange( tArray, size );
  }


  template< typename T >
  SortedList< T >::SortedList( SortedList< T > const& sortedList ) :
    Container< T >(),
    SortedContainer< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList( SortedList< T > const& sortedList )" );
    PushBackRange( sortedList );
  }


  template< typename T >
  SortedList< T >::SortedList( Container< T > const& container ) :
    Container< T >(),
    SortedContainer< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList( Container< T > const& container )" );
    PushBackRange( container );
  }


  template< typename T >
  SortedList< T >& SortedList< T >::operator=( SortedList< T > const& sortedList )
  {
    DFT_FUNC_TRACK( "SortedList< T >& SortedList< T >::operator=( SortedList< T > const& sortedList )" );
    Clear();

    PushBackRange( sortedList );
    return *this;
  }


  template< typename T >
  SortedContainer< T >& SortedList< T >::operator=( SortedContainer< T > const& sortedContainer )
  {
    DFT_FUNC_TRACK( "SortedContainer< T >& SortedList< T >::operator=( SortedContainer< T > const& sortedContainer )" );
    Clear();

    PushBackRange( sortedContainer );
    return *this;
  }


  template< typename T >
  SortedList< T >::~SortedList()
  {
    DFT_FUNC_TRACK( "SortedList< T >::~SortedList()" );
    Clear();
  }


  template< typename T >
  SortedList< T > SortedList< T >::operator+( SortedList< T > const& sortedList ) const
  {
    DFT_FUNC_TRACK( "SortedList< T > SortedList< T >::operator+( SortedList< T > const& sortedList ) const" );
    SortedList< T > newList( *this );
    newList.PushBackRange( sortedList );
    return newList;
  }


  template< typename T >
  SortedList< T >& SortedList< T >::operator+=( SortedList< T > const& sortedList )
  {
    DFT_FUNC_TRACK( "SortedList< T >& SortedList< T >::operator+=( SortedList< T > const& sortedList )" );
    PushBackRange( sortedList );
    return *this;
  }


  template< typename T >
  void SortedList< T >::PushFront( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::PushFront( T const& t )" );
    Push( t );
  }


  template< typename T >
  void SortedList< T >::PushBack( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::PushBack( T const& t )" );
    Push( t );
  }


  template< typename T >
  void SortedList< T >::PopFront()
  {
    DFT_FUNC_TRACK( "void SortedList< T >::PopFront()" );
    if( IsEmpty() )
      return;

    SortedListNode* temp = static_cast< SortedListNode* >( m_front );
    Pop( temp );
  }


  template< typename T >
  void SortedList< T >::PopBack()
  {
    DFT_FUNC_TRACK( "void SortedList< T >::PopBack()" );
    if( IsEmpty() )
      return;

    SortedListNode* temp = static_cast< SortedListNode* >( m_back );
    Pop( temp );
  }


  template< typename T >
  void SortedList< T >::PopFirst( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::PopFirst( T const& t )" );
    if( IsEmpty() )
      return;

    SortedListNode const * temp = static_cast< SortedListNode* >( m_front );
    if( Search( &temp, t ) )
      Pop( temp );
  }


  template< typename T >
  void SortedList< T >::PopAll( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::PopAll( T const& t )" );
    if( IsEmpty() )
      return;
    
    SortedListNode const * temp = static_cast< SortedListNode* >( m_front );
    while( Search( &temp, t ) )
      Pop( temp );
  }


  template< typename T >
  bool const SortedList< T >::Contains( T const& t ) const
  {
    DFT_FUNC_TRACK( "bool const SortedList< T >::Contains( T const& t ) const" );
    if( IsEmpty() )
      return false;
    
    SortedListNode const * temp = static_cast< SortedListNode* >( m_front );
    return Search( &temp, t );
  }  


  template< typename T >
  void SortedList< T >::Clear()
  {
    DFT_FUNC_TRACK( "void SortedList< T >::Clear()" );
    if( IsEmpty() )
      return;

    while( !IsEmpty() )
      PopBack();
    delete m_end;
    m_end = 0;
    m_front = 0;
    m_back = 0;
    m_tiers = 0;
    InvalidateAllIteratorImplementations();
  }    


  template< typename T >
  void SortedList< T >::Push( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::Push( T const& t )" );
    unsigned 
      possibleTiers = m_size / c_logBase,
      currentNodesTiers = 0;
    if( possibleTiers > 0 )
    {
      // randomly calculate how many tiers this node will have
      currentNodesTiers = 0;
      float random = (float)( rand() % 100 );
      while( currentNodesTiers < possibleTiers && ( ( 1.0 / log( ( currentNodesTiers + 1 ) * c_logBase ) ) * 100.0 ) > random )
        ++currentNodesTiers;
    }

    // make sure the front node always has all possible tiers
    if( possibleTiers > m_tiers )
    {
      AddSortedListNodeTierToFront();
      ++m_tiers;
    }

    // allocate space for T and all tiers (including base tier)
    char* memLoc = new char[ sizeof( T ) + ( sizeof( SortedListNode ) * ( currentNodesTiers + 1 ) ) ];

    // allocate new T
    T* newT = new( memLoc ) T( t );

    bool contains;
    SortedListNode *newPrev,
                   *newNext,
                   *node = 0;

    // if we're empty, we know we won't have any tiers, and we know we'll need to set m_front and m_back
    if( IsEmpty() )
    {
      SortedListNode* endNode = static_cast< SortedListNode* >( m_end );
      node = new( memLoc + sizeof( T ) ) SortedListNode( endNode, endNode, newT, endNode );
      m_back = m_front = node;
    }
    // otherwise, we might have tiers
    else
    {
      // allocate new tiers, from bottom to top
      SortedListNode* previousTiersNextTier = static_cast< SortedListNode* >( m_end );
      unsigned i = 0;
      for( ; i <= currentNodesTiers; ++i )
      {
        FindInsertionNodeInTier( m_tiers, i, *newT, contains, &newPrev, &newNext );
        node = new( memLoc + sizeof( T ) + ( sizeof( SortedListNode ) * i ) ) SortedListNode( newPrev, newNext, newT, previousTiersNextTier );
        if( newPrev != m_end )
          newPrev->m_next = node;
        if( newNext != m_end )
          newNext->m_prev = node;
        previousTiersNextTier = node;
      }

      // should we update our back pointer?
      // this way, we can make sure the back pointer always points to the highest tier, too
      if( m_greaterThanFunc( *( node->m_data ), *( m_back->m_data ) ) )
        m_back = node;

      // should we update our front pointer?
      // if so, we might need to add some tiers
      if( m_lessThanFunc( *( node->m_data ), *( m_front->m_data ) ) )
      {
        SortedListNode* tempFront = static_cast< SortedListNode* >( m_front );
        m_front = node;
        if( currentNodesTiers < m_tiers )
        {
          for( unsigned i = currentNodesTiers; i <= m_tiers; ++i )
          {
            AddSortedListNodeTierToFront();
            m_front->m_next = GetBottomTier( tempFront, m_tiers, i + 1 );
          }
        }
      }
    }

    ++m_size;
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void SortedList< T >::AddSortedListNodeTierToFront()
  {
    DFT_FUNC_TRACK( "void SortedList< T >::AddSortedListNodeTierToFront()" );
    SortedListNode *front = static_cast< SortedListNode* >( m_front ),
                   *newTier = new SortedListNode( m_end, m_end, front->m_data, front );
    m_front = newTier;
  }
    

  template< typename T >
  void SortedList< T >::FindInsertionNodeInTier( unsigned const topTierLevel,
                                                 unsigned const tierToInsert,
                                                 T const& t, 
                                                 bool& contains, 
                                                 SortedListNode** prev, 
                                                 SortedListNode** next ) const
  {
    DFT_FUNC_TRACK( "void SortedList< T >::FindInsertionNodeInTier( unsigned const topTierLevel, unsigned const tierToInsert, T const& t, bool& contains, SortedListNode** prev, SortedListNode** next, SortedListNode** nextTier ) const" );
    SortedListNode* pointer = static_cast< SortedListNode* >( m_front );
    int tier = topTierLevel;

    if( pointer->m_next == m_end && tier != tierToInsert )
    {
      pointer = pointer->m_nextTier;
      --tier;
    }

    while( pointer != m_end )
    {
      // if the current node's data is less than the data to be inserted, advance
      if( m_lessThanFunc( *( pointer->m_data ), t ) )
      {
        // if and we're at the end ...
        if( pointer->m_next == m_end )
        {
          // if we're on the tier into which we're inserting, we're done
          if( tier == tierToInsert )
          {
            *prev = pointer;
            *next = static_cast< SortedListNode* >( pointer->m_next );
            return;
          }
          // if we're above the tier into which we're inserting, move down a tier
          else
          {
            pointer = pointer->m_nextTier;
            --tier;
          }
        }
        // if we're not at the end, just move along to the next
        else
        {
          pointer = static_cast< SortedListNode* >( pointer->m_next );
        }
      }
      // if the current node's data is more than the data to be inserted ...
      else if( m_greaterThanFunc( *( pointer->m_data ), t ) )
      {
        // if we're the very first node in the list, we know we don't need to search further, so just get the 
        // tier we need to insert and return
        if( pointer->m_prev == m_end )
        {
          *prev = static_cast< SortedListNode* >( pointer->m_prev );
          *next = GetBottomTier( pointer, tier, tierToInsert );
          return;
        }
        // if we're not the very first node in the list ...
        else
        {
          // if we're above the tier into which we want to insert, go back a node and down a tier
          if( tier > tierToInsert )
          {
            pointer = static_cast< SortedListNode* >( pointer->m_prev )->m_nextTier;
            --tier;
          }
          // if we're at the tier into which we want to insert, we're done
          else
          {
            *prev = static_cast< SortedListNode* >( pointer->m_prev );
            *next = pointer;
            return;
          }
        }
      }
      // if the current node's data is equal to the data to be inserted, return the bottom tier of the current node
      else if( m_equalityFunc( *( pointer->m_data ), t ) )
      {
        contains = true;

        pointer = GetBottomTier( pointer, tier, tierToInsert );
        *prev = static_cast< SortedListNode* >( pointer->m_prev );
        *next = pointer;
        return;
      }
    }

    throw; // TODO: Throw something
  }
  

  template< typename T >
  unsigned const SortedList< T >::GetNumberOfTiers( SortedListNode const * const topTier ) const
  {
    DFT_FUNC_TRACK( "unsigned const SortedList< T >::GetNumberOfTiers( SortedListNode const * const topTier ) const" );
    unsigned number = 0;
    SortedListNode const * node = topTier;
    for( ; node->m_nextTier != m_end; node = node->m_nextTier )
      ++number;
    return number;
  }
  

  template< typename T >
  void SortedList< T >::ClearTiers( SortedListNode const * topTier ) const
  {
    DFT_FUNC_TRACK( "void SortedList< T >::ClearTiers( SortedListNode const * topTier ) const" );
    // the data pointer is the allocation pointer, so deleting that will take care of all the tiers
    // since we allocated everything as one big array
    char* forDelete = (char*)( topTier->m_data );
    while( topTier != m_end )
    {
      if( topTier->m_prev != m_end )
        topTier->m_prev->m_next = topTier->m_next;
      if( topTier->m_next != m_end )
        topTier->m_next->m_prev = topTier->m_prev;

      SortedListNode const * temp = topTier;
      topTier = topTier->m_nextTier;
      temp->~SortedListNode();
    }
    delete forDelete;
  }


  template< typename T >
  bool const SortedList< T >::Search( SortedListNode const** startIndex, T const& t ) const
  {
    DFT_FUNC_TRACK( "bool const SortedList< T >::Search( SortedListNode const** startIndex, T const& t ) const" );
    SortedListNode *prev, *next;
    bool contains = false;
    FindInsertionNodeInTier( m_tiers, 0, t, contains, &prev, &next );
    if( contains )
      *startIndex = next;
    return contains;
  }


  template< typename T >
  void SortedList< T >::Pop( SortedListNode const * const sortedListNode )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::Pop( SortedListNode const * const sortedListNode )" );
    if( sortedListNode == m_front )
    {
      SortedListNode* tempFront = static_cast< SortedListNode* >( m_front );
      m_front = FindNewFront();
      unsigned numberOfTiers = GetNumberOfTiers( static_cast< SortedListNode* >( m_front ) );
      while( numberOfTiers <= m_tiers )
      {
        AddSortedListNodeTierToFront();
        m_front->m_next = GetBottomTier( tempFront, m_tiers, numberOfTiers )->m_next;
        ++numberOfTiers;
      }
    }
    if( sortedListNode == m_back )
      m_back = FindNewBack();
    ClearTiers( sortedListNode );
    --m_size;
    InvalidateAllIteratorImplementations();
  }

  //template class SortedList< int >;
  
}
