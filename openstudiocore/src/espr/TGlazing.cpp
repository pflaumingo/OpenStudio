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
#include <boost/lexical_cast.hpp>
#include "regexp.h"
#include "TGlazing.h"
#include "TFileUtilities.h"

// define overloaded + (plus) operator
TOpticalSet&  TOpticalSet::operator+=(TOpticalSet& rhs)
{



    //Sum the transmissivity.
    TransmissionValues += rhs.TransmissionValues;

    // Sum the visible trans.
    dVisibleTransmission += rhs.dVisibleTransmission;
    AbsorptionSets += rhs.AbsorptionSets;

    return *this;
}


// define overloaded * (mult) operator
TOpticalSet&  TOpticalSet::operator*=( double& rhs)
{
  bool bdebug = false;

    //Scale the transmissivity.
    TransmissionValues *= rhs;


    // Scale the visible trans.
    if (bdebug) std::cerr << "before scale" << dVisibleTransmission << std::cerr;
    dVisibleTransmission *= rhs;
    if (bdebug) std::cerr << "after scale" << dVisibleTransmission << std::cerr;
    //Scale each of the absorption layers.
    std::vector< std::vector< double> >::iterator iter;
    for ( iter = AbsorptionSets.begin(); iter != AbsorptionSets.end(); iter++)
    {
        *iter *=rhs;

    }

    return *this;
}




TGlazing& TGlazing::operator+=(TGlazing& rhs)
{

  //std::cout << "LHS \n" << std::endl;
  //std::cout << StreamOut() << std::endl;
  //std::cout << "RHS \n" << std::endl;
  //std::cout << rhs.StreamOut() << std::endl;

    BlindsUp   += rhs.BlindsUp;
    BlindsDown += rhs.BlindsDown;
    return *this;
}

TGlazing& TGlazing::operator*=( double rhs)
{

    BlindsUp *= rhs;
    BlindsDown *= rhs;
    return *this;
}


TGlazing& TGlazing::operator*( double rhs)
{

    BlindsUp *= rhs;
    BlindsDown *= rhs;
    return *this;
}



TGlazing& TGlazing::operator=( const TGlazing& rhs)
{
		if (this != &rhs) // protect against invalid self-assignment
        {

    bIsThereGlazing = rhs.bIsThereGlazing;
    BlindsUp   = rhs.BlindsUp;
    BlindsDown = rhs.BlindsDown;
		}
    return *this;

}




/**
 * This method given a glazing id number will read in a glazing file and create a glazing 
 * object. All glazing data file live in the Daylight_engine/SkyVisionFiles folder. 
 * @param sGlazingType is the ID number of the glazing as provided by Aziz. 
 * @return Glazing object. 
 */


void TGlazing::SetGlazingFromDatabase(std::string sGlazingID, bool IsASkylight)
{
    // Determine if there is a blind present. The sytax for this is if there is a trailing 'b'
    // in the glazing ID.

    std::vector< std::string > vsIDMatch =  RegexpMatch("(\\d+)(\\D*)", sGlazingID);

    bool bBlinds = false;
    std::string sGlazingNumber;
    // Check if regexp failed.
    if ( vsIDMatch.size() <= 0 )
    {
        std::cerr << "GlazingID "<<  sGlazingID << "is invalid" << std::endl;
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


    //std::cerr << "Glazing file used" << sGlazingFile << std::endl;;

	openstudio::path GlazingPath = openstudio::toPath(sGlazingFile);
    std::vector<std::string> vsGlazingFile =read_file_into_vector( GlazingPath)  ;
    //Need 5 lines of data from glazing database file. (sample)
    //   0.59686    0.56802    0.51980    0.48806    0.37220    0.78587
    //   0.29140    0.31510    0.33064    0.33416    0.33184
    //   0.02470    0.06639 2710.00000  837.00000    0.84000    0.84000
    //   0.29750    0.11762    0.03475    0.03190    0.02315    0.39459
    //   0.53124    0.58106    0.63462    0.61808    0.54463
    //   0.02470    0.06639 2710.00000  837.00000    0.84000    0.84000



    //Line one.
    std::vector<double> vdList0 =ToDouble( Tokenizer(vsGlazingFile[0]," ") );


    // For loop for Transmission values. 0-4
    for (int iCounter = 0 ; iCounter < 5 ; iCounter++)
    {
        BlindsUp.TransmissionValues.push_back(vdList0[iCounter]);
    }
    BlindsUp.dVisibleTransmission = vdList0[5];

    //Line two
    std::vector<double> vdList1 =ToDouble( Tokenizer(vsGlazingFile[1]," ") );

    //  Set Absorption values.
    std::vector<double> AbsorptionSet2;
    for (int iCounter = 0 ; iCounter < 5 ; iCounter++)
    {
        AbsorptionSet2.push_back(vdList1[iCounter]);
    }
    BlindsUp.AbsorptionSets.push_back(AbsorptionSet2);

    if (!bBlinds) 	 
      { 	 
	BlindsDown.TransmissionValues = BlindsUp.TransmissionValues; 	 
	BlindsDown.dVisibleTransmission =       BlindsUp.dVisibleTransmission; 	       BlindsDown.AbsorptionSets =     BlindsUp.AbsorptionSets; 	 
      } 	 
    else 	 
      {





        //Repeat above. Forget about duplicate last line.
        std::vector<double> vdList3 =ToDouble( Tokenizer(vsGlazingFile[3]," ") );
        // For loop for Transmission values. 0-4
        for (int iCounter = 0 ; iCounter < 5 ; iCounter++)
        {
            BlindsDown.TransmissionValues.push_back(vdList3[iCounter]);
        }
        BlindsDown.dVisibleTransmission = vdList3[5];

        std::vector<double> vdList4 =ToDouble( Tokenizer(vsGlazingFile[4]," ") );

        //  Set Absorption values.
        AbsorptionSet2.clear();
        for (int iCounter = 0 ; iCounter < 5 ; iCounter++)
        {
            AbsorptionSet2.push_back(vdList4[iCounter]);
        }
        BlindsDown.AbsorptionSets.push_back( AbsorptionSet2 );
    
      }


}


std::string TGlazing::StreamOut()
    {
        std::stringstream sOutput;
        sOutput << "*****Glazing Object*****" << std::endl;
		sOutput << "bIsThereGlazing " << boost::lexical_cast<std::string>(bIsThereGlazing)<< std::endl;
        if (bIsThereGlazing)
        {
            sOutput << "TOptical BlindsUp" << std::endl;
            sOutput << BlindsUp.StreamOut() << std::endl;
            sOutput << "TOptical BlindsDown"<< std::endl;
            sOutput << BlindsDown.StreamOut() << std::endl;
        }
        return sOutput.str();
    }

