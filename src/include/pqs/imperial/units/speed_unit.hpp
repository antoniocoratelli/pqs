#ifndef PQS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED

#include <pqs/imperial/length_unit.hpp>
#include <pqs/imperial/time_unit.hpp>

namespace pqs{ namespace imperial { namespace speed_unit{

   struct ft_per_s : 
      decltype( length_unit::ft{} / time_unit::s{} )
   {};

   struct yd_per_s :
      decltype( length_unit::yd{} / time_unit::s{} )
   {};

   struct mi_per_h : 
      decltype( length_unit::mi{} / time_unit::h{} ) 
   {};

}}} // pqs::si::length_unit


#endif // PQS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED