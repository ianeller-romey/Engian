#ifndef TEST_TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_H
#define TEST_TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_H

#include "memoryHomogeneousMemoryManager.h"


namespace Test
{

  class TestHelper_MemoryHomogeneousMemoryManager
  {
    public:
      static unsigned const Block_Constructor();
      static unsigned const Block_IsBlockFull();
      static unsigned const Block_IsObjectAvailable();
      static unsigned const Block_ToggleObjectAvailability();
      static unsigned const Block_GetObject();
      static unsigned const Page_Constructor();
      static unsigned const Page_Destructor();
      static unsigned const Page_Allocate0();
      static unsigned const Page_Allocate1();
      static unsigned const Page_Free();
      static unsigned const Page_ObjectsInUse();
      static unsigned const Page_IsFull();
      static unsigned const Page_IsOnPage();
      static unsigned const PageNode_Constructor();
      static unsigned const HomogeneousMemoryManager_Constructor();
      static unsigned const HomogeneousMemoryManager_INSTANCE();
      static unsigned const HomogeneousMemoryManager_Allocate0();
      static unsigned const HomogeneousMemoryManager_Allocate1();
      static unsigned const HomogeneousMemoryManager_Free();
  };

}

#endif
