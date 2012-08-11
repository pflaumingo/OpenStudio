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
#include <model/ModelObject.hpp>
#include <model/ModelObject_Impl.hpp>
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
#include <model/ShadingSurface.hpp>
#include <model/ShadingSurface_Impl.hpp>
#include <model/ShadingSurfaceGroup.hpp>
#include <model/ShadingSurfaceGroup_Impl.hpp>
#include <model/Construction.hpp>
#include <model/Construction_Impl.hpp>
#include <model/MasslessOpaqueMaterial.hpp>
#include <model/MasslessOpaqueMaterial_Impl.hpp>
#include <model/StandardOpaqueMaterial.hpp>
#include <model/StandardOpaqueMaterial_Impl.hpp>
#include <model/SimpleGlazing.hpp>
#include <model/SimpleGlazing_Impl.hpp>
#include <model/FenestrationMaterial.hpp>
#include <model/FenestrationMaterial_Impl.hpp>
#include <model/ModelPartitionMaterial.hpp>
#include <model/ModelPartitionMaterial_Impl.hpp>
#include <utilities/core/Assert.hpp>

#include <utilities/core/Assert.hpp>
#include <utilities/units/UnitFactory.hpp>
#include <utilities/units/QuantityConverter.hpp>

#include <boost/foreach.hpp>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>



namespace openstudio {
namespace ESPR  {



  boost::optional<openstudio::model::Model> ReverseTranslator::ESPRToModel(const openstudio::path& path){
    
    boost::optional<openstudio::model::Model> result;

    if (boost::filesystem::exists(path))
	{

        ReverseTranslator translator;
        result = translator.convert(path);
     }

    return result;
  }

  ReverseTranslator::ReverseTranslator()
  {
  }

  boost::optional<model::Model> ReverseTranslator::convert(const openstudio::path& path)
  {
    return translateESPR(path);
  }

  boost::optional<model::Model> ReverseTranslator::translateESPR(const openstudio::path& path)
  {
    //Hardcode this for now.
	  
	std::wstring test = path.string();
    TBuilding Building(path);

	LOG(Debug,"Create a new Openstudio Model" << std::endl);
    openstudio::model::Model model;
	//Not sure what Fastnaming does. 
    model.setFastNaming(true);

	LOG(Debug,"Creating Default Window and door constructions." << std::endl);
	boost::optional<openstudio::model::Construction> m_windowConstruction;
    boost::optional<openstudio::model::Construction> m_doorConstruction;
		
	//Add some temporary Materials and Constructions for some items that are hard to translate. 


      model::SimpleGlazing windowMaterial(model);
      windowMaterial.setName("Temporary Window Material");
      windowMaterial.setUFactor(2.716);
      windowMaterial.setSolarHeatGainCoefficient(0.7);
      windowMaterial.setVisibleTransmittance(0.8);

      m_windowConstruction = model::Construction(model);
      m_windowConstruction->setName("Temporary Window Construction");
      m_windowConstruction->insertLayer(0, windowMaterial);

      model::StandardOpaqueMaterial doorMaterial(model);
      doorMaterial.setName("Temporary Door Material");
      doorMaterial.setRoughness("MediumSmooth");
      doorMaterial.setThickness(0.025);
      doorMaterial.setThermalConductivity(0.15);
      doorMaterial.setDensity(608);
      doorMaterial.setSpecificHeat(1603);
      doorMaterial.setThermalAbsorptance(0.7);
      doorMaterial.setSolarAbsorptance(0.7);
      doorMaterial.setVisibleAbsorptance(0.7);

      m_doorConstruction = model::Construction(model);
      m_doorConstruction->setName("Temporary Door Construction");
      m_doorConstruction->insertLayer(0, doorMaterial);





    LOG(Debug,"Translating Materials" << std::endl);
	std::vector<TMaterial> Materials = Building.GetMaterials() ;
    BOOST_FOREACH(TMaterial Material, Materials)
	{
      boost::optional<model::ModelObject> material = translateMaterial(Material, model);
      BOOST_ASSERT(material); // Krishnan, what type of error handling do you want?
	  LOG(Debug,"Converted material named " << material->name().get() << std::endl);

    }

    LOG(Debug,"Translating Constructions" << std::endl);
    std::vector<TConstruction> Constructions = Building.GetConstructions();
    BOOST_FOREACH(TConstruction Construction, Constructions)
	{
		boost::optional<model::ModelObject> construction = translateConstruction(Construction, model);
		BOOST_ASSERT(construction); // Krishnan, what type of error handling do you want?
		LOG(Debug,"Converted construction named " << construction->name().get() << std::endl);

    }

    boost::optional<model::ModelObject> facility = translateCampus(Building, model);
    model.setFastNaming(false);
    return model;
  }
  boost::optional<model::ModelObject> ReverseTranslator::translateCampus(TBuilding Building, openstudio::model::Model& model)
  {
    
	//Create New Facility
	openstudio::model::Facility facility = model.getUniqueModelObject<openstudio::model::Facility>();
    //BOOST_ASSERT(facility); 


	//Translate Building, Zones, Spaces and surfaces
	openstudio::model::Building building = model.getUniqueModelObject<openstudio::model::Building>();

    building.setName("ESP-r Model");

    BOOST_FOREACH(TZone Zone, Building.GetZones())
	{
		//Create new OS space and name it. 
		openstudio::model::Space space(model);
        space.setName(Zone.sName);
		//Create Thermal Zone and name it similar to space name. 
		openstudio::model::ThermalZone thermalZone(model);
		thermalZone.setName(Zone.sName + " ThermalZone");
		//Assign the space to the thermal zone. 
        space.setThermalZone(thermalZone);
		//BOOST_ASSERT(space);

		BOOST_FOREACH(TSurface Surface, Zone.SurfaceList)
		{
			translateSurface(Surface, Zone, model);
			//BOOST_ASSERT(surface);
		}



    }

    return building;
    //BOOST_ASSERT(building);
  }





