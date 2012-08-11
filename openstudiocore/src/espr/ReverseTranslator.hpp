/**********************************************************************
*  Copyright (c) 2008-2010, Alliance for Sustainable Energy.
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

// krishnan adding a test comment for SVN check-in

#ifndef ESPR_REVERSETRANSLATOR_HPP
#define ESPR_REVERSETRANSLATOR_HPP

#include "ESPRAPI.hpp"
#include <boost/foreach.hpp>
#include <utilities/core/Path.hpp>
#include <utilities/core/Optional.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/units/Unit.hpp>

#include "TBuilding.h"
#include "TMaterial.h"
#include "TConstruction.h"
#include "TZone.h"
#include "TSurface.h"
#include "Espr3d.h"

class QFile;

namespace openstudio {
namespace model {
  class Model;
  class ModelObject;
  class Surface;
}
namespace ESPR {

  class ESPR_API ReverseTranslator {
  public:
    
    static boost::optional<openstudio::model::Model> ESPRToModel(const openstudio::path& path);


  
  private:

    ReverseTranslator();

    std::string escapeName(QString name);

    boost::optional<openstudio::model::Model> convert(const openstudio::path& path);
    boost::optional<openstudio::model::Model> translateESPR(const openstudio::path& path);
    boost::optional<openstudio::model::ModelObject> translateCampus(TBuilding Building, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateBuilding(TBuilding Building, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateConstruction(TConstruction Construction, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateMaterial(TMaterial Material,  openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateScheduleDay(QFile CFGFile, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateScheduleWeek(QFile CFGFile, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateSchedule(QFile CFGFile, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateSpace(TZone Zone, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateSurface(TSurface Surface, TZone Zone, openstudio::model::Model& model);
    boost::optional<openstudio::model::ModelObject> translateSubSurface(TSurface SubSurface, openstudio::model::Surface& surface);
  
    REGISTER_LOGGER("ESPR.ReverseTranslator");
  };

} // ESPR
} // openstudio

#endif // ESPR_REVERSETRANSLATOR_HPP
