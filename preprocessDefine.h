
#pragma once
#include <boost/multiprecision/cpp_bin_float.hpp>

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
template class FEMProject::name<double, int>;
//template class FEMProject::name<boost::multiprecision::cpp_bin_float_100, int>;
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
template class FEMProject::name<double>;
//template class FEMProject::name<boost::multiprecision::cpp_bin_float_100>;
#endif

//#define instantiatePrec(name) 
//template class FEMProject::name<double>; 
