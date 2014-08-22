
#include "debugFunctionTracker.h"

#include <new>


namespace Debug
{

  FunctionTracker::FunctionTrackerNode::FunctionTrackerNode() :
    m_function( 0 ),
    m_next( 0 )
  {
  }


  bool const FunctionTracker::FunctionTrackerNode::operator==( char const * const function ) const
  {
    for( unsigned i = 0; m_function[ i ] != '\0' && function[ i ] != '\0'; ++i )
      if( m_function[ i ] != function[ i ] )
        return false;
    return true;
  }


  FunctionTracker::FunctionTracker() :
    m_front( 0 )
  {
  }


  FunctionTracker::~FunctionTracker()
  {
    Clear();
  }


  void FunctionTracker::Track( char const * const function )
  {
    unsigned functionLen = 0;
    for( ; function[ functionLen ] != '\0'; ++functionLen ) ;

    char* memory = new char[ sizeof( FunctionTrackerNode ) + ( sizeof( char ) * ( functionLen + 1 ) ) ];
    FunctionTrackerNode* node = new( memory ) FunctionTrackerNode();
    node->m_function = memory + sizeof( FunctionTrackerNode );
    for( unsigned i = 0; i <= functionLen; ++i )
      node->m_function[ i ] = function[ i ];
    node->m_next = m_front;

    m_front = node;
  }


  bool const FunctionTracker::Contains( char const * const function, bool clearAfter )
  {
    bool success = false;

    FunctionTrackerNode* node = m_front;
    for( ; node != 0; node = node->m_next )
    {
      if( ( *node ) == function )
      {
        success = true;
        break;
      }
    }

    if( clearAfter )
      Clear();

    return success;
  }


  void FunctionTracker::Clear()
  {
    while( m_front != 0 )
    {
      FunctionTrackerNode* node = m_front;
      m_front = m_front->m_next;
      delete node;
    }
  }

}
