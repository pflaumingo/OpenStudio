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
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "TZone.h"
#include "TSurface.h"
#include "Espr3d.h"
#include "TFileUtilities.h"
#include "Regexp.h"

int TZone::Get_Number_Of_Surfaces()
{
	return SurfaceList.size();
}

int TZone::Get_Number_Of_Vertexes()
{
	return GlobalVertexList.size();
}

void TZone::AddNewSurface(std::string sNameIn,
						  std::vector <Vertex3D> VertexListIn,
						  TConstruction& ConstructionIn,
						  std::string sGeoTypeIn,
						  std::string sPositionIn,
						  std::string sEnvironmentOtherSideIn,
						  double dSurfaceIndentationIn)
{

	bool bFailed = false;
	for ( std::vector<TSurface>::iterator counter = SurfaceList.begin();
		counter != SurfaceList.end();
		counter++)
	{
		//1. Fail if name is already used.
		if (counter->sName == sNameIn) bFailed = true;

		//2. A surface collision test would be nice here.

	}
	if (bFailed)
	{
		//some kind of throw catch here.
	}
	else
	{

		TSurface Surface(sNameIn,
			VertexListIn,
			ConstructionIn,
			sGeoTypeIn,
			sPositionIn,
			sEnvironmentOtherSideIn,
			dSurfaceIndentationIn);

		SurfaceList.push_back(Surface);
	}
	//Refresh global index.
	RefreshVertexesAndIndexes();
}





void TZone::AddNewSurface (
						   std::string sNameIn,
						   std::vector< Vertex3D > VertexIndex,
						   std::vector<int> VertexIndexListIn,
						   TConstruction& Construction,
						   std::string sGeoTypeIn,
						   std::string sPositionIn,
						   std::string sEnvironmentOtherSideIn,
						   double dSurfaceIndentationIn)
{

	bool bFailed = false;
	for (
		std::vector<TSurface>::iterator counter = SurfaceList.begin();
		counter != SurfaceList.end();
	counter++)

	{
		//1. Fail if name is already used.
		if (counter->sName == sNameIn) bFailed = true;

		//2. A surface collision test would be nice here.

	}
	if (bFailed)
	{
		//some kind of throw catch here.
	}
	else
	{
		TSurface Surface(sNameIn,
			VertexIndex,
			VertexIndexListIn,
			Construction,
			sGeoTypeIn,
			sPositionIn,
			sEnvironmentOtherSideIn,
			dSurfaceIndentationIn);

		SurfaceList.push_back(Surface);
	}
	//Refresh global index.
	RefreshVertexesAndIndexes();
}





void  TZone::RefreshVertexesAndIndexes()
{
	GlobalVertexList.clear();
	//Loop through surface list.

	for ( std::vector<TSurface>::iterator iterSurface = SurfaceList.begin();
		iterSurface != SurfaceList.end();
		iterSurface++)
	{
		//Empty the index vertex list..It will be recreated below.
		iterSurface->VertexIndexList.clear();

		//Loop through vertexes in surface.
		for ( std::vector<Vertex3D>::iterator iterSurfaceVertex = iterSurface->vVx.begin();
			iterSurfaceVertex !=  iterSurface->vVx.end();
			iterSurfaceVertex++)
		{
			//If the vertex was not found in the list.
			std::vector<Vertex3D>::iterator location;
			location =  std::find(GlobalVertexList.begin(), GlobalVertexList.end(),*iterSurfaceVertex );
			if ( GlobalVertexList.end() == location )
			{
				//THen add it to the global list.
				GlobalVertexList.push_back(*iterSurfaceVertex);
			}
			//This is done again to ensure that the correct location in the vector is used.
			location =  find(GlobalVertexList.begin(), GlobalVertexList.end(),*iterSurfaceVertex );
			//Now shove the index to the vertex into the container in the surface object.
			iterSurface->VertexIndexList.push_back(distance(GlobalVertexList.begin(), location)+1);
		}
	}
}

