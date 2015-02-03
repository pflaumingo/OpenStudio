/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
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

#include <boost/optional/optional.hpp>
#include <utilities/idd/AirLoopHVAC_ReturnPlenum_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <memory>
#include <string>
#include <vector>

#include "../../model/AirLoopHVACReturnPlenum.hpp"
#include "../../model/AirLoopHVACReturnPlenum_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/PortList.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/Optional.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"
#include "energyplus/ForwardTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateAirLoopHVACReturnPlenum( AirLoopHVACReturnPlenum & modelObject )
{
  OptionalModelObject temp;
  OptionalString optS;
  std::string s;

  IdfObject idfObject(openstudio::IddObjectType::AirLoopHVAC_ReturnPlenum);

  m_idfObjects.push_back(idfObject);

  // Name
  s = modelObject.name().get();
  idfObject.setName(s);

  //((ZoneName)(Zone Name))
  //((ZoneNodeName)(Zone Node Name))
  
  //  InducedAirOutletNodeorNodeListName
  PortList po = modelObject.getImpl<model::detail::AirLoopHVACReturnPlenum_Impl>()->inducedAirOutletPortList();
  std::vector<ModelObject> inducedNodes = po.modelObjects();
  if( ! inducedNodes.empty() )
  {
    IdfObject nodeList(openstudio::IddObjectType::NodeList); 
    m_idfObjects.push_back(nodeList);
    nodeList.setName(s + " Induced Air Node List");
    idfObject.setString(AirLoopHVAC_ReturnPlenumFields::InducedAirOutletNodeorNodeListName,nodeList.name().get());
    for( std::vector<ModelObject>::const_iterator it = inducedNodes.begin();
         it != inducedNodes.end();
         ++it )
    {
      IdfExtensibleGroup eg = nodeList.pushExtensibleGroup();
      eg.setString(NodeListExtensibleFields::NodeName,it->name().get());
    }
  }

  // OutletNodeName

  if( boost::optional<model::ModelObject> node = modelObject.outletModelObject() )
  {
    idfObject.setString(AirLoopHVAC_ReturnPlenumFields::OutletNodeName,node->name().get());
  }

  //// ZoneName
  //// and
  //// ZoneNodeName

  if( boost::optional<model::ThermalZone> zone = modelObject.thermalZone() )
  {
    if( boost::optional<IdfObject> _zone = translateAndMapModelObject(zone.get()) )
    {
      idfObject.setString(AirLoopHVAC_ReturnPlenumFields::ZoneName,_zone->name().get());

      model::Node node = zone->zoneAirNode();
      idfObject.setString(AirLoopHVAC_ReturnPlenumFields::ZoneNodeName,node.name().get());
    }
  }


  // InletNodeName
  
  std::vector<ModelObject> inletModelObjects = modelObject.inletModelObjects();
  for( auto & inletModelObject : inletModelObjects )
  {
    IdfExtensibleGroup eg = idfObject.pushExtensibleGroup();
    eg.setString(AirLoopHVAC_ReturnPlenumExtensibleFields::InletNodeName,inletModelObject.name().get());
  }

  return boost::optional<IdfObject>(idfObject);
}

} // energyplus

} // openstudio

