
#ifndef UTIL_UNSAFEVECTOR_H
#define UTIL_UNSAFEVECTOR_H

#include "debugDefines.h"

#include "utilVector.h"


namespace Util
{

  template< typename T >
  class UnsafeVector : public Vector< T >
  {
    public:
      //DEBUG_FUNC_TRACK_CLASS_DEC

      UnsafeVector();
      UnsafeVector( unsigned const capacity );
      UnsafeVector( T const * const tArray, unsigned const size );
      UnsafeVector( UnsafeVector< T > const& Vector );
      UnsafeVector( Container< T > const& container );
      virtual UnsafeVector< T >& operator=( UnsafeVector< T > const& uVector );
      virtual Container< T >& operator=( Container< T > const& container );
      virtual ~UnsafeVector();

      virtual void PushFront( T const& t );
      virtual void PushBackRange( T const * const tArray, unsigned const size );
      virtual void PushBackRange( UnsafeVector< T > const& vector );


    protected:
      ////////
      // helper functions
      virtual void Grow();

      virtual void ShiftAndPop( unsigned const startIndex );
  };

}

#include "utilUnsafeVector.inl"

#endif
