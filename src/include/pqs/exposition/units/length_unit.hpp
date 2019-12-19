#ifndef PQS_EXPOSITION_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_EXPOSITION_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/exposition/base_quantity_exp.hpp>
#include <pqs/bits/dimension.hpp>
#include <pqs/bits/unit.hpp>
#include <pqs/base_quantity/length.hpp>

// length unit definition namespace 
namespace pqs_exposition{ namespace length_unit{

   struct mm : pqs::base_unit< 
      pqs_exposition::exp<pqs::base_length,1> ,
      -3
   >{};

   struct ft : pqs::unit_conversion< 
      pqs::base_unit< 
         pqs_exposition::exp<pqs::base_length,1>, 
         -1
      >
      ,381,125
    >{};

}} // pqs::length_unit

#endif //PQS_EXPOSITION_UNITS_LENGTH_UNIT_HPP_INCLUDED