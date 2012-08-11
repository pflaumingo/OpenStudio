#include <stdlib.h>
#include "regexp.h"
#include "TMaterial.h"
#include "TConstruction.h"
#include "TFileUtilities.h"


TConstruction& TConstruction::operator=(const TConstruction& rhs)
{

	if (this != &rhs) // protect against invalid self-assignment
        {
    this->MaterialList.clear();
	this->MaterialList = rhs.MaterialList;
    this->sName = rhs.sName;
    this->Glazing = rhs.Glazing;
	}
    return *this;
}


TConstruction& TConstruction::operator*=(double rhs)
{

    MaterialList*= rhs;

    return *this;
}

TConstruction& TConstruction::operator*(double rhs)
{

    MaterialList*= rhs;

    return *this;
}

TConstruction& TConstruction::operator+=( TConstruction& rhs)
{
    MaterialList += rhs.MaterialList;
    return *this;
}


bool TConstruction::operator==(TConstruction& rhs)
{
return (MaterialListName == rhs.MaterialListName);

}



//TConstruction ScaleConstruction( TConstruction& lhs, const double& rhs)
//{
//	TConstruction Construction;
//	 Construction.MaterialList = lhs.MaterialList * rhs;
//}

void TConstruction::SetGlazing(TGlazing& GlazingIn){

    Glazing = GlazingIn;
}


int TConstruction::Get_Number_Of_Layers()
{
    return    MaterialList.size();
};


int TConstruction::Get_Number_Of_AirGaps()
{
    //Set counter to zero.
    int iNumberOfAirGaps = 0;
    //Loop through the layers.
    for ( TMaterialListIter itrMaterial = MaterialList.begin();
            itrMaterial != MaterialList.end();
            itrMaterial++)
    {
        // find if current layer is an airgap..if so increment counter.
        if (itrMaterial->bIsAirGap == true ) iNumberOfAirGaps++;
    }
    // Return the number of air gaps.
    return iNumberOfAirGaps;
};

