extern "C" {
#include "lua.h"
}


namespace Behavior
{

	class LuaBehavior
	{
		public:
			LuaBehavior();

			void Inquire();
			void Execute();
			

		private:
			unsigned m_numInformation;
			char* m_information;
			unsigned m_numInqueries;
			char* m_inqueries;

			lua_State* m_luaState;
			long m_entityId;
	};

}
