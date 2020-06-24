

#include <type_traits>
#include <pqs/concepts/dimension.hpp>
#include <pqs/bits/base_quantities.hpp>

using pqs::dlist;
using pqs::exp_length;
using pqs::exp_time;
using pqs::exp_mass;
using pqs::meta::merge_dim;

void  experimental_test()
{
   typedef dlist<> empty;
   typedef merge_dim<empty,pqs::times,empty >::type result0a;
   static_assert(std::is_same<result0a,empty>::value,"");
   typedef merge_dim<empty,pqs::divides,empty >::type result0b;
   static_assert(std::is_same<result0b,empty>::value,"");
   
   // n.b must be sorted
   typedef dlist<exp_time<1> > dim1;
   typedef merge_dim<dim1,pqs::times,dim1 >::type result1;
   typedef dlist<exp_time<2> > expected1;
   static_assert(std::is_same<result1,expected1>::value,"");

   typedef merge_dim<dim1,pqs::divides,dim1 >::type result1a;
   typedef dlist<> expected1a;
   static_assert(std::is_same<result1a,expected1a>::value,"");

   typedef dlist<exp_length<-2>, exp_time<2> >  dim2;
   typedef merge_dim<dim1,pqs::times,dim2 >::type result2;
   typedef dlist<exp_length<-2>, exp_time<3> > expected2;
   static_assert(std::is_same<result2,expected2>::value,"");

   typedef merge_dim<dim1,pqs::divides,dim2 >::type result2a;
   typedef dlist<exp_length<2>, exp_time<-1> > expected2a;
   static_assert(std::is_same<result2a,expected2a>::value,"");

   typedef dlist<exp_length<-1>, exp_time<1>, exp_mass<2> >  dim3;
   typedef merge_dim<dim2,pqs::times,dim3 >::type result3;
   typedef dlist<exp_length<-3>, exp_mass<2>, exp_time<3>  > expected3;
   static_assert(std::is_same<result3,expected3>::value,"");

   typedef merge_dim<dim2,pqs::divides,dim3 >::type result3a;
   typedef dlist<exp_length<-1>,exp_mass<-2>,exp_time<1> > expected3a;
   static_assert(std::is_same<result3a,expected3a>::value,"");

   typedef dlist<exp_length<1>, exp_time<1>, exp_mass<2> >  dim4;
   typedef merge_dim<dim3,pqs::times,dim4 >::type result4;
   typedef dlist<exp_mass<4>,exp_time<2> > expected4;
   static_assert(std::is_same<result4,expected4>::value,"");

   typedef merge_dim<dim3,pqs::divides,dim4 >::type result4a;
   typedef dlist<exp_length<-2> > expected4a;
   static_assert(std::is_same<result4a,expected4a>::value,"");


   typedef dlist<exp_length<-1>, exp_time<-1>, exp_mass<-2> >  dim5;
   typedef merge_dim<dim4,pqs::times,dim5 >::type result5;
   typedef dlist<> expected5;
   static_assert(std::is_same<result5,expected5>::value,"");

   typedef merge_dim<dim4,pqs::divides,dim5 >::type result5a;
   typedef dlist<exp_length<2>,exp_mass<4>,exp_time<2> >::type expected5a;
   static_assert(std::is_same<result5a,expected5a>::value,"");

}



