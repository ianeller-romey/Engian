
#ifndef UTIL_LIST_H
#define UTIL_LIST_H

#include "debugForTestDefines.h"

#include "utilContainer.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilList;
}
#define TESTHELPER_UTILLIST_FRIEND friend class Test::TestHelper_UtilList
#else
#define TESTHELPER_UTILLIST_FRIEND
#endif


namespace Util
{

  template< typename T >
  class List : public virtual Container< T >
  {
    protected:
      struct ListNode;

    public:
      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILLIST_FRIEND;

      List();
      List( T const * const tArray, unsigned const size );
      List( List< T > const& list );
      List( Container< T > const& container );
      virtual List< T >& operator=( List< T > const& list );
      virtual Container< T >& operator=( Container< T > const& container );
      virtual ~List();
        

      virtual Iterator Begin() const
      {
        DFT_FUNC_TRACK( "Iterator List< T >::Begin() const" );

        ListIteratorImpl* iter = new ListIteratorImpl( m_front );
        return CreateIteratorFromImplementation( iter );
      }


      virtual Iterator const End() const
      {
        DFT_FUNC_TRACK( "Iterator const List< T >::End() const" );

        ListIteratorImpl* iter = new ListIteratorImpl( m_end );
        return CreateIteratorFromImplementation( iter );
      }


      virtual List< T > operator+( List< T > const& list ) const;
      virtual List< T >& operator+=( List< T > const& list );

      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void PopFront();
      virtual void PopBack();
      virtual void PopFirst( T const& t );
      virtual void PopAll( T const& t );
      virtual bool const Contains( T const& t ) const;
      

    protected:
      ////////
      // member functions
      List( ListNode* end );

      ////////
      // member classes
      struct ListNode
      {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_UTILLIST_FRIEND;

        ListNode( ListNode* prev, ListNode* next, T* data );
        virtual ~ListNode();

        ListNode *m_prev,
                 *m_next;
        T* m_data;
      };

      class ListIteratorImpl : public IteratorImpl
      {
        public:
          DFT_FUNC_TRACK_CLASS_DEC;
          TESTHELPER_UTILLIST_FRIEND;

          ListIteratorImpl( ListNode* const listNode );
          virtual ~ListIteratorImpl();

          virtual bool const operator==( IteratorImpl const& iterator ) const
          {
            DFT_FUNC_TRACK( "bool const List< T >::ListIteratorImpl::operator==( IteratorImpl const& iterator ) const" );

            ListIteratorImpl const* listIteratorImpl = dynamic_cast< ListIteratorImpl const* >( &iterator );
            if( listIteratorImpl == 0 )
              return false;
            
            return m_listNode == listIteratorImpl->m_listNode;
          }  


          virtual bool const operator!=( IteratorImpl const& iterator ) const
          {
            DFT_FUNC_TRACK( "bool const List< T >::ListIteratorImpl::operator!=( IteratorImpl const& iterator ) const" );

            ListIteratorImpl const* listIteratorImpl = dynamic_cast< ListIteratorImpl const* >( &iterator );
            if( listIteratorImpl == 0 )
              return false;

            return m_listNode != listIteratorImpl->m_listNode;
          }


          virtual IteratorImpl * const Clone() const
          {
            DFT_FUNC_TRACK( "IteratorImpl * const List< T >::ListIteratorImpl::Clone() const" );

            return new ListIteratorImpl( *this );
          }
          

        protected:
          virtual void AdvanceValue();
          virtual T const& GetValue() const;

          ListNode* m_listNode;
          //!< We use this boolean to determine if we're an .End() Iterator, while still being able to differentiate between
          //!< .End() Iterators from different Lists (instead of having all .End() Iterators pointing to 0)
          bool m_isEnd;

        private:
          ListIteratorImpl();
          ListIteratorImpl( ListIteratorImpl const& listIteratorImpl );
          ListIteratorImpl& operator=( ListIteratorImpl const& listIteratorImpl );
      };

      ////////
      // member variables
      //!< m_end is an empty pointer to which m_back->m_next will always point; m_prev, m_next, and m_data will all be set to 0 for that ListNode
      //!< m_end should be unique for every List, to prevent accidental equivalence of Iterators
      ListNode* m_end;
      ListNode* m_front;
      ListNode* m_back;


    private:
      bool const Search( ListNode const** startIndex, T const& t ) const;
      void Pop( ListNode const * const listNode );
  };

}

#include "utilList.inl"

#endif