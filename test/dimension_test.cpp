
#include "test.hpp"
#include <pqs/concepts/dimension.hpp>
#include <pqs/bits/meta/merge_dim.hpp>
#include <pqs/types/base_quantities.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/bits/meta/strip_cr.hpp>
#include <pqs/systems/si/units/length_unit.hpp>

namespace {

   void dimensionless_test()
   {
      static_assert( !pqs::dimension<pqs::dimensionless>,"");
      pqs::dimensionless d1;

      pqs::dimensionless d2;

      QUAN_CHECK((std::is_same<std::remove_cvref_t<decltype(d1 * d2)>, pqs::dimensionless>::value))

      QUAN_CHECK((std::is_same<std::remove_cvref_t<decltype(d1 / d2)>, pqs::dimensionless>::value))

      QUAN_CHECK( (pqs::pow<1,2>(d1) == d1) );
      QUAN_CHECK( (pqs::pow<-10>(d1) == d1) );

      QUAN_CHECK((d1 == d2))

      QUAN_CHECK(((d1 != d2) == false))
 
      pqs::dimensionless d3 = d1;  // copy ctor
      pqs::dimensionless d4 = pqs::dimensionless{};
      d2 = d1;                    // assignment
      QUAN_CHECK( (std::is_same_v<pqs::get_exponent<pqs::dimensionless>, std::ratio<0,1> >))
 
   }

   void length_dimension_test()
   {
       typedef pqs::si::length_unit::mm::dimension dimension;

       QUAN_CHECK(( std::is_same_v<dimension,pqs::exp_length<1> > ))
       QUAN_CHECK(( pqs::is_base_quantity_exponent<dimension> ))
       QUAN_CHECK(( pqs::base_quantity<pqs::get_base_quantity<dimension> > ))
       QUAN_CHECK(( std::is_same_v<pqs::get_base_quantity<dimension>,pqs::base_length> ))
       QUAN_CHECK(( std::is_same_v<pqs::get_simple_dimension<dimension>,dimension> ))

   }

   template <typename List>
   struct sort : pqs::meta::merge_sort<List,pqs::meta::detail::base_quantity_exp_sort_fun>{};

   void multiply_dimensions_test()
   {
      typedef pqs::dimension_list<
         pqs::exp_length<1>, 
         pqs::exp_time<-1>, 
         pqs::exp_mass<2> 
      > lhs_dimension;

      QUAN_CHECK((pqs::meta::get_num_elements_v<lhs_dimension> == 3))
      QUAN_CHECK((std::is_same_v<pqs::meta::front_t<lhs_dimension>,pqs::exp_length<1> >))
      QUAN_CHECK((std::is_same_v<pqs::meta::back_t<lhs_dimension>,pqs::exp_mass<2> > ))

      typedef pqs::dimension_list< 
         pqs::exp_mass<2>,
         pqs::exp_time<1>
      > rhs_dimension;

      typedef pqs::binary_op_t<lhs_dimension,pqs::times,rhs_dimension> result;

      typedef pqs::dimension_list<
         pqs::exp_length<1>,  
         pqs::exp_mass<4> 
      > expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::dimension_list<
         pqs::exp_length<-1>,
         pqs::exp_time<1>, 
         pqs::exp_mass<-2> 
      > inv_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::times,inv_dimension>::type empty_result;
      QUAN_CHECK((std::is_same<empty_result, pqs::dimensionless >::value))

      typedef pqs::binary_op<lhs_dimension,pqs::times,empty_result>::type result1;

      QUAN_CHECK((std::is_same<lhs_dimension,result1>::value))

      typedef pqs::binary_op<empty_result, pqs::times,lhs_dimension>::type result2;

      QUAN_CHECK((std::is_same<lhs_dimension,result2>::value))
   }

   void divide_dimensions_test()
   {
      using lhs_dimension = pqs::dimension_list<
         pqs::exp_length<1>, 
         pqs::exp_time<-1>,
         pqs::exp_mass<2> ,
         pqs::exp_current<2> 
      >;

      using rhs_dimension = pqs::dimension_list<
         pqs::exp_mass<2>, 
         pqs::exp_time<1>,
         pqs::exp_length<3>, 
         pqs::exp_current<1> 
      > ;

      using result = pqs::binary_op_t<lhs_dimension,pqs::divides,rhs_dimension> ;

      using expected_result = sort<
         pqs::dimension_list<
            pqs::exp_length<-2>, 
            pqs::exp_time<-2>, 
            pqs::exp_current<1> 
         > 
      >::type ;

      static_assert(std::is_same_v<result,expected_result>);

      using empty_result = pqs::binary_op_t<lhs_dimension,pqs::divides,lhs_dimension>;

      static_assert(std::is_same_v<empty_result,pqs::dimensionless> );

      using result2 = pqs::binary_op_t<pqs::dimension_list<>,pqs::divides,lhs_dimension> ;

      using result2a = pqs::binary_op_t<pqs::dimensionless,pqs::divides,lhs_dimension> ;

      using expected2 = sort<
         pqs::dimension_list<
            pqs::exp_length<-1>, 
            pqs::exp_time<1>,
            pqs::exp_mass<-2> ,
            pqs::exp_current<-2> 
         >
      >::type ;

      static_assert(std::is_same_v<result2,result2a>);

      static_assert(std::is_same_v<result2,expected2> );

      static_assert( std::is_same_v<result2,pqs::unary_op_t<pqs::meta::reciprocal,lhs_dimension> >) ;

   }

