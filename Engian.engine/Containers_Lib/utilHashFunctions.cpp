
#include "utilHashFunctions.h"

#include "MurmurHash3.h"

#include <cstring>


namespace Util
{

  namespace Hash
  {
    
    unsigned const FastHash( void const * const key, unsigned const upperLimit )
    {
      unsigned const* keyPointer = static_cast< unsigned const* >( key );
      unsigned hash = *keyPointer;
      hash ^= hash >> 23;
      hash *= 0x2127599bf4325c37ULL;
      hash ^= hash >> 47;
      hash %= upperLimit;
      return hash;
    }


    unsigned const MurmurHash( void const * const key, unsigned const upperLimit )
    {
      char const* keyPointer = static_cast< char const* >( key );
      unsigned hash;
      MurmurHash3_x86_32( keyPointer, strlen( keyPointer ), 1, &hash );
      hash %= upperLimit;
      return hash;
    }

  }

}
