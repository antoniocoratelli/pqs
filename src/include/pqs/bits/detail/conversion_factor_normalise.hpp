#ifndef PQS_DETAIL_CONVERSION_FACTOR_NORMALISE_HPP_INCLUDED
#define PQS_DETAIL_CONVERSION_FACTOR_NORMALISE_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/detail/conversion_factor_make_ratio_less_than_10.hpp>
#include <pqs/bits/detail/conversion_factor_make_ratio_greater_equal_1.hpp>

namespace  pqs { 

   namespace detail{
      template <typename LLConversionFactor>
      struct ll_conversion_factor_normalise{

         typedef typename pqs::meta::eval_if<
            std::ratio_greater_equal<
               typename pqs::detail::std_ratio_abs<
                  typename LLConversionFactor::multiplier
               >::type,
               std::ratio<10,1> 
            >,
               pqs::detail::ll_conversion_factor_make_ratio_less_than_10<
                   LLConversionFactor
               >,
            std::ratio_less<typename pqs::detail::std_ratio_abs<typename LLConversionFactor::multiplier>::type,std::ratio<1,1> >
                ,pqs::detail::ll_conversion_factor_make_ratio_greater_equal_1<
                  LLConversionFactor
                >,
            LLConversionFactor
         >::type type;
      };
   }

} // pqs

#endif // PQS_DETAIL_CONVERSION_FACTOR_NORMALISE_HPP_INCLUDED
