

// Math
#include "mathVector.h"
#include "mathMatrix.h"

// Memory
#include "memoryHomogeneousMemoryManager.h"
#include "memoryHeterogeneousMemoryManager.h"

// Util
#include "utilVector.h"
#include "utilUnsafeVector.h"
#include "utilString.h"
#include "utilSortedVector.h"
#include "utilList.h"
#include "utilSortedList.h"
#include "utilHashTable.h"
#include "utilDictionary.h"


void main( void )
{
    {
        Math::FVec2 fVector2;
        Math::IVec3 iVector3;
        Math::DVec4 dVector4;
        Math::Vector< unsigned, 5 > vector;

        Math::FMat22 mMatrix22;
        Math::IMat33 iMatrix33;
        Math::DMat44 dMatrix44;
        Math::Matrix< unsigned, 5, 5 > matrix;
    }

    {
        auto d = Memory::HomogeneousMemoryManager< sizeof( unsigned ) >::INSTANCE().Allocate();
        Memory::HeterogeneousMemoryManager hetMemMan;
    }

    {
        Util::Vector< int > vector;
        Util::UnsafeVector< float > uVector;
        Util::String string;
        Util::SortedVector< unsigned > sVector;
        Util::List< long > list;
        Util::SortedList< double > sList;
        Util::HashTable< int, int > hashTable;
        Util::Dictionary< char > dictionary;
    }
}