bool TConstruction::bIsEmptyConstruction()
{
	if (MaterialList.size() <=0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

double TConstruction::GetInsideEmissivity()
{
		if (!bIsEmptyConstruction() )
	{
		return 0.0000;
	}
	else
    return  MaterialList.front().dEmissivity;
};

double TConstruction::GetOutsideEmissivity()
{
	if (!bIsEmptyConstruction() )
	{
		return 0.0000;
	}
	else
    return MaterialList.back().dEmissivity;
};


double TConstruction::GetInsideAbsorptivity()
{
		if (!bIsEmptyConstruction() )
	{
		return 0.0000;
	}
	else
    return MaterialList.front().dSolarAbsorptivity;
};


double TConstruction::GetOutsideAbsorptivity()
{
		if (!bIsEmptyConstruction() )
	{
		return 0.0000;
	}
	else
    return MaterialList.back().dSolarAbsorptivity;
};


void TConstruction::UseFictiousContruction(double dUValue, double dAreaThermalMass)
{


    //This sets up a 'standard wall' Using the ccht wall definition. It uses.

    //1. Determine the size of the paviour brick given the thermal mass.
    /* Properties of Paviour Brick.
       Conduction = 0.960   w/(m deg C)
       Density    = 2000.0  kg/m3
       spec Heat  = 840.0  J/(kg*C)
       emissivity = 0.93
       absorbity  = 0.70
       diff Resist = 12.
    */

    /* Properties of Chipboard.
       Conduction = 0.150   w/(m deg C)
       Density    = 800.0  kg/m3
       spec Heat  = 2093.0  
       emissivity = 0.91
       absorbity  = 0.65
       diff resist = 96.0
       DEFAULT_THICKNESS = 11.0
    */

    /* Properties of Glass Fibre Quilt.
       Conduction = 0.040   w/(m deg C)
       Density    = 12.0  kg/m3
       spec Heat  = 840.0  
       emissivity = 0.90
       absorbity  = 0.65
       diff resist = 30.0
    */

    /* Properties of Plywood.
       Conduction = 0.15   w/(m deg C)
       Density    = 700.0  kg/m3
       spec Heat  = 1420.0  
       emissivity = 0.90
       absorbity  = 0.65
       diff resist = 576.0
       DEFAULT_THICKNESS= 12.0
    */

    /* Two equations and two unknowns. From inside out. Determine the thickness and Air Gap resistance.
                    Brick   + Chipboard  + Air Gap + Plywood  




    Brick Thickness = (-21946.4 + 0.023 * dAreaThermalMass)/( 1680000 - dAreaThermalMass );



    1/Conduction   =  1/(0.960 * thickness)         +  1/(0.150 * 0.011)      + AirgapR +   1/(0.15 * 0.012)





    AirGap Resistance = (Conduction - 0.960 * thickness - 0.00345)

    */

    double dBrickThickness   = (dAreaThermalMass - 26680)
                               / ( 1680000 );
    // double dAirGapResistance = 1/ ( dUValue - 0.960 * dBrickThickness - 0.00345 );
    double dAirGapResistance =  1/dUValue - (1 / (0.96 / dBrickThickness ))
                                - (1/(.15/.010))
                                - (1/(.15 /.010));
    //4. Add the value to the construction materials vector.


    TMaterial Brick;
    Brick.MakeMaterial("paviour_brick", dBrickThickness );
    TMaterial Plywood;
    Plywood.MakeMaterial("plywood", 0.010);
    TMaterial Chipboard;
    Chipboard.MakeMaterial("chipboard", 0.010 );
    TMaterial AirGap;
    AirGap.MakeAirGap( dAirGapResistance );

    MaterialList.push_back( Brick );
    MaterialList.push_back( Chipboard );
    MaterialList.push_back( AirGap );
    MaterialList.push_back( Plywood );
    sName = "no_database";

}

/**
 * This method set the construction to have the thermal properties of the database files 
 * for the glazing set as defined in the SkyVision files. note as per the changes requested by Aziz, the thermal properties
 * of the glazing is now the AVERAGE of the up and down of the blind status.  
 *@param sGlazingID The id of the glazing
 *@ void
 */

void TConstruction::SetThermalPropertiesOfGlazing(std::string sGlazingID, bool IsASkylight)
{
    // Determine if there is a blind present. The sytax for this is if there is a trailing 'b'
    // in the glazing ID.
  //    std::cout << "SETTING THERMAL PROPS of GLAZING!!"<< std::endl;
    std::vector< std::string > vsIDMatch =  RegexpMatch("(\\d+)(\\D*)", sGlazingID);

    bool bBlinds = false;
    std::string sGlazingNumber;
    // Check if regexp failed.
    if ( vsIDMatch.size() <= 0 )
    {
        std::cerr << "GlazingID "<<  sGlazingID << " is invalid" << std::endl;
    }
    //Assign values depending on if blinds are required.
    if (vsIDMatch.size() > 0  )  sGlazingNumber = vsIDMatch[0];
    if (vsIDMatch.size() == 2 && vsIDMatch[1] == "b" ) bBlinds = true;


    std::string sGlazingFile;

    //To-Do move to global singleton.
    if (  true == IsASkylight  )
      {
	sGlazingFile = "../daylight_engine/SkyVisionFiles/ESPr_Skylight"
                               + sGlazingNumber + ".tmp";
      }
    else
      { 
        sGlazingFile = "../daylight_engine/SkyVisionFiles/ESPr_Window"
                               + sGlazingNumber + ".tmp";
      }



	

	openstudio::path GlazingPath = openstudio::toPath(sGlazingFile);
	FileExists( GlazingPath );
    std::vector<std::string> vsGlazingFile =read_file_into_vector(GlazingPath);
    // Line Three..assign materials
    std::vector<double> vdList2 =ToDouble( Tokenizer(vsGlazingFile[2]," ") );
    std::vector<double> vdList5 =ToDouble( Tokenizer(vsGlazingFile[5]," ") );
    // Line Three..assign materials
    TMaterial Material;
    if (bBlinds == true)
      {
	Material.dThickness                 = ( vdList2[0] +  vdList5[0] ) / 2.0 ;
	Material.dConductivity              = ( vdList2[1] +  vdList5[1] ) / 2.0 ;
	Material.dDensity                   = ( vdList2[2] +  vdList5[2] ) / 2.0 ;
	Material.dSpecificHeat              = ( vdList2[3] +  vdList5[3] ) / 2.0 ;
	Material.dEmissivity       = ( vdList2[4] +  vdList5[4] ) / 2.0 ;
	Material.dEmissivity        = ( vdList2[5] +  vdList5[5] ) / 2.0 ;
	Material.dSolarAbsorptivity  = 0.0500;
	Material.dSolarAbsorptivity = 0.0500;
	Material.dMoisture_factor           = 0.0;
	Material.dRef_temp                  = 0.0;
	Material.iDpnd_type                 = 0;
	Material.sName                      = sGlazingID;
      }
    else
      {
	Material.dThickness                 =  vdList2[0]  ;
	Material.dConductivity              =  vdList2[1]  ;
	Material.dDensity                   =  vdList2[2]  ;
	Material.dSpecificHeat              =  vdList2[3]  ;
	Material.dEmissivity       =  vdList2[4]  ;
	Material.dEmissivity        =  vdList2[5]  ;
	Material.dSolarAbsorptivity  = 0.0500;
	Material.dSolarAbsorptivity = 0.0500;
	Material.dMoisture_factor           = 0.0;
	Material.dRef_temp                  = 0.0;
	Material.iDpnd_type                 = 0;
	Material.sName                      = sGlazingID;	

      }

       std::cout << "Glazing Thermal Properties \n";
       std::cout << "File name " << sGlazingFile << "\n";
       std::cout << Material.StreamOut() << "\n";
    // Put it into the Glazings construction container.
    MaterialList.push_back(Material);
}



