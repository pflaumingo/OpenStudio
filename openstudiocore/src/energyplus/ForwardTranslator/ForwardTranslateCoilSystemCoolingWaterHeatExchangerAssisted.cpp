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

#include "../ForwardTranslator.hpp"
#include "../../model/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../../model/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/SetpointManager.hpp"
#include "../../model/SetpointManager_Impl.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../../model/CoilCoolingWater.hpp"
#include "../../model/CoilCoolingWater_Impl.hpp"
#include "../../model/ControllerWaterCoil.hpp"
#include "../../model/ControllerWaterCoil_Impl.hpp"
#include "../../model/Model.hpp"
#include "../../utilities/core/Assert.hpp"
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;
using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateCoilSystemCoolingWaterHeatExchangerAssisted( 
    CoilSystemCoolingWaterHeatExchangerAssisted & modelObject)
{
  IdfObject idfObject(IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted);
  m_idfObjects.push_back(idfObject);

  // Name
  if( auto s = modelObject.name() ) {
    idfObject.setName(*s);
  }

  std::string hxSupplyAirInletNodeName;
  // InletNodeName
  if( auto mo = modelObject.inletModelObject() ) {
    if( auto node = mo->optionalCast<Node>() ) {
      hxSupplyAirInletNodeName = node->name().get();
    }
  }

  std::string hxExhaustAirOutletNodeName;
  std::vector<SetpointManager> spms;
  // OutletNodeName
  if( auto mo = modelObject.outletModelObject() ) {
    if( auto node = mo->optionalCast<Node>() ) {
      hxExhaustAirOutletNodeName = node->name().get();
      // Check for SPM we will duplicate this and apply it to the 
      // cooling outlet node
      spms = node->setpointManagers();
    }
  }

  std::string hxSupplyAirOutletNodeName = modelObject.name().get() + " HX Supply Air Outlet - Cooling Inlet Node";
  std::string hxExhaustAirInletNodeName = modelObject.name().get() + " HX Exhaust Air Inlet - Cooling Outlet Node";

  // There needs to be an inner setpoint manager inside the 
  // coil system. Unfortunately this node doesn't exist in the OS Model,
  // because we are not currently making any "interior" connections.
  // This creates some problems. There is no place for an OS client to
  // attach this inner setpoint manager.
  //
  // Here we are going to make an assumption that the correct SPM to use
  // on the inside is going to be the same as the SPM on the coil system outlet node.
  // We clone the "exterior" spm and use this clone on the inside. 
  // Here again we have to hack because we don't have a node to assign the spm clone to.
  // We do at this point know the node name as it will appear in the idf file so we make a
  // standin node and assign that to the spm clone. This is a hack, but effective.
  if( ! spms.empty ) {
    auto model = modelObject.model();
    Node node(model);
    node.setName(hxExhaustAirInletNodeName);

    for( const auto & spm : spms ) {
      auto spmClone = spm.clone(model).cast<SetpointManager>();
      // Need to use some private stuff. :(
      auto spmImpl = spmClone.getImpl<detail::SetpointManager_Impl>()
      spmImpl->setSetpointNode(node);
    }
  }

  // HeatExchangerObjectType
  // HeatExchangerName
  {
    auto hx = modelObject.heatExchanger();
    if( auto idf = translateAndMapModelObject(hx) ) {
      idfObject.setString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType,idf->iddObject().name());
      idfObject.setString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName,idf->name().get());
      if( idf->iddObject().type() == IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent ) {
        idf->setString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName,hxSupplyAirInletNodeName);
        idf->setString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName,hxSupplyAirOutletNodeName);
        idf->setString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNodeName,hxExhaustAirOutletNodeName);
        idf->setString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName,hxExhaustAirInletNodeName);
      }
    }
  }

  // CoolingCoilObjectType
  // CoolingCoilName
  {
    auto coolingCoil = modelObject.coolingCoil();
    if( auto idf = translateAndMapModelObject(coolingCoil) ) {
      idfObject.setString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType,idf->iddObject().name());
      idfObject.setString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName,idf->name().get());
      if( idf->iddObject().type() == IddObjectType::Coil_Cooling_Water ) {
        idf->setString(Coil_Cooling_WaterFields::AirInletNodeName,hxSupplyAirOutletNodeName);
        idf->setString(Coil_Cooling_WaterFields::AirOutletNodeName,hxExhaustAirInletNodeName);
      }
    }
    if( auto coilCoolingWater = coolingCoil.optionalCast<CoilCoolingWater>() ) {
      if( auto controller = coilCoolingWater->controllerWaterCoil() ) {
        if( auto idf = translateAndMapModelObject(controller.get()) ) {
          idf->setString(Controller_WaterCoilFields::SensorNodeName,hxExhaustAirInletNodeName);
        }
      }
    }
  }

  return idfObject;
}

} // energyplus
} // openstudio
