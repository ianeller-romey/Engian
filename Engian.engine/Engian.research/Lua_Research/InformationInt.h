
#include "Information.h"


namespace Behavior
{

	class InformationInt : Information
	{

		public:
			InformationInt( int const & value );
			virtual char const * const Value() const;
			virtual unsigned const Size() const;


		private:
			int m_value;
	};

}
