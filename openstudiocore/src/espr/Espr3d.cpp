// ---------------------------------------------	// Espr3dD.cpp : H3K/ESP-r 3D library
#include "stdafx.h"										// Required for PCH (Pre Compiled Headers)
#include "Espr3d.h"

//IMPLEMENT_SERIAL(Vertex3D, CObject, VERSIONABLE_SCHEMA|0)

namespace _espR
{
	/*
	// -------------------------------------------- // Local helper methods
	static void FileVersionError(CString const & objectType, int nFileVersion)
	{
		CString msgStr;
      msgStr.Format("INTERNAL ERROR: Problem deserializing ESP-r %s data - file version %d not supported.", objectType, nFileVersion);
      AfxMessageBox(msgStr);
	}
	*/
}



// -------------------------------------------- // genreral math fucntions

void solvePolynomial(									// Solve polynomial ax2 + bx + c == 0
	const double & va, 
	const double & vb, 
	const double & vc,
	vector<double> & res )
{
	double delta; // discriminant -> delta = b² - 4ac for polynomial ax² + bx+ c=0

	delta = ( vb * vb ) - ( 4 * va * vc );

	// If delta > 0, then there are two distinct roots, both of which are real numbers.
	if( delta >= 0 )
	{
		if( delta > 0 )
		{ 
			res.push_back( ( -vb - sqrt(delta) ) / ( 2 * va ) ); 
			res.push_back( ( -vb + sqrt(delta) ) / ( 2 * va ) ); 

		}

		// If delta == 0, then there is exactly one distinct real root
		// x = -( b / 2a )
		if( delta == 0 )
		{ 
			res.push_back( - (vb / 2 * va) );
		}
	}

	// If delta < 0, then there are no real roots.
	// return 999
	else 
	{ 
		res.push_back( -999.0 );
	}
}

int timesNHigh(											// check how many components of V are higher then n
	int n,
	vector<int> &V )
{
	int c = 0 ; // counter

	if( V.size() == 0 ) return (c);
	else
	{	
		for( unsigned int i = 0; i < V.size(); i++ )
		{
			if ( V[i] > n ) 
			{
				c++;
				V[i]++;
			}	
		}
		return (c);
	}
}


// -------------------------------------------- // VECTOR3D class

Vector3D::Vector3D()										// constructor
{
	vx = 0.0;
	vy = 0.0;
	vz = 0.0;
}

Vector3D::Vector3D(										// copy constructor
	const Vector3D & V )									// vector V
{
	vx = V.vx;
	vy = V.vy;
	vz = V.vz;
}

Vector3D::Vector3D(										// constructor with arguments
	const double & x,										// Z-axis coordinate
	const double & y,										// Z-axis coordinate
	const double & z )									// Z-axis coordinate
{
	vx = x;
	vy = y;
	vz = z;
}

double & Vector3D::operator [] (						// acces/modify components 1(x), 2(y) or 3(z) of 3D vector
	const int & i )										// iterator
{
	if( i == 1 ) return vx;
	if( i == 2 ) return vy;
	else return vz;
}

const double & Vector3D::operator [] (				// acces - without modification - components 1(x), 2(y) or 3(z) of 3D vector
	const int & i ) const								// iterator
{
	if( i == 1 ) return vx;
	if( i == 2 ) return vy;
	else return vz;
}

Vector3D & Vector3D::operator = (					// assinment operator
	const Vector3D & Q )									// vector Q
{
	if( this != &Q )
	{
		vx = Q.vx;
		vy = Q.vy;
		vz = Q.vz;
	}
	return *this;
}

bool Vector3D::operator == (							// compare V to current vector; returns true if same vector
	const Vector3D & V ) const											
{
	if( equals( vx, V.vx ) &&  equals( vy, V.vy ) && equals( vz, V.vz ) ) return true;
	else return false;
}

bool Vector3D::operator != (							// compare V to current vector;returns true if different vector
	const Vector3D & V ) const											
{
	if( ! equals( vx, V.vx ) || ! equals( vy, V.vy ) || ! equals( vz, V.vz ) ) return true;
	else return false;
}

double Vector3D::operator * (							// calculates dot product of 3D vector V and current 3D vector
	const Vector3D & V ) const							// vector V
{
	return vx * V.vx + vy * V.vy + vz * V.vz;
}

Vector3D Vector3D::operator * (							// calculates dot product of 3D vector V and current 3D vector
	double S ) const							// vector V
{
	Vector3D P = *this;
	Vector3D R;
	R[1] = S * P[1];
	R[2] = S * P[2];
	R[3] = S * P[3];
	return R;
}

const Vector3D Vector3D::operator + (				// calculates sum of current 3D vector + 3D vector V
	const Vector3D & V ) const							// vector V
{
	Vector3D P = *this;
	P.vx = vx + V.vx;
	P.vy = vy + V.vy;
	P.vz = vz + V.vz;
	return P;
}

const Vector3D Vector3D::operator - (				// calculates difference between current 3D vector & 3D vector V
	const Vector3D & V ) const							// vector V
{
	Vector3D P = *this;
	P.vx = vx - V.vx;
	P.vy = vy - V.vy;
	P.vz = vz - V.vz;
	return P;
}

void Vector3D::Normalize ()							// Normalize current vector
{ 
	double l;
	Vector3D vnul(0,0,0);								// null vector

	if( *this != vnul) 
	{
		l = Norm( *this );
		this->vx  =  this->vx / l ;
		this->vy  =  this->vy / l ;
		this->vz  =  this->vz / l ;
	}

}

void Vector3D::Invert ()							// Invertcurrent vector
{ 
	Vector3D vnul(0,0,0);								// null vector

	if( *this != vnul) 
	{
		this->vx  = - ( this->vx ) ;
		this->vy  = - ( this->vy ) ;
		this->vz  = - ( this->vz ) ;
	}

}

double Vector3D::CalcAngle(						// Calculates angle between current vector and vector V
	const Vector3D & V )

{
						
	float aA = 0.0;										// angle 
	float CosA = 0.0;									// Cos angle 

	// cos (aOrient) = (vProj * vSouth) / (|vProj| * |vSouth|)
	CosA = (float)( *this * V ) / ( (float)Norm( *this ) * (float)Norm( V ) );
	aA = acos( CosA );

	// convert radians to degrees
	// degre = 180 * (radian) / pi 
	aA = (float)180.0 * aA / (float) espR::PI  ;

	return ( aA ) ;
}

Vector3D Cross_product(									// calculates cross product between 3D vectors P and Q
	Vector3D P,												// vector P
	Vector3D Q )											// vector Q
{
	Vector3D R( P.vy * Q.vz - P.vz * Q.vy, P.vz * Q.vx - P.vx * Q.vz, P.vx * Q.vy - P.vy * Q.vx );
	return R;
}

double Norm(												// calculates norm of 3D vector P
	Vector3D P )											// vector P
{
	double sum = P.vx * P.vx + P.vy * P.vy + P.vz * P.vz;
	return ( double ) sqrt( sum );
}

/*
const Vector3D operator * (							// calculates scalar product of 3D vector V and scalar S
	const double & S,										// scalar
	Vector3D & V )											// vector V
{
	Vector3D R;
	R[1] = S * V[1];
	R[2] = S * V[2];
	R[3] = S * V[3];
	return R;
}

Vector3D Scalar_product(							// calculates scalar product of 3D vector V and scalar S
	double S,										// scalar
	Vector3D & V )											// vector V
{
	Vector3D R;
	R[1] = S * V[1];
	R[2] = S * V[2];
	R[3] = S * V[3];
	return R;
}

*/

Vector3D::~Vector3D()									// destructor
{
}


// -------------------------------------------- // VERTEX3D class

Vertex3D::Vertex3D()										// constructor; creates a vertex at the origin
{
	vx = 0.0;
	vy = 0.0;
	vz = 0.0;
}

Vertex3D::Vertex3D(										// copy constructor
	const Vertex3D & V )									// vertex V
{
	vx = V.vx;
	vy = V.vy;
	vz = V.vz;
}

Vertex3D::Vertex3D(										// creates a vertex at x,y,z
	const double & x,										// X-axis coordinate
	const double & y,										// Y-axis coordinate
	const double & z )									// Z-axis coordinate
{
	vx = x;
	vy = y;
	vz = z;
}

double & Vertex3D::operator [] (						// acces/modify components 1(x), 2(y) or 3(z) of current 3D vertex
	const int & i )										// iterator
{
	if( i == 1 ) return vx;
	if( i == 2 ) return vy;
	else return vz;
}

const double & Vertex3D::operator [] (				// acces - without modification - components 1(x), 2(y) or 3(z) of current 3D vertex
	const int & i ) const								// iterator
{
	if( i == 1 ) return vx;
	if( i == 2 ) return vy;
	else return vz;
}

Vertex3D & Vertex3D::operator = (					// assignment operator
	const Vertex3D & P )
{
	if( this != &P )
	{
		vx = P.vx;
		vy = P.vy;
		vz = P.vz;
	}
	return *this;
}

bool Vertex3D::operator == (							// compare P to current vertex; returns true if same vertex
	const Vertex3D & P2 ) const						// vertex P2
{
	if( equals( vx, P2.vx ) && equals( vy, P2.vy ) && equals( vz, P2.vz ) ) return true;
	else return false;
}

bool Vertex3D::operator != (							// compare P to current vertex;returns true if different vertex
	const Vertex3D & P2 ) const						// vertex P2
{
	if( ! equals( vx, P2.vx ) || ! equals( vy, P2.vy ) || ! equals( vz, P2.vz ) ) return true;
	else return false;
}

const Vector3D Vertex3D::operator - (				// calculates the difference between current vertex and vertex P
	const Vertex3D & P )	const							// vertex P
{
	Vector3D Q;
	Q[1] = vx - P.vx;
	Q[2] = vy - P.vy;
	Q[3] = vz - P.vz;
	return Q;
}

const Vertex3D Vertex3D::operator + (				// calculates the sum of current vertex and 3d vector V
	Vector3D V ) const									//	vector V
{
	Vertex3D Q = *this;
	Q.vx = vx + V[1];
	Q.vy = vy + V[2];
	Q.vz = vz + V[3];
	return Q;
} 

void Vertex3D::translation(							// Apply translation to current surface
	const double & tX,									// X translation
	const double & tY,									// Y translation
	const double & tZ )									// Z translation
{
	Array2D<double> Tr(4,4);							// Translation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);								// original vertex
	
	P[0][0] = this->vx;
	P[1][0] = this->vy;
	P[2][0] = this->vz;
	P[3][0] = 1;

	Tr[0][0] = 1 ;
	Tr[0][1] = 0;
	Tr[0][2] = 0;
	Tr[0][3] = tX;

	Tr[1][0] = 0;
	Tr[1][1] = 1;
	Tr[1][2] = 0;
	Tr[1][3] = tY;

	Tr[2][0] = 0;
	Tr[2][1] = 0;
	Tr[2][2] = 1;
	Tr[2][3] = tZ;
	
	Tr[3][0] = 0;
	Tr[3][1] = 0;
	Tr[3][2] = 0;
	Tr[3][3] = 1;

	//Apply transformation matrix to vertex
	P = matmult(Tr, P);			
				
	this->vx = P[0][0];
	this->vy = P[1][0];
	this->vz = P[2][0];
}

void Vertex3D::rotateX(			// rotate surface around X axis 
	const double & angle )
{
	Array2D<double> Rot(4,4);	// rotation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	double ang = (angle * (espR::PI) /180);	

	P[0][0] = this->vx;
	P[1][0] = this->vy;
	P[2][0] = this->vz;
	P[3][0] = 1;		

	Rot[0][0] = 1;
	Rot[0][1] = 0;
	Rot[0][2] = 0;
	Rot[0][3] = 0;

	Rot[1][0] = 0;
	Rot[1][1] = cos ( ang );
	Rot[1][2] = -sin ( ang );
	Rot[1][3] = 0;

	Rot[2][0] = 0;
	Rot[2][1] = sin ( ang );
	Rot[2][2] = cos ( ang );
	Rot[2][3] = 0;
	
	Rot[3][0] = 0;
	Rot[3][1] = 0;
	Rot[3][2] = 0;
	Rot[3][3] = 1;				
				
	//Apply transformation matrix to vertex
	P = matmult(Rot, P);
	
	this->vx = P[0][0];
	this->vy = P[1][0];
	this->vz = P[2][0];	
}

void Vertex3D::rotateY(			// rotate surface around Y axis 
	const double & angle )
{
	Array2D<double> Rot(4,4);	// rotation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	double ang = (angle * (espR::PI) /180);	
	
	P[0][0] = this->vx;
	P[1][0] = this->vy;
	P[2][0] = this->vz;
	P[3][0] = 1;

	Rot[0][0] = cos ( ang );
	Rot[0][1] = 0;
	Rot[0][2] = sin ( ang );
	Rot[0][3] = 0;

	Rot[1][0] = 0;
	Rot[1][1] = 1;
	Rot[1][2] = 0;
	Rot[1][3] = 0;

	Rot[2][0] = -sin ( ang );
	Rot[2][1] = 0;
	Rot[2][2] = cos ( ang );
	Rot[2][3] = 0;
	
	Rot[3][0] = 0;
	Rot[3][1] = 0;
	Rot[3][2] = 0;
	Rot[3][3] = 1;

	//Apply transformation matrix to vertex
	P = matmult(Rot, P);
	
	this->vx = P[0][0];
	this->vy = P[1][0];
	this->vz = P[2][0];
}

void Vertex3D::rotateZ(			// rotate surface around Z axis 
	const double & angle )
{
	Array2D<double> Rot(4,4);	// rotation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	double ang = (angle * (espR::PI) /180);	
	
	P[0][0] = this->vx;
	P[1][0] = this->vy;
	P[2][0] = this->vz;
	P[3][0] = 1;

	Rot[0][0] = cos ( ang );
	Rot[0][1] = -sin ( ang );
	Rot[0][2] = 0;
	Rot[0][3] = 0;

	Rot[1][0] = sin ( ang );
	Rot[1][1] = cos ( ang );
	Rot[1][2] = 0;
	Rot[1][3] = 0;

	Rot[2][0] = 0;
	Rot[2][1] = 0;
	Rot[2][2] = 1;
	Rot[2][3] = 0;
	
	Rot[3][0] = 0;
	Rot[3][1] = 0;
	Rot[3][2] = 0;
	Rot[3][3] = 1;

	//Apply transformation matrix to vertex
	P = matmult(Rot, P);
	
	this->vx = P[0][0];
	this->vy = P[1][0];
	this->vz = P[2][0];
} 

bool Vertex3D::Compare_vertex3D_xplus(				// compares 2 vertex according to their x value (returns true if P1x > P2x)
	const Vertex3D & P1,									// vertex P1
	const Vertex3D & P2 )								// vertex P2
{
	return( lessThan( P1.vx, P2.vx ) );
}

bool Vertex3D::Compare_vertex3D_xminus(			// compares 2 vertex according to their x value (returns true if P1x < P2x)
	const Vertex3D & P1,									// vertex P1
	const Vertex3D & P2 )								// vertex P2
{
	return( greaterThan( P1.vx, P2.vx ) );
}

bool Vertex3D::Compare_vertex3D_yplus(				// compares 2 vertex according to their y value (returns true if P1y > P2y)
	const Vertex3D & P1,									// vertex P1
	const Vertex3D & P2 )								// vertex P2
{
	return( lessThan( P1.vy, P2.vy ) );
}

bool Vertex3D::Compare_vertex3D_yminus(			// compares 2 vertex according to their y value (returns true if P1y < P2y)
	const Vertex3D & P1,									// vertex P1
	const Vertex3D & P2 )								// vertex P2
{
	return( greaterThan( P1.vy, P2.vy ) );
}

bool Vertex3D::Compare_vertex3D_zplus(				// compares 2 vertex according to their y value (returns true if P1y > P2y)
	const Vertex3D & P1,									// vertex P1 
	const Vertex3D & P2 )								// vertex P2 
{
	return( lessThan( P1.vz, P2.vz ) );
}

bool Vertex3D::Compare_vertex3D_zminus(			// compares 2 vertex according to their y value (returns true if P1y < P2y)
	const Vertex3D & P1,									// vertex P1 
	const Vertex3D & P2 )								// vertex P2 
{
	return( greaterThan( P1.vz, P2.vz ) );
}

double Vertex3D::Calculate_distance(
	const Vertex3D & P1 ) const
{
	double dx;
	double dy;
	double dz;

	dx = vx - P1.vx;
	dy = vy - P1.vy;
	dz = vz - P1.vz;

	return( sqrt ( ( dx * dx ) + ( dy * dy ) + ( dz * dz) ) );
}

/*void Vertex3D::Serialize(CArchive& ar)
{
   CObject::Serialize(ar);
   if (ar.IsStoring())
   {
      ar << vx;
      ar << vy;
      ar << vz;
   }
   else
   {
      int nVersion = ar.GetObjectSchema();

      ar >> vx;
      ar >> vy;
      ar >> vz;

      switch(nVersion)
      {
      case -1:
      case 0:
         break;
      default:
         _espR::FileVersionError("Vertex3D", nVersion);
         break;
      }
   }
}

TiXmlElement* Vertex3D::GetXML()
{
	TiXmlElement* base = new TiXmlElement(GetTagName());

    AddElement(base, XML("vx", vx));
    AddElement(base, XML("vy", vy));
    AddElement(base, XML("vz", vz));

    return base;
}

void Vertex3D::FromXML(TiXmlElement* element)
{
   // 07-Mar-2011 BAL: changed to floating point!!!
    vx = GetChildAsFloat(element, "vx");
    vy = GetChildAsFloat(element, "vy");
    vz = GetChildAsFloat(element, "vz");
}
*/

// -------------------------------------------- // Line3D class

Line3D::Line3D()
{
	// TODO Auto-generated constructor stub
}

Line3D::Line3D(											// Creates a 3D line starting at Vertex3D P and ending at Vertex3D Q
	const Vertex3D & P,
	const Vertex3D & Q )
{
	Start = P ;
	End = Q;
}

void Line3D::setStart(									// Sets starting vertex at S
	const Vertex3D & S )
{
	Start = S;
}

void Line3D::setStart(									// Sets starting vertex at Sx,Sy,Sz
	const double & Sx,
	const double & Sy,
	const double & Sz )
{
	Start[1]= Sx;
	Start[2]= Sy;
	Start[3]= Sz;
}

void Line3D::setLine(									// Sets current Line from S to E			
	const Vertex3D & S,
	const Vertex3D & E )
{
	this->setStart(S);
	this->setEnd(E);
}

void Line3D::setEnd(										// Sets end vertex at E
	const Vertex3D & E )
{
	End = E;
}

void Line3D::setEnd(										// Sets end vertex at Ex,Ey,Ez
	const double & Ex,
	const double & Ey,
	const double & Ez )
{
	End[1]= Ex;
	End[2]= Ey;
	End[3]= Ez;
}

Vertex3D Line3D::getStart() const					// Returns Starting Vertex3D
{
	return Start;
}

Vertex3D Line3D::getEnd() const						// Returns Ending Vertex3D
{
	return End;
}

Vertex3D Line3D::getMidPoint() const				// Returns Ending Vertex3D
{
	Vertex3D mid;

	double dx = (End[1] - Start[1]) / 2.0 ;
	double dy = (End[2] - Start[2]) / 2.0 ;
	double dz = (End[3] - Start[3]) / 2.0 ;

	mid[1] = Start[1] + dx;
	mid[2] = Start[2] + dy;
	mid[3] = Start[3] + dz;  

	return (mid);
}

double Line3D::getLength() const						// Calculates & returns lenght of the current line
{	
	double a = End[1] - Start[1];
	double b = End[2] - Start[2];
	double c = End[3] - Start[3];

	return ( sqrt ( (a*a) + (b*b) + (c*c) ) );
}

bool Line3D::isLnParral(								// Returns true if L is || to current Line
	Line3D L ) const
{
	double dx1;
	double dy1;
	double dz1;

	double dx2;
	double dy2;
	double dz2;

	dx1 = this->getEnd()[1] - this->getStart()[1] ;
	dy1 = this->getEnd()[2] - this->getStart()[2] ;
	dz1 = this->getEnd()[3] - this->getStart()[3] ;

	// create 2 vectors with lines
	Vector3D V1( dx1, dy1, dz1 );

	dx2 = L.getEnd()[1] - L.getStart()[1];
	dy2 = L.getEnd()[2] - L.getStart()[2];
	dz2 = L.getEnd()[3] - L.getStart()[3];

	Vector3D V2( dx2, dy2, dz2 );

	// calculate angle  between V1 & V2
	double CosA = ( V1 * V2 ) / ( Norm (V1) * Norm (V2) );
		
	// if fabs of CosA == 1.0 the 2 lines are ||
	if ( equals( fabs(CosA) , 1.0 )) return true;
	else return false;
}

bool Line3D::doLineCross(								// Returns true if L crosses current Line
	const Line3D & L ) const
{
	Vector3D V1;
	Vector3D V2;
	
	double t1 =0;
	double t2 =0;

	Vector3D Int;
	Vector3D Int2;
	
	if( this->isLnParral( L ) == true ) return false;
	else
	{
		V1 = this->End - this->Start;
		V2 = L.End - L.Start;

		if( equals( V1[2],0 ) && equals( V2[2],0 ) )
		{
			t1 = ( ( -V2[3] *
				    ( this->Start[1] - L.Start[1] ) ) +
					 ( V2[1] *
					 ( this->Start[3] - L.Start[3] ) ) ) /
				  ( ( - V2[3] * - V1[1]) + (V2[1] * - V1[3] ) );
			t2 = ( ( -V1[3] *
				    ( L.Start[1] - this->Start[1] ) ) +
					 ( V1[1] * ( L.Start[3] - this->Start[3] ) ) ) /
				  ( ( -V1[3] * - V2[1] ) + ( V1[1] * - V2[3] ) );
		}
		
		else 
		{
			if( equals (V1[1],0) && equals (V2[1],0) )
			{
				t1 = ((-V2[3]* (this->Start[2] - L.Start[2])) + (V2[2]* (this->Start[3] - L.Start[3])))/ ((- V2[3] * - V1[2]) + (V2[2] * - V1[3]));
				t2 = ((-V1[3]* (L.Start[2] - this->Start[2])) + (V1[2]* (L.Start[3] - this->Start[3])))/ ((- V1[3] * - V2[2]) + (V1[2] * - V2[3]));
			}

			else 
			{	
				t1 = ((-V2[2]* (this->Start[1] - L.Start[1])) + (V2[1]* (this->Start[2] - L.Start[2])))/ ((- V2[2] * - V1[1]) + (V2[1] * - V1[2]));
				t2 = ((-V1[2]* (L.Start[1] - this->Start[1])) + (V1[1]* (L.Start[2] - this->Start[2])))/ ((- V1[2] * - V2[1]) + (V1[1] * - V2[2]));
			}
		}

		Int[1] = this->Start[1] + V1[1] * t1;
		Int[2] = this->Start[2] + V1[2] * t1;
		Int[3] = this->Start[3] + V1[3] * t1;	

		Int2[1] = L.Start[1] + V2[1] * t2;
		Int2[2] = L.Start[2] + V2[2] * t2;
		Int2[3] = L.Start[3] + V2[3] * t2;

		if ( Int != Int2 ) return (false);
		else return (true);
	}
}

