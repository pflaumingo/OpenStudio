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

#ifndef MODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP
#define MODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP

#include <boost/optional/optional.hpp>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>
#include <vector>

#include "HVACComponent.hpp"
#include "ModelAPI.hpp"
#include "model/../utilities/idd/../core/LogMessage.hpp"
#include "model/../utilities/idd/../core/Logger.hpp"
#include "model/../utilities/idd/IddEnums.hpp"
#include "model/Curve.hpp"
#include "model/Model.hpp"
#include "model/Schedule.hpp"

namespace openstudio {
namespace detail {
class IdfObject_Impl;
}  // namespace detail
}  // namespace openstudio

namespace openstudio {

namespace model {

class Curve;
class Schedule;

namespace detail {

  class CoilHeatingDXVariableRefrigerantFlow_Impl;

} // detail

/** CoilHeatingDXVariableRefrigerantFlow is a HVACComponent that wraps the OpenStudio IDD object 'OS:Coil:Heating:DX:VariableRefrigerantFlow'. */
class MODEL_API CoilHeatingDXVariableRefrigerantFlow : public HVACComponent {
 public:

  explicit CoilHeatingDXVariableRefrigerantFlow(const Model& model);

  virtual ~CoilHeatingDXVariableRefrigerantFlow() {}

  static IddObjectType iddObjectType();

  Schedule availabilitySchedule() const;

  bool setAvailabilitySchedule(Schedule& schedule);

  boost::optional<double> ratedTotalHeatingCapacity() const;

  bool isRatedTotalHeatingCapacityAutosized() const;

  bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);

  void autosizeRatedTotalHeatingCapacity();

  boost::optional<double> ratedAirFlowRate() const;

  bool isRatedAirFlowRateAutosized() const;

  bool setRatedAirFlowRate(double ratedAirFlowRate);

  void autosizeRatedAirFlowRate();

  Curve heatingCapacityRatioModifierFunctionofTemperatureCurve() const;

  bool setHeatingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve);

  Curve heatingCapacityModifierFunctionofFlowFractionCurve() const;

  bool setHeatingCapacityModifierFunctionofFlowFractionCurve(const Curve& curve);

 protected:

  /// @cond
  typedef detail::CoilHeatingDXVariableRefrigerantFlow_Impl ImplType;

  explicit CoilHeatingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlow_Impl> impl);

  friend class detail::CoilHeatingDXVariableRefrigerantFlow_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond

 private:

  REGISTER_LOGGER("openstudio.model.CoilHeatingDXVariableRefrigerantFlow");
};

/** \relates CoilHeatingDXVariableRefrigerantFlow*/
typedef boost::optional<CoilHeatingDXVariableRefrigerantFlow> OptionalCoilHeatingDXVariableRefrigerantFlow;

/** \relates CoilHeatingDXVariableRefrigerantFlow*/
typedef std::vector<CoilHeatingDXVariableRefrigerantFlow> CoilHeatingDXVariableRefrigerantFlowVector;

} // model
} // openstudio

#endif // MODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP

