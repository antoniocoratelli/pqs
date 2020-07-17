#ifndef PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

/**
 * @brief implement intensity as a model of base_quantity
*/

namespace pqs{ 

    struct base_intensity : pqs::base_quantity_of<
      pqs::newtonian_universe::intensity_uuid
    >{
       using type = base_intensity;
    };

   template <int... N>
   struct exp_intensity;

   template <int N, int D>
   struct exp_intensity<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_intensity base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_intensity type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_intensity<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_intensity  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_intensity type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_intensity<N,1> : exp_intensity<N>{};

   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_intensity<N> > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_intensity<N,D> > = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::intensity_uuid,Ratio>
      : exp_intensity<Ratio::type::num, Ratio::type::den>{};

   }// impl

   template <int N = 1 , int D = 1>
   inline constexpr auto abstract_intensity = std::conditional_t<
      (D == 1),
      exp_intensity<N>,
      exp_intensity<N,D>
   >{};
}

#endif //PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED