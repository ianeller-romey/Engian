
#ifndef DEBUGFORTEST_DEFINES_H
#define DEBUGFORTEST_DEFINES_H

#ifdef USE_DFT_LIB

#include "debugForTestFunctionTracker.h"

#define DFT_FUNC_TRACK_CLASS_DEC static DebugForTest::FunctionTracker s_functionTracker
#define DFT_FUNC_TRACK( funcDec ) s_functionTracker.Track( funcDec )
#define DFT_FUNC_CHECK( classDec, function ) classDec ## ::s_functionTracker.Contains( function )

#else

#define DFT_FUNC_TRACK_CLASS_DEC
#define DFT_FUNC_TRACK( funcDec ) ((void)0)
#define DFT_FUNC_CHECK( classDec, function ) ((void)0)

#endif

#endif
