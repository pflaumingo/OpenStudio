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
#include <utilities/idd/Schedule_Week_Daily_FieldEnums.hxx>
#include <vector>

#include "../../model/ScheduleDay.hpp"
#include "../../model/ScheduleWeek.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/IddEnums.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"


using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

#define MAP_SCHEDULE(_idfObject, _fieldIndex, _scheduleDay) \
if (_scheduleDay){ \
  boost::optional<IdfObject> idfScheduleDay = translateAndMapModelObject(*(_scheduleDay)); \
  if (idfScheduleDay){ \
    _idfObject.setString(_fieldIndex, idfScheduleDay->name().get()); \
  } \
} 


boost::optional<IdfObject> ForwardTranslator::translateScheduleWeek( ScheduleWeek & modelObject )
{
  IdfObject scheduleWeek( openstudio::IddObjectType::Schedule_Week_Daily );

  m_idfObjects.push_back(scheduleWeek);

  scheduleWeek.setName(modelObject.name().get());

  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::SundaySchedule_DayName, modelObject.sundaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::MondaySchedule_DayName, modelObject.mondaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::TuesdaySchedule_DayName, modelObject.tuesdaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::WednesdaySchedule_DayName, modelObject.wednesdaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::ThursdaySchedule_DayName, modelObject.thursdaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::FridaySchedule_DayName, modelObject.fridaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::SaturdaySchedule_DayName, modelObject.saturdaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::HolidaySchedule_DayName, modelObject.holidaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::SummerDesignDaySchedule_DayName, modelObject.summerDesignDaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::WinterDesignDaySchedule_DayName, modelObject.winterDesignDaySchedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::CustomDay1Schedule_DayName, modelObject.customDay1Schedule());
  MAP_SCHEDULE(scheduleWeek, Schedule_Week_DailyFields::CustomDay2Schedule_DayName, modelObject.customDay2Schedule());

  return scheduleWeek;
}

} // energyplus

} // openstudio

