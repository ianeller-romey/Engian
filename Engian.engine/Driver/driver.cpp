
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
  Util::Vector< int > vector;
  Util::UnsafeVector< float > uVector;
  Util::String string;
  Util::SortedVector< unsigned > sVector;
  Util::List< long > list;
  Util::SortedList< double > sList;
  Util::HashTable< int, int > hashTable;
  Util::Dictionary< char > dictionary;
}
