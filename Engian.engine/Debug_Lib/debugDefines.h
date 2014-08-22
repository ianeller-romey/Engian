
#ifndef DEBUG_DEFINES_H
#define DEBUG_DEFINES_H

#ifdef USE_DEBUG_LIB

#include "debugFunctionTracker.h"

#define DEBUG_FUNC_TRACK_CLASS_DEC static Debug::FunctionTracker s_functionTracker
#define DEBUG_FUNC_TRACK_CLASS_DEF( classDec ) Debug::FunctionTracker classDec ## ::s_functionTracker
#define DEBUG_FUNC_TRACK_CLASS_T_DEF( tDec, classDec ) tDec Debug::FunctionTracker classDec ## ::s_functionTracker
#define DEBUG_FUNC_TRACK( funcDec ) s_functionTracker.Track( funcDec )
#define DEBUG_FUNC_CHECK( classDec, function ) classDec ## ::s_functionTracker.Contains( function )
#define DEBUG_VAR_GET( var, type ) type dbgGet_ ## var() const { return var; }

#else

#define DEBUG_FUNC_TRACK_CLASS_DEC
#define DEBUG_FUNC_TRACK_CLASS_DEF( classDec )
#define DEBUG_FUNC_TRACK_CLASS_T_DEF( tDec, classDec )
#define DEBUG_FUNC_TRACK( funcDec )
#define DEBUG_FUNC_CHECK( classDec, function )
#define DEBUG_VAR_GET( var, type )

#endif

#endif
