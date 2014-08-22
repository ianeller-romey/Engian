
#ifndef DEBUG_FUNCTIONTRACKER_H
#define DEBUG_FUNCTIONTRACKER_H

namespace Debug
{

  class FunctionTracker
  {
    public:
      FunctionTracker();
      ~FunctionTracker();

      void Track( char const * const function );
      bool const Contains( char const * const function, bool clearAfter = false );
      void Clear();


    private:
      FunctionTracker( FunctionTracker const& other );
      FunctionTracker& operator=( FunctionTracker const& other );

      class FunctionTrackerNode
      {
        public:
          FunctionTrackerNode();
          FunctionTrackerNode* m_next;
          char*                m_function;

          bool const operator==( char const * const function ) const;

        private:
          FunctionTrackerNode( FunctionTrackerNode const& other );
          FunctionTrackerNode& operator=( FunctionTrackerNode const& other );
      };

      FunctionTrackerNode* m_front;
  };

}

#endif
