
#ifndef TGLAZINGH
#define TGLAZINGH

/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *           
 *                                                                         *
 ***************************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Templates.h"
#include "TStringify.h"
//typedef std::vector<double> TAbsorptionSet;
//typedef std::vector< TAbsorptionSet > TAbsorptionSets;


/**
 * This class contains the optical data for a surface. Only surface types of 
 * glazing may have optical properties.
 * 
 */
class TOpticalSet
{
public:
    /**
     * Transmission values for each angle. Contained in a vector of doubles.
     */
    std::vector< double > TransmissionValues;

    /**
     * The visible transmission of the glazing.
     */  
    double dVisibleTransmission;

    /**
     * The Absorbtion values for each layer for each angle. (Vector of vector of doubles).
     */
    std::vector< std::vector<double> > AbsorptionSets;


    TOpticalSet&  operator+=( TOpticalSet& rhs);
    TOpticalSet&  operator*=( double& rhs);

    std::string StreamOut()
    {
        std::stringstream sOutput;
        sOutput << "******TOpticalSet******" << std::endl;
        sOutput << "Visible Tranmission Value " << dVisibleTransmission << std::endl;
        sOutput << "Transmission Values " << std::endl;
        sOutput << StreamOutVector(TransmissionValues) <<std::endl;
        sOutput <<"AbsorptionSets"<< std::endl;
        sOutput << StreamOutVector(AbsorptionSets) <<std::endl;
        sOutput << "******End TOpticalSet******" << std::endl;
        return sOutput.str();

    }

};

/**
 * This class contains the optical data sets for a glazing. This is to supplement the data from TSurface.
 * For now there is only two Optical sets. One for blinds up and down..In the future, there could be 
 * more scenarios added. But will require a better control strategy.
 * 
 */
class TGlazing
{
public:
    /**
     * Flag for glazing presence.
     */
    bool bIsThereGlazing;
    /**
     * The optical set for blinds up.
     */ 
    TOpticalSet BlindsUp;
    /**
     * The optical set for blinds down. 
     */ 
    TOpticalSet BlindsDown;

    void  SetGlazingFromDatabase(std::string sGlazingID, bool IsASkylight);

    TGlazing()
    {
        bIsThereGlazing = false;
    };

	TGlazing& operator=( const TGlazing& other);
    TGlazing& operator+=( TGlazing& rhs);
    TGlazing& operator*=( double rhs);
    TGlazing& operator*( double rhs);
    std::string StreamOut();

};








//---------------------------------------------------------------------------
#endif
