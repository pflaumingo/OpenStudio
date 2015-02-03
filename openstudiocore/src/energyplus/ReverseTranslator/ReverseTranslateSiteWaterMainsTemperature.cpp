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
#include <utilities/idd/Site_WaterMainsTemperature_FieldEnums.hxx>
#include <memory>

#include "../../model/Schedule.hpp"
#include "../../model/SiteWaterMainsTemperature.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../ReverseTranslator.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/EnumBase.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/LogMessage.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/Logger.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/IddObject.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idf/WorkspaceObject.hpp"
#include "energyplus/ReverseTranslator/../../model/Model.hpp"
#include "energyplus/ReverseTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

OptionalModelObject ReverseTranslator::translateSiteWaterMainsTemperature( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::Site_WaterMainsTemperature )
  {
     LOG(Error, "WorkspaceObject is not IddObjectType: Site_WaterMainsTemperature");
     return boost::none;
  }

  SiteWaterMainsTemperature mo = m_model.getUniqueModelObject<SiteWaterMainsTemperature>();

  boost::optional<WorkspaceObject> wo;
  boost::optional<Schedule> schedule;

  wo = workspaceObject.getTarget(Site_WaterMainsTemperatureFields::TemperatureScheduleName);
  if( wo )
  {
    boost::optional<ModelObject> mo2 = translateAndMapWorkspaceObject(wo.get());
    if( mo2 )
    {
      if( (schedule = mo2->optionalCast<Schedule>()) )
      {
        mo.setTemperatureSchedule(schedule.get());
      }
    }
  }

  boost::optional<double> value = workspaceObject.getDouble(Site_WaterMainsTemperatureFields::AnnualAverageOutdoorAirTemperature);
  if( value )
  {
    mo.setAnnualAverageOutdoorAirTemperature(value.get());
  }

  value = workspaceObject.getDouble(Site_WaterMainsTemperatureFields::MaximumDifferenceInMonthlyAverageOutdoorAirTemperatures);
  if( value )
  {
    mo.setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(value.get());
  }

  return mo;
}

} // energyplus

} // openstudio