   void to_power_dimension_test1()
   {
      typedef pqs::dimension_list<
         pqs::exp_length<1>, 
         pqs::exp_time<-1>, 
         pqs::exp_mass<2>,
         pqs::exp_current<2> 
      > dimension;
      typedef std::ratio<2> multiplier;

      typedef pqs::binary_op<dimension,struct pqs::to_power,multiplier>::type result;

      typedef sort<
         pqs::dimension_list<
            pqs::exp_length<2>, 
            pqs::exp_time<-2>, 
            pqs::exp_mass<4>,
            pqs::exp_current<4> 
         > 
      >::type expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      // TODO fails since its is a list of zero values
      typedef pqs::binary_op<dimension,struct pqs::to_power,std::ratio<0> >::type empty_result;
    //  int x = empty_result{};
      QUAN_CHECK( (std::is_same<empty_result,pqs::dimension_list<> >::value ))

  }

   void to_power_dimension_test2()
   {
      typedef pqs::dimension_list<
         pqs::exp_length<2>, 
         pqs::exp_time<-2>, 
         pqs::exp_mass<4>,
         pqs::exp_current<4> 
      > dimension;

      typedef std::ratio<2> divisor;

      typedef pqs::binary_op<
         dimension,struct pqs::to_power,typename pqs::unary_op<pqs::meta::reciprocal,divisor>::type 
      >::type result1;

      typedef sort<
         pqs::dimension_list<
            pqs::exp_length<1>, 
            pqs::exp_time<-1>,
            pqs::exp_mass<2>,
            pqs::exp_current<2> 
         > 
      >::type expected_result1;

      QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

      typedef pqs::binary_op<
         result1,struct pqs::to_power,typename pqs::unary_op<pqs::meta::reciprocal,divisor>::type
      >::type result2;

      typedef sort <
         pqs::dimension_list<
            pqs::exp_length<1,2>,
            pqs::exp_time<-1,2>, 
            pqs::exp_mass<1>,
            pqs::exp_current<1> 
         >
      >::type expected_result2;

      QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))
     
  }

  void reciprocal_dimension_test()
  {
      typedef pqs::dimension_list<
         pqs::exp_length<2>,
         pqs::exp_time<-2>, 
         pqs::exp_mass<4>,
         pqs::exp_current<4> 
      > dimension;

      typedef pqs::unary_op<pqs::meta::reciprocal,dimension>::type result1;

      typedef sort<
         pqs::dimension_list<
            pqs::exp_length<-2>, 
            pqs::exp_time<2>, 
            pqs::exp_mass<-4>,
            pqs::exp_current<-4> 
         > 
      >::type expected_result1;
  
     QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

     typedef pqs::dimension_list<
         pqs::exp_length<1,2>,
         pqs::exp_time<-5,2>, 
         pqs::exp_mass<1> ,
         pqs::exp_current<10> 
     > dimension2;

     typedef pqs::unary_op<pqs::meta::reciprocal,dimension2>::type result2;

     typedef sort<
         pqs::dimension_list<
            pqs::exp_length<-1,2>,
            pqs::exp_time<5,2>,
            pqs::exp_mass<-1>,
            pqs::exp_current<-10> 
         > 
      >::type expected_result2;

     QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))
  }

  void compare_dimension_test()
  {
      typedef pqs::dimension_list<
         pqs::exp_time<-2>, 
         pqs::exp_mass<4>,
         pqs::exp_current<4>, 
         pqs::exp_length<2> 
      > dimension1;

      typedef pqs::dimension_list<
         pqs::exp_length<4,2>,
         pqs::exp_time<-2>, 
         pqs::exp_current<4>, 
         pqs::exp_mass<4>
      > dimension2;

      typedef pqs::dimension_list<
         pqs::exp_length<-1,2>, 
         pqs::exp_time<5,2>, 
         pqs::exp_current<-10>, 
         pqs::exp_mass<-1>
      > dimension3;

      typedef pqs::binary_op<dimension1,pqs::equal_to, dimension2> are_equal12;
      QUAN_CHECK(are_equal12::value == true)
      typedef pqs::binary_op<dimension1,pqs::not_equal_to, dimension2> are_not_equal12;
      QUAN_CHECK(are_not_equal12::value == false)

      typedef pqs::binary_op<dimension1, pqs::equal_to,dimension3> are_equal13;
      QUAN_CHECK(are_equal13::value == false)
      typedef pqs::binary_op<dimension1,pqs::not_equal_to, dimension3> are_not_equal13;
      QUAN_CHECK(are_not_equal13::value == true)
  }
}

void dimension_test()
{
   dimensionless_test();
   length_dimension_test();
   multiply_dimensions_test();
   divide_dimensions_test();
   to_power_dimension_test1();
   to_power_dimension_test2();
   reciprocal_dimension_test();
   compare_dimension_test();
}