  boost::optional<model::ModelObject> ReverseTranslator::translateSurface(TSurface Surface, TZone Zone, openstudio::model::Model& model)
  {
    boost::optional<model::ModelObject> result;
      
    std::vector<openstudio::Point3d> vertices;
    
	//Dump vertexes here. It will be shoved into the surface object later.
	BOOST_FOREACH( Vertex3D vertex, Surface.vVx)
	{
		vertices.push_back(openstudio::Point3d(vertex.vx,vertex.vy,vertex.vz));
	}

//    std::cout << "surface vertices " << vertices << std::endl;

	std::string surfaceType = Surface.sPosition;
	std::string EnvironmentOtherSide = Surface.sEnvironmentOtherSide;


	  //Create new surface with vetexes and model. 
      openstudio::model::Surface surface(vertices, model);


//      std::cout << toString(surfaceName) << std::endl;
	  surface.setName(Surface.sName);


      if (surfaceType =="VERT"){
        surface.setSurfaceType("Wall"); 
      }else if (surfaceType == "CEIL"){
        surface.setSurfaceType("RoofCeiling"); 
      }else if (surfaceType == "FLOR"){
        surface.setSurfaceType("Floor"); 
      }

      if (EnvironmentOtherSide == "EXTERIOR"){
        surface.setOutsideBoundaryCondition("Outdoors");
        surface.setSunExposure("SunExposed");
        surface.setWindExposure("WindExposed");
      }else if (surfaceType == "BASESIMP"){
        surface.setOutsideBoundaryCondition("Ground");
        surface.setSunExposure("NoSun");
        surface.setWindExposure("NoWind");
      }else{
        surface.setOutsideBoundaryCondition("Surface");
        surface.setSunExposure("NoSun");
        surface.setWindExposure("NoWind");
      }

      result = surface;


        boost::optional<openstudio::WorkspaceObject> workspaceObject = model.getObjectByTypeAndName(IddObjectType::OS_Space, Zone.sName);
        if (workspaceObject && workspaceObject->optionalCast<openstudio::model::Space>()){
          surface.setSpace(workspaceObject->cast<openstudio::model::Space>());
        }
	//Assign Contruction to Surface
		std::string constructionName = Surface.sDBName;
		boost::optional<model::ConstructionBase> construction = workspaceObject->cast<openstudio::model::Space>().model().getModelObjectByName<model::ConstructionBase>(constructionName);
		//BOOST_ASSERT(construction);
		surface.setConstruction(*construction);

	//This needs to be done after all surfaces have been added. 
		if (Surface.sEnvironmentOtherSideObject != "") 
		{
			boost::optional<openstudio::model::Surface> AdjacentSurface = model.getModelObjectByName<model::Surface>(Surface.sEnvironmentOtherSideObject);
			if ( AdjacentSurface ) {
			surface.setAdjacentSurface(*AdjacentSurface);
			//Also add the current surface to the adjacent surface. This may be done more than once since
			//check to see if constructions are the same. 
			AdjacentSurface->setAdjacentSurface(surface);
            AdjacentSurface->setConstruction(*construction);
			cout <<AdjacentSurface << std::endl;
			}
		}

      // translate subSurfaces
		BOOST_FOREACH(TSurface SubSurface, Surface.subSurfaces){
        boost::optional<model::ModelObject> subSurface = translateSubSurface(SubSurface, surface);
		// std::cout << "subSurface vertices " <<subSurface.name().get() << subSurface.vertices << std::endl;
        //BOOST_ASSERT(surface);
      }

	  //might have to deal with other side surface. 

    return result;
  } 
  boost::optional<openstudio::model::ModelObject> ReverseTranslator::translateSubSurface(TSurface SubSurface, openstudio::model::Surface& surface)
  {
    openstudio::model::Model model = surface.model();

    boost::optional<model::ModelObject> result;
      
    std::vector<openstudio::Point3d> vertices;

	BOOST_FOREACH( Vertex3D vertex, SubSurface.vVx)
	{
		vertices.push_back(openstudio::Point3d(vertex.vx,vertex.vy,vertex.vz));
	}

    //std::cout << "subSurface vertices " << vertices << std::endl;

    openstudio::model::SubSurface subSurface(vertices, model);
    //Assign Contruction to Surface
	std::string constructionName = SubSurface.sDBName;
	if (SubSurface.sGeoType == "TRAN" )
	{
		constructionName = "Temporary Window Construction";
	}
	boost::optional<model::ConstructionBase> construction = model.getModelObjectByName<model::ConstructionBase>(constructionName);
	//BOOST_ASSERT(construction);
	subSurface.setConstruction(*construction);
    subSurface.setSurface(surface);
    subSurface.setName(SubSurface.sName);

    return subSurface;
  }


