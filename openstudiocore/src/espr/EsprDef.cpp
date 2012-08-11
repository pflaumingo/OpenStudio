// --------------------------------------------	// EsprDef.cpp : H3K/ESP-r Definitions (Namespace)
// -------------------------------------------- // and general functions
#include "stdafx.h"										// Required for PCH (Pre Compiled Headers)
#include "EsprDef.h"


// --------------------------------------------	// general boolean functions

double MIN(													// returns true if f1 is less than f2
	const double & f1,
	const double & f2 )
{
 	const double scale = ( fabs( f1 ) + fabs( f2 ) ) / 2.0; 

	if( fabs( f1 - f2 ) > ( FLT_EPSILON * scale )  && f1 < f2 ) return f1;
	else return f2;
}

double MAX(													// returns true if f1 is greater than f2
	const double & f1,
	const double & f2 )
{
 	const double scale = ( fabs( f1 ) + fabs( f2 ) ) / 2.0;

	if( fabs( f1 - f2 ) > ( FLT_EPSILON * scale )  && f1 > f2 ) return f1;
	else return f2;
}

bool equals(												// returns true if floats are equal
	const double & f1,
	const double & f2 )
{	
	if( fabs( f1 - f2 ) <=  ( double (0.001) )) return true;
	else return false;
}

bool lessThan(												// returns true if f1 is less than f2
	const double & f1,
	const double & f2 )
{
	if( fabs( f1 - f2 ) > ( double (0.001) )  && f1 < f2 ) return true;
	else return false;
}

bool greaterThan(											// returns true if f1 is greater than f2
	const double & f1,
	const double & f2 )
{
	if( fabs( f1 - f2 ) > ( double (0.001) ) && f1 > f2 ) return true;
	else return false;
}

bool lessOrEqualThan(									// returns true if f1 is less or equal than f2
	const double & f1,
	const double & f2 )
{
	if( fabs( f1 - f2 ) < ( double (0.001) )  ) return true;
	else if( f1 < f2 ) return true;
	else return false;
}

bool greaterOrEqualThan(								// returns true if f1 is greater or equal than f2
	const double & f1,
	const double & f2 )
{
	if( fabs( f1 - f2 ) < ( double (0.001) ) ) return true;
	else if( f1 > f2 ) return true;
	else return false;
}


