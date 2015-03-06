#ifndef BOOST_VARIANT_UTILS_HPP_
#define BOOST_VARIANT_UTILS_HPP_

#include <boost/variant.hpp>

namespace boost_variant_utils_detail
{

// code from http://www.baryudin.com/blog/boost-variant-and-lambda-functions-c-11.html

template <typename ReturnT, typename... Lambdas>
struct lambda_visitor;
 
template <typename ReturnT, typename L1, typename... Lambdas>
struct lambda_visitor< ReturnT, L1 , Lambdas...> : public L1, public lambda_visitor<ReturnT, Lambdas...>
{
    using L1::operator();
    using lambda_visitor< ReturnT , Lambdas...>::operator();
    lambda_visitor(L1 l1, Lambdas... lambdas) 
      : L1(l1), lambda_visitor< ReturnT , Lambdas...> (lambdas...)
    {}
};
 
template <typename ReturnT, typename L1>
struct lambda_visitor<ReturnT, L1> : public L1, public boost::static_visitor<ReturnT>
{
    using L1::operator();
    lambda_visitor(L1 l1) 
      :  L1(l1), boost::static_visitor<ReturnT>()
    {}
};
 
template <typename ReturnT>
struct lambda_visitor<ReturnT> : public boost::static_visitor<ReturnT> 
{
 
    lambda_visitor() : boost::static_visitor<ReturnT>() {}
};
 
template <typename ReturnT, typename... Lambdas>
lambda_visitor<ReturnT, Lambdas...> make_lambda_visitor(Lambdas... lambdas)
{
    return { lambdas... };
}

}


template<class ReturnType = void, class VariantType, class... Visitors>
ReturnType visit(VariantType& variant, Visitors... visitors)
{
    using namespace boost_variant_utils_detail;

    lambda_visitor<ReturnType, Visitors...> visitor{std::move(visitors)...};
    return boost::apply_visitor(visitor, variant);
}


#endif