void  TZone::RotateAndScale(double dAngle,double dWidth,double dDepth,double dHeight)
{

	//convert angle to radians.
	//Got this trick to get an more accurate value of PI from ESP-r.
	const double PI = 4.0 * atan( 1.0 );
	double dRadians = dAngle* PI / 180.0;


	//iterate thorugh the Global vertex list and modify values for each vertex.

	std::vector<Vertex3D>::iterator iterGlobalVertexList;
	for ( iterGlobalVertexList = GlobalVertexList.begin();
		iterGlobalVertexList != GlobalVertexList.end();
		iterGlobalVertexList++)
	{
		//perform scale
		//basic house is normalized to 10m units. So we have to divide by 10 and then apply the
		//Scale factor for each dimension.
		iterGlobalVertexList->vx *= dWidth/10.0;
		iterGlobalVertexList->vy *= dDepth/10.0;
		iterGlobalVertexList->vz *= dHeight/10.0;

		//Perform the rotation about the Z-axis
		//absolute lentgh of vector.

		double CA=cos(dRadians);
		double SA=sin(dRadians);
		//std::cout <<"SA= " << SA <<std::endl;
		//std::cout <<"CA= " << CA <<std::endl;
		double oldX = iterGlobalVertexList->vx ;
		double oldY = iterGlobalVertexList->vy ;

		//std::cout <<"old " << oldX << "," <<  oldY <<std::endl;

		//std::cout << (iterGlobalVertexList->vx * CA) << " - " << (iterGlobalVertexList->vy * SA)<< std::endl;
		//std::cout <<  (iterGlobalVertexList->vy * CA)<<" + "<< (iterGlobalVertexList->vx * SA)<< std::endl;
		double newX = (iterGlobalVertexList->vx * CA) - (iterGlobalVertexList->vy * SA);
		double newY = (iterGlobalVertexList->vy * CA) + (iterGlobalVertexList->vx * SA);

		iterGlobalVertexList->vx = newX;
		iterGlobalVertexList->vy = newY;

		//	std::cout <<"old " << oldX << "," <<  oldY <<std::endl;


		//std::cout <<"new "<< iterGlobalVertexList->vx << "," <<  iterGlobalVertexList->vy <<std::endl;



	}

	// Now go through each surface and modify their internal surface vertexes
	//   Loop through surface list.

	for ( std::vector<TSurface>::iterator iterSurface = SurfaceList.begin();
		iterSurface != SurfaceList.end();
		iterSurface++)
	{
		//Empty the index vertex list..It will be recreated below.
		iterSurface->vVx.clear();

		//Loop through vertexes in surface.
		for ( std::vector<int>::iterator iterVertexIndexList = iterSurface->VertexIndexList.begin();
			iterVertexIndexList !=  iterSurface->VertexIndexList.end();
			iterVertexIndexList++)
		{
			iterSurface->vVx.push_back(GlobalVertexList[*iterVertexIndexList - 1]);

		}
	}





}//end rotate and scale


TSurface* TZone::GetSurface(std::string sSearchSurfaceName)
{

	TSurface* Return;

	//1.Iterate through all surfaces and find the parent surface base on the sName.
	bool bFoundSurface = false;
	for( std::vector<TSurface>::iterator iterSurface = SurfaceList.begin();
		iterSurface != SurfaceList.end();
		iterSurface++ )
	{
		//If found then store the pointer to ParentSurface.
		if( iterSurface->sName == sSearchSurfaceName )
		{
			Return = &(*iterSurface);
			bFoundSurface= true;
		}
	}
	//If not then throw an error.
	if( bFoundSurface == false )
	{
		//To do should throw an exception.
		std::cout<<"no such surface"<<sSearchSurfaceName<<std::endl;
	}
	return Return;
}




void TZone::Rotate(double dAngle)
{

	//convert angle to radians.
	//Got this trick to get an more accurate value of PI from ESP-r.
	const double PI = 4.0 * atan( 1.0 );
	double dRadians = dAngle* PI / 180.0;


	//iterate thorugh the Global vertex list and modify values for each vertex.

	std::vector<Vertex3D>::iterator iterGlobalVertexList;
	for ( iterGlobalVertexList = GlobalVertexList.begin();
		iterGlobalVertexList != GlobalVertexList.end();
		iterGlobalVertexList++)
	{


		//Perform the rotation about the Z-axis
		//absolute lentgh of vector.

		double CA=cos(dRadians);
		double SA=sin(dRadians);

		double oldX = iterGlobalVertexList->vx ;
		double oldY = iterGlobalVertexList->vy ;

		double newX = (iterGlobalVertexList->vx * CA) - (iterGlobalVertexList->vy * SA);
		double newY = (iterGlobalVertexList->vy * CA) + (iterGlobalVertexList->vx * SA);

		iterGlobalVertexList->vx = newX;
		iterGlobalVertexList->vy = newY;


	}

	// Now go through each surface and modify their internal surface vertexes
	//   Loop through surface list.

	for ( std::vector<TSurface>::iterator iterSurface = SurfaceList.begin();
		iterSurface != SurfaceList.end();
		iterSurface++)
	{
		//Empty the index vertex list..It will be recreated below.
		iterSurface->vVx.clear();

		//Loop through vertexes in surface.
		for ( std::vector<int>::iterator iterVertexIndexList = iterSurface->VertexIndexList.begin();
			iterVertexIndexList !=  iterSurface->VertexIndexList.end();
			iterVertexIndexList++)
		{
			iterSurface->vVx.push_back(GlobalVertexList[*iterVertexIndexList - 1]);

		}
	}





}



