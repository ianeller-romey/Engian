
#include "LuaBehavior.h"
#include "BehaviorManager.h"


namespace Behavior
{

	LuaBehavior::LuaBehavior()
	{
	}


	void LuaBehavior::Inquire()
	{
		for( unsigned i = 0; i < m_numInqueries; ++i )
		{
			Information* info = BehaviorManager::Instance()->InqueryToInformation( m_inqueries[ m_numInqueries ], m_entityId );
		}
	}

}
