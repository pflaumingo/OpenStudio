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

#include <utilities/idd/IddEnums.hxx>
#include <string>

#include "../utilities/core/Assert.hpp"
#include "InfraredTransparentMaterial.hpp"
#include "InfraredTransparentMaterial_Impl.hpp"
#include "model/../utilities/idd/../core/EnumBase.hpp"
#include "model/../utilities/idd/IddObject.hpp"
#include "model/../utilities/idf/IdfObject.hpp"
#include "model/../utilities/idf/WorkspaceObject_Impl.hpp"
#include "model/ModelPartitionMaterial.hpp"
#include "model/ModelPartitionMaterial_Impl.hpp"

namespace openstudio {
namespace model {
class Model;
}  // namespace model
}  // namespace openstudio

namespace openstudio {
namespace model {

namespace detail {

class Model_Impl;

  InfraredTransparentMaterial_Impl::InfraredTransparentMaterial_Impl(const IdfObject& idfObject,
                                                                     Model_Impl* model,
                                                                     bool keepHandle)
    : ModelPartitionMaterial_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == InfraredTransparentMaterial::iddObjectType());
  }

  InfraredTransparentMaterial_Impl::InfraredTransparentMaterial_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                     Model_Impl* model,
                                                                     bool keepHandle)
    : ModelPartitionMaterial_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == InfraredTransparentMaterial::iddObjectType());
  }

  InfraredTransparentMaterial_Impl::InfraredTransparentMaterial_Impl(const InfraredTransparentMaterial_Impl& other,
                                                                     Model_Impl* model,
                                                                     bool keepHandle)
    : ModelPartitionMaterial_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& InfraredTransparentMaterial_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType InfraredTransparentMaterial_Impl::iddObjectType() const {
    return InfraredTransparentMaterial::iddObjectType();
  }

} // detail

InfraredTransparentMaterial::InfraredTransparentMaterial(const Model& model)
  : ModelPartitionMaterial(InfraredTransparentMaterial::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::InfraredTransparentMaterial_Impl>());

  // TODO: Appropriately handle the following required object-list fields.
  bool ok = true;
  // ok = setHandle();
  OS_ASSERT(ok);
}

IddObjectType InfraredTransparentMaterial::iddObjectType() {
  return IddObjectType(IddObjectType::OS_Material_InfraredTransparent);
}

/// @cond
InfraredTransparentMaterial::InfraredTransparentMaterial(std::shared_ptr<detail::InfraredTransparentMaterial_Impl> impl)
  : ModelPartitionMaterial(impl)
{}
/// @endcond

} // model
} // openstudio

