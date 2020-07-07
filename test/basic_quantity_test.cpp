#include "test.hpp"
#include <pqs/bits/base_quantities.hpp>
#include <pqs/instance/basic_quantity.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/si/length.hpp>
#include <pqs/imperial/length.hpp>
#include <iostream>

struct dummy_system{ 

   typedef dummy_system type; 
};

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<::dummy_system> : std::true_type{};
   }
}

namespace {

   void basic_quantity_test1()
   {
      static_assert(pqs::is_defined_legacy<double>::value,"");
      pqs::basic_quantity<
         pqs::basic_unit<
            dummy_system,
            decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
            decltype( std::ratio<30,2>{} * pqs::exponent10<3>{})
         >, double
      > constexpr q{20.0};

      using tu = pqs::get_unit<decltype(q)>;
         
      using td = pqs::get_dimension<decltype(q)>;

      using tv = pqs::get_numeric_type<decltype(q)>;

      using tcf = pqs::get_conversion_factor<decltype(q)>;

      using ts = pqs::get_measurement_system<decltype(q)>;

      auto constexpr v = get_numeric_value(q);
     
      std::cout << " qs numeric value = " << v << '\n';

      QUAN_CHECK(( v == 20.0 ))

      auto constexpr r = q + q;

      QUAN_CHECK(( get_numeric_value(r) == 40.0))

     // int x = r;
   }

   void basic_quantity_test2()
   {
      auto q_si1 = pqs::si::length::m<>{1};
      auto q_si2 = pqs::si::length::mm<>{321};
      auto q_sir = q_si1 + q_si2;
      QUAN_CHECK( (get_numeric_value(q_sir) == 1321))
      std::cout << " q_r numeric value = " << get_numeric_value(q_sir) << '\n';

      auto q_si3 = pqs::si::length::ft<>{6};
      auto q_sir1 = q_si1 + q_si3;
      std::cout << " q_r numeric value = " << get_numeric_value(q_sir1) << '\n';
      QUAN_CHECK(( std::is_same_v<
         pqs::get_conversion_factor<decltype(q_sir1)>,
         pqs::conversion_factor<std::ratio<1>,pqs::exponent10<-1> >
      > ))

      auto b = pqs::imperial::length::ft<>{1};
      auto c = pqs::imperial::length::yd<>{2};
      auto d = b + c;
      QUAN_CHECK( (get_numeric_value(d) == 7))
      std::cout << " imp numeric value = " << get_numeric_value(d) << '\n';
   }

   void basic_quantity_multiply_test()
   {
      auto q_si1 = pqs::si::length::m<>{10};
      auto q_si2 = pqs::si::length::mm<>{321};
      auto q_sir = q_si1 * q_si2;
      QUAN_CHECK( (get_numeric_value(q_sir) == 3210))
      std::cout << "result of mux = "  << get_numeric_value(q_sir) <<'\n';

      pqs::basic_quantity<
         pqs::si::unit<
            pqs::exp_length<-1>,
            pqs::exponent10<-1>
         >
      > q_si3{2};
      auto r1 = q_si1 * q_si3;
      QUAN_CHECK( (r1 == 2.))
      std::cout << "result of dimless mux = "  << r1 <<'\n';    
   }

   using namespace pqs;

   void check_conversion_factor_test()
   {

#if 1

   using Qb = si::length::m<>;
   using Q  = si::length::ft<>;

   static_assert( evaluate<get_conversion_factor<Qb> >() == 1 );
   static_assert( evaluate<get_conversion_factor<Q> >() != 1 );

   constexpr dimensionless_quantity n = -12345.678;
   
   constexpr Q  q{n};
   constexpr Qb qB = q;

   static_assert( 
      get_numeric_value(qB) == 
         get_numeric_value(q) * evaluate<get_conversion_factor<Q> >() 
   );

#else
      using Qb = pqs::si::length::m<>;
      using Q = pqs::si::length::ft<>;

      static_assert( pqs::evaluate<pqs::get_conversion_factor<Qb> >() == 1 );
      static_assert( pqs::evaluate<pqs::get_conversion_factor<Q> >() != 1 );

      pqs::dimensionless_quantity constexpr n = 12345.678;
      
      Q  constexpr q{n};
      Qb constexpr qB = q;

      static_assert( 
         get_numeric_value(qB) == 
            get_numeric_value(q) *  pqs::evaluate<pqs::get_conversion_factor<Q> >() 
      );
#endif
   }
}

void basic_quantity_test()
{
   basic_quantity_test1();
   basic_quantity_test2();
   check_conversion_factor_test();
   basic_quantity_multiply_test();
}