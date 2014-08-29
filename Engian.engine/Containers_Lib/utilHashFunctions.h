
#ifndef UTIL_HASHES_H
#define UTIL_HASHES_H


namespace Util
{

  namespace Hash
  {

    typedef unsigned const (*HashFunc) ( void const * const key, unsigned const upperLimit );

    unsigned const FastHash( void const * const key, unsigned const upperLimit );
    unsigned const MurmurHash( void const * const key, unsigned const upperLimit );

  }

}

#endif
