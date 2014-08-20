
#ifndef UTIL_TEMPLATECOMPARISONFUNCTIONS_H
#define UTIL_TEMPLATECOMPARISONFUNCTIONS_H

#include "../Engian.test/Engian.test/testIcle.h"


namespace Util
{

  template< typename T >
  struct TemplateComparisonFunctions
  {
    typedef bool const (*EqualityFunc) ( T const&, T const& );
    typedef bool const (*GreaterThanFunc) ( T const&, T const& );
    typedef bool const (*LessThanFunc) ( T const&, T const& );

    static bool const DefaultEquals( T const& left, T const& right );
    static bool const DefaultGreaterThan( T const& left, T const& right );
    static bool const DefaultLessThan( T const& left, T const& right );
  };

}

#include "utilTemplateComparisonFunctions.inl"

#endif
