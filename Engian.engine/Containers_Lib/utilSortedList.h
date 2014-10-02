
#ifndef UTIL_SORTEDLIST_H
#define UTIL_SORTEDLIST_H

#include "debugForTestDefines.h"

#include "utilSorter.h"
#include "utilList.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilSortedList;
}
#define TESTHELPER_UTILSORTEDLIST_FRIEND friend class Test::TestHelper_UtilSortedList
#else
#define TESTHELPER_UTILSORTEDLIST_FRIEND
#endif


namespace Util
{

  template< typename T >
  class SortedList : public Sorter< T >, public List< T >
  {
    public:
      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );

      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILSORTEDLIST_FRIEND;

      SortedList();
      SortedList( T const * const tArray, unsigned const size );
      SortedList( SortedList< T > const& sortedList );
      SortedList( Container< T > const& container );
      virtual ~SortedList();
      virtual SortedList< T >& operator=( SortedList< T > const& sortedList );        

      virtual Iterator Begin() const
      {
        DFT_FUNC_TRACK( "Iterator SortedList< T >::Begin() const" );

        ListIteratorImpl* iter = new ListIteratorImpl( GetBottomTier( static_cast< SortedListNode* >( m_front ), m_tiers, 0 ) );
        return CreateIteratorFromImplementation( iter );
      }


      virtual Iterator const End() const
      {
        DFT_FUNC_TRACK( "Iterator const SortedList< T >::End() const" );

        ListIteratorImpl* iter = new ListIteratorImpl( m_end );
        return CreateIteratorFromImplementation( iter );
      }

      virtual SortedList< T > operator+( SortedList< T > const& list ) const;
      virtual SortedList< T >& operator+=( SortedList< T > const& list );
      
      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void PopFront();
      virtual void PopBack();
      virtual void PopFirst( T const& t );
      virtual void PopAll( T const& t );
      virtual bool const Contains( T const& t ) const;


    protected:
      ////////
      // member classes
      struct SortedListNode : public List< T >::ListNode
      {
        //DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_UTILSORTEDLIST_FRIEND;

        SortedListNode( ListNode* prev, 
                        ListNode* next, 
                        T* data, 
                        SortedListNode* nextTier );

        SortedListNode* m_nextTier;
      };

      ////////
      // member functions
      void Push( T const& t );

      void AddTierToHead();
      unsigned const CalculateRandomNumberOfTiers() const;

      void FindInsertionNodeInTier( SortedListNode* startTier,
                                    unsigned const startTierNumber, 
                                    unsigned const tierToInsert, 
                                    T const& t, 
                                    bool& contains, 
                                    SortedListNode** prev, 
                                    SortedListNode** next ) const;
      
      SortedListNode* GetBottomTier( SortedListNode* const topTier, unsigned const topTierLevel, unsigned const bottomTierLevel ) const
      {
        DFT_FUNC_TRACK( "SortedListNode* SortedList< T >::GetBottomTier( SortedListNode* const topTier, unsigned const topTierLevel, unsigned const bottomTierLevel ) const" );
        SortedListNode* bottom = topTier;
        if( bottomTierLevel == 0 )
        {
          while( bottom->m_nextTier != m_end )
            bottom = bottom->m_nextTier;
        }
        else
        {
          for( unsigned i = topTierLevel; i > bottomTierLevel; --i )
            bottom = bottom->m_nextTier;
        }
        return static_cast< SortedListNode* >( bottom );
      }

      unsigned const GetNumberOfTiers( SortedListNode const * const topTier ) const;

      void ClearTiers( SortedListNode const * topTier ) const;

      SortedListNode* FindNewFront() const
      {
        DFT_FUNC_TRACK( "SortedListNode* SortedList< T >::FindNewFront() const" );
        SortedListNode *node = dynamic_cast< SortedListNode* >( m_head ),
                       *temp;
        for( unsigned i = m_tiers; i > 0; --i )
        {
          // if every tier's m_prev pointer is m_head, then this is the very first node
          for( temp = static_cast< SortedListNode* >( node->m_next ); temp != m_end; temp = temp->m_nextTier )
          {
            if( temp->m_prev->m_prev != m_end )
              break;
          }
          // if we made it past the bottom tier, this is our new front pointer
          if( temp == m_end )
            return static_cast< SortedListNode* >( node->m_next );
          // otherwise, move down a tier and start over
          else
            node = node->m_nextTier;
        }
        return static_cast< SortedListNode* >( m_end );
      }


      SortedListNode* FindNewBack() const
      {
        DFT_FUNC_TRACK( "SortedListNode* SortedList< T >::FindNewBack() const" );
        SortedListNode *node = dynamic_cast< SortedListNode* >( m_head ),
                       *temp;
        while( node != m_end )
        {
          // walk to the end of this tier
          while( node->m_next != m_end )
            node = static_cast< SortedListNode* >( node->m_next );

          // if every tier's m_next pointer is m_end, then this is the very last node
          for( temp = node; temp != m_end; temp = temp->m_nextTier )
          {
            if( temp->m_next != m_end )
              break;
          }
          // if we made it past the bottom tier, this is our new back pointer
          if( temp == m_end )
            return node;
          // otherwise, move down a tier and start over
          else
            node = node->m_nextTier;
        }
        return static_cast< SortedListNode* >( m_end );
      }

      virtual void Deallocate();

      ////////
      // member variable
      static float const c_logBase;
      unsigned m_tiers;
      SortedListNode* m_head;


    private:
      bool const Search( SortedListNode const** startIndex, T const& t ) const;
      void Pop( SortedListNode const * const sortedListNode );

  };

}

#include "utilSortedList.inl"

#endif
