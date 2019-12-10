
#include <quan_matters/test/test.hpp>

#include <pqs/meta/ratio_exp.hpp>

namespace {

   void is_ratio_exp_test()
   {
      typedef pqs::meta::ratio_exp<
         std::ratio<1,2>,1
      > ratio_exp;

      typedef pqs::meta::ratio_exp<
         int,1
      > ratio_exp1;

      QUAN_CHECK((pqs::meta::is_ratio_exp<ratio_exp>::value));

      QUAN_CHECK((pqs::meta::is_ratio_exp<ratio_exp1>::value == true));
   }

   void ratio_exp_lt_10_test()
   {
      typedef  pqs::meta::ratio_exp<
         std::ratio<210000,2>
         ,1
      > ratio_exp2;

      typedef  typename pqs::meta::detail::ratio_exp_make_ratio_less_than_10<
            ratio_exp2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::meta::ratio_exp<std::ratio<21,20>, 6 > >::value ))

      typedef  pqs::meta::ratio_exp<
         std::ratio<-210000,2>
         ,1
      > ratio_exp3;
         typedef  typename pqs::meta::detail::ratio_exp_make_ratio_less_than_10<
            ratio_exp3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::meta::ratio_exp<std::ratio<-21,20>, 6 > >::value ))

   }

   void ratio_exp_gt_0_pt_1_test()
   {

     typedef  pqs::meta::ratio_exp<
         std::ratio<21,20000>
         ,6
      > ratio_exp2;

      typedef  typename pqs::meta::detail::ratio_exp_make_ratio_greater_than_0_pt_1<
            ratio_exp2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::meta::ratio_exp<std::ratio<21,200>, 4 > >::value ))

      typedef  pqs::meta::ratio_exp<
         std::ratio<-21,20000>
         ,6
      > ratio_exp3;

      typedef  typename pqs::meta::detail::ratio_exp_make_ratio_greater_than_0_pt_1<
            ratio_exp3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::meta::ratio_exp<std::ratio<-21,200>, 4 > >::value ))

   }

   // intmax_t is 9223372036854775807 on my system
   //             9223372036854775807
   // e.g approx 10^19
   // assume a max of 6 decimals for the fraction, so either part of the rational can be between 0 and 10^6
   // then either part of rational can be muxed by 10^12
   // so therefore one can work a range of exponents of 10^12
   // e.g 1 km + 1 n.m. After that there may be issues
   void ratio_add_exp_test()
   {
      QUAN_CHECK( (pqs::meta::detail::to_power<10,0>::value == 1));

      QUAN_CHECK( (pqs::meta::detail::to_power<10,1>::value == 10));
      QUAN_CHECK( (pqs::meta::detail::to_power<10,2>::value == 100));

      typedef pqs::meta::ratio_exp<std::ratio<1,2>,3> t1;
       
      using pqs::meta::detail::ratio_exp_add_exp_n;

      typedef ratio_exp_add_exp_n<t1,4>::type t2;

      QUAN_CHECK((std::is_same<t2,pqs::meta::ratio_exp<std::ratio<1,20000>,7> >::value ))

      typedef ratio_exp_add_exp_n<t2,-4>::type t3;

      QUAN_CHECK((std::is_same<t3,t1>::value ))

      typedef ratio_exp_add_exp_n<t1,4>::type t2;

      QUAN_CHECK((std::is_same<t2,pqs::meta::ratio_exp<std::ratio<1,20000>,7> >::value ))

      typedef ratio_exp_add_exp_n<t2,-4>::type t3;

      QUAN_CHECK((std::is_same<t3,t1>::value ))

   }

  /*
       to add ratio_exp.
       First normalise
  */
   void ratio_exp_normalise_test()
   {
       typedef pqs::meta::ratio_exp<std::ratio<1,200>,4> t1;
       typedef pqs::meta::detail::ratio_exp_normalise<t1>::type t2;

       QUAN_CHECK((std::is_same<t2,pqs::meta::ratio_exp<std::ratio<1,2>,2> >::value ))

       typedef pqs::meta::ratio_exp<std::ratio<201,20>,-3> t3;
       typedef pqs::meta::detail::ratio_exp_normalise<t3>::type t4;

       QUAN_CHECK((std::is_same<t4,pqs::meta::ratio_exp<std::ratio<201,200>,-2> >::value ))

       typedef pqs::meta::ratio_exp<std::ratio<202000,20>,-9> t5;
       typedef pqs::meta::detail::ratio_exp_normalise<t5>::type t6;

       QUAN_CHECK((std::is_same<t6,pqs::meta::ratio_exp<std::ratio<101,100>,-5> >::value ))

       typedef pqs::meta::ratio_exp<std::ratio<9,1>,4> t7;
       typedef pqs::meta::detail::ratio_exp_normalise<t7>::type t8;

        QUAN_CHECK((std::is_same<t7,t8 >::value ))
       
       
   }
  

} // namespace

void ratio_exp_test()
{
    is_ratio_exp_test();
    ratio_exp_lt_10_test();
    ratio_exp_gt_0_pt_1_test();
    ratio_add_exp_test();
    ratio_exp_normalise_test();
}