
#include "Information.h"


namespace Behavior
{

	class InformationBool : Information
	{

		public:
			InformationBool( bool const & value );
			virtual char const * const Value() const;
			virtual unsigned const Size() const;


		private:
			bool m_value;
	};

}
