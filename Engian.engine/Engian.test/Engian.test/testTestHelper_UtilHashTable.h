#ifndef TEST_TESTHELPER_UTILHASHTABLE_H
#define TEST_TESTHELPER_UTILHASHTABLE_H

namespace Util
{
  template< typename T > class Container;
  template< typename T, typename KEY > class HashTable;
  template< typename T1, typename T2 > struct KeyValuePair;
}


namespace Test
{

  class TestHelper_UtilHashTable
  {
    public:

      static unsigned const KeyedIterator_CopyConstructor();
      static unsigned const KeyedIterator_Constructor0();
      static unsigned const KeyedIterator_Constructor1();
      static unsigned const KeyedIterator_Key();
      static unsigned const KeyedIterator_PrefixIncrement();
      static unsigned const KeyedIterator_BasicAssignment();
      static unsigned const HashTableIteratorImpl_Constructor0();
      static unsigned const HashTableIteratorImpl_Constructor1();
      static unsigned const HashTableIteratorImpl_CopyConstructor();
      static unsigned const HashTableIteratorImpl_Clone();
      static unsigned const HashTableIteratorImpl_Key();
      static unsigned const HashTableIteratorImpl_AdvanceValue();
      static unsigned const HashTableIteratorImpl_GetValue();
      static unsigned const HashTableIteratorImpl_GetKey();
      static unsigned const HashTableIteratorImpl_EqualTo();
      static unsigned const HashTableIteratorImpl_NotEqualTo();
      static unsigned const HashTableIteratorImpl_BasicAssignment();
      static unsigned const HashTable_Constructor0();
      static unsigned const HashTable_Constructor1();
      static unsigned const HashTable_Constructor2();
      static unsigned const HashTable_Constructor3();
      static unsigned const HashTable_Constructor4();
      static unsigned const HashTable_Constructor5();
      static unsigned const HashTable_Constructor6();
      static unsigned const HashTable_CopyConstructor();
      static unsigned const HashTable_Begin();
      static unsigned const HashTable_End();
      static unsigned const HashTable_KeyedBegin();
      static unsigned const HashTable_KeyedEnd();
      static unsigned const HashTable_PushFront();
      static unsigned const HashTable_PushBack();
      static unsigned const HashTable_Push0();
      static unsigned const HashTable_Push1();
      static unsigned const HashTable_PopFront();
      static unsigned const HashTable_PopBack();
      static unsigned const HashTable_PopFirst();
      static unsigned const HashTable_PopAll();
      static unsigned const HashTable_Pop();
      static unsigned const HashTable_GetKeys();
      static unsigned const HashTable_GetCapacity();
      static unsigned const HashTable_Clear0();
      static unsigned const HashTable_Clear1();
      static unsigned const HashTable_CheckAndGrow();
      static unsigned const HashTable_Grow();
      static unsigned const HashTable_Deallocate();
      static unsigned const HashTable_CreateKeyedIteratorFromImplementation();
      static unsigned const HashTable_BasicAssignment0();
      static unsigned const HashTable_BasicAssignment1();
      static unsigned const HashTable_ArraySubscript();
      static unsigned const HashTable_Addition();
      static unsigned const HashTable_AdditionAssignment();


  private:
    template< typename T, typename KEY >
    static unsigned const CheckUtilHashTable( Util::HashTable< T, KEY > const& hTable, Util::Container< Util::KeyValuePair< T, KEY > > const& contains );
  };

}

#endif