void Line3D::getIntersection(						// Calculates & returns intersection between current line & line L  
	Line3D & L,
	Vertex3D & Int)
{
	Vector3D V1;
	Vector3D V2;
	
	double t1 =0;
	double t2 =0;

	V1 = this->End - this->Start;
	V2 = L.End - L.Start;

	// Int[1] = this->Start[1] + V1[1] * t1;
	// Int[2] = this->Start[2] + V1[2] * t1;
	// Int[3] = this->Start[3] + V1[3] * t1;

	// Int[1] = L.Start[1] + V2[1] * t2;
	// Int[2] = L.Start[2] + V2[2] * t2;
	// Int[3] = L.Start[3] + V2[3] * t2;

	// this->Start[1] + V1[1] * t1 = L.Start[1] + V2[1] * t2;
	// this->Start[2] + V1[2] * t1 = L.Start[2] + V2[2] * t2;

	// this->Start[1] - L.Start[1] = (V2[1] * t2) - (V1[1] * t1);
	// this->Start[2] - L.Start[2] = (V2[2] * t2) - (V1[2] * t1);

	if( equals ( V1[2], 0 ) && equals ( V2[2], 0 ) )
	{
		// Use z & x instead of y & x
		// multiply first equation by (- V2[3]) and second by (V2[1])
		// we get:
		// -V2[3]* (this->Start[1] - L.Start[1]) = - V2[3] * - (V1[1] * t1);
		// V2[1]* (this->Start[3] - L.Start[3]) =   V2[1] * - (V1[3] * t1);
		t1 = ((-V2[3]* (this->Start[1] - L.Start[1])) + (V2[1]* (this->Start[3] - L.Start[3])))/ ((- V2[3] * - V1[1]) + (V2[1] * - V1[3]));
	}
	
	else 
	{
		if( equals ( V1[1], 0 ) && equals ( V2[1], 0 ) )
		{
			// Use z & y instead of x & y 
			// multiply first equation by (- V2[3]) and second by (V2[1])
			// we get:
			// -V2[3]* (this->Start[1] - L.Start[1]) = - V2[3] * - (V1[1] * t1);
			// V2[1]* (this->Start[3] - L.Start[3]) =   V2[1] * - (V1[3] * t1);

			t1 = ((-V2[3]* (this->Start[2] - L.Start[2])) + (V2[2]* (this->Start[3] - L.Start[3])))/ ((- V2[3] * - V1[2]) + (V2[2] * - V1[3]));
		}
		else 
		{	
			// multiply first equation by (- V2[2]) and second by (V2[1])
			// we get:
			// -V2[2]* (this->Start[1] - L.Start[1]) = - V2[2] * - (V1[1] * t1);
			// V2[1]* (this->Start[2] - L.Start[2]) =   V2[1] * - (V1[2] * t1);

			t1 = ((-V2[2]* (this->Start[1] - L.Start[1])) + (V2[1]* (this->Start[2] - L.Start[2])))/ ((- V2[2] * - V1[1]) + (V2[1] * - V1[2]));
		}
	}

	Int[1] = this->Start[1] + V1[1] * t1;
	Int[2] = this->Start[2] + V1[2] * t1;
	Int[3] = this->Start[3] + V1[3] * t1;

}


bool Compare_Length(							// compares length for 2 lines returns true if L1 < L2
	const Line3D & L1, 
	const Line3D & L2 )
{
	return ( L1.getLength() < L2.getLength() );
}

bool Line3D::isVertexOnLine(				// calculates if vertex P is on current line (within limits)
	const Vertex3D & P,
	const double & ang1,						// rotation angles needed to bring line and vertex on a plane defined by X & Y
	const double & ang2 ) const

{
	Line3D Ltmp;	// temporary line3d
	Vertex3D Vtmp;	// tempotary vertex3d
	bool status = false;
	float slope1;
	float slope2;

	//	make copy of line
	Ltmp.setLine ( this->getStart(), this->getEnd());	
	
	Vtmp = P;

	//	bring line to a horizontal plane using ang1 and ang2	
	// align by rotating aroud z
	Ltmp.Start.rotateZ ( - ang1 );
	Ltmp.End.rotateZ ( - ang1 );
				
	// align by rotating around x
	Ltmp.Start.rotateX ( - ang2 );
	Ltmp.End.rotateX ( - ang2 );

	// Apply same transformations to current vertex
	Vtmp.rotateZ ( - ang1 );
	Vtmp.rotateX ( - ang2 );

	if( equals (Vtmp[3], Ltmp.Start[3]))
	{

		if(		greaterOrEqualThan( Vtmp[2], MIN(Ltmp.Start[2], Ltmp.End[2])) &&
				lessOrEqualThan( Vtmp[2], MAX(Ltmp.Start[2], Ltmp.End[2])) &&
				greaterOrEqualThan( Vtmp[1], MIN(Ltmp.Start[1], Ltmp.End[1])) &&
				 lessOrEqualThan( Vtmp[1], MAX(Ltmp.Start[1], Ltmp.End[1])) )
			{
					// Does Vtmp verifiy Equation of current polygon edge     
					slope1 = (float)((Vtmp[2] - Ltmp.Start[2]) * (Ltmp.End[1] - Ltmp.Start[1]));
					slope2 = (float)((Vtmp[1] - Ltmp.Start[1]) * (Ltmp.End[2] - Ltmp.Start[2]));
							
					// if so its on the line
					if( equals ( fabs( slope1),  fabs( slope2 )) )
					{
						status = true;
					}// end if
			}//end if
	}
	return(status);
}

Line3D::~Line3D()
{
}

// -------------------------------------------- // SURFACE3D class

Surface3D::Surface3D()									// constructor
{
	a = 0.0;
	b = 0.0;
	c = 0.0;
	d = 0.0;

	vVx.clear();
	Normal[1] = 0.0;
	Normal[2] = 0.0;
	Normal[3] = 0.0;
	Orient = 0;
}

Surface3D::Surface3D(									// constructor with arguments
	const vector<Vertex3D> &vSummits )
{
	a = 0.0;
	b = 0.0;
	c = 0.0;
	d = 0.0;

	vVx.clear();
	vVx = vSummits;
	Normal[1] = 0.0;
	Normal[2] = 0.0;
	Normal[3] = 0.0;
	Orient = 0;

	if( vVx.size() > 0 ) SetSurfEquation();
}

Surface3D::Surface3D(									// copy constructor
	const Surface3D & S )								// surface S
{
	a = 0.0;
	b = 0.0;
	c = 0.0;
	d = 0.0;

	vVx.clear();
	Normal[1] = 0.0;
	Normal[2] = 0.0;
	Normal[3] = 0.0;
	Orient = 0;

//	if( S.vVx.size() > 0 )
	//{
		vVx = S.vVx;

		a = S.a;
		b = S.b;
		c = S.c;
		d = S.d;

		Normal [1] = a;
		Normal [2] = b;
		Normal [3] = c;

		Orient = S.Orient;
	//}
}

double Surface3D::GetA()							// Access function returns current surface equation coeff. A
{
	return this->a;
}

double Surface3D::GetB()							// Access function returns current surface equation coeff. B
{
	return this->b;
}

double Surface3D::GetC()							// Access function returns current surface equation coeff. C
{
	return this->c;
}

double Surface3D::GetD()							// Access function returns current surface equation coeff. D
{
	return this->d;
}

int Surface3D::GetOrient()							// Access function returns current surface orientation
{
	return this->Orient;
}

Surface3D & Surface3D::operator = (					// assignment operator
	const Surface3D & S )								// surface S
{
	if( this != &S )
	{
		a = 0.0;
		b = 0.0;
		c = 0.0;
		d = 0.0;

		vVx.clear();
		Normal[1] = 0.0;
		Normal[2] = 0.0;
		Normal[3] = 0.0;
		Orient = 0;

		if( S.vVx.size() > 0 )
		{
			vVx = S.vVx;

			a = S.a;
			b = S.b;
			c = S.c;
			d = S.d;

			Normal [1] = a;
			Normal [2] = b;
			Normal [3] = c;

			Orient = S.Orient;
		}
	}
	return *this;
}

bool Surface3D::operator == (							// compare S to current surface; returns true if same
	const Surface3D & S ) const						// surface S
{
	int k;

	Surface3D Sf1;
	Surface3D Sf2;

	Sf1 = *this;
	Sf2 = S;
	
	Sf1.SetSurfEquation();
	Sf2.SetSurfEquation();

	Sf1.putLowLeftFirst();
	Sf2.putLowLeftFirst();

	if( Sf1.vVx.size() == Sf2.vVx.size() )
		{
			// loop through all vertices of Sf2
			for( k = 0; k < (int)Sf2.vVx.size(); k++ )
			{
				if( Sf1.vVx.at( k ) != Sf2.vVx.at( k ) ) return false;
			}
			return true;
		}
	
	else return false;
}

/*

bool Surface3D::operator == (							// compare S to current surface; returns true if same
	const Surface3D & S ) const						// surface S
{
	int k;

	if( this != &S )
	{
		if( vVx.size() == S.vVx.size() )
		{
			// loop through all vertices of S
			for( k = 0; k < (int)S.vVx.size(); k++ )
			{
				if( vVx.at( k ) != S.vVx.at( k ) ) return false;
			}
			return true;
		}
		else return false;
	}
	else return true;
}
*/

bool Surface3D::operator != (							// compare S to current surface; returns true if different
	const Surface3D & S ) const						// surface S
{
	int k;

	if( this == &S ) return false;
	else
	{
		if( vVx.size() != S.vVx.size() ) return true;
		else
		{
			// loop through all vertices of S
			for( k = 0; k < (int)S.vVx.size(); k++ )
			{
				if( vVx.at( k ) != vVx.at( k ) ) return true;
			}
		}
	}
	return false;
}


void Surface3D::Calculate_eq_coeff(
	const Vector3D & V,
	const Vertex3D & T )
{	
	// P is any 3d point in our surface 
	//	PT is a vector from P to T
	//	PT = (Px - Tx, Py - Ty, Pz - Tz);
	//	by doing the cross product between px1 and the normal to the surface (vector V)we get
	//	(Px - Tx) Vx + (Py - Ty) Vy + (Pz - Tz) Vz =0
	//	VxPx - VxTx + VyPy - VyTy + VzPz - VzTz =0
	//	Therefore: 

	a = V[1];
	b = V[2];
	c = V[3];
	d = -((-V[1])*(T[1]) + (-V[2])*(T[2]) + (-V[3])*(T[3])); // d is negative because we put the equation in the form ax+by+cz=d
}

void Surface3D::SetSurfEquation()					// calculates coefficients a,b,c,d of the equation of a plane
{	
	Vertex3D  T;
	Vector3D  N;

	if ( this->isSurfaceValid() == true )
	{
		// Calculates and sets normal
		CalcSurfNormal();
		T = vVx[0];

		//		P is any 3d point in our surface 
		//		T is the first vertex of the surface
		//		PT is a vector from P to T
		//		PT = (Px - Tx, Py - Ty, Pz - Tz);
		//		by doing the cross product between PT and the normal to the surface (vector N) we get
		//		(Px - Tx) Nx + (Py - Ty) Ny + (Pz - Tz) Nz =0
		//		NxPx - NxTx + NyPy - NyTy + NzPz - NzTz =0
		//		Therefore: 

		this->a = this->Normal[1];
		this->b = this->Normal[2];
		this->c = this->Normal[3];
		d = -((-a)*(T[1]) + (-b)*(T[2]) + (-c)*(T[3])); // d is negative because we put the equation in the form ax+by+cz=d

		this->Orient = this->calcOrientation(this->getAzimut());
	}

	else // put everything to 0
	{
		this->a = 0;
		this->b = 0;
		this->c = 0;
		d = 0; 

		this->Normal[1] = 0;
		this->Normal[2] = 0;
		this->Normal[3] = 0;
		this->Orient = 0;
	}
}

void Surface3D::SetSurfEquation(
	vector<Vertex3D> &V,
	int i,
	double ag )
{
	
	Vector3D V1;
	Vector3D Vx (1,0,0);
	Surface3D Stmp;
	double dA1;
	double dA2;
	double dAx;
	
	int j = (i + 1) % V.size();	// next vertex

	// 1 copy every vertices of V in Stmp
	Stmp.vVx = V;

	// 2 set surface
	Stmp.SetSurfEquation();

	dA1 = Stmp.alignX();
	dA2 = Stmp.alignZ();

	// 3 Bring surface to origin	
	Stmp.translation ( - V[i][1] , - V[i][2], - V[i][3] );

	// 4 align on x by rotating aroud z
	Stmp.rotateZ ( - dA1 );

	// 5 align normal with z by rotating around x
	Stmp.rotateX ( - dA2 );

	// 7 calculate angle between current baseline and x axis (case of non rectangular shapes)
	V1 = Stmp.vVx[j] - Stmp.vVx[i];
	V1.Normalize();
	dAx = V1 * Vx;
	dAx = acos( dAx ) * ( 180.0 / ( espR::PI ) );	
	if ( greaterThan( V1[2], double ( 0.0 ) ) ) dAx = - dAx;
	Stmp.rotateZ ( dAx );

	// 7 rotate surface around X to match roof slope
	Stmp.rotateX ( ag) ; 

	// apply inverse tensformations to put back surface at original position
	// Return surface to its original position
	// Rotate inverse	
	Stmp.rotateZ ( -dAx );
	Stmp.rotateX ( dA2 );
	Stmp.rotateZ ( dA1 );

	// Translate inverse
	Stmp.translation ( V[i][1] , V[i][2], V[i][3] );

	Stmp.SetSurfEquation();
	this->copySurfEquation ( 
		Stmp.GetA(), 
		Stmp.GetB(), 
		Stmp.GetC(), 
		Stmp.GetD(), 
		Stmp.GetSurfNormal(), 
		Stmp.GetOrient()
		);

	// push back 2 baseline vertices 
	this->vVx.push_back( V[i] );
	this->vVx.push_back( V[j] );	
}

void Surface3D::copySurfEquation(
	const double & eqa,
	const double & eqb,
	const double & eqc,
	const double & eqd,
	const Vector3D & No,
	const int & or )
{
	this->a = eqa;
	this->b = eqb;
	this->c = eqc;
	this->d = eqd;

	this->Normal = No;
	this->Orient = or;
}

void Surface3D::CalcSurfNormal()						// calculates adnd returns surface normal
{
	Vector3D v21;											// vector between point pt2 and pt1
	Vector3D v31;											// vector between point pt3 and pt1
	Vector3D no;											// normal vector to vector v21 and v41

	Vector3D vno1(0,0,0);								// first possible normal
	Vector3D vno2(0,0,0);								// second possible normal (vno1 inverted)
	Vector3D vnul(0,0,0);								// null vector

	int c1 = 0;												// counter
	int c2 = 0;												// counter				

	unsigned int i, j, k;								// iterators

	no[1] = 0;
	no[2] = 0;
	no[3] = 0;

	// Calculate first normal diffrent from 0,0,0

	for( i = 0; vno1 == vnul; i++ ) 
	{	
		// control to acces next or previous surfaces index ( O to vVx.size() )
		j = i + 1;	
		if( j == this->vVx.size() ) j = 0;
		k = i-1;
		if( i == 0) k = this->vVx.size() - 1;
	
		v21[1] = this->vVx[j][1] - this->vVx[i][1]; 
		v21[2] = this->vVx[j][2] - this->vVx[i][2]; 
		v21[3] = this->vVx[j][3] - this->vVx[i][3]; 
	
		v31[1] = this->vVx[k][1] - this->vVx[i][1]; 
		v31[2] = this->vVx[k][2] - this->vVx[i][2]; 
		v31[3] = this->vVx[k][3] - this->vVx[i][3];
	
		// 2.	Execute cross product to obtain normal vector 
		vno1 = Cross_product( v21, v31 ); 
		if( vno1 != vnul) vno1.Normalize();
	}

	for( i = 0; i < this->vVx.size(); i++ ) 
	{	
		// control to acces next or previous surfaces index ( O to vVx.size() )
		j = i + 1;	
		if( j == this->vVx.size() ) j = 0;
		k = i - 1;
		if( i == 0) k = this->vVx.size() - 1;
	
		v21[1] = this->vVx[j][1] - this->vVx[i][1]; 
		v21[2] = this->vVx[j][2] - this->vVx[i][2]; 
		v21[3] = this->vVx[j][3] - this->vVx[i][3]; 
	
		v31[1] = this->vVx[k][1] - this->vVx[i][1]; 
		v31[2] = this->vVx[k][2] - this->vVx[i][2]; 
		v31[3] = this->vVx[k][3] - this->vVx[i][3];
	
		// 2.	Execute cross product to obtain normal vector 
		no = Cross_product( v21, v31 ); 
		if( no != vnul) no.Normalize();

		if( no == vnul ) continue;	// 3 points are colinear 
		if( no == vno1 ) c1++ ;		// normal on same direction as calculated in firts part 
		if( no != vnul && no != vno1 )  // normal inverted  
		{
			if ( vno2 == vnul ) 
			{
				vno2 = no;
				c2++ ;
			}
			else c2++ ;
		}
	}

	// 3.	Select the correct normal  
	if ( c1 > c2 ) this->Normal = vno1;
	else this->Normal = vno2;
}

Vector3D Surface3D::GetSurfNormal() const
{
	return( this->Normal );
}

Vertex3D Surface3D::Calculate_intersection(		// calculates and returns the intersection (Vertex3D) between 3 planes 
	const Surface3D & S2,								// surface S2
	const Surface3D & S3 )								// surface S3
{
	// Standard procedure to calculate the intersection of 3 planar surfaces
	// Using TNT JAMA/C++
	// Solve equation system Ax = b
	
	Vertex3D P;

	Array2D<double> A(3,3);
	Array2D<double> B(3,1);
	Array2D<double> X(3,2);

	A[0][0] = this->a;
	A[0][1] = this->b;
	A[0][2] = this->c;

	A[1][0] = S2.a;
	A[1][1] = S2.b;
	A[1][2] = S2.c;

	A[2][0] = S3.a;
	A[2][1] = S3.b;
	A[2][2] = S3.c;

	B[0][0] = this->d;
	B[1][0] = S2.d;
	B[2][0] = S3.d;

	LU <double> res(A);		// Solve system
	X = res.solve(B);

	// if the system cannot be solved (null matrix) return vertex -99,-99,-99
	if ( X.dim1() ==0 ) 
	{
		P[1] = -99;
		P[2] = -99;
		P[3] = -99;		
	}
	else
	{
		P[1] = X[0][0];
		P[2] = X[1][0];
		P[3] = X[2][0];
	}
	
	return P;					// Return intersection vertex	
}

bool Surface3D::canSurfaceBeCut(			// Verifies if current Surface intersects with cutting plane oS 
	const Surface3D & oS)					
{
	double r;
	double ps = 0;
	double ng = 0;

	unsigned int i;
	bool bSt = false;

	// first condition: current surface and oS cannot be parallel
	if ( this->areSurfParallel( oS ) == true ) return (false);

	else 
	{	
		// go through every pair of consecutice summits of current surface
		for( i = 0 ; i < this->vVx.size() ; i++ ) 
		{
			// if the summits are all ont the same side of the cutting plane 
			// it cannot be cut
			r = ( oS.a * this->vVx[i][1]) +  ( oS.b * this->vVx[i][2]) + ( oS.c * this->vVx[i][3]) - ( oS.d ) ;

			if ( equals ( r , double (0.0) ) ) continue;
			else
			{
				if ( lessThan ( r , double (0.0) ) ) ps++;
				else ng++;
			}

		}// end for i

		if ( ps > 0 && ng > 0 ) return ( true );
		else return ( false);
		
	}//end else

	return (bSt);
}

bool Surface3D::doSurfacesIntersect(			// Verifies if current Surface intersects with cutting plane oS 
	const Surface3D & oS)					
{
	int j, k;
	vector<Vertex3D> vvIt;
	Vertex3D vVn;
	Surface3D sTs;
	Vertex3D vInt;
	Surface3D sC = *this ;	// copy of current surface
	Surface3D sO = oS ;		// copy of oS surface
	Line3D lT;
	// Faire la liste des intersections entre les edges de la current surface and surface oS

	if ( sC.canSurfaceBeCut( sO ) == false ) return (false);

	// for every edge of current surface
		for ( unsigned int i = 0; i < sC.vVx.size(); i++ )
		{
			j = (i + 1) % sC.vVx.size();	// next vertex
			k = i - 1 ; // previous surface index
			if ( i == 0 ) k = sC.vVx.size() - 1; 

			// calculate second surface representing edge
			vVn = sC.vVx[i]+ sC.GetSurfNormal();
			sTs.vVx.push_back( sC.vVx[i] );
			sTs.vVx.push_back( sC.vVx[j] );
			sTs.vVx.push_back( vVn );
			sTs.SetSurfEquation();

			// check if edge intersects with oS surface
			vInt = sC.Calculate_intersection ( sTs, sO );

			if ( sO.IsVertexInside ( vInt ) == INSIDE || sO.IsVertexInside ( vInt ) == ONEDGE ) 
			{
				if ( IsVertexInList( vvIt, vInt) == false )  vvIt.push_back( vInt);	
			}
			sTs.clearValues();
		}

		// for every edge of oS surface
		for ( unsigned int i = 0; i < sO.vVx.size(); i++ )
		{
			j = (i + 1) % sO.vVx.size();	// next vertex
			k = i - 1 ; // previous surface index
			if ( i == 0 ) k = sO.vVx.size() - 1;

			// calculate second surface representing edge
			vVn = sO.vVx[i]+ sO.GetSurfNormal();
			sTs.vVx.push_back( sO.vVx[i] );
			sTs.vVx.push_back( sO.vVx[j] );
			sTs.vVx.push_back( vVn );
			sTs.SetSurfEquation();

			// check if edge intersects with oS surface
			vInt = sO.Calculate_intersection ( sTs, sC );

			if ( sC.IsVertexInside ( vInt ) == INSIDE || sC.IsVertexInside ( vInt ) == ONEDGE ) 
			{
				if ( IsVertexInList( vvIt, vInt) == false )  vvIt.push_back( vInt);	
			}
			sTs.clearValues();
		}

		// create line between every pair of consecutive intersections vertices

		// for every edge of oS surface
		for ( unsigned int i = 0; i < vvIt.size(); i++ )
		{
			j = (i + 1) % vvIt.size();	// next vertex
			lT.setLine( vvIt[i], vvIt[j] );
			vInt = lT.getMidPoint();
			
			// if the line midepoint is inside both surfaces, surfaces cross
			if ( sC.IsVertexInside ( vInt ) == INSIDE) 
			{
				if (  sO.IsVertexInside ( vInt ) == INSIDE || sO.IsVertexInside ( vInt ) == ONEDGE )  
					return ( true);
			}
	
		}
		

	return (false);

	/*Surface3D sC = *this ;	// copy of current surface
	Surface3D sO = oS ;		// copy of oS surface
	int j;
	Vertex3D vVn;
	Surface3D sTs;
	Vertex3D vInt;
	double dRi;
	double dRj;


	sC.elimColinearVertices();
	sO.elimColinearVertices();

	if ( sC.canSurfaceBeCut( sO ) == false  || sO.canSurfaceBeCut( sC ) == false  ) return (false);

	else
	{	
		// for every edge of current surface
		for ( unsigned int i = 0; i < sC.vVx.size(); i++ )
		{
			j = (i + 1) % sC.vVx.size();	// next vertex
			int k = i - 1 ; // previous surface index
			if ( i == 0 ) k = sC.vVx.size() - 1; 
			dRi = 0;
			dRj = 0;

			// calculate second surface representing edge
			vVn = sC.vVx[i]+ sC.GetSurfNormal();
			sTs.vVx.push_back( sC.vVx[i] );
			sTs.vVx.push_back( sC.vVx[j] );
			sTs.vVx.push_back( vVn );
			sTs.SetSurfEquation();

			// check if edge intersects with oS surface
			vInt = sC.Calculate_intersection ( sTs, sO );

			if ( sO.IsVertexInside ( vInt ) == INSIDE ) return ( true);		
			else sTs.clearValues();

		}

		// for every edge of oS surface
		for ( unsigned int i = 0; i < sO.vVx.size(); i++ )
		{
			j = (i + 1) % sO.vVx.size();	// next vertex
			int k = i - 1 ; // previous surface index
			if ( i == 0 ) k = sO.vVx.size() - 1;

			// calculate second surface representing edge
			vVn = sO.vVx[i]+ sO.GetSurfNormal();
			sTs.vVx.push_back( sO.vVx[i] );
			sTs.vVx.push_back( sO.vVx[j] );
			sTs.vVx.push_back( vVn );
			sTs.SetSurfEquation();

			// check if edge intersects with oS surface
			vInt = sO.Calculate_intersection ( sTs, sC );

			if ( sC.IsVertexInside ( vInt ) == INSIDE ) return ( true);	
			else sTs.clearValues();
		}
	}
	
	return (false);
	*/
}
/*bool Surface3D::doSurfacesIntersect(			// Verifies if current Surface intersects with cutting plane oS 
	const Surface3D & oS)					
{
	Surface3D sC = *this ;	// copy of current surface
	Surface3D sO = oS ;		// copy of oS surface

	if ( sC.canSurfaceBeCut( sO ) && sO.canSurfaceBeCut( sC )  ) return (true);

	else
	{
		for ( unsigned int i = 0; i < sO.vVx.size(); i++)
		{	
			if ( sC.IsVertexInside( sO.vVx[i] ) == INSIDE || sC.IsVertexInside( sO.vVx[i] ) == ONEDGE ) return true;
			else continue;
		}

	for ( unsigned int i = 0; i < sC.vVx.size(); i++)
		{	
			if ( sO.IsVertexInside( sC.vVx[i] ) == INSIDE || sO.IsVertexInside( sC.vVx[i] ) == ONEDGE ) return true;
			else continue;
		}
	}

	return (false);

}
*/

bool Surface3D::findValidIntersection(			// Verifies if current Surface intersects with cutting plane oS 
	const Surface3D & sEdg1,
	const Surface3D & sEdg2,
	const Surface3D & oS)					
{
	Vertex3D vI;
	Vertex3D vNl ( -99, -99, -99 );

	
	vI = this->Calculate_intersection ( sEdg1, oS ) ;

	if( vI == vNl )  return ( false ); // invalid intersection point

	else 
	{
		if ( this->IsVertexInside ( vI ) == ONEDGE || this->IsVertexInside ( vI ) == INSIDE) 
		{
			if ( oS.IsVertexInside ( vI ) == ONEDGE || oS.IsVertexInside ( vI ) == INSIDE)  return ( true );

			else 
			{
				vI = this->Calculate_intersection ( sEdg2, oS ) ;

				if( vI == vNl )  return ( false ); // invalid intersection point

				else 
				{
					if ( this->IsVertexInside ( vI ) == ONEDGE || this->IsVertexInside ( vI ) == INSIDE) 
					{
						if ( oS.IsVertexInside ( vI ) == ONEDGE || oS.IsVertexInside ( vI ) == INSIDE)  return ( true );
						else return ( false );
					}
					else return ( false );
				}
			}
		}

		else 
		{
			vI = this->Calculate_intersection ( sEdg2, oS ) ;

				if( vI == vNl )  return ( false ); // invalid intersection point

				else 
				{
					if ( this->IsVertexInside ( vI ) == ONEDGE || this->IsVertexInside ( vI ) == INSIDE) 
					{
						if ( oS.IsVertexInside ( vI ) == ONEDGE || oS.IsVertexInside ( vI ) == INSIDE)  return ( true );
						else return ( false );
					}
					else return ( false );
				}
		}
	}
	
}	

bool Surface3D::doSurfacesIntersect(						// verifies if 2 surfaces have a valid intersection
			int iEdc1,
			int iEdc2,
			int iD,
			vector<Surface3D> & vsOs)
{

	int j = (iD + 1) % vsOs.size();	// next surface index
	int k = iD - 1 ; // previous surface index
	if ( iD == 0 ) k = vsOs.size() - 1; 

	if ( this->canSurfaceBeCut(vsOs[iD] ) == true && vsOs[iD].canSurfaceBeCut(* this ) == true) 
	{
		if ( this->findValidIntersection( vsOs[iEdc1], vsOs[iEdc2], vsOs[iD] ) == true  || vsOs[iD].findValidIntersection( vsOs[j], vsOs[k], *this ) == true) return (true);
		else return (false);
	}
	else return (false);

}





void Surface3D::cutSurface(					// divides current Surface according to intersection with non parrallel oS surface 
	const Surface3D & oS,					// Limit surface
	vector<Surface3D> & vSurfF )			// Resulting vector of Surface3D
{
	Vertex3D  T ;
	Surface3D S1;
	Surface3D Stst;
	Surface3D oStst;

	unsigned int i;
	unsigned int j;
	int a = 0 ;
	int hits = 0; 
	int ttlhits = 0 ;

	vector<int> toerase;

	// first condition: current surface and oS cannot be parallel
	if ( this->canSurfaceBeCut(oS) == false ) vSurfF.push_back( *this);

	else 
	{
		// Make sure vSurfF is emty
		if ( vSurfF.size() > 0 ) 
		{
			vSurfF.clear();
		}

		//Create a copy of current surface
		Stst = *this;
		oStst = oS;
	
		int total = Stst.vVx.size() ;
		int total2 =0 ;

		// go through every pair of consecutice summits of current surface
		for( a = 0 ; a <= total ; a++ ) 
		{
			// loop control
			j = (a + 1) % Stst.vVx.size();
			i = (a) % Stst.vVx.size();

			// case of an edge parallel to cutting line
			// push back second vertex
			if ( oStst.isVertexInPlane( Stst.vVx[i] ) == true && oStst.isVertexInPlane( Stst.vVx[j] ) == true ) 
			{				
				ttlhits++;
				S1.vVx.clear();
				// reset hits to 1 and add Stst.vVx[j] to S1 because the last point of a new surface is the first of the next one
				hits = 1; 
				S1.vVx.push_back( Stst.vVx[j] );			
			}// end if

			else
			{
				// cannot start with T being a summit of current surface
				if ( oStst.isVertexInPlane( Stst.vVx[i] ) == true && a == 0 && hits == 0 && ttlhits == 0) total ++;
				
				else 
				{
					T = Stst.getEdgeIntersection( i, j, oStst);

					// If T is not a vertex of the surface 
 					if ( T != Stst.vVx[i])
					{
						if( ttlhits > 0 && hits == 1 && S1.vVx[0] != Stst.vVx[i]) 
						{
							S1.vVx.push_back( Stst.vVx[i] );
						}// end if

						if( equals(T[1], -99 ) && equals(T[2], -99 ) && equals(T[3], -99) ) // invalid intersection point
						{ 
							// adjust loop lenght & position 
							if( ttlhits == 0 ) 
							{
								total++;		
								continue;
							}// end if
						}// end if
						else // valid intersection point
						{
							hits++;
							ttlhits++;						
							S1.vVx.push_back( T );

							if( hits == 2 ) 
							{	
								vSurfF.push_back( S1 );															
								// Empty S1
								S1.vVx.clear();
								// reset hits to 1 and add T to S1 because the last point of a new surface is the first of the next one
								hits = 1; 
								S1.vVx.push_back( T );
							}// end if
						}// end else
					}// end if ( T != Stst.vVx[i])
					// If T is a vertex of the surface continue
					else continue;
					}// end else
				}// end else
		}// end for

		// go through every new surface and put "hole surfaces" at the right place
		for( i = 0; i < vSurfF.size(); i++ )
		{
			for( j = 0; j < vSurfF.size(); j++ )
			{
				vSurfF[i].SetSurfEquation();
				vSurfF[j].SetSurfEquation();

				//	if one point of surface i is inside surface j, 
				for ( unsigned int u = 0 ; u < vSurfF[i].vVx.size() ; u++)
				{
					//	mark i to be erased
					if ( vSurfF[j].IsVertexInside(vSurfF[i].vVx[u]) == INSIDE) 
					{
						toerase.push_back( i );
						// add summits of j to i in the correct counter clocwise order
						for( unsigned int v = 0 ; v < vSurfF[i].vVx.size(); v++ )
						{
							vSurfF[j].vVx.push_back( vSurfF[i].vVx[v]);
						}// end for jv	
					}// end if
				}// end for u 
			}// end for j

			// apply inverse tensformations to put back surface at original position
			// Return surface to its original position
			// Rotate inverse
			vSurfF[i].SetSurfEquation();
			vSurfF[i].copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient);
		}// end for i

		a = 0;

		// Erase hole surfaces
		for( i = 0 ; i < toerase.size(); i++ )
		{
			vSurfF.erase( vSurfF.begin()+ ( toerase[i] - a)  );
			a++;
		}
	}// end else (if surfaces are not parallel)

}

void Surface3D::multiCutSurface(
	vector<Surface3D> & vsEdges,
	vector<Surface3D> & vsRes)
	
{
	vector <Surface3D> vsCut;
	vector <Surface3D> vsTmp;
	int iNc;
		
	vsTmp.push_back ( *this );

	while ( vsTmp.size() > 0 )
	{
		iNc = 0 ; // put number of cuts to 0
		
		for (unsigned int i = 0 ; i < vsEdges.size(); i++)
			{
				if ( vsTmp[0].doSurfacesIntersect( vsEdges[i] ) )  
				{
					vsTmp[0].cutSurface( vsEdges[i], vsCut); 
					vsCut[0].putLowLeftFirst();
					vsCut[1].putLowLeftFirst();
					vsTmp.push_back( vsCut[0] );
					vsTmp.push_back( vsCut[1] );
					vsTmp.erase( vsTmp.begin() );
					vsCut.clear();
					iNc++;
				}

			}
		if ( iNc == 0 ) 
		{
			vsRes.push_back( vsTmp[0] );
			vsTmp.erase( vsTmp.begin() );
		}
	}


}

	void Surface3D::divideSurfaceHoriz(					// divides a Surface horizontally
	double distFloor,
	vector<Surface3D> & vSurfF )
{
	Vertex3D  T ;
	Surface3D S1;
	Surface3D Stst;
	vector<Vertex3D> mbox(4);
	double a1 = this->alignX();
	double a2 = this->alignZ();

	unsigned int i;
	unsigned int j;
	int a = 0 ;
	int hits = 0; 
	int ttlhits = 0 ;

	vector<int> toerase;

	// Make sure vSurfF is emty
	if ( vSurfF.size() > 0 ) 
		{
			vSurfF.clear();
		}
	
	//Create a copy of current surface
	Stst = *this;
	
	int total = Stst.vVx.size() ;
	int total2 =0 ;
	
	// 1 Calculate bounding box for current surface
	Stst.createBoundingBox(mbox);
	
	// 2 Bring surface to origin	
	Stst.translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);

	// 3 align on x by rotating aroud z
	Stst.rotateZ ( - a1 );

	// 4 align normal with z by rotating around x
	Stst.rotateX ( - a2 );

	// go through every pair of consecutice summits of current surface
	for( a = 0 ; a <= total ; a++ ) 
	{
		// loop control
		j = (a + 1) % Stst.vVx.size();
		i = (a) % Stst.vVx.size();

		// case of an edge parallel to cutting line
		// push back second vertex
		if ( Stst.vVx[i][2] == distFloor && Stst.vVx[j][2] == distFloor ) 
		{
			
			ttlhits++;
			S1.vVx.clear();
			// reset hits to 1 and add Stst.vVx[j] to S1 because the last point of a new surface is the first of the next one
			hits = 1; 
			S1.vVx.push_back( Stst.vVx[j] );
			
		}// end if

		else
		{
			T = Stst.getEdgeIntersection( 'h', i, j, distFloor );

			// If T is not a vertex of the surface 
			if ( T != Stst.vVx[i])
			{
				if( ttlhits > 0 && hits == 1 && S1.vVx[0] != Stst.vVx[i]) 
				{
					S1.vVx.push_back( Stst.vVx[i] );
				}// end if

				if( equals(T[1], -99 ) && equals(T[2], -99 ) && equals(T[3], -99) ) // invalid intersection point
				{ 
					// adjust loop lenght & position 
					if( ttlhits == 0 ) 
					{
						total++;		
						continue;
					}// end if
				}// end if
				else // valid intersection point
				{
					hits++;
					ttlhits++;
							
					S1.vVx.push_back( T );

					if( hits == 2 ) 
					{	
						vSurfF.push_back( S1 );
														
						// Empty S1
						total2 = S1.vVx.size();

						for( int w =0 ; w < total2 ; w++ ) 	
						{ 
							S1.vVx.pop_back();
						}

						// reset hits to 1 and add T to S1 because the last point of a new surface is the first of the next one
						hits = 1; 
						S1.vVx.push_back( T );
					}// end if
				}// end else
			}// end if ( T != Stst.vVx[i])
			// If T is a vertex of the surface continue
			else continue;
		}// end else
	}// end for

	// go through every new surface and put "hole surfaces" at the right place
	for( i = 0; i < vSurfF.size(); i++ )
	{
		for( j = 0; j < vSurfF.size(); j++ )
		{
			vSurfF[i].SetSurfEquation();
			vSurfF[j].SetSurfEquation();

			//	if one point of surface i is inside surface j, 
			for ( unsigned int u = 0 ; u < vSurfF[i].vVx.size() ; u++)
			{
				//	mark i to be erased
				if ( vSurfF[j].IsVertexInside(vSurfF[i].vVx[u]) == INSIDE) 
				{
					toerase.push_back( i );

					// add summits of j to i in the correct counter clocwise order
					for( unsigned int v = 0 ; v < vSurfF[i].vVx.size(); v++ )
					{
						vSurfF[j].vVx.push_back( vSurfF[i].vVx[v]);
					}// end for jv	
				}// end if
			}// end for u 
		}// end for j

		// apply inverse tensformations to put back surface at original position
		// Return surface to its original position
		// Rotate inverse
		vSurfF[i].SetSurfEquation();
		vSurfF[i].rotateX ( a2 );
		vSurfF[i].rotateZ ( a1 );

		// Translate inverse
		vSurfF[i].translation ( mbox[0][1] , mbox[0][2], mbox[0][3] );

		vSurfF[i].copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient);
	}// end for i

	a = 0;

	// Erase hole surfaces
	for( i = 0 ; i < toerase.size(); i++ )
	{
		vSurfF.erase( vSurfF.begin()+ ( toerase[i] - a)  );
		a++;
	}
}

void Surface3D::divideSurfaceVert(					// divides a Surface horizontally
	double distLeft,										// distance from left surface edge (m)
	vector<Surface3D> &vSurfF)
{
	Vertex3D  T ;
	Surface3D S1;
	Surface3D Stst;
	vector<Vertex3D> mbox(4);
	double a1 = this->alignX();
	double a2 = this->alignZ();

	unsigned int i;
	unsigned int j;
	int a = 0 ;
	int hits = 0; 
	int ttlhits = 0 ;

	vector<int> toerase;

	// Make sure vSurfF is emty
	if ( vSurfF.size() > 0 ) 
		{
			vSurfF.clear();
		}
	
	//Create a copy of current surface
	Stst = *this;
	
	int total = Stst.vVx.size() ;
	int total2 =0 ;
	
	// 1 Calculate bounding box for current surface
	Stst.createBoundingBox(mbox);
	
	// 2 Bring surface to origin	
	Stst.translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);

	// 3 align on x by rotating aroud z
	Stst.rotateZ ( - a1 );

	// 4 align normal with z by rotating around x
	Stst.rotateX ( - a2 );
	
	// go through every pair of consecutice summits of current surface
	for( a = 0 ; a <= total ; a++ ) 
	{
		// loop control
		j = (a + 1) % Stst.vVx.size();
		i = (a) % Stst.vVx.size();

		// case of an edge parallel to cutting line
		// push back second vertex
		if ( Stst.vVx[i][1] == distLeft && Stst.vVx[j][1] == distLeft) 
		{
			S1.vVx.clear();
			// reset hits to 1 and add Stst.vVx[j] to S1 because the last point of a new surface is the first of the next one
			hits = 1; 
			S1.vVx.push_back( Stst.vVx[j] );
			
		}// end if

		else
		{		
			T = Stst.getEdgeIntersection( 'v', i, j, distLeft );

			// If T is not a vertex of the surface 
			if ( T != Stst.vVx[i])
			{
				if( ttlhits > 0 && hits == 1 ) 
				{
					S1.vVx.push_back( Stst.vVx[i] );
				}// end if

				if( equals(T[1], -99 )  && equals(T[2], -99 ) && equals(T[3], -99 ) ) // invalid intersection point
				{ 
					// adjust loop lenght & position 
					if( ttlhits == 0 ) 
					{
						total++;		
						continue;
					}// end if
				}// end if
				else // valid intersection point
				{
					hits++;
					ttlhits++;
					
					S1.vVx.push_back( T );
								
					if( hits == 2 ) 
					{	
						vSurfF.push_back( S1 );
								
						// Empty S1
						total2 = S1.vVx.size();

						for( int w =0 ; w < total2 ; w++ ) 
						{ 
							S1.vVx.pop_back();
						}

						// reset hits to 1 and add T to S1 because the last point of a new surface is the first of the next one
						hits = 1; 
						S1.vVx.push_back( T );	
						}// end if
					}// end else
				}// end if ( T != Stst.vVx[i])
				// If T is a vertex of the surface continue
				else continue;
		}// end else
	}// end for

	// go through every new surface and put "hole surfaces" at the right place
	for( i = 0; i < vSurfF.size(); i++ )
	{
		for( j = 0; j < vSurfF.size(); j++ )
		{
			vSurfF[i].SetSurfEquation();
			vSurfF[j].SetSurfEquation();

			//	if one point of surface i is inside surface j, 
			for ( unsigned int u = 0 ; u < vSurfF[i].vVx.size() ; u++)
			{
				//	mark i to be erased
				if ( vSurfF[j].IsVertexInside(vSurfF[i].vVx[u]) == INSIDE) 
				{
					toerase.push_back( i );

					// add summits of j to i in the correct counter clocwise order
					for( unsigned int v = 0 ; v < vSurfF[i].vVx.size(); v++ )
					{
						vSurfF[j].vVx.push_back( vSurfF[i].vVx[v]);
					}// end for jv	
				}// end if
			}// end for u 
		}// end for j

		// apply inverse tensformations to put back surface at original position
		// Return surface to its original position
		// Rotate inverse
		vSurfF[i].SetSurfEquation();
		vSurfF[i].rotateX ( a2 );
		vSurfF[i].rotateZ ( a1 );

		// Translate inverse
		vSurfF[i].translation ( mbox[0][1] , mbox[0][2], mbox[0][3] );

		vSurfF[i].copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient);
	}// end for i
	
	a = 0;

	// Erase hole surfaces
	for( i = 0 ; i < toerase.size(); i++ )
	{
		vSurfF.erase( vSurfF.begin()+ ( toerase[i] - a)  );
		a++;
	}
}

Vertex3D Surface3D::getEdgeIntersection(			// gets surface edge intersection with a surface
	int iA,											// index of edge 1
	int iB,											// index of edge 2
	const Surface3D & oS )							// cutting surface
{
	
	Vertex3D P;
	Vertex3D T;
	// Add current surface normal to T to find third point
	T = this->vVx[iA] + this->Normal;

	// Create a third surface using iA, iB and T
	Surface3D third;
	third.vVx.push_back( this->vVx[iA] );
	third.vVx.push_back( this->vVx[iB] );
	third.vVx.push_back( T );
	third.SetSurfEquation();

	P = this->Calculate_intersection(oS,third);
	
	// the intersection vertex must be in the bounding box  formed by the x,y and z values of vVx[iA] & vVx[iB]
	// if true return P
	if(	this->IsVertexInside( P ) == ONEDGE 
		&& greaterOrEqualThan ( P[3],  MIN(this->vVx[iA][3], this->vVx[iB][3]) )
		&&	lessOrEqualThan ( P[3], MAX(this->vVx[iA][3], this->vVx[iB][3]) )
		&&	greaterOrEqualThan ( P[2], MIN(this->vVx[iA][2], this->vVx[iB][2]) )
		&&	lessOrEqualThan ( P[2], MAX(this->vVx[iA][2], this->vVx[iB][2]) )
		&&	greaterOrEqualThan ( P[1], MIN(this->vVx[iA][1], this->vVx[iB][1]) )
		&&	lessOrEqualThan ( P[1], MAX(this->vVx[iA][1], this->vVx[iB][1]) ) )
	{
		return (P);
	}
	
	else // return impossible value
	{
		P[1] = -99;
		P[2] = -99;
		P[3] = -99;

		return (P);
	}
}

