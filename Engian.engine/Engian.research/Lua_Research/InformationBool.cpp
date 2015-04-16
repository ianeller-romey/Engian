
#include "InformationBool.h"


namespace Behavior
{

	InformationBool::InformationBool( bool const & value ) :
		m_value( value )
	{
	}


	char const * const InformationBool::Value() const
	{
		return (char const * const)( &m_value );
	}


	unsigned const InformationBool::Size() const
	{
		return sizeof( bool );
	}

}
