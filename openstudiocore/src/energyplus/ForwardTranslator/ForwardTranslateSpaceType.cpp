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

#include <boost/none.hpp>
#include <boost/optional/optional.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../../model/ElectricEquipment.hpp"
#include "../../model/GasEquipment.hpp"
#include "../../model/HotWaterEquipment.hpp"
#include "../../model/InternalMass.hpp"
#include "../../model/Lights.hpp"
#include "../../model/Luminaire.hpp"
#include "../../model/OtherEquipment.hpp"
#include "../../model/People.hpp"
#include "../../model/Space.hpp"
#include "../../model/SpaceInfiltrationDesignFlowRate.hpp"
#include "../../model/SpaceInfiltrationEffectiveLeakageArea.hpp"
#include "../../model/SpaceType.hpp"
#include "../../model/SteamEquipment.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../utilities/core/Logger.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/Compare.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/LogMessage.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"
#include "energyplus/ForwardTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateSpaceType( SpaceType & modelObject )
{
  std::vector<Space> spaces = modelObject.spaces();

  // check if this is a dummy space type meant to prevent inheriting building space type
  std::vector<ModelObject> children = modelObject.children();
  if (children.empty()){
    LOG(Info, "SpaceType " << modelObject.name().get() << " has no children, it will not be translated");
    return boost::none;
  }

  IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::ZoneList, 
                                                       modelObject);

  std::set<std::string> zoneNames;
  for (const Space& space : spaces){
    boost::optional<ThermalZone> thermalZone = space.thermalZone();
    if (thermalZone){
      zoneNames.insert(thermalZone->name().get());
    }
  }

  idfObject.clearExtensibleGroups();
  for (const std::string& zoneName : zoneNames){
    idfObject.pushExtensibleGroup(std::vector<std::string>(1, zoneName));
  }

  // translate internal mass
  InternalMassVector internalMasses = modelObject.internalMass();
  std::sort(internalMasses.begin(), internalMasses.end(), WorkspaceObjectNameLess());
  for (InternalMass& internalMass : internalMasses){
    translateAndMapModelObject(internalMass);
  }

  // translate lights
  LightsVector lights = modelObject.lights();
  std::sort(lights.begin(), lights.end(), WorkspaceObjectNameLess());
  for (Lights& light : lights){
    translateAndMapModelObject(light);
  }

  // translate luminaires
  LuminaireVector luminaires = modelObject.luminaires();
  std::sort(luminaires.begin(), luminaires.end(), WorkspaceObjectNameLess());
  for (Luminaire& luminaire : luminaires){
    translateAndMapModelObject(luminaire);
  }

  // translate people
  PeopleVector people = modelObject.people();
  std::sort(people.begin(), people.end(), WorkspaceObjectNameLess());
  for (People& person : people){
    translateAndMapModelObject(person);
  }

  // translate electric equipment
  ElectricEquipmentVector electricEquipment = modelObject.electricEquipment();
  std::sort(electricEquipment.begin(), electricEquipment.end(), WorkspaceObjectNameLess());
  for (ElectricEquipment& equipment : electricEquipment){
    translateAndMapModelObject(equipment);
  }

  // translate gas equipment
  GasEquipmentVector gasEquipment = modelObject.gasEquipment();
  std::sort(gasEquipment.begin(), gasEquipment.end(), WorkspaceObjectNameLess());
  for (GasEquipment& equipment : gasEquipment){
    translateAndMapModelObject(equipment);
  }

  // translate hot water equipment
  HotWaterEquipmentVector hotWaterEquipment = modelObject.hotWaterEquipment();
  std::sort(hotWaterEquipment.begin(), hotWaterEquipment.end(), WorkspaceObjectNameLess());
  for (HotWaterEquipment& equipment : hotWaterEquipment){
    translateAndMapModelObject(equipment);
  }

  // translate steam equipment
  SteamEquipmentVector steamEquipment = modelObject.steamEquipment();
  std::sort(steamEquipment.begin(), steamEquipment.end(), WorkspaceObjectNameLess());
  for (SteamEquipment& equipment : steamEquipment){
    translateAndMapModelObject(equipment);
  }

  // translate other equipment
  OtherEquipmentVector otherEquipment = modelObject.otherEquipment();
  std::sort(otherEquipment.begin(), otherEquipment.end(), WorkspaceObjectNameLess());
  for (OtherEquipment& equipment : otherEquipment){
    translateAndMapModelObject(equipment);
  }

  // translate SpaceInfiltration_DesignFlowRate
  SpaceInfiltrationDesignFlowRateVector spaceInfiltrationDesignFlowRates = modelObject.spaceInfiltrationDesignFlowRates();
  std::sort(spaceInfiltrationDesignFlowRates.begin(), spaceInfiltrationDesignFlowRates.end(), WorkspaceObjectNameLess());
  for (SpaceInfiltrationDesignFlowRate& spaceInfiltrationDesignFlowRate : spaceInfiltrationDesignFlowRates){
    translateAndMapModelObject(spaceInfiltrationDesignFlowRate);
  }

  // translate SpaceInfiltration_EffectiveLeakageArea
  SpaceInfiltrationEffectiveLeakageAreaVector spaceInfiltrationEffectiveLeakageAreas = modelObject.spaceInfiltrationEffectiveLeakageAreas();
  std::sort(spaceInfiltrationEffectiveLeakageAreas.begin(), spaceInfiltrationEffectiveLeakageAreas.end(), WorkspaceObjectNameLess());
  for (SpaceInfiltrationEffectiveLeakageArea& spaceInfiltrationEffectiveLeakageArea : spaceInfiltrationEffectiveLeakageAreas){
    translateAndMapModelObject(spaceInfiltrationEffectiveLeakageArea);
  }

  return idfObject;
}

} // energyplus

} // openstudio

