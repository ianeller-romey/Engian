extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "BehaviorManager.h"


namespace Behavior
{
	
	BehaviorManager* BehaviorManager::s_instance = NULL;


	BehaviorManager* BehaviorManager::Instance()
	{
		if( s_instance == NULL )
			s_instance = new BehaviorManager();
		return s_instance;
	}

		
	Information* BehaviorManager::InqueryToInformation( int inqueryId, long entityId )
	{
		return NULL;
	}


	BehaviorManager::BehaviorManager()
	{
		lua_State *L = luaL_newstate();
		luaL_loadfile(L, "..\\Lua_Research\\Config.lua");
		lua_close(L);
	}

}
