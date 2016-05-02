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

#include "ObjectPointer.hpp"

#include "../core/Assert.hpp"

template struct UTILITIES_API openstudio::ObjectPointer<unsigned, openstudio::Handle>;
template struct UTILITIES_API openstudio::ObjectPointer<openstudio::Handle, unsigned>;
template struct UTILITIES_API openstudio::ObjectPointer<openstudio::Handle, openstudio::Handle>;

template class UTILITIES_API std::vector<openstudio::UHPointer>;
template class UTILITIES_API std::vector<openstudio::HUPointer>;
template class UTILITIES_API std::vector<openstudio::HHPointer>;


namespace openstudio {

} // openstudio
