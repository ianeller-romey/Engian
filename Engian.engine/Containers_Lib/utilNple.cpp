
#include "utilNple.h"

namespace Util
{

  template< typename T >
  Nple< T, 2 > CreateTuple()
  {
    return Nple< T, 2 >();
  }


  template< typename T >
  Nple< T, 2 > CreateTuple( T* values )
  {
    return Nple< T, 2 >( values );
  }


  template< typename T >
  Nple< T, 2 > CreateTuple( T value1, T value2 )
  {
    Nple< T, 2 > nple;
    nple[ 0 ] = value1;
    nple[ 1 ] = value2;
    return nple;
  }


  template< typename T >
  Nple< T, 3 > CreateThreeple()
  {
    return Nple< T, 3 >();
  }


  template< typename T >
  Nple< T, 3 > CreateThreeple( T* values )
  {
    return Nple< T, 3 >( values );
  }


  template< typename T >
  Nple< T, 3 > CreateThreeple( T value1, T value2, T value3 )
  {
    Nple< T, 3 > nple;
    nple.m_values[ 0 ] = value1;
    nple.m_values[ 1 ] = value2;
    nple.m_values[ 2 ] = valuue3;
    return nple;
  }

}
