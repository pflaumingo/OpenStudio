#include <vector>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Espr3d.h"




template < typename  T >
std::vector< T >& operator+=(std::vector< T >& a, std::vector< T >& b)
{
    if ( a.size() == b.size() )
    {

        typedef typename std::vector< T >::iterator TVectorIter;
        TVectorIter  itb = b.begin();
        for (
            TVectorIter  ita =  a.begin();
            ita !=  a.end();
            ita++)
        {
            *ita += *itb;
            itb++;
        }
        return a;
    }
    else
    {
        std::string sOutputError = "Vector addition cannot be performed on vectors of different sizes" +a.size();
        throw std::domain_error("Vector addition cannot be performed on vectors of different sizes");
    }
}


template < typename T >
std::vector< T > operator*=( std::vector< T >& a, double scalar)
{
    typedef typename std::vector< T >::iterator TVectorIter;

    std::vector< T > Return;
    for (TVectorIter it =  a.begin();
            it !=  a.end(); it++)
    {
        *it *= scalar;
    }
    return a;
}

template < typename T >
std::string StreamOutVector( const std::vector< T >& a )
{
    std::stringstream sOutput;
    typedef typename std::vector< T >::const_iterator TVectorIter;
    std::vector< T > Return;
    for (TVectorIter it =  a.begin();
            it !=  a.end(); it++)
    {
        sOutput << *it << " ";
    }
    return sOutput.str();
}

template < typename T >
std::string StreamOutVector( const std::vector< std::vector< T > >& a )
{
    std::stringstream sOutput;
    typedef typename std::vector< std::vector< T > >::const_iterator TVectorIter;
    for (TVectorIter it =  a.begin();
            it <  a.end(); it++)
    {
        sOutput << StreamOutVector(*it) << std::endl;
    }
    return sOutput.str();
}

//template < typename T >
//std::string StreamOutVector( const std::vector< std::vector< TVertex > >& a )
//{
//    std::stringstream sOutput;
//    typedef typename std::vector< TVertex >::const_iterator TVectorIter;
//    sOutput << "Vertex List " << std::endl;
//    for (TVectorIter it =  a.begin();
//            it !=  a.end(); it++)
//    {
//        sOutput << it->StreamOut() << std::endl;
//    }
//    return sOutput.str();
//}
