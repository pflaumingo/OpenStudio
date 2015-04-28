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

#include <model/TemperingValve.hpp>
#include <model/TemperingValve_Impl.hpp>
#include <model/Node.hpp>
#include <model/Node_Impl.hpp>
#include <model/Mixer.hpp>
#include <model/Mixer_Impl.hpp>
#include <model/PumpConstantSpeed.hpp>
#include <model/PumpConstantSpeed_Impl.hpp>
#include <model/PumpVariableSpeed.hpp>
#include <model/PumpVariableSpeed_Impl.hpp>
#include <model/HeaderedPumpsConstantSpeed.hpp>
#include <model/HeaderedPumpsConstantSpeed_Impl.hpp>
#include <model/HeaderedPumpsVariableSpeed.hpp>
#include <model/HeaderedPumpsVariableSpeed_Impl.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OS_TemperingValve_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace model {

namespace detail {

  TemperingValve_Impl::TemperingValve_Impl(const IdfObject& idfObject,
                                           Model_Impl* model,
                                           bool keepHandle)
    : StraightComponent_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == TemperingValve::iddObjectType());
  }

  TemperingValve_Impl::TemperingValve_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle)
    : StraightComponent_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == TemperingValve::iddObjectType());
  }

  TemperingValve_Impl::TemperingValve_Impl(const TemperingValve_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle)
    : StraightComponent_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& TemperingValve_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType TemperingValve_Impl::iddObjectType() const {
    return TemperingValve::iddObjectType();
  }

  boost::optional<Node> TemperingValve_Impl::stream2SourceNode() const {
    return getObject<ModelObject>().getModelObjectTarget<Node>(OS_TemperingValveFields::Stream2SourceNode);
  }

  boost::optional<Node> TemperingValve_Impl::temperatureSetpointNode() const {
    return getObject<ModelObject>().getModelObjectTarget<Node>(OS_TemperingValveFields::TemperatureSetpointNode);
  }

  boost::optional<Node> TemperingValve_Impl::pumpOutletNode() const {
    return getObject<ModelObject>().getModelObjectTarget<Node>(OS_TemperingValveFields::PumpOutletNode);
  }

  bool TemperingValve_Impl::setStream2SourceNode(const boost::optional<Node> & stream2SourceNode) {
    bool result(false);
    if (stream2SourceNode) {
      result = setPointer(OS_TemperingValveFields::Stream2SourceNode, stream2SourceNode.get().handle());
    }
    else {
      resetStream2SourceNode();
      result = true;
    }
    return result;
  }

  void TemperingValve_Impl::resetStream2SourceNode() {
    bool result = setString(OS_TemperingValveFields::Stream2SourceNode, "");
    OS_ASSERT(result);
  }

  bool TemperingValve_Impl::setTemperatureSetpointNode(const boost::optional<Node> & temperatureSetpointNode) {
    bool result(false);
    if (temperatureSetpointNode) {
      result = setPointer(OS_TemperingValveFields::TemperatureSetpointNode, temperatureSetpointNode.get().handle());
    }
    else {
      resetTemperatureSetpointNode();
      result = true;
    }
    return result;
  }

  void TemperingValve_Impl::resetTemperatureSetpointNode() {
    bool result = setString(OS_TemperingValveFields::TemperatureSetpointNode, "");
    OS_ASSERT(result);
  }

  bool TemperingValve_Impl::setPumpOutletNode(const boost::optional<Node> & pumpOutletNode) {
    bool result(false);
    if (pumpOutletNode) {
      result = setPointer(OS_TemperingValveFields::PumpOutletNode, pumpOutletNode.get().handle());
    }
    else {
      resetPumpOutletNode();
      result = true;
    }
    return result;
  }

  void TemperingValve_Impl::resetPumpOutletNode() {
    bool result = setString(OS_TemperingValveFields::PumpOutletNode, "");
    OS_ASSERT(result);
  }

  unsigned TemperingValve_Impl::inletPort() {
    return OS_TemperingValveFields::InletNodeName;
  }

  unsigned TemperingValve_Impl::outletPort() {
    return OS_TemperingValveFields::OutletNodeName;
  }

  bool TemperingValve_Impl::addToNode(Node & node)
  {
    auto plant = node.plantLoop();

    if( ! plant ) {
      return false;
    }
    
    std::vector<ModelObject> allpumps;
    auto pumps = plant->supplyComponents(PumpVariableSpeed::iddObjectType());
    allpumps.insert(allpumps.end(),pumps.begin(),pumps.end());
    pumps = plant->supplyComponents(PumpConstantSpeed::iddObjectType());
    allpumps.insert(allpumps.end(),pumps.begin(),pumps.end());
    pumps = plant->supplyComponents(HeaderedPumpsConstantSpeed::iddObjectType());
    allpumps.insert(allpumps.end(),pumps.begin(),pumps.end());
    pumps = plant->supplyComponents(HeaderedPumpsVariableSpeed::iddObjectType());
    allpumps.insert(allpumps.end(),pumps.begin(),pumps.end());

    if( allpumps.size() == 1 ) {
      if( auto mo = allpumps.back().cast<StraightComponent>().outletModelObject() ) {
        if( auto node = mo->optionalCast<Node>() ) {
          setPumpOutletNode(node);
        }
      }
    }

    auto mixer = plant->supplyMixer();

    {
      auto mo = mixer.outletModelObject();
      OS_ASSERT(mo);
      if( auto node = mo->optionalCast<Node>() ) {
        setTemperatureSetpointNode(node.get());
      }
    }

    { 
      auto inletObjects = mixer.inletModelObjects();
      if( inletObjects.size() == 1u ) {
        if( auto node = inletObjects.front().optionalCast<Node>() ) {
          setStream2SourceNode(node.get());
        }
      }
    }

    return StraightComponent_Impl::addToNode(node);
  }

} // detail

