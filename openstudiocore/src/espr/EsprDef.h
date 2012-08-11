// --------------------------------------------	// Header file for H3K/ESP-r Definitions (Namespace)
// -------------------------------------------- // and general functions

#ifndef _ESPRDEF_H
#define _ESPRDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <locale>
#include <cmath>
#include <math.h>
#include <float.h>
#include <string>
#include <sstream>

#include "EsprHot3000.h"


// -------------------------------------------- // espR namespace
namespace espR
{
	int const MATERIAL = 5001;							// tangible material
	int const AIRGAP = 5002;							// air gap (as opposed to MATERIAL)

	int const MIN_EMISSIVITY = 1;						// minimum far infrared emissivity
	int const MAX_EMISSIVITY = 99;					// maximum far infrared emissivity
	int const MIN_ABSORPTIVITY = 1;					// minimum solar absorptivity
	int const MAX_ABSORPTIVITY = 99;					// maximum solar absorptivity
	
	int const HOUSE = 0;									// single-family dwelling
	int const MURB = 1;									// multi-residential building
	
	int const ISOLATED = 31;							// standalone house or MURB
	int const ROW_LEFT = 32;							// left-side, row-house/MURB or duplex/MURB
	int const ROW_RIGHT = 33;							// right-side, row-house/MURB or duplex/MURB
	int const ROW_MIDDLE = 34;							// row-house/MURB, between units
	
	int const EXTERIOR = 201;							// surface boundary conditions
	int const SIMILAR = 202;							// surface boundary conditions
	int const GROUND = 203;								// surface boundary conditions
	int const ADIABATIC = 204;							// surface boundary conditions
	
	int const FULL_BASEMENT = 80;						// basement type
	int const SHALLOW_BASEMENT = 81;					// basement type
	int const OPEN_CRAWLSPACE = 82;					// basement type
	int const VENTILATED_CRAWLSPACE = 83;			// basement type
	int const VENTILATED_HEATED_CRAWLSPACE = 84;	// basement type
	int const CLOSED_CRAWLSPACE = 85;				// basement type
	int const CLOSED_HEATED_CRAWLSPACE = 86;		// basement type

	int const WINECELLAR = 94;							// space function option
	int const SUNROOM = 95;								// space function option
	int const LIVING = 96;								// space function option; thermally-distinct from MAIN
	int const GARAGE = 97;								// space function option
	int const MUDROOM = 98;								// space function option
	int const MAIN = 99;									// default for main core; & any zone not thermally-distinct from MAIN
	
	int const CORE = 110;								// extension position
	int const FRONT = 100;								// extension position; wall/aperture orientation
	int const RIGHT = 101;								// extension position; wall/aperture orientation
	int const BACK  = 102;								// extension position; wall/aperture orientation
	int const LEFT  = 103;								// extension position; wall/aperture orientation
	int const UP = 511;									// extension position; ceiling orientation
	int const DOWN = 512;								// extension position; floor orientation
	int const NONE = 105;								// wall/aperture orientation; WWR0%

	int const TEN_EVEN = 61;							// WWR10%, evenly distributed
	int const FIFTEEN_EVEN = 62;						// WWR15%, evenly distributed
	int const TEN_MOST_FRONTBACK = 63;				// WWR10%, 90% front/back & 10% right/left
	int const FIFTEEN_MOST_FRONTBACK = 64;			// WWR15%, 90% front/back & 10% right/left
	int const TEN_ALL_FRONTBACK = 65;				// WWR10%, 100% front/back
	int const FIFTEEN_ALL_FRONTBACK = 66;			// WWR15%, 100% front/back
	int const TEMPLATE_DEFAULTS = 67;				// calculate WWR% and distribution% based on "builder"

	int const MX_BUILDINGS = 10;						// maximum number of buildings per project
	int const MX_LEVELS = 5;							// maximum number of building levels, if Wiz'ed
	int const MX_EXTENSIONS = 5;						// maximum number of level extensions, if Wiz'ed
	int const MX_ZONES = 50;							// maximum number of thermal zones per building
	int const MX_BOUNDARIES = 200;					// maximum number of boundaries per thermal zone
	int const MX_SURFACES = 30;						// maximum number of surfaces per boundary
	int const MX_VERTICES = 50;						// maximum number of vertices per boundary and surface
	int const MX_CONSTRUCTIONS = 100;				// maximum number of constructions per project
	int const MX_MATERIALS = 100;						// maximum number of materials per project
	int const MX_LAYERS = 10;							// maximum number of layers per construction
	
	int const ILEVELS = 2;								// default; normally reset by user
	int const LEVEL_HEIGHT = 2700;					// default; in millimeters; normally reset by builder
	int const X_ORIGIN = 100;							// in meters; no reason to reset ...
	int const Y_ORIGIN = 100;							// in meters; no reason to reset ...
	int const BELOW_GRADE_HEIGHT = 1800;			// default; in millimeters; normally reset by builder
	int const GROUND_HEIGHT = 100;					// default; no reason to reset
	int const CORE_WIDTH = 15;							// default; in meters; normally reset by user
	int const CORE_DEPTH = 10;							// default; in meters; normally reset by user
	int const ORIENTATION = 0;							// default; in degrees; normally reset by user

	double const PI = 3.14159265;						// PI

	// Possible Surface relations
	int const NO_RELATION = 501;						// non coplanar or parallel surfaces 
	int const PARALLEL = 502;							// parallel surfaces 
	int const COPLANAR = 503;							// coplanar surfaces
	int const COPLSHAREONE = 504;						// Coplanar that share only one summit
	int const ADJACENT = 505;							// coplanar & adjacent surfaces (share two or more consecutive summits)
	int const OVERLAPPING = 506;						// coplanar & overlapping surfaces
	int const INCLUDED = 507;							// Os is inside current  surface without touching edges
	int const INCLUDEDTOUCH = 508;						// Os is inside current surface and touching edges
}


// -------------------------------------------- // general boolean functions

double MIN(													// returns minimum value between f1 and f2
	const double & f1,
	const double & f2 );
double MAX(													// returns maximum value between f1 and f2
	const double & f1,
	const double & f2 );
bool equals(												// returns true if floats are equal
	const double & f1,
	const double & f2 );
bool lessThan(												// returns true if f1 is less than f2
	const double & f1,
	const double & f2 );
bool greaterThan(											// returns true if f1 is greater than f2
	const double & f1,
	const double & f2 );
bool lessOrEqualThan(									// returns true if f1 is less or equal than f2
	const double & f1,
	const double & f2 );
bool greaterOrEqualThan(								// returns true if f1 is greater or equal than f2
	const double & f1,
	const double & f2 );


// -------------------------------------------- // general code/string generators
/*
std::string GenerateZoneID(							// generate unique zone identifier string
	int iZone,												// zone [0,MX_ZONES)
	int iFunction,											// MAIN | LIVING | etc.
	int iLevel,												// level [0,MX_LEVELS)
	int iExt );												// CORE | FRONT | RIGHT | BACK | LEFT

std::string GenerateSurfaceID(						// generate unique surface identifier string
	int iZone,												// zone [0,MX_ZONES]
	int iLevel,												// level [0,MX_LEVELS)
	int iExt,												// CORE | FRONT | RIGHT | BACK | LEFT
	int iSurfaceType,										// WALL | CEILING | FLR | WINDW | DOOR | SKYLIGHT
	int iSurface );										// surface order [0,MX_SURFACES)
*/
#endif // _ESPRDEF_H