void TZone::Scale( double dWidth,double dDepth,double dHeight)
{
	//iterate thorugh the Global vertex list and modify values for each vertex.

	std::vector<Vertex3D>::iterator iterGlobalVertexList;
	for ( iterGlobalVertexList = GlobalVertexList.begin();
		iterGlobalVertexList != GlobalVertexList.end();
		iterGlobalVertexList++)
	{
		//perform scale
		//basic house is normalized to 10m units. So we have to divide by 10 and then apply the
		//Scale factor for each dimension.
		iterGlobalVertexList->vx *= dWidth/10.0;
		iterGlobalVertexList->vy *= dDepth/10.0;
		iterGlobalVertexList->vz *= dHeight/10.0;

	}

	// Now go through each surface and modify their internal surface vertexes
	//   Loop through surface list.

	for ( std::vector<TSurface>::iterator iterSurface = SurfaceList.begin();
		iterSurface != SurfaceList.end();
		iterSurface++)
	{
		//Empty the index vertex list..It will be recreated below.
		iterSurface->vVx.clear();

		//Loop through vertexes in surface.
		for ( std::vector<int>::iterator iterVertexIndexList = iterSurface->VertexIndexList.begin();
			iterVertexIndexList !=  iterSurface->VertexIndexList.end();
			iterVertexIndexList++)
		{
			iterSurface->vVx.push_back(GlobalVertexList[*iterVertexIndexList - 1]);

		}
	}


}






std::vector<TEdge> TZone::GetEdgeList()
{

	std::vector<TEdge> EdgeList;
	for ( std::vector<TSurface>::iterator iterSurface = SurfaceList.begin();
		iterSurface != SurfaceList.end();
		iterSurface++)
	{
		TEdge Edge;
		Edge.SurfaceName=iterSurface->sName;
		std::cerr << iterSurface->sName << std::endl;
		//Loop through vertexes in surface.
		int iLast = iterSurface->VertexIndexList.size();
		int iCounter = 0;
		for ( std::vector<int>::iterator iterVertexIndexList = iterSurface->VertexIndexList.begin();
			iterVertexIndexList !=  iterSurface->VertexIndexList.end();
			iterVertexIndexList++)
		{
			iCounter += 1;
			TEdge Edge;
			Edge.Index1 = *iterVertexIndexList;

			if (iCounter !=  iLast )
			{
				std::vector<int>::iterator iterVertexIndexListNext = iterVertexIndexList;
				iterVertexIndexListNext++;
				Edge.Index2 = *iterVertexIndexListNext;
			}
			else
			{  
				Edge.Index2 = iterSurface->VertexIndexList.front();
			}

			//std::cerr << "Index " << Edge.Index1 <<" " << Edge.Index2 << std::endl    ;
			EdgeList.push_back(Edge);


		}
	}
	return EdgeList;
}









