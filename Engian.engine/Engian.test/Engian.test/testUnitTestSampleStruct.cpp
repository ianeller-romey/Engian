
#include "testUnitTestSampleStruct.h"

#include <cstring>
#include <cstdlib>


namespace Test
{
  
  unsigned UnitTestSampleStruct::s_numberOfDeletes = 0;

  
  UnitTestSampleStruct::UnitTestSampleStruct() :
    m_int1( 0 ),
    m_int2( 0 ),
    m_int3( 0 ),
    m_referenceCount( new unsigned( 1 ) )
  {
    for( unsigned i = 0; i < 5; ++i )
      m_doubles[ i ] = 0.0;

  }


  UnitTestSampleStruct::UnitTestSampleStruct( int int1, int int2, int int3, double* doubles ) :
    m_int1( int1 ),
    m_int2( int2 ),
    m_int3( int3 ),
    m_referenceCount( new unsigned( 1 ) )
  {
    if( doubles != 0 )
      for( unsigned i = 0; i < 5; ++i )
        m_doubles[ i ] = doubles[ i ];
    else
      for( unsigned i = 0; i < 5; ++i )
        m_doubles[ i ] = 0.0;
  }


  UnitTestSampleStruct::UnitTestSampleStruct( UnitTestSampleStruct const& other ) :
    m_int1( other.m_int1 ),
    m_int2( other.m_int2 ),
    m_int3( other.m_int3 ),
    m_referenceCount( other.m_referenceCount )
  {
    memcpy( m_doubles, other.m_doubles, sizeof( double ) * 5 );
    ++( *m_referenceCount );
  }


  
  UnitTestSampleStruct& UnitTestSampleStruct::operator=( UnitTestSampleStruct const& other )
  {
    m_int1 = other.m_int1;
    m_int2 = other.m_int2;
    m_int3 = other.m_int3;
    m_referenceCount = other.m_referenceCount;
    memcpy( m_doubles, other.m_doubles, sizeof( double ) * 5 );
    ++( *m_referenceCount );
    return *this;
  }


  UnitTestSampleStruct::~UnitTestSampleStruct()
  {
    if( --( *m_referenceCount ) <= 0 )
    {
      delete m_referenceCount;
      ++s_numberOfDeletes;
    }
  }


  bool const UnitTestSampleStruct::operator==( UnitTestSampleStruct const& other ) const
  {
    if( m_int1 != other.m_int1 ||
      m_int2 != other.m_int2 ||
      m_int3 != other.m_int3 )
      return false;
    for( unsigned i = 0; i < 5; ++i )
      if( m_doubles[ i ] != other.m_doubles[ i ] )
        return false;
    return true;
  }


  bool const UnitTestSampleStruct::operator!=( UnitTestSampleStruct const& other ) const
  {
    return !( *this == other );
  }


  bool const UnitTestSampleStruct::operator>( UnitTestSampleStruct const& other ) const
  {
    return Sum() > other.Sum();
  }


  bool const UnitTestSampleStruct::operator<( UnitTestSampleStruct const& other ) const
  {
    return Sum() < other.Sum();
  }


  bool const UnitTestSampleStruct::operator>=( UnitTestSampleStruct const& other ) const
  {
    return Sum() >= other.Sum();
  }


  bool const UnitTestSampleStruct::operator<=( UnitTestSampleStruct const& other ) const
  {
    return Sum() <= other.Sum();
  }


  int const UnitTestSampleStruct::Sum() const
  {
    return m_int1 + m_int2 + m_int3 + m_doubles[ 0 ] + m_doubles[ 1 ] + m_doubles[ 2 ] + m_doubles[ 3 ] + m_doubles[ 4 ];
  }


  void UnitTestSampleStruct::UpdateAnArray( UnitTestSampleStruct* array, unsigned const arraySize )
  {
    for( unsigned i = 0; i < arraySize; ++i )
    {
      array[ i ].m_int1 = i;
      array[ i ].m_int2 = arraySize - i;
      array[ i ].m_int3 = rand();
    }
  }

}
