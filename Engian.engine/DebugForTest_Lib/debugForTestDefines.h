
#ifndef DEBUGFORTEST_DEFINES_H
#define DEBUGFORTEST_DEFINES_H

#ifdef USE_DFT_LIB

#include "debugForTestFunctionTracker.h"

#define DFT_FUNC_TRACK_CLASS_DEC static Debug::FunctionTracker s_functionTracker
#define DFT_FUNC_TRACK( funcDec ) s_functionTracker.Track( funcDec )
#define DFT_FUNC_CHECK( classDec, function ) classDec ## ::s_functionTracker.Contains( function )
#define DFT_VAR_GET( var, type ) type dbgGet_ ## var() const { return var; }
#define DFT_S_VAR_GET( var, type ) static type dbgGet_ ## var() { return var; }

namespace Test
{
  template< typename HELPER > struct TestHelper_UtilVector;
  template< typename HELPER > struct TestHelper_UtilSortedVector;
  struct TestHelper_UtilString;
  template< typename HELPER > struct TestHelper_UtilList;
}

#define DFT_UTILVECTOR_FRIEND       friend class TestHelper_UtilVector;
#define DFT_UTILSORTEDVECTOR_FRIEND friend class TestHelper_UtilSortedVector;
#define DFT_UTILSTRING_FRIEND       friend class TestHelper_UtilString;
#define DFT_UTILLIST_FRIEND         friend class TestHelper_UtilList;

#else

#define DFT_FUNC_TRACK_CLASS_DEC
#define DFT_FUNC_TRACK( funcDec ) { ; }
#define DFT_FUNC_CHECK( classDec, function ) { ; }
#define DFT_VAR_GET( var, type )
#define DFT_S_VAR_GET( var, type )

#define DFT_UTILVECTOR_FRIEND
#define DFT_UTILSORTEDVECTOR_FRIEND
#define DFT_UTILSTRING_FRIEND
#define DFT_UTILLIST_FRIEND

#endif

#endif
