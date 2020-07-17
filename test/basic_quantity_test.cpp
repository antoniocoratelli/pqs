#include "test.hpp"

// test interaction with time.h
#include <time.h>
#include <pqs/si/length.hpp>
#include <pqs/si/reciprocal_length.hpp>
#include <pqs/si/time.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/imperial/time.hpp>
#include <pqs/imperial/speed.hpp>
#include <pqs/bits/quantity_output.hpp>

#include <iomanip>
#include <iostream>

struct dummy_system{ 

   typedef dummy_system type; 
};

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<
         ::dummy_system
      > : std::true_type{};
   }
}

namespace {

   template <intmax_t N, intmax_t D>
   constexpr
   std::ostream & operator << (std::ostream & os, std::ratio<N,D> )
   {
      using r = std::ratio<N,D>;
      if constexpr ( r::den == 1)
         return os  << r::num ;
      else 
         return os << "(" << r::num << "/" << r::den << ")" ;
   }

   template <int N, int D>
   constexpr
   std::ostream & operator << (std::ostream & os, pqs::exponent10<N,D> )
   {
      using r = typename pqs::exponent10<N,D>::ratio;
      if constexpr ( r::den ==1) 
         return os << r::num;
      else
         return os << "(" << r::num << "/" << r::den << ")" ;

   }

   template <typename M, typename E>
   std::ostream & operator << (std::ostream & os, pqs::conversion_factor<M,E> v)
   {
      return os << typename decltype(v)::multiplier{} << "*10^" << typename decltype(v)::exponent{} ;
   }
}

using namespace pqs;

namespace {

   /**
     *  @brief test quantity requirements
     */
   void basic_quantity_concept_test()
   {
      basic_quantity<
         basic_unit<
            dummy_system,
            decltype(abstract_length<> / abstract_time<> ),
            decltype( std::ratio<30,2>{} ^ exponent10<3>{})
         >, double
      > constexpr q{20.0};

      using Q = decltype(q);

      static_assert( quantity<Q> );

      using U = get_unit<Q>;

      static_assert( ! si::is_normative_unit<U> );
         
      using D = get_dimension<Q>;

      using V = get_numeric_type<Q>;

      using Cf = get_conversion_factor<Q>;

      using Sm = get_measurement_system<Q>;

      auto constexpr v = get_numeric_value(q);

      static_assert( v == 20.0 );

      auto constexpr r = q + q;

      static_assert( get_numeric_value(r) == 40.0);
   }

   void basic_quantity_add_test()
   {
      auto q1 = si::length::m<>{1};
      QUAN_CHECK(( get_numeric_value(q1) == 1))
      static_assert( si::is_normative_unit<get_unit<decltype(q1)> > );

      auto q1a = q1 + q1;
      // addition of exact same types does not change type
      static_assert(std::is_same_v<decltype(q1a),decltype(q1)>);
      QUAN_CHECK(( get_numeric_value(q1a) == 2))

      auto q2 = si::length::mm<>{321};
      static_assert( si::is_normative_unit<get_unit<decltype(q1)> > );

      auto q3 = q1 + q2;
     // int x = q2;
      static_assert( si::is_normative_unit<get_unit<decltype(q3)> > );

      //#######################################################################
      // the mm usit is derived from normative_unit so not same as deduced normative unit
      // This must be accepted,  else we cant derive units in si
      // static_assert(std::is_same_v<decltype(q3),decltype(q2)>);
      //#################################################################

      QUAN_CHECK(( get_numeric_value(q3) == 1321))

      auto q4 = si::length::ft<>{6};
      auto q5 = q1 + q4;
      static_assert( si::is_normative_unit<get_unit<decltype(q5)> > );
     // std::cout << "q5 numeric value = " << get_numeric_value(q5) << '\n';

      using Cf5 = get_conversion_factor<decltype(q5)>;

      static_assert( std::is_same_v< 
         Cf5, conversion_factor<std::ratio<1>,exponent10<-1> >
      > );

      auto q6 = imperial::length::ft<>{1};
      auto q7 = imperial::length::yd<>{2};
      auto q8 = q6 + q7;
      QUAN_CHECK((get_numeric_value(q8) == 7))
     // std::cout << " imp numeric value = " << get_numeric_value(q8) << '\n';
   }

   void basic_quantity_imperial_test()
   {
      auto constexpr q1 = imperial::time::s<>{10};
      imperial::time::min<> q2 = q1;
     // std::cout << get_numeric_value(q2) <<'\n';
      QUAN_CHECK(( get_numeric_value(q2) == 10./(60) ))
      imperial::time::hr<> q3 = q1;
     // std::cout << get_numeric_value(q3) <<'\n';
      QUAN_CHECK(( get_numeric_value(q3) == 10./(60*60) ))
   }

   void basic_quantity_multiply_test()
   {
      auto q1 = si::length::m<>{10};
      auto q2 = si::length::mm<>{321};

      using U1 = get_unit<decltype(q1)>;

      static_assert( si::is_normative_unit<U1> );

      auto q3 = q1 * q2;
      QUAN_CHECK( (get_numeric_value(q3) == 3210))
     // std::cout << "result of mux = "  << get_numeric_value(q3) <<'\n';

      basic_quantity<
         si::normative_unit<
            exp_length<-1>,
            exponent10<-1>
         >
      > q4{2};
      auto v1 = q1 * q4;
      QUAN_CHECK( (v1 == 2.))
     // std::cout << "result of dimless mux = "  << v1 <<'\n'; 

      si::length::ft<> q5 = q1;
      using U5 = get_unit<decltype(q5)>;
      static_assert( not si::is_normative_unit<U5> );

      auto q6 = q5 * q2; 
      static_assert( si::is_normative_unit<get_unit<decltype(q6)> > );
     // std::cout << "result of mux1 = "  << get_numeric_value(q6) <<'\n';  
   }

