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
#include <qstring.h>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_Meter_Cumulative_FieldEnums.hxx>
#include <utilities/idd/Output_Meter_Cumulative_MeterFileOnly_FieldEnums.hxx>
#include <utilities/idd/Output_Meter_FieldEnums.hxx>
#include <utilities/idd/Output_Meter_MeterFileOnly_FieldEnums.hxx>
#include <vector>

#include "../../model/Meter.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/String.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateMeter( Meter & modelObject )
{
  boost::optional<IdfObject> idfObject;

  QString name = toQString(modelObject.name()).replace(QString("FuelOil_"), QString("FuelOil#"));

  if (modelObject.meterFileOnly() && modelObject.cumulative()){
    idfObject = IdfObject (openstudio::IddObjectType::Output_Meter_Cumulative_MeterFileOnly);
    m_idfObjects.push_back(*idfObject);

    idfObject->setString(Output_Meter_Cumulative_MeterFileOnlyFields::Name, toString(name));

    if (!modelObject.isReportingFrequencyDefaulted()){
      idfObject->setString(Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency, modelObject.reportingFrequency());
    }

  }else if (modelObject.meterFileOnly()){
    idfObject = IdfObject (openstudio::IddObjectType::Output_Meter_MeterFileOnly);
    m_idfObjects.push_back(*idfObject);

    idfObject->setString(Output_Meter_MeterFileOnlyFields::Name, toString(name));

    if (!modelObject.isReportingFrequencyDefaulted()){
      idfObject->setString(Output_Meter_MeterFileOnlyFields::ReportingFrequency, modelObject.reportingFrequency());
    }

  }else if (modelObject.cumulative()){
    idfObject = IdfObject (openstudio::IddObjectType::Output_Meter_Cumulative);
    m_idfObjects.push_back(*idfObject);

    idfObject->setString(Output_Meter_CumulativeFields::Name, toString(name));

    if (!modelObject.isReportingFrequencyDefaulted()){
      idfObject->setString(Output_Meter_CumulativeFields::ReportingFrequency, modelObject.reportingFrequency());
    }

  }else{
    idfObject = IdfObject (openstudio::IddObjectType::Output_Meter);
    m_idfObjects.push_back(*idfObject);

    idfObject->setString(Output_MeterFields::Name, toString(name));

    if (!modelObject.isReportingFrequencyDefaulted()){
      idfObject->setString(Output_MeterFields::ReportingFrequency, modelObject.reportingFrequency());
    }

  }

  return idfObject;
}

} // energyplus

} // openstudio

