/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <boost/format.hpp> 
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include "TESPR.h"
#include "TZone.h"
#include "TSurface.h"





std::string StringifyVertexList(std::vector<Vertex3D> TempVertexList)
{

    std::string sTemp;
    std::vector<Vertex3D>::iterator vertex;
    int iVertNumber = 0;
	BOOST_FOREACH(Vertex3D vertex, TempVertexList)
    {
        iVertNumber++;
        char buffer[200];
        sprintf_s(buffer,"      %10.6f     %10.6f     %10.6f  # vert   %d",vertex.vx, vertex.vy,vertex.vz,iVertNumber);

        sTemp = sTemp + std::string(buffer);

    }
    sTemp = sTemp + std::string("\n");
    return sTemp;
}



std::string GetESPRVertexList(TZone& Zone)
{

    std::string sTemp;
    int iVertNumber = 0;

	BOOST_FOREACH(Vertex3D vertex, Zone.GlobalVertexList)
    {
        iVertNumber++;
        char buffer[200];
        sprintf_s(buffer,"      %10.6f     %10.6f     %10.6f  # vert   %d",vertex.vx, vertex.vy,vertex.vz,iVertNumber);

        sTemp = sTemp + std::string(buffer);

    }
    sTemp = sTemp + std::string("\n");
    return sTemp;
}


std::string GetESPRSurfaceVertexList(TZone& Zone)
{
    std::string sTemp ="";
    std::vector<TSurface>::iterator iterSurface;

	
    for (iterSurface = Zone.SurfaceList.begin();
            iterSurface != Zone.SurfaceList.end();
            iterSurface++)
    {
        char buffer[6];
        sprintf_s(buffer,"  %d,",iterSurface->VertexIndexList.size());
        sTemp = sTemp + std::string(buffer);

        std::vector<int>::const_iterator iterVertexIndexList = iterSurface->VertexIndexList.begin();
        if (iterVertexIndexList != iterSurface->VertexIndexList.end()){};
        for (iterVertexIndexList  = iterSurface->VertexIndexList.begin();
                iterVertexIndexList != iterSurface->VertexIndexList.end();
                iterVertexIndexList++)
        {


            char buffer[10];
            sprintf_s(buffer,"%3d,",*iterVertexIndexList);
            sTemp = sTemp + std::string(buffer);
        }

        sTemp += "  #  " + iterSurface->sName;

        std::vector<TSurface>::iterator last_iterSurface = iterSurface;
        if (++last_iterSurface != Zone.SurfaceList.end() )
        {
            sTemp = sTemp + std::string("\n");
        }

    }
    return sTemp;
};


std::string esprGeoFile(TZone& Zone)
{
    std::stringstream sGeoFile;

    sGeoFile << boost::format("# geometry of %s \n") % Zone.sName;

    sGeoFile << boost::format("GEN  %s  no description  # type, name, descr\n") % Zone.sName;
    sGeoFile << boost::format("%8d %8d %8.3f    # vertices, surfaces, rotation angle\n")
    % Zone.Get_Number_Of_Vertexes()
    % Zone.Get_Number_Of_Surfaces()
    % 0.00;

    sGeoFile << "#  X co-ord, Y co-ord, Z co-ord\n";
    sGeoFile << GetESPRVertexList(Zone);
    sGeoFile << std::endl;
    sGeoFile << "# no of vertices followed by list of associated vert\n";
    sGeoFile << GetESPRSurfaceVertexList(Zone);
    sGeoFile << std::endl;

    //Unused index.
    sGeoFile << "# unused index"<<std::endl;
    for( int iCounter=0;
            iCounter < Zone.Get_Number_Of_Surfaces();
            iCounter++)
    {
        sGeoFile << " 0";
    }
    sGeoFile << std::endl;
    sGeoFile <<"# surfaces indentation (m)\n";

    //Iterate through each surface in the zone.
    std::vector<TSurface>::iterator iterSurface;

    for (
        iterSurface  = Zone.SurfaceList.begin();
        iterSurface != Zone.SurfaceList.end();
        iterSurface++
    )
    {
        sGeoFile << boost::format(" %10.4f ") % iterSurface->dSurfaceIndentation;
    }
    sGeoFile << std::endl;


    sGeoFile <<"   3   0   0   0    # default insolation distribution" << std::endl;

    //    3   0   0   0    # default insolation distribution
    sGeoFile << "# surface attributes follow:\n";
    sGeoFile << "# id  surface      geom  loc/  mlc db       environment\n";
    sGeoFile << "# no  name         type  posn  name         other side\n";

    //1. Iterate Through all surfaces in a zone.


    int iSurfaceNumber = 0;

    //Iterate through each surface in the zone.
    for (
        iterSurface  = Zone.SurfaceList.begin();
        iterSurface != Zone.SurfaceList.end();
        iterSurface++
    )
    {
        iSurfaceNumber++;

        sGeoFile << boost::format("%3d, %-12s  %-4s  %-4s  %-11s  %-10s\n")
        % iSurfaceNumber
        % iterSurface->sName
        % iterSurface->sGeoType
        % iterSurface->sPosition
        % iterSurface->sDBName
        % iterSurface->sEnvironmentOtherSide
        ;


    }
    //what is this? No longer needed?
    sGeoFile <<"# base" <<std::endl;
    sGeoFile <<"   6   0   0   0   0   0   108.37" <<std::endl;
    std::string sResult;
    sResult =  sGeoFile.str();
    //    std::cout << sResult;
    return sResult;
};


