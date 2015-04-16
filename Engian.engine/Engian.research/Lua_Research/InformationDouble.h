
#include "Information.h"


namespace Behavior
{

	class InformationDouble : Information
	{

		public:
			InformationDouble( double const & value );
			virtual char const * const Value() const;
			virtual unsigned const Size() const;


		private:
			double m_value;
	};

}
