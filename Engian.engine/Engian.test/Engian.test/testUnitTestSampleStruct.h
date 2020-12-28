
#ifndef TEST_UNITTESTSAMPLESTRUCT_H
#define TEST_UNITTESTSAMPLESTRUCT_H

namespace Test
{

  struct UnitTestSampleStruct
  {
    int m_int1,
      m_int2,
      m_int3;
    double m_doubles[ 5 ];

    UnitTestSampleStruct();
    UnitTestSampleStruct( int int1, int int2, int int3, double* doubles );
    UnitTestSampleStruct( UnitTestSampleStruct const& other );
    UnitTestSampleStruct& operator=( UnitTestSampleStruct const& other );
    ~UnitTestSampleStruct();

    bool const operator==( UnitTestSampleStruct const& other ) const;
    bool const operator!=( UnitTestSampleStruct const& other ) const;
    bool const operator>( UnitTestSampleStruct const& other ) const;
    bool const operator<( UnitTestSampleStruct const& other ) const;
    bool const operator>=( UnitTestSampleStruct const& other ) const;
    bool const operator<=( UnitTestSampleStruct const& other ) const;

    double const Sum() const;

    static void UpdateAnArray( UnitTestSampleStruct* array, unsigned const arraySize );
  };

}

#endif
