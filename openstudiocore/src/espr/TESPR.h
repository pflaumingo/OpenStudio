/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *           
 *                                                                 *
 ***************************************************************************/
#ifndef TESPRH
#define TESPRH

#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <string> 

#include "Espr3d.h"
std::string StringifyVertexList(std::vector<Vertex3D> TempVertexList);

//Pre-declared classes.
class TZone;


/**
 * This will return a list of all the vertexes in the TZone object, in ESP-r style.
 * @param Zone A TZone. object.
 * @return The std::string of all the vertex in ESP-r style. 
 */
std::string GetESPRVertexList(TZone& Zone);


/**
 * This will return a list of all the Surface vertex index list in the TZone object, in ESP-r style.
 * @param Zone A TZone object.
 * @return A list of all the Vertex indexes for each TSurface in TZone, in ESP-r style. 
 */

std::string GetESPRSurfaceVertexList(TZone& Zone);


std::string esprConFile(TZone& Zone);
std::string esprGeoFile(TZone& Zone);
std::string esprTMCFile(TZone& Zone);
std::string esprCNNFile(TZone& Zone);
#endif
