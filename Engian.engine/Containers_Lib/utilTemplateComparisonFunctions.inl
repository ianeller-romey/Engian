
namespace Util
{

  template< typename T >
  bool const TemplateComparisonFunctions< T >::DefaultEquals( T const& left, T const& right )
  {
    return left == right;
  }

  template< typename T >
  bool const TemplateComparisonFunctions< T >::DefaultGreaterThan( T const& left, T const& right )
  {
    return left > right;
  }

  template< typename T >
  bool const TemplateComparisonFunctions< T >::DefaultLessThan( T const& left, T const& right )
  {
    return left < right;
  }

}