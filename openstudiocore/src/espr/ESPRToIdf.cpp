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

#include <ESPR/ReverseTranslator.hpp>
#include <model/Model.hpp>
#include <energyplus/ForwardTranslator.hpp>

#include <utilities/idf/Workspace.hpp>
#include <utilities/idf/IdfFile.hpp>
#include <utilities/core/CommandLine.hpp>
#include <utilities/core/Path.hpp>

#include <string>
#include <iostream>


int main(int argc, char *argv[])
{
  std::string inputPathString;

  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
      ("help", "print help message")
      ("inputPath", boost::program_options::value<std::string>(&inputPathString), "path to ESPR CFG file")
  ;

  boost::program_options::variables_map vm;        
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);    

  if (vm.count("help")) {
    std::cout << "Usage: ESPRToIdf --inputPath=./path/to/project/*.cfg" << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }

//  if (vm.count("inputPath")) {
    if (true)
	{
  //Set cfg path. 
    openstudio::path inputPath = openstudio::toPath("C:/HOT3000v3Beta/user/2StoreyGarage/cfg/2StoreyGarage.cfg");

	//Create OSM
    boost::optional<openstudio::model::Model> model = openstudio::ESPR::ReverseTranslator::ESPRToModel(inputPath);
    
	//If model is created. 
	if(model){
	  //create osm path.
      openstudio::path osmPath = inputPath.replace_extension(openstudio::toPath("osm").string());
      //save the file. 
	  model->save(osmPath, true);

	  //create idf file path. 
      openstudio::path idfPath = inputPath.replace_extension(openstudio::toPath("idf").string());
      
	  //generate energyplus model
	  openstudio::energyplus::ForwardTranslator forwardTranslator;
      openstudio::Workspace workspace =  forwardTranslator.translateModel(*model);
      //save the file. 
	  workspace.toIdfFile().save(idfPath, true);
      return 0;

    }else{
      std::cout << "Could not convert file at '" << inputPathString << "' to an OpenStudio Model" << std::endl;
      return 1;
    }

  } else {
    std::cout << "No input path given." << desc << std::endl;
    std::cout << "Usage: ESPRToIdf --inputPath=./path/to/ESPR.xml" << std::endl;
    return 1;
  }
}



