
#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include "debugForTestDefines.h"

#include "utilContainer.h"


#ifdef USE_DFT_LIB
namespace Test
{
  class TestHelper_UtilVector;
}
#define TESTHELPER_UTILVECTOR_FRIEND friend class Test::TestHelper_UtilVector
#else
#define TESTHELPER_UTILVECTOR_FRIEND
#endif


namespace Util
{

  template< typename T >
  class Vector : public Container< T >
  {
    public:
      //DFT_FUNC_TRACK_CLASS_DEC;
      TESTHELPER_UTILVECTOR_FRIEND;

      Vector();
      Vector( unsigned const capacity );
      Vector( T const * const tArray, unsigned const size );
      Vector( Vector< T > const& vector );
      Vector( Container< T > const& container );
      virtual Vector< T >& operator=( Vector< T > const& vector );
      virtual Container< T >& operator=( Container< T > const& container );
      virtual ~Vector();
        

      virtual Iterator Begin() const
      {
        DFT_FUNC_TRACK( "Iterator Vector< T >::Begin() const" );

        VectorIteratorImpl* iter = new VectorIteratorImpl( m_array );
        return CreateIteratorFromImplementation( iter );
      }


      virtual Iterator const End() const
      {
        DFT_FUNC_TRACK( "Iterator Vector< T >::End() const" );

        VectorIteratorImpl* iter = new VectorIteratorImpl( m_array + m_size );
        return CreateIteratorFromImplementation( iter );
      }

      
      virtual T& operator[]( int const index ) const;
      virtual Vector< T > operator+( Vector< T > const& vector ) const;
      virtual Vector< T >& operator+=( Vector< T > const& vector );
      virtual T const* operator*() const;

      virtual void PushFront( T const& t );
      virtual void PushBack( T const& t );
      virtual void PopFront();
      virtual void PopBack();
      virtual void PopFirst( T const& t );
      virtual void PopAll( T const& t );
      virtual bool const Contains( T const& t ) const;
      virtual bool const IsFull() const;

      virtual unsigned const GetCapacity() const;

      virtual void Clear();
      virtual void Clear( unsigned const newCapacity );

      
    protected:
      class VectorIteratorImpl : public IteratorImpl
      {
        public:
          DFT_FUNC_TRACK_CLASS_DEC;
          TESTHELPER_UTILVECTOR_FRIEND;

          VectorIteratorImpl( T* const tArray );
          virtual ~VectorIteratorImpl();


          virtual bool const operator==( IteratorImpl const& iterator ) const
          {
            DFT_FUNC_TRACK( "bool const Vector< T >::VectorIteratorImpl::operator==( IteratorImpl const& iterator ) const" );

            VectorIteratorImpl const* vectorIteratorImpl = dynamic_cast< VectorIteratorImpl const* >( &iterator );
            if( vectorIteratorImpl == 0 )
              return false;

            return m_value == vectorIteratorImpl->m_value;
          }


          virtual bool const operator!=( IteratorImpl const& iterator ) const
          {
            DFT_FUNC_TRACK( "bool const Vector< T >::VectorIteratorImpl::operator!=( IteratorImpl const& iterator ) const" );

            VectorIteratorImpl const* vectorIteratorImpl = dynamic_cast< VectorIteratorImpl const* >( &iterator );
            if( vectorIteratorImpl == 0 )
              return false;

            return m_value != vectorIteratorImpl->m_value;
          }


          virtual IteratorImpl * const Clone() const
          {
            DFT_FUNC_TRACK( "IteratorImpl * const Vector< T >::VectorIteratorImpl::Clone() const" );

            return new VectorIteratorImpl( *this );
          }
          

        protected:
          virtual void AdvanceValue();
          virtual T const& GetValue() const;

          T* m_value;


        private:
          VectorIteratorImpl();
          VectorIteratorImpl( VectorIteratorImpl const& vectorIteratorImpl );
          VectorIteratorImpl& operator=( VectorIteratorImpl const& vectorIteratorImpl );
      };

      ////////
      // member functions
      virtual void CheckAndGrow();
      virtual void Grow();

      virtual void Deallocate();

      virtual bool const Search( unsigned& startIndex, T const& t ) const;
      virtual void ShiftAndPop( unsigned const startIndex );

      ////////
      // member variables
      static unsigned const c_defaultCapacity;
      static float const    c_growMultiplier; // TODO: Dynamically calculated grow multiplier?
      unsigned              m_capacity;
      T*                    m_array;
  };

}

#include "utilVector.inl"

#endif