// -------------------------------------------- // general code/string generators
/*
std::string GenerateZoneID(							// generate unique zone identifier string
	int iZone,												// zone [0,MX_ZONES)
	int iFunction,											// MAIN | LIVING | FULL_BASEMENT etc.
	int iLevel,												// level [0,MX_LEVELS)
	int iExt )												// CORE | FRONT | RIGHT | BACK | LEFT
{
   CString sRes;											// used for loading resource strings
	std::string sZone;
	std::ostringstream osZone;
	std::string sZonePrefix;
	std::string sFunction;
	std::string sLevel;
	std::ostringstream osLevel;
	std::string sLevelPrefix;
	std::string sExt;
	std::string sID;

	if( ( iZone >= 0 && iZone < espR::MX_ZONES )				&&
		 ( iLevel >= 0 && iLevel < espR::MX_LEVELS )			&&
		 ( iFunction == CRAWLSPACE									||
		   iFunction == espR::WINECELLAR							||
			iFunction == espR::SUNROOM								||
			iFunction == espR::LIVING								||
			iFunction == espR::GARAGE								||
			iFunction == espR::MUDROOM								||
			iFunction == espR::MAIN									||
			iFunction == espR::FULL_BASEMENT						||
			iFunction == espR::SHALLOW_BASEMENT					||
			iFunction == ATTIC )										&&
		 ( iExt == espR::CORE										||
			iExt == espR::FRONT										||
			iExt == espR::RIGHT										||
			iExt == espR::BACK										||
			iExt == espR::LEFT ) )
	{
		// 1. setting level string
		iLevel++;
		sLevelPrefix = "L";
		osLevel << iLevel;
		sLevel = sLevelPrefix + osLevel.str();

		// 2. setting zone string
		iZone++;
		sZonePrefix = " Z";
		osZone << iZone;
		sZone = sZonePrefix + osZone.str();

		// 3. setting extension string
		if( iExt == espR::CORE ) sExt = " Core";
		else if( iExt == espR::FRONT ) sExt = " Front";
		else if( iExt == espR::RIGHT ) sExt = " Right";
		else if( iExt == espR::BACK ) sExt = " Back";
		else sExt = " Left";

		// 4. setting function string
		if( iFunction == CRAWLSPACE ) sRes.LoadStringA(ID_CRAWLSPACE);
		else if( iFunction == espR::WINECELLAR ) sRes.LoadStringA(IDS_WINECELLAR);
		else if( iFunction == espR::SUNROOM ) sRes.LoadStringA(IDS_SUNROOM);
		else if( iFunction == espR::LIVING ) sRes.LoadStringA(IDS_LIVING);
		else if( iFunction == espR::GARAGE ) sRes.LoadStringA(ID_GARAGE);
		else if( iFunction == espR::MUDROOM ) sRes.LoadStringA(IDS_MUDROOM);
      else if( iFunction == espR::MAIN ) sRes.LoadStringA(IDS_MAINSTR);
		else if( iFunction == espR::FULL_BASEMENT ) sRes.LoadStringA(ID_BASEMENT);
		else if( iFunction == espR::SHALLOW_BASEMENT ) sRes.LoadStringA(ID_BASEMENT);
      else sRes.LoadStringA(IDS_ATTIC);

		sFunction = sRes.GetBuffer();

		// 4. setting final surface string
		sID += sLevel;
		sID += sZone;
		sID += sExt;
		sID += " " + sFunction;
	}
   else
   {
      sID = "Unknown";
   }
	return sID;
}

std::string GenerateSurfaceID(						// generate unique surface identifier string
	int iZone,												// zone [0,MX_ZONES]
	int iLevel,												// level [0,MX_LEVELS)
	int iExt,												// CORE | FRONT | RIGHT | BACK | LEFT
	int iSurfaceType,										// WALL | CEILING | FLR | WINDW | DOOR | SKYLIGHT
	int iSurface )											// surface order [0,MX_SURFACES)
{
	CString sRes;											// used for loading resource strings
	std::string sZone;
	std::ostringstream osZone;
	std::string sZonePrefix;
	std::string sLevel;
	std::ostringstream osLevel;
	std::string sLevelPrefix;
	std::string sExt;
	std::string sSurfaceType;
	std::string sSurfacePrefix;
	std::ostringstream osSurface;
	std::string sSurface;
	std::string sID;

	if( ( iZone >= 0 && iZone < espR::MX_ZONES )				&&
		 ( iLevel >= 0 && iLevel < espR::MX_LEVELS )			&&
		 ( iExt == espR::CORE										||
			iExt == espR::FRONT										||
			iExt == espR::RIGHT										||
			iExt == espR::BACK										||
			iExt == espR::LEFT )										&&
		 ( iSurface >= 0 && iSurface < espR::MX_SURFACES )	&&
		 ( iSurfaceType == WALL										||
		   iSurfaceType == CEILING									||
			iSurfaceType == FLR										||
			iSurfaceType == WINDW									||
			iSurfaceType == DOOR										||
			iSurfaceType == SKYLIGHT ) )
	{
		// 1. setting zone string
		sZonePrefix = "0";
		osZone << iZone + 1;
		if( iZone < 9 ) sZone = sZonePrefix + osZone.str();
		else sZone = osZone.str();

		// 2. setting level string
		sLevelPrefix = "0";
		osLevel << iLevel + 1;
		sLevel = sLevelPrefix + osLevel.str();

		// 3. setting extension string
		if( iExt == espR::CORE ) sExt = "C";
		else if( iExt == espR::FRONT ) sExt = "F";
		else if( iExt == espR::RIGHT ) sExt = "R";
		else if( iExt == espR::BACK ) sExt = "B";
		else sExt = "L"; 

		// 4. setting surface order number
		sSurfacePrefix = "0";
		osSurface << iSurface + 1;
		if( iSurface < 9 ) sSurface = sSurfacePrefix + osSurface.str();
		else sSurface = osSurface.str();

		// 5. setting prefix (surface type):
		if( iSurfaceType == WALL ) sSurfaceType = "wa";
		else if( iSurfaceType == CEILING ) sSurfaceType = "ce";
		else if( iSurfaceType == FLR ) sSurfaceType = "fl";
		else if( iSurfaceType == WINDW ) sSurfaceType = "wi";
		else if( iSurfaceType == DOOR ) sSurfaceType = "do";
		else if( iSurfaceType == SKYLIGHT ) sSurfaceType = "sk";
		else sSurfaceType = "NO";

		// 6. setting final surface string
		sID += sSurfaceType;
		sID += sSurface;
		sID += sExt;
		sID += sLevel;
		sID += sZone;
	}
	else
   {
      sID = "Unknown";
   }
	return sID;
}
*/