TemperingValve::TemperingValve(const Model& model)
  : StraightComponent(TemperingValve::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::TemperingValve_Impl>());
}

IddObjectType TemperingValve::iddObjectType() {
  return IddObjectType(IddObjectType::OS_TemperingValve);
}

boost::optional<Node> TemperingValve::stream2SourceNode() const {
  return getImpl<detail::TemperingValve_Impl>()->stream2SourceNode();
}

boost::optional<Node> TemperingValve::temperatureSetpointNode() const {
  return getImpl<detail::TemperingValve_Impl>()->temperatureSetpointNode();
}

boost::optional<Node> TemperingValve::pumpOutletNode() const {
  return getImpl<detail::TemperingValve_Impl>()->pumpOutletNode();
}

bool TemperingValve::setStream2SourceNode(const Node & stream2SourceNode) {
  return getImpl<detail::TemperingValve_Impl>()->setStream2SourceNode(stream2SourceNode);
}

void TemperingValve::resetStream2SourceNode() {
  getImpl<detail::TemperingValve_Impl>()->resetStream2SourceNode();
}

bool TemperingValve::setTemperatureSetpointNode(const Node & temperatureSetpointNode) {
  return getImpl<detail::TemperingValve_Impl>()->setTemperatureSetpointNode(temperatureSetpointNode);
}

void TemperingValve::resetTemperatureSetpointNode() {
  getImpl<detail::TemperingValve_Impl>()->resetTemperatureSetpointNode();
}

bool TemperingValve::setPumpOutletNode(const Node & pumpOutletNode) {
  return getImpl<detail::TemperingValve_Impl>()->setPumpOutletNode(pumpOutletNode);
}

void TemperingValve::resetPumpOutletNode() {
  getImpl<detail::TemperingValve_Impl>()->resetPumpOutletNode();
}

/// @cond
TemperingValve::TemperingValve(std::shared_ptr<detail::TemperingValve_Impl> impl)
  : StraightComponent(impl)
{}
/// @endcond

} // model
} // openstudio