std::string esprConFile(TZone& Zone)
{

    std::stringstream sCon1, sCon2, sCon3, sCon4, sCon5, sCon6, sCon7;

    //1. Iterate Through all surfaces in a zone.

    std::vector<TSurface>::iterator iterSurface;
    int iSurfaceNumber = 0;
    sCon1<< "#thermophysical properties of "<<Zone.sName<<" defined in " <<" ../zones/" << std::endl;
    sCon1<< "#no of |air |surface(from geo)| multilayer construction" << std::endl;
    sCon1<< "#layers|gaps|  no.  name      | database name " << std::endl;
    //Iterate through each surface in the zone.
    for (
        iterSurface  = Zone.SurfaceList.begin();
        iterSurface != Zone.SurfaceList.end();
        iterSurface++
    )
    {
        iSurfaceNumber++;


        sCon1 << boost::format("%3d,%3d #%3d %s       simwiz generated database.\n")
        % (iterSurface->Construction.Get_Number_Of_Layers() )
        % (iterSurface->Construction.Get_Number_Of_AirGaps() )
        % (iSurfaceNumber)
        % (iterSurface->sName);

        //Add the emmissivity and solar absorption data.
        sCon4 << boost::format("%10.4f ")
        % (iterSurface->Construction.GetInsideEmissivity());

        sCon5 << boost::format("%10.4f ")
        % (iterSurface->Construction.GetOutsideEmissivity());

        sCon6 << boost::format("%10.4f ")
        % (iterSurface->Construction.GetInsideAbsorptivity());

        sCon7 << boost::format("%10.4f ")
        % (iterSurface->Construction.GetOutsideAbsorptivity());




        //Iterate through each material in each surface.
        int iLayer = 1;
        for ( TMaterialListIter itrMaterial = iterSurface->Construction.MaterialList.begin();
                itrMaterial != iterSurface->Construction.MaterialList.end();
                itrMaterial++)
        {
            // find if current layer is an airgap..if so increment counter.
            if (itrMaterial->bIsAirGap == true )
            {
                //Outputs the airgap location and the resistance.
                sCon2 << boost::format("# air gap position and resistance for surface  %d\n")
                % iSurfaceNumber;
                sCon2 << boost::format("%3d,%10.4f\n")
                % iLayer
                % itrMaterial->dAirGapResistance;
            }
            //Output all data of material required by ESP-r


            sCon3 << boost::format("%10.4f,%10.4f,%10.4f,%10.4f,%3d,%10.4f,%10.4f,%10.4f#%3d  %3d \n")
            % (itrMaterial->dConductivity)
            % (itrMaterial->dDensity)
            % (itrMaterial->dSpecificHeat)
            % (itrMaterial->dThickness)
            % (itrMaterial->iDpnd_type)
            % (itrMaterial->dRef_temp)
            % (itrMaterial->dTemp_factor)
            % (itrMaterial->dMoisture_factor)
            % (iSurfaceNumber)
            % (iLayer);
            iLayer++;
        } //End Material Loop.

    } //End Surface Loop.



    std::string sConstructionHeader = "# conduc-  |  density | specific | thick- |dpnd|  ref. |  temp. |moisture| surf|lyr\n# tivity   |          | heat     | ness(m)|type|  temp | factor | factor |     |  \n";



    std::string sResult;
    sResult =  sCon1.str() + sCon2.str()
               + sConstructionHeader
               + sCon3.str()
               + "# for each surface: inside face emissivity\n"
               + sCon4.str() + "\n"
               + "# for each surface: outside face emissivity\n"
               + sCon5.str() + "\n"
               + "# for each surface: inside face solar absorptivity\n"
               + sCon6.str() + "\n"
               + "# for each surface: outside face solar absorptivity\n"
               + sCon7.str() + "\n";

    return sResult;

};


