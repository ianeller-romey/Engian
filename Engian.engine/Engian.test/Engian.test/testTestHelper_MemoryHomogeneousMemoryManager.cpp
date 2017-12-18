
#include "testTestHelper_MemoryHomogeneousMemoryManager.h"


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Block_Constructor() 
    {
        auto allocation = Memory::HOMOGENEOUSINSTANCE_SIZEOF( unsigned ).Allocate();

        RETURNLINEIFFAILED( Memory::HOMOGENEOUSINSTANCE_SIZEOF( unsigned ).m_pageNodes );

        Memory::HomogeneousMemoryManager< sizeof(unsigned) >::INSTANCE().Free( allocation );
        return 0; 
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Block_IsBlockFull()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Block_IsObjectAvailable()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Block_ToggleObjectAvailability()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Block_GetObject()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_Constructor()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_Destructor()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_Allocate0()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_Allocate1()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_Free()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_ObjectsInUse()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_IsFull()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::Page_IsOnPage()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::PageNode_Constructor()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::HomogeneousMemoryManager_Constructor()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::HomogeneousMemoryManager_INSTANCE()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::HomogeneousMemoryManager_Allocate0()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::HomogeneousMemoryManager_Allocate1()
    {
        return 0;
    }


    unsigned const TestHelper_MemoryHomogeneousMemoryManager::HomogeneousMemoryManager_Free()
    {
        return 0;
    }

}
