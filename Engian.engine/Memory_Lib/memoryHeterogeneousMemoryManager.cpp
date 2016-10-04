
// Memory
#include "memoryHeterogeneousMemoryManager.h"

// std
#include <stdlib.h>
#include <new>


namespace Memory
{

#ifdef USE_DFT_LIB
    DebugForTest::FunctionTracker HeterogeneousMemoryManager::s_functionTracker;
    DebugForTest::FunctionTracker HeterogeneousMemoryManager::Page::s_functionTracker;
    DebugForTest::FunctionTracker HeterogeneousMemoryManager::Page::Object::s_functionTracker;
    DebugForTest::FunctionTracker HeterogeneousMemoryManager::PageNode::s_functionTracker;
#endif


    const unsigned HeterogeneousMemoryManager::c_totalPageSize = 1024;


    HeterogeneousMemoryManager::HeterogeneousMemoryManager() :
        m_pageNodes( new PageNode( c_totalPageSize ) ),
        m_currentNode( m_pageNodes )
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::HeterogeneousMemoryManager()" );
    }


    HeterogeneousMemoryManager::~HeterogeneousMemoryManager()
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::HeterogeneousMemoryManager()" );

        while ( m_pageNodes )
        {
            m_currentNode = m_pageNodes;
            m_pageNodes = m_pageNodes->m_next;
            delete m_currentNode;
        }
        m_pageNodes = 0;
        m_currentNode = 0;
    }


    void* HeterogeneousMemoryManager::Allocate( size_t size )
    {
        DFT_FUNC_TRACK( "void* HeterogeneousMemoryManager::Allocate( size_t size )" );

        return Allocate( size, m_currentNode );
    }


    void HeterogeneousMemoryManager::Free( void* memory )
    {
        DFT_FUNC_TRACK( "void HeterogeneousMemoryManager::Free( void* memory )" );

        // start at the beginning, don't worry about m_currentNode
        auto pageNode = m_pageNodes;
        while ( pageNode )
        {
            if ( pageNode->m_page.IsOnPage( memory ) )
            {
                pageNode->m_page.Free( memory );
                return;
            }
            pageNode = pageNode->m_next;
        }
    }


    void HeterogeneousMemoryManager::Defragment()
    {
        DFT_FUNC_TRACK( "void HeterogeneousMemoryManager::Defragment()" );

        auto node = m_pageNodes;
        while ( node )
        {
            node->m_page.Defragment();
            node = node->m_next;
        }
    }


    void* HeterogeneousMemoryManager::Allocate( const unsigned size, PageNode* currentPageNode )
    {
        DFT_FUNC_TRACK( "void* HeterogeneousMemoryManager::Allocate( const unsigned size, PageNode* currentPageNode )" );

        auto lastPageNode = currentPageNode;
        do
        {
            // if we've found an available page, break
            if ( currentPageNode->m_page.CanFitOnPage( size ) )
            {
                m_currentNode = currentPageNode;
                return currentPageNode->m_page.Allocate( size );
            }

            // otherwise, we'll check the next page
            currentPageNode = currentPageNode->m_next;

            // if we've reached the end, start over
            if ( currentPageNode == 0 )
                currentPageNode = m_pageNodes;
        } while ( currentPageNode != lastPageNode );

        // if we've made it this far, we need a new page
        auto newPage = new PageNode( c_totalPageSize );
        newPage->m_next = m_currentNode->m_next;
        m_currentNode->m_next = newPage;
        m_currentNode = newPage;

        return m_currentNode->m_page.Allocate( size );
    }


    HeterogeneousMemoryManager::Page::Page( const unsigned totalSize ) :
        m_objects( (char*)calloc( 1, totalSize ) ),
        m_current( (Object*)m_objects ),
        c_totalSize( totalSize ),
        m_sizeInUse( 0 )
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::Page::Page( const unsigned totalSize )" );

        new( m_current ) Object( c_totalSize );

        m_sizeInUse += sizeof( Object );
    }


    HeterogeneousMemoryManager::Page::~Page()
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::Page::~Page()" );

        free( m_objects );
        m_objects = 0;
        m_current = 0;
        m_sizeInUse = 0;
    }


    void* HeterogeneousMemoryManager::Page::Allocate( const unsigned size )
    {
        DFT_FUNC_TRACK( "void* HeterogeneousMemoryManager::Page::Allocate( const unsigned size )" );

        return Allocate( size, m_current );
    }


    void HeterogeneousMemoryManager::Page::Free( void* memory )
    {
        DFT_FUNC_TRACK( "void HeterogeneousMemoryManager::Page::Free( void* memory )" );

        // get object pointer
        Object* object = ( ( Object* )memory ) - 1;

        // "free" object
        object->ReleaseObject();

        // update size
        m_sizeInUse -= object->m_size;

        // check for object consolidation
        Consolidate( object );
    }


    const bool HeterogeneousMemoryManager::Page::CanFitOnPage( const unsigned size ) const
    {
        DFT_FUNC_TRACK( "const bool HeterogeneousMemoryManager::Page::CanFitOnPage( const unsigned size ) const" );

        return size <= ( c_totalSize - m_sizeInUse );
    }


    const bool HeterogeneousMemoryManager::Page::IsOnPage( void* memory ) const
    {
        DFT_FUNC_TRACK( "const bool HeterogeneousMemoryManager::Page::IsOnPage( void* memory ) const" );

        return memory >= m_objects && memory < m_objects + c_totalSize;
    }


    void HeterogeneousMemoryManager::Page::Defragment()
    {
        DFT_FUNC_TRACK( "void HeterogeneousMemoryManager::Page::Defragment()" );

        auto current = ( Object* )m_objects;
        while ( current )
        {
            Consolidate( current );
            current = current->m_next;
        }
    }


    void* HeterogeneousMemoryManager::Page::Allocate( const unsigned size, Object* currentObject )
    {
        DFT_FUNC_TRACK( "void* HeterogeneousMemoryManager::Page::Allocate( const unsigned size, Object* currentObject )" );

        void* forReturn = 0;
        auto lastObject = currentObject;
        do
        {
            if ( currentObject->IsObjectAvailable() )
            {
                if ( currentObject->m_size > size )
                {
                    char* currentCharPtr = ( char* )currentObject;

                    // create the next object if room remains
                    auto nextSize = currentObject->m_size - size - sizeof( Object );
                    if ( nextSize > 0 )
                    {
                        char* nextObject = currentCharPtr + sizeof( Object ) + size;
                        //                                           - size - size of newly created object
                        new( nextObject ) Object( nextSize, currentObject->m_next );
                        currentObject->m_next = ( Object* )nextObject;

                        // adjust "size in use" to account for the newly created object
                        m_sizeInUse += sizeof( Object );
                    }

                    // reset the current object's size
                    currentObject->m_size = size;

                    // the current object's blob is what we'll allocate
                    forReturn = currentObject->GetObject();
                }
                else if ( currentObject->m_size == size )
                {
                    forReturn = currentObject->GetObject();
                }
            }
            else
            { 
                currentObject = currentObject->m_next;

                // start over if we have to
                if ( currentObject == 0 )
                    currentObject = ( Object* )m_objects;
            }
        } while ( forReturn == 0 && currentObject != lastObject );

        m_current = currentObject->m_next;
        m_sizeInUse += size;
        return forReturn;
    }


    void HeterogeneousMemoryManager::Page::Consolidate( Object* object )
    {
        DFT_FUNC_TRACK( "void HeterogeneousMemoryManager::Page::Consolidate( Object* object )" );

        auto next = object->m_next;
        while ( next && next->IsObjectAvailable() )
        {
            object->m_size += next->m_size;

            // only subtract size of next object
            // size of next object's blob has already been subtracted
            m_sizeInUse -= sizeof( Object );

            next = next->m_next;
        }
    }


    HeterogeneousMemoryManager::Page::Object::Object( unsigned size ) :
        m_size( size ),
        m_blob( 0 ),
        m_next( 0 )
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::Page::Object::Object( unsigned size )" );
    }


    HeterogeneousMemoryManager::Page::Object::Object( unsigned size, Object* next ) :
        m_size( size ),
        m_blob( 0 ),
        m_next( next )
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::Page::Object::Object( unsigned size, Object* next )" );
    }


    const bool HeterogeneousMemoryManager::Page::Object::IsObjectAvailable() const
    {
        DFT_FUNC_TRACK( "const bool HeterogeneousMemoryManager::Page::Object::IsObjectAvailable() const" );

        return m_blob == 0;
    }


    void* HeterogeneousMemoryManager::Page::Object::GetObject()
    {
        DFT_FUNC_TRACK( "void* HeterogeneousMemoryManager::Page::Object::GetObject()" );

        if( m_blob == 0 )
            m_blob = ( ( char* )this ) + sizeof( Object );
        return m_blob;
    }


    void HeterogeneousMemoryManager::Page::Object::ReleaseObject()
    {
        DFT_FUNC_TRACK( "void HeterogeneousMemoryManager::Page::Object::ReleaseObject()" );

        m_blob = 0;
    }


    HeterogeneousMemoryManager::PageNode::PageNode( const unsigned totalSize ) :
        m_next( 0 ),
        m_page( totalSize )
    {
        DFT_FUNC_TRACK( "HeterogeneousMemoryManager::PageNode::PageNode( const unsigned totalSize )" );
    }

}
