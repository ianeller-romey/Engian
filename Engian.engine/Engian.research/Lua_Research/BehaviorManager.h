
#include "Information.h"


namespace Behavior
{

	class BehaviorManager
	{
		public:
			static BehaviorManager* Instance();

			Information* InqueryToInformation( int inqueryId, long entityId );


		private:
			static BehaviorManager* s_instance;

			BehaviorManager();
	};

}