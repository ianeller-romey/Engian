
#include "testTestHelper_UtilHashTable.h"
#include "testTestHelper_UtilContainer.h"

#include "testUnitTestSampleStruct.h"
#include "testUnitTestSampleClass.h"

#include "utilHashTable.h"
#include "utilString.h"
#include "utilKeyValuePair.h"

#include <iostream>
#include <fstream>


#define RETURNLINEIFFAILED( check ) if( ( check ) == false ) return __LINE__;


namespace Test
{

  unsigned const TestHelper_UtilHashTable::KeyedIterator_CopyConstructor()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::KeyedIterator_Constructor0()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::KeyedIterator_Constructor1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::KeyedIterator_Key()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::KeyedIterator_PrefixIncrement()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::KeyedIterator_BasicAssignment()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_Constructor0()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_Constructor1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_CopyConstructor()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_Clone()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_Key()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_AdvanceValue()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_GetValue()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_GetKey()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_EqualTo()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_NotEqualTo()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTableIteratorImpl_BasicAssignment()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor0()
  {
    Util::HashTable< UnitTestSampleClass, Util::String > hashTable;
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor2()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor3()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor4()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor5()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Constructor6()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_CopyConstructor()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Begin()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_End()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_KeyedBegin()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_KeyedEnd()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_PushFront()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_PushBack()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Push0()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Push1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_PopFront()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_PopBack()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_PopFirst()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_PopAll()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Pop()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_GetKeys()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_GetCapacity()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Clear0()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Clear1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_CheckAndGrow()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Grow()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Deallocate()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_CreateKeyedIteratorFromImplementation()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_BasicAssignment0()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_BasicAssignment1()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_ArraySubscript()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_Addition()
  {
    return 0;
  }


  unsigned const TestHelper_UtilHashTable::HashTable_AdditionAssignment()
  {
    return 0;
  }


  template< typename T, typename KEY >
  unsigned const TestHelper_UtilHashTable::CheckUtilHashTable( Util::HashTable< T, KEY > const& hTable, Util::Container< Util::KeyValuePair< T, KEY > > const& contains )
  {
    auto counted = 0;
    for( auto i = 0; i < hTable.m_buckets; ++i )
    {
      auto node = hTable.m_buckets[ i ];
      while( node != NULL )
      {
        ++counted;
        node = node->m_next;
      }
    }
    RETURNLINEIFFAILED( counted == hTable.m_size );

    for( auto itB = contains.Begin(), itE = contains.End(); itB != itE; ++itB )
    {
      auto kv = *itB;
      RETURNLINEIFFAILED( hTable[ kv.m_value2 ] == kv.m_value1 );
    }
  }

}
