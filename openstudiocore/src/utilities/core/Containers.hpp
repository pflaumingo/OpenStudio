/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.  
*  All rights reserved.
*  
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_CORE_CONTAINERS_HPP
#define UTILITIES_CORE_CONTAINERS_HPP

#include "../UtilitiesAPI.hpp"
#include "Compare.hpp"

#include <boost/optional.hpp>

#include <vector>
#include <set>
#include <string>

namespace openstudio {

UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<bool>;
typedef std::vector<bool>        BoolVector;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<unsigned>;
typedef std::vector<unsigned>    UnsignedVector;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<int>;
typedef std::vector<int>         IntVector;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<double>;
typedef std::vector<double>      DoubleVector;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<std::string>;
typedef std::vector<std::string> StringVector;

UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::set<unsigned>;
typedef std::set<unsigned>       UnsignedSet;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::set<int>;
typedef std::set<int>            IntSet;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::set<double>;
typedef std::set<double>         DoubleSet;
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::set<std::string>;
typedef std::set<std::string>    StringSet;

/** Set of strings with case-insensitive comparison. */
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::set<std::string,IstringCompare>;
typedef std::set<std::string,IstringCompare> IStringSet;

UTILITIES_TEMPLATE_EXT template struct UTILITIES_API std::pair<std::string,std::string>;
typedef std::pair<std::string,std::string> StringPair;

UTILITIES_API std::vector<std::string> eraseEmptyElements(const std::vector<std::string>& sv);

/** Helper function to cast a whole vector of objects. \relates IdfObject */
template<typename T, typename U> 
std::vector<T> castVector(const std::vector<U>& objects) {
  std::vector<T> result;
  for (auto & object : objects) {
    T castObject = object.template cast<T>();
    result.push_back( castObject );
  }
  return result;
}

/** Returns a subset of original cast to a new type, only keeping those objects for which the
 *  optionalCast is successful. \relates IdfObject */
template <typename T,typename U>
std::vector<T> subsetCastVector(const std::vector<U>& original) {
  std::vector<T> result;
  for (const auto & elem : original)
  {
    boost::optional<T> oCastObject = elem.template optionalCast<T>();
    if (oCastObject) { result.push_back(*oCastObject); }
  }
  return result;
}

template <typename T, typename U>
std::vector< std::vector<T> > castArray (const std::vector< std::vector<U> >& original) {
  std::vector< std::vector<T> > result;
  for (const auto & elem : original)
  {
    typename std::vector<T> subVector = castVector<T>(elem);
    result.push_back(subVector);
  }
  return result;
}

} // openstudio

#endif // UTILITIES_CORE_CONTAINERS_HPP
