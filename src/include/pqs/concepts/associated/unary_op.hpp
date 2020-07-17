#ifndef PQS_UNARY_OP_HPP_INCLUDED
#define PQS_UNARY_OP_HPP_INCLUDED

#include <pqs/bits/meta/unary_op_tags.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/meta/strip_cr.hpp>

namespace pqs{

   namespace impl{

      template <typename Op, typename T, typename Where = void>
      struct unary_op_impl : pqs::undefined{};

   } // impl

   template < typename Op, typename T>
   struct unary_op : impl::unary_op_impl<
      Op,
      typename pqs::meta::strip_cr<T>::type
   >{};

   template < typename Op, typename T>
   using unary_op_t = typename unary_op<Op,T>::type;

}

#endif // PQS_UNARY_OP_HPP_INCLUDED