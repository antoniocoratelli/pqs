#ifndef PQS_TYPE_FUNCTIONS_GET_DIMENSION_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_DIMENSION_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/concepts/dimension.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct get_dimension_impl : pqs::undefined{};

   }

   template <typename T>
   struct get_dimension_legacy 
   : impl::get_dimension_impl<
      typename pqs::meta::strip_cr<T>::type
   >{};

   template <typename T>
   using get_dimension 
      = typename get_dimension_legacy<T>::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_DIMENSION_HPP_INCLUDED