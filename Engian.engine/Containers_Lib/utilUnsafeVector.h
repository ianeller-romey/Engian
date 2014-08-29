
#ifndef UTIL_UNSAFEVECTOR_H
#define UTIL_UNSAFEVECTOR_H

#include "debugForTestDefines.h"

#include "utilVector.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilUnsafeVector;
}
#define TESTHELPER_UTILUNSAFEVECTOR_FRIEND friend class Test::TestHelper_UtilUnsafeVector
#else
#define TESTHELPER_UTILUNSAFEVECTOR_FRIEND
#endif


namespace Util
{

  template< typename T >
  class UnsafeVector : public Vector< T >
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILUNSAFEVECTOR_FRIEND;

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
