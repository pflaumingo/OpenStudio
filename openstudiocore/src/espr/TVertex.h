/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *           
 *                                                                 *
 ***************************************************************************/

//---------------------------------------------------------------------------

#ifndef TVERTEXH
#define TVERTEXH

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
/*std::string ToString(const double& val)
  {
  std::stringstream<char> strm;
  strm >> val;
  return strm.str();
  }
*/




/**
 * This class contains all information required for a vertex in ESP-r.
 */ 
class TVertex
{
public:

    /**
     * Default Contrcutor for a TVertex.
     * @param Xin X value 
     * @param Yin Y value
     * @param Zin Z value (up)
     * @return void.
     */
    TVertex(double Xin,double Yin,double Zin)
    {
        X=Xin;Y=Yin;Z=Zin;
    };

    /**
     * An overloaded equality operator for TVertex.. 
     * @param Vertex A TVertex co-ordinate.
     * @return true or flase depending on equality of X, Y, Z.
     */
    bool operator==(const TVertex Vertex) const
    {
        if (X == Vertex.X && Y == Vertex.Y && Z==Vertex.Z)
        {
            return true;
        }
        else
        {
            return false;
        };

    }

    /**
     * The X co-ordinate.
     */
    double X;

    /**
     * The Y co-ordinate.
     */
    double Y;

    /**
     * The Z co-ordinate.
     */ 
    double Z;
    std::string StreamOut()
    {

        std::stringstream sOutput;
        sOutput<< "X, Y, Z" << X << " "<<Y << " "<< Z<<std::endl;
        return sOutput.str();
    }

};
#endif

