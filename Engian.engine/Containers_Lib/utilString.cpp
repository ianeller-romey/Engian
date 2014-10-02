
#include "utilString.h"

#include <cstring>


namespace Util
{
    
  String::String() :
    UnsafeVector< char >()
  {
    DFT_FUNC_TRACK( "String::String()" );
    MakeEmptyString();
  }


  String::String( unsigned const capacity ) :
    UnsafeVector< char >( capacity )
  {
    DFT_FUNC_TRACK( "String::String( unsigned const capacity )" );
    MakeEmptyString();
  }


  String::String( char const * const string ) :
    UnsafeVector< char >( string, strlen( string ) + 1 )
  {
    DFT_FUNC_TRACK( "String::String( char const * const string )" );
  }


  String::String( char const character ) :
    UnsafeVector< char >( 2 )
  {
    DFT_FUNC_TRACK( "String::String( char const character )" );
    m_array[ 0 ] = character;
    m_array[ 1 ] = '\0';
    m_size = 2;
  }


  String::String( String const& string ) :
    UnsafeVector( string )
  {
    DFT_FUNC_TRACK( "String::String( String const& string )" );
  }


  String::String( Container< char > const& container ) :
    UnsafeVector( container.GetSize() )
  {
    DFT_FUNC_TRACK( "String::String( Container< char > const& container )" );
    MakeEmptyString();
    Vector< char >::PushBackRange( container );
  }


  String& String::operator=( char const * const string )
  {
    DFT_FUNC_TRACK( "String& String::operator=( char const * const string )" );
    Deallocate();
    
    m_capacity = strlen( string ) + 1;
    m_size = m_capacity;
    m_array = new char[ m_capacity ];
    memcpy( m_array, string,  sizeof( char ) * m_size );

    return *this;
  }


  String& String::operator=( char const character )
  {
    DFT_FUNC_TRACK( "String& String::operator=( char const character )" );
    Deallocate();
    
    m_capacity = 2;
    m_size = m_capacity;
    m_array = new char[ m_capacity ];
    m_array[ 0 ] = character;
    m_array[ 1 ] = '\0';

    return *this;
  }


  String& String::operator=( String const& string )
  {
    DFT_FUNC_TRACK( "String& String::operator=( String const& string )" );
    Deallocate();
    
    m_capacity = string.m_size;
    m_size = m_capacity;
    m_array = new char[ m_capacity ];
    memcpy( m_array, string.m_array, sizeof( char ) * m_size );

    return *this;
  }


  Container< char >& String::operator=( Container< char > const& container )
  {
    DFT_FUNC_TRACK( "Container< char >& String::operator=( Container< char > const& container )" );
    Deallocate();
    
    m_capacity = container.GetSize() + 1;
    m_array = new char[ m_capacity ];
    MakeEmptyString();
    Vector< char >::PushBackRange( container );

    return *this;
  }


  String::~String()
  {
    DFT_FUNC_TRACK( "String::~String()" );
    Deallocate();
    InvalidateAllIteratorImplementations();
  }


  String::operator const char *() const
  {
    DFT_FUNC_TRACK( "String::operator const char *() const" );
    return m_array;
  }


  bool const String::operator==( char const * const string ) const
  {
    DFT_FUNC_TRACK( "bool const String::operator==( char const * const string ) const" );
    return strcmp( m_array, string ) == 0;
  }


  bool const String::operator==( char const character ) const
  {
    DFT_FUNC_TRACK( "bool const String::operator==( char const character ) const" );
    return GetStrLen() == 1 && m_array[ 0 ] == character;
  }


  bool const String::operator==( String const& string ) const
  {
    DFT_FUNC_TRACK( "bool const String::operator==( String const& string ) const" );
    return m_size == string.m_size && strcmp( m_array, string.m_array ) == 0;
  }


  bool const String::operator!=( char const * const string ) const
  {
    DFT_FUNC_TRACK( "bool const String::operator!=( char const * const string ) const" );
    return strcmp( m_array, string ) != 0;
  }


  bool const String::operator!=( char const character ) const
  {
    DFT_FUNC_TRACK( "bool const String::operator!=( char const character ) const" );
    return GetStrLen() != 1 || m_array[ 0 ] != character;
  }


  bool const String::operator!=( String const& string ) const
  {
    DFT_FUNC_TRACK( "bool const String::operator!=( String const& string ) const" );
    return m_size != string.m_size || strcmp( m_array, string.m_array ) != 0;
  }


  String String::operator+( char const * const string ) const
  {
    DFT_FUNC_TRACK( "String String::operator+( char const * const string ) const" );
    String newString( *this );
    newString.PushBackRange( string, strlen( string ) );
    return newString;
  }


  String String::operator+( char const character ) const
  {
    DFT_FUNC_TRACK( "String String::operator+( char const character ) const" );
    String newString( *this );
    newString.PushBack( character );
    return newString;
  }


  String String::operator+( String const& string ) const
  {
    DFT_FUNC_TRACK( "String String::operator+( String const& string ) const" );
    String newString( *this );
    newString.PushBackRange( string );
    return newString;
  }


  String String::operator+( Container< char > const& container ) const
  {
    DFT_FUNC_TRACK( "String String::operator+( Container< char > const& container ) const" );
    String newString( *this );
    newString.PushBackRange( container );
    return newString;
  }


  String& String::operator+=( char const * const string )
  {
    DFT_FUNC_TRACK( "String& String::operator+=( char const * const string )" );
    PushBackRange( string, strlen( string ) );
    return *this;
  }


  String& String::operator+=( char const character )
  {
    DFT_FUNC_TRACK( "String& String::operator+=( char const character )" );
    PushBack( character );
    return *this;
  }  


  String& String::operator+=( String const& string )
  {
    DFT_FUNC_TRACK( "String& String::operator+=( String const& string )" );
    PushBackRange( string );
    return *this;
  }


  String& String::operator<<( int const integer )
  {
    DFT_FUNC_TRACK( "String& String::operator<<( int const integer )" );
    // TODO: this can be optimized
    for( int n = ( integer < 0 ) ? -integer : integer; n; n /= 10 )
      PushFront( ( n % 10 ) + 48 );
    if( integer < 0 )
      PushFront( '-' );
    return *this;
  }


  String& String::operator<<( unsigned const uinteger )
  {
    DFT_FUNC_TRACK( "String& String::operator<<( unsigned const uinteger )" );
    for( unsigned n = uinteger; n; n /= 10 )
      PushFront( ( n % 10 ) + 48 );
    return *this;
  }


  void String::PushBack( char const& t )
  {
    DFT_FUNC_TRACK( "void String::PushBack( char const& t )" );
    CheckAndGrow();
    m_array[ m_size - 1 ] = t;
    m_array[ m_size++ ] = '\0';
    InvalidateAllIteratorImplementations();
  }

    
  void String::PushBackRange( char const * const string )
  {
    DFT_FUNC_TRACK( "void String::PushBackRange( char const * const string )" );
    PushBackRange( string, strlen( string ) );
  }

    
  void String::PushBackRange( char const * const string, unsigned const strLen )
  {
    DFT_FUNC_TRACK( "void String::PushBackRange( char const * const tArray, unsigned const size )" );
    while( ( m_size + strLen + 1 ) >= m_capacity )
      Grow();
    char* copyTo = m_array + m_size - 1;
    memcpy( copyTo, string, sizeof( char ) * strLen );
    copyTo[ strLen ] = '\0';
    m_size += strLen;
    InvalidateAllIteratorImplementations();
  }

    
  void String::PushBackRange( String const& string )
  {
    DFT_FUNC_TRACK( "void String::PushBackRange( String const& string )" );
    PushBackRange( string.m_array, string.GetStrLen() );
  }


  void String::PopBack()
  {
    DFT_FUNC_TRACK( "void String::PopBack()" );
    if( IsEmpty() )
      return;
    --m_size;
    m_array[ m_size - 1 ] = '\0';
  }



  unsigned const String::GetStrLen() const
  {
    DFT_FUNC_TRACK( "unsigned const String::GetStrLen() const" );
    return m_size - 1;
  }


  bool const String::BeginsWith( char const * const string ) const
  {
    DFT_FUNC_TRACK( "bool const String::BeginsWith( char const * const string ) const" );
    int strLen = strlen( string );
    return BeginsWith( string, strLen );
  }


  bool const String::BeginsWith( char const character ) const
  {
    DFT_FUNC_TRACK( "bool const String::BeginsWith( char const character ) const" );
    return m_array[ 0 ] == character;
  }


  bool const String::BeginsWith( char const * const string, unsigned strLen ) const
  {
    DFT_FUNC_TRACK( "bool const String::BeginsWith( char const * const string, unsigned strLen ) const" );
    if( GetStrLen() < strLen )
      return false;
    return strncmp( m_array, string, strLen ) == 0;
  }


  bool const String::BeginsWith( String const& string ) const
  {
    DFT_FUNC_TRACK( "bool const String::BeginsWith( String const& string ) const" );
    return BeginsWith( string.m_array, string.GetStrLen() );
  }


  bool const String::BeginsWith( Container< char > const& container ) const
  {
    DFT_FUNC_TRACK( "bool const String::BeginsWith( Container< char > const& container ) const" );
    if( GetStrLen() < container.GetSize() )
      return false;
    Container< char >::Iterator itB = container.Begin(),
                                itE = container.End();
    for( unsigned i = 0, j = GetStrLen(); i < j && itB != itE; ++i, ++itB )
      if( m_array[ i ] != itB.Get() )
        return false;
    return true;
  }


  bool const String::EndsWith( char const * const string ) const
  {
    DFT_FUNC_TRACK( "bool const String::EndsWith( char const * const string ) const" );
    int strLen = strlen( string );
    return EndsWith( string, strLen );
  }


  bool const String::EndsWith( char const character ) const
  {
    DFT_FUNC_TRACK( "bool const String::EndsWith( char const character ) const" );
    return m_array[ GetStrLen() - 1 ] == character;
  }


  bool const String::EndsWith( char const * const string, unsigned strLen ) const
  {
    DFT_FUNC_TRACK( "bool const String::EndsWith( char const * const string, unsigned strLen ) const" );
    if( GetStrLen() < strLen )
      return false;
    return strncmp( m_array + ( GetStrLen() - strLen ), string, strLen ) == 0;
  }


  bool const String::EndsWith( String const& string ) const
  {
    DFT_FUNC_TRACK( "bool const String::EndsWith( String const& string ) const" );
    return EndsWith( string.m_array, string.GetStrLen() );
  }


  bool const String::EndsWith( Container< char > const& container ) const
  {
    DFT_FUNC_TRACK( "bool const String::EndsWith( Container< char > const& container ) const" );
    if( GetStrLen() < container.GetSize() )
      return false;
    Container< char >::Iterator itB = container.Begin(),
                                itE = container.End();
    for( unsigned j = GetStrLen(), i = j - container.GetSize(); i < j && itB != itE; ++i, ++itB )
      if( m_array[ i ] != itB.Get() )
        return false;
    return true;
  }


  bool const String::IsEmpty() const
  {
    DFT_FUNC_TRACK( "bool const String::IsEmpty() const" );
    return m_size == 1;
  }
  
      
  void String::Clear()
  {
    DFT_FUNC_TRACK( "void String::Clear()" );
    MakeEmptyString();
  }


  void String::Clear( unsigned const newCapacity )
  {
    DFT_FUNC_TRACK( "void String::Clear( unsigned const newCapacity )" );
    if( m_array != 0 )
      delete m_array;
    m_capacity = newCapacity;
    m_array = new char[ m_capacity ];
    MakeEmptyString();
  }


  void String::MakeEmptyString()
  {
    DFT_FUNC_TRACK( "void String::MakeEmptyString()" );
    m_array[ 0 ] = '\0';
    m_size = 1;
    InvalidateAllIteratorImplementations();
  }
  
      
  void String::Deallocate()
  {
    DFT_FUNC_TRACK( "void String::Deallocate()" );

    if( m_array != 0 )
    {
      delete [] m_array;
      m_array = 0;
    }

    m_capacity = 0;
    m_size = 0;
  }

}