   void basic_quantity_divide_test()
   {
      // dimensionless
      auto q1 = si::length::m<>{10};
      auto q2 = si::length::mm<>{10000};
      auto v1 =  q1 / q2;
      QUAN_CHECK(( v1 == 1 ))
     // std::cout << "result of div = "  << v1 <<'\n';

      auto q4 = si::time::s<>{5};

      auto q5 = q1 / q4;
      QUAN_CHECK(( get_numeric_value(q5) == 2 ))
      //std::cout << "result of div1 = "  << get_numeric_value(q5) <<'\n';

      si::time::min<> q6 = q4;
     // std::cout << "q6 cf = " << get_conversion_factor<decltype(q6)>() << '\n';
      static_assert(not si::is_normative_unit<get_unit<decltype(q6)> > );

      auto q7 = q1 / q6;
      static_assert( si::is_normative_unit<get_unit<decltype(q7)> > );
    //  std::cout << "q7 cf = " << get_conversion_factor<decltype(q7)>() << '\n';
     // std::cout << "q7 = "  << get_numeric_value(q7) <<'\n';
      QUAN_CHECK(( get_numeric_value(q7) == 0.02 ))
   }

   void scalar_multiply_test()
   {
      auto constexpr q1 = si::length::m<>{10};
      static_assert(unit_to_fixed_string<charset_ascii>(q1) == "m" );
      static_assert(unit_to_fixed_string<charset_utf8>(q1) == "m" );

      auto q2 = si::length::mm<>{10000};
      QUAN_CHECK( ( unit_to_fixed_string<charset_ascii>(q2) == "mm" ))
      QUAN_CHECK( ( unit_to_fixed_string<charset_utf8>(q2) == "mm" ))

      auto constexpr q1a = q1 * 2.0;
      static_assert(std::is_same_v<decltype(q1a),decltype(q1)>);
      QUAN_CHECK(( get_numeric_value(q1a) == 20 ))

      auto q2a = 3.0 * q2;
      static_assert(std::is_same_v<decltype(q2a),decltype(q2)>);
      QUAN_CHECK(( get_numeric_value(q2a) == 30000 ))

      auto constexpr q3 = imperial::speed::mi_per_hr<>{60};
      QUAN_CHECK( ( unit_to_fixed_string<charset_ascii>(q3) == "mi/hr" ))

      auto constexpr q3a = q3 * 4;
      static_assert(std::is_same_v<decltype(q3a),decltype(q3)>);
      static_assert(get_numeric_value(q3a) == 240 );

      auto constexpr q3b = 2 * q3a;
      static_assert(std::is_same_v<decltype(q3b),decltype(q3)>);
      static_assert( get_numeric_value(q3b) == 480 );
   }

   void scalar_divide_test()
   {
      auto q1 = si::length::m<>{10};
      auto q2 = 1. / q1;
      QUAN_CHECK(( get_numeric_value(q2) == 1./10 ));
  //    output<charset_utf8>(std::cout << "q2 = ", q2) << '\n';

      auto q3 = si::length::mm<>{10};
      auto q4 = 1. / q3;
      QUAN_CHECK(( get_numeric_value(q4) == 1./10 ));
    //  output<charset_utf8>(std::cout << "q4 = ", q4) << '\n';

      auto q5 = q1 / 2.;
      QUAN_CHECK(( get_numeric_value(q5) == 5 ));
    //  output<charset_utf8>(std::cout << "q5 = ", q5) << '\n';

      auto q6 = q2 / 2.;
      QUAN_CHECK(( get_numeric_value(q6) == 1./20 ));
    //  output<charset_utf8>(std::cout << "q6 = ", q6) << '\n';

      // test normative si
      si::reciprocal_length::per_mm<> q7 = q4;
    //  output<charset_utf8>(std::cout << "q7 = ", q7) << '\n';
   }

   // wiki example
   void conversion_factor_semantic_test()
   {
      using Qb = si::length::m<>;
      using Q  = si::length::ft<>;

      static_assert( same_measurement_system<Q,Qb> );
      static_assert( evaluate<get_conversion_factor<Qb> >() == 1 );
      static_assert( evaluate<get_conversion_factor<Q> >() != 1 );

      constexpr dimensionless_quantity n = -12345.678;
      
      constexpr Q  q{n};
      constexpr Qb qB = q;

      static_assert( 
         get_numeric_value(qB) == 
            get_numeric_value(q) * evaluate<get_conversion_factor<Q> >() 
      );
   }

   void output_test()
   {
      auto constexpr q1 = si::length::m<>{100};
      si::length::ft<> constexpr q2 = q1;

     // output<charset_utf8>( std::cout << std::setprecision(7), q1);
     // output< charset_utf8>( std::cout << " == ", q2) << '\n';
   }
}

void basic_quantity_test()
{
   basic_quantity_concept_test();
   basic_quantity_add_test();
   basic_quantity_imperial_test();
   conversion_factor_semantic_test();
   basic_quantity_multiply_test();
   basic_quantity_divide_test();
   output_test();
   scalar_multiply_test();
   scalar_divide_test();
}