Vertex3D Surface3D::getEdgeIntersection(			// gets surface edge intersection with a horizontal or vertical ray
	char ornt,												// orientation of ray "h" (horiz.) or "v" (vertical)
	int iA,
	int iB,
	double cutVal )										// distance from floor or from left corner
{
	Vertex3D intEdge ;
	double cVal = 0 ;

	if( ornt == 'h' ) 
	{	
		cVal = cutVal;
		intEdge[1] = ((cVal - vVx[iA][2]) *  (vVx[iB][1] -  vVx[iA][1]) / (vVx[iB][2] -  vVx[iA][2])) + vVx[iA][1] ;
		intEdge[2] = cVal;
		intEdge[3] = ((cVal - vVx[iA][2]) *  (vVx[iB][3] -  vVx[iA][3]) / (vVx[iB][2] -  vVx[iA][2])) + vVx[iA][3] ;
	}

	if( ornt == 'v' ) 
	{	
		cVal = cutVal;
		intEdge[1] = cVal;
		intEdge[2] = ((cVal - vVx[iA][1]) *  (vVx[iB][2] -  vVx[iA][2]) / (vVx[iB][1] -  vVx[iA][1])) + vVx[iA][2] ;
		intEdge[3] = ((cVal - vVx[iA][1]) *  (vVx[iB][3] -  vVx[iA][3]) / (vVx[iB][1] -  vVx[iA][1])) + vVx[iA][3] ;
	}

	// the intersection vertex must be in the bounding box  formed by the x,y and z values of vVx[iA] & vVx[iB]
	// if true return intEge
	if(	greaterOrEqualThan ( intEdge[3],  MIN(vVx[iA][3], vVx[iB][3]) )
		&&	lessOrEqualThan ( intEdge[3], MAX(vVx[iA][3], vVx[iB][3]) )
		&&	greaterOrEqualThan ( intEdge[2], MIN(vVx[iA][2], vVx[iB][2]) )
		&&	lessOrEqualThan ( intEdge[2], MAX(vVx[iA][2], vVx[iB][2]) )
		&&	greaterOrEqualThan ( intEdge[1], MIN(vVx[iA][1], vVx[iB][1]) )
		&&	lessOrEqualThan ( intEdge[1], MAX(vVx[iA][1], vVx[iB][1]) ) )
	{
		return (intEdge);
	}
	else // return impossible value
	{
		intEdge[1] = -99;
		intEdge[2] = -99;
		intEdge[3] = -99;

		return (intEdge);
	}
}

void Surface3D::offsetVertex(							// calculate offset (horiz or vert) of vertex parallel to on of the sides of current surface bounding box
	char ornt,												// orientation of offset "h" (horiz.) or "v" (vertical)
	float dist,												// distance to offset											
	vector<Vertex3D> & vbox,							// 4 corners of original boundary 
	Vertex3D & PTest)										// resulting Vertex 				
{
	double oa ;
	double ob ;
	double oc ;

	double x1 ;
	double y1 ;
	double z1 ;

	double x2 ;
	double y2 ;
	double z2 ;

	Vector3D Vdir; 
	
	int ct = 0 ;
	
	if( ornt == 'h') 
	{
		x1 = vbox [0][1];
		y1 = vbox [0][2];
		z1 = vbox [0][3];

		x2 = vbox [1][1];
		y2 = vbox [1][2];
		z2 = vbox [1][3];

		oa = x2 - x1 ;
		ob = y2 - y1 ;
		oc = z2 - z1 ;

		Vdir = vbox[3]-vbox[0];
	}

	if( ornt == 'v') 
	{
		x1 = vbox [0][1];
		y1 = vbox [0][2];
		z1 = vbox [0][3];

		x2 = vbox [3][1];
		y2 = vbox [3][2];
		z2 = vbox [3][3];

		oa = x2 - x1 ;
		ob = y2 - y1 ;
		oc = z2 - z1 ;
		
		Vdir = vbox[1]-vbox[0];
	}

	// count number of vectors || to an axis

	if ( equals ( oa, 0.0) ) ct++;
	if ( equals ( ob, 0.0) ) ct++;
	if ( equals ( oc, 0.0) ) ct++;

	//Special cases if edge of bounding box parrallel to one of axis
	
	if ( ct > 1)
	{
		//Case parrallel to z  
		if ( ornt == 'v' && equals ( oa, 0.0) && equals ( ob, 0.0) ) 
		{	
			PTest[1] = x1 ;
			PTest[2] = y1 ;
			PTest[3] = z1 + dist;
		}

		//Case parrallel to  y
		if ( ornt == 'h' && equals ( oa, 0.0) && equals ( oc, 0.0) ) 
		{	
			PTest[1] = x1 ;
			PTest[2] = y1 + dist ;
			PTest[3] = z1 ;
		}

		//Case parrallel to  x
		if ( ornt == 'h' && equals ( ob, 0.0) && equals ( oc, 0.0) ) 
		{	
			PTest[1] = x1  + dist ;
			PTest[2] = y1 ;
			PTest[3] = z1 ;
		}
	}
	else
	{
		// distance = sqrt(x2 + y2 + z2)
		// symetric equations on a 3d line
		// (x - x1)/a = (y - y1)/b = (z - z1)/c

		// use symetric equations to replace y & z by x 
		double od = ob / oa;
		double oe = (-od * x1) + y1 ;
		double of = oc / oa;
		double og = (-of * x1) + z1 ;

		// y = (od * x) + oe 
		// z = (of * x) + og 
		// we get dist2 = (x-x1)2 + (y-((od * x) + oe))2 + (z-((of * x) + og ))2

		double pa =	1 + (od * od) + (of * of);					// polynomial a
		double pb =	(-2 * x1) + (2 * od * oe) - (2 * od * y1) + (2 * of * og) - (2 * of * z1);		// polynomial b
		double pc =	(x1 * x1) + (oe * oe) - (2 * oe * y1) + (y1 * y1) + (og * og) - (2 * og * z1) + (z1 * z1) - (dist * dist);	// polynomial c
	
		vector<double> polyres;

		solvePolynomial( pa, pb, pc, polyres );

		// If delta > 0, then there are two distinct roots, both of which are real numbers.
		if( polyres.size() > 1 )
		{
			if ( this->IsVertexInside(vbox, PTest)== ONEDGE || this->IsVertexInside(vbox, PTest)== INSIDE)
			{
				PTest[1] = polyres[0];
				PTest[2] = ( od * polyres[0] ) + oe ;
				PTest[3] = ( of * polyres[0] ) + og ;
			}
			else // return second value
			{
				PTest[1] = polyres[1];
				PTest[2]  = (od * polyres[1]) + oe ;
				PTest[3]  = (of * polyres[1]) + og ;
			}
		}
		else 
		{	
			// If delta == 0, then there is exactly one distinct real root
			// x = -(b / 2a)
			if( polyres[0] != -999 )
			{ 
				PTest[1] = polyres[0];
				PTest[2] = (od * polyres[0]) - oe ;
				PTest[2] = (of * polyres[0]) - og ;
			}

			// If delta < 0, then there are no real roots.
			// return -1,-1,-1
			else 
			{ 
				PTest[1] = -1.0 ;
				PTest[2] = -1.0 ;
				PTest[3] = -1.0 ;
			}
		}
	}
}

void Surface3D::offsetEdge(							// calculate offset (horiz or vert) to move surface inside boundary
	char ornt,												// orientation of offset "h" (horiz.) or "v" (vertical)
	float dist,												// distance to offset											
	vector<Vertex3D> & vbox,							// 4 corners of original boundary 
	Line3D & Loff )								
{
	double oa ;
	double ob ;
	double oc ;

	double x1 ;
	double y1 ;
	double z1 ;

	double x2 ;
	double y2 ;
	double z2 ;

	Vector3D Vdir; 
	Vertex3D PTest;

	int ct = 0 ;
	
	if( ornt == 'h') 
	{
		x1 = vbox [0][1];
		y1 = vbox [0][2];
		z1 = vbox [0][3];

		x2 = vbox [1][1];
		y2 = vbox [1][2];
		z2 = vbox [1][3];

		oa = x2 - x1 ;
		ob = y2 - y1 ;
		oc = z2 - z1 ;

		Vdir = vbox[3]-vbox[0];
	}

	if( ornt == 'v') 
	{
		x1 = vbox [0][1];
		y1 = vbox [0][2];
		z1 = vbox [0][3];

		x2 = vbox [3][1];
		y2 = vbox [3][2];
		z2 = vbox [3][3];

		oa = x2 - x1 ;
		ob = y2 - y1 ;
		oc = z2 - z1 ;

		Vdir = vbox[1]-vbox[0];
	}
	
	// count number of vectors || to an axis

	if ( equals ( oa, 0.0) ) ct++;
	if ( equals ( ob, 0.0) ) ct++;
	if ( equals ( oc, 0.0) ) ct++;

	//Special cases if edge of bounding box parrallel to one of axis
	
	if ( ct > 1)
	{
		//Case parrallel to z  
		if ( ornt == 'v' && equals ( oa, 0.0) && equals ( ob, 0.0) ) 
		{	
			PTest[1] = x1 ;
			PTest[2] = y1 ;
			PTest[3] = z1 + dist;
		}

		//Case parrallel to  y
		if ( ornt == 'h' && equals ( oa, 0.0) && equals ( oc, 0.0) ) 
		{	
			PTest[1] = x1 ;
			PTest[2] = y1 + dist ;
			PTest[3] = z1 ;
		}

		//Case parrallel to  x
		if ( ornt == 'h' && equals ( ob, 0.0) && equals ( oc, 0.0) ) 
		{	
			PTest[1] = x1  + dist ;
			PTest[2] = y1 ;
			PTest[3] = z1 ;
		}

		Loff.setStart(PTest);
		Loff.setEnd(Loff.getStart()+Vdir);
	}// end if ct
	else
	{
		// distance = sqrt(x2 + y2 + z2)
		// symetric equations on a 3d line
		// (x - x1)/a = (y - y1)/b = (z - z1)/c
		
		// use symetric equations to replace y & z by x 
		double od = ob / oa;
		double oe = (-od * x1) + y1 ;
		double of = oc / oa;
		double og = (-of * x1) + z1 ;

		// y = (od * x) + oe 
		// z = (of * x) + og 
		// we get dist2 = (x-x1)2 + (y-((od * x) + oe))2 + (z-((of * x) + og ))2

		double pa =	1 + (od * od) + (of * of);					// polynomial a
		double pb =	(-2 * x1) + (2 * od * oe) - (2 * od * y1) + (2 * of * og) - (2 * of * z1);		// polynomial b
		double pc =	(x1 * x1) + (oe * oe) - (2 * oe * y1) + (y1 * y1) + (og * og) - (2 * og * z1) + (z1 * z1) - (dist * dist);	// polynomial c
		
		vector<double> polyres;

		solvePolynomial( pa, pb, pc, polyres );

		// If delta > 0, then there are two distinct roots, both of which are real numbers.
		if( polyres.size() > 1 )
		{
			PTest[1] = polyres[0];
			PTest[2] = ( od * polyres[0] ) + oe ;
			PTest[3] = ( of * polyres[0] ) + og ;

			if ( this->IsVertexInside(vbox, PTest)== ONEDGE || this->IsVertexInside(vbox, PTest)== INSIDE)
			{
				Loff.setStart(PTest);
			}
			else // return second value
			{
				PTest[1] = polyres[1];
				PTest[2]  = (od * polyres[1]) + oe ;
				PTest[3]  = (of * polyres[1]) + og ;
				Loff.setStart( PTest);
			}
		}
		else 
		{	
			// If delta == 0, then there is exactly one distinct real root
			// x = -(b / 2a)
			if( polyres[0] != -999 )
			{ 
				PTest[1] = polyres[0];
				PTest[2] = (od * polyres[0]) - oe ;
				PTest[2] = (of * polyres[0]) - og ;
				Loff.setStart(PTest);
			}

			// If delta < 0, then there are no real roots.
			// return -1,-1,-1
			else 
			{ 
				Loff.setStart(-1.0 , -1.0, -1.0);
			}
		}

		// find second point of Line by adding Vdir to start point of Loff
		Loff.setEnd(Loff.getStart()+Vdir);
	}// end else
}

void Surface3D::moveSurface(					// move surface	
	double hr,										// horizontal distance 
	double vr )										// vertical distance
{
	Vector3D vdir;  // direction of movement
	Vertex3D or;	// surface origin
	Vertex3D vh;	// test vertex (horizontal)
	Vertex3D vv;	// test vertex (vertical)
	Vector3D phor;	// vertical direction 
	Vector3D pver;	// horizontal direction

	vector<Vertex3D> mbox(4);

	//  calculate boundig box of current surface
	this->createBoundingBox(mbox);

	// origin of surface becomes first point of bounding box (lower left corner)
	or = mbox[0];

	// define horizontal component of direction vector 
	// i.e horizontal offset point ( if hr != 0)
	if (equals( hr, 0.0) == true) 
	{
		phor [1] = 0.0;
		phor [2] = 0.0;
		phor [3] = 0.0;
	}
	else
	{
		this->offsetVertex('h', (float)hr , mbox, vh);
		phor = vh - or;
	}
	
	// define vertical component of direction vector
	// i.e vertical offset point ( if vr != 0)
	if (equals( vr, 0.0) == true) 
	{
		pver [1] = 0.0;
		pver [2] = 0.0;
		pver [3] = 0.0;
	}
	else
	{
		this->offsetVertex('v', (float)vr , mbox, vv);
		pver = vv - or;
	}

	// calculate direction of movement (sum of horizontal component + vertical component)
	vdir = phor + pver;

	//move every summit of the surface
	for ( unsigned int i = 0; i < this->vVx.size();i++)
	{
		this->vVx[i] = this->vVx[i] + vdir;
	}
}

void Surface3D::resizeSurface(					// resize surface	
	double NWidth,									// new surface widht (m)
	double NHeight )									// new surface height (m)
{
	double sfX ; // scale factor X
	double sfY ; // scale factor Y

	sfX = NWidth / this->getWidth();
	sfY = NHeight / this->getHeight();

	this->scale ( sfX, sfY, (double) 1.0 );
}

void Surface3D::rotateX(					// rotate surface around X axis 
	double angle )
{
	Array2D<double> Rot(4,4);	// rotation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	double ang = (angle * (espR::PI) /180);	

	Rot[0][0] = 1;
	Rot[0][1] = 0;
	Rot[0][2] = 0;
	Rot[0][3] = 0;

	Rot[1][0] = 0;
	Rot[1][1] = cos ( ang );
	Rot[1][2] = -sin ( ang );
	Rot[1][3] = 0;

	Rot[2][0] = 0;
	Rot[2][1] = sin ( ang );
	Rot[2][2] = cos ( ang );
	Rot[2][3] = 0;
	
	Rot[3][0] = 0;
	Rot[3][1] = 0;
	Rot[3][2] = 0;
	Rot[3][3] = 1;

	//rotate every summit of the surface
	for( unsigned int i = 0; i < this->vVx.size();i++)
	{
		P[0][0] = this->vVx[i][1];
		P[1][0] = this->vVx[i][2];
		P[2][0] = this->vVx[i][3];
		P[3][0] = 1;

		P = matmult(Rot, P);			
				
		this->vVx[i][1] = P[0][0];
		this->vVx[i][2] = P[1][0];
		this->vVx[i][3] = P[2][0];
	}

	// update surface equation
	this->SetSurfEquation();
}

void Surface3D::rotateY(						// rotate surface around Y axis 
	double angle)
{
	Array2D<double> Rot(4,4);	// rotation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	double ang = (angle * (espR::PI) /180);	
	
	Rot[0][0] = cos ( ang );
	Rot[0][1] = 0;
	Rot[0][2] = sin ( ang );
	Rot[0][3] = 0;

	Rot[1][0] = 0;
	Rot[1][1] = 1;
	Rot[1][2] = 0;
	Rot[1][3] = 0;

	Rot[2][0] = -sin ( ang );
	Rot[2][1] = 0;
	Rot[2][2] = cos ( ang );
	Rot[2][3] = 0;
	
	Rot[3][0] = 0;
	Rot[3][1] = 0;
	Rot[3][2] = 0;
	Rot[3][3] = 1;

	//rotate every summit of the surface
	for( unsigned int i = 0; i < this->vVx.size();i++)
	{
		P[0][0] = this->vVx[i][1];
		P[1][0] = this->vVx[i][2];
		P[2][0] = this->vVx[i][3];
		P[3][0] = 1;

		P = matmult(Rot, P);			
		
		this->vVx[i][1] = P[0][0];
		this->vVx[i][2] = P[1][0];
		this->vVx[i][3] = P[2][0];
	}

	// update surface equation
	this->SetSurfEquation();
}

void Surface3D::rotateZ(					// rotate surface around Z axis 
	double angle)
{
	Array2D<double> Rot(4,4);	// rotation matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	double ang = (angle * (espR::PI) /180);	

	Rot[0][0] = cos ( ang );
	Rot[0][1] = -sin ( ang );
	Rot[0][2] = 0;
	Rot[0][3] = 0;

	Rot[1][0] = sin ( ang );
	Rot[1][1] = cos ( ang );
	Rot[1][2] = 0;
	Rot[1][3] = 0;

	Rot[2][0] = 0;
	Rot[2][1] = 0;
	Rot[2][2] = 1;
	Rot[2][3] = 0;
	
	Rot[3][0] = 0;
	Rot[3][1] = 0;
	Rot[3][2] = 0;
	Rot[3][3] = 1;

	//rotate every summit of the surface
	for( unsigned int i = 0; i < this->vVx.size();i++)
	{
		P[0][0] = this->vVx[i][1];
		P[1][0] = this->vVx[i][2];
		P[2][0] = this->vVx[i][3];
		P[3][0] = 1;

		P = matmult(Rot, P);			
		
		this->vVx[i][1] = P[0][0];
		this->vVx[i][2] = P[1][0];
		this->vVx[i][3] = P[2][0];
	}

	// update surface equation
	this->SetSurfEquation();
}

void Surface3D::scaleOr(		// Scale a surface origin of scale is 0,0,0
	double sX,						// X scale factor
	double sY,						// Y scale factor
	double sZ)						// Z scale factor
{
	Array2D<double> Sc(4,4);	// Scale matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	Sc[0][0] = sX ;
	Sc[0][1] = 0;
	Sc[0][2] = 0;
	Sc[0][3] = 0;

	Sc[1][0] = 0;
	Sc[1][1] = sY;
	Sc[1][2] = 0;
	Sc[1][3] = 0;

	Sc[2][0] = 0;
	Sc[2][1] = 0;
	Sc[2][2] = sZ;
	Sc[2][3] = 0;
	
	Sc[3][0] = 0;
	Sc[3][1] = 0;
	Sc[3][2] = 0;
	Sc[3][3] = 1;

	//Scale every summit of the surface
	for( unsigned int i = 0; i < this->vVx.size();i++)
	{
		P[0][0] = this->vVx[i][1];
		P[1][0] = this->vVx[i][2];
		P[2][0] = this->vVx[i][3];
		P[3][0] = 1;

		P = matmult(Sc, P);			
		
		this->vVx[i][1] = P[0][0];
		this->vVx[i][2] = P[1][0];
		this->vVx[i][3] = P[2][0];
	}

	// update surface equation
	this->SetSurfEquation();
}

void Surface3D::scaleUnifOr(	// Unifor scaling of a surface, origin of scale is 0,0,0
	double sU )						// uniform scale factor
{
	this->scaleOr ( sU, sU, sU);
}

void Surface3D::scale(			// Scale surface (origin of scale = lower left corner of bounding box)
	double scX,						// X scale factor
	double scY,						// Y scale factor
	double scZ)						// Z scale factor
{
	vector<Vertex3D> mbox(4);
	double a1 = this->alignX();
	double a2 = this->alignZ();

	// 1 Calculate bounding box for current surface
	this->createBoundingBox(mbox);
	
	// 2 Bring surface to origin	
	this->translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);

	// 3 align on x by rotating aroud z
	this->rotateZ ( - a1 );

	// 4 align normal with z by rotating around x
	this->rotateX ( - a2 );

	// 5 Scale the surface
	this->scaleOr ( scX, scY, scZ) ;

	// Return surface to its original position
	// 6 Rotate inverse
	this->rotateX ( a2 );
	this->rotateZ ( a1 );

	// 7 Translate inverse
	this->translation ( mbox[0][1] , mbox[0][2], mbox[0][3] );
}

void Surface3D::scaleUnif(		// Unifor scaling of current surface origin of scale is 0,0,0
	double sU)						// uniform scale factor
{
	this->scale ( sU, sU, sU);
}

void Surface3D::translation(	// Apply translation to current surface
	double tX,						// X translation
	double tY,						// Y translation
	double tZ )						// Z translation
{
	Array2D<double> Tr(4,4);	// Scale matrix (Homogeneous coordinates)
	Array2D<double> P(4,1);		// original summit

	Tr[0][0] = 1 ;
	Tr[0][1] = 0;
	Tr[0][2] = 0;
	Tr[0][3] = tX;

	Tr[1][0] = 0;
	Tr[1][1] = 1;
	Tr[1][2] = 0;
	Tr[1][3] = tY;

	Tr[2][0] = 0;
	Tr[2][1] = 0;
	Tr[2][2] = 1;
	Tr[2][3] = tZ;
	
	Tr[3][0] = 0;
	Tr[3][1] = 0;
	Tr[3][2] = 0;
	Tr[3][3] = 1;

	//Scale every summit of the surface
	for( unsigned int i = 0; i < this->vVx.size();i++)
	{
		P[0][0] = this->vVx[i][1];
		P[1][0] = this->vVx[i][2];
		P[2][0] = this->vVx[i][3];
		P[3][0] = 1;

		P = matmult(Tr, P);			
		
		this->vVx[i][1] = P[0][0];
		this->vVx[i][2] = P[1][0];
		this->vVx[i][3] = P[2][0];
	}

	// update surface equation
	this->SetSurfEquation();
}

int Surface3D::IsVertexInside(						// calculates if Vertex V is inside current surface Return 1 if inside, 0 if outside & 2 if on edge
	const Vertex3D & V )	const							// vertex V
{
	Surface3D Stst;							
	Vertex3D Vtst;
	unsigned int i; 
	unsigned int j = vVx.size() - 1;
	int oddNodes = OUTSIDE ;
	float slope1;
	float slope2;
	vector<Vertex3D> mbox(4);
	
	//Create a copy of current surface
	Stst = *this;

	double a1 = Stst.alignX();
	double a2 = Stst.alignZ();

	//Create a copy of vertex V
	Vtst = V;

	// 1 Check is  V verifies equation of current surface
	if( equals(((this->a * V[1]) + (this->b * V[2]) + (this->c * V[3]) - this->d), 0.0) )
	{
		// 2 check if V is one of the summits of current surface
		// if it is return true
		for( i = 0; i < vVx.size(); i++ )
		{	   	
			if( V == vVx[i] )
			{
				return ONEDGE;
			}
		}

		// Bring both the vertex and the surface at the origin on a plane defined by x and y	
		// Calculate bounding box for current surface
		Stst.createBoundingBox(mbox);
	
		// Bring surface to origin	
		Stst.translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);

		// align on x by rotating aroud z
		Stst.rotateZ ( - a1 );

		// align normal with z by rotating around x
		Stst.rotateX ( - a2 );

		// Apply same transformations to current vertex
		Vtst.translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);
		Vtst.rotateZ ( - a1 );
		Vtst.rotateX ( - a2 );

		// 3 check if V is right on one of the edges of the current polygon
		// if it is return true
		for( i = 0; i < Stst.vVx.size(); i++ )
		{
			j = (i+1) % Stst.vVx.size();
						
			if( greaterOrEqualThan ( Vtst[2],  MIN( Stst.vVx[i][2], Stst.vVx[j][2] )) &&
				 lessOrEqualThan ( Vtst[2], MAX( Stst.vVx[i][2], Stst.vVx[j][2] )) &&
				 greaterOrEqualThan ( Vtst[1],  MIN( Stst.vVx[i][1], Stst.vVx[j][1] )) &&
				 lessOrEqualThan ( Vtst[1], MAX( Stst.vVx[i][1], Stst.vVx[j][1] )) )
			{
				// Does V verifiy Equation of current polygon edge     
				slope1 = (float)((Vtst[2] - Stst.vVx[i][2]) * (Stst.vVx[j][1] - Stst.vVx[i][1]));
				slope2 = (float)((Vtst[1] - Stst.vVx[i][1]) * (Stst.vVx[j][2] - Stst.vVx[i][2]));
						
				// if so overlies an edge
				if( equals ( fabs( slope1),  fabs( slope2 )) )
				{
					return ONEDGE;
				}// end if
			}// end if
		} // end for
					
		j = Stst.vVx.size() - 1;
					
		// 4 count the number of times an horizontal ray crosse the surface perimeter on one side of the vertex
		// odd number == inside
		// even number == outside
					
		for( i = 0; i < Stst.vVx.size(); i++ )
		{
			if( ( lessThan(Stst.vVx[i][2], Vtst[2] ) && greaterOrEqualThan( Stst.vVx[j][2], Vtst[2]) ) ||
			    ( lessThan(Stst.vVx[j][2], Vtst[2] ) && greaterOrEqualThan( Stst.vVx[i][2], Vtst[2]) ) ) 
			{
				if( lessThan(Stst.vVx[i][1] + (Vtst[2] - Stst.vVx[i][2] ) / ( Stst.vVx[j][2] - Stst.vVx[i][2] ) * ( Stst.vVx[j][1] - Stst.vVx[i][1] ), Vtst[1] ) ) 
				{
					oddNodes++; 
				}
			}
			j = i;
		} // end for

		// EVEN
		if( oddNodes % 2 == 0 ) return OUTSIDE;
			
		// ODD
		else return INSIDE ;
	}
	else return OUTSIDE ;
}

int Surface3D::IsVertexInside(						// calculates if Vertex V is inside Polygon Poly Return 1 if inside, 0 if outside & 2 if on edge
	const vector<Vertex3D> & Poly,
	const Vertex3D & V )
{
	Surface3D Stst;
	vector<Vertex3D> Ptst;
	Vertex3D Vtst;
	unsigned int i; 
	unsigned int j = Poly.size() - 1;
	int oddNodes = OUTSIDE ;
	float slope1;
	float slope2;
	vector<Vertex3D> mbox(4);
	
	//Create a copy of current surface
	Stst = *this;

	double a1 = Stst.alignX();
	double a2 = Stst.alignZ();

	//Create a copy of Poly
	Ptst = Poly;

	//Create a copy of vertex V
	Vtst = V;

	// 1 Check is  V verifies equation of current surface
	if( equals(((this->a * V[1]) + (this->b * V[2]) + (this->c * V[3]) - this->d), 0.0) )
	{
		// 2 check if V is one of the summits of current surface
		// if it is return true
		for( i = 0; i < Poly.size(); i++ )
		{	   	
			if( V == Poly[i] )
			{
				return ONEDGE;
			}
		}

		// Bring both the vertex and the polygon at the origin on a plane defined by x and y	
		// Calculate bounding box for current surface
		this->createBoundingBox(mbox);
	
		// Bring every summit on a plane formed by x and y axis
		// Apply translation
		for( i = 0; i < Poly.size(); i++ )
		{
			Ptst[i].translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);
		}		
		
		// align on x by rotating aroud z
		for( i = 0; i < Poly.size(); i++ )
		{
			Ptst[i].rotateZ ( - a1 );
		}			

		// align normal with z by rotating around x
		for( i = 0; i < Poly.size(); i++ )
		{
			Ptst[i].rotateX ( - a2 );
		}	

		// Apply same transformations to current vertex
		Vtst.translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);
		Vtst.rotateZ ( - a1 );
		Vtst.rotateX ( - a2 );

		// check if V is right on one of the edges of the current polygon
		// if it is return true
		for( i = 0; i < Ptst.size(); i++ )
		{
			j = (i+1) % Ptst.size();
				
			if( greaterOrEqualThan ( Vtst[2], MIN(Ptst[i][2], Ptst[j][2])) &&
				 lessOrEqualThan ( Vtst[2], MAX(Ptst[i][2], Ptst[j][2])) &&
				 greaterOrEqualThan ( Vtst[1], MIN(Ptst[i][1], Ptst[j][1])) &&
				 lessOrEqualThan ( Vtst[1], MAX(Ptst[i][1], Ptst[j][1])) )
			{
				// Does V verifiy Equation of current polygon edge     
				slope1 = (float)((Vtst[2] - Ptst[i][2]) * (Ptst[j][1] - Ptst[i][1]));
				slope2 = (float)((Vtst[1] - Ptst[i][1]) * (Ptst[j][2] - Ptst[i][2]));
						
				// if so overlies an edge
				if( equals ( fabs( slope1),  fabs( slope2 )) )
				{
					return ONEDGE;
				}// end if
			}
		}
			
		j = Ptst.size() - 1;
			
		// count the number of times an horizontal ray crosse the surface perimeter on one side of the vertex
		// odd number == inside
		// even number == outside
			
		for( i = 0; i < Ptst.size(); i++ )
		{
			if( ( lessThan(Ptst[i][3], Vtst[3] ) && greaterOrEqualThan( Ptst[j][3], Vtst[3]) ) ||
				 ( lessThan(Ptst[j][3], Vtst[3] ) && greaterOrEqualThan( Ptst[i][3], Vtst[3]) ) ) 
			{
				if( lessThan(Ptst[i][1] + (Vtst[3] - Ptst[i][3] ) / ( Ptst[j][3] - Ptst[i][3] ) * ( Ptst[j][1] - Ptst[i][1] ), Vtst[1] ) ) 
				{
					oddNodes++; 
				}
			}
			j = i;
		}
		
		// EVEN
		if( oddNodes % 2 == 0 ) return OUTSIDE;
			
		// ODD
		else return INSIDE ;
	}
	else return OUTSIDE ;
}

bool Surface3D::isVertexInPlane(						// Verifies if V is in plane defined by current surface
	const Vertex3D & V )
{

	if( equals(((this->a * V[1]) + (this->b * V[2]) + (this->c * V[3]) - this->d), 0.0) ) return true;
	else return false;

}

bool Surface3D::IsSurfaceInside(						// calculates if current surface contains surface oS
	const Surface3D & oS ) const						
{
	unsigned int i;
	Vertex3D P;
	
	// check all oS summits
	// if one lies outside current surface surface oS is not inside
	for( i = 0; i < oS.vVx.size(); i++ ) 
	{	
		P = oS.vVx[i];
		
		if( IsVertexInside( P ) == OUTSIDE )
		{
			return false;
			break;
		}
	}

	// check all current surface summits
	// if one lies inside surface oS, oS is not inside
	for( i = 0; i < vVx.size(); i++ ) 
	{	
		P = vVx[i];

		if( oS.IsVertexInside( P ) == INSIDE )
		{
			return false;
			break;
		}
	}
	return true;
}

bool Surface3D::IsOneVertexInside(							// returns true if a vertex of Vl is inside current surface
	const vector<Vertex3D> & Vl)
{
	bool r = false;
	
	for ( unsigned int i = 0; i < Vl.size(); i++ )
	{
		if ( this->IsVertexInside ( Vl[i] ) == INSIDE ) return true;
	}

	return (r);

}

bool Surface3D::IsOneVertexOutside(							// returns true if a vertex of Vl is outside current surface
	const vector<Vertex3D> & Vl)
{
	bool r = false;
	
	for ( unsigned int i = 0; i < Vl.size(); i++ )
	{
		if ( this->IsVertexInside ( Vl[i] ) == OUTSIDE ) return true;
	}

	return (r);

}

float Surface3D::getAzimut() const					// calculates surface orientation 
{
	Vector3D vProj;										// projection of surface normal onto xy plane
	Vector3D vSouth;										// vector pointing South (0,-1,0)
	float aAz = 0.0;										// angle azimut	
	float CosAz = 0.0;									// Cos angle azimut

	vSouth [1] = 0;
	vSouth [2] = 1;
	vSouth [3] = 0;

	vProj = this->GetSurfNormal();

	// case normal points perpendicular to xy plane
	if( equals( vProj[1], 0.0 ) && equals( vProj[2], 0.0 )) 
	{
		if ( lessThan( vProj[3], 0.0 ) ) return ((float)espR::DOWN);	// floor (facing Down)
		if ( greaterThan( vProj[3], 0.0 ) ) return ((float)espR::UP);	// ceiling (facing Up)
	}
	else 
	{
		vProj[3] = 0;
		
		// calculate angle aOrient between vProj & vSouth 
		// cos (aOrient) = (vProj * vSouth) / (|vProj| * |vSouth|)
		CosAz = (float)( vProj * vSouth ) / ( (float)Norm( vProj ) * (float)Norm( vSouth ) );
		aAz = acos( CosAz );
	}

	// convert radians to degrees
	// degre = 180 * (radian) / pi 
	aAz = (float)180.0 * aAz / (float) espR::PI  ; 

	if ( lessThan( vProj[1], 0.0 ) ) 
	{
		aAz = (float)360.0 - aAz;
		return (aAz);
	}
	else return (aAz);
}

float Surface3D::alignX() const						// calculates angle needed to align surface baseline with x axis (i.e Normal with -Y)
{
	Vector3D vProj;										// projection of surface normal onto xy plane
	Vector3D vX;											// vector pointing along towards -y (0,-1,0)
	float aPan = 0.0;										// angle azimut	
	float CosPan = 0.0;									// Cos angle azimut

	vX [1] = 0;
	vX [2] = -1;
	vX [3] = 0;

	vProj = this->GetSurfNormal();
	vProj[3] = 0;

	// case normal points perpendicular to xy plane
	if( equals( vProj[1], 0.0 ) && equals( vProj[2], 0.0 )) return (0);
	else 
	{
		// calculate angle aOrient between vProj & vSouth 
		// cos (aOrient) = (vProj * vSouth) / (|vProj| * |vSouth|)
		CosPan = (float)( vProj * vX ) / ( (float)Norm( vProj ) * (float)Norm( vX) );
		aPan = acos( CosPan );
	}

	// convert radians to degrees
	// degre = 180 * (radian) / pi 
	aPan = (float)180.0 * aPan / (float) espR::PI  ; 

	if ( lessThan( vProj[1], 0.0 ) ) 
	{
		aPan = (float)360.0 - aPan;
		return (aPan);
	}
	else return (aPan);
}

float Surface3D::getAltitude() const				// calculates surface altitude 
{
	Vector3D vNorm;										// Normal vector of surface	
	Vector3D vProj;										// projection of surface normal onto xy plane
	float aAlt = 0.0;										// angle altitude	
	float CosAlt = 0.0;									// Cos angle orientation	

	vNorm = GetSurfNormal();

	if( equals(vNorm[3] , 0.0) ) // horizontal normal 
	{
		aAlt = 90;
		return (aAlt); 
	}
	else
	{
		if( equals(vNorm[1] , 0.0) && equals(vNorm[2] , 0.0) ) // vertical normal 
		{
			aAlt = 0;
			return (aAlt); 
		}
		
		else
		{
			vProj = vNorm ;
			vProj[3] = 0;
		 
			// calculate angle aOrient between vProj & vNorm 
			// cos (aOrient) = (vProj * vSouth) / (|vProj| * |vSouth|)

			CosAlt = (float)( vNorm * vProj ) / ( (float)Norm( vNorm ) * (float)Norm( vProj ) );

			aAlt = acos ( CosAlt );
			
			// convert radians to degrees
			// degre = 180 * (radian) / pi 

			aAlt = (float)180.0 * aAlt / (float) espR::PI  ; 

			// since altitude is calculated from z axis

			aAlt = (float)90.0 - aAlt;

			if( lessThan( vNorm[3], 0.0 ) ) 
			{
				aAlt = - aAlt;
				return (aAlt);
			}
			else return (aAlt);
		}
	}
}

float Surface3D::alignZ() const				// Returns angle needed to align surface Normal to Z 
{
	return (this->getAltitude());
}

float Surface3D::getRoll() const						// calculates surface Roll (rotation around y axis)
{
	Vector3D vProj;										// projection of surface normal onto xy plane
	Vector3D vX;											// vector pointing toward z axis (1,0,0)
	float aRoll = 0.0;									// angle Roll	
	float CosRoll = 0.0;									// Cos angle Roll

	vX [1] = 1;
	vX [2] = 0;
	vX [3] = 0;

	vProj = this->GetSurfNormal();
	vProj[2] = 0;

	// case normal points perpendicular to zx plane
	if( equals( vProj[1], 0.0 ) && equals( vProj[3], 0.0 )) return (400);
	else 
	{
		// calculate angle aOrient between vProj & vSouth 
		// cos (aOrient) = (vProj * vSouth) / (|vProj| * |vSouth|)
		CosRoll = (float)( vProj * vX ) / ( (float)Norm( vProj ) * (float)Norm( vX) );
		aRoll = acos( CosRoll );
	}

	// convert radians to degrees
	// degre = 180 * (radian) / pi 
	aRoll = (float)180.0 * aRoll / (float) espR::PI  ; 

	if ( lessThan( vProj[2], 0.0 ) ) 
	{
		aRoll = (float)360.0 - aRoll;
		return (aRoll);
	}
	else return (aRoll);
}

int Surface3D::calcOrientation(						// Calculates & returns surface orientation (Front, Back...)
	float azimut )	const									// surface azimut 
{
	int iOrient = 0 ;

	if( azimut == espR::DOWN) return ( espR::DOWN );
	if( azimut == espR::UP) return ( espR::UP );
	if( lessThan(azimut, 135.0) && greaterOrEqualThan(azimut, 45.0) ) return (espR::RIGHT); // RIGHT
	if( lessThan(azimut, 225.0) && greaterOrEqualThan(azimut, 135.0) ) return (espR::FRONT); // FRONT
	if( lessThan(azimut, 315.0) && greaterOrEqualThan(azimut, 225.0) ) return (espR::LEFT); // LEFT
	else return (espR::BACK); // BACK

	return (iOrient);
}

int Surface3D::getOrientation() const
{
	return Orient;
}

void Surface3D::setOrientation(
	int Or) 
{
	this->Orient = Or;
}

void Surface3D::createBoundingBox(					// creates bounding box around surface 
	vector<Vertex3D> & Bbox )						
{
	// 1 bounding boxes will alway be || to the ground

	vector<Vertex3D>::iterator p;	// vector iterator

	int iOrient; // surface orientation
	
	//vector <Vertex3D> Bbox(4); // bounding box Vertex counter clockwise order : [0] = Lower Left, [1] = Lower Right..
	Vertex3D L; // Vertex value left limit of current surface
	Vertex3D R; // Vertex value right limit of current surface
	Vertex3D D; // Vertex value down limit of current surface
	Vertex3D U; // Vertex value up limit of current surface

	bool cll = false ; // counter lower left
	bool clr = false ; // counter lower right
	bool cur = false ; // counter upper right
	bool cul = false ; // counter upper left

	iOrient = this->getOrientation();

	// if surface orientation is UP (511) or DOWN (512)

	if( iOrient == espR::UP || iOrient == espR::DOWN )
	{
		// Find minimum x value in vertex list forming surface
		p = min_element(vVx.begin(), vVx.end(), Compare_vertex3D_xplus); // initialize left limit
		L = (*p);
			
		p = min_element(vVx.begin(), vVx.end(), Compare_vertex3D_yplus); // initialize down limit
		D = (*p);

		p = max_element(vVx.begin(), vVx.end(), Compare_vertex3D_xplus);
		R = (*p);

		p = max_element(vVx.begin(), vVx.end(), Compare_vertex3D_yplus);
		U = (*p);

		Bbox[0][1] = L[1];
		Bbox[0][2] = D[2];
		Bbox[0][3] = L[3];

		Bbox[1][1] = R[1];
		Bbox[1][2] = D[2];
		Bbox[1][3] = R[3];

		Bbox[2][1] = R[1];
		Bbox[2][2] = U[2];
		Bbox[2][3] = R[3];

		Bbox[3][1] = L[1];
		Bbox[3][2] = U[2];
		Bbox[3][3] = R[3];
	}
	else  // if orientation is not up or down
	{	
		// if surface orientation is front or back
		if ( iOrient == espR::FRONT || iOrient == espR::BACK ) 
		{
			// Find minimum x value in vertex list forming surface
			p = min_element(vVx.begin(), vVx.end(), Compare_vertex3D_xplus); // initialize left limit
			L = (*p);
				
			p = min_element(vVx.begin(), vVx.end(), Compare_vertex3D_zplus); // initialize down limit
			D = (*p);

			p = max_element(vVx.begin(), vVx.end(), Compare_vertex3D_xplus);
			R = (*p);

			p = max_element(vVx.begin(), vVx.end(), Compare_vertex3D_zplus);
			U = (*p);
		}

		// if surface orientation is left (103) or right (101)
		if ( iOrient == espR::LEFT  || iOrient== espR::RIGHT ) 
		{
			// Find minimum x value in vertex list forming surface
				
			p = min_element(vVx.begin(), vVx.end(), Compare_vertex3D_yplus); // initialize left limit
			L  = (*p);

			p = min_element(vVx.begin(), vVx.end(), Compare_vertex3D_zplus); // initialize down limit
			D = (*p);

			p = max_element(vVx.begin(), vVx.end(), Compare_vertex3D_yplus);
			R = (*p);

			p = max_element(vVx.begin(), vVx.end(), Compare_vertex3D_zplus);
			U = (*p);
		}

		// Define upper and lower y value 

		Bbox[0][3] = D[3]; // lower limit must be horizontal (to stay || to ground)
		Bbox[1][3] = D[3];
		Bbox[2][3] = U[3]; // upper limit must be horizontal (to stay || to ground)
		Bbox[3][3] = U[3];


		for ( unsigned int i = 0 ; i < this->vVx.size() ; i++ )
		{
			// if surface orientation is front or back
			if ( iOrient == espR::FRONT || iOrient == espR::BACK ) 
			{
				if( equals ( this->vVx[i][1], L [1]) && equals ( this->vVx[i][3], D [3]) ) 
				{
					Bbox[0] = this->vVx[i] ;
					cll = true;
				}

				if( equals ( this->vVx[i][1], R [1]) && equals ( this->vVx[i][3], D [3]) ) 
				{
					Bbox[1] = this->vVx[i] ;
					clr = true;
				}

				if( equals ( this->vVx[i][1], R [1]) && equals ( this->vVx[i][3], U [3]) ) 
				{
					Bbox[2] = this->vVx[i] ;
					cur = true;
				}

				if( equals ( this->vVx[i][1], L [1]) && equals ( this->vVx[i][3], U [3]) ) 
				{
					Bbox[3] = this->vVx[i] ;
					cul = true;
				}
			}// end if FRONT OR BACK

			// if surface orientation is left (103) or right (101)
			if ( iOrient == espR::LEFT  || iOrient== espR::RIGHT ) 
			{
				if( equals ( this->vVx[i][2], L [2]) && equals ( this->vVx[i][3], D [3]) ) 
				{
					Bbox[0] = this->vVx[i] ;
					cll = true;
				}

				if( equals ( this->vVx[i][2], R [2]) && equals ( this->vVx[i][3], D [3]) ) 
				{
					Bbox[1] = this->vVx[i] ;
					clr = true;
				}

				if( equals ( this->vVx[i][2], R [2]) && equals ( this->vVx[i][3], U [3]) ) 
				{
					Bbox[2] = this->vVx[i] ;
					cur = true;
				}

				if( equals ( this->vVx[i][2], L [2]) && equals ( this->vVx[i][3], U [3]) ) 
				{
					Bbox[3] = this->vVx[i] ;
					cul = true;
				}
			}


		} // end for i

		if ( cll == false ) calculateBoxCorner( D, L, Bbox[0] );
		if ( clr == false ) calculateBoxCorner( D, R, Bbox[1] ); 
		if ( cur == false ) calculateBoxCorner( U, R, Bbox[2] );
		if ( cul == false ) calculateBoxCorner( U, L, Bbox[3] );
		

	} // end else

	// if Bbox orientation is back, left OR down we must reoder the vertex
	if( iOrient == espR::BACK || iOrient == espR::LEFT || iOrient == espR::DOWN  ) 
	{
		Vertex3D VTmp;

		VTmp = Bbox[0];
		Bbox[0]= Bbox[1];
		Bbox[1]= VTmp;
		VTmp = Bbox[2];
		Bbox[2]= Bbox[3];
		Bbox[3]= VTmp;
	}
}

