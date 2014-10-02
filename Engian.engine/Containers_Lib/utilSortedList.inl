
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
    Sorter< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 ),
    m_head( new SortedListNode( m_end, m_end, 0, static_cast< SortedListNode* >( m_end ) ) )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList()" );
  }


  template< typename T >
  SortedList< T >::SortedList( T const * const tArray, unsigned const size ) :
    Sorter< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 ),
    m_head( new SortedListNode( m_end, m_end, 0, static_cast< SortedListNode* >( m_end ) ) )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList( T const * const tArray, unsigned const size )" );
    PushBackRange( tArray, size );
  }


  template< typename T >
  SortedList< T >::SortedList( SortedList< T > const& sortedList ) :
    Sorter< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 ),
    m_head( new SortedListNode( m_end, m_end, 0, static_cast< SortedListNode* >( m_end ) ) )
  {
    DFT_FUNC_TRACK( "SortedList< T >::SortedList( SortedList< T > const& sortedList )" );
    PushBackRange( sortedList );
  }


  template< typename T >
  SortedList< T >::SortedList( Container< T > const& container ) :
    Sorter< T >(),
    List< T >( new SortedListNode( 0, 0, 0, 0 ) ),
    m_tiers( 0 ),
    m_head( new SortedListNode( m_end, m_end, 0, static_cast< SortedListNode* >( m_end ) ) )
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
  SortedList< T >::~SortedList()
  {
    DFT_FUNC_TRACK( "SortedList< T >::~SortedList()" );
    Deallocate();
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

    // TODO: Use known number of tiers here to see if we only need to walk back one node to find the new back
    SortedListNode* temp = static_cast< SortedListNode* >( m_back );
    unsigned tiers = 0;
    for( SortedListNode* temp2 = temp; temp2 != m_end; temp2 = temp2->m_nextTier )
    {
      ++tiers;
    }
    Pop( temp );
    m_back = FindNewBack();
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
  void SortedList< T >::Push( T const& t )
  {
    DFT_FUNC_TRACK( "void SortedList< T >::Push( T const& t )" );

    ////////
    // if we're empty, 
    // we know we won't have any tiers, and we know we'll need to set m_front and m_back
    if( IsEmpty() )
    {
      SortedListNode* endNode = static_cast< SortedListNode* >( m_end );

      char* memLoc = new char[ sizeof( T ) + sizeof( SortedListNode ) ];
      T* newT = new( memLoc ) T( t );

      SortedListNode* node = new( memLoc + sizeof( T ) ) SortedListNode( m_head, endNode, newT, endNode );
      m_back = m_front = node;
      m_head->m_next = m_front;
    }
    ////////
    // otherwise, we might have tiers,
    // which is way more complicated
    else
    {
      ////////
      // calculate number of tiers
      unsigned currentNodesTiers = CalculateRandomNumberOfTiers(),
               startSearchTiers = m_tiers;

      ////////
      // allocate space
      char* memLoc = new char[ sizeof( T ) + ( sizeof( SortedListNode ) * ( currentNodesTiers + 1 ) ) ];
      T* newT = new( memLoc ) T( t );

      SortedListNode *previouslyInsertedTier = static_cast< SortedListNode* >( m_end ),
                     *node,
                     *startSearchNode = static_cast< SortedListNode* >( m_head->m_next );
      // ^ we're saving the startSearchNode now, in case we update m_head->m_next with a new node that doesn't have m_nextTier set yet

      ////////
      // make sure the head node always has all possible tiers
      {
        for( ; currentNodesTiers > startSearchTiers; --currentNodesTiers )
        {
          AddTierToHead();
          // TODO:
          // From here ...
          node = new( memLoc + sizeof( T ) + ( sizeof( SortedListNode ) * currentNodesTiers ) ) SortedListNode( m_head, 
                                                                                                                m_head->m_next, 
                                                                                                                newT, 
                                                                                                                static_cast< SortedListNode* >( m_end ) );
          m_head->m_next = node;
          if( previouslyInsertedTier != m_end )
            previouslyInsertedTier->m_nextTier = node;
          previouslyInsertedTier = node;
          // ... to here uses a lot of the same functionality as the insertions that happen below,
          // and this couple probably be separated in to an isolated function

          ++m_tiers;
        }
      }
      
      ////////
      // insert nodes that aren't part of the new tier(s),
      // from the top to the bottom
      {
        SortedListNode *newPrev,
                       *newNext;
        bool contains;
        ////////
        // first, insert all but the bottom tier, keeping track of the last place we inserted,
        // so that we don't have to start from the beginning when inserting into every tier
        for( ; currentNodesTiers > 0; )
        {
          FindInsertionNodeInTier( startSearchNode, startSearchTiers, currentNodesTiers, *newT, contains, &newPrev, &newNext );
          node = new( memLoc + sizeof( T ) + ( sizeof( SortedListNode ) * currentNodesTiers ) ) SortedListNode( newPrev, 
                                                                                                                newNext, 
                                                                                                                newT, 
                                                                                                                static_cast< SortedListNode* >( m_end ) );
          // newPrev should never equal m_end, so there's no need to check
          newPrev->m_next = node;
          if( newNext != m_end )
            newNext->m_prev = node;
          if( previouslyInsertedTier != m_end )
            previouslyInsertedTier->m_nextTier = node;

          ////////
          // for next loop
          previouslyInsertedTier = node;
          // don't bother starting the next tier's search on this tier; automatically go down one
          // we can't just do = node->m_nextTier, because m_nextTier hasn't been assigned yet!
          startSearchNode = static_cast< SortedListNode* >( static_cast< SortedListNode* >( node->m_prev )->m_nextTier );
          if( startSearchNode->m_next != m_end )
            startSearchNode = static_cast< SortedListNode* >( startSearchNode->m_next );

          --currentNodesTiers;
          startSearchTiers = currentNodesTiers;
        }
        ////////
        // On the very bottom tier, we don't need to set perviouslyInsertedTier or startSearchNode equal to
        // anything new, since the loop is done
        {
          FindInsertionNodeInTier( startSearchNode, startSearchTiers, currentNodesTiers, *newT, contains, &newPrev, &newNext );
          node = new( memLoc + sizeof( T ) ) SortedListNode( newPrev, 
                                                             newNext, 
                                                             newT, 
                                                             static_cast< SortedListNode* >( m_end ) );
          // newPrev should never equal m_end, so there's no need to check
          newPrev->m_next = node;
          if( newNext != m_end )
            newNext->m_prev = node;
          if( previouslyInsertedTier != m_end )
            previouslyInsertedTier->m_nextTier = node;
        }
      }

      // should we update our back pointer?
      // this way, we can make sure the back pointer always points to the highest tier, too
      if( m_greaterThanFunc( *( node->m_data ), *( m_back->m_data ) ) )
        m_back = node;
      // should we update our front pointer?
      else if( m_lessThanFunc( *( node->m_data ), *( m_front->m_data ) ) ||
               m_equalityFunc( *( node->m_data ), *( m_front->m_data ) ) )
        m_front = node;
    }

    ++m_size;
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void SortedList< T >::AddTierToHead()
  {
    DFT_FUNC_TRACK( "void SortedList< T >::AddTierToHead()" );
    SortedListNode *newTier = new SortedListNode( m_end, m_end, 0, m_head );
    m_head = newTier;
  }


  template< typename T >
  unsigned const SortedList< T >::CalculateRandomNumberOfTiers() const
  {
    DFT_FUNC_TRACK( "unsigned const SortedList< T >::CalculateRandomNumberOfTiers() const" );
    unsigned 
      possibleTiers = m_size / c_logBase,
      calculatedTiers = 0;
    if( possibleTiers > 0 )
    {
      // randomly calculate how many tiers this node will have
      // TODO: More efficient algo
      float random = (float)( rand() % 100 );
      while( calculatedTiers < possibleTiers && ( ( 1.0 / log( ( calculatedTiers + 1 ) * c_logBase ) ) * 100.0 ) > random )
        ++calculatedTiers;
    }
    return calculatedTiers;
  }
    

  template< typename T >
  void SortedList< T >::FindInsertionNodeInTier( SortedListNode* startTier,
                                                 unsigned const startTierNumber,
                                                 unsigned const tierToInsert,
                                                 T const& t, 
                                                 bool& contains, 
                                                 SortedListNode** prev, 
                                                 SortedListNode** next ) const
  {
    DFT_FUNC_TRACK( "void SortedList< T >::FindInsertionNodeInTier( SortedListNode* startTier, unsigned const startTierNumber, T const& t, bool& contains, SortedListNode** prev, SortedListNode** next, SortedListNode** nextTier ) const" );
    SortedListNode* pointer = startTier;
    int tier = startTierNumber;

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
        if( pointer->m_prev->m_prev == m_end )
        {
          pointer = GetBottomTier( pointer, tier, tierToInsert );

          // go back on the current tier until we find our insert location
          while( pointer->m_prev->m_prev != m_end && m_greaterThanFunc( *( pointer->m_prev->m_data ), t ) )
            pointer = static_cast< SortedListNode* >( pointer->m_prev );

          *prev = static_cast< SortedListNode* >( pointer->m_prev );
          *next = pointer;
          return;
        }
        // if we're not the very first node in the list ...
        else
        {
          // if we're at the tier into which we want to insert, we're done
          if( tier == tierToInsert )
          {
            // go back on the current tier until we find our insert location
            while( pointer->m_prev->m_prev != m_end && m_greaterThanFunc( *( pointer->m_prev->m_data ), t ) )
              pointer = static_cast< SortedListNode* >( pointer->m_prev );
            *prev = static_cast< SortedListNode* >( pointer->m_prev );
            *next = pointer;
            return;
          }
          // if we're above the tier into which we want to insert, go back a node and down a tier
          else
          {
            pointer = static_cast< SortedListNode* >( static_cast< SortedListNode* >( pointer->m_prev )->m_nextTier->m_next );
            --tier;
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
  void SortedList< T >::Deallocate()
  {
    DFT_FUNC_TRACK( "void SortedList< T >::Deallocate()" );
    Clear();
    while( m_head != m_end )
    {
      SortedListNode* tempHead = m_head;
      m_head = m_head->m_nextTier;
      delete tempHead;
    }      
    delete m_end;
    m_front = m_back = m_end = 0;
    m_tiers = 0;
  }


  template< typename T >
  bool const SortedList< T >::Search( SortedListNode const** startIndex, T const& t ) const
  {
    DFT_FUNC_TRACK( "bool const SortedList< T >::Search( SortedListNode const** startIndex, T const& t ) const" );
    SortedListNode *prev, *next;
    bool contains = false;
    FindInsertionNodeInTier( static_cast< SortedListNode* >( m_head->m_next ), m_tiers, 0, t, contains, &prev, &next );
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
      // we don't need to update where m_head is pointing, since ClearTiers() will take care of that
      //for( SortedListNode* tempFront = m_front; tempFront != m_end; tempFront = tempFront->m_next )
      //  tempFront->m_prev->m_next = tempFront->m_next;
      m_front = FindNewFront();
    }
    if( sortedListNode == m_back )
      m_back = FindNewBack();
    ClearTiers( sortedListNode );
    --m_size;
    InvalidateAllIteratorImplementations();
  }

}
