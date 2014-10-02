
#ifndef UTIL_SORTER_H
#define UTIL_SORTER_H

#include "debugForTestDefines.h"

#include "utilTemplateComparisonFunctions.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilSorter;
}
#define TESTHELPER_UTILSORTER_FRIEND friend class Test::TestHelper_UtilSorter
#else
#define TESTHELPER_UTILSORTER_FRIEND
#endif


namespace Util
{

  template< typename T >
  class Sorter
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILSORTER_FRIEND;

      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );


      Sorter( EqualityFunc    const equalityFunc    = TemplateComparisonFunctions< T >::DefaultEquals, 
              GreaterThanFunc const greaterThanFunc = TemplateComparisonFunctions< T >::DefaultGreaterThan, 
              LessThanFunc    const lessThanFunc    = TemplateComparisonFunctions< T >::DefaultLessThan ) :
        m_equalityFunc( equalityFunc ),
        m_greaterThanFunc( greaterThanFunc ),
        m_lessThanFunc( lessThanFunc )
      {
      }


      virtual ~Sorter()
      {
      }


    protected:
      EqualityFunc const    m_equalityFunc;
      GreaterThanFunc const m_greaterThanFunc;
      LessThanFunc const    m_lessThanFunc;
  };

}

#endif
