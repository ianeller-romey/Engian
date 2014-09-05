
#ifndef UTIL_SORTEDCONTAINER_H
#define UTIL_SORTEDCONTAINER_H

#include "debugForTestDefines.h"

#include "utilContainer.h"
#include "utilTemplateComparisonFunctions.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilSortedContainer;
}
#define TESTHELPER_UTILSORTEDCONTAINER_FRIEND friend class Test::TestHelper_UtilSortedContainer
#else
#define TESTHELPER_UTILSORTEDCONTAINER_FRIEND
#endif


namespace Util
{

  template< typename T >
  class SortedContainer : public virtual Container< T >
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILSORTEDCONTAINER_FRIEND;

      typedef bool const (*EqualityFunc) ( T const&, T const& );
      typedef bool const (*GreaterThanFunc) ( T const&, T const& );
      typedef bool const (*LessThanFunc) ( T const&, T const& );


      SortedContainer( EqualityFunc const equalityFunc = TemplateComparisonFunctions< T >::DefaultEquals, 
                       GreaterThanFunc const greaterThanFunc = TemplateComparisonFunctions< T >::DefaultGreaterThan, 
                       LessThanFunc const lessThanFunc = TemplateComparisonFunctions< T >::DefaultLessThan ) :
        Container< T >(),
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