bool TZone::CheckEnclosure()
{
	//   //Create a list of all the edges in the zone.
	//   //std::cerr << " Create a list of all the edges in the zone." << std::endl;
	//   std::vector<TEdge> EdgeList = GetEdgeList();
	//   //std::cerr << " Create storage space for unbounded edges." << std::endl;
	//   //Create storage space for unbounded edges. 
	//   std::vector<TEdge> UnboundedEdgeList;

	//   //Loop through each edge. 
	//   //std::cerr << "Loop through each edge. ." << std::endl;
	//   BOOST_FOREACH( TEdge Edge1, EdgeList )
	//   {
	//     //Initialize Edge to false. 
	//     //std::cerr << "Initialize Edge to false. Loop through each edge. ." << Edge1.SurfaceName<< std::endl;
	//     Edge1.bMatched = false;
	//     //std::cerr << " Edge to false. Loop through each edge. ." << Edge1.SurfaceName<< std::endl;
	//     //Initialize Matched Surface to NULL.
	//     //std::cerr << "Initialize Matched Surface to NULLLoop through each edge. ." << std::endl;
	//     Edge1.MatchedSurfaceName = "";
	//     //std::cerr << "Loop through other edges. " << std::endl;
	//     //Loop through the other edges for comparision.
	//     BOOST_FOREACH( TEdge Edge2, EdgeList )
	//     {
	//       //don't compare the same edge!
	//       //std::cerr << "don't compare the same edge! " << std::endl;
	//       if ( !(Edge1.Index1 == Edge2.Index1 
	// 	     && Edge1.Index2 == Edge2.Index2 
	// 	     && Edge1.SurfaceName == Edge2.SurfaceName) 
	// 	   )

	// 	{
	//           //Check to see if the there is a reverse edge that matches the current edge.
	// 	  //std::cerr << "Check to see if the there is a reverse edge that matches the current edge." << std::endl;
	// 	  if (Edge1.Index1 == Edge2.Index2 
	// 	      && Edge1.Index2 == Edge2.Index1 )
	// 	    {
	// 	      //Set matched flag to true.
	// 	      //std::cerr << "Set matched flag to true.." << std::endl;
	// 	      Edge1.bMatched = true; 
	// 	      //std::cerr << "Store information on which surface matched" << std::endl;
	// 	      //Store information on which surface matched. 
	// 	      Edge1.MatchedSurfaceName = Edge2.SurfaceName;
	// 	    }

	// 	}

	//     }
	//     // if no match was found. 
	//     if (Edge1.bMatched == false)
	//       {
	// 	//add to unbounded edge list. 
	// 	UnboundedEdgeList.push_back(Edge1);
	//       }

	//   }
	//   //Check if there were any unbounded edges. 
	//   if (UnboundedEdgeList.size() > 1 ) 
	//     {
	//       //Tell user the problem. 
	//       std::cerr << "Zone is not bounded correctly" << std::endl; 
	//       //Loop through all the 
	//       BOOST_FOREACH( TEdge Edge, UnboundedEdgeList  )
	//       {
	// 	std::cerr << "Surface"  << std::endl;
	// 	std::cerr << Edge.SurfaceName << std::endl;
	//       }
	//       throw "Stop";
	//       return false;
	//       throw "Stop";
	//     }
	//   //If everything was correct. 
	//   else
	//     {
	//       std::cerr << "Zone is bounded correctly" << std::endl; 
	//       return true;
	//     }
	return true;
}

void TZone::LoadGeoFile(const openstudio::path& GEOPath)
{

		//Read Zone name. 
		ReadZoneName(GEOPath);
		//Read Num or vertexes Surfaces and rotation values. 
		ReadNumberOfZoneVertexesSurfacesAndRotation(GEOPath);
		//Create Empty Surfaces
		for (int iSurfCounter = 0 ; iSurfCounter < iNumOfSurfaces ; iSurfCounter++)
		{
			TSurface surface;
			SurfaceList.push_back(surface);
		}

		//Populate Surfaces
		//Read Zone Vertexes
		ReadZoneVertexes(GEOPath);
		//Read EdgesList
		ReadSurfaceEdgeLists(GEOPath);
		//Read Surface Attributes
		ReadSurfaceAttributes(GEOPath);
		//Read Indentation values
		ReadSurfaceIndentation( GEOPath);





}


void TZone::ReadNumberOfZoneVertexesSurfacesAndRotation(const openstudio::path& GEOPath)
{
	if (boost::filesystem::exists(GEOPath))
	{
	std::vector<string> GEOFile = read_file_into_vector_strip_comments(GEOPath);
	//match with this format "34 14 0.000 # vertices , surfaces , rotation angle"
	string zoneNameSearch= "^\\s*(\\d*)\\s*(\\d*)\\s*(\\d*\\.\\d*)\\s*(\\#.*)?";
	std::vector<string> Matches = RegexpMatch(zoneNameSearch, GEOFile[1]);
			if (Matches.size() > 1)  
			{
				iNumOfVertexes = boost::lexical_cast<int>(Matches[0]);
				iNumOfSurfaces = boost::lexical_cast<int>(Matches[1]);
				fRotation = boost::lexical_cast<float>(Matches[2]);
			}

	}



}

