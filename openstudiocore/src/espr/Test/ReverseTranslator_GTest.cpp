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

#include <gtest/gtest.h>
#include <ESPR/Test/ESPRFixture.hpp>

#include <ESPR/ReverseTranslator.hpp>
#include <ESPR/ForwardTranslator.hpp>

#include <energyplus/ForwardTranslator.hpp>

#include <model/Model.hpp>
#include <model/Facility.hpp>
#include <model/Facility_Impl.hpp>
#include <model/Building.hpp>
#include <model/Building_Impl.hpp>
#include <model/ThermalZone.hpp>
#include <model/ThermalZone_Impl.hpp>
#include <model/Space.hpp>
#include <model/Space_Impl.hpp>
#include <model/Surface.hpp>
#include <model/Surface_Impl.hpp>
#include <model/SubSurface.hpp>
#include <model/SubSurface_Impl.hpp>

#include <utilities/idf/Workspace.hpp>
#include <utilities/core/Optional.hpp>

#include <resources.hxx>

#include <sstream>

using namespace openstudio::ESPR;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(ESPRFixture, ReverseTranslator_Geometry)
{
  openstudio::path inputPath = resourcesPath() / openstudio::toPath("espr/2StoreyGarage/cfg/2StoreyGarage.cfg");
  openstudio::path OSMoutputPath = resourcesPath() / openstudio::toPath("espr/2StoreyGarage/cfg/2StoreyGarage.osm");
  openstudio::path IDFoutputPath = resourcesPath() / openstudio::toPath("espr/2StoreyGarage/cfg/2StoreyGarage.idf");

  boost::optional<openstudio::model::Model> model = openstudio::ESPR::ReverseTranslator::ESPRToModel(inputPath);

  ASSERT_TRUE(model);

  //Ensure that a surface that is exterior is set to "Outdoors." 
  OptionalSurface osurf = model->getModelObjectByName<Surface>("wa01C0303");
  ASSERT_TRUE(osurf);
  EXPECT_EQ("Outdoors",osurf->outsideBoundaryCondition());

  //Ensure that an internal surface is deisgnated as a "Surface"
  OptionalSurface interiorFloorSurf = model->getModelObjectByName<Surface>("fl01C0303");
  ASSERT_TRUE(interiorFloorSurf);
  EXPECT_EQ("Surface",interiorFloorSurf->outsideBoundaryCondition());

  //Ensure that glazings are set to default glazing construction. 
  //Ensure that an internal surface is deisgnated as a "Surface"
  boost::optional<SubSurface> Window = model->getModelObjectByName<SubSurface>("wi04C0303");
  ASSERT_TRUE(Window);


 // EXPECT_EQ("Temporary Window Construction",Window->constructionType());



  model->save(OSMoutputPath, true);

  
  openstudio::energyplus::ForwardTranslator energyPlusTranslator;
  openstudio::Workspace workspace = energyPlusTranslator.translateModel(*model);

  EXPECT_TRUE(workspace.numObjects() > 0);

  workspace.save(IDFoutputPath , true);

}

