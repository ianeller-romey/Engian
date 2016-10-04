
#ifndef MEMORY_HETEROGENEOUSMEMORYMANAGER_H
#define MEMORY_HETEROGENEOUSMEMORYMANAGER_H

// debug
#include "debugForTestDefines.h"


#ifdef USE_DFT_LIB
namespace Test
{
    class TestHelper_HeterogeneousMemoryManager;
}
#define TESTHELPER_MEMORYHETEROGENEOUSMEMORYMANAGER_FRIEND friend class Test::TestHelper_HeterogeneousMemoryManager
#else
#define TESTHELPER_MEMORYHETEROGENEOUSMEMORYMANAGER_FRIEND
#endif


namespace Memory 
{

    class HeterogeneousMemoryManager
    {
        public:
            DFT_FUNC_TRACK_CLASS_DEC;
            TESTHELPER_MEMORYHETEROGENEOUSMEMORYMANAGER_FRIEND;

            HeterogeneousMemoryManager();
            ~HeterogeneousMemoryManager();

            void* Allocate( size_t size );
            void Free( void* memory );

            void Defragment();

        private:
            static const unsigned c_totalPageSize;

            HeterogeneousMemoryManager( const HeterogeneousMemoryManager& rhs );
            HeterogeneousMemoryManager& operator=( const HeterogeneousMemoryManager& rhs );

            class Page
            {
                public:
                    DFT_FUNC_TRACK_CLASS_DEC;
                    TESTHELPER_MEMORYHETEROGENEOUSMEMORYMANAGER_FRIEND;

                    Page( const unsigned totalSize );
                    ~Page();

                    void* Allocate( const unsigned size );
                    void Free( void* memory );

                    const bool CanFitOnPage( const unsigned size ) const;
                    const bool IsOnPage( void* memory ) const;

                    void Defragment();

                private:
                    Page( const Page& rhs );
                    Page& operator=( const Page& rhs );

                    struct Object
                    {
                        DFT_FUNC_TRACK_CLASS_DEC;
                        TESTHELPER_MEMORYHETEROGENEOUSMEMORYMANAGER_FRIEND;

                        unsigned m_size;
                        Object* m_next;
                        char* m_blob;

                        Object( unsigned size );
                        Object( unsigned size, Object* next );

                        const bool IsObjectAvailable() const;
                        void* GetObject();
                        void ReleaseObject();
                    };

                    void* Allocate( const unsigned size, Object* currentObject );

                    void Consolidate( Object* object );
                    
                    char* m_objects;
                    Object* m_current;
                    const unsigned c_totalSize;
                    unsigned m_sizeInUse;
            };

            struct PageNode
            {
                DFT_FUNC_TRACK_CLASS_DEC;
                TESTHELPER_MEMORYHETEROGENEOUSMEMORYMANAGER_FRIEND;

                PageNode* m_next;
                Page m_page;

                PageNode( const unsigned totalSize );
            };

            PageNode *m_pageNodes,
                     *m_currentNode;

            void* Allocate( const unsigned size, PageNode* currentPageNode );
    };

}

#endif