  boost::optional<openstudio::model::ModelObject> ReverseTranslator::translateConstruction(TConstruction EConstruction, openstudio::model::Model& model)
    {

		


        // Krishnan, this constructor should only be used for unique objects like Building and Site
        //openstudio::model::Construction construction = model.getUniqueModelObject<openstudio::model::Construction>();

		//Create new contruction.
        openstudio::model::Construction construction(model);
		//Set Name of Construction. Should be unique.
        construction.setName(EConstruction.sName);
        std::vector<openstudio::model::Material> materials;
		//Get materials in the ESPR  Construction
		BOOST_FOREACH ( std::string MaterialName, EConstruction.MaterialListName)
		{
			//Get Materials as previously stored in the translateMaterial method. 
			  boost::optional<openstudio::model::Material> material = model.getModelObjectByName<openstudio::model::Material>(MaterialName);
              BOOST_ASSERT(material); // Krishnan, what type of error handling do you want?
              materials.push_back(*material);
		}
        
        // now assign all layers to real material, does ESPR have same layer order convention as E+?
        for (unsigned i = 0; i < materials.size(); ++i){
          bool test = false;
          if (materials[i].optionalCast<openstudio::model::OpaqueMaterial>()){
            test = construction.insertLayer(i, materials[i].cast<openstudio::model::OpaqueMaterial>());
          }else if (materials[i].optionalCast<openstudio::model::FenestrationMaterial>()){
            test = construction.insertLayer(i, materials[i].cast<openstudio::model::FenestrationMaterial>());
          }else if (materials[i].optionalCast<openstudio::model::ModelPartitionMaterial>()){
            test = construction.setLayer(materials[i].cast<openstudio::model::ModelPartitionMaterial>());
          }
          
          BOOST_ASSERT(test); // Krishnan, what type of error handling do you want?
        }

        return construction;
    }

  boost::optional<openstudio::model::ModelObject> ReverseTranslator::translateMaterial(TMaterial Material, openstudio::model::Model& model)
    {






        double rvalue= Material.dAirGapResistance;
        // Check if this is an air gap. 
        if (rvalue  > 0.0)  //Material no mass that has only R-value
        {
            // Krishnan, this constructor should only be used for unique objects like Building and Site
            //openstudio::model::MasslessOpaqueMaterial material = model.getUniqueModelObject<openstudio::model::MasslessOpaqueMaterial>();

            // the idd specifies a minimum value of .001 for rvalue
            rvalue = std::max(rvalue, .001);


            openstudio::model::MasslessOpaqueMaterial material(model);
            material.setThermalResistance(rvalue);            
			material.setRoughness("MediumRough");
            material.setName(Material.sName);
            return material;
        }

        else
        {
            // Krishnan, this constructor should only be used for unique objects like Building and Site
            //openstudio::model::StandardOpaqueMaterial material = model.getUniqueModelObject<openstudio::model::StandardOpaqueMaterial>();

            openstudio::model::StandardOpaqueMaterial material(model);

			
            double density = Material.dDensity;
            double conductivity = Material.dConductivity;
            double thickness = Material.dThickness;
            double specificHeat = Material.dSpecificHeat;

            material.setDensity(density);
            material.setThermalConductivity(conductivity);
            material.setThickness(thickness);
            material.setSpecificHeat(specificHeat);
			//Hardocded since ESPr does not have roughness. 
            material.setRoughness("MediumRough");

            
            material.setName(Material.sName);
            return material;
        }

        return boost::none;
    }


} // ESPR
} // openstudio
