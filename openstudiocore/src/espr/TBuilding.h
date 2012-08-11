#pragma once
//#include "TZone.h" 
#include <vector>
#include <string> 
#include <boost/filesystem.hpp> 

//OpenSutdio definition for paths. 
#include <utilities/core/Path.hpp>

class TZone;
class TMaterial;
class TConstruction;
class TBuilding
{
private:
	std::string sName;
	std::vector<TZone> ZoneList;
	std::vector<TMaterial> MaterialList;
	std::vector<TConstruction> ConstructionList;
	/*
	std::vector<TDaySchedule> DaySchedules;
    std::vector<TWeekSchedule> WeekSchedules;
    */

public:
	TBuilding(void);
	TBuilding(const openstudio::path& CFGFile);
	~TBuilding(void);
	void TBuilding::ReadCFGFile( const openstudio::path& sCFGFile );

	//Zonal Files. 
	std::vector<openstudio::path> GEOFiles;
	std::vector<openstudio::path> CONFiles;
	std::vector<openstudio::path> OPRFiles;
	std::vector<openstudio::path> TMCFiles;
	

	//Unique Files. 
    openstudio::path CFGFilePath;
	openstudio::path HVACFilePath;
	openstudio::path DHWFilePath;
	openstudio::path AIMFilePath;
	openstudio::path BCDFilePath;
	openstudio::path CTLFilePath;


	//FOlder of CFG file. 
	openstudio::path CFGFolderpath;

	std::vector<TMaterial> TBuilding::GetMaterials();
	TMaterial AddMaterial( TMaterial material );
	std::vector<TMaterial> AddMaterial(std::vector<TMaterial> materials);
	
	std::vector<TConstruction> TBuilding::GetConstructions();
	TConstruction AddConstruction(TConstruction construction); 
	std::vector<TConstruction> AddConstruction(std::vector<TConstruction> constructions);
    /*
	std::vector<TDaySchedule> TBuilding::GetDaySchedules();
	TDaySchedule AddDaySchedule(TDaySchedule DaySchedule);

	std::vector<TWeekSchedule> TBuilding::TWeekSchedules();
	TWeekSchedule AddWeekSchedule(TWeekSchedule WeekSchedule);
    */
	std::vector<TZone> TBuilding::GetZones();
	TZone AddZone(TZone Zone);
	void ReadCONFile(const openstudio::path& CONPath, TZone& zone);
	void ReadTMCFile(const openstudio::path& TMCPath, TZone& zone);

};
