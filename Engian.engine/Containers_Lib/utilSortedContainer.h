
#ifndef UTIL_SORTEDCONTAINER_H
#define UTIL_SORTEDCONTAINER_H

#include "debugDefines.h"

#include "utilContainer.h"
#include "utilTemplateComparisonFunctions.h"


namespace Util
{

  template< typename T >
  class SortedContainer : public virtual Container< T >
  {
    public:
      //DEBUG_FUNC_TRACK_CLASS_DEC
      DEBUG_VAR_GET( m_equalityFunc, EqualityFunc )
      DEBUG_VAR_GET( m_greaterThanFunc, GreaterThanFunc )
      DEBUG_VAR_GET( m_lessThanFunc, LessThanFunc )

      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );


      SortedContainer( EqualityFunc const equalityFunc = TemplateComparisonFunctions< T >::DefaultEquals, 
                       GreaterThanFunc const greaterThanFunc = TemplateComparisonFunctions< T >::DefaultGreaterThan, 
                       LessThanFunc const lessThanFunc = TemplateComparisonFunctions< T >::DefaultLessThan ) :
        m_equalityFunc( equalityFunc ),
        m_greaterThanFunc( greaterThanFunc ),
        m_lessThanFunc( lessThanFunc )
      {
      }


      virtual ~SortedContainer()
      {
      }


    protected:
      EqualityFunc const    m_equalityFunc;
      GreaterThanFunc const m_greaterThanFunc;
      LessThanFunc const    m_lessThanFunc;
  };

}

#endif
