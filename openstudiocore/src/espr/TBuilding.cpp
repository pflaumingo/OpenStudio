
#include "StdAfx.h"
#include <vector>
#include <string> 
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/lexical_cast.hpp>
#include <utilities/core/Logger.hpp>
#include "TBuilding.h"
#include "TZone.h"
#include "TConstruction.h"
#include "TMaterial.h"
#include "TFileUtilities.h"
#include "Regexp.h"

TBuilding::TBuilding(void)
{
}

TBuilding::~TBuilding(void)
{
}


TBuilding::TBuilding(const openstudio::path& sCFGFile)
{
		ReadCFGFile( sCFGFile );

}

std::vector<TMaterial> TBuilding::GetMaterials()
{

return MaterialList ;
}

std::vector<TConstruction> TBuilding::GetConstructions()
{

return ConstructionList ;
}


std::vector<TZone> TBuilding::GetZones()
{
	return ZoneList;
}
void TBuilding::ReadCFGFile(const openstudio::path& sCFGFile )
{
	    

	CFGFilePath=sCFGFile;
	boost::filesystem::wpath CFGFolderPath= CFGFilePath;
	CFGFolderPath.remove_filename();



	if (boost::filesystem::exists(CFGFilePath))
	{

	//Let us parse the cfg file and get the *geo files.
		std::vector<string> vsCFGFile = read_file_into_vector(sCFGFile);
		BOOST_FOREACH(string line, vsCFGFile) 
		{
			
			string TmcSearch= "^\\s*\\*geo\\s+(.*\\.tmc)\\s*(.*)";
			std::vector<string> Matches = RegexpMatch(TmcSearch, line);
			if (Matches.size() == 2)
			{
				openstudio::path FullPath = CFGFolderPath / openstudio::toPath(Matches[0]);
				TMCFiles.push_back(FullPath);
				//LOG(Debug,"Found *geo file :" << std::endl);
			}

			string GeoSearch= "^\\s*\\*geo\\s+(.*\\.geo)\\s*(.*)";
			Matches = RegexpMatch(GeoSearch, line);
			if (Matches.size() == 2)
			{
				openstudio::path FullPath = CFGFolderPath / openstudio::toPath(Matches[0]);
				GEOFiles.push_back(FullPath);
			}

			string CONSearch= "^\\s*\\*con\\s+(.*\\.con)\\s*(.*)";
			 Matches = RegexpMatch(CONSearch, line);
			if (Matches.size() == 2)
			{
				const openstudio::path FullPath = CFGFolderPath / openstudio::toPath(Matches[0]);
				CONFiles.push_back(FullPath);
			}

			string OPRSearch= "^\\s*\\*opr\\s+(.*\\.opr)\\s*(.*)";
			Matches = RegexpMatch(OPRSearch, line);
			if (Matches.size() == 2)
			{
				const openstudio::path FullPath = CFGFolderPath / openstudio::toPath(Matches[0]);
				OPRFiles.push_back(FullPath);
			}
		}

		//Determine Number of zones
		int iNumofZones = GEOFiles.size();
		int iZone;
		for (iZone = 0; iZone <iNumofZones; iZone++)
		{
			TZone Zone;
			Zone.LoadGeoFile(GEOFiles[iZone]);
			ReadCONFile(CONFiles[iZone], Zone);
			//ReadTMCFile(TMCFiles[iZone], Zone);

			Zone.RemoveHoles();
			Zone.FindParentSurfaces();
			ZoneList.push_back(Zone);
		}
		//Find Interzonal Surfaces and match the surfaces.  

		BOOST_FOREACH(TZone &ZoneOuter, ZoneList)
		{
			BOOST_FOREACH(TSurface &surfaceOuter, ZoneOuter.SurfaceList) 
			{
				//Check same zones. There should not be a reverse match. 
				BOOST_FOREACH(TZone &ZoneInner, ZoneList)
				{
					BOOST_FOREACH(TSurface &surfaceInner, ZoneInner.SurfaceList) 
					{
						//Check to see if same number of Vertexes
						//std::cout<<"Check Mirror\n";

							if (surfaceOuter.bMirror(surfaceInner))
							{
							//Assign the other side environment to the internal matching surface name.
							surfaceOuter.sEnvironmentOtherSideObject = surfaceInner.sName;
							
							}


					}
					
	
				}

			}
		}
	}
	else
	{
		std::cerr << "This file does not exist: " << openstudio::toString(CFGFilePath);
	}

}


void TBuilding::ReadCONFile(const openstudio::path& CONPath, TZone& zone)
{
	int iCurrentStartPoint = 0;
	struct Data
	{
		int iNumOfLayers;
		int iNumOfAirGaps;
		int iStartingPoint;
	};

	struct GapData
	{
		int iGapPosition;
		double dResistance;
	};


	std::vector<Data> LayerData;
	std::vector<GapData> AirGapData;
	int TotalNumberOfAirGaps = 0;
	int TotalNumberOfMaterials = 0;
	int StartSectionIndex = 0; 
	int EndSectionIndex   = zone.SurfaceList.size(); 
	if (boost::filesystem::exists(CONPath))
	{

	    std::vector<string> Matches;
		std::vector<string> CONFile = read_file_into_vector_strip_comments(CONPath);
		//Grab first part of con file. 
		for (int icounter = StartSectionIndex ;icounter < EndSectionIndex ; icounter++)
		{

		    string LayerSearch= "^\\s*(\\d*)\\s*,\\s*(\\d*)(\\s*.*)?";
			Matches = RegexpMatch(LayerSearch, CONFile[icounter]);
			if (Matches.size() > 1)
			{
				Data data;
				data.iNumOfLayers  = boost::lexical_cast<int>(Matches[0]);
				data.iNumOfAirGaps = boost::lexical_cast<int>(Matches[1]);
				TotalNumberOfAirGaps += data.iNumOfAirGaps;
				TotalNumberOfMaterials += data.iNumOfLayers;
				if ( data.iNumOfAirGaps > 0 )
				{
					data.iStartingPoint = iCurrentStartPoint;
					iCurrentStartPoint += data.iNumOfAirGaps;

				}
				LayerData.push_back(data);
			}

		}
		//Get Air gap data section.
	    StartSectionIndex = zone.SurfaceList.size(); 
	    EndSectionIndex   = zone.SurfaceList.size() + TotalNumberOfAirGaps; 
		for (int icounter = StartSectionIndex ;icounter < EndSectionIndex ; icounter++)
		{

		    string LayerSearch= "^\\s*(\\d*)\\s*,\\s*(\\d*\\.\\d*)(\\s*.*)?";
			Matches = RegexpMatch(LayerSearch, CONFile[icounter]);
			if (Matches.size() > 1)
			{
				GapData data;
				data.iGapPosition  = boost::lexical_cast<int>(Matches[0]);
				data.dResistance = boost::lexical_cast<double>(Matches[1]);
				AirGapData.push_back(data);
			}
		}

		//Get Emissivity and solar Abs values.

		std::vector<double> InsideEmissivityList = SplitToDouble(CONFile[zone.SurfaceList.size() + TotalNumberOfAirGaps + TotalNumberOfMaterials]," ");
		std::vector<double> OutsideEmissivityList = SplitToDouble(CONFile[zone.SurfaceList.size() + TotalNumberOfAirGaps + TotalNumberOfMaterials+1]," ");
		std::vector<double> InsideSolarAbsList = SplitToDouble(CONFile[zone.SurfaceList.size() + TotalNumberOfAirGaps + TotalNumberOfMaterials+2]," ");
        std::vector<double> OutsideSolarAbsList = SplitToDouble(CONFile[zone.SurfaceList.size() + TotalNumberOfAirGaps + TotalNumberOfMaterials+3]," ");



		//Detemine start of Materials list. 
		int iLineNumber = AirGapData.size() + zone.SurfaceList.size();
		//Create Constructions for each surface in Zone. 
		for (unsigned int iCurrentConstruction = 0 ;iCurrentConstruction < zone.SurfaceList.size() ; iCurrentConstruction++)
		{
			//New Construction
			TConstruction construction;
			//Assign name has branded in goe file. 
			construction.sName = zone.SurfaceList[iCurrentConstruction].sDBName;
			//Loop through each layer. 
			for (int iCurrentMaterial = 0; iCurrentMaterial < LayerData[iCurrentConstruction].iNumOfLayers ; iCurrentMaterial++ ) 
			{

				//Create new material.
				TMaterial material;
				//Set default values for below. Only inside and outside material layer data is known. 
				double dEmissivity= 0.;
				double dSolarAbsorptivity= 0.;

				//If this is the first layer (outside) add a few items
				if ( iCurrentMaterial == 0 ) 
				{
				dEmissivity = OutsideEmissivityList[iCurrentConstruction];
				dSolarAbsorptivity= OutsideSolarAbsList[iCurrentConstruction];
				}

			    //If this is the first layer (inside) add a few items
				if ( iCurrentMaterial == LayerData[iCurrentConstruction].iNumOfLayers - 1) 
				{
				dEmissivity= InsideEmissivityList[iCurrentConstruction];
				dSolarAbsorptivity= InsideSolarAbsList[iCurrentConstruction];
				}

				//Check if there is an airgap
				double dAirGapResistance = 0.;
				if (LayerData[iCurrentConstruction].iNumOfAirGaps > 0)
				{
					// Check if this layer should be a gap. 
					for (int airgapindex = LayerData[iCurrentConstruction].iStartingPoint ; airgapindex  < (LayerData[iCurrentConstruction].iStartingPoint + LayerData[iCurrentConstruction].iNumOfAirGaps); airgapindex++)
					{

						//If this is an air gap set the resistance. 
						if (AirGapData[airgapindex].iGapPosition = iCurrentMaterial+1 )
						{
							dAirGapResistance = AirGapData[airgapindex].dResistance;
						}
					}
				}

				
				std::string MaterialData = "^\\s*(\\d*.\\d*)\\s*,\\s*(\\d*\\.\\d*),\\s*(\\d*\\.\\d*),\\s*(\\d*\\.\\d*),\\s*(\\d*),\\s*(\\d*\\.\\d*),\\s*(\\d*\\.\\d*),\\s*(\\d*\\.\\d*)\\s*(.*)?";
				Matches = RegexpMatch(MaterialData, CONFile[iLineNumber]);
				material.Set(
					("espr-mat-" + boost::lexical_cast<std::string>( MaterialList.size())),
					boost::lexical_cast<double>(Matches[0]), //conductivity. 
					boost::lexical_cast<double>(Matches[1]), //density
					boost::lexical_cast<double>(Matches[2]), //spec heat
					boost::lexical_cast<double>(Matches[3]), //thickness
					boost::lexical_cast<int>(Matches[4]),	//dpnd type
					boost::lexical_cast<double>(Matches[5]), // Ref temp
					boost::lexical_cast<double>(Matches[6]), // Temp_factorIn,
					boost::lexical_cast<double>(Matches[7]),	// dMoisture_factorIn,
					(dAirGapResistance >0.0),				//IsAirGap
					dAirGapResistance,						//dAirGapResistanceIn,
					dEmissivity,						//dInside_EmissivityIn,
					dSolarAbsorptivity);			//dSolarAbsorptivityIn

				TMaterial NewMaterial = AddMaterial(material);
				construction.MaterialListName.push_back(NewMaterial.sName);
				iLineNumber++;
			}

			//Adds construction to the list. and ensures that there are no duplication. 
			zone.SurfaceList[iCurrentConstruction].sDBName =    AddConstruction(construction).sName;	
		}
	}

}

