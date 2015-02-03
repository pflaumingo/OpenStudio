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

#ifndef MODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP
#define MODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP

#include <boost/optional/optional.hpp>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>
#include <vector>

#include "ModelAPI.hpp"
#include "ModelObject.hpp"
#include "StraightComponent.hpp"
#include "model/../utilities/idd/../core/LogMessage.hpp"
#include "model/../utilities/idd/../core/Logger.hpp"
#include "model/../utilities/idd/IddEnums.hpp"
#include "model/HVACComponent.hpp"
#include "model/Model.hpp"
#include "model/Schedule.hpp"

namespace openstudio {
class IdfObject;
namespace detail {
class IdfObject_Impl;
}  // namespace detail
}  // namespace openstudio

namespace openstudio {
namespace model {

class HVACComponent;
// TODO: Check the following class names against object getters and setters.
class Schedule;

namespace detail {

  class AirTerminalSingleDuctConstantVolumeReheat_Impl;

} // detail

/** AirTerminalSingleDuctConstantVolumeReheat is a StraightComponent that wraps the OpenStudio IDD object 'OS:AirTerminal:SingleDuct:ConstantVolume:Reheat'. */
class MODEL_API AirTerminalSingleDuctConstantVolumeReheat : public StraightComponent {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit AirTerminalSingleDuctConstantVolumeReheat(const Model& model, Schedule& availabilitySchedule, HVACComponent& coil);

  virtual ~AirTerminalSingleDuctConstantVolumeReheat() {}

  //@}

  static IddObjectType iddObjectType();

  /** @name Getters */
  //@{

  // TODO: Check return type. From object lists, some candidates are: Schedule.
  Schedule availabilitySchedule() const;

  boost::optional<double> maximumAirFlowRate() const;

  bool isMaximumAirFlowRateAutosized() const;

  // TODO: Check return type. From object lists, some candidates are: HeatingCoilName.
  HVACComponent reheatCoil() const;

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;

  bool isMaximumHotWaterorSteamFlowRateAutosized() const;

  double minimumHotWaterorSteamFlowRate() const;

  bool isMinimumHotWaterorSteamFlowRateDefaulted() const;

  double convergenceTolerance() const;

  bool isConvergenceToleranceDefaulted() const;

  double maximumReheatAirTemperature() const;

  bool isMaximumReheatAirTemperatureDefaulted() const;

  //@}
  /** @name Setters */
  //@{

  // TODO: Check argument type. From object lists, some candidates are: Schedule.
  bool setAvailabilitySchedule(Schedule& schedule);

  bool setMaximumAirFlowRate(double maximumAirFlowRate);

  void resetMaximumAirFlowRate();

  void autosizeMaximumAirFlowRate();

  // TODO: Check argument type. From object lists, some candidates are: HeatingCoilName.
  bool setReheatCoil(const HVACComponent& coil);

  void resetReheatCoil();

  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);

  void resetMaximumHotWaterorSteamFlowRate();

  void autosizeMaximumHotWaterorSteamFlowRate();

  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

  void resetMinimumHotWaterorSteamFlowRate();

  bool setConvergenceTolerance(double convergenceTolerance);

  void resetConvergenceTolerance();

  bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);

  void resetMaximumReheatAirTemperature();

  //@}
  /** @name Other */
  //@{

  //@}
 protected:
  /// @cond
  typedef detail::AirTerminalSingleDuctConstantVolumeReheat_Impl ImplType;

  explicit AirTerminalSingleDuctConstantVolumeReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl);

  friend class detail::AirTerminalSingleDuctConstantVolumeReheat_Impl;
  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.AirTerminalSingleDuctConstantVolumeReheat");
};

/** \relates AirTerminalSingleDuctConstantVolumeReheat*/
typedef boost::optional<AirTerminalSingleDuctConstantVolumeReheat> OptionalAirTerminalSingleDuctConstantVolumeReheat;

/** \relates AirTerminalSingleDuctConstantVolumeReheat*/
typedef std::vector<AirTerminalSingleDuctConstantVolumeReheat> AirTerminalSingleDuctConstantVolumeReheatVector;

} // model
} // openstudio

#endif // MODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP

