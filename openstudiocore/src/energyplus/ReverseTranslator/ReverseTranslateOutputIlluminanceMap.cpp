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
#include <utilities/idd/Output_IlluminanceMap_FieldEnums.hxx>
#include <memory>

#include "../../model/IlluminanceMap.hpp"
#include "../../model/Space.hpp"
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

OptionalModelObject ReverseTranslator::translateOutputIlluminanceMap( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::Output_IlluminanceMap ){
    LOG(Error, "WorkspaceObject is not IddObjectType: Output:IlluminanceMap");
    return boost::none;
  }

  IlluminanceMap illuminanceMap( m_model );

  OptionalString s = workspaceObject.name();
  if (s){
    illuminanceMap.setName(*s);
  }

  OptionalWorkspaceObject target = workspaceObject.getTarget(Output_IlluminanceMapFields::ZoneName);
  if (target){
    OptionalModelObject modelObject = translateAndMapWorkspaceObject(*target);
    if (modelObject){
      if (modelObject->optionalCast<Space>()){
        illuminanceMap.setSpace(modelObject->cast<Space>());
      }
    }
  }

  OptionalDouble d = workspaceObject.getDouble(Output_IlluminanceMapFields::Zheight);
  if (d){
    illuminanceMap.setOriginZCoordinate(*d);
  }

  d = workspaceObject.getDouble(Output_IlluminanceMapFields::XMinimumCoordinate);
  if (d){
    illuminanceMap.setOriginXCoordinate(*d);

    OptionalDouble maxX = workspaceObject.getDouble(Output_IlluminanceMapFields::XMaximumCoordinate);
    if (maxX){
      illuminanceMap.setXLength(*maxX - *d);
    }
  }

  OptionalInt i = workspaceObject.getInt(Output_IlluminanceMapFields::NumberofXGridPoints);
  if (i){
    illuminanceMap.setNumberofXGridPoints(*i);
  }

  d = workspaceObject.getDouble(Output_IlluminanceMapFields::YMinimumCoordinate);
  if (d){
    illuminanceMap.setOriginYCoordinate(*d);

    OptionalDouble maxY = workspaceObject.getDouble(Output_IlluminanceMapFields::YMaximumCoordinate);
    if (maxY){
      illuminanceMap.setYLength(*maxY - *d);
    }
  }

  i = workspaceObject.getInt(Output_IlluminanceMapFields::NumberofYGridPoints);
  if (i){
    illuminanceMap.setNumberofYGridPoints(*i);
  }

  return illuminanceMap;
}

} // energyplus

} // openstudio

