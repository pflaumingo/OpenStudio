
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include "TStringify.h"

template<typename T> std::string stringify(const T& x)
{
    std::ostringstream out;
    out << x;
    return out.str();
}


template<> std::string stringify<int>(const int& x)
{
    std::ostringstream out;
    out << x;
    return out.str();
}

template<> std::string stringify<bool>(const bool& x)
{
    std::ostringstream out ;
    out << std::boolalpha << x;
    return out.str();
}

template<> std::string stringify<double>(const double& x)
{
    const int sigdigits = std::numeric_limits<double>::digits10;
    std::ostringstream out;
    out.setf(std::ios::fixed | std::ios::showpoint, std::ios::floatfield);
    out << std::setprecision(sigdigits) << x;
    return out.str();
}

template<> std::string stringify<float>(const float& x)
{
    const int sigdigits = std::numeric_limits<float>::digits10;
    std::ostringstream out;
    out.setf(std::ios::fixed);
    out << std::setprecision(sigdigits) << x;
    return out.str();
}

template<> std::string stringify<long double>(const long double& x)
{
    const int sigdigits = std::numeric_limits<long double>::digits10;
    std::ostringstream out;
    out.setf(std::ios::fixed);
    out << std::setprecision(sigdigits) << x;
    return out.str();
}
