
#ifndef UTIL_CONTAINER_H
#define UTIL_CONTAINER_H

#include "../Engian.test/Engian.test/testIcle.h"


namespace Util
{

  template< typename T >
  class Container
  {      
    public:
      TESTCHASSISFRIEND;

      class Iterator;

    protected:
      /*!  \class IteratorImpl
       *  \brief This abstract class contains the actual implementation of an Iterator,
       *  and must be derived from in any class that derives from a Container< T >.
       */
      class IteratorImpl
      {
        public:
          TESTCHASSISFRIEND;

          IteratorImpl( bool valid );
          virtual ~IteratorImpl();
          
          IteratorImpl& operator++()
          {
            AdvanceValue();
            return *this;
          }

          virtual bool const operator==( IteratorImpl const& iterator ) const = 0;
          virtual bool const operator!=( IteratorImpl const& iterator ) const = 0;

          virtual IteratorImpl * const Clone() const = 0;

          T const& Get();

          void Invalidate();


        protected:
          ////////
          // member functions
          void CheckValid() const;
          virtual void AdvanceValue() = 0;
          virtual T const& GetValue() const = 0;
          
          ////////
          // member variables
          static char const * const c_exception_invalidatedContainer; //!< This exception message will be thrown whenever
                                                                      //!< an invalidated IteratorImpl is accessed.
          bool m_valid; //!< When the parent Container< T > changes size, all existing IteratorImpls are effectively invalidated.

        private:
          IteratorImpl(); //!< No default constructor allowed.
          IteratorImpl( IteratorImpl const& iterator ); //!< We don't want to be able to copy construct or assign.
          IteratorImpl& operator=( IteratorImpl const& iterator ); //!< We don't want to be able to copy construct or assign.
      };

      /*! \struct IteratorImplNode
       *  \brief We're going to have a linked list of all the IteratorImpls that we've created,
       *  so that we can easily invalidate them when needed.
       *  \remarks We'll just have this be a singly-linked list; I don't mind having to walk the entire list to remove
       *  an IteratorNode, since the list for any given Container should never be THAT big.
       */
      struct IteratorImplNode
      {
        IteratorImplNode( IteratorImpl* implementation, IteratorImplNode* next );

        IteratorImpl* m_implementation;
        IteratorImplNode* m_next;
      };
      
      Iterator CreateIteratorFromImplementation( IteratorImpl* const implementation ) const
      {    
        if( m_implementations == 0 )
          m_implementations = new IteratorImplNode( implementation, 0 );
        else
        {
          IteratorImplNode* node = new IteratorImplNode( implementation, m_implementations );
          m_implementations = node;
        }

        return Iterator( implementation, &m_implementations );
      }

      void InvalidateAllIteratorImplementations();

      unsigned m_size;
      mutable IteratorImplNode* m_implementations;


    public:
      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );
      typedef void (*SortFunc) ( T const * const, unsigned );

      class Iterator
      {
        public:
          TESTCHASSISFRIEND;

          friend class Container< T >; //!< Friending always feels gross, but this allows a Container< T > to create
                                       //!< an original Iterator, whereas a user can only create a copy constructed Iterator. 
          Iterator( Iterator const& iterator ); //!< Users should only ever be able to copy-construct an Iterator.
          virtual ~Iterator();
            
          Iterator& operator++()
          {
            ++( *m_implementation );
            return *this;
          }

          bool operator==( Iterator const& iterator ) const;
          bool operator!=( Iterator const& iterator ) const;

          T const& operator*() const;
          T const& Get() const;


        protected:
          ////////
          // member functions
          Iterator( IteratorImpl* implementation, IteratorImplNode** parentList ); //!< The constructor needs to be private to ensure
                                                                                   //!< that it is only ever created from a call to 
                                                                                   //!< Container< T >.Begin() or .End().
          void CheckValid();
          void RemoveFromParentList();
          
          ////////
          // member variables
          IteratorImpl* m_implementation;
          IteratorImplNode** m_parentsIterators;


        private:
          Iterator(); //!< No default constructor allowed.
          Iterator& operator=( Iterator const& iterator ); //!< No assignment allowed.
      };

      Container();
      virtual ~Container();

      virtual Container< T >& operator=( Container< T > const& container ) = 0;
      virtual bool const operator==( Container< T > const& container ) const;
      virtual bool const operator!=( Container< T > const& container ) const;
      virtual Container< T >& operator+=( Container< T > const& container );

      virtual Iterator Begin() const = 0;
      virtual Iterator const End() const = 0;

      virtual void PushFront( T const& t ) = 0;
      virtual void PushBack( T const& t ) = 0;
      virtual void PushBackRange( T const * const tArray, unsigned const size );
      virtual void PushBackRange( Container< T > const& container );
      virtual void PopFront() = 0;
      virtual void PopBack() = 0;
      virtual void PopFirst( T const& t ) = 0;
      virtual void PopAll( T const& t ) = 0;
      virtual bool const Contains( T const& t ) const;
      virtual bool const IsEmpty() const;

      virtual unsigned const GetSize() const;

      virtual void Clear();
  };

}

#include "utilContainer.inl"

#endif
