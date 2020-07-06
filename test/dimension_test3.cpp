
#include "test.hpp"
#include <type_traits>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/instance/basic_quantity.hpp>

using namespace pqs;

namespace {

   void mul_ee_test()
   {
      using x = std::remove_cvref_t< decltype(abstract_length<1> / abstract_time<1>) >;

      static_assert(std::is_same_v<x,dimension_list<exp_length<1>,exp_time<-1> > >,"");

      using y = std::remove_cvref_t< decltype( abstract_time<-1> * abstract_length<1> ) >;

      static_assert(std::is_same_v<y,dimension_list<exp_length<1>,exp_time<-1> > >,"");

      using z = std::remove_cvref_t<decltype( std::declval<x>() * abstract_time<1>)>;
      static_assert(std::is_same_v<z,exp_length<1> >,"");
   
      using a = decltype(std::declval<x>() * abstract_current<2> / abstract_time<2>) ;

      static_assert( std::is_same_v<a,dimension_list<exp_length<1>, exp_time<-3>, exp_current<2> > >,"");

      using b= decltype((abstract_current<2> / abstract_time<2>) * std::declval<x>() ) ;

      static_assert( std::is_same_v<a,dimension_list<exp_length<1>, exp_time<-3>, exp_current<2> > >,"");

     // static_assert( a{} == b{},"");

   }
}

void dimension_test3()
{
   mul_ee_test();
}