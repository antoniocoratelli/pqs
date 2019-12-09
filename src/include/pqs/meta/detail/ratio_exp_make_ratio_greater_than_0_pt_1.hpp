#ifndef QUAN_META_DETAIL_RATIO_EXP_MAKE_RATIO_GREATER_THAN_0_PT_1_HPP_INCLUDED
#define QUAN_META_DETAIL_RATIO_EXP_MAKE_RATIO_GREATER_THAN_0_PT_1_HPP_INCLUDED

#include <pqs/meta/ratio_exp_def.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ namespace meta{

   namespace detail{
      // input RatioExp must always be positive
      template <typename RatioExp>
         struct ratio_exp_abs_make_ratio_greater_than_0_pt_1{
         static_assert(std::ratio_greater<typename RatioExp::ratio,std::ratio<0,1> >::value);
         typedef typename meta::eval_if<
            std::ratio_greater_equal<typename RatioExp::ratio,std::ratio<1,10> >
            ,RatioExp
            ,ratio_exp_abs_make_ratio_greater_than_0_pt_1<
               ratio_exp< 
                  std::ratio_multiply<typename RatioExp::ratio,std::ratio<10,1> >
                 ,RatioExp::exp - 1
               >
            >
         >::type type;            
      };

      // input  RatioExp is non zero
      template <typename RatioExp>
      struct ratio_exp_non_zero_make_ratio_greater_than_0_pt_1{

         static_assert(std::ratio_not_equal<typename RatioExp::ratio,std::ratio<0,1> >::value);
         typedef std::ratio_less< 
            typename RatioExp::ratio,std::ratio<0,1> 
         > is_negative;

         typedef typename meta::eval_if<
            is_negative
            ,ratio_exp<
               std::ratio_multiply<typename RatioExp::ratio,std::ratio<-1,1> > 
               ,RatioExp::exp
            >
            ,RatioExp
         >::type abs_type_in;

         typedef typename ratio_exp_abs_make_ratio_greater_than_0_pt_1<abs_type_in>::type abs_type_out;

         typedef typename meta::eval_if<
            is_negative
             ,ratio_exp<
                std::ratio_multiply<typename abs_type_out::ratio, std::ratio<-1,1> > 
               ,abs_type_out::exp
            >,
            abs_type_out
         >::type type;
        
      };

      template <typename RatioExp>
      struct ratio_exp_make_ratio_greater_than_0_pt_1{
          // remove zero case
          typedef typename meta::eval_if<
            std::ratio_equal<typename RatioExp::ratio,std::ratio<0,1> >
            ,ratio_exp< std::ratio<0,1>,0>
            ,ratio_exp_non_zero_make_ratio_greater_than_0_pt_1<RatioExp>
          >::type type;      
      };

   } // detail

}} //pqs::meta

#endif // QUAN_META_DETAIL_RATIO_EXP_MAKE_RATIO_GREATER_THAN_0_PT_1_HPP_INCLUDED