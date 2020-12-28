
#ifndef UTIL_KEYVALUEPAIR_H
#define UTIL_KEYVALUEPAIR_H

namespace Util
{

  template< typename T1, typename T2 >
  struct KeyValuePair
  {
    T1 m_v1;
    T2 m_v2;
  };

}

#endif
