
#ifndef UTIL_DICTIONARY_H
#define UTIL_DICTIONARY_H

#include "utilHashTable.h"
#include "utilString.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilDictionary;
}
#define TESTHELPER_UTILDICTIONARY_FRIEND friend class Test::TestHelper_UtilDictionary
#else
#define TESTHELPER_UTILDICTIONARY_FRIEND
#endif


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
      //DFT_FUNC_TRACK_CLASS_DEC
      TESTHELPER_UTILDICTIONARY_FRIEND;

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
