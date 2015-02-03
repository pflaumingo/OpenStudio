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
#include <utilities/idd/AirTerminal_SingleDuct_Uncontrolled_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <exception>
#include <ostream>
#include <string>
#include <vector>

#include "../../model/AirTerminalSingleDuctUncontrolled.hpp"
#include "../../model/Schedule.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/LogMessage.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/Logger.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/Optional.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"
#include "energyplus/ForwardTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateAirTerminalSingleDuctUncontrolled( AirTerminalSingleDuctUncontrolled & modelObject )
{
  OptionalModelObject temp;
  OptionalString optS;
  boost::optional<double> value;
  std::string s;

  IdfObject idfObject(openstudio::IddObjectType::AirTerminal_SingleDuct_Uncontrolled);

  s = modelObject.name().get();
  idfObject.setName(s);

  // hook up required objects
  try {
    idfObject.setString( openstudio::AirTerminal_SingleDuct_UncontrolledFields::AvailabilityScheduleName,
                         modelObject.availabilitySchedule().name().get() );
  }
  catch (std::exception& e) {
    LOG(Error,"Could not translate " << modelObject.briefDescription() << ", because " 
        << e.what() << ".");
    return boost::none;
  }

  temp = modelObject.outletModelObject();
  if(temp)
  {
    optS = temp->name();
    if(optS)
      idfObject.setString(openstudio::AirTerminal_SingleDuct_UncontrolledFields::ZoneSupplyAirNodeName,*optS);
  }

  if( modelObject.isMaximumAirFlowRateAutosized() )
  {
    idfObject.setString(openstudio::AirTerminal_SingleDuct_UncontrolledFields::MaximumAirFlowRate,"AutoSize");
  }
  else if( (value = modelObject.maximumAirFlowRate()) )
  {
    idfObject.setDouble(openstudio::AirTerminal_SingleDuct_UncontrolledFields::MaximumAirFlowRate,value.get());
  }

  m_idfObjects.push_back(idfObject);
  return boost::optional<IdfObject>(idfObject);
}

} // energyplus

} // openstudio

