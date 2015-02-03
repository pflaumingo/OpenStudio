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
#include <utilities/idd/InternalMass_FieldEnums.hxx>
#include <memory>
#include <string>

#include "../../model/ConstructionBase.hpp"
#include "../../model/InternalMass.hpp"
#include "../../model/InternalMassDefinition.hpp"
#include "../../model/Space.hpp"
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

OptionalModelObject ReverseTranslator::translateInternalMass( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::InternalMass ){
    LOG(Error, "WorkspaceObject is not IddObjectType: InternalMass");
    return boost::none;
  }

  // create the definition
  openstudio::model::InternalMassDefinition definition(m_model);
  
  OptionalString s = workspaceObject.name();
  if(s){
    definition.setName(*s + " Definition");
  }

  OptionalWorkspaceObject target = workspaceObject.getTarget(openstudio::InternalMassFields::ConstructionName);
  if (target){
    OptionalModelObject modelObject = translateAndMapWorkspaceObject(*target);
    if (modelObject){
      if (modelObject->optionalCast<ConstructionBase>()){
        definition.setConstruction(modelObject->cast<ConstructionBase>());
      }
    }
  }

  OptionalDouble d = workspaceObject.getDouble(openstudio::InternalMassFields::SurfaceArea);
  if(d){
    definition.setSurfaceArea(*d);
  }

  // create the instance
  InternalMass internalMass(definition);

  s = workspaceObject.name();
  if(s){
    internalMass.setName(*s);
  }

  target = workspaceObject.getTarget(openstudio::InternalMassFields::ZoneName);
  if (target){
    OptionalModelObject modelObject = translateAndMapWorkspaceObject(*target);
    if (modelObject){
      if (modelObject->optionalCast<Space>()){
        internalMass.setSpace(modelObject->cast<Space>());
      }else if (modelObject->optionalCast<SpaceType>()){
        internalMass.setSpaceType(modelObject->cast<SpaceType>());
      }
    }
  }

  return internalMass;
}

} // energyplus

} // openstudio

