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
#include <utilities/idd/OS_RunPeriodControl_SpecialDays_FieldEnums.hxx>
#include <utilities/idd/RunPeriodControl_SpecialDays_FieldEnums.hxx>
#include <string>
#include <vector>

#include "../../model/RunPeriodControlSpecialDays.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/String.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateRunPeriodControlSpecialDays( RunPeriodControlSpecialDays & modelObject )
{
  IdfObject idfObject( openstudio::IddObjectType::RunPeriodControl_SpecialDays);

  m_idfObjects.push_back(idfObject);

  boost::optional<std::string> s;

  s = modelObject.name();
  if (s) {
    idfObject.setName(*s);
  }

  s = modelObject.getString(OS_RunPeriodControl_SpecialDaysFields::StartDate);
  if( s )
  {
    QString temp = toQString(s.get());
    temp.replace("5th", "Last");
    idfObject.setString(RunPeriodControl_SpecialDaysFields::StartDate,temp.toStdString());
  }

  s = modelObject.getString(OS_RunPeriodControl_SpecialDaysFields::Duration);
  if( s )
  {
    idfObject.setString(RunPeriodControl_SpecialDaysFields::Duration,s.get());
  }

  s = modelObject.getString(OS_RunPeriodControl_SpecialDaysFields::SpecialDayType);
  if( s )
  {
    idfObject.setString(RunPeriodControl_SpecialDaysFields::SpecialDayType,s.get());
  }

  return boost::optional<IdfObject>(idfObject);
}

} // energyplus

} // openstudio

