
#ifndef UTIL_DICTIONARY_H
#define UTIL_DICTIONARY_H

#include "utilHashTable.h"
#include "utilString.h"


namespace Util
{
  
  // Kind of a hack-y way to get around the void* constraint
  unsigned const DictionaryHash( void const* key, unsigned const upperLimit )
  {
    String const* stringPointer = static_cast< String const* >( key );
    return Hash::MurmurHash( *( *stringPointer ), upperLimit );
  }

  template< typename T >
  class Dictionary : public HashTable< T, String >
  {
    public:      
      //DEBUG_FUNC_TRACK_CLASS_DEC

      Dictionary();
      Dictionary( T const * const tArray, unsigned const size );
      Dictionary( Dictionary< T > const& dictionary );
      Dictionary( Container< T > const& container );
      virtual ~Dictionary();

      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void Push( T const& t, String const& key );
  };

}

#include "utilDictionary.inl"

#endif
