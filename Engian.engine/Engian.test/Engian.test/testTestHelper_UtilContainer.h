
#ifndef TEST_TESTHELPER_UTILCONTAINER_H
#define TEST_TESTHELPER_UTILCONTAINER_H

#include "utilContainer.h"


namespace Test
{  

  class TestHelper_UtilContainer
  {
    public:
      template< typename T >
      static unsigned const GetUtilContainerSize( Util::Container< T > const& container )
      {
        return container.m_size;
      }
  };

}

#endif
