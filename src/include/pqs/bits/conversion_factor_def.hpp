#ifndef PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
#define PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED

#include <pqs/concepts/associated/get_exponent.hpp>
#include <pqs/bits/conversion_factor_ops.hpp>
#include <pqs/bits/conversion_factor_fwd.hpp>

namespace pqs{ 

   template <typename Multiplier, typename  Exponent>
      requires 
         pqs::is_ratio<Multiplier> && 
         pqs::is_exponent10<Exponent>
   struct conversion_factor{
      
      using multiplier = typename Multiplier::type;
      using exponent = typename Exponent::type;

      static_assert(Multiplier::num != 0, 
         "conversion_factor : only non-zero ratios values allowed");
      using type = conversion_factor<multiplier,exponent>;

      template <
         intmax_t N1, intmax_t D1
      > 
      constexpr
      friend
      auto operator * ( conversion_factor, std::ratio<N1,D1>)
      {
         return pqs::normalise<
            pqs::conversion_factor<
               std::ratio_multiply<multiplier,std::ratio<N1,D1> >,
               Exponent
            >
         >{};
      }

      template <
         intmax_t N1, intmax_t D1
      > 
      constexpr
      friend
      auto operator * ( std::ratio<N1,D1>, conversion_factor)
      {
         return pqs::normalise<
            pqs::conversion_factor<
               std::ratio_multiply<multiplier,std::ratio<N1,D1> >,
               Exponent
            >
         >{};
      }

      template <
         intmax_t N1, intmax_t D1
      > 
      constexpr
      friend
      auto operator / ( conversion_factor, std::ratio<N1,D1> )
      {
         return pqs::normalise<
            pqs::conversion_factor<
               std::ratio_divide<multiplier,std::ratio<N1,D1> >,
               Exponent
            >
         >{};
      }

      template <
         intmax_t N1, intmax_t D1
      > 
      constexpr
      friend
      auto operator / ( std::ratio<N1,D1>,conversion_factor )
      {
         return pqs::normalise<
            pqs::conversion_factor<
               std::ratio_divide<std::ratio<N1,D1>,multiplier>,
               exponent10<
                  -exponent::ratio::num,
                  exponent::ratio::den
               >
            >
         >{};
      }
   }; // conversion_factor

   namespace impl{

      template <intmax_t MuxNum, intmax_t MuxDenom, typename UnitExp>
      struct is_conversion_factor_impl<
         pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            UnitExp 
         >
      > : std::true_type{};

      template <intmax_t MuxNum, intmax_t MuxDenom, typename UnitExp>
      struct get_exponent_impl<
        pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            UnitExp 
         >
      > {
         typedef typename  pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            UnitExp 
         >::exponent type;
      };

   } //impl

}  // pqs

#endif // PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
