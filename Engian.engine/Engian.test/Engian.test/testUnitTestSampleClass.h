
#ifndef TEST_UNITTESTSAMPLECLASS_H
#define TEST_UNITTESTSAMPLECLASS_H

#include "testUnitTestSampleStruct.h"


namespace Test
{  

  class UnitTestSampleClass
  {
    private:
      char* m_string;
      int m_int;
      UnitTestSampleStruct m_struct;


    public:
      UnitTestSampleClass();
      UnitTestSampleClass( char const * const string, int i, UnitTestSampleStruct utss );
      UnitTestSampleClass( UnitTestSampleClass const& other );
      UnitTestSampleClass& operator=( UnitTestSampleClass const& other );
      ~UnitTestSampleClass();

      bool const operator==( UnitTestSampleClass const& other ) const;
      bool const operator!=( UnitTestSampleClass const& other ) const;
      bool const operator>( UnitTestSampleClass const& other ) const;
      bool const operator<( UnitTestSampleClass const& other ) const;
      bool const operator>=( UnitTestSampleClass const& other ) const;
      bool const operator<=( UnitTestSampleClass const& other ) const;

      static void UpdateAnArray( UnitTestSampleClass* array, unsigned const arraySize );
  };

}

#endif
