#ifndef PQS_SYSTEMS_IMPERIAL_TIME_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_TIME_UNIT_HPP_INCLUDED

#include <pqs/systems/imperial/unit.hpp>
#include <pqs/types/base_quantity/time.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace imperial { namespace time_unit{

   struct s : pqs::base_unit<
      base_time,imperial_measurement_system
   >{};

   struct min : named<"min">,
      decltype( s() * std::ratio<60>() )
   {};

   struct hr : named<"hr">,
      decltype( min() * std::ratio<60>() ) 
   {};

}}} // pqs::si::time_unit


#endif // PQS_SYSTEMS_IMPERIAL_TIME_UNIT_HPP_INCLUDED
