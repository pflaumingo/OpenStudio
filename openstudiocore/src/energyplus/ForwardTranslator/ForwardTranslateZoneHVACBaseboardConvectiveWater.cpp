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
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_Convective_Water_FieldEnums.hxx>
#include <memory>
#include <string>

#include "../../model/CoilHeatingWaterBaseboard.hpp"
#include "../../model/ModelObject.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/StraightComponent.hpp"
#include "../../model/ZoneHVACBaseboardConvectiveWater.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateZoneHVACBaseboardConvectiveWater(
    ZoneHVACBaseboardConvectiveWater & modelObject )
{
  // Makes sure the modelObject gets put in the map, and that the new idfObject gets put in 
  // the final file. Also set's the idfObject's name.
  IdfObject idfObject = createRegisterAndNameIdfObject(IddObjectType::ZoneHVAC_Baseboard_Convective_Water,modelObject);

  boost::optional<std::string> s;
  boost::optional<double> value;
  boost::optional<ModelObject> temp;
  //get the heating coil as a straight component, cast it to optional HT coil, if cast is successful, 
  //get the object of class CoilHeatingWaterBaseboard
  StraightComponent coilStraight = modelObject.heatingCoil();
  boost::optional<CoilHeatingWaterBaseboard>  coilOptionalHeatBBConvWater = coilStraight.optionalCast<CoilHeatingWaterBaseboard>();
  
  // AvailabilityScheduleName
  Schedule availabilitySchedule = modelObject.availabilitySchedule();
  translateAndMapModelObject(availabilitySchedule);
  idfObject.setString(ZoneHVAC_Baseboard_Convective_WaterFields::AvailabilityScheduleName,
                      availabilitySchedule.name().get() );

  if (coilOptionalHeatBBConvWater){
    CoilHeatingWaterBaseboard coilHeatBBConvWater = *coilOptionalHeatBBConvWater;

    // Heating Design Capacity Method - introduced in 8.2.0 and not yet supported in OS
    idfObject.setString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod,"HeatingDesignCapacity");

    // Heating Design Capacity - introduced in 8.2.0 and not yet supported in OS
    idfObject.setString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity,"Autosize");

    // Inlet Node Name 
    temp = coilHeatBBConvWater.inletModelObject();
    if(temp)
    {
      s = temp->name();
      if(s)
      {
        idfObject.setString(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName,*s);
      }
    }

    // Outlet Node Name 
    temp = coilHeatBBConvWater.outletModelObject();
    if(temp)
    {
      s = temp->name();
      if(s)
      {
        idfObject.setString(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName,*s);
      }
    }

    // UFactorTimesAreaValue
    if(coilHeatBBConvWater.isUFactorTimesAreaValueAutosized())
    {
      idfObject.setString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue,"Autosize");
    }
    else if( (value = coilHeatBBConvWater.uFactorTimesAreaValue()) )
    {
      idfObject.setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue,value.get());
    }

   // MaximumWaterFlowRate

    if(coilHeatBBConvWater.isMaximumWaterFlowRateAutosized() )
    {
      idfObject.setString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate,"Autosize");
    }
    else if( (value = coilHeatBBConvWater.maximumWaterFlowRate()) )
    {
      idfObject.setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate,value.get());
    }

   // Convergence Tolerance

    if( coilHeatBBConvWater.isConvergenceToleranceDefaulted())
    {
      idfObject.setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance,0.001);
    }
    else if( (value = coilHeatBBConvWater.convergenceTolerance()) )
    {
      idfObject.setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance,value.get());
    }
  }
 return idfObject;
}

} // energyplus

} // openstudio