std::string esprCNNFile(TZone& Zone)
{
    //This is a sigle zone application....so the zone level information can take care of the
    //Connection file. For multizones this will have to be change to take a building object.
    std::string sResult;
    std::stringstream sCNN;
    sCNN << "*connections  for lightswitch" <<std::endl;
    sCNN << "*Date Wed Nov 15 20:25:53 2006" <<std::endl;
    sCNN << boost::format("   %d # number of connections\n")
    % Zone.Get_Number_Of_Surfaces();
    //Iterate through each surface in the zone.
    std::vector<TSurface>::iterator iterSurface;
    int iCounter = 0;
    for (
        iterSurface  = Zone.SurfaceList.begin();
        iterSurface != Zone.SurfaceList.end();
        iterSurface++
    )
    {
        int iEnv = 0;
        if ( iterSurface->sEnvironmentOtherSide == "EXTERIOR") iEnv = 0;
        if ( iterSurface->sEnvironmentOtherSide == "ADIABATIC") iEnv = 5;

        iCounter++;
        sCNN << boost::format("   %d  %d  %d  %d %d # %s in %s is %s")
        % 1
        % iCounter
        % iEnv
        % 0
        % 0
        % iterSurface->sName
        % "Zone-1"
        % iterSurface->sEnvironmentOtherSide;
        sCNN << std::endl;
    }
    sResult = sCNN.str();
    return sResult;
};

std::string esprTMCFile(TZone& Zone)
{
    //This is a sigle zone application....so the zone level information can take care of the
    //Connection file. For multizones this will have to be change to take a building object.
    std::string sResult;
    std::stringstream sTMC, sTMC2;
    sTMC << "# transparent properties of zone." <<std::endl;
    sTMC << boost::format("  %d # Surfaces") % Zone.Get_Number_Of_Surfaces() <<std::endl;
    sTMC << "# tmc index for each surface" << std::endl;
    //Loop through all surfaces and find ones that are glazing. Each glazing will have it's own entry.
    //Iterate through each surface in the zone.
    int iGlazingIndex = 0;
    std::vector<TSurface>::iterator iterSurface;
    for (
        iterSurface  = Zone.SurfaceList.begin();
        iterSurface != Zone.SurfaceList.end();
        iterSurface++
    )
    {
        if (iterSurface->Construction.Glazing.bIsThereGlazing)
        {
            iGlazingIndex++;
            sTMC << boost::lexical_cast<string>(iGlazingIndex) << " ";
            sTMC2 << boost::format("%d  tmc_type_%d # layers in tmc type %d")
            % iterSurface->Construction.Get_Number_Of_Layers()
            % iGlazingIndex
            % iGlazingIndex << std::endl;

            sTMC2 << "# Transmission @ 5 angles & visible tr." << std::endl;
            sTMC2 << StreamOutVector(iterSurface->Construction.Glazing.BlindsUp.TransmissionValues)
            << iterSurface->Construction.Glazing.BlindsUp.dVisibleTransmission <<std::endl;
            sTMC2 << "# For each layer absorption @ 5 angles" << std::endl;
            sTMC2 << StreamOutVector(iterSurface->Construction.Glazing.BlindsUp.AbsorptionSets);
            sTMC2 << "1  # optical control flag" << std::endl;
            sTMC2 << "1   1  # no control periods & sensor loc" << std::endl;
            sTMC2 << "# Replacement properties for each control period" << std::endl;
            sTMC2 << "0  24   # period start and end" << std::endl;
            sTMC2 << "4   0.0  # sensing lightswitch @ actuation point" << std::endl;

            sTMC2 << "# Alt solar & vis trans followed by absorp for each layer" << std::endl;
            sTMC2 << StreamOutVector(iterSurface->Construction.Glazing.BlindsDown.TransmissionValues)
            << iterSurface->Construction.Glazing.BlindsDown.dVisibleTransmission <<std::endl;
            sTMC2 << StreamOutVector(iterSurface->Construction.Glazing.BlindsDown.AbsorptionSets);
            sTMC2 << "0" << std::endl;

        }
        else
        {
            sTMC << "0 ";
        }
    }
    sTMC << std::endl;

    sResult = sTMC.str() + sTMC2.str();
    return sResult;
};

