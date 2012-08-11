#ifndef TCONSTRUCTIONH
#define TCONSTRUCTIONH

#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include "TMaterial.h"
#include "TGlazing.h"

//pre-declaration.

/**
 * This class contains the material data of a particular construction. 
 */
class TConstruction
{
public:

    /**
     * A list of materials, in order, used in the construction.
     */
    std::vector< TMaterial > MaterialList;
	std::vector< std::string > MaterialListName;

    /**
     * The name of the construction.
     */
    std::string sName ;

    TGlazing Glazing;

    void SetGlazing(TGlazing& GlazingIn);
    TConstruction& operator=(const TConstruction& other);


	TConstruction& operator+=( TConstruction& rhs);
    TConstruction& operator*=(double rhs);
    TConstruction& operator*(double rhs);
	bool operator==(TConstruction& rhs);
    TConstruction()
    {
        sName = "no_database";
    };

    //~TConstruction(){} ;         // code depends on X

    std::string StreamOut()
    {
        std::stringstream sOutput;

        sOutput <<"*********Construction******" << std::endl;
        sOutput << "Construction sName: " << sName << std::endl;
        sOutput << "Get_Number_Of_Layers():" <<  Get_Number_Of_Layers()<<std::endl; 
        if (Get_Number_Of_Layers() != 0)
        {
        sOutput << "Get_Number_Of_AirGaps():" << 	Get_Number_Of_AirGaps()<<std::endl;
        sOutput << "GetInsideEmissivity():" <<	GetInsideEmissivity()<<std::endl;
        sOutput << "GetOutsideEmissivity():" <<	GetOutsideEmissivity()<<std::endl;
        sOutput << "GetInsideAbsorptivity():"	<< GetInsideAbsorptivity()<<std::endl;
        }
        sOutput << "*****Material List******\n";
        int iCounter = 0;
        for ( TMaterialListIter itrLHSMaterial = MaterialList.begin();
                itrLHSMaterial != MaterialList.end();
                itrLHSMaterial++)
        {
            sOutput << "Material #" << iCounter << std::endl;
            sOutput << itrLHSMaterial->StreamOut() << std::endl;
            iCounter++;
        }
        sOutput << "Glazing " << std::endl<< Glazing.StreamOut()<< std::endl;
        return sOutput.str();
    }


    /**
     * This returns the number of layers in the construction. The return is an int. 
     */
    int Get_Number_Of_Layers();

    /**
     * This returns the number of airgaps in the construction. The return is an int. 
     */
    int Get_Number_Of_AirGaps();

    /**
     * Get the inside emissivity of the total construction. Returns a double.
     */
    double GetInsideEmissivity();

    /**
     * Get the outside emissivity of the total construction. Returns a double.
     */
    double GetOutsideEmissivity();

    /**
     * Get the inside absorptivity of the total construction. Returns a double.
     */
    double GetInsideAbsorptivity();

    /**
     * Get the inside absorptivity of the total construction. Returns a double.
     */
    double GetOutsideAbsorptivity();

    /**
     * Set the current object to a fictious construction. This Deletes the current List of materials if already 
     * populated.
     * @param dUValue is a double representing the U-value of the consturction.
     * @param dAreaThermalMass is a double representing the Thermal mass of the construction.
     */
    void UseFictiousContruction(double dUValue, double dAreaThermalMass);
    void SetThermalPropertiesOfGlazing(std::string sGlazingID, bool IsASkylight);


    
    bool bIsEmptyConstruction();
};


TConstruction ScaleConstruction(TConstruction lhs, double rhs);
//---------------------------------------------------------------------------
#endif
