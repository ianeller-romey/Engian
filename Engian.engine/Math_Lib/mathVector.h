
#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

// std
#include <cmath>

// debug
#include "debugForTestDefines.h"


#ifdef USE_DFT_LIB
namespace Test
{
    class TestHelper_MathVector;
    class TestHelper_MathVector2;
    class TestHelper_MathVector3;
    class TestHelper_MathVector4;
}
#define TESTHELPER_MATHVECTOR_FRIEND friend class Test::TestHelper_MathVector
#define TESTHELPER_MATHVECTOR2_FRIEND friend class Test::TestHelper_MathVector2
#define TESTHELPER_MATHVECTOR3_FRIEND friend class Test::TestHelper_MathVector3
#define TESTHELPER_MATHVECTOR4_FRIEND friend class Test::TestHelper_MathVector4
#else
#define TESTHELPER_MATHVECTOR_FRIEND
#define TESTHELPER_MATHVECTOR2_FRIEND
#define TESTHELPER_MATHVECTOR3_FRIEND
#define TESTHELPER_MATHVECTOR4_FRIEND
#endif


#define VECTS Vector< T, SIZE >
#define VECT2 Vector< T, 2 >
#define VECT3 Vector< T, 3 >
#define VECT4 Vector< T, 4 >


namespace Math
{

    template< typename T, unsigned SIZE >
    struct Vector
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHVECTOR_FRIEND;

        T m_data[SIZE];


        Vector< T, SIZE >()
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >::Vector()" );

