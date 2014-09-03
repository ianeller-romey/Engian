
#ifndef TEST_TESTHELPER_UTILVECTOR_H
#define TEST_TESTHELPER_UTILVECTOR_H

#include "utilVector.h"


namespace Test
{  

  class TestHelper_UtilVector
  {
    public:    
      template< typename T >
      static T const* GetUtilVectorArray( Util::Vector< T > const& vector )
      {
        return vector.m_array;
      }

      static unsigned const VectorIteratorImpl_Constructor0();
      static unsigned const VectorIteratorImpl_AdvanceValue();
      static unsigned const VectorIteratorImpl_GetValue();
      static unsigned const VectorIteratorImpl_EqualTo();
      static unsigned const VectorIteratorImpl_NotEqualTo();
      static unsigned const Vector_Constructor0();
      static unsigned const Vector_Constructor1();
      static unsigned const Vector_Constructor2();
      static unsigned const Vector_Constructor3();
      static unsigned const Vector_CopyConstructor();
      static unsigned const Vector_Begin();
      static unsigned const Vector_End();
      static unsigned const Vector_PushFront();
      static unsigned const Vector_PushBack();
      static unsigned const Vector_PopFront();
      static unsigned const Vector_PopBack();
      static unsigned const Vector_PopFirst();
      static unsigned const Vector_PopAll();
      static unsigned const Vector_Contains();
      static unsigned const Vector_IsFull();
      static unsigned const Vector_GetCapacity();
      static unsigned const Vector_Clear();
      static unsigned const Vector_BasicAssignment0();
      static unsigned const Vector_BasicAssignment1();
      static unsigned const Vector_ArraySubscript();
      static unsigned const Vector_Addition();
      static unsigned const Vector_AdditionAssignment();
      static unsigned const Vector_Indirection();

    private:
      template< typename T >
      static unsigned const CheckUtilVectorInit( Util::Vector< T > const& vector, unsigned const capacity, unsigned const size );   
      template< typename T >
      static unsigned const CheckUtilVectorInit( Util::Vector< T > const& vector, unsigned const size );    
      template< typename T >
      static unsigned const CheckUtilVectorAgainstArray( Util::Vector< T > const& vector, 
                                                         T const * const compareAgainst, 
                                                         unsigned const compareAgainstLen ); 
      template< typename T >
      static unsigned const CheckUtilVectorAgainstArray( Util::Vector< T > const& vector, 
                                                         unsigned const vectorStartPos,
                                                         T const * const compareAgainst, 
                                                         unsigned const compareAgainstLen );
      template< typename T >
      static unsigned const CheckUtilVectorAgainstContainer( Util::Vector< T > const& vector, Util::Container< T > const& container );

  };

}

#endif
