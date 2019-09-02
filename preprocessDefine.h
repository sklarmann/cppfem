
#pragma once
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <string>
namespace boost{ namespace multiprecision{
typedef number<cpp_bin_float<32> > cpp_bin_float_32;
typedef number<cpp_bin_float<64> > cpp_bin_float_64;
typedef number<cpp_bin_float<128> > cpp_bin_float_128;
}}
#ifdef DLL_EXPORT // Set to true when you build the dll
#define API __declspec(dllexport)
#define instantiateHeader(name)
#elif APPLICATION
#define instantiateHeader(name) 
#else
#define API __declspec(dllimport)
#define instantiateHeader(name) \
extern template class API FEMProject::name<double,int>; \
extern template class API FEMProject::name<float, int>;
#endif

#ifdef DLL_EXPORT
#define instantiate(name) \
template class API FEMProject::name<double,int>; 
#elif APPLICATION
#define instantiate(name) \
template class FEMProject::name<float, int>;\
template class FEMProject::name<double, int>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_100, int>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_32, int>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_64, int>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_128, int>;
#endif

#ifdef DLL_EXPORT // Set to true when you build the dll
#define API2 __declspec(dllexport)
#define instantiateHeaderPrec(name)
#elif APPLICATION
#define instantiateHeaderPrec(name) 
#else
#define API2 __declspec(dllimport)
#define instantiateHeaderPrec(name) \
extern template class API2 FEMProject::name<double>; \
extern template class API2 FEMProject::name<float>;

#endif

#ifdef DLL_EXPORT
#define instantiatePrec(name) \
template class API FEMProject::name<double>; 
#elif APPLICATION
#define instantiatePrec(name) \
template class FEMProject::name<float>;\
template class FEMProject::name<double>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_100>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_32>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_64>;\
template class FEMProject::name<boost::multiprecision::cpp_bin_float_128>;
#endif

//#define instantiatePrec(name) 
//template class FEMProject::name<double>; 