void Surface3D::calculateBoxCorner(					// calculate a given corner of surface bounding box
	const Vertex3D & H,									// Horizontal limit
	const Vertex3D & V,
	Vertex3D & Corner ) const				
{
	double pa; // polynomial coeff.
	double pb; // polynomial coeff.	
	double pc; // polynomial coeff.

	double i ; //coeff
	double e ; //coeff
	double f ; //coeff

	vector<double> polyres; 

	int iOrient = this->getOrientation();
	
	// vector3d CornerH = H - Corner
	// vector3d CornerV = V - Corner

	// CornerH & CornerV must be |_ so dot product == 0
	// 0 == ((H[1] - x) * (V[1] - x)) + ((H[2] - y) * (V[2] - y)) + 0
	// using the current surface equation ax + by + cz + d =0 we have
	// since we know z,
	// i = cz + d
	// y = (-a/b*x) + (i/b)
	// lets say a/b = e and i/b = f

	if ( iOrient == espR::FRONT  || iOrient== espR::BACK ) 
	{
		i = (this->c * H[3]) - (this->d); // - d because we put the equation in the form ax+bx+cz+d=0
		e = -(this->a) / this->b;
		f = - i / this->b;

		// solve dot product : polynomial -> pax2 + pbx + pc = 0
		pa = 1 + (e * e);
		pb = -H[1] - V[1] + (2.0 * e * f) - (V[2] * e) - (H[2] *e);
		pc = (H[1] * V[1]) + (f * f) - (V[2] * f) - (H[2] * f) + (H[2] * V[2]);

		solvePolynomial( pa, pb, pc, polyres );

		// If delta > 0, then there are two distinct roots, both of which are real numbers.
		if( polyres.size() > 1 )
		{ 
			//  test first value
			Corner[1] = polyres[0];
			Corner[2] = ( e * polyres[0] ) + f ;
			//Corner[3] =  ( - this->a * Corner[1] - this->b * Corner[2] + this->d) / (this->c);
			Corner[3] =  H[3]; //already known since lover limit parrallel to z axis
				
			if ( Corner == H || Corner == V ) // if the calculated corner == one of the 2 limit Vertex go to second value
			{	
				Corner[1] = polyres[1];
				Corner[2] = ( e * polyres[1] ) + f ;
				//Corner[3] =  ( - this->a * Corner[1] - this->b * Corner[2] + this->d) / (this->c);
				Corner[3] =  H[3]; //already known since lover limit parrallel to z axis
			}
		}
		else 
		{	
			// If delta == 0, then there is exactly one distinct real root
			if( polyres[0] != -999 )
			{ 
				Corner[1] = polyres[0];
				Corner[2] = ( e * polyres[0] ) + f ;
				//Corner[3] =  ( - this->a * Corner[1] - this->b * Corner[2] + this->d) / (this->c);
				Corner[3] =  H[3]; //already known since lover limit parrallel to z axis
			}
			// If delta < 0, then there are no real roots.
			else 
			{ 
				Corner[1] = -1;
				Corner[2] = -1;
				Corner[3] = -1;
			}
		}
	}
	
	if ( iOrient == espR::LEFT  || iOrient== espR::RIGHT ) 
	{
		i = (this->c * H[3]) - (this->d); // - d because we put the equation in the form ax+bx+cz+d=0
		e = -(this->b) / this->a;
		f = - i / this->a;

		// solve dot product : polynomial -> pax2 + pbx + pc = 0

		pa = 1 + (e * e);
		pb = -H[2] - V[2] + (2.0 * e * f) - (V[1] * e) - (H[1] *e);
		pc = (H[2] * V[2]) + (f * f) - (V[1] * f) - (H[1] * f) + (H[1] * V[1]);

		solvePolynomial( pa, pb, pc, polyres );

		// If delta > 0, then there are two distinct roots, both of which are real numbers.
		if( polyres.size() > 1 )
		{ 
			//  test first value
			Corner[2] = polyres[0];
			Corner[1] = ( e * polyres[0] ) + f ;
			//Corner[3] =  ( - this->a * Corner[1] - this->b * Corner[2] + this->d) / (this->c);
			Corner[3] =  H[3]; //already known since lover limit parrallel to z axis
				
			if ( Corner == H || Corner == V ) // if the calculated corner == one of the 2 limit Vertex go to second value
			{	
				Corner[2] = polyres[1];
				Corner[1] = ( e * polyres[1] ) + f ;
				//Corner[3] =  ( - this->a * Corner[1] - this->b * Corner[2] + this->d) / (this->c);
				Corner[3] =  H[3]; //already known since lover limit parrallel to z axis
			}
		}
		else 
		{	
			// If delta == 0, then there is exactly one distinct real root
			if( polyres[0] != -999 )
			{ 
				Corner[2] = polyres[0];
				Corner[1] = ( e * polyres[0] ) + f ;
				//Corner[3] =  ( - this->a * Corner[1] - this->b * Corner[2] + this->d) / (this->c);
				Corner[3] =  H[3]; //already known since lover limit parrallel to z axis
			}
			// If delta < 0, then there are no real roots.
			else 
			{ 
				Corner[1] = -1;
				Corner[2] = -1;
				Corner[3] = -1;
			}
		}
	}
}

bool Surface3D::areSurfCoplanar(					// Verifies if surface oS and current Surface are coplanar
	const Surface3D & oS ) const
{
	// if all points of oS verify equation of current surface, oS and current surface are coplanar
	int match = 0;

	// check for matches
	for( unsigned int i = 0; i < oS.vVx.size() ; i++ )
	{	
		if( equals(((this->a * oS.vVx[i][1]) + (this->b * oS.vVx[i][2]) + (this->c * oS.vVx[i][3]) - this->d), 0.0) ) 
		{
			match++;
		}
	}// end for
	
	if( match == oS.vVx.size())
	{
		return (true);
	}
	else return (false);
}

bool Surface3D::areSurfParallel(					// Verifies if surface oS is parrallel to current Surface
	const Surface3D & oS ) const
{
	Vector3D N1 = this->GetSurfNormal();
	Vector3D N2 = oS.GetSurfNormal();

	double cosA = (N1 * N2 ) / (Norm (N1) * Norm (N2));
	
	if( equals( fabs(cosA), 1.0 ))
	{
		return (true);
	}
	else return (false);

}

bool Surface3D::checkOverlap(						// Checks for overlap between 2 coplanar surfaces
	const Surface3D & oS ) const
{
	bool overlap = false;
	int match = 0;
	int mdout = 0;
	vector<Vertex3D> mdCur; // midpoints for all lines forming current surface
	vector<Vertex3D> mdOs;	// midpoints for all lines forming oS surface
	Line3D ln;
	Vertex3D mdPoint;
	int j;

	// create midpoints for current dans os surfaces
	for ( unsigned int i = 0; i< this->vVx.size(); i++ )
	{	
		j = (i + 1) % this->vVx.size();	// next vertex

		// set line
		ln.setLine( this->vVx[i], this->vVx[j] ); 
		mdPoint = ln.getMidPoint();
		mdCur.push_back ( mdPoint );
	}

	for ( unsigned int i = 0; i< oS.vVx.size(); i++ )
	{	
		j = (i + 1) % oS.vVx.size();	// next vertex

		// set line
		ln.setLine( oS.vVx[i], oS.vVx[j] ); 
		mdPoint = ln.getMidPoint();
		mdOs.push_back ( mdPoint );
	}
	
	// create copy of current surface
	Surface3D Ctmp;
	// create copy of oS surface
	Surface3D Otmp;

	Ctmp = *this;
	Otmp = oS;

	// 4 cases :
	// a) at least one summit of oS is inside current surface or vice versa
	// b) at least one of the midpoints is inside the other surface
	// c) all the summits of oS are on the edges of current surfaces or vice versa
	

	for( unsigned int i = 0; i< this->vVx.size(); i++ )
	{
		if( oS.IsVertexInside( this->vVx[i] ) == INSIDE ) return ( true );
		if( oS.IsVertexInside( mdCur[i] ) == INSIDE ) return ( true );
		if( oS.IsVertexInside( mdCur[i] ) == OUTSIDE ) mdout++ ;
		if( oS.IsVertexInside( this->vVx[i] ) == ONEDGE ) match ++ ;
	}
		
	if ( match == this->vVx.size() && mdout == 0 ) return ( true );
	else 
	{
		match = 0;
		mdout = 0;
	}
		
	for( unsigned int i = 0; i< oS.vVx.size(); i++ )
	{
		if( this->IsVertexInside( oS.vVx[i] ) == INSIDE ) return ( true );
		if( this->IsVertexInside( mdOs[i] ) == INSIDE ) return ( true );
		if( this->IsVertexInside( mdOs[i] ) == OUTSIDE ) mdout++ ;
		if( this->IsVertexInside( oS.vVx[i] ) == ONEDGE ) match ++ ;
	}

	if( match == oS.vVx.size() && mdout == 0 ) return ( true );

	// calculate both surfaces summits including intersections if they touch and are coplanar
	if ( this->checkTouching (oS) == true && this->areSurfCoplanar (oS) == true )
	{
		Ctmp.calcComSummits ( Otmp );
		// d) if we have a new summits in both surfaces when we calculate the intersection the surfaces overlap
		for ( unsigned int i = 0 ; i < Ctmp.vVx.size(); i++)
		{
			if ( IsVertexInList( this->vVx, Ctmp.vVx[i] ) == false &&  IsVertexInList( oS.vVx, Ctmp.vVx[i]) == false ) return ( true );
			
		}
		for ( unsigned int i = 0 ; i < Otmp.vVx.size(); i++)
		{
			if ( IsVertexInList( this->vVx, Otmp.vVx[i] ) == false &&  IsVertexInList( oS.vVx, Otmp.vVx[i]) == false ) return ( true );
			
		}
	}

	return ( overlap );
}


bool Surface3D::checkTouchOne(							// Checks if current surface and oS share only one summit
	const Surface3D & oS ) const
{
	Surface3D sC = *this ;	// copy of current surface
	Surface3D sO = oS ;		// copy of oS surface
	unsigned int onedg = 0;
	bool adjc = false;
	int j = 0 ;
	int k = 0 ; 

	sC.calcComSummits( sO );

	for( unsigned int i = 0; i< sC.vVx.size(); i++ )
	{
		j = (i + 1) % sC.vVx.size();	// next vertex
		k = i - 1 ; // previous vertex
		if ( i == 0 ) k = sC.vVx.size() - 1; 

		if( sO.IsVertexInside( sC.vVx[i] ) == ONEDGE && sO.IsVertexInside( sC.vVx[j] ) == OUTSIDE && sO.IsVertexInside( sC.vVx[k] ) == OUTSIDE ) 
		{
			return ( true );
		}
	}


	for( unsigned int i = 0; i< sO.vVx.size(); i++ )
	{
		j = (i + 1) % sO.vVx.size();	// next vertex
		k = i - 1 ; // previous vertex
		if ( i == 0 ) k = sO.vVx.size() - 1; 

		if( sC.IsVertexInside( sO.vVx[i] ) == ONEDGE && sC.IsVertexInside( sO.vVx[j] ) == OUTSIDE && sC.IsVertexInside( sO.vVx[k] ) == OUTSIDE ) 
		{
			return ( true );
		}

	}
	return ( adjc ) ;
}

bool Surface3D::checkTouching(							// Checks if current surface and oS edges are touching
	const Surface3D & oS ) const
{
	Surface3D sC = *this ;	// copy of current surface
	Surface3D sO = oS ;		// copy of oS surface
	unsigned int onedg = 0;
	bool adjc = false;
	int j = 0 ;
	int k = 0 ;

	sC.calcComSummits( sO );

	for( unsigned int i = 0; i< sC.vVx.size(); i++ )
	{
		j = (i + 1) % sC.vVx.size();	// next vertex
		k = i - 1 ; // previous vertex
		if ( i == 0 ) k = sC.vVx.size() - 1; 	

		if( sO.IsVertexInside( sC.vVx[i] ) == ONEDGE && sO.IsVertexInside( sC.vVx[j] ) == ONEDGE ) onedg ++ ;
		if( sO.IsVertexInside( sC.vVx[i] ) == ONEDGE && sO.IsVertexInside( sC.vVx[j] ) == OUTSIDE && sO.IsVertexInside( sC.vVx[k] ) == OUTSIDE ) return ( false );
	}

	if( onedg > 0 && onedg < sC.vVx.size() ) return ( true );


	for( unsigned int i = 0; i< sO.vVx.size(); i++ )
	{
		j = (i + 1) % sO.vVx.size();	// next vertex
		k = i - 1 ; // previous vertex
		if ( i == 0 ) k = sO.vVx.size() - 1; 

		if( sC.IsVertexInside( sO.vVx[i] ) == ONEDGE && sC.IsVertexInside( sO.vVx[j] ) == ONEDGE ) onedg ++ ;
		if( sC.IsVertexInside( sO.vVx[i] ) == ONEDGE && sC.IsVertexInside( sO.vVx[j] ) == OUTSIDE && sC.IsVertexInside( sO.vVx[k] ) == OUTSIDE ) return ( false );

	}

	if( onedg > 0 && onedg < sO.vVx.size() ) return ( true );

	return ( adjc ) ;
}

bool Surface3D::checkIncluded(							// Checks if oS is inside current without touching edges
	const Surface3D & oS ) const
{
	int ins = 0 ;

	for( unsigned int i = 0; i< oS.vVx.size(); i++ )
	{
		if( this->IsVertexInside( oS.vVx[i] ) == INSIDE ) ins++;
	}

	if( ins == oS.vVx.size() ) return (true);
	else return (false);
}

bool Surface3D::checkIncludedTouch(							// Checks if oS is inside current and touching edges
	const Surface3D & oS ) const 
{
	int ins = 0 ;
	int touch = 0 ;
	int j = 0 ;
	vector<Vertex3D> mdOs;	// midpoints for all lines forming oS surface
	vector<Vertex3D> mdT;	// midpoints for all lines forming current surface
	Line3D ln;
	Vertex3D mdPoint;

	for ( unsigned int i = 0; i< oS.vVx.size(); i++ )
	{	
		j = (i + 1) % oS.vVx.size();	// next vertex

		// set line
		ln.setLine( oS.vVx[i], oS.vVx[j] ); 
		mdPoint = ln.getMidPoint();
		mdOs.push_back ( mdPoint );
	}

	for ( unsigned int i = 0; i< this->vVx.size(); i++ )
	{	
		j = (i + 1) % this->vVx.size();	// next vertex

		// set line
		ln.setLine( this->vVx[i], this->vVx[j] ); 
		mdPoint = ln.getMidPoint();
		mdT.push_back ( mdPoint );
	}
		
	// if any mid point of current surface is inside oS than the surface is not included touch 
	for( unsigned int i = 0; i< this->vVx.size(); i++ )
	{
		if( oS.IsVertexInside( this->vVx[i] ) == INSIDE )return ( false );
		if( oS.IsVertexInside( mdT[i] ) == INSIDE ) return ( false );
	}
		
	for( unsigned int i = 0; i< oS.vVx.size(); i++ )
	{
		if( this->IsVertexInside( oS.vVx[i] ) == INSIDE ) ins++;
		if( this->IsVertexInside( oS.vVx[i] ) == ONEDGE ) touch++;
		if( this->IsVertexInside( mdOs[i] ) == OUTSIDE ) return ( false );
	}

	if( touch > 0 && (touch + ins) == oS.vVx.size() )return (true);
	else return (false);
}


void Surface3D::getIntSummits(							// Look through current surface summits and surface oS summits to find common points
	const Surface3D & oS,
	vector<Vertex3D> & Int ) const
{
	for( unsigned int i = 0; i< this->vVx.size(); i++ )
	{
		for( unsigned int j = 0; j< oS.vVx.size(); j++ )
		{
			if( this->vVx[i] == oS.vVx[j] ) Int.push_back(this->vVx[i]);
		}
	}
}

int Surface3D::getSurfRelation(						// Returns 6 possible surface relation  
	const Surface3D & oS ) const						// espR::NO_RELATION (501) -> non coplanar or parallel surfaces 
																// espR::PARALLEL (502) ->	parallel surfaces 
																// espR::COPLANAR (503) -> coplanar surfaces
																// espR::COPLSHAREONE (504) -> share one summit
																// espR::ADJACENT (505) -> coplanar & adjacent surfaces (share 2 or more consecutive summits)
																// espR::OVERLAPPING (506) -> coplanar & overlapping surfaces
																// espR::INCLUDED (507)-> Os is inside current surface without touching edges
																// espR::INCLUDEDTOUCH (508)-> Os is inside current surface and touching edges
{
	int status = 0;
	
	//Equations must be set!
	//this->SetSurfEquation();
	//oS.SetSurfEquation();
	
	// 1- non coplanar or parallel surfaces 
	if ( this->areSurfParallel(oS) == false && this->areSurfCoplanar(oS) == false ) status = espR::NO_RELATION ;
	
	// 2- parallel surfaces 
	if ( this->areSurfParallel(oS) == true && this->areSurfCoplanar(oS) == false )	status = espR::PARALLEL ;

	// 3- coplanar surfaces 
	if ( this->areSurfCoplanar(oS) == true ) status = espR::COPLANAR ;

	// 4- coplanar & adjacent surfaces (share 1 summit)
	if ( this->areSurfCoplanar(oS) == true && this->checkTouchOne(oS) == true && this->checkOverlap(oS) == false ) status = espR::COPLSHAREONE ;

	// 5- coplanar & adjacent surfaces (share 2 or more consecutive summits)
	if ( this->areSurfCoplanar(oS) == true && this->checkTouching(oS) == true && this->checkOverlap(oS) == false ) status = espR::ADJACENT ;
	
	// 6- overlapping surfaces
	if ( this->areSurfCoplanar(oS) == true && this->checkOverlap(oS) == true ) status = espR::OVERLAPPING ;

	// 7- included surface without touching edges
	if ( this->areSurfCoplanar(oS) == true && this->checkIncluded(oS) == true) status = espR::INCLUDED ;

	// 8- included surface and touching edges
	if ( this->areSurfCoplanar(oS) == true && this->checkIncludedTouch(oS) == true) status = espR::INCLUDEDTOUCH ;

	

	return (status);
}

