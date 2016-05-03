/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
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

#ifndef MODEL_DEFAULTSCHEDULESET_HPP
#define MODEL_DEFAULTSCHEDULESET_HPP

#include "ModelAPI.hpp"
#include "ResourceObject.hpp"

#include "../utilities/core/Enum.hpp"

namespace openstudio {
namespace model {

class Schedule;

namespace detail {

  class DefaultScheduleSet_Impl;

} // detail

OPENSTUDIO_ENUM(DefaultScheduleType, 
  ((HoursofOperationSchedule)(Hours of Operation Schedule)(1)) 
  ((NumberofPeopleSchedule)(Number of People Schedule)(2))
  ((PeopleActivityLevelSchedule)(People Activity Level Schedule)(3))
  ((LightingSchedule)(Lighting Schedule)(4))
  ((ElectricEquipmentSchedule)(Electric Equipment Schedule)(5))
  ((GasEquipmentSchedule)(Gas Equipment Schedule)(6))
  ((HotWaterEquipmentSchedule)(Hot Water Equipment Schedule)(7))
  ((InfiltrationSchedule)(Infiltration Schedule)(8))
  ((SteamEquipmentSchedule)(Steam Equipment Schedule)(9))
  ((OtherEquipmentSchedule)(Other Equipment Schedule)(10))
);

/** DefaultScheduleSet is a ResourceObject that wraps the OpenStudio IDD object
 *  'OS:DefaultScheduleSet'. */
class MODEL_API DefaultScheduleSet : public ResourceObject {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit DefaultScheduleSet(const Model& model);

  virtual ~DefaultScheduleSet() {}

  //@}
  /** @name Static Methods */
  //@{

  static IddObjectType iddObjectType();

  //@}
  /** @name Getters */
  //@{

  boost::optional<Schedule> hoursofOperationSchedule() const;

  boost::optional<Schedule> numberofPeopleSchedule() const;

  boost::optional<Schedule> peopleActivityLevelSchedule() const;

  boost::optional<Schedule> lightingSchedule() const;

  boost::optional<Schedule> electricEquipmentSchedule() const;

  boost::optional<Schedule> gasEquipmentSchedule() const;

  boost::optional<Schedule> hotWaterEquipmentSchedule() const;

  boost::optional<Schedule> infiltrationSchedule() const;

  boost::optional<Schedule> steamEquipmentSchedule() const;

  boost::optional<Schedule> otherEquipmentSchedule() const;

  //@}
  /** @name Setters */
  //@{

  bool setHoursofOperationSchedule(Schedule& schedule);

  void resetHoursofOperationSchedule();

  bool setNumberofPeopleSchedule(Schedule& schedule);

  void resetNumberofPeopleSchedule();

  bool setPeopleActivityLevelSchedule(Schedule& schedule);

  void resetPeopleActivityLevelSchedule();

  bool setLightingSchedule(Schedule& schedule);

  void resetLightingSchedule();

  bool setElectricEquipmentSchedule(Schedule& schedule);

  void resetElectricEquipmentSchedule();

  bool setGasEquipmentSchedule(Schedule& schedule);

  void resetGasEquipmentSchedule();

  bool setHotWaterEquipmentSchedule(Schedule& schedule);

  void resetHotWaterEquipmentSchedule();

  bool setInfiltrationSchedule(Schedule& schedule);

  void resetInfiltrationSchedule();

  bool setSteamEquipmentSchedule(Schedule& schedule);

  void resetSteamEquipmentSchedule();

  bool setOtherEquipmentSchedule(Schedule& schedule);

  void resetOtherEquipmentSchedule();

  //@}
  /** @name Other */
  //@{

  /// Returns the default schedule of a particular type.
  boost::optional<Schedule> getDefaultSchedule(const DefaultScheduleType& defaultScheduleType) const;

  /// Merge this object with other one, keep fields from this object if set otherwise set to value from other.
  void merge(const DefaultScheduleSet& other);

  //@}
 protected:
  /// @cond
  typedef detail::DefaultScheduleSet_Impl ImplType;

  friend class Model;
  friend class openstudio::IdfObject;

  explicit DefaultScheduleSet(std::shared_ptr<detail::DefaultScheduleSet_Impl> impl);

  /// @endcond
 private:

  REGISTER_LOGGER("openstudio.model.DefaultScheduleSet");
};

/** \relates DefaultScheduleSet*/
typedef boost::optional<DefaultScheduleSet> OptionalDefaultScheduleSet;

/** \relates DefaultScheduleSet*/
typedef std::vector<DefaultScheduleSet> DefaultScheduleSetVector;

} // model
} // openstudio

extern template class boost::optional<openstudio::model::DefaultScheduleSet>;
template<> std::vector<openstudio::model::DefaultScheduleSet>::vector(size_type) = delete; // do not instantiate
template<> void std::vector<openstudio::model::DefaultScheduleSet>::resize(size_type) = delete; // do not instantiate
extern template class std::vector<openstudio::model::DefaultScheduleSet>;

#endif // MODEL_DEFAULTSCHEDULESET_HPP
