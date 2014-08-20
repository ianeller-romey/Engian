
#include <cstdlib>
#include <cmath>


namespace Util
{

  template< typename T >
  float const SortedList< T >::c_logBase = 50.0;


  template< typename T >
  SortedList< T >::SortedListNode::SortedListNode(  ListNode* prev, 
                            ListNode* next, 
                            T* data, 
                            SortedListNode* nextTier ) :
    ListNode( prev, next, data ),
    m_nextTier( nextTier )
  {
  }
      

  template< typename T >
  SortedList< T >::SortedList() :
    m_tiers( 0 ),
    List< T >(),
    SortedContainer< T >()
  {
  }


  template< typename T >
  SortedList< T >::SortedList( T const * const tArray, unsigned const size ) :
    m_tiers( 0 ),
    List< T >(),
    SortedContainer< T >(),
  {
    PushBackRange( tArray, size );
  }


  template< typename T >
  SortedList< T >::SortedList( SortedList< T > const& sortedList ) :
    m_tiers( 0 ),
    List< T >(),
    SortedContainer< T >()
  {
    PushBackRange( sortedList );
  }


  template< typename T >
  SortedList< T >::SortedList( Container< T > const& container ) :
    m_tiers( 0 ),
    List< T >(),
    SortedContainer< T >()
  {
    PushBackRange( container );
  }


  template< typename T >
  SortedList< T >& SortedList< T >::operator=( SortedList< T > const& sortedList )
  {
    Clear();

    PushBackRange( sortedList );
    return *this;
  }


  template< typename T >
  SortedContainer< T >& SortedList< T >::operator=( SortedContainer< T > const& sortedContainer )
  {
    Clear();

    PushBackRange( sortedContainer );
    return *this;
  }


  template< typename T >
  SortedList< T >::~SortedList()
  {
    Clear();
  }


  template< typename T >
  SortedList< T > SortedList< T >::operator+( SortedList< T > const& sortedList ) const
  {
    SortedList< T > newList( *this );
    newList.PushBackRange( sortedList );
    return newList;
  }


  template< typename T >
  SortedList< T >& SortedList< T >::operator+=( SortedList< T > const& sortedList )
  {
    PushBackRange( sortedList );
    return *this;
  }


  template< typename T >
  void SortedList< T >::PushFront( T const& t )
  {
    Push( t );
  }


  template< typename T >
  void SortedList< T >::PushBack( T const& t )
  {
    Push( t );
  }


  template< typename T >
  void SortedList< T >::PopFront()
  {
    if( IsEmpty() )
      return;

    SortedListNode* temp = static_cast< SortedListNode* >( m_front );
    Pop( temp );
  }


  template< typename T >
  void SortedList< T >::PopBack()
  {
    if( IsEmpty() )
      return;

    SortedListNode* temp = static_cast< SortedListNode* >( m_back );
    Pop( temp );
  }


  template< typename T >
  void SortedList< T >::PopFirst( T const& t )
  {
    if( IsEmpty() )
      return;

    SortedListNode const * temp = static_cast< SortedListNode* >( m_front );
    if( Search( &temp, t ) )
      Pop( temp );
  }


  template< typename T >
  void SortedList< T >::PopAll( T const& t )
  {
    if( IsEmpty() )
      return;
    
    SortedListNode const * temp = static_cast< SortedListNode* >( m_front );
    while( Search( &temp, t ) )
      Pop( temp );
  }


  template< typename T >
  bool const SortedList< T >::Contains( T const& t ) const
  {
    if( IsEmpty() )
      return false;
    
    SortedListNode const * temp = static_cast< SortedListNode* >( m_front );
    return Search( &temp, t );
  }  


  template< typename T >
  void SortedList< T >::Clear()
  {
    if( IsEmpty() )
      return;

    ClearTiers( static_cast< SortedListNode* >( m_front ) );
    m_front = 0;
    m_back = 0;
    m_tiers = 0;
    InvalidateAllIteratorImplementations();
  }    


  template< typename T >
  void SortedList< T >::Push( T const& t )
  {
    unsigned 
      possibleTiers = m_size / c_logBase,
      currentNodesTiers = 0;
    if( possibleTiers > 0 )
    {
      // randomly calculate how many tiers this node will have
      currentNodesTiers = 1;
      while( currentNodesTiers < possibleTiers && ( ( 1.0 / log( currentNodesTiers * c_logBase ) ) * 100.0 ) > (float)( rand() % 100 ) )
        ++currentNodesTiers;
    }

    // make sure the front node always has all possible tiers
    if( possibleTiers > m_tiers )
      NewSortedListNodeTier();

    // allocate space for T and all tiers (including base tier)
    char* memLoc = new char[ sizeof( T ) + ( sizeof( SortedListNode ) * ( currentNodesTiers + 1 ) ) ];

    // allocate new T
    T* newT = new( memLoc ) T( t );

    bool contains;
    SortedListNode  *newPrev,
            *newNext,
            *newNextTier,
            *node = 0;

    // if we're empty, we know we won't have any tiers, and we know we'll need to set m_front and m_back
    if( IsEmpty() )
    {
      node = new( memLoc + sizeof( T ) ) SortedListNode( 0, 0, newT, 0 );
      m_back = m_front = node;
    }
    // otherwise, we might have tiers
    else
    {
      // allocate new tiers, from bottom to top
      for( unsigned i = 0; i <= currentNodesTiers; ++i )
      {
        FindInsertionNodeInTier( m_tiers, i, *newT, contains, &newPrev, &newNext, &newNextTier );
        node = new( memLoc + sizeof( T ) + ( sizeof( SortedListNode ) * i ) ) SortedListNode( newPrev, newNext, newT, newNextTier );
        if( newPrev != 0 )
          newPrev->m_next = node;
        if( newNext != 0 )
          newNext->m_prev = node;
      }

      // should we update our back pointer?
      // this way, we can make sure the back pointer always points to the highest tier, too
      if( m_greaterThanFunc( *( node->m_data ), *( m_back->m_data ) ) )
        m_back = node;
    }

    ++m_size;
    InvalidateAllIteratorImplementations();
  }