void Surface3D::calcComEdge(				// Calculates common summits for 2 adjacent coplanar surfaces (Current surface & sO)
	Surface3D & sO,
	vector<Vertex3D> & vEdge)
{
	
	int j,l;		// counters
	Line3D Lt1; // Test line edge of current surface
	Line3D Lt2; // Test line edge of sO surface
	Vertex3D vIt; // Intersection vertex
	; // vector of intersection for line i
	
	// surfaces musts be adjacent if not retur an impossible edge
	if ( this->checkTouching ( sO ) == false ) 
	{
		vIt[1] = -99;
		vIt[2] = -99;
		vIt[3] = -99;
		vEdge.push_back( vIt ) ;
	}

	else
	{
		double a1 = this->alignX();
		double a2 = this->alignZ();
		double a3 = sO.alignX();
		double a4 = sO.alignZ();
			
		// Create intersection list for current surface
		for( unsigned int i = 0; i< this->vVx.size(); i++ )
		{	
			j = (i + 1) % this->vVx.size(); // next point
			// set line current surface
			Lt1.setLine( this->vVx[i], this->vVx[j] );	

			for( unsigned int k = 0; k< sO.vVx.size(); k++ )
			{		
				l = (k + 1) % sO.vVx.size();
				Lt2.setLine( sO.vVx[k], sO.vVx[l] ); // set line sO surface

				// check if sO.vVx[k] is an intersection of both surfaces and add it to the list 
				if ( (Lt1.isVertexOnLine( sO.vVx[k], a1, a2) == true ) && (Lt2.isVertexOnLine( sO.vVx[k], a3, a4) == true ) ) 
				{					
					// put It in the list of Vector3D to class for this edge
					if ( IsVertexInList( vEdge, sO.vVx[k]) == false ) 
						vEdge.push_back(sO.vVx[k]);
				}	// end if ONEDGES
			
				// then verify line intersection
				// only calculate intersection if Lines cross
				if( Lt1.doLineCross(Lt2) == true )
				{
					// Calculate intersection
					Lt1.getIntersection(Lt2,vIt);

					if( ( Lt1.isVertexOnLine( vIt, a1, a2 ) == true ) && ( Lt2.isVertexOnLine( vIt, a3, a4 ) == true ) ) 
					{					
						// put It in the list of Vector3D to class for this edge
						if ( IsVertexInList( vEdge, vIt ) == false ) 
							vEdge.push_back( vIt ); 
					}	// end if ONEDGES
				} // end if lines not parrallel
			}// end for k
		}// end for i
	}// end else
}					
void Surface3D::calcComSummits(				// Calculates common summits for 2 adjacent coplanar surfaces (Current surface & oS)
	Surface3D & oS )
{
	Line3D Lt1; // Test line edge of current surface
	Line3D Lt2; // Test line edge of oS surface

	Vertex3D It; // Intersection vertex
	vector<Vertex3D> VtoClass; // vector of intersection for line i
	vector<Line3D> ltst; // vector of 3D Lines to test
	vector <Surface3D> Stmp(2); // temporary surfaces
	vector<vector<Vertex3D> > ThisEdges ;	// Vector of edges for Current Surface
	vector<vector<Vertex3D> > oSEdges ;		// Vector of edges for oS Surface
	Line3D CLine; // test line 

	double a1 = this->alignX();
	double a2 = this->alignZ();

	double a3 = oS.alignX();
	double a4 = oS.alignZ();

	int j;		// counter
	int l;		// counter

	// Create intersection list for current surface
	for( unsigned int i = 0; i< this->vVx.size(); i++ )
	{	
		j = (i + 1) % this->vVx.size(); // next point
		// set line current surface
		Lt1.setLine( this->vVx[i], this->vVx[j] );	

		for( unsigned int k = 0; k< oS.vVx.size(); k++ )
		{		
			l = (k + 1) % oS.vVx.size();
			Lt2.setLine( oS.vVx[k], oS.vVx[l] ); // set line oS surface

			// check if oS.vVx[k] is an intersection of both surfaces and add it to the list 
			if ( (Lt1.isVertexOnLine( oS.vVx[k], a1, a2) == true ) && (Lt2.isVertexOnLine( oS.vVx[k], a3, a4) == true ) ) 
						{					
							// put It in the list of Vector3D to class for this edge
							if ( IsVertexInList( this->vVx, oS.vVx[k] ) == false ) VtoClass.push_back(oS.vVx[k]); 

						}	// end if ONEDGES
			
			// then verify line intersection
			// only calculate intersection if Lines cross
			if( Lt1.doLineCross(Lt2) == true )
			{
				// Calculate intersection
				Lt1.getIntersection(Lt2,It);

				if( ( Lt1.isVertexOnLine( It, a1, a2 ) == true ) && ( Lt2.isVertexOnLine( It, a3, a4 ) == true ) ) 
				{					
					// put It in the list of Vector3D to class for this edge
					if ( IsVertexInList( this->vVx, It ) == false ) VtoClass.push_back( It ); 
				}	// end if ONEDGES

			} // end if lines not parrallel

		}// end for k

		// Put intersections in the correct order for every edge, 
		// starting with the intersection closest to the first corner
		if( VtoClass.size() > 0 ) 
		{
			// Create new line vector to clssify intersections
			// For every intersection point 
			// Create a line between intersection and first edge corner.
			for( unsigned int f = 0; f < VtoClass.size() ; f++ )
			{
				CLine.setLine(Lt1.getStart(),VtoClass[f]);
				ltst.push_back(CLine);
			}

			// Sort every intersection
			sort( ltst.begin(), ltst.end(), Compare_Length );		

			// Append intersection points
			for( unsigned int f = 0; f < ltst.size() ; f++ )
			{
				VtoClass[f] = ltst[f].getEnd();
			}// end for i

			// Empty temporary vector
			ltst.clear();
		} // end if (*VtoClass) is not empty

		// Insert Start point of edge
		VtoClass.insert( VtoClass.begin(),  Lt1.getStart() );
		
		// Append end point of edge
		VtoClass.push_back( Lt1.getEnd());

		// Append VtoClass to the list of edges forming current surface
		ThisEdges.push_back( VtoClass );

		// Empty temporary vectors
		VtoClass.clear();
				
	}// end for i

	// Create intersection list for oS surface

	for( unsigned int i = 0; i < oS.vVx.size(); i++ )
	{	
		j = (i + 1) % oS.vVx.size();	// next vertex

		// set line oS surface
		Lt1.setLine( oS.vVx[i], oS.vVx[j]); 

		for( unsigned int k = 0; k < this->vVx.size(); k++ )
		{
			l = (k + 1) % this->vVx.size();
			Lt2.setLine( this->vVx[k], this->vVx[l]);	// set line current surface

			// check if oS.vVx[k] is an intersection of both surfaces and add it to the list 
			if ( (Lt1.isVertexOnLine( this->vVx[k], a3, a4) == true ) && (Lt2.isVertexOnLine( this->vVx[k], a1, a2) == true ) ) 
			{					
				// put It in the list of Vector3D to class for this edge
				if ( IsVertexInList( oS.vVx, this->vVx[k] ) == false ) VtoClass.push_back(this->vVx[k]); 
			}	// end if ONEDGES
				
			if ( Lt1.doLineCross(Lt2) == true )
			{
				Lt1.getIntersection(Lt2,It);
							
				if( ( Lt1.isVertexOnLine( It, a3, a4 ) == true ) && ( Lt2.isVertexOnLine( It, a1, a2 ) == true ) ) 
				{					
					// put It in the list of Vector3D to class for this edge
					if ( IsVertexInList( oS.vVx, It ) == false ) VtoClass.push_back(It); 
				}	// end if ONEDGES

			} // end if lines not parrallel
	 
		}// end for k

		// Put intersections in the correct order for every edge, 
		// starting with the intersection closest to the first corner

		if( VtoClass.size() > 0 ) 
		{					
			// Create new line vector to clssify intersections
			// For every intersection point 
			// Create a line between intersection and first edge corner.
			for( unsigned int f = 0; f < VtoClass.size() ; f++ )
			{
				CLine.setLine( Lt1.getStart(), VtoClass[f] );
				ltst.push_back(CLine);
			}

			// Sort every intersection
			sort( ltst.begin(), ltst.end(), Compare_Length );		

			// Append intersection points
			for( unsigned int f = 0; f < ltst.size() ; f ++)
			{
				VtoClass[f] = ltst[f].getEnd();
			}// end for i

			// Empty temporary vector
			ltst.clear();

		} // end if (*VtoClass) is not empty

		// Insert Start point of edge
		VtoClass.insert( VtoClass.begin(), Lt1.getStart() );
				
		// Append end point of edge
		VtoClass.push_back( Lt1.getEnd());

		// Append (*VtoClass) to the list of edges forming current surface
		oSEdges.push_back( VtoClass );

		// Empty temporary vectors
		VtoClass.clear();
				
	}// end for i

	// Recreate current surface in Stmp[0] with recalculated edges (including intersections)
	for( unsigned int i = 0; i < ThisEdges.size(); i++ )
	{
		for( unsigned int j = 0; j < ThisEdges[i].size() ; j ++)
		{
			if( IsVertexInList( Stmp[0].vVx, ThisEdges[i][j] ) == false ) Stmp[0].vVx.push_back( ThisEdges[i][j] );
		}// end for j
				
	}// end for i

	this->vVx = Stmp[0].vVx;
		
	// Recreate oS surface in Stmp[1] with recalculated edges (including intersections)
	for( unsigned int i = 0; i < oSEdges.size(); i++ )
	{
		for( unsigned int j = 0; j < oSEdges[i].size(); j++ )
		{
			if( IsVertexInList( Stmp[1].vVx, oSEdges[i][j] ) == false ) Stmp[1].vVx.push_back( oSEdges[i][j] );
		}// end for j
				
	}// end for i

	oS.vVx = Stmp[1].vVx;
}					

		
void Surface3D::calcSurfInt(							// Calculates intersection between current surface and surface oS (both surfaces must be coplanar)
	Surface3D & oS,
	Surface3D & Int,										// intersection
	vector<Surface3D> & Res1,
	vector<Surface3D> & Res2 )
{
	int j;		// counter
	Vertex3D dummy;
	vector<Surface3D> Stmp(2); // temporary surfaces
	vector<vector<int>> inters (2); // Vector of intersection vertices for both surfaces
	
	// Make sure Int is emty
	if( Int.vVx.size() > 0 ) 
	{
		Int.vVx.clear();
	}


	// 1 if oS == current surface
	if ( *this == oS  ) 
	{	
		Int = *this;
		return;
	}
	
	// 2 if oS is included in current surface
	if ( this->getSurfRelation(oS) == espR::INCLUDED ) 
	{	
		Int = oS;
		return;
	}

	// 3 if current surface is included in oS
	if ( oS.getSurfRelation(*this) == espR::INCLUDED ) 
	{
		Int = *this;
		return;
	}
	
	// Calculate common summits between current surface ans oS
	this->calcComSummits( oS );

	// Copy vertex from both surfaces into temporary surfaces
	Stmp[0].vVx = this->vVx;
	Stmp[1].vVx = oS.vVx;

	// Identify intersection points and create lists in inters[0] and inters[1]
	for( unsigned int i = 0; i < Stmp[0].vVx.size() ; i++ )
	{
		if( findVertexInList( Stmp[1].vVx, Stmp[0].vVx[i] ) != -1 ) // Louis: préférable de comparer à -1?
		{
			inters[0].push_back(i);
		}
	}// end for i

	for( unsigned int i = 0; i < Stmp[1].vVx.size() ; i++ )
	{
		if( findVertexInList( Stmp[0].vVx, Stmp[1].vVx[i] ) != -1 ) // Louis: préférable de comparer à -1?
		{
			inters[1].push_back(i);
		}
	}// end for i

	// create temporary vector same size  as Stmp[1]
	vector<Vertex3D> vAlign( Stmp[1].vVx.size(), dummy );
	
	// create temporary vector same size  as inters[1]
	vector<int> vAInts( inters[1].size(), 0 );

	// then we must align the 2 surfaces so the first intersection point in Stmp[0]
	// is also the first intersection point in Stmp[1]

	// Copy vertex in vAling in the new correct order

	int fint = findVertexInList( Stmp[1].vVx, Stmp[0].vVx[inters[0][0]] );

	for( unsigned int i = 0; i < Stmp[1].vVx.size(); i++ )
	{	
		vAlign[i] = Stmp[1].vVx[fint];	
		fint = ( fint + 1) % Stmp[1].vVx.size();
	}

	for( unsigned int i = 0; i < inters[1].size(); i++ )
	{	
		fint = findVertexInList( vAlign, Stmp[1].vVx[inters[1][i]] );
		vAInts[i] = fint; 
	}

	sort( vAInts.begin(), vAInts.end() );

	// put the vertex of Stmp[1] in the same order as vAlign
	Stmp[1].vVx = vAlign; 
	inters[1] = vAInts; 

	vAlign.clear();
	vAInts.clear();
			
	// go through Stmp1 starting with firt intersection point -> inters[0][0]

	// Set start vertex
	Vertex3D start = Stmp[0].vVx[inters[0][0]];

	Vertex3D test;
	int side = 0;
		
	// Append first intersection point to Int
	Int.vVx.push_back(Stmp[0].vVx[inters[0][0]]);

	for( unsigned int i = (inters[side][0]) + 1; test != start; i++ )
	{
		j = i % Stmp[side].vVx.size();

		// go to next point 
		// if next point is outside, go to next point in other surface
		if( side == 0 ) // current side == 0
		{
			if( oS.IsVertexInside(Stmp[0].vVx[j]) == INSIDE || oS.IsVertexInside(Stmp[0].vVx[j]) == ONEDGE)
			{
				Int.vVx.push_back(Stmp[0].vVx[j]);
				test = Int.vVx.back();
			}

			else
			{
				// change side
				side = 1;
							
				// find position of current intersection in oS vertex list
				i = findVertexInList( Stmp[1].vVx, Int.vVx.back() );
			}
		}
		else // curent side == 1 
		{
			if( this->IsVertexInside(Stmp[1].vVx[j]) == INSIDE || this->IsVertexInside(Stmp[1].vVx[j]) == ONEDGE)
			{
				Int.vVx.push_back(Stmp[1].vVx[j]);
				test = Int.vVx.back();
			}
			else
			{
				// change side
				side = 0;

				// find position of current intersection in oS vertex list
				i = findVertexInList( Stmp[0].vVx, Int.vVx.back() );
			}
		}
	} // end for

	Int.vVx.pop_back(); // remove last point (dupicated)

	// Set up equations for intersection
	Int.elimWrongVertices();
	Int.copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient );
	Int.putLowLeftFirst();
	
	int x;	// counter
	int y;	// counter

	int d0;	// counter
	int d1; // counter

	// Create all sub surfaces

	// for all intersecion vertices
	for( unsigned int i = 0; i < inters[0].size(); i++ )
	{
		j = (i + 1) % inters[0].size(); //point following i

		// if the 2 intersection point are not consecutive on one of the 2 original surfaces
		// create a new surface
		if( ( inters[0][j] - inters[0][i] ) != 1 || ( inters[1][j] - inters[1][i] ) != 1 )
		{
			Surface3D out;

			// first append first intersection point to new surf
			out.vVx.push_back( Stmp[0].vVx[inters[0][i]] );

			x = (inters[0][i] + 1)  % Stmp[0].vVx.size(); // point following intersection in Stmp[0]
			y = (inters[1][i] + 1)  % Stmp[1].vVx.size(); // point following intersection in Stmp[1]
				
			// figure out if 2 intersection points are consecutive on current surface
			d0 = (inters[0][j] - inters[0][i]);
			if( d0 < 0 ) d0 = (inters[0][j] + Stmp[0].vVx.size()) - inters[0][i]; // special case for intersection 1 on last segment and intersection 1 on firts segment 

			// figure out if 2 intersection points are consecutive on oS surface
			d1 = (inters[1][j] - inters[1][i]);
			if (d1 < 0 ) d1 = (inters[1][j] + Stmp[1].vVx.size()) - inters[1][i]; // special case for intersection 1 on last segment and intersection 1 on firts segment

			// then append points of surface that are outside the intersection
			if( d0 > 1 ) 
			{ 
				if( Int.IsVertexInside(Stmp[0].vVx[x]) == OUTSIDE )
				{	
					side = 0; // set side to 0
				}// end if 
			}// end if d0

			if( d1 > 1 )
			{ 
				if( Int.IsVertexInside(Stmp[1].vVx[y]) == OUTSIDE ) 
				{	
					side = 1; // set side to 1
				}
			}// end if d1

			// Append all outside points first
			if( side == 0 )
			{
				for (int n = 1 ; n < d0 ; n++)
				{
					x = (inters[0][i] + n)  % Stmp[0].vVx.size();
					out.vVx.push_back(Stmp[0].vVx[x]);
				}// end for

				// append second intersection
				out.vVx.push_back(Stmp[0].vVx[inters[0][j]]);

				// append inside points frome side 1 in inverse order

				for( int n = (d1-1); n > 0; n-- )
				{
					x = (inters[1][i] + n)  % Stmp[1].vVx.size();
					out.vVx.push_back(Stmp[1].vVx[x]);
				}// end for
			}// end side =0 

			if( side == 1 )
			{
				for( int n = 1; n < d1; n++ )
				{
					y = (inters[1][i] + n)  % Stmp[1].vVx.size();
					out.vVx.push_back(Stmp[1].vVx[y]);
				}// end for

				// append second intersection
				out.vVx.push_back(Stmp[0].vVx[inters[0][j]]);

				// append inside points from side 0 in inverse order
				for( int n = d0-1; n > 0; n-- )
				{
					x = (inters[0][i] + n)  % Stmp[0].vVx.size();
					out.vVx.push_back(Stmp[0].vVx[x]);
				}// end for
			}// end side =1
			
			// if out has more than 2 points	
			if( out.vVx.size() > 2 )
			{
				// if second point of out is inside current surface append out to Res1
				// else append out to Res2
				if( this->IsVertexInside( out.vVx[1] ) == ONEDGE ) Res1.push_back( out );
				else Res2.push_back( out );
			}
		}// end if
	}// end for i

	// put lower left corner first in vVX for every surface and set up equations
	for( unsigned int i = 0; i < Res1.size(); i++ )
	{
		Res1[i].elimWrongVertices();
		Res1[i].copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient);
		Res1[i].putLowLeftFirst();
	}

	for (unsigned int i =0 ;  i < Res2.size(); i++)
	{
		Res2[i].elimWrongVertices();
		Res2[i].copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient);
		Res2[i].putLowLeftFirst();
	}
}

void Surface3D::mergeSurf(								// Calculates current surface + oS surface
	Surface3D & oS,
	Surface3D & SMerged )								// resulting surface
{
	Vertex3D dummy;

	// 1 if oS == current surface
	if ( *this == oS  ) 
	{	
		SMerged = *this;
		return;
	}
	
	// 2 if oS is included in current surface
	if ( this->getSurfRelation(oS) == espR::INCLUDED || this->getSurfRelation(oS) == espR::INCLUDEDTOUCH  ) 
	{	
		SMerged = *this;
		return;
	}

	// 3 if current surface is included in oS
	if ( oS.getSurfRelation(*this) == espR::INCLUDED || oS.getSurfRelation(*this) == espR::INCLUDEDTOUCH ) 
	{
		SMerged = oS;
		return;
	}
	
	vector <Surface3D> Stmp(2); // temporary surfaces
	vector<vector<int> > inters (2); // Vector of intersection vertices for both surfaces
	
	// Calculate common summits between current surface ans oS
	this->calcComSummits ( oS);
	//this->calcComSummits ( oS, Stmp[0], Stmp[1] );

	int j;		// counter
	
	// Copy vertex from both surfaces into temporary surfaces
	Stmp[0].vVx = this->vVx;
	Stmp[1].vVx = oS.vVx;

	// Identify intersection points and create lists in inters[0] and inters[1]
	for( unsigned int i = 0; i < Stmp[0].vVx.size(); i++ )
	{
		if( findVertexInList( Stmp[1].vVx, Stmp[0].vVx[i] ) != -1 )
		{
			inters[0].push_back(i);
		}
	}// end for i

	for( unsigned int i = 0; i < Stmp[1].vVx.size(); i++ )
	{
		if( findVertexInList( Stmp[0].vVx, Stmp[1].vVx[i] ) != -1 )
		{
			inters[1].push_back(i);
		}
	}// end for i

	// create temporary vector same size  as Stmp[1]
	// vector<Vertex3D> *vAlign = new vector<Vertex3D> (Stmp[1].vVx.size());
	vector<Vertex3D> vAlign( Stmp[1].vVx.size(), dummy );

	// create temporary vector same size  as inters[1]
	// vector<int> *vAInts = new vector<int> (inters[1].size());
	vector<int> vAInts( inters[1].size(), 0 );

	// then we must align the 2 surfaces so the first intersection point in Stmp[0]
	// is also the first intersection point in Stmp[1]

	// Copy vertex in vAling in the new correct order

	int fint = findVertexInList( Stmp[1].vVx, Stmp[0].vVx[inters[0][0]] );

	for( unsigned int i = 0; i < Stmp[1].vVx.size(); i++ )
	{	
		vAlign[i] = Stmp[1].vVx[fint];	
		fint = ( fint + 1 ) % Stmp[1].vVx.size();
	}

	for( unsigned int i = 0; i < inters[1].size(); i++ )
	{	
		fint = findVertexInList( vAlign, Stmp[1].vVx[inters[1][i]] );
		vAInts[i] = fint; 
	}

	sort( vAInts.begin(), vAInts.end() );

	// put the vertex of Stmp[1] in the same order as vAlign
	Stmp[1].vVx = vAlign; 
	inters[1] = vAInts; 

	vAlign.clear();
	vAInts.clear();
			
	int x;	// counter
	int y;	// counter

	int d0;	// counter
	int d1; // counter

	int side;
	int chside = 0;

	// Create all sub surfaces

	// for all intersecion vertices
	for( unsigned int i = 0; i < inters[0].size(); i++ )
	{
		j = (i + 1) % inters[0].size(); //point following i

		x = (inters[0][i] + 1)  % Stmp[0].vVx.size(); // point following intersection in Stmp[0]
		y = (inters[1][i] + 1)  % Stmp[1].vVx.size(); // point following intersection in Stmp[1]

		// if the 2 intersection point are not consecutive on one of the 2 original surfaces
		// create a new surface 
		// if( (inters[0][j] - inters[0][i]) != 1 || (inters[1][j] - inters[1][i]) != 1 )
		if( this->IsVertexInside( Stmp[1].vVx[ y ] ) == OUTSIDE || oS.IsVertexInside( Stmp[0].vVx[ x ]) == OUTSIDE )
		{
			// first append first intersection point to new surf
			if ( chside == 0) 
			{	
				if ( this->IsVertexInside( Stmp[1].vVx[ y ] ) == OUTSIDE ) SMerged.vVx.push_back(Stmp[1].vVx[inters[1][i]]);
				else  SMerged.vVx.push_back(Stmp[0].vVx[inters[0][i]]);	
			}

			else 
			{
				if ( side == 0) SMerged.vVx.push_back(Stmp[1].vVx[inters[1][i]]);
				else SMerged.vVx.push_back(Stmp[0].vVx[inters[0][i]]);
			}
				
				
			// figure out if 2 intersection points are consecutive on current surface
			d0 = (inters[0][j] - inters[0][i]);
			if (d0 < 0 ) d0 = (inters[0][j] + Stmp[0].vVx.size()) - inters[0][i]; // special case for intersection 1 on last segment and intersection 1 on firts segment 

			// figure out if 2 intersection points are consecutive on oS surface
			d1 = (inters[1][j] - inters[1][i]);
			if (d1 < 0 ) d1 = (inters[1][j] + Stmp[1].vVx.size()) - inters[1][i]; // special case for intersection 1 on last segment and intersection 1 on firts segment
				
			// then append points of surface that are outside the intersection
			if( d0 > 1 && d0 > d1 ) 
			{ 
				if( oS.IsVertexInside(Stmp[0].vVx[x]) == OUTSIDE )
				{	
					side = 0; // set side to 0
				}// end if 
			}// end if d0

			if( d1 > 1 && d1 > d0 )
			{ 
				if( this->IsVertexInside(Stmp[1].vVx[y]) == OUTSIDE ) 
				{	
					side = 1; // set side to 1
				}
			}// end if d1

			// Append all outside points 
			if( side == 0 )
			{
				chside ++;
				for( int n = 1; n < d0; n++ )
				{
					x = (inters[0][i] + n)  % Stmp[0].vVx.size();
					SMerged.vVx.push_back(Stmp[0].vVx[x]);
				}// end for

				if (d1 > 1 && d0 > 1 )
				{
					for( int n = 1 ;n < d1 ;n++ )
					{
						y = (inters[1][i] + n)  % Stmp[1].vVx.size();
						SMerged.vVx.push_back(Stmp[1].vVx[y]);
					}// end for
					chside ++;
				}// end if 

			}// end side =0 

			if( side == 1 )
			{
				chside ++;
				for( int n = 1 ;n < d1 ;n++ )
				{
					y = (inters[1][i] + n)  % Stmp[1].vVx.size();
					SMerged.vVx.push_back(Stmp[1].vVx[y]);
				}// end for

				if (d1 > 1 && d0 > 1 )
				{
					for( int n = 1 ;n < d1 ;n++ )
					{
						x = (inters[0][i] + n)  % Stmp[0].vVx.size();
						SMerged.vVx.push_back(Stmp[0].vVx[x]);
					}// end for
					chside ++;
				}// end if 

			}// end side =1
		}// end if

		else 
		{
			continue;
		}
	}// end for i

	// add next vertex if needed to close polygon if there was only one change of side
	if ( chside == 1 ) 
	{
		if ( side ==0 )
		{
			x = findVertexInList(Stmp[0].vVx, SMerged.vVx.back());
			y = (x + 1)  % Stmp[0].vVx.size(); // point following intersection in Stmp[1]
			SMerged.vVx.push_back(Stmp[0].vVx[y]);
		}
		else 
		{
			x = findVertexInList(Stmp[1].vVx, SMerged.vVx.back());
			y = (x + 1)  % Stmp[1].vVx.size(); // point following intersection in Stmp[1]
			SMerged.vVx.push_back(Stmp[1].vVx[y]);
		}
	}

	//Set surface equations according to current surface equation
	SMerged.copySurfEquation( this->a, this->b, this->c, this->d, this->Normal, this->Orient);

	// put lower left corner first in SMerged
	SMerged.putLowLeftFirst();
}

bool Surface3D::doSurfsFormValley(
			Surface3D & sO)
{
	
	vector<Vertex3D> vEg;
	double dLC ;
	double dLO;
	Vertex3D vI(-99,-99,-99);

	// find current surface lowest vertex
	dLC = this->vVx[0][3];
	for( unsigned int i = 1; i < this->vVx.size(); i++)
	{
		if ( lessThan( this->vVx[i][3], dLC ) ) 
			dLC = this->vVx[i][3];
	}

	// find second surface lowest vertex
	dLO = sO.vVx[0][3];
	for( unsigned int i = 1; i < sO.vVx.size(); i++)
	{
		if ( lessThan( sO.vVx[i][3], dLO  ) ) 
			dLO = sO.vVx[i][3];
	}

	// surfaces must share lowest vertex
	if ( equals ( dLC, dLO ) == false ) return false;

	// calculate common edge 
	this->calcComEdge ( sO, vEg );

	if ( vEg[0] == vI) 
		return ( false );

	if ( this->areSurfCoplanar (sO) == true ) return ( false );

	if ( equals( (double) 0.0, this->GetSurfNormal()[3] ) &&  equals( (double) 0.0, sO.GetSurfNormal()[3] )  )
		return ( false );
	else
	{
		for( unsigned int i = 1; i < vEg.size(); i++)
		{
			if ( equals ( vEg[i][3], dLC ) == false )
				return ( false );
		}

		return ( true );
	}

}

void Surface3D::getIntersection(				// Calculates intersection between current surface and surface oS 
	Surface3D & oS,
	Surface3D & Inter )
{
	vector<Surface3D> R1;
	vector<Surface3D> R2;	

	this->calcSurfInt( oS, Inter, R1, R2 );
}

void Surface3D::getCurrentMinusOS(				// Calculates resulting surfaces when we substract oS to current
	Surface3D & oS,
	vector<Surface3D> & ResCur )
{
	vector<Surface3D> R;
	Surface3D I;	

	this->calcSurfInt( oS, I, ResCur, R );
}

void Surface3D::getOSMinusCurrent(					// Calculates resulting surfaces when we substract current to oS 
	Surface3D & oS,
	vector<Surface3D> & ResOS )
{
	vector<Surface3D> R;
	Surface3D I;	

	this->calcSurfInt( oS, I, R, ResOS );
}
	
double Surface3D::calcPerim()	const					// Calculates current surface perimeter
{
	Line3D ln;			// Line
	double perim = 0 ;	// premimeter
	unsigned int j ;	// counter
	
	for( unsigned int i = 0; i < this->vVx.size(); i++ )
	{
		j = (i + 1) % this->vVx.size(); // next point
		
		// set line 
		ln.setLine( this->vVx[i], this->vVx[j]);
		perim = perim + ln.getLength();
	}
	
	return (perim);
}		

double Surface3D::calcArea() const					// Calculates current surface area
{
	Surface3D Stst; // temporary surface
	double area = 0;
	vector<Vertex3D> mbox(4);
	double a1 = this->alignX();
	double a2 = this->alignZ();

	double tmpX = 0;
	double tmpY = 0;	
	double sumX = 0;
	double sumY = 0;

	unsigned int j ;	// counter

	//Create a copy of current surface
	Stst = *this;
	
	// 1 Calculate bounding box for current surface
	Stst.createBoundingBox(mbox);
	
	// 2 Bring surface to origin	
	Stst.translation (- mbox[0][1] , - mbox[0][2], - mbox[0][3]);

	// 3 align on x by rotating aroud z
	Stst.rotateZ ( - a1 );

	// 4 align normal with z by rotating around x
	Stst.rotateX ( - a2 );

	// 5 Calculate area

	// 6 List the x and y coordinates of each vertex of the polygon in counterclockwise order. 
	//   Repeat the coordinates of the first point at the bottom of the list.
	
	for( unsigned int i = 0; i< Stst.vVx.size(); i++)
	{
		j = (i + 1) % Stst.vVx.size(); // next point
	
		// 7 Multiply the x coordinate of each vertex by the y coordinate of the next vertex. 
		//   Add these
		tmpX = Stst.vVx[i][1] * Stst.vVx[j][2];
		sumX = sumX + tmpX;
		
		// 8 Multiply the y coordinate of each vertex by the x coordinate of the next vertex. 
		//   Add these.
		tmpY = Stst.vVx[i][2] * Stst.vVx[j][1];
		sumY = sumY + tmpY;
	}
	
	// 9 Subtract the sum of the products computed in step 8 from the sum of the products from step 7.
	area = sumX - sumY;
	
	// 10 Divide this difference by 2 to get the area of the polygon.
	area = area / 2;	

	if ( lessThan( area , float(0.0))) area = - area;

	return (area);
}

