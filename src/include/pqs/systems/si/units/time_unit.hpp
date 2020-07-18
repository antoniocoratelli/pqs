#ifndef PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/time.hpp>
#include <pqs/systems/si/unit.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace time_unit{

   struct s : si::base_unit<base_time>{};

   struct ms : si::normative_unit<exp_time<1>, exponent10<-3> >{};

   template <conversion_factor CF>
   struct conversion : 
   pqs::si::unit_conversion<
      decltype(abstract_time<>),
      decltype(CF)
   >{};

   struct min : named<"min"> ,
      conversion< 
         std::ratio<1,60>() ^ exponent10<0>()
      >
   {};

}}} // pqs::si::time_unit

#endif //PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED
