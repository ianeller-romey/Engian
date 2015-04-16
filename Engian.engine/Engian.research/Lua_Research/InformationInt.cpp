
#include "InformationInt.h"


namespace Behavior
{

	InformationInt::InformationInt( int const & value ) :
		m_value( value )
	{
	}


	char const * const InformationInt::Value() const
	{
		return (char const * const)( &m_value );
	}


	unsigned const InformationInt::Size() const
	{
		return sizeof( int );
	}

}
