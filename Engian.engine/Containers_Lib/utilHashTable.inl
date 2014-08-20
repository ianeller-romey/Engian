
#include "utilHashFunctions.h"


namespace Util
{

  template< typename T, typename KEY >
  HashTable< T, KEY >::KeyedIterator::KeyedIterator( KeyedIterator const& iterator ) :
    m_implementation( ++iterator.m_implReferenceCounter ),
    m_implementation( iterator.m_implementation ),
    m_parentsIterators( iterator.m_parentsIterators )
  {
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::KeyedIterator::~KeyedIterator()
  {
    Container< T >::Iterator::~Iterator();
  }


  template< typename T, typename KEY >
  KEY const& HashTable< T, KEY >::KeyedIterator::Key() const
  {
    return static_cast< HashTableIteratorImpl* >( m_implementation )->Key();
  }
  

  template< typename T, typename KEY >
  HashTable< T, KEY >::KeyedIterator::KeyedIterator(  IteratorImpl* implementation, 
                            IteratorImplNode** parentList ) :
    Iterator( implementation, parentList )
  {
  }
        

  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTableNode::HashTableNode( HashTableNode* next, T* data, KEY const& key ) :
    m_next( next ),
    m_data( data ),
    m_key( key )
  {
  }

      
  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTableNode::~HashTableNode()
  {
  }

      
  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTableIteratorImpl::HashTableIteratorImpl( HashTableNode** buckets, unsigned const numberOfBuckets ) :
    IteratorImpl( true ),
    m_buckets( buckets ),
    m_capacity( numberOfBuckets ),
    m_currentBucketIndex( 0 ),
    m_currentBucketNode( 0 )
  {
    // m_buckets will be 0 if this is and .End() or .KeyedEnd() iterator
    // if m_buckets is not 0, but the first bucket is, walk forward until we find the first non-0 bucket
    if( m_buckets != 0 && m_buckets[ m_currentBucketIndex ] == 0 )
    {
      while( ++m_currentBucketIndex < m_capacity )
      {
        if( m_buckets[ m_currentBucketIndex ] != 0 )
        {
          m_currentBucketNode = m_buckets[ m_currentBucketIndex ];
          break;
        }
      }
    }
  }

  
  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTableIteratorImpl::~HashTableIteratorImpl()
  {
  }
  

  template< typename T, typename KEY >
  KEY const& HashTable< T, KEY >::HashTableIteratorImpl::Key() const
  {
    if( !m_valid )
      throw c_exception_invalidatedContainer;

    return GetKey();
  }
      
  
  template< typename T, typename KEY >
  void HashTable< T, KEY >::HashTableIteratorImpl::AdvanceValue()
  {
    if( m_currentBucketNode->m_next != 0 )
      m_currentBucketNode = m_currentBucketNode->m_next;
    else
    {
      while( ++m_currentBucketIndex < m_capacity )
      {
        if( m_buckets[ m_currentBucketIndex ] == 0 )
          continue;
        m_currentBucketNode = m_buckets[ m_currentBucketIndex ];
        return;
      }

      m_currentBucketNode = 0;
    }
  }
  

  template< typename T, typename KEY >
  T const& HashTable< T, KEY >::HashTableIteratorImpl::GetValue() const
  {
    return *( m_currentBucketNode->m_data );
  }
  

  template< typename T, typename KEY >
  KEY const& HashTable< T, KEY >::HashTableIteratorImpl::GetKey() const
  {
    return m_currentBucketNode->m_key;
  }
  

  template< typename T, typename KEY >
  unsigned const  HashTable< T, KEY >::c_defaultCapacity = 20;
  template< typename T, typename KEY >
  float const HashTable< T, KEY >::c_growRatio = 0.75;
  template< typename T, typename KEY >
  float const HashTable< T, KEY >::c_growMultiplier = 2.0;


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable() :
    Container< T >(),
    m_capacity( c_defaultCapacity ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( Hash::FastHash )
  {
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( T const * const tArray, unsigned const size ) :
    Container< T >(),
    m_capacity( size ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( Hash::FastHash )
  {
    PushBackRange( tArray, size );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( HashTable< T, KEY > const& hashTable ) :
    Container< T >(),
    m_capacity( hashTable.GetCapacity() ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( Hash::FastHash )
  {
    for( KeyedIterator kitB = hashTable.KeyedBegin(), kitE = hashTable.KeyedEnd(); kitB != kitE; ++kitB )
      Push( kitB.Get(), kitB.Key() );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( Container< T > const& container ) :
    Container< T >(),
    m_capacity( container.GetSize() ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( Hash::FastHash )
  {
    for( Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      PushBack( itB.Get() );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( HashFunc hashFunc ) :
    Container< T >(),
    m_capacity( c_defaultCapacity ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( hashFunc )
  {
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( T const * const tArray, unsigned const size, HashFunc hashFunc ) :
    Container< T >(),
    m_capacity( size ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( hashFunc )
  {
    PushBackRange( tArray, size );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( HashTable< T, KEY > const& hashTable, HashFunc hashFunc ) :
    Container< T >(),
    m_capacity( hashTable.GetCapacity() ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( hashFunc )
  {
    for( KeyedIterator kitB = hashTable.KeyedBegin(), kitE = hashTable.KeyedEnd(); kitB != kitE; ++kitB )
      Push( kitB.Get(), kitB.Key() );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::HashTable( Container< T > const& container, HashFunc hashFunc ) :
    Container< T >(),
    m_capacity( container.GetSize() ),
    m_buckets( new HashTableNode*[ m_capacity ]() ),
    m_hashFunc( hashFunc )
  {
    for( Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      PushBack( itB.Get() );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >& HashTable< T, KEY >::operator=( HashTable< T, KEY > const& hashTable )
  {
    Clear();

    m_capacity = hashTable.GetCapacity();
    m_buckets = new HashTableNode*[ m_capacity ];
    memset( m_buckets, 0, m_capacity * sizeof( HashTableNode* ) );
    
    for( KeyedIterator kitB = hashTable.KeyedBegin(), kitE = hashTable.KeyedEnd(); kitB != kitE; ++kitB )
      Push( kitB.Get(), kitB.Key() );

    return *this;
  }


  template< typename T, typename KEY >
  Container< T >& HashTable< T, KEY >::operator=( Container< T > const& container )
  {
    Clear();

    m_capacity = container.GetSize();
    m_buckets = new HashTableNode*[ m_capacity ];
    memset( m_buckets, 0, m_capacity * sizeof( HashTableNode* ) );

    for( Iterator itB = container.Begin(), itE = container.End(); itB != itE; ++itB )
      PushBack( itB.Get() );

    return *this;
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >::~HashTable()
  {
    Clear();
  }


  template< typename T, typename KEY >
  T& HashTable< T, KEY >::operator[]( KEY const& key ) const
  {
    unsigned const index = m_hashFunc( &key, m_capacity );
    HashTableNode* node = m_buckets[ index ];
    while( node != 0 && node->m_key != key )
      node = node->m_next;

    if( node == 0 )
      throw; // TODO: actually throw something

    return *( node->m_data );
  }


  template< typename T, typename KEY >
  HashTable< T, KEY > HashTable< T, KEY >::operator+( HashTable< T, KEY > const& hashTable ) const
  {
    HashTable< T, KEY > newTable( *this );
    
    for( KeyedIterator kitB = hashTable.KeyedBegin(), kitE = hashTable.KeyedEnd(); kitB != kitE; ++kitB )
      newTable.Push( kitB.Get(), kitB.Key() );

    return newTable;
  }


  template< typename T, typename KEY >
  HashTable< T, KEY >& HashTable< T, KEY >::operator+=( HashTable< T, KEY > const& hashTable )
  {
    for( KeyedIterator kitB = hashTable.KeyedBegin(), kitE = hashTable.KeyedEnd(); kitB != kitE; ++kitB )
      Push( kitB.Get(), kitB.Key() );

    return *this;
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::PushFront( T const& t )
  {
    unsigned tAddress = (unsigned)( &t );
    KEY key( tAddress );
    Push( t, key );
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::PushBack( T const& t )
  {
    unsigned tAddress = (unsigned)( &t );
    KEY key( tAddress );
    Push( t, key );
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::Push( T const& t, KEY const& key )
  {
    CheckAndGrow();
    Push( t, &key, m_buckets, m_capacity );
    ++m_size;
    InvalidateAllIteratorImplementations();
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::PopFront()
  {
    if( IsEmpty() )
      return;

    HashTableNode* node = 0;
    for( unsigned i = 0; i < m_capacity && node == 0; ++i )
      // we only want the very first node, so don't worry about walking the list
      node = m_buckets[ i ];

    if( node == 0 )
      throw; // TODO: actually throw something

    Pop( node->m_key );
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::PopBack()
  {
    if( IsEmpty() )
      return;

    HashTableNode* node = 0;
    for( unsigned i = m_capacity - 1; i >= 0 && node == 0; ++i )
    {
      node = m_buckets[ i ];
      // we want to get the last one, so walk all the way to the end of the list
      if( node != 0 )
        while( node->m_next != 0 )
          node = node->m_next;
    }

    if( node == 0 )
      throw; // TODO: actually throw something

    Pop( node->m_key );
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::PopFirst( T const& t )
  {
    if( IsEmpty() )
      return;

    HashTableNode* node = 0;

    for( unsigned i = 0; i < m_capacity; ++i )
    {
      node = m_buckets[ i ];
      while( node != 0 )
      {
        if( *( node->m_data ) == t )
        {
          // TODO:
          // this is a little slower than removing the node immediately; do we care?
          Pop( node->m_key );
          return;
        }
        else
          node = node->m_next;
      }
    }
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::PopAll( T const& t )
  {
    if( IsEmpty() )
      return;

    HashTableNode* node = 0;

    for( unsigned i = 0; i < m_capacity; ++i )
    {
      node = m_buckets[ i ];
      while( node != 0 )
      {
        if( *( node->m_data ) == t )
        {
          // TODO:
          // this is a little slower than removing the node immediately; do we care?
          Pop( node->m_key );
        }
        else
          node = node->m_next;
      }
    }
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::Pop( KEY const& key )
  {
    unsigned const index = m_hashFunc( &key, m_capacity );

    HashTableNode  *node = m_buckets[ index ],
            *prevNode = 0;

    while( node != 0 && node->m_key != key )
    {
      prevNode = node;
      node = node->m_next;
    }

    if( node == 0 )
      throw; // TODO: actually throw something

    if( prevNode != 0 )
      prevNode->m_next = node->m_next;

    delete node->m_data;
    delete node;

    --m_size;
    InvalidateAllIteratorImplementations();
  }

      
  template< typename T, typename KEY >
  Vector< KEY > HashTable< T, KEY >::GetKeys() const
  {
    Vector< KEY > vectorOfKeys( GetSize() );
    for( KeyedIterator kitB = KeyedBegin(), kitE = KeyedEnd(); kitB != kitE; ++kitB )
      vectorOfKeys.PushBack( kitB.Key() );
    return vectorOfKeys;
  }

      
  template< typename T, typename KEY >
  unsigned const HashTable< T, KEY >::GetCapacity() const
  {
    return m_capacity;
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::Clear()
  {
    Clear( m_buckets, m_capacity );
    m_size = 0;
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::Push( T const& t, void const * const key, HashTableNode** const buckets, unsigned const bucketArraySize )
  {
    KEY const* keyPointer = static_cast< KEY const* >( key );
    for( KeyedIterator kitB = KeyedBegin(), kitE = KeyedEnd(); kitB != kitE; ++kitB )
      if( kitB.Key() == *keyPointer )
        throw; // TODO: Throw something

    char* memLoc = new char[ sizeof( HashTableNode ) + sizeof( T ) ];
    
    T* newT = new( memLoc + sizeof( HashTableNode ) ) T( t );

    unsigned const index = m_hashFunc( key, bucketArraySize );
    HashTableNode  *next = buckets[ index ],
            *node = new( memLoc ) HashTableNode( next, newT, *keyPointer );
    buckets[ index ] = node;
  }

    
  template< typename T, typename KEY >
  void HashTable< T, KEY >::CheckAndGrow()
  {
    if( ( (float)m_size / (float)m_capacity ) > c_growRatio )
      Grow();
  }

    
  template< typename T , typename KEY >
  void HashTable< T, KEY >::Grow()
  {
    unsigned tempCapacity = ( m_capacity != 0 ) ? ( unsigned )( ( float )m_capacity * c_growMultiplier ) : c_defaultCapacity;
    HashTableNode** tempArray = new HashTableNode*[ tempCapacity ];

    for( KeyedIterator kitB = KeyedBegin(), kitE = KeyedEnd(); kitB != kitE; ++kitB )
      Push( kitB.Get(), &( kitB.Key() ), tempArray, tempCapacity );

    Clear( m_buckets, m_capacity );
    m_buckets = (HashTableNode**)tempArray;
    m_capacity = tempCapacity;
    InvalidateAllIteratorImplementations();
  }

      
  template< typename T, typename KEY >
  void HashTable< T, KEY >::Clear( HashTableNode**& buckets, unsigned& bucketArraySize )
  {
    HashTableNode* node = 0;
    for( unsigned i = 0; i < bucketArraySize; ++i )
    {
      node = buckets[ i ];
      while( node != 0 )
      {
        HashTableNode* temp = node;
        node = node->m_next;

        // we used placement new, so we only need to delete the HashTableNode*
        temp->m_data->~T();
        delete temp;
      }
    }

    delete buckets;
    buckets = 0;
    bucketArraySize = 0;
    InvalidateAllIteratorImplementations();
  }

}
