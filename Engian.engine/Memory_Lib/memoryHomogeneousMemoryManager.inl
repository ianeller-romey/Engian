
#define OBJECT_IS_AVAILABLE( x ) ( x == 0 )
#define BLOCK_IS_FULL( x ) ( x == (char)0xff )

namespace Memory
{

#ifdef USE_DFT_LIB
    template< unsigned SIZE >
    DebugForTest::FunctionTracker HomogeneousMemoryManager< SIZE >::s_functionTracker;
    template< unsigned SIZE >
    DebugForTest::FunctionTracker HomogeneousMemoryManager< SIZE >::Page::s_functionTracker;
    template< unsigned SIZE >
    DebugForTest::FunctionTracker HomogeneousMemoryManager< SIZE >::Page::Block::s_functionTracker;
    template< unsigned SIZE >
    DebugForTest::FunctionTracker HomogeneousMemoryManager< SIZE >::PageNode::s_functionTracker;
#endif


    template< unsigned SIZE >
    const unsigned HomogeneousMemoryManager< SIZE >::c_numObjectsPerPage = 512;


    template< unsigned SIZE >
    void* HomogeneousMemoryManager< SIZE >::Allocate()
    {
        DFT_FUNC_TRACK( "void* HomogeneousMemoryManager< T >::Allocate()" );

        return Allocate( m_currentNode );
    }


