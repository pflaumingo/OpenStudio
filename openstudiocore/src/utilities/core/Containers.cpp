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

#include "Containers.hpp"

template class UTILITIES_API std::vector<bool>;
template class UTILITIES_API std::vector<unsigned>;
template class UTILITIES_API std::vector<int>;
template class UTILITIES_API std::vector<double>;
template class UTILITIES_API std::vector<std::string>;

template class UTILITIES_API std::set<unsigned>;
template class UTILITIES_API std::set<int>;
template class UTILITIES_API std::set<double>;
template class UTILITIES_API std::set<std::string>;

template class UTILITIES_API std::set<std::string, openstudio::IstringCompare>;

template struct UTILITIES_API std::pair<std::string, std::string>;

namespace openstudio {

  StringVector eraseEmptyElements(const StringVector& sv) {
    StringVector result;
    for (const std::string& str : sv) {
      if (!str.empty()) {
        result.push_back(str);
      }
    }
    return result;
  }

} // openstudio 
