//---------------------------------------------------------------------------

#ifndef TSURFACEH
#define TSURFACEH

/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *           
 *                                                                 *
 ***************************************************************************/
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "Espr3d.h"
#include "TZone.h"
#include "TSurface.h"
#include "TConstruction.h"
#include "TGlazing.h"



/**
 * This class contains all information required for a surface in ESP-r.
 */
class TSurface : public Surface3D
{
private:

	

public:

	std::vector<TSurface> subSurfaces;


	  /**
     * List of the vertex index. 
     */
    std::vector<int> VertexIndexList;


    /**
     *  The unique name of the surface.
     */
    int idNumber;

    /**
     * The unique name of the surface. 
     */
    std::string sName;

    /**
     * The Geometry Type Current valid values are 'OPAQ'
     */
    std::string sGeoType;

    /**
     *The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
     */
    std::string sPosition;

    /**
     *The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
     */
    std::string sDBName;



    /**
     * The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
     */
    std::string sEnvironmentOtherSide;


	std::string sEnvironmentOtherSideObject;


    /**
     * Indentation of the surface in Metres.
     */ 
    double dSurfaceIndentation;



    /**
     * The method to add a surface.
     */
    void AddSurfaceInSurface();

    /**
     * The vector which contains all the vertexes present in the surface, stored in anti-clockwise order.
     */
   // std::vector <Vertex3D> vVx;



    TConstruction Construction;


bool TSurface::operator == (const TSurface & V ) const	
{
	if (vVx == V.vVx) 
	{return true;}
	else
	{return false;}
}

bool TSurface::operator != (const TSurface & V ) const	
{
	if (vVx != V.vVx) 
	{return true;}
	else
	{return false;}
}


    /**
     * Default Constructor of the TSurface Object.
     *
     */
    TSurface(){

        dSurfaceIndentation = 0.0;
        idNumber = 0;
    };

	TSurface & operator= (const TSurface & other)
	{
	if (this != &other) // protect against invalid self-assignment

	{
		Construction = other.Construction;
		dSurfaceIndentation = other.dSurfaceIndentation;
		idNumber = other.idNumber;
		sEnvironmentOtherSide = other.sEnvironmentOtherSide;
		sGeoType = other.sGeoType;
		sName = other.sName;
		sPosition = other.sPosition;
		VertexIndexList = other.VertexIndexList;
		vVx = other.vVx;
	}
	return *this;

	}

    /**
     * Constructor of the TSurface Object. 
     * @param sNameIn  The unique name of the surface. 
     * @param VertexListIn The vector which contains all the vertexes present in the surface, stored in anti-clockwise order. 
     * @param sGeoTypeIn The Geometry Type Current valid values are 'OPAQ'
     * @param sPositionIn The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
     * @param sContructionIn The Construction Type. This is a dummy value since the real construction is set in the .con file. It may be useful for debugging database problems. Values include 'extern_wall' 'inter_wall' 'ceiling' susp_floor'.
     * @param sEnvironmentOtherSideIn The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
     * @param dSurfaceIndentationIn This is the value that the surface in indented by. This is useful for sunken windows. 
     */
    TSurface(std::string sNameIn,
             std::vector <Vertex3D> VertexListIn,
             std::string sGeoTypeIn,
             std::string sPositionIn,
             std::string sEnvironmentOtherSideIn,
             double dSurfaceIndentationIn)
    {

        sName = sNameIn;
        vVx = VertexListIn;
        sGeoType = sGeoTypeIn;
        sPosition = sPositionIn;
        sEnvironmentOtherSide = sEnvironmentOtherSideIn;
        dSurfaceIndentation =   dSurfaceIndentationIn;
    }

    TSurface(std::string sNameIn,
             std::vector <Vertex3D> VertexListIn,
             TConstruction& ConstructionIn,
             std::string sGeoTypeIn,
             std::string sPositionIn,
             std::string sEnvironmentOtherSideIn,
             double dSurfaceIndentationIn)
    {

        sName = sNameIn;
        vVx = VertexListIn;
        sGeoType = sGeoTypeIn;
        sPosition = sPositionIn;
        sEnvironmentOtherSide = sEnvironmentOtherSideIn;
        Construction = ConstructionIn;
        dSurfaceIndentation =   dSurfaceIndentationIn;
    }