    template< unsigned SIZE >
    void HomogeneousMemoryManager< SIZE >::Free( void* memory )
    {
        DFT_FUNC_TRACK( "void HomogeneousMemoryManager< T >::Free( void* memory )" );

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


    template< unsigned SIZE >
    HomogeneousMemoryManager< SIZE >::HomogeneousMemoryManager() :
        m_pageNodes( new PageNode( c_numObjectsPerPage ) ),
        m_currentNode( m_pageNodes )
    {
        DFT_FUNC_TRACK( "HomogeneousMemoryManager< T >::HomogeneousMemoryManager()" );
    }


    template< unsigned SIZE >
    HomogeneousMemoryManager< SIZE >::~HomogeneousMemoryManager()
    {
        DFT_FUNC_TRACK( "HomogeneousMemoryManager< T >::~HomogeneousMemoryManager()" );

        while ( m_pageNodes )
        {
            m_currentNode = m_pageNodes;
            m_pageNodes = m_pageNodes->m_next;
            delete m_currentNode;
        }
        m_pageNodes = 0;
        m_currentNode = 0;
    }


    template< unsigned SIZE >
    void* HomogeneousMemoryManager< SIZE >::Allocate( PageNode* currentPageNode )
    {
        DFT_FUNC_TRACK( "void* HomogeneousMemoryManager< T >::Allocate( PageNode* currentPageNode )" );

        auto lastPageNode = currentPageNode;
        do
        {
            // if we've found an available page, break
            if ( !currentPageNode->m_page.IsFull() )
            {
                m_currentNode = currentPageNode;
                return currentPageNode->m_page.Allocate();
            }

            // otherwise, we'll check the next page
            currentPageNode = currentPageNode->m_next;

            // if we've reached the end, start over
            if ( currentPageNode == 0 )
                currentPageNode = m_pageNodes;
        } while ( currentPageNode != lastPageNode );

        // if we've made it this far, we need a new page
        auto newPage = new PageNode( c_numObjectsPerPage );
        newPage->m_next = m_currentNode->m_next;
        m_currentNode->m_next = newPage;
        m_currentNode = newPage;

        return m_currentNode->m_page.Allocate();
    }


    template< unsigned SIZE >
    HomogeneousMemoryManager< SIZE >::Page::Page( const unsigned numObjects ) :
        c_numObjects( numObjects ),
        c_numBlocks( c_numObjects / OBJECTS_PER_BLOCK ),
        m_objectsInUse( 0 )
    {
        DFT_FUNC_TRACK( "HomogeneousMemoryManager< T >::Page::Page( const unsigned numObjects )" );

        m_blocks = new Block[c_numBlocks];
        m_current = m_blocks;
    }


    template< unsigned SIZE >
    HomogeneousMemoryManager< SIZE >::Page::~Page()
    {
        DFT_FUNC_TRACK( "HomogeneousMemoryManager< T >::Page::~Page()" );

        delete[] m_blocks;
        m_blocks = 0;
        m_current = 0;
        m_objectsInUse = 0;
    }


    template< unsigned SIZE >
    void* HomogeneousMemoryManager< SIZE >::Page::Allocate()
    {
        DFT_FUNC_TRACK( "void* HomogeneousMemoryManager< T >::Page::Allocate()" );

        return Allocate( m_current );
    }


    template< unsigned SIZE >
    void HomogeneousMemoryManager< SIZE >::Page::Free( void* memory )
    {
        DFT_FUNC_TRACK( "void HomogeneousMemoryManager< T >::Page::Free( void* memory )" );

        auto memoryAddress = (unsigned)memory;
        auto blockAddress = (unsigned)m_blocks;

        auto difference = memoryAddress - blockAddress;

        auto numBlocks = difference / sizeof( Block );

        auto currentBlock = m_blocks + numBlocks;

        currentBlock->ToggleObjectAvailability( ( (char*)memory - ( currentBlock->m_blob ) ) / SIZE );

        --m_objectsInUse;
    }


    template< unsigned SIZE >
    const unsigned HomogeneousMemoryManager< SIZE >::Page::ObjectsInUse() const
    {
        DFT_FUNC_TRACK( "const unsigned HomogeneousMemoryManager< T >::Page::ObjectsInUse() const" );

        return m_objectsInUse;
    }


    template< unsigned SIZE >
    const bool HomogeneousMemoryManager< SIZE >::Page::IsFull() const
    {
        DFT_FUNC_TRACK( "const bool HomogeneousMemoryManager< T >::Page::IsFull() const" );

        return m_objectsInUse == c_numObjects;
    }


    template< unsigned SIZE >
    const bool HomogeneousMemoryManager< SIZE >::Page::IsOnPage( void* memory ) const
    {
        DFT_FUNC_TRACK( "const bool HomogeneousMemoryManager< T >::Page::IsOnPage( void* memory ) const" );

        return memory >= m_blocks && memory < m_blocks + c_numBlocks;
    }


    template< unsigned SIZE >
    void* HomogeneousMemoryManager< SIZE >::Page::Allocate( Block* currentBlock )
    {
        DFT_FUNC_TRACK( "void* HomogeneousMemoryManager< T >::Page::Allocate( Block* currentBlock ) const" );

        auto lastBlock = currentBlock;
        do
        {
            if ( !currentBlock->IsBlockFull() )
            {
                for ( unsigned i = 0, j = OBJECTS_PER_BLOCK; i < j; ++i )
                {
                    if ( currentBlock->IsObjectAvailable( i ) )
                    {
                        m_current = currentBlock;
                        ++m_objectsInUse;
                        currentBlock->ToggleObjectAvailability( i );
                        return currentBlock->GetObject( i );
                    }
                }
            }
            currentBlock = currentBlock + 1;
            if ( currentBlock >= m_blocks + c_numBlocks )
                currentBlock = m_blocks;
        } while ( currentBlock != lastBlock );

        // theoretically, we shouldn't be able to get this far; before we get into this function, we verify that
        // there is space available
    }


    template< unsigned SIZE >
    HomogeneousMemoryManager< SIZE >::Page::Block::Block() :
        m_objectsInUse( 0 )
    {
        DFT_FUNC_TRACK( "HomogeneousMemoryManager< T >::Page::Block::Block()" );
    }


    template< unsigned SIZE >
    const bool HomogeneousMemoryManager< SIZE >::Page::Block::IsBlockFull() const
    {
        DFT_FUNC_TRACK( "const bool HomogeneousMemoryManager< T >::Page::Block::IsBlockFull() const" );

        return BLOCK_IS_FULL( m_objectsInUse );
    }


    template< unsigned SIZE >
    const bool HomogeneousMemoryManager< SIZE >::Page::Block::IsObjectAvailable( const unsigned object ) const
    {
        DFT_FUNC_TRACK( "const bool HomogeneousMemoryManager< T >::Page::Block::IsObjectAvailable( const unsigned object ) const" );

        return OBJECT_IS_AVAILABLE( getBit( m_objectsInUse, object ) );
    }


    template< unsigned SIZE >
    void HomogeneousMemoryManager< SIZE >::Page::Block::ToggleObjectAvailability( const unsigned object )
    {
        DFT_FUNC_TRACK( "void HomogeneousMemoryManager< T >::Page::Block::ToggleObjectAvailability( const unsigned object )" );

        toggleBit( m_objectsInUse, object );
    }


    template< unsigned SIZE >
    void* HomogeneousMemoryManager< SIZE >::Page::Block::GetObject( const unsigned object )
    {
        DFT_FUNC_TRACK( "void* HomogeneousMemoryManager< T >::Page::Block::GetObject( const unsigned object )" );

        return m_blob + ( SIZE * object );
    }


    template< unsigned SIZE >
    HomogeneousMemoryManager< SIZE >::PageNode::PageNode( const unsigned numObjects ) :
        m_next( 0 ),
        m_page( numObjects )
    {
        DFT_FUNC_TRACK( "HomogeneousMemoryManager< SIZE >::PageNode::PageNode( const unsigned numObjects )" );
    }

}
