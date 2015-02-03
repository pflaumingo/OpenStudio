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
#include <utilities/idd/ZoneInfiltration_EffectiveLeakageArea_FieldEnums.hxx>
#include <memory>
#include <ostream>
#include <string>

#include "../../model/Schedule.hpp"
#include "../../model/Space.hpp"
#include "../../model/SpaceInfiltrationEffectiveLeakageArea.hpp"
#include "../../model/SpaceType.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../ReverseTranslator.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/EnumBase.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/LogMessage.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/Logger.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/Optional.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/IddObject.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idf/WorkspaceObject.hpp"
#include "energyplus/ReverseTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

OptionalModelObject ReverseTranslator::translateZoneInfiltrationEffectiveLeakageArea( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::ZoneInfiltration_EffectiveLeakageArea ){
    LOG(Error, "WorkspaceObject " << workspaceObject.briefDescription()
        << " is not IddObjectType: SpaceInfiltration_EffectiveLeakageArea");
    return boost::none;
  }

  // create the instance
  SpaceInfiltrationEffectiveLeakageArea spaceInfiltrationEffectiveLeakageArea(m_model);

  OptionalString s = workspaceObject.name();
  if(s){
    spaceInfiltrationEffectiveLeakageArea.setName(*s);
  }

  OptionalWorkspaceObject target = workspaceObject.getTarget(ZoneInfiltration_EffectiveLeakageAreaFields::ZoneName);
  if (target){
    OptionalModelObject modelObject = translateAndMapWorkspaceObject(*target);
    if (modelObject){
      if (modelObject->optionalCast<Space>()){
        spaceInfiltrationEffectiveLeakageArea.setSpace(modelObject->cast<Space>());
      }else if (modelObject->optionalCast<SpaceType>()){
        spaceInfiltrationEffectiveLeakageArea.setSpaceType(modelObject->cast<SpaceType>());
      }
    }
  }

  target = workspaceObject.getTarget(ZoneInfiltration_EffectiveLeakageAreaFields::ScheduleName);
  if (target){
    OptionalModelObject modelObject = translateAndMapWorkspaceObject(*target);
    if (modelObject){
      if (OptionalSchedule intermediate = modelObject->optionalCast<Schedule>()){
        Schedule schedule(*intermediate);
        spaceInfiltrationEffectiveLeakageArea.setSchedule(schedule);
      }
    }
  }

  boost::optional<double> value = workspaceObject.getDouble(ZoneInfiltration_EffectiveLeakageAreaFields::EffectiveAirLeakageArea);
  if( value )
  {
    spaceInfiltrationEffectiveLeakageArea.setEffectiveAirLeakageArea(value.get());
  }

  value = workspaceObject.getDouble(ZoneInfiltration_EffectiveLeakageAreaFields::StackCoefficient);
  if( value )
  {
    spaceInfiltrationEffectiveLeakageArea.setStackCoefficient(value.get());
  }

  value = workspaceObject.getDouble(ZoneInfiltration_EffectiveLeakageAreaFields::WindCoefficient);
  if( value )
  {
    spaceInfiltrationEffectiveLeakageArea.setWindCoefficient(value.get());
  }
  
  return spaceInfiltrationEffectiveLeakageArea;
}

} // energyplus

} // openstudio