    /**
     * 
     * @param sNameIn The unique name of the surface.
     * @param VertexIndex The vertex index. 
     * @param VertexIndexListIn The list of vertexes used in the surface. 
     * @param sGeoTypeIn  The Geometry Type Current valid values are 'OPAQ'
     * @param sPositionIn The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
     * @param sContructionIn The Construction Type. This is a dummy value since the real construction is set in the .con file. It may be useful for debugging database problems. Values include 'extern_wall' 'inter_wall' 'ceiling' susp_floor'.
     * @param sEnvironmentOtherSideIn The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
     * @param dSurfaceIndentationIn This is the value that the surface in indented by. This is useful for sunken windows. 
     * @return None.
     */
    TSurface(std::string sNameIn,
             std::vector< Vertex3D > VertexIndex,
             std::vector<int> VertexIndexListIn,
             TConstruction& ConstructionIn,
             std::string sGeoTypeIn,
             std::string sPositionIn,
             std::string sEnvironmentOtherSideIn,
             double dSurfaceIndentationIn)
    {
        // Assign passed values to object's members.
        sName = sNameIn;
        VertexIndexList = VertexIndexListIn;
        sGeoType = sGeoTypeIn;
        sPosition = sPositionIn;
        dSurfaceIndentation =   dSurfaceIndentationIn;
        sEnvironmentOtherSide = sEnvironmentOtherSideIn;
        Construction = ConstructionIn;
        
        vVx.clear();

        //Loop through surface vertex index list.
        for ( std::vector<int>::iterator iterVertexIndexList = VertexIndexList.begin();
                iterVertexIndexList !=  VertexIndexList.end();
                iterVertexIndexList++ )
        {
            // This adds the vertex to the vertex list as defined in the Vertex index.Note the index start at 1 by default
            vVx.push_back( VertexIndex[ *iterVertexIndexList - 1 ] );
        }
        //Empty the vertex index list..This should be configured with the TZone object only.
        VertexIndexList.clear();
    }

    //    /**
    //     *
    //     * @param sNameIn The unique name of the surface.
    //     * @param VertexIndex The vertex index.
    //     * @param VertexIndexListIn The list of vertexes used in the surface.
    //     * @param sGeoTypeIn  The Geometry Type Current valid values are 'OPAQ'
    //     * @param sPositionIn The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
    //     * @param sContructionIn The Construction Type. This is a dummy value since the real construction is set in the .con file. It may be useful for debugging database problems. Values include 'extern_wall' 'inter_wall' 'ceiling' susp_floor'.
    //     * @param sEnvironmentOtherSideIn The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
    //     * @param dSurfaceIndentationIn This is the value that the surface in indented by. This is useful for sunken windows.
    //     * @return None.
    //     */
    //    TSurface(std::string sNameIn,
    //             std::vector< TVertex > VertexIndex,
    //             std::vector<int> VertexIndexListIn,
    //             TConstruction ConstructionIn,
    //             std::string sGeoTypeIn,
    //             std::string sPositionIn,
    //             std::string sEnvironmentOtherSideIn,
    //             double dSurfaceIndentationIn)
    //    {
    //        // Assign passed values to object's members.
    //        sName = sNameIn;
    //        VertexIndexList = VertexIndexListIn;
    //        sGeoType = sGeoTypeIn;
    //        sPosition = sPositionIn;
    //        sEnvironmentOtherSide = sEnvironmentOtherSideIn;
    //        Construction = ConstructionIn;
    //        VertexList.clear();
    //
    //        //Loop through surface vertex index list.
    //        for ( std::vector<int>::iterator iterVertexIndexList = VertexIndexList.begin();
    //                iterVertexIndexList !=  VertexIndexList.end();
    //                iterVertexIndexList++ )
    //        {
    //            // This adds the vertex to the vertex list as defined in the Vertex index.Note the index start at 1 by default
    //            VertexList.push_back( VertexIndex[ *iterVertexIndexList - 1 ] );
    //        }
    //        //Empty the vertex index list..This should be configured with the TZone object only.
    //        VertexIndexList.clear();
    //    }

    std::string StreamOut()
    {
        std::stringstream sOutput;
        sOutput << "int idNumber " <<  idNumber << std::endl;

        /**
         * The unique name of the surface. 
         */
        sOutput << "sName " <<  sName << std::endl;


        /**
         * The Geometry Type Current valid values are 'OPAQ'
         */
        sOutput << "sGeoType " << sGeoType << std::endl;

        /**
         *The Position. Current valid values are 'CEIL' 'FLOOR' 'VERT'
         */
        sOutput << "sPosition " << sPosition << std::endl;


        /**
         * The condition on the outside of this wall with respect to the zone. Valid values include 'EXTERIOR' 'INTERIOR' 'ADIABATIC'
         */
        sOutput << "sEnvironmentOtherSide " << sEnvironmentOtherSide << std::endl;

        /**
         * Indentation of the surface in Metres.
         */ 
        sOutput << "dSurfaceIndentation " <<dSurfaceIndentation << std::endl;


        /**
         * List of the vertex index. 
         */
        sOutput << " VertexIndexList" <<StreamOutVector(VertexIndexList) << std::endl;

        /**
         * The vector which contains all the vertexes present in the surface, stored in anti-clockwise order.
         */
        sOutput << " VertexIndexList" << std::endl <<StreamOutVector(VertexIndexList) << std::endl;
        sOutput << "Construction "<< std::endl << Construction.StreamOut()<< std::endl;

        return sOutput.str();
    }

void SetConstruction(TConstruction ConstructionIn)
{
  Construction = ConstructionIn;
}










};
//---------------------------------------------------------------------------
#endif
