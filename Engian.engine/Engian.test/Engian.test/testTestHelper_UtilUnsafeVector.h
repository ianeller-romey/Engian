
#ifndef TEST_TESTHELPER_UTILUNSAFEVECTOR_H
#define TEST_TESTHELPER_UTILUNSAFEVECTOR_H


namespace Util
{
  template< typename T > class Container;
  template< typename T > class UnsafeVector;
}


namespace Test
{  

  class TestHelper_UtilUnsafeVector
  {
    public:
      static unsigned const UnsafeVector_Constructor0();
      static unsigned const UnsafeVector_Constructor1();
      static unsigned const UnsafeVector_Constructor2();
      static unsigned const UnsafeVector_Constructor3();
      static unsigned const UnsafeVector_CopyConstructor();
      static unsigned const UnsafeVector_PushFront();
      static unsigned const UnsafeVector_PushBackRange0();
      static unsigned const UnsafeVector_PushBackRange1();
      static unsigned const UnsafeVector_BasicAssignment0();
      static unsigned const UnsafeVector_BasicAssignment1();


    private:    
      template< typename T >
      static unsigned const CheckUtilUnsafeVectorInit( Util::UnsafeVector< T > const& uVector, 
                                                       unsigned const capacity,
                                                       unsigned const size );   
      template< typename T >
      static unsigned const CheckUtilUnsafeVectorInit( Util::UnsafeVector< T > const& uVector, unsigned const size );    
      template< typename T >
      static unsigned const CheckUtilUnsafeVectorAgainstArray( Util::UnsafeVector< T > const& uVector, 
                                                               T const * const compareAgainst, 
                                                               unsigned const compareAgainstLen ); 
      template< typename T >
      static unsigned const CheckUtilUnsafeVectorAgainstContainer( Util::UnsafeVector< T > const& uVector, 
                                                                   Util::Container< T > const& container );
      
  };

}

#endif
