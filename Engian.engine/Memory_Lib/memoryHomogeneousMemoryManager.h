
#ifndef MEMORY_HOMOGENEOUSMEMORYMANAGER_H
#define MEMORY_HOMOGENEOUSMEMORYMANAGER_H


// Utils
#include "memoryUtils.h"

// std
#include <stdlib.h>
#include <string.h>
#include <new>
#include <cmath>

// debug
#include "debugForTestDefines.h"


#ifdef USE_DFT_LIB
namespace Test
{
    class TestHelper_HomogeneousMemoryManager;
}
#define TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_FRIEND friend class Test::TestHelper_HomogeneousMemoryManager
#else
#define TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_FRIEND
#endif


#define OBJECTS_PER_BLOCK 8

#define HOMOGENEOUSINSTANCE( x ) HomogeneousMemoryManager< x >::INSTANCE()
#define HOMOGENEOUSINSTANCE_SIZEOF( x ) HOMOGENEOUSINSTANCE( sizeof( x ) )


namespace Memory 
{

    template < unsigned SIZE >
    class HomogeneousMemoryManager
    {
        public:
            DFT_FUNC_TRACK_CLASS_DEC;
            TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_FRIEND;

            static HomogeneousMemoryManager< SIZE >& INSTANCE()
            {
                DFT_FUNC_TRACK( "HomogeneousMemoryManager< SIZE >& HomogeneousMemoryManager< SIZE >::INSTANCE() )" );

                static HomogeneousMemoryManager< SIZE > manager;
                return manager;
            }

            void* Allocate();
            void Free( void* memory );

        private:
            static const unsigned c_numObjectsPerPage;
            static HomogeneousMemoryManager* s_instance;

            HomogeneousMemoryManager();
            ~HomogeneousMemoryManager();
            HomogeneousMemoryManager( const HomogeneousMemoryManager& rhs );
            HomogeneousMemoryManager& operator=( const HomogeneousMemoryManager& rhs );

            class Page
            {
                public:
                    DFT_FUNC_TRACK_CLASS_DEC;
                    TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_FRIEND;

                    Page( const unsigned numObjects );
                    ~Page();

                    void* Allocate();
                    void Free( void* memory );

                    const unsigned ObjectsInUse() const;
                    const bool IsFull() const;
                    const bool IsOnPage( void* memory ) const;

                private:
                    Page( const Page& rhs );
                    Page& operator=( const Page& rhs );

                    struct Block
                    {
                        DFT_FUNC_TRACK_CLASS_DEC;
                        TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_FRIEND;

                        char m_objectsInUse;
                        char m_blob[SIZE * OBJECTS_PER_BLOCK];

                        Block();

                        const bool IsBlockFull() const;
                        const bool IsObjectAvailable( const unsigned object ) const;
                        void ToggleObjectAvailability( const unsigned object );
                        void* GetObject( const unsigned object );
                    };

                    void* Allocate( Block* currentBlock );
                    
                    Block* m_blocks;
                    Block* m_current;
                    const unsigned c_numObjects,
                                   c_numBlocks;
                    unsigned m_objectsInUse;
            };

            struct PageNode
            {
                DFT_FUNC_TRACK_CLASS_DEC;
                TESTHELPER_MEMORYHOMOGENEOUSMEMORYMANAGER_FRIEND;

                PageNode* m_next;
                Page m_page;

                PageNode( const unsigned numObjects );
            };

            PageNode *m_pageNodes,
                     *m_currentNode;

            void* Allocate( PageNode* currentPageNode );
    };

}

#include "memoryHomogeneousMemoryManager.inl"

#endif
