extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "BehaviorManager.h"


int main()
{
	Behavior::BehaviorManager* manager = Behavior::BehaviorManager::Instance();
	return 0;
}
