
#include "utilList.h"


namespace Test
{  

  template< typename HELPER >
  struct UnitTestChassis_Helper_List
  {

    static char const * const CheckEmptyList( void* check )
    {
      Util::List< HELPER >* list = static_cast< Util::List< HELPER >* >( check );
      if( list->m_size != 0 ) return "did not properly initialize m_size";
      if( list->m_implementations != 0 ) return "did not properly initialize m_implementations";
      if( list->m_end == 0 ) return "m_end initialized to 0";
      if( list->m_end->m_prev != 0 ) return "m_end->m_prev not initialized to 0";
      if( list->m_end->m_next != 0 ) return "m_end->m_next not initialized to 0";
      if( list->m_end->m_data != 0 ) return "m_end->m_data not initialized to 0";
      if( list->m_front == 0 ) return "m_front initialized to 0";
      if( list->m_front != list->m_end ) return "m_front not initialized to m_end";
      if( list->m_back == 0 ) return "m_back initialized to 0";
      if( list->m_back != list->m_end ) return "m_back not initialized to m_end";
      return 0;
    }


    static char const * const CheckListFrontAndBack( void* check, unsigned const size, bool endCheck )
    {
      Util::List< HELPER >* list = static_cast< Util::List< HELPER >* >( check );
      if( list->m_size != size ) return "did not properly initialize m_size";
      if( list->m_implementations != 0 ) return "did not properly initialize m_implementations";
      if( list->m_end == 0 ) return "m_end initialized to 0";
      if( list->m_end->m_prev != 0 ) return "m_end->m_prev not initialized to 0";
      if( list->m_end->m_next != 0 ) return "m_end->m_next not initialized to 0";
      if( list->m_end->m_data != 0 ) return "m_end->m_data not initialized to 0";
      if( list->m_front == 0 ) return "m_front initialized to 0";
      if( list->m_back == 0 ) return "m_back initialized to 0";
      if( endCheck )
      {
        if( list->m_front == list->m_end ) return "m_front initialized to m_end";
        if( list->m_front->m_prev != list->m_end ) return "initialized m_front->m_prev to a non-m_end value";
        if( list->m_back == list->m_end ) return "m_back initialized to m_end";
        if( list->m_back->m_next != list->m_end ) return "initialized m_back->m_next to a non-m_end value"; 
      }
      return 0;
    }
  

    static char const * const CheckListAgainstArray( void* compareFrom, HELPER* compareAgainst, unsigned const arraySize, int const incr )
    {
      Util::List< HELPER >* list = static_cast< Util::List< HELPER >* >( compareFrom );

      int i = 0;
      Util::List< HELPER >::ListNode* node = list->m_front;
      for( ; node != list->m_end && abs( i ) < arraySize; node = node->m_next, i += incr )
      {
        if( node->m_prev != list->m_end )
        {
          if( ( *( node->m_prev->m_data ) == compareAgainst[ i - incr ] ) == false ) return "did not properly initialize a node's m_prev pointer";
        }
        else
          if( ( i == 0 ) == false ) return "did not properly initialize a node's m_prev pointer, as an element that isn't the first one has an m_prev pointer pointing to 0";

        if( node->m_next != list->m_end )
        {
          if( ( *( node->m_next->m_data ) == compareAgainst[ i + incr ] ) == false ) return "did not properly initialize a node's m_next pointer";
        }
        else
          if( ( abs( i ) == arraySize - 1 ) == false ) return "did not properly initialize a node's m_next pointer, as an element that isn't the last one has an m_next pointer pointing to 0";

        if( ( *( node->m_data ) == compareAgainst[ i ] ) == false ) return "did not properly initialize the list of nodes";
      }

      return 0;
    }

  
    static char const * const CheckListAgainstContainer( void* compareFrom, void* compareAgainst )
    {
      Util::List< HELPER >* list = static_cast< Util::List< HELPER >* >( compareFrom );
      Util::Container< HELPER >* container = static_cast< Util::Container< HELPER >* >( compareAgainst );
    
      unsigned i = 0;
      Util::List< HELPER >::ListNode *node = list->m_front;
      Util::Container< HELPER >::Iterator itB = container->Begin(), itE = container->End();
      HELPER prevData;
      for( ; node != 0 && itB != itE; node = node->m_next, ++itB, ++i )
      {
        if( node->m_prev != list->m_end )
        {
          if( ( *( node->m_prev->m_data ) == prevData ) == false ) return "did not properly initialize a node's m_prev pointer";
        }
        else
          if( ( i == 0 ) == false ) return "did not properly initialize a node's m_prev pointer, as an element that isn't the first one has an m_prev pointer pointing to 0";

        if( node->m_next != list->m_end )
        {
          if( ( *( node->m_next->m_data ) == ( Util::Container< HELPER >::Iterator( itB )++ ).Get() ) == false ) return "did not properly initialize a node's m_next pointer";
        }
        else
          if( ( i == container->m_size - 1 ) == false ) return "did not properly initialize a node's m_next pointer, as an element that isn't the last one has an m_next pointer pointing to 0";

        if( ( *( node->m_data ) == itB.Get() ) == false ) return "did not properly initialize the list of nodes";

        prevData = itB.Get();
      }

      return 0;
    }

  };

}
