#ifndef PQS_CONCEPTS_QUANTITY_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_DEFINITION_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/type_functions/get_unit.hpp>
#include <pqs/type_functions/get_dimension.hpp>
#include <pqs/type_functions/get_numeric_type.hpp>
#include <pqs/type_functions/get_conversion_factor.hpp>
#include <pqs/type_functions/get_measurement_system.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_quantity_impl : std::false_type{};

   }// impl

   template <typename T>
   struct is_quantity_legacy : impl::is_quantity_impl< std::remove_cvref_t<T> >{};

   template <typename T>
   inline constexpr bool is_quantity = is_quantity_legacy<T>::value;

   template <typename T>
   concept quantity = is_quantity<T>;


   namespace impl{

      template <quantity Q>
      struct get_dimension_impl<Q> : get_dimension<get_unit<Q> >{};

      template <quantity Q>
      struct get_conversion_factor_impl<Q> : get_conversion_factor<get_unit<Q> >{};

      template <quantity Q>
      struct get_measurement_system_impl<Q> : get_measurement_system<get_unit<Q> >{};


      template <typename Lhs, typename Rhs>
      struct provide_operator_plus_impl : std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_minus_impl : std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_times_impl :std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_divides_impl : std::true_type{};

   }
  
    template <quantity Lhs, quantity Rhs>
    inline constexpr bool provide_operator_plus = 
    impl::provide_operator_plus_impl<
         std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <quantity Lhs, quantity Rhs>
    inline constexpr bool provide_operator_minus = 
    impl::provide_operator_minus_impl<
         std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <quantity Lhs, quantity Rhs>
    inline constexpr bool provide_operator_times = 
    impl::provide_operator_times_impl<
         std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <quantity Lhs, quantity Rhs>
    inline constexpr bool provide_operator_divides = 
    impl::provide_operator_divides_impl<
         std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

}// pqs

#endif // PQS_CONCEPTS_QUANTITY_HPP_INCLUDED