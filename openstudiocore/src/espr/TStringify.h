#ifndef TSTRINGIFY_H_
#define TSTRINGIFY_H_
#include<string>
/*
 * 
 * This creates templates to string-ize almost anything that is stringable. Using meta-templates.
*/





template<typename T> std::string stringify(const T& x);

template<> std::string stringify<int>(const int& x);

template<> std::string stringify<bool>(const bool& x);

template<> std::string stringify<double>(const double& x);

template<> std::string stringify<float>(const float& x);

template<> std::string stringify<long double>(const long double& x);

#endif /*TSTRINGIFY_H_*/
