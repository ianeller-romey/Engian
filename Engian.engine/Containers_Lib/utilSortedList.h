
#ifndef UTIL_SORTEDLIST_H
#define UTIL_SORTEDLIST_H

#include "debugForTestDefines.h"

#include "utilSortedContainer.h"
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
  class SortedList : public SortedContainer< T >, public List< T >
  {
    public:
      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );

      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILSORTEDLIST_FRIEND;

      SortedList();
      SortedList( unsigned const capacity );
      SortedList( T const * const tArray, unsigned const size );
      SortedList( SortedList< T > const& sortedList );
      SortedList( Container< T > const& container );
      virtual ~SortedList();
      virtual SortedList< T >& operator=( SortedList< T > const& sortedList );
      virtual SortedContainer< T >& operator=( SortedContainer< T > const& sortedContainer );

      virtual SortedList< T > operator+( SortedList< T > const& list ) const;
      virtual SortedList< T >& operator+=( SortedList< T > const& list );
      
      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void PopFront();
      virtual void PopBack();
      virtual void PopFirst( T const& t );
      virtual void PopAll( T const& t );
      virtual bool const Contains( T const& t ) const;

      virtual void Clear();


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
      void NewSortedListNodeTier();

      void FindInsertionNodeInTier( unsigned const topTierLevel, unsigned const tierToInsert, T const& t, bool& contains, SortedListNode** prev, SortedListNode** next, SortedListNode** nextTier ) const;
      
      SortedListNode* GetBottomTier( SortedListNode* const topTier, unsigned const topTierLevel, unsigned const bottomTierLevel ) const
      {
        DFT_FUNC_TRACK( "SortedListNode* SortedList< T >::GetBottomTier( SortedListNode* const topTier, unsigned const topTierLevel, unsigned const bottomTierLevel ) const" );

        SortedListNode* bottom = topTier;
        // NOTE: second condition SHOULD be redundant, and can HOPEFULLY be removed after testing
        for( unsigned i = topTierLevel; i > bottomTierLevel && bottom->m_nextTier != 0; --i )
          bottom = bottom->m_nextTier;
        return static_cast< SortedListNode* >( bottom );
      }

      unsigned const GetNumberOfTiers( SortedListNode const * const topTier ) const;

      void ClearTiers( SortedListNode const * topTier ) const;
      
      SortedListNode* FindNewFront() const
      {
        DFT_FUNC_TRACK( "SortedListNode* SortedList< T >::FindNewFront() const" );

        SortedListNode* node = static_cast< SortedListNode* >( m_front );
        while( node->m_next == 0 && node != 0 )
          node = node->m_nextTier;
        return ( node == 0 ) ? 0 : static_cast< SortedListNode* >( node->m_next );
      }


      SortedListNode* FindNewBack() const
      {
        DFT_FUNC_TRACK( "SortedListNode* SortedList< T >::FindNewBack() const" );

        SortedListNode  *node = dynamic_cast< SortedListNode* >( m_front ),
                *temp;
        while( node != 0 )
        {
          // if every tier's m_next pointer is null, then this is the very last node
          for( temp = node; temp != 0; temp = temp->m_nextTier )
          {
            if( temp->m_next != 0 )
              break;
          }
          // if no m_next pointers were found, this is the last node
          if( temp == 0 )
            return node;
          // if we're at the end of the tier, move down to the next tier
          if( node->m_next == 0 && node->m_nextTier != 0 )
            node = node->m_nextTier;
          node = static_cast< SortedListNode* >( node->m_next );
        }
        return 0;
      }

      ////////
      // member variable
      unsigned m_tiers;
      static float const c_logBase;


    private:
      bool const Search( SortedListNode const** startIndex, T const& t ) const;
      void Pop( SortedListNode const * const sortedListNode );

  };

}

#include "utilSortedList.inl"

#endif