void TBuilding::ReadTMCFile(const openstudio::path& TMCPath, TZone& zone)
{

	//Since we alreacy know the number of surfaces in this zone. We can skip the first line. 
	//We should iterate thought all the surface. Determine if the surface is a glazing and then read the extra optical data into the surface. 
	// The interesting thing is that the optical charectistics are independant of the construction and materials. Why why why...?
    // So should this be a part of the material?


	
	std::vector<string> TMCFile = read_file_into_vector_strip_comments(TMCPath);
	int iLineCounter = 3;
	//Loop through Surfaces
	
	//start at iLineCounter. 
	//Get numoflayers and Surface name. 
	//Read in Tranmission into Construction.
	//Read in Layer data to Materials. 
	//Read in Blind Control Flag. Ensure that it is zero. If not flag user to remove blind control data and stop.  
	//Increment start point by 2 + Numof Surfaces. 

	string Layer= "^\\s*(\\d*)\\s*(\\S*)(\\s*.*)?";
	std::vector<string> Matches = RegexpMatch(Layer, TMCFile[iLineCounter]);



	int StartSectionIndex = 3; 
	int EndSectionIndex   = zone.SurfaceList.size(); 
	if (boost::filesystem::exists(TMCPath))
	{
		for (int icounter = StartSectionIndex ;icounter < EndSectionIndex ; icounter++)
		{

			
		}


	}
}






TMaterial TBuilding::AddMaterial(TMaterial Material) 
{
	
	BOOST_FOREACH(TMaterial storedMaterial, MaterialList)
	{

		if (storedMaterial == Material)
		{
			return storedMaterial;
			break;
		}
	
	}
	MaterialList.push_back(Material);
	return Material;

}

TConstruction TBuilding::AddConstruction(TConstruction Construction) 
{	
	//Ensure the name is unique
	BOOST_FOREACH(TConstruction storedConstruction, ConstructionList)
	{
		if ( storedConstruction.sName == Construction.sName) 
		{

				Construction.sName = "const-"+boost::lexical_cast<std::string>(ConstructionList.size());
		}

	}
	

	BOOST_FOREACH(TConstruction storedConstruction, ConstructionList)
	{

		if (storedConstruction == Construction)
		{
			return storedConstruction;
			break;
		}
	
	}
	ConstructionList.push_back(Construction);
	return Construction;

}