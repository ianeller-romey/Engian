#ifndef TEST_TESTHELPER_UTILHASHTABLE_H
#define TEST_TESTHELPER_UTILHASHTABLE_H

namespace ClassNamespace
{
  class ClassName;
}


namespace Test
{

  class TestHelper_UtilHashTable
  {
    public:

      static unsigned const KeyedIterator_CopyConstructor( char const * const name );
      static unsigned const KeyedIterator_Constructor0( char const * const name );
      static unsigned const KeyedIterator_Constructor1( char const * const name );
      static unsigned const KeyedIterator_Key( char const * const name );
      static unsigned const KeyedIterator_PrefixIncrement( char const * const name );
      static unsigned const KeyedIterator_BasicAssignment( char const * const name );
      static unsigned const HashTableIteratorImpl_Constructor0( char const * const name );
      static unsigned const HashTableIteratorImpl_Constructor1( char const * const name );
      static unsigned const HashTableIteratorImpl_CopyConstructor( char const * const name );
      static unsigned const HashTableIteratorImpl_Clone( char const * const name );
      static unsigned const HashTableIteratorImpl_Key( char const * const name );
      static unsigned const HashTableIteratorImpl_AdvanceValue( char const * const name );
      static unsigned const HashTableIteratorImpl_GetValue( char const * const name );
      static unsigned const HashTableIteratorImpl_GetKey( char const * const name );
      static unsigned const HashTableIteratorImpl_EqualTo( char const * const name );
      static unsigned const HashTableIteratorImpl_NotEqualTo( char const * const name );
      static unsigned const HashTableIteratorImpl_BasicAssignment( char const * const name );
      static unsigned const HashTable_Constructor0( char const * const name );
      static unsigned const HashTable_Constructor1( char const * const name );
      static unsigned const HashTable_Constructor2( char const * const name );
      static unsigned const HashTable_Constructor3( char const * const name );
      static unsigned const HashTable_Constructor4( char const * const name );
      static unsigned const HashTable_Constructor5( char const * const name );
      static unsigned const HashTable_Constructor6( char const * const name );
      static unsigned const HashTable_CopyConstructor( char const * const name );
      static unsigned const HashTable_Begin( char const * const name );
      static unsigned const HashTable_End( char const * const name );
      static unsigned const HashTable_KeyedBegin( char const * const name );
      static unsigned const HashTable_KeyedEnd( char const * const name );
      static unsigned const HashTable_PushFront( char const * const name );
      static unsigned const HashTable_PushBack( char const * const name );
      static unsigned const HashTable_Push0( char const * const name );
      static unsigned const HashTable_Push1( char const * const name );
      static unsigned const HashTable_PopFront( char const * const name );
      static unsigned const HashTable_PopBack( char const * const name );
      static unsigned const HashTable_PopFirst( char const * const name );
      static unsigned const HashTable_PopAll( char const * const name );
      static unsigned const HashTable_Pop( char const * const name );
      static unsigned const HashTable_GetKeys( char const * const name );
      static unsigned const HashTable_GetCapacity( char const * const name );
      static unsigned const HashTable_Clear0( char const * const name );
      static unsigned const HashTable_Clear1( char const * const name );
      static unsigned const HashTable_CheckAndGrow( char const * const name );
      static unsigned const HashTable_Grow( char const * const name );
      static unsigned const HashTable_Deallocate( char const * const name );
      static unsigned const HashTable_CreateKeyedIteratorFromImplementation( char const * const name );
      static unsigned const HashTable_BasicAssignment0( char const * const name );
      static unsigned const HashTable_BasicAssignment1( char const * const name );
      static unsigned const HashTable_ArraySubscript( char const * const name );
      static unsigned const HashTable_Addition( char const * const name );
      static unsigned const HashTable_AdditionAssignment( char const * const name );
  };

}

#endif
