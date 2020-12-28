
namespace Util
{

  template< typename T, unsigned N >
  Nple< T, N >::Nple()
  {
  }


  template< typename T, unsigned N >
  Nple< T, N >::Nple( T* values )
  {
    for( auto i = 0; i < N; ++i )
    {
      m_values[ i ] = values[ i ];
    }
  }


  template< typename T, unsigned N >
  Nple< T, N >::Nple( Nple< T, N > const& nple )
  {
    for( auto i = 0; i < N; ++i )
    {
      m_values[ i ] = nple.m_values[ i ];
    }
  }


  template< typename T, unsigned N >
  Nple< T, N >& Nple< T, N >::operator=( Nple< T, N > const& nple )
  {
    for( auto i = 0; i < N; ++i )
    {
      m_values[ i ] = nple.m_values[ i ];
    }

    return *this;
  }

}