  template< typename T >
  void SortedList< T >::NewSortedListNodeTier()
  {
    SortedListNode  *front = static_cast< SortedListNode* >( m_front ),
            *newTier = new SortedListNode( 0, 0, front->m_data, front->m_nextTier );
    front->m_nextTier = newTier;
    ++m_tiers;
  }
    

  template< typename T >
  void SortedList< T >::FindInsertionNodeInTier(  unsigned const topTierLevel,
                          unsigned const tierToInsert,
                          T const& t, 
                          bool& contains, 
                          SortedListNode** prev, 
                          SortedListNode** next,
                          SortedListNode** nextTier ) const
  {
    SortedListNode* pointer = static_cast< SortedListNode* >( m_front );
    unsigned tier = topTierLevel;

    while( pointer->m_next != 0 )
    {
      // if the current node's data is less than the data to be inserted, advance
      if( m_lessThanFunc( *( pointer->m_data ), t ) )
        pointer = static_cast< SortedListNode* >( pointer->m_next );
      // if the current node's data is more than the data to be inserted ...
      else if( m_greaterThanFunc( *( pointer->m_data ), t ) )
      {
        // if we're not on the bottom tier, go back a node and go down a tier
        // NOTE: second condition SHOULD be redundant, and can HOPEFULLY be removed after testing
        if( --tier > tierToInsert && pointer->m_nextTier != 0 )
        {
          pointer = static_cast< SortedListNode* >( pointer->m_prev )->m_nextTier;
        }
        // otherwise, if we are, return the current and previous nodes
        else
        {
          *prev = static_cast< SortedListNode* >( pointer->m_prev );
          *next = pointer;
          *nextTier = pointer->m_nextTier;
          return;
        }
      }
      // if the current node's data is equal to the data to be inserted, return the bottom tier of the current node
      else if( m_equalityFunc( *( pointer->m_data ), t ) )
      {
        contains = true;

        pointer = GetBottomTier( pointer, tier, tierToInsert );
        *prev = static_cast< SortedListNode* >( pointer->m_prev );
        *next = pointer;
        *nextTier = pointer->m_nextTier;
        return;
      }
    }

    // if the very last node's data is less than the data to be inserted,
    // return the last node as the new previous and the last node's m_next (0) as the new next
    if( m_lessThanFunc( *( pointer->m_data ), t ) )
    {
      *prev = pointer;
      *next = static_cast< SortedListNode* >( pointer->m_next );
    }
    // if the very last node's data is greater than or equal to the data to be inserted,
    // return the last node's m_prev as the new previous and the last node as the new next
    else
    {
      if( m_equalityFunc( *( pointer->m_data ), t ) )
        contains = true;
      
      *prev = static_cast< SortedListNode* >( pointer->m_prev );
      *next = pointer;
    }
    *nextTier = pointer->m_nextTier;
  }
  

  template< typename T >
  unsigned const SortedList< T >::GetNumberOfTiers( SortedListNode const * const topTier ) const
  {
    unsigned number = 0;
    SortedListNode const * node = topTier;
    for( ; node->m_nextTier != 0; node = node->m_nextTier )
      ++number;
    return number;
  }
  

  template< typename T >
  void SortedList< T >::ClearTiers( SortedListNode const * topTier ) const
  {
    while( topTier != 0 )
    {
      if( topTier->m_prev != 0 )
        topTier->m_prev->m_next = topTier->m_next;
      if( topTier->m_next != 0 )
        topTier->m_next->m_prev = topTier->m_prev;

      SortedListNode const * temp = topTier;
      topTier = topTier->m_nextTier;
      delete temp;
    }
  }


  template< typename T >
  bool const SortedList< T >::Search( SortedListNode const** startIndex, T const& t ) const
  {
    SortedListNode *prev, *next, *nextTier;
    bool contains = false;
    FindInsertionNodeInTier( m_tiers, 0, t, contains, &prev, &next, &nextTier );
    if( contains )
      *startIndex = next;
    return contains;
  }


  template< typename T >
  void SortedList< T >::Pop( SortedListNode const * const sortedListNode )
  {
    if( sortedListNode == m_front )
    {
      m_front = FindNewFront();
      while( GetNumberOfTiers( static_cast< SortedListNode* >( m_front ) ) < m_tiers )
        NewSortedListNodeTier();
    }
    if( sortedListNode == m_back )
      m_back = FindNewBack();
    ClearTiers( sortedListNode );
    --m_size;
    InvalidateAllIteratorImplementations();
  }
  
}
