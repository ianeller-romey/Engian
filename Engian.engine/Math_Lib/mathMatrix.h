
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H


// Math
#include "mathVector.h"

// debug
#include "debugForTestDefines.h"


#ifdef USE_DFT_LIB
namespace Test
{
    class TestHelper_MathMatrix;
    class TestHelper_MathMatrix22;
    class TestHelper_MathMatrix33;
    class TestHelper_MathMatrix44;
}
#define TESTHELPER_MATHMATRIX_FRIEND friend class Test::TestHelper_MathMatrix
#define TESTHELPER_MATHMATRIX22_FRIEND friend class Test::TestHelper_MathMatrix22
#define TESTHELPER_MATHMATRIX33_FRIEND friend class Test::TestHelper_MathMatrix33
#define TESTHELPER_MATHMATRIX44_FRIEND friend class Test::TestHelper_MathMatrix44
#else
#define TESTHELPER_MATHMATRIX_FRIEND
#define TESTHELPER_MATHMATRIX2_FRIEND
#define TESTHELPER_MATHMATRIX3_FRIEND
#define TESTHELPER_MATHMATRIX4_FRIEND
#endif


#define MATTRC Matrix< T, ROWS, COLS >
#define MATT22 Matrix< T, 2, 2 >
#define MATT33 Matrix< T, 3, 3 >
#define MATT44 Matrix< T, 4, 4 >


namespace Math
{

    template< typename T, unsigned ROWS, unsigned COLS >
    struct Matrix
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHMATRIX_FRIEND;

        T m_data[ROWS][COLS];


        Matrix< T, ROWS, COLS >()
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >::Matrix()" );

            static_assert( ROWS > 0 && COLS > 0, "CANNOT CREATE A ZERO-DIMENSION MATRIX" );
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++j )
                    m_data[i][j] = (T)0;
        }


        Matrix< T, ROWS, COLS >( const MATTRC& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >::Matrix( const Matrix< T, ROWS, COLS >& rhs )" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++j )
                    m_data[i][j] = rhs.m_data[i][j];
        }


        static MATTRC Identity()
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS > Matrix< T, ROWS, COLS >::Identity()" );

            static_assert( ROWS == COLS, "CANNOT CREATE IDENTITY FOR UNEVEN MATRIX" );
            Matrix< T, ROWS, COLS > m;
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++j )
                    m.m_data[i][j] = ( i == j ) ? (T)1 : (T)0;
            return m;
        }


        operator T**()
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >::operator T**()" );

            return m_data;
        }


        operator const T**() const
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >::operator const T**() const" );

            return m_data;
        }


        const bool operator==( const MATTRC& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, ROWS, COLS >::operator==( const Matrix< T, ROWS, COLS >& rhs ) const" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for( unsigned j = 0; j < COLS; ++i )
                    if ( m_data[i][j] != rhs.m_data[i][j] )
                        return false;
            return true;
        }


        const bool operator!=( const MATTRC& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, ROWS, COLS >::operator!=( const Matrix< T, ROWS, COLS >& rhs ) const" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    if ( m_data[i][j] != rhs.m_data[i][j] )
                        return true;
            return false;
        }


        MATTRC& operator=( const MATTRC& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >& Matrix< T, ROWS, COLS >::operator=( const Matrix< T, ROWS, COLS >& rhs )" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m_data[i][j] = rhs.m_data[i][j];
            return *this;
        }


        MATTRC operator-() const
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS > Matrix< T, ROWS, COLS >::operator-() const" );

            MATTRC m;
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m.m_data[i][j] = -m_data[i][j];
            return m;
        }


        MATTRC operator+( const MATTRC& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS > Matrix< T, ROWS, COLS >::operator+( const Matrix< T, ROWS, COLS >& rhs ) const" );

            MATTRC m;
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m.m_data[i][j] = m_data[i][j] + rhs.m_data[i][j];
            return m;
        }


        MATTRC operator-( const MATTRC& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS > Matrix< T, ROWS, COLS >::operator-( const Matrix< T, ROWS, COLS >& rhs ) const" );

            MATTRC m;
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m.m_data[i][j] = m_data[i][j] - rhs.m_data[i][j];
            return m;
        }


        MATTRC operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS > Matrix< T, ROWS, COLS >::operator*( const T& value ) const" );

            MATTRC m;
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m.m_data[i][j] = m_data[i][j] * value;
            return m;
        }


        MATTRC operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS > Matrix< T, ROWS, COLS >::operator/( const T& value ) const" );

            MATTRC m;
            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m.m_data[i][j] = m_data[i][j] / value;
            return m;
        }


        MATTRC& operator+=( const MATTRC& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >& Matrix< T, ROWS, COLS >::operator+=( const Matrix< T, ROWS, COLS >& rhs )" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m_data[i][j] += rhs.m_data[i][j];
            return *this;
        }


        MATTRC& operator-=( const MATTRC& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >& Matrix< T, ROWS, COLS >::operator-=( const Matrix< T, ROWS, COLS >& rhs )" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m_data[i][j] -= rhs.m_data[i][j];
            return *this;
        }


        MATTRC& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >& Matrix< T, ROWS, COLS >::operator*( const T& value )" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m_data[i][j] *= rhs.m_data[i][j];
            return *this;
        }


        MATTRC& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, ROWS, COLS >& Matrix< T, ROWS, COLS >::operator/( const T& value )" );

            for ( unsigned i = 0; i < ROWS; ++i )
                for ( unsigned j = 0; j < COLS; ++i )
                    m_data[i][j] /= rhs.m_data[i][j];
            return *this;
        }
    };


    typedef Matrix< int, 2, 2 > IMat22;
    typedef Matrix< unsigned, 2, 2 > UMat22;
    typedef Matrix< float, 2, 2 > FMat22;
    typedef Matrix< double, 2, 2 > DMat22;

    typedef Matrix< int, 3, 3 > IMat33;
    typedef Matrix< unsigned, 3, 3 > UMat33;
    typedef Matrix< float, 3, 3 > FMat33;
    typedef Matrix< double, 3, 3 > DMat33;

    typedef Matrix< int, 4, 4 > IMat44;
    typedef Matrix< unsigned, 4, 4 > UMat44;
    typedef Matrix< float, 4, 4 > FMat44;
    typedef Matrix< double, 4, 4 > DMat44;


    template < typename T > 
    struct Matrix< T, 2, 2 > 
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHMATRIX22_FRIEND;

        union 
        { 
            T m_data[2][2]; 
            struct { T _00, _01, _10, _11; }; 
            Vector< Vector< T, 2 >, 2 > v;
        };


        Matrix< T, 2, 2 >()
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >::Matrix()" );

            v.x = MakeVec2< T >( (T)0, (T)0 );
            v.y = MakeVec2< T >( (T)0, (T)0 );
        }


        Matrix< T, 2, 2 >( const MATT22& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >::Matrix( const Matrix< T, 2, 2 >& rhs )" );

            v = rhs.v;
        }


        static MATT22 Identity()
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Matrix< T, 2, 2 >::Identity()" );

            MATT22 m;
            m.v.x = MakeVec2< T >( (T)1, (T)0 );
            m.v.y = MakeVec2< T >( (T)0, (T)1 );
            return m;
        }


        operator T**()
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >::operator T**()" );

            return m_data;
        }


        operator const T**() const
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >::operator const T**() const" );

            return m_data;
        }


        const bool operator==( const MATT22& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, 2, 2 >::operator==( const Matrix< T, 2, 2 >& rhs ) const" );

            return v == rhs.v;
        }


        const bool operator!=( const MATT22& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, 2, 2 >::operator!=( const Matrix< T, 2, 2 >& rhs ) const" );

            return v != rhs.v;
        }


        MATT22& operator=( const MATT22& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >& Matrix< T, 2, 2 >::operator=( const Matrix< T, 2, 2 >& rhs )" );

            v = rhs.v;
            return *this;
        }


        MATT22 operator-() const
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Matrix< T, 2, 2 >::operator-() const" );

            MATT22 m;
            m.v = -v;
            return m;
        }


        MATT22 operator+( const MATT22& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Matrix< T, 2, 2 >::operator+( const Matrix< T, 2, 2 >& rhs ) const" );

            MATT22 m;
            m.v = v + rhs.v;
            return m;
        }


        MATT22 operator-( const MATT22& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Matrix< T, 2, 2 >::operator-( const Matrix< T, 2, 2 >& rhs ) const" );

            MATT22 m;
            m.v = m.v - rhs.v;
            return m;
        }


        MATT22 operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Matrix< T, 2, 2 >::operator*( const T& value ) const" );

            MATT22 m;
            m.v = v * value;
            return m;
        }


        MATT22 operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Matrix< T, 2, 2 >::operator/( const T& value ) const" );

            MATT22 m;
            m.v = v / value;
            return m;
        }


        MATT22& operator+=( const MATT22& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >& Matrix< T, 2, 2 >::operator+=( const Matrix< T, 2, 2 >& rhs )" );

            v += rhs;
            return *this;
        }


        MATT22& operator-=( const MATT22& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >& Matrix< T, 2, 2 >::operator-=( const Matrix< T, 2, 2 >& rhs )" );

            v -= rhs;
            return *this;
        }


        MATT22& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >& Matrix< T, 2, 2 >::operator*=( const T& value )" );

            v *= value;
            return *this;
        }


        MATT22& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, 2, 2 >& Matrix< T, 2, 2 >::operator/=( const T& value )" );

            v /= value;
            return *this;
        }
    };


    template < typename T >
    struct Matrix< T, 3, 3 >
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHMATRIX33_FRIEND;

        union
        {
            T m_data[3][3];
            struct { T _00, _01, _02, _10, _11, _12, _20, _21, _22; };
            Vector< Vector< T, 3 >, 3 > v;
        };


        Matrix< T, 3, 3 >()
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >::Matrix()" );

            v.x = MakeVec3< T >( (T)0, (T)0, (T)0 );
            v.y = MakeVec3< T >( (T)0, (T)0, (T)0 );
            v.z = MakeVec3< T >( (T)0, (T)0, (T)0 );
        }


        Matrix< T, 3, 3 >( const MATT33& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >::Matrix( const Matrix< T, 3, 3 >& rhs )" );

            v = rhs.v;
        }


        static MATT33 Identity()
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Matrix< T, 3, 3 >::Identity()" );

            MATT33 m;
            m.v.x = MakeVec3< T >( (T)1, (T)0, (T)0 );
            m.v.y = MakeVec3< T >( (T)0, (T)1, (T)0 );
            m.v.z = MakeVec3< T >( (T)0, (T)0, (T)1 );
            return m;
        }


        operator T**()
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >::operator T**()" );

            return m_data;
        }


        operator const T**() const
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >::operator const T**() const" );

            return m_data;
        }


        const bool operator==( const MATT33& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, 3, 3 >::operator==( const Matrix< T, 3, 3 >& rhs ) const" );

            return v == rhs.v;
        }


        const bool operator!=( const MATT33& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, 3, 3 >::operator!=( const Matrix< T, 3, 3 >& rhs ) const" );

            return v != rhs.v;
        }


        MATT33& operator=( const MATT33& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >& Matrix< T, 3, 3 >::operator=( const Matrix< T, 3, 3 >& rhs )" );

            v = rhs.v;
            return *this;
        }


        MATT33 operator-() const
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Matrix< T, 3, 3 >::operator-() const" );

            MATT33 m;
            m.v = -v;
            return m;
        }


        MATT33 operator+( const MATT33& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Matrix< T, 3, 3 >::operator+( const Matrix< T, 3, 3 >& rhs ) const" );

            MATT33 m;
            m.v = v + rhs.v;
            return m;
        }


        MATT33 operator-( const MATT33& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Matrix< T, 3, 3 >::operator-( const Matrix< T, 3, 3 >& rhs ) const" );

            MATT33 m;
            m.v = m.v - rhs.v;
            return m;
        }


        MATT33 operator*( const T& value ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Matrix< T, 3, 3 >::operator*( const T& value ) const" );

            MATT33 m;
            m.v = v * value;
            return m;
        }


        MATT33 operator/( const T& value ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Matrix< T, 3, 3 >::operator/( const T& value ) const" );

            MATT33 m;
            m.v = v / value;
            return m;
        }


        MATT33& operator+=( const MATT33& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >& Matrix< T, 3, 3 >::operator+=( const Matrix< T, 3, 3 >& rhs )" );

            v += rhs;
            return *this;
        }


        MATT33& operator-=( const MATT33& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >& Matrix< T, 3, 3 >::operator-=( const Matrix< T, 3, 3 >& rhs )" );

            v -= rhs;
            return *this;
        }


        MATT33& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >& Matrix< T, 3, 3 >::operator*=( const T& value )" );

            v *= value;
            return *this;
        }


        MATT33& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, 3, 3 >& Matrix< T, 3, 3 >::operator/=( const T& value )" );

            v /= value;
            return *this;
        }
    };


    template < typename T >
    struct Matrix< T, 4, 4 >
    {
        DFT_FUNC_TRACK_CLASS_DEC;
        TESTHELPER_MATHMATRIX44_FRIEND;

        union
        {
            T m_data[4][4];
            struct { T _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33; };
            Vector< Vector< T, 4 >, 4 > v;
        };


        Matrix< T, 4, 4 >()
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >::Matrix()" );

            v.x = MakeVec4< T >( (T)0, (T)0, (T)0, (T)0 );
            v.y = MakeVec4< T >( (T)0, (T)0, (T)0, (T)0 );
            v.z = MakeVec4< T >( (T)0, (T)0, (T)0, (T)0 );
            v.w = MakeVec4< T >( (T)0, (T)0, (T)0, (T)0 );
        }


        Matrix< T, 4, 4 >( const MATT44& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >::Matrix( Matrix< T, 4, 4 >& rhs )" );

            v = rhs.v;
        }


        static MATT44 Identity()
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 > Matrix< T, 4, 4 >::Identity()" );

            MATT44 m;
            m.v.x = MakeVec4< T >( (T)1, (T)0, (T)0, (T)0 );
            m.v.y = MakeVec4< T >( (T)0, (T)1, (T)0, (T)0 );
            m.v.z = MakeVec4< T >( (T)0, (T)0, (T)1, (T)0 );
            m.v.w = MakeVec4< T >( (T)0, (T)0, (T)0, (T)1 );
            return m;
        }


        operator T**()
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >::operator T**()" );

            return m_data;
        }


        operator const T**() const
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >::operator const T**() const" );

            return m_data;
        }


        const bool operator==( const MATT44& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, 4, 4 >::operator==( const Matrix< T, 4, 4 >& rhs ) const" );

            return v == rhs.v;
        }


        const bool operator!=( const MATT44& rhs ) const
        {
            DFT_FUNC_TRACK( "const bool Matrix< T, 4, 4 >::operator!=( const Matrix< T, 4, 4 >& rhs ) const" );

            return v != rhs.v;
        }


        MATT44& operator=( const MATT44& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >& Matrix< T, 4, 4 >::operator=( const Matrix< T, 4, 4 >& rhs )" );

            v = rhs.v;
            return *this;
        }


        MATT44 operator-() const
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 > Matrix< T, 4, 4 >::operator-() const" );

            MATT44 m;
            m.v = -v;
            return m;
        }


        MATT44 operator+( const MATT44& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 > Matrix< T, 4, 4 >::operator+( const Matrix< T, 4, 4 >& rhs ) const" );

            MATT44 m;
            m.v = v + rhs.v;
            return m;
        }


        MATT44 operator-( const MATT44& rhs ) const
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 > Matrix< T, 4, 4 >::operator-( const Matrix< T, 4, 4 >& rhs ) const" );

            MATT44 m;
            m.v = m.v - rhs.v;
            return m;
        }


        MATT44 operator*( const T& value ) const
        {
            TRACK("Matrix< T, 4, 4 > Matrix< T, 4, 4 >::operator*( const T& value ) const" );

            MATT44 m;
            m.v = v * value;
            return m;
        }


        MATT44 operator/( const T& value ) const
        {
            TRACK("Matrix< T, 4, 4 > Matrix< T, 4, 4 >::operator/( const T& value ) const" );

            MATT44 m;
            m.v = v / value;
            return m;
        }


        MATT44& operator+=( const MATT44& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >& Matrix< T, 4, 4 >::operator+=( const Matrix< T, 4, 4 >& rhs )" );

            v += rhs;
            return *this;
        }


        MATT44& operator-=( const MATT44& rhs )
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >& Matrix< T, 4, 4 >::operator-=( const Matrix< T, 4, 4 >& rhs )" );

            v -= rhs;
            return *this;
        }


        MATT44& operator*=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >& Matrix< T, 4, 4 >::operator*=( const T& value )" );

            v *= value;
            return *this;
        }


        MATT44& operator/=( const T& value )
        {
            DFT_FUNC_TRACK( "Matrix< T, 4, 4 >& Matrix< T, 4, 4 >::operator/=( const T& value )" );

            v /= value;
            return *this;
        }
    };


    template< typename T, unsigned ROWS1, unsigned COLS1, unsigned ROWS2, unsigned COLS2 >
    Matrix< T, ROWS1, COLS2 > Dot( const Matrix< T, ROWS1, COLS1 >& m1, const Matrix< T, ROWS2, COLS2 >& m2 )
    {
        DFT_FUNC_TRACK( "Matrix< T, ROWS1, COLS2 > Dot( const Matrix< T, ROWS1, COLS1 >& m1, const Matrix< T, ROWS2, COLS2 >& m2  )" );

        static_assert( COLS1 == ROWS2, "CANNOT MULTIPLY MATRICES WITH UNMATCHED COLUMNS AND ROWS" );
        Matrix< T, ROWS1, COLS2 > m;
        for( unsigned i = 0; i < ROWS1; ++i )
            for ( unsigned j = 0; j < COLS2; ++j )
            {
                // make a vector out of the second matrix's column
                Vector< T, ROWS2 > v2;
                for ( unsigned x = 0; x < ROWS2; ++x )
                    v2.m_data[x] = m2.m_data[x][j];
                m.m_data[i][j] = Dot< T >( MakeVec< T, COLS1 >( ( T* )m1.m_data[i] ), v2 );
            }
        return m;
    }


    template< typename T >
    MATT22 Dot( const MATT22& m1, const MATT22& m2 )
    {
        DFT_FUNC_TRACK( "Matrix< T, 2, 2 > Dot( const Matrix< T, 2, 2 >& m1, const Matrix< T, 2, 2 >& m2  )" );

        MATT22 m;
        m._00 = Dot< T >( MakeVec2< T >( m1._00, m1._01 ), MakeVec2< T >( m2._00, m2._10 ) );
        m._01 = Dot< T >( MakeVec2< T >( m1._00, m1._01 ), MakeVec2< T >( m2._01, m2._11 ) );
        m._10 = Dot< T >( MakeVec2< T >( m1._10, m1._11 ), MakeVec2< T >( m2._00, m2._10 ) );
        m._11 = Dot< T >( MakeVec2< T >( m1._10, m1._11 ), MakeVec2< T >( m2._01, m2._11 ) );
        return m;
    }


    template< typename T >
    MATT33 Dot( const MATT33& m1, const MATT33& m2 )
    {
        DFT_FUNC_TRACK( "Matrix< T, 3, 3 > Dot( const Matrix< T, 3, 3 >& m1, const Matrix< T, 3, 3 >& m2  )" );

        MATT33 m;
        m._00 = Dot< T >( MakeVec3< T >( m1._00, m1._01, m1._02 ), MakeVec3< T >( m2._00, m2._10, m2._20 ) );
        m._01 = Dot< T >( MakeVec3< T >( m1._00, m1._01, m1._02 ), MakeVec3< T >( m2._01, m2._11, m2._21 ) );
        m._02 = Dot< T >( MakeVec3< T >( m1._00, m1._01, m1._02 ), MakeVec3< T >( m2._02, m2._12, m2._22 ) );
        m._10 = Dot< T >( MakeVec3< T >( m1._10, m1._11, m1._12 ), MakeVec3< T >( m2._00, m2._10, m2._20 ) );
        m._11 = Dot< T >( MakeVec3< T >( m1._10, m1._11, m1._12 ), MakeVec3< T >( m2._01, m2._11, m2._21 ) );
        m._12 = Dot< T >( MakeVec3< T >( m1._10, m1._11, m1._12 ), MakeVec3< T >( m2._02, m2._12, m2._22 ) );
        m._20 = Dot< T >( MakeVec3< T >( m1._20, m1._21, m1._22 ), MakeVec3< T >( m2._00, m2._10, m2._20 ) );
        m._21 = Dot< T >( MakeVec3< T >( m1._20, m1._21, m1._22 ), MakeVec3< T >( m2._01, m2._11, m2._21 ) );
        m._22 = Dot< T >( MakeVec3< T >( m1._20, m1._21, m1._22 ), MakeVec3< T >( m2._02, m2._12, m2._22 ) );
        return m;
    }


    template< typename T >
    MATT44 Dot( const MATT44& m1, const MATT44& m2 )
    {
        DFT_FUNC_TRACK( "Matrix< T, 4, 4 > Dot( const Matrix< T, 4, 4 >& m1, const Matrix< T, 4, 4 >& m2  )" );

        MATT44 m;
        m._00 = Dot< T >( MakeVec4< T >( m1._00, m1._01, m1._02, m1._03 ), MakeVec4< T >( m2._00, m2._10, m2._20, m3._30 ) );
        m._01 = Dot< T >( MakeVec4< T >( m1._00, m1._01, m1._02, m1._03 ), MakeVec4< T >( m2._01, m2._11, m2._21, m3._31 ) );
        m._02 = Dot< T >( MakeVec4< T >( m1._00, m1._01, m1._02, m1._03 ), MakeVec4< T >( m2._02, m2._12, m2._22, m3._32 ) );
        m._03 = Dot< T >( MakeVec4< T >( m1._00, m1._01, m1._02, m1._03 ), MakeVec4< T >( m2._03, m2._13, m2._23, m3._33 ) );
        m._10 = Dot< T >( MakeVec4< T >( m1._10, m1._11, m1._12, m1._13 ), MakeVec4< T >( m2._00, m2._10, m2._20, m3._30 ) );
        m._11 = Dot< T >( MakeVec4< T >( m1._10, m1._11, m1._12, m1._13 ), MakeVec4< T >( m2._01, m2._11, m2._21, m3._31 ) );
        m._12 = Dot< T >( MakeVec4< T >( m1._10, m1._11, m1._12, m1._13 ), MakeVec4< T >( m2._02, m2._12, m2._22, m3._32 ) );
        m._13 = Dot< T >( MakeVec4< T >( m1._10, m1._11, m1._12, m1._13 ), MakeVec4< T >( m2._03, m2._13, m2._23, m3._33 ) );
        m._20 = Dot< T >( MakeVec4< T >( m1._20, m1._21, m1._22, m1._23 ), MakeVec4< T >( m2._00, m2._10, m2._20, m3._30 ) );
        m._21 = Dot< T >( MakeVec4< T >( m1._20, m1._21, m1._22, m1._23 ), MakeVec4< T >( m2._01, m2._11, m2._21, m3._31 ) );
        m._22 = Dot< T >( MakeVec4< T >( m1._20, m1._21, m1._22, m1._23 ), MakeVec4< T >( m2._02, m2._12, m2._22, m3._32 ) );
        m._23 = Dot< T >( MakeVec4< T >( m1._20, m1._21, m1._22, m1._23 ), MakeVec4< T >( m2._03, m2._13, m2._23, m3._33 ) );
        m._30 = Dot< T >( MakeVec4< T >( m1._30, m1._31, m1._32, m1._33 ), MakeVec4< T >( m2._00, m2._10, m2._20, m3._30 ) );
        m._31 = Dot< T >( MakeVec4< T >( m1._30, m1._31, m1._32, m1._33 ), MakeVec4< T >( m2._01, m2._11, m2._21, m3._31 ) );
        m._32 = Dot< T >( MakeVec4< T >( m1._30, m1._31, m1._32, m1._33 ), MakeVec4< T >( m2._02, m2._12, m2._22, m3._32 ) );
        m._33 = Dot< T >( MakeVec4< T >( m1._30, m1._31, m1._32, m1._33 ), MakeVec4< T >( m2._03, m2._13, m2._23, m3._33 ) );
        return m;
    }

#ifdef USE_DFT_LIB
    template< typename T, unsigned ROWS, unsigned COLS >
    DebugForTest::FunctionTracker Matrix< T, ROWS, COLS >::s_functionTracker;
    template< typename T >
    DebugForTest::FunctionTracker Matrix< T, 2, 2 >::s_functionTracker;
    template< typename T >
    DebugForTest::FunctionTracker Matrix< T, 3, 3 >::s_functionTracker;
    template< typename T >
    DebugForTest::FunctionTracker Matrix< T, 4, 4 >::s_functionTracker;
#endif

}

#endif
