/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *           
 *                                                                 *
 ***************************************************************************/
#ifndef TZONEH
#define TZONEH

#include <vector>
#include <string> 
#include <boost/filesystem.hpp> 
//Openstudio File additions. 
#include <utilities/core/Path.hpp>


#include "Espr3d.h"
#include "TSurface.h"

class TEdge
{
 public:
  bool bMatched;
  int Index1; 
  int Index2;
  std::string SurfaceName;
  std::string  MatchedSurfaceName;

};


/**
 * This class contains all information required for a Zone in ESP-r. This includes vertex and surface management routines. 
 */

class TZone
{

public:
    /**
     * Zone name
     **/
    std::string sName;

    std::vector<std::vector<int>> SurfaceEdgeLists;
	std::vector<std::vector<std::string>> SurfaceAtributes;  


    /**
     * This is the list of all the vertexes in the geometry system.
     */
	int iNumOfVertexes;
    int iNumOfSurfaces;
	float fRotation;



    std::vector<Vertex3D> GlobalVertexList;
    /**
     * This is the list of all surfaces in the zone.
     */ 
    std::vector<TSurface> SurfaceList;



    /**
     * This function will add a surface to the model.
     * @param sNameIn  The unique name of the surface. 
     * @param VertexListIn The vector which contains all the vertexes present in the surface, stored in anti-clockwise order. 
     * @param sGeoTypeIn The Zone Type Current valid values are 'OPAQ'
     * @param sPositionIn The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
     * @param sContructionIn The Construction Type. This is a dummy value since the real construction is set in the .con file. It may be useful for debugging database problems. Values include 'extern_wall' 'inter_wall' 'ceiling' susp_floor'.
     * @param sEnvironmentOtherSideIn The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
     * @param dSurfaceIndentationIn This is the value that the surface in indented by. This is useful for sunken windows. 
     */
    void AddNewSurface( std::string sNameIn,
                        std::vector <Vertex3D> VertexListIn,
                        std::string sGeoTypeIn,
                        std::string sPositionIn,
                        std::string sEnvironmentOtherSideIn,
                        double dSurfaceIndentationIn);

    void AddNewSurface( std::string sNameIn,
                        std::vector <Vertex3D> VertexListIn,
                        TConstruction& Construction,
                        std::string sGeoTypeIn,
                        std::string sPositionIn,
                        std::string sEnvironmentOtherSideIn,
                        double dSurfaceIndentationIn);


    /**
     * This function will take a vector of TSurface with the TSurface::VertexList for each surface already defined. The TZone::GlobalVertexList will be created dynamically as will the each TSurface::VertexIndexList.  
     * @param sNameIn The unique name of the surface. 
     * @param VertexIndex The temporary list of vertexes available.
     * @param VertexIndexListIn The index of vertexes the surface contains w.r.t. VertexIndex.
     * @param sGeoTypeIn The Zone Type Current valid values are 'OPAQ'
     * @param sPositionIn The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
     * @param sContructionIn The Construction Type. This is a dummy value since the real construction is set in the .con file.
     * @param sEnvironmentOtherSideIn The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
     * @param dSurfaceIndentationIn This is the value that the surface in indented by. This is useful for sunken windows.
     */
    void AddNewSurface(
        std::string sNameIn,
        std::vector< Vertex3D > VertexIndex,
        std::vector<int> VertexIndexListIn,
        TConstruction& Construction,
        std::string sGeoTypeIn,
        std::string sPositionIn,
        std::string sEnvironmentOtherSideIn,
        double dSurfaceIndentationIn);

    /**
     * This Function will refresh the Global vertex list as well as the index number for each vertex in each surface. This method should be called anytime geometry has been changed. 
     */
    void RefreshVertexesAndIndexes();




    /**
     * This method will transform the geometry on a rotation, and scale the width Depth and height of the zone.
     * @param dAngle The rotation in degrees.
     * @param dWidth The X component scale factor.
     * @param dDepth The Y component scale factor.
     * @param dHeight The Z component scale factor.
     */
    void  RotateAndScale(
        double dAngle,
        double dWidth,
        double dDepth,
        double dHeight);

    void  Rotate(double dAngle);

    void  Scale( double dWidth,
			  double dDepth,
			  double dHeight);

    /**
     * This function returns the number of surfaces in the zone. 
     * @param Zone The TZone object.
     * @return 
     */
    int Get_Number_Of_Surfaces();

    /**
     * This funtion returns the number of vertexes in the TZone object.
     * @param Zone The TZone Object. 
     * @return 
     */
    int Get_Number_Of_Vertexes();

    TSurface* GetSurface(std::string sSearchSurfaceName);

    std::string StreamOut()
    {
        std::stringstream sOutput;
        sOutput << "****Zone Object****" << std::endl;
        sOutput <<  "sName " <<  sName << std::endl;
        //       sOutput <<"GlobalVertexList "<< StreamOutVector(GlobalVertexList) << std::endl;
        for (
            std::vector<TSurface>::iterator counter = SurfaceList.begin();
            counter != SurfaceList.end();
            counter++)

        {
            sOutput <<  "****Surface*****" <<  std::endl;
            sOutput << counter->StreamOut()<<  std::endl;
        }
        return sOutput.str();
    };

    std::vector<TEdge> GetEdgeList();
    bool CheckEnclosure();
	void LoadGeoFile(const openstudio::path&  GEOFile);
	void ReadNumberOfZoneVertexesSurfacesAndRotation(const openstudio::path& GEOPath);
	std::vector<Vertex3D> ReadZoneVertexes(const openstudio::path&  GEOPath);
	void ReadSurfaceEdgeLists(const openstudio::path&  GEOPath);
	std::string ReadZoneName(const openstudio::path&  GEOPath);
	void ReadSurfaceAttributes(const openstudio::path&  GEOPath);
	void ReadSurfaceIndentation(const openstudio::path&  GEOPath);

    void LoadConFile(const openstudio::path&  CONFile);
	void ReadDBNamesAirGapsAndLayers(const openstudio::path&  CONPath);
	void ReadAirGaps(const openstudio::path&  CONPath);
	void ReadMaterialLayers(const openstudio::path&  CONPath);
	void ReadEmissivity(const openstudio::path&  CONPath);
	void ReadSolarAbsortivity(const openstudio::path&  CONPath);


	void RemoveHoles();
	void FindParentSurfaces();



};

#endif