double Surface3D::getWidth() const					// Calculates current surface width (of bounding box)
{
	vector<Vertex3D> mbox(4);							// bounding box
	Line3D ln;												// Line
	Surface3D S = *this;

	// 1 Calculate bounding box for current surface
	S.createBoundingBox( mbox );

	// 2 Set line 
	ln.setLine( mbox[0], mbox[1] );
	return( ln.getLength() );
}

double Surface3D::getHeight() const					// Calculates current surface height (of bounding box)
{
	vector<Vertex3D> mbox(4);							// bounding box
	Line3D ln;												// Line
	Surface3D S = *this;

	// 1 Calculate bounding box for current surface
	S.createBoundingBox( mbox );

	// 2 Set line 
	ln.setLine( mbox[1], mbox[2]);
	return( ln.getLength() );
}

void Surface3D::putLowLeftFirst()					// Puts lower left vertex first in current surface vertex list
{
	vector<Vertex3D> mbox(4);							// bounding box
	double dist ;											// distance between vertex and LL corner of bbox
	double mindist;										// minimum distance between vertex and LL corner of bbox
	int posmin;												// original position in vVX of LL corner
	double dLr1;								// distance from lower right corner of bbox
	double dLr2;								// distance from lower right corner of bbox	
	vector<Vertex3D> vtmp(this->vVx.size());
	
	// 1 Calculate bounding box for current surface
	this->createBoundingBox(mbox);

	// 2 Perform permutation only if lower left corner is not lower left corner of bounding box
	if ( mbox[0] != this->vVx[0]) 
	{
		mindist = this->vVx[0].Calculate_distance( mbox [0] );
		posmin = 0;

		// 3 Figure out which vertex is closer to LL corner of bbox
		for ( unsigned int i = 1; i< this->vVx.size(); i++)
		{	
			dist = this->vVx[i].Calculate_distance( mbox [0] );
			if ( lessThan( dist , mindist ))  
			{
				mindist = dist;
				posmin = i;
			}// end if

			else
			{
				// if 2 point are at equal distance put the one nearest to the LowerRight corner first
				if ( equals (dist, mindist) )
				{
					dLr1 = this->vVx[i].Calculate_distance( mbox [1] );
					dLr2 = this->vVx[posmin].Calculate_distance( mbox [1] );
					
					if ( greaterThan ( dLr2, dLr1 ) )
					{
						mindist = dist;
						posmin = i;
					}
				}
			}
		}// end for

		// Copy vertex in vtmp in the new correct order if lower left corner is not already the first vertex	
		if ( posmin != 0) 
		{
			int fint = posmin ;

			for (unsigned int i =0; i <   this->vVx.size(); i++)
			{	
				vtmp[i] = this->vVx[fint];	
				fint = ( fint + 1) % this->vVx.size();
			}

			// transfer correct ordering to current surface
			this->vVx = vtmp ;

		} // end if
	}// end if 
}

void Surface3D::putClockwise(							// puts current surface vertices clockwise in V
	vector<Vertex3D> & V ) const
{	
	int ntl = this->vVx.size() - 1 ;

	// first vertex of V will be first vertex of current surface
	V.push_back ( this->vVx.front() );

	// insert all othe vertices starting by the last one

	for ( int i = ntl; i > 0; i--)
	{
		V.push_back ( this->vVx [i] );
	}
}	

void Surface3D::putClockwise() 						// puts current surface vertices clockwise in V

{	
	vector<Vertex3D> V;
	int ntl = this->vVx.size() - 1 ;

	// first vertex of V will be first vertex of current surface
	V.push_back ( this->vVx.front() );

	// insert all othe vertices starting by the last one

	for ( int i = ntl; i > 0; i--)
	{
		V.push_back ( this->vVx [i] );
	}

	this->vVx = V;
	this->SetSurfEquation();
}	

void Surface3D::punchApertures(						// Creates vertex list (Wall) for a surface including apertures Apert 
	vector<Surface3D> & Apert,
	vector<Vertex3D> & Wall )
{
	unsigned int j =0; // counter
	vector<int> overlap;	// index of overlapping surfaces
	vector<int> inside;		// index of contained surfaces
	vector<Surface3D> cut ;	// current resulting surface after boolean operation (stage 3)
	vector<Vertex3D> clkwise ;	 // vector clockwise summits for openings
	
	// 1	Check if there is overlapping in Apert vector. If so, stop here.
	if( Apert.size() > 1 )
	{	for ( unsigned int i = 0; i< (Apert.size() -1) ; i++ )
		{	
			for ( j = (i + 1) % Apert.size(); j < Apert.size(); j++ )
			{
				// Add try catch here instead of return ... |||||||||||||||||||
				if ( Apert[i].checkOverlap( Apert[j]) ) return;
			} // end for j

		} // end for i 
	}

	// 2	Create a list of overlapping Apertures & Create a list of contained Apertures	
	for( unsigned int i = 0; i < Apert.size(); i++ )
	{
		switch ( this->getSurfRelation( Apert[i] ) )
		{
			case espR::OVERLAPPING : overlap.push_back(i); break;
			case espR::INCLUDED : inside.push_back(i); break;
			break;
		} // end switch
	}// end for i

	// 3	if Overlapping list is not empty
	//		Cut overlapping surfaces from current surface
	if ( overlap.size() > 0)
	{		
		for( unsigned int i = 0; i < overlap.size() ; i++ )
		{
			this->getCurrentMinusOS( Apert [overlap[i]] , cut );
			this->vVx = cut[0].vVx ;
			cut.clear();
		}// end for i 
	}// end if overlap

	// 4	if inside list is not empty
	if( inside.size() > 0)
	{
		// 5	Put lower left corner first for every INCLUDED surface. 
		for ( unsigned int i = 0; i < inside.size() ; i++ )
		{
			Apert [inside[i]].putLowLeftFirst();
		}

		// 6	Create final vertex list 
		//		Append all vertices of current surface and append first vertex at the end
		for ( unsigned int i = 0; i < this->vVx.size() ; i++ )
		{
			Wall.push_back( this->vVx[i] );
		}
		
		Wall.push_back( this->vVx[0] );

		// 7	For every included surface generate a clockwise vertex list 
		//		Add every INCLUDED aperture clockwise and create leader line form LL corner of current
		//		surafce to LL corner of aperture
		for( unsigned int i = 0; i < inside.size() ; i++ )
		{
			Apert [inside[i]].putClockwise ( clkwise );

			for ( unsigned int j = 0; j < clkwise.size() ; j++ )
			{
				Wall.push_back( clkwise[j] );
			}// end for j

			Wall.push_back( clkwise[0] );
			Wall.push_back( this->vVx[0] );
			clkwise.clear();
		}// end for i
	}// end if
}

void Surface3D::resetX(									// resets Z-axis values
	double x )												// Z-axis value
{
	int i;

	for( i = 0; i < (int)vVx.size(); i++ )
	{
		vVx.at( i )[1] = x;
	}
}

void Surface3D::resetY(									// resets Z-axis values
	double y )												// Z-axis value
{
	int i;

	for( i = 0; i < (int)vVx.size(); i++ )
	{
		vVx.at( i )[2] = y;
	}
}

void Surface3D::resetZ(									// resets Z-axis values
	double z )												// Z-axis value
{
	int i;

	for( i = 0; i < (int)vVx.size(); i++ )
	{
		vVx.at( i )[3] = z;
	}
}

double Surface3D::calcX(								// Using known x and y values, calculate z value using current surface equation
	double fy,
	double fz ) const
{
	double fx;

	if ( equals ( this->a , float (0.0) )) return (0);
	else
	{
		// ax + by + cz = d
		// x = (d - b(y) - c(z)) / a

		fx = ((this->d) -  ((this->b) * fy) -  ((this->c) * fz)) / (this->a);
	}

	return (fx);
}

double Surface3D::calcY(								// Using known x and y values, calculate z value using current surface equation
	double fx,
	double fz ) const
{
	double fy;

	if ( equals ( this->b , float (0.0) )) return (0);
	else
	{
		// ax + by + cz = d
		// y = (d - a(x) - c(z)) / b

		fy = ((this->d) -  ((this->a) * fx) -  ((this->c) * fz)) / (this->b);
	}

	return (fy);
}

double Surface3D::calcZ(								// Using known x and y values, calculate z value using current surface equation
	double fx,
	double fy ) const
{
	double fz;

	if ( equals ( this->c , float (0.0) )) return (0);
	else
	{
		// ax + by + cz = d
		// z = (d - a(x) - b(y)) / c

		fz = ((this->d) -  ((this->a) * fx) -  ((this->b) * fy)) / (this->c);
	}

	return (fz);
}

bool Surface3D::bMirror(								// Returns true if S is exact mirror of current surface
	const Surface3D & S ) const						// (potential) mirrored surface
{
	Surface3D C, U;
	std::vector<Vertex3D> V;
	bool mirror = false;

	// C is the current surface with inverted vertices
	this->putClockwise( V );
	C.vVx = V;
	C.SetSurfEquation();
	C.putLowLeftFirst();
	
	U = S;
	U.SetSurfEquation();
	U.putLowLeftFirst();

	if( C == U ) mirror = true;

	return mirror;
}


void Surface3D::elimWrongVertices()
{
	int u;
	int v;
	int j;
	Vector3D v1;
	Vector3D v2;
	Vector3D vr;
	Vector3D vnul(0,0,0);								// null vector

	if ( this->isSurfaceValid() == true)
	{
		// 1. If we have the same vertex twice (consecutively) remove the second vertex
		for ( unsigned int i = 0; i < this->vVx.size(); i++ ) 
		{
			j = (i + 1) % this->vVx.size();	// next vertex
			// if next vertex == current vertex, eliminate current vertex
			if ( this->vVx[i] == this->vVx[j] )
			{
				this->vVx.erase( this->vVx.begin()+ i );
			}
		}

		// 2. Eliminate incorrect egdes (a-b) from surface

		//	b|
		//	 |
		//	a|_________
		//	 |         |
		//	 |         |
		//	 |_________|

		for ( unsigned int i = 0; i < this->vVx.size(); i++ ) 
		{
			u = (i + 1) % this->vVx.size();	// next vertex
			v = (i + 2) % this->vVx.size();	// next vertex
			
			v1 = this->vVx[u] - this->vVx [i];
			v1.Normalize();
			v2 = this->vVx[v] - this->vVx [u];
			v2.Normalize();
			vr = v2 + v1; 
			vr.Normalize();

			if ( vr == vnul)
			{
				// remove vertices forming second vector
				this->vVx.erase(this->vVx.begin() + u);
				this->vVx.erase(this->vVx.begin() + u);
			}
		}
	}
}

void Surface3D::elimColinearVertices()
{
	// Eliminate unnecessary vertex (b) from surface
	
	//	a _________
	//	 |         |
	//	b|         |
	//	 |         |
	//	c|_________|
	
	int u;
	int v;
	Vector3D v1;
	Vector3D v2;
	Vector3D vr;
	Vector3D vnul(0,0,0);								// null vector

	if (this->isSurfaceValid() == true)
	{
		for ( unsigned int i = 0; i < this->vVx.size(); i++ ) 
		{
			u = (i + 1) % this->vVx.size();	// next vertex
			v = (i + 2) % this->vVx.size();	// next vertex
			
			v1 = this->vVx[u] - this->vVx [i];
			v1.Normalize();
			v2 = this->vVx[v] - this->vVx [u];
			v2.Normalize();

			if ( v1 == v2)
			{
				// remove vertex 
				this->vVx.erase(this->vVx.begin() + u);
			}
		}
	}
}

bool Surface3D::isSurfaceValid()
{
	if( this->vVx.size() > 2) return (true);
	else return (false);

}

double Surface3D::putVertexinEquation(						// returns the result of ax+by+cz+d for V
		const Vertex3D & V )
{

	return ( (this->a * V[1]) + (this->b * V[2]) + (this->c * V[3]) - this->d  ); 
}

double Surface3D::GetHighestValue()
{
	double dTop = 0;
	
	for( unsigned int i =0; i < vVx.size(); i++ )
	{
		if( greaterThan (vVx[i][3], dTop )== true )
		{
			dTop = vVx[i][3];
		} // end if
	} // end for

	return (dTop);
}

double Surface3D::GetLowestValue()
{
	double dMin = vVx[0][3];
	
	for( unsigned int i = 1; i < vVx.size(); i++ )
	{
		if( lessThan (vVx[i][3], dMin  )== true )
		{
			dMin = vVx[i][3];
		} // end if
	} // end for

	return (dMin);
}

void Surface3D::clearValues()
{
	this->vVx.clear();
	this->a = 0 ;
	this->b = 0 ;
	this->c = 0 ;
	this->d = 0 ;
	this->Normal[1] = 0;
	this->Normal[2] = 0;
	this->Normal[3] = 0;
	this->Orient = 0;
}

void findSurfsWithUniqueVertices(
	vector<Surface3D> & vsS,
	vector<Surface3D> & vsOr,
	double dBvl)
{
	Vertex3D vTst;
	int iC;
	int iS;
	vector<int> viL;

	
	// We have to share vertices first
	for ( unsigned int a = 0 ; a < vsS.size(); a++ )
	{
		for ( unsigned int b = a+1 ; b < vsS.size(); b++ )
		{			
			vsS[a].calcComSummits( vsS[b] );
		}
	}
	
		
	// go through all surfaces et éliminer celles qui ont un sommet orphelin
	// for every roof surface
	for ( unsigned int a = 0 ; a < vsS.size(); a++ )
	{
		iS = 0;
		// for every summit of that surface
		for ( unsigned int b = 0; b < vsS[a].vVx.size(); b++ )
		{
			iC = 0 ;
			if ( equals ( vsS[a].vVx[b][3] , dBvl ) == false )
			{
				vTst = vsS[a].vVx[b];
				for ( unsigned int c = 0 ; c < vsS.size(); c++ )
				{
						if ( c != a)
						{
							for ( unsigned int d = 0; d < vsS[c].vVx.size(); d++ )
							{
								if ( vsS[c].vVx[d] == vTst ) 
									{
										iC ++;
									}
							}// end for d
						}

				}// end for c
				if ( iC < 2 ) 
				{
					iS ++;
				}
			}
		}// end for b
		if ( iS > 0) 
			{
				vsOr.push_back( vsS[a] ) ;
			}
					
	}// end for a
	
}

void deleteSurfaces(
	vector<Surface3D> & vsS,
	vector<Surface3D> & vsOs)
{
	for ( unsigned int i = 0; i < vsOs.size(); i++ )
	{
		for ( unsigned int j = 0; j < vsS.size(); j++ )
		{
			if ( vsOs[i] == vsS[j] ) 
			{
				vsS.erase( vsS.begin() + j );
				j--;
			}

		}// end for j
	}// end for i
}

bool IsSurfInList(
	const vector<Surface3D> & vsS, 
	const Surface3D & sS )
{
	unsigned int i;
	bool match = false;

	for (i=0; i < vsS.size(); i++)
	{
		if(	vsS[i] == sS )
		{
			match = true;
			break;
		} // end if
	} // end for

	return (match);
}

bool IsVertexInList(
	const vector<Vertex3D> & V,
	const Vertex3D & P )
{
	unsigned int i;
	bool match = false;

	for (i=0; i < V.size(); i++)
	{
		if(	fabs(P[1] - V[i][1]) < double (0.001) && 
			fabs(P[2] - V[i][2]) < double (0.001) && 
			fabs(P[3] - V[i][3]) < double (0.001) )
		{
			match = true;
			break;
		} // end if
	} // end for

	return (match);
}

int findVertexInList(
	const vector<Vertex3D> & V,
	const Vertex3D & P )
{
	unsigned int i;
	int match = -1;

	for (i=0; i < V.size(); i++)
	{
		if (fabs(P[1] - V[i][1]) < double (0.001) && 
			fabs(P[2] - V[i][2]) < double (0.001) && 
			fabs(P[3] - V[i][3]) < double (0.001) )
		{
			match = i;
		}// end if

	}// end for

	return (match);
}

bool isEdgeInSurface(
	const vector<Vertex3D> &V,
	const Vertex3D &P,
	const Vertex3D &Q)
{
	int u = findVertexInList ( V, P );
	int v = findVertexInList ( V, Q );

	if ( u == (V.size() -1 ) )
	{
		if ( v == 0 ) return true;
		else return (false);
	}

	else
	{
	
		if ( (v - u) != 1 ) return ( false );
		else  return ( true );

	}	
}

void mergeSurfList(
	vector<Surface3D> & vsS)
{
	
	Surface3D sTmp;

	// go through all roof surfaces and merge adjacent or overlapping surfaces
	// for every extension surface
	for ( unsigned int a = 0 ; a < vsS.size() ; a++ )
		{
		 vsS[a].elimColinearVertices();
		 for ( unsigned int b = a+1 ; b < vsS.size() ; b++ )
			{

			 if ( vsS[a].getSurfRelation( vsS[b] ) == espR::ADJACENT || vsS[a].getSurfRelation( vsS[b] ) == espR::OVERLAPPING  )
				{
					// merge
					vsS[a].mergeSurf (vsS[b], sTmp );
					vsS[a].vVx = sTmp.vVx;
					sTmp.vVx.clear();
					vsS[a].elimColinearVertices();
					// delete second surface from original vector
					vsS.erase (vsS.begin() + b); 
					b = a;

				}

			else 
				{
					if ( vsS[a].getSurfRelation( vsS[b] ) == espR::INCLUDED || vsS[a].getSurfRelation( vsS[b] ) == espR::INCLUDEDTOUCH  )
					{
						// delete second surface from original vector
						vsS.erase (vsS.begin() + b); 
						b = a;
					}

				}
			}
		}
}

void Surface3D::Print_surface_vertex()				// prints all the vertex forming the current surface
{	
	unsigned int i;

	if( vVx.size()>1 )
	{
		for( i=0; i < vVx.size(); i++ )
		{
			// print every vertex of the current roof surface
			cout << "point " << i+1 << "  =  (" << vVx[i][1] << ", " << vVx[i][2] << ", " << vVx[i][3] << ")" << endl ;
		}
		cout << endl << endl;
	}

	else 
	{
		cout << "Empty surface" << endl << endl;
	}
}

Surface3D::~Surface3D()
{
}

// -------------------------------------------- // POLYHEDRON3D class

Polyhedron3D::Polyhedron3D()									// constructor
{
}

Polyhedron3D::Polyhedron3D(
	const vector<Surface3D> & vSurfs )		// constructor with arguments

{
	vSx = vSurfs;
}

bool Polyhedron3D::CheckValidity()		// checks polyhedron validity

{
	int c; // counter
	Vertex3D vC;
	
	// 1- the must be more than 2 surfaces
	if ( this->vSx.size() < 3 ) return false;
	else 
	{

		// 2 faces cannot overlap
		for ( unsigned int a = 0; a < ( this->vSx.size() -1 )  ; a++) // for every surface
		{
			for ( unsigned int b = a + 1 ; b < this->vSx.size() ; b++) // for every surface
			{
				if ( this->vSx[a].getSurfRelation ( this->vSx[b] ) == espR::OVERLAPPING ) return false;
			} // end for b

		} // end for a
		
		// each vertex has to be on at least 3 faces
		for ( unsigned int i = 0; i < ( this->vSx.size() -1 )  ; i++) // for every surface
		{
			
			for ( unsigned int j = 0 ; j < this->vSx[i].vVx.size() ; j++ ) // for every vertex
			{
				c = 1;
				vC = this->vSx[i].vVx[j];
			
				for ( unsigned int n = 0 ; n < this->vSx.size() ; n++ ) // for every surface
				{
					if ( IsVertexInList( this->vSx[n].vVx, vC ) == true && n!= i) c++;
				} // end for n

				if ( c < 3 ) 
					return false;
			
			} // end for i
			
		} // end for j
	}// end else
	return true;
}

double Polyhedron3D::CalcVol()							// Calculates volume of current polyhedron
{
	double dV = 0;
	double dVt = 0;
	unsigned int c = 0;

	Vector3D vT;		// Unit tangent vector from the vertex along the edge towards the other end.
	Vector3D vN;		// Unit vector normal to the edge in the plane of the face, and pointing from the edge into the face.
	Vector3D vB;		// Unit vector normal to the plane of the face, and pointing into the polyhedron.
	Vector3D vV;

	// for every summit of every surface of current polyhedron

	// 1 polygon must be valid

	if ( this->CheckValidity() == false ) 
		return 0;

	else
	{

		for ( unsigned int a = 0; a < this->vSx.size(); a++) // for every surface
		{
			// Calculate vB which is constant for each surface
			vB = this->vSx[a].GetSurfNormal();
			vB.Invert();
			vB.Normalize();
		
			for ( unsigned int b = 0; b < this->vSx[a].vVx.size(); b++) // for every summit
			{
				vV[1] = this->vSx[a].vVx[b][1];
				vV[2] = this->vSx[a].vVx[b][2];
				vV[3] = this->vSx[a].vVx[b][3];

				c = (b + 1) % this->vSx[a].vVx.size();	// next vertex
				vT = this->vSx[a].vVx[c] - this->vSx[a].vVx[b];
				vT.Normalize();
				vN = Cross_product( vT, vB );

				dVt = -0.166667 * (( vV * vT ) * ( vV * vN ) * ( vV * vB ) ) ;
				dV = dV+ dVt;

				// DO 10 I=1,NSUR
				// J=JVN(I,1)
				// PV=.16667*(X(J)*XSUM(I)+Y(J)*YSUM(I)+Z(J)*ZSUM(I))
				// V=V+PV
				// 10 CONTINUE
				// VOL(ICOMP)=ABS(V)

				// x(J) est la coordonne x du vertex actuel

				c = b - 1 ; // previous surface index
				if ( b == 0 ) c = this->vSx[a].vVx.size() - 1;

				vT = this->vSx[a].vVx[c] - this->vSx[a].vVx[b];
				vT.Normalize();
				vN = Cross_product( vT, vB );
			
				dVt = 0.166667 * (( vV * vT ) * ( vV * vN ) * ( vV * vB ) ) ;
				dV = dV+ dVt;


			} // end for b

		}// end for a

		
	}

	if ( lessThan (dV, 0)) return 0;
	else return( dV );
}

Polyhedron3D::~Polyhedron3D()
{
}
