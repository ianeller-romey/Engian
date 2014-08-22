
#ifndef UTIL_HASHTABLE_H
#define UTIL_HASHTABLE_H

#include "debugDefines.h"

#include "utilContainer.h"
#include "utilVector.h"
#include "utilList.h"


namespace Util
{

  template< typename T, typename KEY >
  class HashTable : public virtual Container< T >
  {
    protected:
      struct HashTableNode;

    public:
      typedef unsigned const (*HashFunc) ( void const * const key, unsigned const upperLimit );
      
      //DEBUG_FUNC_TRACK_CLASS_DEC
      DEBUG_VAR_GET( c_defaultCapacity, static unsigned const )
      DEBUG_VAR_GET( c_growRatio, static float const )
      DEBUG_VAR_GET( c_growMultiplier, static float const )
      DEBUG_VAR_GET( m_hashFunc, HashFunc const )
      DEBUG_VAR_GET( m_capacity, unsigned )
      DEBUG_VAR_GET( m_buckets, HashTableNode** )

      class KeyedIterator : public Container< T >::Iterator
      {
        public:
          //DEBUG_FUNC_TRACK_CLASS_DEC

          friend class HashTable< T, KEY >;  //!< Friending always feels gross, but this allows a HashTable< T, KEY > to create
                                             //!< an original KeyedIterator, whereas a user can only create a copy constructed KeyedIterator. 
          KeyedIterator( KeyedIterator const& iterator ); //!< Users should only ever be able to copy-construct an Iterator.
          virtual ~KeyedIterator();
            
          KeyedIterator& operator++()
          {
            ++( *m_implementation );
            return *this;
          }

          KEY const& Key() const;


        private:
          KeyedIterator(); //!< No default constructor allowed.
          KeyedIterator( Container< T >::IteratorImpl* implementation, 
                         Container< T >::IteratorImplNode** parentList ); //!< The constructor needs to be private to ensure
                                                                          //!< that it is only ever created from a call to 
                                                                          //!< HashTable< T, KEY >.KeyedBegin() or .KeyedEnd().
          KeyedIterator& operator=( KeyedIterator const& iterator ); //!< No assignment allowed.
      };
      
      HashTable();
      HashTable( T const * const tArray, unsigned const size );
      HashTable( HashTable< T, KEY > const& hashTable );
      HashTable( Container< T > const& container );
      HashTable( HashFunc hashFunc );
      HashTable( T const * const tArray, unsigned const size, HashFunc hashFunc );
      HashTable( HashTable< T, KEY > const& hashTable, HashFunc hashFunc );
      HashTable( Container< T > const& container, HashFunc hashFunc );
      virtual HashTable< T, KEY >& operator=( HashTable< T, KEY > const& hashTable );
      virtual Container< T >& operator=( Container< T > const& container );
      virtual ~HashTable();
        
      virtual Iterator Begin() const
      {
        DEBUG_FUNC_TRACK( "Iterator HashTable< T, KEY >::Begin() const" );

        HashTableIteratorImpl* iter = new HashTableIteratorImpl( m_buckets, m_capacity );
        return CreateIteratorFromImplementation( iter );
      }
      

      virtual Iterator const End() const
      {
        DEBUG_FUNC_TRACK( "Iterator const HashTable< T, KEY >::End() const" );

        HashTableIteratorImpl* iter = new HashTableIteratorImpl( 0, m_capacity );
        return CreateIteratorFromImplementation( iter );
      }        


      virtual KeyedIterator KeyedBegin() const
      {
        DEBUG_FUNC_TRACK( "KeyedIterator HashTable< T, KEY >::KeyedBegin() const" );

        HashTableIteratorImpl* iter = new HashTableIteratorImpl( m_buckets, m_capacity );
        return CreateKeyedIteratorFromImplementation( iter );
      }
      

      virtual KeyedIterator const KeyedEnd() const
      {
        DEBUG_FUNC_TRACK( "KeyedIterator const HashTable< T, KEY >::KeyedEnd() const" );

        HashTableIteratorImpl* iter = new HashTableIteratorImpl( 0, m_capacity );
        return CreateKeyedIteratorFromImplementation( iter );
      }
      
      virtual T& operator[]( KEY const& key ) const;
      virtual HashTable< T, KEY > operator+( HashTable< T, KEY > const& hashTable ) const;
      virtual HashTable< T, KEY >& operator+=( HashTable< T, KEY > const& hashTable );
      

      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void Push( T const& t, KEY const& key );
      virtual void PopFront();
      virtual void PopBack();
      virtual void PopFirst( T const& t );
      virtual void PopAll( T const& t );
      virtual void Pop( KEY const& key );

