#ifndef PQS_TYPE_FUNCTIONS_GET_EXPONENT_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_EXPONENT_HPP_INCLUDED

#include <pqs/bits/undefined_arg.hpp>
#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void >
      struct get_exponent_impl : pqs::undefined_arg<T>{};
   }

   template <typename T>
   struct get_exponent_legacy : impl::get_exponent_impl<
      typename std::remove_cvref<T>::type
   >{};

   template <typename T>
   using get_exponent = typename get_exponent_legacy<T>::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_EXPONENT_HPP_INCLUDED