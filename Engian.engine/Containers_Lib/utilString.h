
#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include "debugForTestDefines.h"

#include "utilUnsafeVector.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilString;
}
#define TESTHELPER_UTILSTRING_FRIEND friend class Test::TestHelper_UtilString
#else
#define TESTHELPER_UTILSTRING_FRIEND
#endif


namespace Util
{

  class String : public UnsafeVector< char >
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILSTRING_FRIEND;

      String();
      String( unsigned const capacity );
      String( char const * const string );
      String( char const character );
      String( String const& string );
      String( Container< char > const& container );
      String& operator=( char const * const string );
      String& operator=( char const character );
      String& operator=( String const& string );
      Container< char >& operator=( Container< char > const& container );
      virtual ~String();
      
      virtual operator char const *() const;
      virtual bool const operator==( char const * const string ) const;
      virtual bool const operator==( char const character ) const;
      virtual bool const operator==( String const& string ) const;
      virtual bool const operator!=( char const * const string ) const;
      virtual bool const operator!=( char const character ) const;
      virtual bool const operator!=( String const& string ) const;
      virtual String operator+( char const * const string ) const;
      virtual String operator+( char const character ) const;
      virtual String operator+( String const& string ) const;
      virtual String operator+( Container< char > const& container ) const;
      virtual String& operator+=( char const * const string );
      virtual String& operator+=( char const character );
      virtual String& operator+=( String const& string );
      virtual String& operator<<( int const integer );
      virtual String& operator<<( unsigned const uinteger );

      virtual void PushBack( char const& t );
      virtual void PushBackRange( char const * const string );
      virtual void PushBackRange( char const * const string, unsigned const strLen );
      virtual void PushBackRange( String const& string );
      virtual void PopBack();

      unsigned const GetStrLen() const;

      bool const BeginsWith( char const * const string ) const;
      bool const BeginsWith( char const character ) const;
      bool const BeginsWith( char const * const string, unsigned strLen ) const;
      bool const BeginsWith( String const& string ) const;
      bool const BeginsWith( Container< char > const& container ) const;
      bool const EndsWith( char const * const string ) const;
      bool const EndsWith( char const character ) const;
      bool const EndsWith( char const * const string, unsigned strLen ) const;
      bool const EndsWith( String const& string ) const;
      bool const EndsWith( Container< char > const& container ) const;

      virtual bool const IsEmpty() const;

      virtual void Clear();


    protected:
      void MakeEmptyString();
      void Deallocate();
  };

}

#endif
