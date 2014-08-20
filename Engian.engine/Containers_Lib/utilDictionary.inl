
#include "utilHashFunctions.h"


namespace Util
{

  template< typename T >
  Dictionary< T >::Dictionary() :
    HashTable< T, String >( DictionaryHash )
  {
  }


  template< typename T >
  Dictionary< T >::Dictionary( T const * const tArray, unsigned const size ) :
    HashTable< T, String >( tArray, size, DictionaryHash )
  {
  }

  
  template< typename T >
  Dictionary< T >::Dictionary( Dictionary< T > const& hashTable ) :
    HashTable< T, String >( hashTable, DictionaryHash )
  {
  }

  
  template< typename T >
  Dictionary< T >::Dictionary( Container< T > const& container ) :
    HashTable< T, String >( container, DictionaryHash )
  {
  }
  

  template< typename T >
  Dictionary< T >::~Dictionary()
  {
    Clear();
  }
      
  template< typename T >
  void Dictionary< T >::PushFront( T const& t )
  {
    unsigned n = ( unsigned )( &t );
    String keyString;
    keyString << n;
    Push( t, keyString );
  }

      
  template< typename T >
  void Dictionary< T >::PushBack( T const& t )
  {
    unsigned n = ( unsigned )( &t );
    String keyString;
    keyString << n;
    Push( t, keyString );
  }


  template< typename T >
  void Dictionary< T >::Push( T const& t, String const& key )
  {
    CheckAndGrow();
    HashTable< T, String >::Push( t, &key, m_buckets, m_capacity );
    ++m_size;
    InvalidateAllIteratorImplementations();
  }

}
