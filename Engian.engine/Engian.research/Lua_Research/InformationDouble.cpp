
#include "InformationDouble.h"


namespace Behavior
{

	InformationDouble::InformationDouble( double const & value ) :
		m_value( value )
	{
	}


	char const * const InformationDouble::Value() const
	{
		return (char const * const)( &m_value );
	}


	unsigned const InformationDouble::Size() const
	{
		return sizeof( double );
	}

}