std::vector<Vertex3D> TZone::ReadZoneVertexes(const openstudio::path& GEOPath)
{
	int StartSectionIndex = 2; 
	int EndSectionIndex   = iNumOfVertexes + 2; 
	if (boost::filesystem::exists(GEOPath))
	{
	    std::vector<Vertex3D> VertexList;
	    std::vector<string> Matches;
		std::vector<string> GEOFile = read_file_into_vector_strip_comments(GEOPath.string());
		for (int icounter = StartSectionIndex ;icounter < EndSectionIndex ; icounter++)
		{
			std::string line = GEOFile[icounter];
			//Store Vertexes
			//TO-DO Bullet proof this so pound symbol is not required. 
			string VertexSearch= "^\\s*(\\d*\\.\\d*)\\s*(\\d*\\.\\d*)\\s*(\\d*\\.\\d*)\\s*\\#.*?";
			Matches = RegexpMatch(VertexSearch, line);
			if (Matches.size() == 3)
			{
				Vertex3D vertex(boost::lexical_cast<double>(Matches[0]),
					boost::lexical_cast<double>(Matches[1]),
					boost::lexical_cast<double>(Matches[2])
					);
				VertexList.push_back(vertex);
			}

		}
		GlobalVertexList = VertexList;
}
	return GlobalVertexList;
}

std::string TZone::ReadZoneName(const openstudio::path& GEOPath)
{
	std::vector<string> GEOFile = read_file_into_vector_strip_comments(GEOPath.string());
	//Match to this format "GEN reception # type zone name"
    string zoneNameSearch= "^GEN\\s*(\\S*)\\s*.*";
	std::vector<string> Matches = RegexpMatch(zoneNameSearch, GEOFile[0]);
			if (Matches.size() == 1)  
			{
				sName = Matches[0];
			}
	return sName;
}

void TZone::ReadSurfaceEdgeLists(const openstudio::path& GEOPath)
{


	if (boost::filesystem::exists(GEOPath))
	{
		//Set start and stop area for section. 
		int StartSectionIndex = iNumOfVertexes + 2; 
		int EndSectionIndex = iNumOfSurfaces + iNumOfVertexes + 2; 

		std::vector<string> GEOFile = read_file_into_vector_strip_comments(GEOPath.string());
		int iSurfaceCounter = 0; 
		for (int icounter = StartSectionIndex ; icounter < EndSectionIndex ; icounter++)
		{
			//Read and store VeterxIndexes for each surface in the zone. 
            std::string line = GEOFile[icounter];
			string IndexSearch= "(^\\s*\\d+,\\s*\\d+,\\s*\\d+,\\s*\\d+,).*$";
		    std::vector<string> Matches = RegexpMatch(IndexSearch, line);
			if (Matches.size() >= 1)  
			{

				std::vector<string> strings;
				boost::erase_all(line," ");
				boost::split(strings,line,boost::is_any_of(","));
				//Get rid of first number which is the number of vertexes, we dont need it. 
				strings.erase(strings.begin());
				std::vector<int> IndexList;
				BOOST_FOREACH(string value, strings) 
				{
					if (value != "") 
					{
						SurfaceList[iSurfaceCounter].VertexIndexList.push_back( boost::lexical_cast<int>(value));
						
						SurfaceList[iSurfaceCounter].vVx.push_back( GlobalVertexList[boost::lexical_cast<int>(value) - 1] );
						
					}
				}
				//Once all vertices have been added, set the equation of the surface. 
				SurfaceList[iSurfaceCounter].SetSurfEquation();	

			}
			iSurfaceCounter++;
		}
	}

}



void TZone::ReadSurfaceIndentation(const openstudio::path& GEOPath)
{


	if (boost::filesystem::exists(GEOPath))
	{
		//Set start and stop area for section. 
		int StartSectionIndex = 2 + iNumOfSurfaces + iNumOfVertexes +1 ; 


		std::vector<string> GEOFile = read_file_into_vector_strip_comments(GEOPath.string());


			//Read and store VeterxIndexes for each surface in the zone. 
            std::string line = GEOFile[StartSectionIndex];
			std::vector<string> strings;
			boost::split(strings,line,boost::is_any_of(" "));
            int iSurfaceCounter = 0;
			BOOST_FOREACH(std::string value, strings) 
				{
					if (value != "") 
					{
						SurfaceList[iSurfaceCounter].dSurfaceIndentation = ( boost::lexical_cast<double>(value));
						iSurfaceCounter++;
					}
				}
				

			
		}


}




