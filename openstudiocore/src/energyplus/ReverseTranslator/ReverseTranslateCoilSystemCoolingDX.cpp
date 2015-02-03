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
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <string>

#include "../../utilities/idd/IddEnums.hpp"
#include "../ReverseTranslator.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/EnumBase.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/LogMessage.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/Logger.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/IddObject.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idf/Workspace.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idf/WorkspaceObject.hpp"
#include "energyplus/ReverseTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

OptionalModelObject ReverseTranslator::translateCoilSystemCoolingDX( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::CoilSystem_Cooling_DX )
  {
     LOG(Error, "WorkspaceObject is not IddObjectType: CoilSystem:Cooling:DX");
     return boost::none;
  }

  Workspace workspace = workspaceObject.workspace();

  boost::optional<std::string> coolingCoilObjectType;
  boost::optional<std::string> coolingCoilName;

  coolingCoilObjectType = workspaceObject.getString(CoilSystem_Cooling_DXFields::CoolingCoilObjectType);
  coolingCoilName = workspaceObject.getString(CoilSystem_Cooling_DXFields::CoolingCoilName);

  boost::optional<WorkspaceObject> wo;

  if( coolingCoilObjectType && coolingCoilName )
  {
    wo = workspace.getObjectByTypeAndName(IddObjectType(coolingCoilObjectType.get()),coolingCoilName.get());
  }

  if( wo )
  {
    return translateAndMapWorkspaceObject(wo.get());
  }
  else
  {
    return boost::none;
  }
}

} // energyplus

} // openstudio

