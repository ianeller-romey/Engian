
#ifndef UTIL_NPLE_H
#define UTIL_NPLE_H

namespace Util
{

  template< typename T, unsigned N >
  struct Nple
  {
    Nple();
    Nple( T* values );
    Nple( Nple const& nple );

    Nple& operator=( Nple const& nple );


    T m_values[ N ];
  };


  template< typename T >
  Nple< T, 2 > CreateTuple();
  template< typename T >
  Nple< T, 2 > CreateTuple( T* values );
  template< typename T >
  Nple< T, 2 > CreateTuple( T value1, T value2 );

  template< typename T >
  Nple< T, 3 > CreateThreeple();
  template< typename T >
  Nple< T, 3 > CreateThreeple( T* values );
  template< typename T >
  Nple< T, 3 > CreateThreeple( T value1, T value2, T value3 );

}

#include "utilNple.inl"

#endif
