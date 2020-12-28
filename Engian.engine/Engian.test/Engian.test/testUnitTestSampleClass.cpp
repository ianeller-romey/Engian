
#include "testUnitTestSampleClass.h"

#include <cstring>


namespace Test
{
  
  UnitTestSampleClass::UnitTestSampleClass() :
    m_string( 0 ),
    m_int( 0 )
  {
  }


  UnitTestSampleClass::UnitTestSampleClass( char const * const string, int i, UnitTestSampleStruct utss ) :
    m_int( i ),
    m_struct( utss )
  {
    unsigned strLen = strlen( string ) + sizeof( char );
    m_string = new char[ strLen ];
    memcpy( m_string, string, strLen );
  }


  UnitTestSampleClass::UnitTestSampleClass( UnitTestSampleClass const& other ) :
    m_string( 0 ),
    m_int( other.m_int ),
    m_struct( other.m_struct )
  {
    unsigned strLen = strlen( other.m_string ) + sizeof( char );
    m_string = new char[ strLen ];
    memcpy( m_string, other.m_string, strLen );
  }


  UnitTestSampleClass& UnitTestSampleClass::operator=( UnitTestSampleClass const& other )
  {
    if( m_string != 0 )
      delete [] m_string;
    m_string = 0;
    m_int = other.m_int;
    m_struct = other.m_struct;

    unsigned strLen = strlen( other.m_string ) + sizeof( char );
    m_string = new char[ strLen ];
    memcpy( m_string, other.m_string, strLen );

    return *this;
  }


  UnitTestSampleClass::~UnitTestSampleClass()
  {
    if( m_string != 0 )
      delete [] m_string;
  }


  bool const UnitTestSampleClass::operator==( UnitTestSampleClass const& other ) const
  {
    return strcmp( m_string, other.m_string ) == 0 && m_int == other.m_int && m_struct == other.m_struct;
  }


  bool const UnitTestSampleClass::operator!=( UnitTestSampleClass const& other ) const
  {
    return !( *this == other );
  }


  bool const UnitTestSampleClass::operator>( UnitTestSampleClass const& other ) const
  {
    return Sum() > other.Sum();
  }


  bool const UnitTestSampleClass::operator<( UnitTestSampleClass const& other ) const
  {
    return Sum() < other.Sum();
  }


  bool const UnitTestSampleClass::operator>=( UnitTestSampleClass const& other ) const
  {
    return Sum() >= other.Sum();
  }


  bool const UnitTestSampleClass::operator<=( UnitTestSampleClass const& other ) const
  {
    return Sum() <= other.Sum();
  }


  double const UnitTestSampleClass::Sum() const
  {
    return strlen( m_string ) + m_int + m_struct.Sum();
  }


  void UnitTestSampleClass::UpdateAnArray( UnitTestSampleClass* array, unsigned const arraySize )
  {
    for( unsigned i = 0; i < arraySize; ++i )
    {
      unsigned const strLen = 10 + 1;
      char strChar = (char)i;
      if( strChar == '\0' )
        ++strChar;
      char str[ strLen ];
      for( unsigned j = 0; j < strLen - 1 ; ++j )
        str[ j ] = strChar;
      str[ strLen - 1 ] = '\0';
      array[ i ] = UnitTestSampleClass( str, i, UnitTestSampleStruct( 0 - (int)i, i, 0, NULL ) );
    }
  }

}
