#ifndef PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>

namespace pqs{ 

   /**
    * @addtogroup base_quantity_model
    * @{ **/
   /**
    * @brief implement base_length as a model of base_quantity
   */
   struct base_length : pqs::impl::base_quantity_of<
      pqs::newtonian_universe::length_uuid
   >{
      typedef base_length type;
   };
   /** @} */

   template <int... N>
   struct exp_length;

   template <int N, int D>
   struct exp_length<N,D> 
   : pqs::detail::base_quantity_exp_base_class {
      typedef base_length  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_length type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_length<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_length  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_length type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_length<N,1> : exp_length<N> {};

   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exponent_impl< pqs::exp_length<N>  > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exponent_impl< pqs::exp_length<N,D>  > = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::length_uuid,Ratio>
      : exp_length<Ratio::type::num, Ratio::type::den>{};

   }// impl

   using abstract_length_t = exp_length<1>;
   inline constexpr auto abstract_length_v  = abstract_length_t{};

}

#endif // PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