void TZone::ReadSurfaceAttributes(const openstudio::path& GEOPath)
{
	if (boost::filesystem::exists(GEOPath))
	{
		//Set start and stop area for section. 
		int StartSectionIndex = 2 + iNumOfSurfaces + iNumOfVertexes + 3; 
		int EndSectionIndex =   2 + iNumOfSurfaces + iNumOfVertexes + 3 + iNumOfSurfaces ; 

		std::vector<string> GEOFile = read_file_into_vector_strip_comments(GEOPath.string());
		int iSurfaceCounter = 0;
		for (int icounter = StartSectionIndex ; icounter < EndSectionIndex ; icounter++)
		{
            std::string line = GEOFile[icounter];
			string IndexSearch= "^\\s*\\d*,\\s*(\\S*)\\s*(\\S*)\\s*(\\S*)\\s*(\\S*)\\s*(\\S*)\\s*(\\#.*)?";
		    std::vector<string> Matches = RegexpMatch(IndexSearch, line);
			if (Matches.size() >= 1)  
			{ 
				SurfaceList[iSurfaceCounter].sName = Matches[0];
				SurfaceList[iSurfaceCounter].sGeoType = Matches[1];
				SurfaceList[iSurfaceCounter].sPosition = Matches[2];
				SurfaceList[iSurfaceCounter].sDBName = Matches[3];
				SurfaceList[iSurfaceCounter].sEnvironmentOtherSide = Matches[4];
				iSurfaceCounter++;

			}		
		}
	}
}


void TZone::RemoveHoles()
{
	//Go clear any parent children already assigned
	BOOST_FOREACH(TSurface surface, SurfaceList) 
	{
		surface.subSurfaces.clear();

	}


	int iSurfaceCounter = 0;
	std::vector<int> IndexOfSurfacesToRemove;

	//Remove subsurface holes from surfaces. 
	BOOST_FOREACH(TSurface surface, SurfaceList) 
	{

		//remove all holes from surface.

		//Find start of hole by determining if the first vertex has been used twice.
		int iDuplicateVertexIndexStart = 0;
		int iDupCounter= 0;
		int iVertexCounter = 0;
		BOOST_FOREACH( Vertex3D vertex, surface.vVx) 
		{
			
			if (*surface.vVx.begin() == vertex)
			{
				iDupCounter++;
			}
			//Twice because it will match the first time always. 
			if (iDupCounter == 2 && iDuplicateVertexIndexStart == 0) 
			{
				iDuplicateVertexIndexStart = iVertexCounter;
			}
			iVertexCounter++;
		}
		//Remove interior points from all surfaces. 

		if ( iDuplicateVertexIndexStart > 0 ) 
		{
		SurfaceList[iSurfaceCounter].vVx.erase(SurfaceList[iSurfaceCounter].vVx.begin()+ iDuplicateVertexIndexStart, SurfaceList[iSurfaceCounter].vVx.end() );
		//Must reset Surface Equation.. This should really be an observer pattern that detect any changes to the TSurface or Surface3D object. 
		SurfaceList[iSurfaceCounter].SetSurfEquation();	
		SurfaceList[iSurfaceCounter].VertexIndexList.erase(SurfaceList[iSurfaceCounter].VertexIndexList.begin()+ iDuplicateVertexIndexStart, SurfaceList[iSurfaceCounter].VertexIndexList.end() );
		}
		iSurfaceCounter++;
	}
};

void TZone::FindParentSurfaces()

{
	std::vector<int> IndexOfSurfacesToRemove;
	int iSurfaceCounter = 0;
	BOOST_FOREACH(TSurface surface, SurfaceList) 
	{
		int iPossibleChildCounter = 0;
		BOOST_FOREACH(TSurface possibleSubSurface, SurfaceList) 
		{
			//Make sure you do not compare the same surface. 
			if (surface != possibleSubSurface)
			{
				//Check to see if the possible subsurface is completely contained or touches an edge of the parent surface. 
				if ( 507 == surface.getSurfRelation(possibleSubSurface) ||
					 508 == surface.getSurfRelation(possibleSubSurface) )
				{
					//cout<<"Parent"<<iSurfaceCounter<<"child"<<iPossibleChildCounter<<"\n";
					//add subsurface to the parent surface. 
					SurfaceList[iSurfaceCounter].subSurfaces.push_back(possibleSubSurface); 

					//SurfaceList[iSurfaceCounter].subSurfaces.push_back(possibleSubSurface);
					IndexOfSurfacesToRemove.push_back(iPossibleChildCounter);
				}
			}
			iPossibleChildCounter++;
		}
		iSurfaceCounter++;
	}
		//Now remove surfaces that have been assigned as a subsurface. 

	BOOST_REVERSE_FOREACH(int index, IndexOfSurfacesToRemove)
	{
			SurfaceList.erase(SurfaceList.begin()+index);
	}

};














