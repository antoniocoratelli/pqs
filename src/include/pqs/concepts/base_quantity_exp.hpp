#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/ratio.hpp>
#include <pqs/concepts/base_quantity.hpp>

namespace pqs{

   template <typename T>
   struct is_base_quantity_exp;

   /*
      Where T,Lhs,Rhs,are models of base_quantity_exp
        R is model of ratio
        B is a nodel of meta_bool_constant

      requires 
            binary_op<Lhs,plus,Rhs> -> T
            binary_op<Lhs,minus,Rhs> -> T
            binary_op<Lhs,times,R> -> T;
            binary_op<Lhs,divides,R> -> T
            unary_op<negate,Lhs> -> T
            binary_op<lhs,equal_to,Rhs> -> B
            binary_op<lhs,not_equal_to,Rhs> -> B
            
  
   */

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_exp_impl : std::false_type{};

      template <typename T, typename Where = void>
      struct get_base_quantity_impl : pqs::undefined{};
      
      template <typename Lhs, typename Rhs, typename Where = void>
      struct of_same_base_quantity_impl : std::false_type{};

/*
      template <typename Lhs, typename Rhs, typename Where = void>
      struct add_base_quantity_exp_impl : pqs::undefined{};
   
      template <typename Lhs, typename Rhs, typename Where = void>
      struct subtract_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Rhs, typename Where = void>
      struct multiply_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Rhs, typename Where = void>
      struct divide_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Where = void>
      struct negate_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Rhs, typename Where = void>
      struct base_quantity_exp_equal_to_impl : pqs::undefined {};

      // derive default from equality ?
      template <typename Lhs, typename Rhs, typename Where = void>
      struct base_quantity_exp_not_equal_impl : pqs::undefined {};
*/
      // derive default
      template <typename T, typename Where = void>
      struct base_quantity_exp_is_zero_impl : pqs::undefined {};
   }

   template <typename T>
   struct is_base_quantity_exp : pqs::impl::is_base_quantity_exp_impl<T>{};

   template <typename T>
   struct get_base_quantity : pqs::impl::get_base_quantity_impl<T>{};

   template <typename Lhs, typename Rhs>
   struct of_same_base_quantity : pqs::impl::of_same_base_quantity_impl<Lhs,Rhs>{};

    
/*
   template <typename Lhs, typename Rhs>
   struct add_base_quantity_exp : pqs::impl::add_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct subtract_base_quantity_exp : pqs::impl::subtract_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct multiply_base_quantity_exp : pqs::impl::multiply_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct divide_base_quantity_exp : pqs::impl::divide_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename T>
   struct negate_base_quantity_exp  : pqs::impl::negate_base_quantity_exp_impl<T>{};

   template <typename Lhs, typename Rhs>
   struct base_quantity_exp_equal_to : pqs::impl::base_quantity_exp_equal_to_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct base_quantity_exp_not_equal : pqs::impl::base_quantity_exp_not_equal_impl<Lhs,Rhs>{};
*/
   template <typename T>
   struct base_quantity_exp_is_zero : pqs::impl::base_quantity_exp_is_zero_impl<T>{};

}


#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
