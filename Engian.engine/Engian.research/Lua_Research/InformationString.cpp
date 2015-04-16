
#include <cstring>

#include "InformationString.h"


namespace Behavior
{

	InformationString::InformationString( char const * const value )
	{
		m_size = strlen( value ) + 1;
		m_value = new char[ m_size ];
		strcpy( m_value, value );
	}


	char const * const InformationString::Value() const
	{
		return m_value;
	}


	unsigned const InformationString::Size() const
	{
		return m_size;
	}

}
