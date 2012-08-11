#include "TMaterial.h"
TMaterial::TMaterial(
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
)

{
    sName = sNameIn;
    dConductivity = dConductivityIn;
    dDensity = dDensityIn;
    dSpecificHeat =dSpecificHeatIn;
    dThickness = dThicknessIn;
    iDpnd_type = iDpnd_typeIn;
    dRef_temp = dRef_tempIn;
    dTemp_factor = dTemp_factorIn;
    dMoisture_factor = dMoisture_factorIn;
    bIsAirGap = bIsAirGapIn;
    dAirGapResistance = dAirGapResistanceIn;
    dEmissivity= dEmissivityIn;
    dSolarAbsorptivity = dSolarAbsorptivityIn;

};
void   TMaterial::Set(
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

)

{
    sName = sNameIn;
    dConductivity = dConductivityIn;
    dDensity = dDensityIn;
    dSpecificHeat =dSpecificHeatIn;
    dThickness = dThicknessIn;
    iDpnd_type = iDpnd_typeIn;
    dRef_temp = dRef_tempIn;
    dTemp_factor = dTemp_factorIn;
    dMoisture_factor = dMoisture_factorIn;
    bIsAirGap = bIsAirGapIn;
    dAirGapResistance = dAirGapResistanceIn;
    dEmissivity= dEmissivityIn;
    dSolarAbsorptivity = dSolarAbsorptivityIn;
};




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














TMaterial& TMaterial::operator+( TMaterial& rhs)
{

    *this += rhs;
    return *this;
}

TMaterial& TMaterial::operator+=( TMaterial& rhs)
{

    dConductivity = dConductivity + rhs.dConductivity;
    dDensity = dDensity + rhs.dDensity;
    dSpecificHeat = dSpecificHeat + rhs.dSpecificHeat;
    dThickness = dThickness + rhs.dThickness;
    iDpnd_type = iDpnd_type + rhs.iDpnd_type;
    dRef_temp = dRef_temp + rhs.dRef_temp;
    dTemp_factor = dTemp_factor + rhs.dTemp_factor;
    dMoisture_factor =dMoisture_factor + rhs.dMoisture_factor;
    bIsAirGap = false;
    dAirGapResistance = dAirGapResistance + rhs.dAirGapResistance;
    dEmissivity= dEmissivity+ rhs.dEmissivity;
    dSolarAbsorptivity = dSolarAbsorptivity + rhs.dSolarAbsorptivity;

    return *this;
}

bool TMaterial::operator==( TMaterial& rhs)
{
	return (
    dConductivity == rhs.dConductivity &&
    dDensity == rhs.dDensity &&
    dSpecificHeat == rhs.dSpecificHeat &&
    dThickness == rhs.dThickness &&
    iDpnd_type == rhs.iDpnd_type &&
    dRef_temp == rhs.dRef_temp &&
    dTemp_factor ==rhs.dTemp_factor &&
    dMoisture_factor == rhs.dMoisture_factor &&
	bIsAirGap ==rhs.bIsAirGap &&
    dAirGapResistance == rhs.dAirGapResistance &&
    dEmissivity == rhs.dEmissivity &&
    dSolarAbsorptivity == rhs.dSolarAbsorptivity);

}

std::vector< TMaterial >& operator+=( std::vector< TMaterial >& lhs,  std::vector< TMaterial >& rhs)
{

    if (lhs.size() != rhs.size()) throw 11;

    TMaterialListIter itrRHSMaterial = rhs.begin();
    for ( TMaterialListIter itrLHSMaterial = lhs.begin();
            itrLHSMaterial != lhs.end();
            itrLHSMaterial++)
    {
        TMaterial* Material1= &*itrLHSMaterial;
        TMaterial* Material2= &*itrRHSMaterial;
        *Material1 += *Material2;
        itrRHSMaterial++;
    }
    return lhs;
}

//std::vector< TMaterial > operator=( std::vector< TMaterial > rhs)
//{
//
//	std::vector< TMaterial > MaterialList;
//	for ( TMaterialListIter itrRHSMaterial = rhs.begin();
//            itrRHSMaterial != rhs.end();
//            itrRHSMaterial++)
//            {
//
//            TMaterial Material2 = *itrRHSMaterial;
//            TMaterial MaterialResult = Material2;
//            MaterialList.push_back(MaterialResult);
//
//    }
//    return MaterialList;
//}


TMaterial& TMaterial::operator*(double rhs)
{

    dConductivity = dConductivity * rhs;
    dDensity = dDensity * rhs;
    dSpecificHeat = dSpecificHeat * rhs;
    dThickness = dThickness * rhs;
    iDpnd_type = 0;
    dRef_temp = dRef_temp * rhs;
    dTemp_factor = dTemp_factor * rhs;
    dMoisture_factor =dMoisture_factor * rhs;
    bIsAirGap = false;
    dAirGapResistance = dAirGapResistance * rhs;
    dEmissivity= dEmissivity* rhs;
    dEmissivity= dEmissivity* rhs;
    dSolarAbsorptivity = dSolarAbsorptivity * rhs;
    dSolarAbsorptivity =dSolarAbsorptivity * rhs;
    return *this;
}

TMaterial& TMaterial::operator*=(double rhs)
{

    dConductivity = dConductivity * rhs;
    dDensity = dDensity * rhs;
    dSpecificHeat = dSpecificHeat * rhs;
    dThickness = dThickness * rhs;
    iDpnd_type = 0;
    dRef_temp = dRef_temp * rhs;
    dTemp_factor = dTemp_factor * rhs;
    dMoisture_factor =dMoisture_factor * rhs;
    bIsAirGap = false;
    dAirGapResistance = dAirGapResistance * rhs;
    dEmissivity= dEmissivity* rhs;
    dEmissivity= dEmissivity* rhs;
    dSolarAbsorptivity = dSolarAbsorptivity * rhs;
    dSolarAbsorptivity =dSolarAbsorptivity * rhs;
    return *this;
}
std::vector< TMaterial >& operator*(  std::vector< TMaterial >& lhs,  double& rhs)
{
    for ( TMaterialListIter itrLHSMaterial = lhs.begin();
            itrLHSMaterial != lhs.end();
            itrLHSMaterial++)
    {
      //std::cout << "Material multiplication" << itrLHSMaterial->StreamOut() << " *  " << rhs << std::endl; 
      *itrLHSMaterial *= rhs;
      //std::cout << "Result =               " << itrLHSMaterial->StreamOut() << std::endl; 
    }
    return lhs;
}


std::vector< TMaterial >& operator*=(  std::vector< TMaterial >& lhs,  double& rhs)
{
    for ( TMaterialListIter itrLHSMaterial = lhs.begin();
            itrLHSMaterial != lhs.end();
            itrLHSMaterial++)
    {
      //std::cout << "Material multiplication" << itrLHSMaterial->StreamOut() << " *  " << rhs << std::endl; 
      *itrLHSMaterial *= rhs;
      //std::cout << "Result =               " << itrLHSMaterial->StreamOut() << std::endl; 
    }
    return lhs;
}

