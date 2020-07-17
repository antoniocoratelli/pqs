#ifndef PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   template <typename Multiplier, typename  Exponent>
   struct conversion_factor;

   namespace impl{

      template <typename T, typename Where = void> 
      struct is_conversion_factor_impl : std::false_type{};
   }

   template  <typename T>
   inline constexpr bool is_conversion_factor = impl::is_conversion_factor_impl< 
      std::remove_cvref_t<T>
   >::value;

   template <typename T>
   struct is_conversion_factor_legacy : std::bool_constant< 
      is_conversion_factor<T>
   >{};
}

#endif // PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED
