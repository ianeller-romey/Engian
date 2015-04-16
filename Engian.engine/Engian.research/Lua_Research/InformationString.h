
#include "Information.h"


namespace Behavior
{

	class InformationString : Information
	{

		public:
			InformationString( char const * const value );
			virtual char const * const Value() const;
			virtual unsigned const Size() const;


		private:
			char* m_value;
			unsigned m_size;
	};

}