      virtual Vector< KEY > GetKeys() const;

      virtual unsigned const GetCapacity() const;

      virtual void Clear();


    protected:
      ////////
      // member classes
      struct HashTableNode
      {
        DEBUG_FUNC_TRACK_CLASS_DEC;

        HashTableNode( HashTableNode* next, T* data, KEY const& key );
        virtual ~HashTableNode();

        HashTableNode *m_next;
        T* m_data;
        KEY m_key;
      };

      class HashTableIteratorImpl : public Container< T >::IteratorImpl
      {
        public:
          //DEBUG_FUNC_TRACK_CLASS_DEC
          DEBUG_VAR_GET( m_buckets, HashTableNode** const )
          DEBUG_VAR_GET( m_capacity, unsigned const )
          DEBUG_VAR_GET( m_currentBucketIndex, unsigned )
          DEBUG_VAR_GET( m_currentBucketNode, HashTableNode* )

          HashTableIteratorImpl( HashTableNode** buckets, unsigned const numberOfBuckets );
          virtual ~HashTableIteratorImpl();
          
          virtual bool const operator==( IteratorImpl const& iterator ) const
          {
            DEBUG_FUNC_TRACK( "bool const HashTable< T, KEY >::HashTableIteratorImpl::operator==( IteratorImpl const& iterator ) const" );

            HashTableIteratorImpl const* hashTableIteratorImpl = dynamic_cast< HashTableIteratorImpl const* >( &iterator );
            if( hashTableIteratorImpl == 0 )
              return false;
            
            return m_currentBucketNode == hashTableIteratorImpl->m_currentBucketNode;
          }  


          virtual bool const operator!=( IteratorImpl const& iterator ) const
          {
            DEBUG_FUNC_TRACK( "bool const HashTable< T, KEY >::HashTableIteratorImpl::operator=!( IteratorImpl const& iterator ) const" );

            HashTableIteratorImpl const* hashTableIteratorImpl = dynamic_cast< HashTableIteratorImpl const* >( &iterator );
            if( hashTableIteratorImpl == 0 )
              return false;
            
            return m_currentBucketNode != hashTableIteratorImpl->m_currentBucketNode;
          }


          virtual IteratorImpl * const Clone() const
          {
            DEBUG_FUNC_TRACK( "IteratorImpl * const HashTable< T, KEY >::HashTableIteratorImpl::Clone() const" );

            return new HashTableIteratorImpl( *this );
          }
          
          virtual KEY const& Key() const;


        protected:
          virtual void AdvanceValue();
          virtual T const& GetValue() const;
          virtual KEY const& GetKey() const;

          HashTableNode** const m_buckets;
          unsigned const m_capacity;
          unsigned m_currentBucketIndex;
          HashTableNode* m_currentBucketNode;

        private:
          HashTableIteratorImpl();
          HashTableIteratorImpl( HashTableIteratorImpl const& hashTableNodeImpl );
          HashTableIteratorImpl& operator=( HashTableIteratorImpl const& hashTableNodeImpl );
      };

      ////////
      // member functions
      virtual void Push( T const& t, void const * const key, HashTableNode** const buckets, unsigned const bucketArraySize );
      virtual void CheckAndGrow();
      virtual void Grow();
      void Clear( HashTableNode**& buckets, unsigned& bucketArraySize );
      
      KeyedIterator CreateKeyedIteratorFromImplementation( IteratorImpl* const implementation ) const
      {    
        DEBUG_FUNC_TRACK( "KeyedIterator HashTable< T, KEY >::CreateKeyedIteratorFromImplementation( IteratorImpl* const implementation ) const" );

        if( m_implementations == 0 )
          m_implementations = new Container< T >::IteratorImplNode( implementation, 0 );
        else
        {
          Container< T >::IteratorImplNode* node = new Container< T >::IteratorImplNode( implementation, m_implementations );
          m_implementations = node;
        }

        return KeyedIterator( implementation, &m_implementations );
      }
      
      ////////
      // member variables
      static unsigned const c_defaultCapacity;
      static float const    c_growRatio,
                            c_growMultiplier; // TODO: Dynamically calculated grow multiplier?
      HashFunc const        m_hashFunc;
      unsigned              m_capacity;
      HashTableNode**       m_buckets;

  };

}

#include "utilHashTable.inl"

#endif
