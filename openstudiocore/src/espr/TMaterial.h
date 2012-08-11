#ifndef TMATERIALH
#define TMATERIALH

#include<string>
#include<vector>
#include<map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>


class TMaterial
{
public:
    std::string sName;
    double dConductivity;
    double dDensity;
    double dSpecificHeat;
    double dThickness;
    int    iDpnd_type;
    double dRef_temp;
    double dTemp_factor;
    double dMoisture_factor;
    bool   bIsAirGap;
    double dAirGapResistance;
	double dEmissivity;
	double dSolarAbsorptivity;



    TMaterial (){

        Initialize();

    };

    void Initialize()
    {
        Set( "empty",
             0.0,
             0.0,
             0.0,
             0.0,
             0,
             0,
             0.0,
             0.0,
             false,
             0.0,
             0.0,
             0.0
           );

    };

    TMaterial(
        std::string sNameIn,
        double dConductivityIn,
        double dDensityIn,
        double dSpecificHeatIn,
        double dThicknessIn,
        int    iDpnd_typeIn,
        double dRef_tempIn,
        double dTemp_factorIn,
        double dMoisture_factorIn,
        bool   bIsAirGapIn,
        double dAirGapResistanceIn,
        double dIEmissivityIn,
        double dSolarAbsorptivityIn
    );



    void   Set(
        std::string sNameIn,
        double dConductivityIn,
        double dDensityIn,
        double dSpecificHeatIn,
        double dThicknessIn,
        int    iDpnd_typeIn,
        double dRef_tempIn,
        double dTemp_factorIn,
        double dMoisture_factorIn,
        bool   bIsAirGapIn,
        double dAirGapResistanceIn,
        double dEmissivityIn,
        double dSolarAbsorptivityIn
    );


    void MakeAirGap( double dResistance )
    {

        Set(
            "airgap",
            0.0000,
            0.0000,
            0.0000,
            0.0010,
            0,
            0.0000,
            0.0000,
            0.0000,
            true,
            dResistance,
            0.0000,
            0.0000
        );
    };

    void MakeMaterial(std::string sMaterialName, double dThickness)
    {
        if ("plywood" == sMaterialName)
        {
            Set( "plywood",
                 0.1500,
                 700.0000,
                 1420.0000,
                 dThickness,
                 0,
                 0.0000,
                 0.0000,
                 0.0000,
                 false,
                 0.0000,
                 0.9300,
                 0.7000
               );
        }
        else if("paviour_brick" == sMaterialName)
        {
            Set( "paviour_brick",
                 0.9600,
                 2000.0000,
                 840.0000,
                 dThickness,
                 0,
                 0.0000,
                 0.0000,
                 0.0000,
                 false,
                 0.0000,
                 0.9300,
                 0.7000
               );
        }
        else if("chipboard" ==sMaterialName)
        {
            Set( "chipboard",
                 0.1500,
                 800.0000,
                 2093.0000,
                 dThickness,
                 0,
                 0.0000,
                 0.0000,
                 0.0000,
                 false,
                 0.0000,
                 0.9100,
                 0.6500
               );
        }






    };
    TMaterial& operator*(double rhs) ;
    TMaterial& operator*=(double rhs);
    TMaterial& operator+( TMaterial& rhs);
    TMaterial& operator+=( TMaterial& rhs);
	bool operator==( TMaterial& rhs);



    std::string StreamOut()
    {
        std::stringstream sOutput;
        sOutput << "******Material Data**********\n";
        sOutput <<"sName "<<sName << std::endl;
        sOutput <<"dDensity "<< dDensity<< std::endl;
        sOutput <<"dConductivity "<< dConductivity<< std::endl;
        sOutput <<"dSpecificHeat "<<dSpecificHeat << std::endl;
        sOutput <<"dThickness "<< dThickness<< std::endl;
        sOutput <<"iDpnd_type "<<iDpnd_type << std::endl;
        sOutput <<"dRef_temp "<<dRef_temp << std::endl;
        sOutput <<"dTemp_factor "<<dTemp_factor << std::endl;
        sOutput <<"dMoisture_factor "<<dMoisture_factor << std::endl;
        sOutput <<"bIsAirGap "<< bIsAirGap<< std::endl;
        sOutput <<"dAirGapResistance "<<dAirGapResistance << std::endl;
        sOutput <<"dEmissivity"<<dEmissivity<< std::endl;
        sOutput <<"dSolarAbsorptivity "<<dSolarAbsorptivity << std::endl;
        return sOutput.str();
    }







};







typedef std::vector< TMaterial >::iterator TMaterialListIter;
std::vector< TMaterial >& operator+=( std::vector< TMaterial >& lhs,  std::vector< TMaterial >& rhs);
std::vector< TMaterial >& operator*( std::vector< TMaterial >& lhs,  double rhs);
std::vector< TMaterial >& operator*=(  std::vector< TMaterial >& lhs,  double& rhs);


//---------------------------------------------------------------------------
#endif