            static_assert( SIZE > 0, "CANNOT CREATE A ZERO-DIMENSION VECTOR" );
        }



        Vector< T, SIZE >( const VECTS& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >::Vector( const Vector< T, SIZE >& rhs )" );

            for ( unsigned i = 0; i < SIZE; ++i )
                m_data[i] = rhs.m_data[i];
        }


        operator T*()
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >::operator T*()" );

            return m_data;
        }


        operator const T*() const
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >::operator const T*() const" );

            return m_data;
        }


        const bool operator==( const VECTS& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, SIZE >::operator==( const Vector< T, SIZE >& rhs) const" );

            for ( unsigned i = 0; i < SIZE; ++i )
                if ( m_data[i] != rhs.m_data[i] )
                    return false;
            return true;
        }


        const bool operator!=( const VECTS& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, SIZE >::operator!=( const Vector< T, SIZE >& rhs) const" );

            for ( unsigned i = 0; i < SIZE; ++i )
                if ( m_data[i] != rhs.m_data[i] )
                    return true;
            return false;
        }


        VECTS& operator=( const VECTS& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >& Vector< T, SIZE >::operator=( const Vector< T, SIZE >& rhs)" );

            for ( unsigned i = 0; i < SIZE; ++i )
                m_data[i] = rhs.m_data[i];
            return *this;
        }


        VECTS operator-() const
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE > Vector< T, SIZE >::operator-() const" );

            VECTS v;
            for ( unsigned i = 0; i < SIZE; ++i )
                v.m_data[i] = -m_data[i];
            return v;
        }


        VECTS operator+( const VECTS& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE > Vector< T, SIZE >::operator+( const Vector< T, SIZE >& rhs ) const" );

            VECTS v;
            for ( unsigned i = 0; i < SIZE; ++i )
                v.m_data[i] = m_data[i] + rhs.m_data[i];
            return v;
        }


        VECTS operator-( const VECTS& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE > Vector< T, SIZE >::operator-( const Vector< T, SIZE >& rhs ) const" );

            VECTS v;
            for ( unsigned i = 0; i < SIZE; ++i )
                v.m_data[i] = m_data[i] - rhs.m_data[i];
            return v;
        }


        VECTS operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE > Vector< T, SIZE >::operator*( const T& value ) const" );

            VECTS v;
            for ( unsigned i = 0; i < SIZE; ++i )
                v.m_data[i] = m_data[i] * value;
            return v;
        }


        VECTS operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE > Vector< T, SIZE >::operator/( const T& value ) const" );

            VECTS v;
            for ( unsigned i = 0; i < SIZE; ++i )
                v.m_data[i] = m_data[i] / value;
            return v;
        }


        VECTS& operator+=( const VECTS& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >& Vector< T, SIZE >::operator+=( const Vector< T, SIZE >& value )" );

            for ( unsigned i = 0; i < SIZE; ++i )
                m_data[i] += rhs.m_data[i];
            return *this;
        }


        VECTS& operator-=( const VECTS& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >& Vector< T, SIZE >::operator-=( const Vector< T, SIZE >& value )" );

            for ( unsigned i = 0; i < SIZE; ++i )
                m_data[i] -= rhs.m_data[i];
            return *this;
        }


        VECTS& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >& Vector< T, SIZE >::operator*=( const T& value )" );

            for ( unsigned i = 0; i < SIZE; ++i )
                m_data[i] *= rhs.m_data[i];
            return *this;
        }


        VECTS& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, SIZE >& Vector< T, SIZE >::operator/=( const T& value )" );

            for ( unsigned i = 0; i < SIZE; ++i )
                m_data[i] /= rhs.m_data[i];
            return *this;
        }
    };

    typedef Vector< int, 2 > IVec2;
    typedef Vector< unsigned, 2 > UVec2;
    typedef Vector< float, 2 > FVec2;
    typedef Vector< double, 2 > DVec2;

    typedef Vector< int, 3 > IVec3;
    typedef Vector< unsigned, 3 > UVec3;
    typedef Vector< float, 3 > FVec3;
    typedef Vector< double, 3 > DVec3;

    typedef Vector< int, 4 > IVec4;
    typedef Vector< unsigned, 4 > UVec4;
    typedef Vector< float, 4 > FVec4;
    typedef Vector< double, 4 > DVec4;


    template < typename T > 
    struct Vector< T, 2 > 
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHVECTOR2_FRIEND;

        union 
        { 
            T m_data[2]; 
            struct { T x, y; }; 
        };


        Vector< T, 2 >()
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >::Vector()" );
        }


        Vector< T, 2 >( const VECT2& rhs ) :
            x( rhs.x ),
            y( rhs.y )
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >::Vector( const Vector< T, 2 >& rhs )" );
        }


        operator T*()
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >::operator T*()" );

            return m_data;
        }


        operator const T*() const
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >::operator const T*() const" );

            return m_data;
        }


        const bool operator==( const VECT2& rhs ) const
        {
            FUNC_TRACK("const bool Vector< T, 2 >::operator==( const Vector< T, 2 >& rhs) const" );

            return x == rhs.x && y == rhs.y;
        }


        const bool operator!=( const VECT2& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, 2 >::operator!=( const Vector< T, 2 >& rhs) const" );

            return x != rhs.x || y != rhs.y;
        }


        VECT2& operator=( const VECT2& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >& Vector< T, 2 >::operator=( const Vector< T, 2 >& rhs)" );

            x = rhs.x;
            y = rhs.y;
            return *this;
        }


        VECT2 operator-() const
        {
            DFT_FUNC_TRACK( "Vector< T, 2 > Vector< T, 2 >::operator-() const" );

            VECT2 v;
            v.x = -x;
            v.y = -y;
            return v;
        }


        VECT2 operator+( const VECT2& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 2 > Vector< T, 2 >::operator+( const Vector< T, 2 >& rhs ) const" );

            VECT2 v;
            v.x = x + rhs.x;
            v.y = y + rhs.y;
            return v;
        }


        VECT2 operator-( const VECT2& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 2 > Vector< T, 2 >::operator-( const Vector< T, 2 >& rhs ) const" );

            VECT2 v;
            v.x = x - rhs.x;
            v.y = y - rhs.y;
            return v;
        }


        VECT2 operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 2 > Vector< T, 2 >::operator*( const T& value ) const" );

            VECT2 v;
            v.x = x * value;
            v.y = y * value;
            return v;
        }


        VECT2 operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 2 > Vector< T, 2 >::operator/( const T& value ) const" );

            VECT2 v;
            v.x = x / value;
            v.y = y / value;
            return v;
        }


        VECT2& operator+=( const VECT2& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >& Vector< T, 2 >::operator+=( const Vector< T, 2 >& value )" );

            x += rhs.x;
            y += rhs.y;
            return *this;
        }


        VECT2& operator-=( const VECT2& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >& Vector< T, 2 >::operator-=( const Vector< T, 2 >& value )" );

            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }


        VECT2& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >& Vector< T, 2 >::operator*=( const T& value )" );

            x *= value;
            y *= value;
            return *this;
        }


        VECT2& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, 2 >& Vector< T, 2 >::operator/=( const T& value )" );

            x /= value;
            y /= value;
            return *this;
        }
    };


    template < typename T > 
    struct Vector< T, 3 > 
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHVECTOR3_FRIEND;

        union 
        { 
            T m_data[3];
            struct { T x, y, z; };
            struct { T r, g, b; };
            Vector< T, 2 > xy;
        };


        Vector< T, 3 >()
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >::Vector()" );
        }


        Vector< T, 3 >( const VECT3& rhs ) :
            x( rhs.x ),
            y( rhs.y ),
            z( rhs.z )
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >::Vector( const Vector< T, 3 >& rhs )" );
        }


        operator T*()
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >::operator T*()" );

            return m_data;
        }


        operator const T*() const
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >::operator const T*() const" );

            return m_data;
        }


        const bool operator==( const VECT3& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, 3 >::operator==( const Vector< T, 3 >& rhs) const" );

            return x == rhs.x && y == rhs.y && z == rhs.z;
        }


        const bool operator!=( const VECT3& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, 3 >::operator!=( const Vector< T, 3 >& rhs) const" );

            return x != rhs.x || y != rhs.y || z != rhs.z;
        }


        VECT3& operator=( const VECT3& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >& Vector< T, 3 >::operator=( const Vector< T, 3 >& rhs)" );

            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }


        VECT3 operator-() const
        {
            DFT_FUNC_TRACK( "Vector< T, 3 > Vector< T, 3 >::operator-() const" );

            VECT3 v;
            v.x = -x;
            v.y = -y;
            v.z = -z;
            return v;
        }


        VECT3 operator+( const VECT3& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 3 > Vector< T, 3 >::operator+( const Vector< T, 3 >& rhs ) const" );

            VECT3 v;
            v.x = x + rhs.x;
            v.y = y + rhs.y;
            v.z = z + rhs.z;
            return v;
        }


        VECT3 operator-( const VECT3& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 3 > Vector< T, 3 >::operator-( const Vector< T, 3 >& rhs ) const" );

            VECT3 v;
            v.x = x - rhs.x;
            v.y = y - rhs.y;
            v.z = z - rhs.z;
            return v;
        }


        VECT3 operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 3 > Vector< T, 3 >::operator*( const T& value ) const" );

            VECT3 v;
            v.x = x * value;
            v.y = y * value;
            v.z = z * value;
            return v;
        }


        VECT3 operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 3 > Vector< T, 3 >::operator/( const T& value ) const" );

            VECT3 v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;
            return v;
        }


        VECT3& operator+=( const VECT3& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >& Vector< T, 3 >::operator+=( const Vector< T, 3 >& value )" );

            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }


        VECT3& operator-=( const VECT3& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >& Vector< T, 3 >::operator-=( const Vector< T, 3 >& value )" );

            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }


        VECT3& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >& Vector< T, 3 >::operator*=( const T& value )" );

            x *= value;
            y *= value;
            z *= value;
            return *this;
        }


        VECT3& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, 3 >& Vector< T, 3 >::operator/=( const T& value )" );

            x /= value;
            y /= value;
            z /= value;
            return *this;
        }
    };


    template < typename T > 
    struct Vector< T, 4 > 
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHVECTOR4_FRIEND;

        union 
        { 
            T m_data[4];
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            Vector< T, 2 > xy;
            Vector< T, 3 > xyz;
            Vector< T, 3 > rgb;
        };


        Vector< T, 4 >()
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >::Vector()" );
        }


        Vector< T, 4 >( const VECT4& rhs ) :
            x( rhs.x ),
            y( rhs.y ),
            z( rhs.z ),
            w( rhs.w )
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >::Vector( const Vector< T, 4 >& rhs )" );
        }


        operator T*()
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >::operator T*()" );

            return m_data;
        }


        operator const T*() const
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >::operator const T*() const" );

            return m_data;
        }


        const bool operator==( const VECT4& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, 4 >::operator==( const Vector< T, 4 >& rhs) const" );

            return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
        }


        const bool operator!=( const VECT4& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Vector< T, 4 >::operator!=( const Vector< T, 4 >& rhs) const" );

            return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
        }


        VECT4& operator=( const VECT4& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >& Vector< T, 4 >::operator=( const Vector< T, 4 >& rhs)" );

            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            w = rhs.w;
            return *this;
        }


        VECT4 operator-() const
        {
            DFT_FUNC_TRACK( "Vector< T, 4 > Vector< T, 4 >::operator-() const" );

            VECT4 v;
            v.x = -x;
            v.y = -y;
            v.z = -z;
            v.w = -w;
            return v;
        }


        VECT4 operator+( const VECT4& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 4 > Vector< T, 4 >::operator+( const Vector< T, 4 >& rhs ) const" );

            VECT4 v;
            v.x = x + rhs.x;
            v.y = y + rhs.y;
            v.z = z + rhs.z;
            v.w = w + rhs.w;
            return v;
        }


        VECT4 operator-( const VECT4& rhs ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 4 > Vector< T, 4 >::operator-( const Vector< T, 4 >& rhs ) const" );

            VECT4 v;
            v.x = x - rhs.x;
            v.y = y - rhs.y;
            v.z = z - rhs.z;
            v.w = w - rhs.w;
            return v;
        }


        VECT4 operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 4 > Vector< T, 4 >::operator*( const T& value ) const" );

            VECT4 v;
            v.x = x * value;
            v.y = y * value;
            v.z = z * value;
            v.w = w * value;
            return v;
        }


        VECT4 operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Vector< T, 4 > Vector< T, 4 >::operator/( const T& value ) const" );

            VECT4 v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;
            v.w = w / value;
            return v;
        }


        VECT4& operator+=( const VECT4& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >& Vector< T, 4 >::operator+=( const Vector< T, 4 >& value )" );

            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }


        VECT4& operator-=( const VECT4& rhs )
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >& Vector< T, 4 >::operator-=( const Vector< T, 4 >& value )" );

            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }


        VECT4& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >& Vector< T, 4 >::operator*=( const T& value )" );

            x *= value;
            y *= value;
            z *= value;
            w *= value;
            return *this;
        }


        VECT4& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Vector< T, 4 >& Vector< T, 4 >::operator/=( const T& value )" );

            x /= value;
            y /= value;
            z /= value;
            w /= value;
            return *this;
        }
    };


    template< typename T, unsigned SIZE >
    Vector< T, SIZE > MakeVec( T* data )
    {
#ifdef USE_DFT_LIB
        Vector< T, SIZE >::s_functionTracker.Track( "Vector< T, SIZE >& MakeVec( T* data )" );
#endif

        Vector< T, SIZE > v;
        for ( unsigned i = 0; i < SIZE; ++i )
            v.m_data[i] = data[i];
        return v;
    }


    template< typename T >
    Vector< T, 2 > MakeVec2( const T& x, const T& y )
    {
#ifdef USE_DFT_LIB
        Vector< T, 2 >::s_functionTracker.Track("Vector< T, 2 >& MakeVec2( const T& x, const T& y )" );
#endif

        Vector< T, 2 > v;
        v.x = x;
        v.y = y;
        return v;
    }


    template< typename T >
    Vector< T, 3 > MakeVec3( const T& x, const T& y, const T& z )
    {
#ifdef USE_DFT_LIB
        Vector< T, 3 >::s_functionTracker.Track("Vector< T, 3 >& MakeVec3( const T& x, const T& y, const T& z )" );
#endif

        Vector< T, 3 > v;
        v.x = x;
        v.y = y;
        v.z = z;
        return v;
    }


    template< typename T >
    Vector< T, 4 > MakeVec4( const T& x, const T& y, const T& z, const T& w )
    {
#ifdef USE_DFT_LIB
        Vector< T, 4 >::s_functionTracker.Track("Vector< T, 4 >& MakeVec4( const T& x, const T& y, const T& z, const T& w )" );
#endif

        Vector< T, 4 > v;
        v.x = x;
        v.y = y;
        v.z = z;
        v.w = w;
        return v;
    }


    template< typename T, unsigned SIZE >
    T Dot( const VECTS& v1, const VECTS& v2 )
    {
        DFT_FUNC_TRACK( "T Dot( const Vector< T, SIZE >& v1, const Vector< T, SIZE >& v2 )" );

        T t = v1.m_data[0] * v2.m_data[0];
        for ( unsigned i = 1; i < SIZE; ++i )
            t += v1.m_data[i] * v2.m_data[i];
        return t;
    }


    template< typename T >
    T Dot( const VECT2& v1, const VECT2& v2 )
    {
        DFT_FUNC_TRACK( "T Dot( const Vector< T, 2 >& v1, const Vector< T, 2 >& v2 )" );

        return v1.x * v2.x + v1.y * v2.y;
    }


    template< typename T >
    T Dot( const VECT3& v1, const VECT3& v2 )
    {
        DFT_FUNC_TRACK( "T Dot( const Vector< T, 3 >& v1, const Vector< T, 3 >& v2 )" );

        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }


    template< typename T >
    T Dot( const VECT4& v1, const VECT4& v2 )
    {
        DFT_FUNC_TRACK( "T Dot( const Vector< T, 4 >& v1, const Vector< T, 4 >& v2 )" );

        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }


    template< typename T, unsigned SIZE >
    T Magnitude2( const VECTS& v )
    {
        DFT_FUNC_TRACK( "T Magnitude2( const Vector< T, SIZE >& v )" );

        return Dot( v, v );
    }


    template< typename T, unsigned SIZE >
    T Magnitude( const VECTS& v )
    {
        DFT_FUNC_TRACK( "T Magnitude( const Vector< T, SIZE >& v )" );

        return sqrt( Magnitude2< T, SIZE >( v ) );
    }


    template< typename T, unsigned SIZE >
    bool IsNormalized( const VECTS& v )
    {
        DFT_FUNC_TRACK( "bool IsNormalized( const Vector< T, SIZE >& v )" );

        return Magnitude2( v ) == (T)1;
    }


    template< typename T, unsigned SIZE >
    VECTS Normalize( const VECTS& v )
    {
        DFT_FUNC_TRACK( "Vector< T, SIZE > Normalize( const Vector< T, SIZE >& v )" );

        VECTS normalized( v );
        if ( !IsNormalized( normalized ) )
        {
            auto mag = Magnitude( normalized );
            normalized /= mag;
        }
        return normalized;
    }


    template< typename T, unsigned SIZE >
    VECTS Cross( const VECTS& v1, const VECTS& v2 )
    {
        DFT_FUNC_TRACK( "Vector< T, SIZE > Cross( const Vector< T, SIZE >& v1, const Vector< T, SIZE >& v2 )" );

        static_assert( SIZE == 3, "CANNOT TAKE THE CROSS PRODUCT OF VECTORS THAT ARE NOT THREE-DIMENSIONAL" )
    }


    template< typename T >
    VECT3 Cross( const VECT3& v1, const VECT3& v2 )
    {
        DFT_FUNC_TRACK( "Vector< T, 3 > Cross( const Vector< T, 3 >& v1, const Vector< T, 3 >& v2 )" );

        return MakeVec3( v1.y * v2.z - v1.z * v2.y,
                         v1.z * v2.x - v1.x * v2.z,
                         v1.x * v2.y - v1.y * v2.x );
    }

#ifdef USE_DFT_LIB
    template< typename T, unsigned SIZE >
    DebugForTest::FunctionTracker Vector< T, SIZE >::s_functionTracker;
    template< typename T >
    DebugForTest::FunctionTracker Vector< T, 2 >::s_functionTracker;
    template< typename T >
    DebugForTest::FunctionTracker Vector< T, 3 >::s_functionTracker;
    template< typename T >
    DebugForTest::FunctionTracker Vector< T, 4 >::s_functionTracker;
#endif

}

#endif
