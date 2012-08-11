// ---------------------------------------------	// Header file for H3K/ESP-r 3D library

#ifndef _ESPR3D_H
#define _ESPR3D_H

#include "tnt.h"
#include "jama_lu.h"

#include "EsprDef.h"

using namespace TNT;
using namespace JAMA;

#define INSIDE		1
#define OUTSIDE		0
#define ONEDGE		2


// -------------------------------------------- // general math fucntions

void solvePolynomial(									// Solve polynomial ax2 + bx + c == 0
	const double & va, 
	const double & vb, 
	const double & vc,
	vector<double> & res );

int timesNHigh(											// Counts how many components of V have higher int value then n
	int n,
	vector<int> &V );


// -------------------------------------------- // VECTOR3D class

class Vector3D
{
	protected :
		double vx;											// X-axis coordinate
		double vy;											// Y-axis coordinate
		double vz;											// Z-axis coordinate

	public :
		Vector3D();											// constructor
		Vector3D(											// copy constructor
			const Vector3D & V );						// vector V
		Vector3D & operator = (							// assignment operator
			const Vector3D & Q );						// vector Q
		Vector3D(											// constructor with arguments
			const double & x,								// X-axis coordinate 
			const double & y, 							// Y-axis coordinate
			const double & z );							// Z-axis coordinate
		double & operator [] (							// acces/modify components 1(x), 2(y) or 3(z) of 3D vector
			const int & i );								// iterator
		const double & operator [] (					// acces - without modification - components 1(x), 2(y) or 3(z) of 3D vector
			const int & i ) const;						// iterator
		bool operator == (								// compare V to current vector; returns true if same vector		
			const Vector3D & V ) const;				// vector V
		bool operator != (								// compare V to current vector;returns true if different vector
			const Vector3D & V ) const;				// vector V
		double operator * (								// calculates dot product of 3D vector V and current 3D vector
			const Vector3D & V ) const;				// vector V
		Vector3D operator * (							// calculates scalar product between current 3D vector V ans Scalar S
			double S) const;				// vector V
		const Vector3D operator + (					// calculates sum of current 3D vector + 3D vector V
			const Vector3D & V ) const;				// vector V
		const Vector3D operator - (					// calculates difference between current 3D vector & 3D vector V
			const Vector3D & V ) const;				// vector V
		void Normalize ();								// Normalize current vector
		void Invert ();								// Invert current vector [1] = -[1]...
		double CalcAngle(						// Calculates angle between current vector and vector V
			const Vector3D & V );				// vector V
		friend Vector3D Cross_product(				// calculates cross product between 3D vectors P and Q
			Vector3D P,										// vector P
			Vector3D Q ); 									// vector Q
		/*friend Vector3D Scalar_product(				// calculates scalar product between 3D vector V ans Scalar S
			double S,								// scalar S
			Vector3D V ); 									// vector V
			*/
		friend double Norm(								// calculates norm of 3D vector P
			Vector3D P );									// vector P
		~Vector3D();										// destructor
};


// -------------------------------------------- // VERTEX3D class

class Vertex3D //: public CObject, public XMLElement
{
	public :
		double vx;											// X coordinate (meters)
		double vy;											// Y coordinate (meters)
		double vz;											// Z coordinate (meters)


		Vertex3D();											// constructor; creates a vertex at the origin
		Vertex3D(											// copy constructor
			const Vertex3D & V );						// vertex V
		Vertex3D(											// constructor; creates a vertex at x,y,z
			const double & x,								// X-axis coordinate 
			const double & y,								// Y-axis coordinate 
			const double & z );							// Z-axis coordinate
		double & operator [] (							// acces/modify components 1(x), 2(y) or 3(z) of current 3D vertex
			const int & i );								// iterator
		const double & operator [] (					// acces - without modification - components 1(x), 2(y) or 3(z) of current 3D vertex
			const int & i ) const;						// iterator
		Vertex3D & operator = (							// assignment operator
			const Vertex3D & P );						// vertex P
		bool operator == (								// compare P to current vertex; returns true if same vertex		
			const Vertex3D & P ) const;				// vertex P
		bool operator != (								// compare P to current vertex; returns true if different vertex
			const Vertex3D & P ) const;				// vertex P
		const Vector3D operator - (					// calculates the difference between current vertex and vertex P
			const Vertex3D & P ) const;				// vertex P 
		const Vertex3D operator + (					// calculates the sum of current vertex and 3d vector V
			Vector3D V ) const;							// vector V  
		void translation(									// Apply translation to current vertex
			const double & tX,							// x distance
			const double & tY,							// y distance
			const double & tZ);							// z distance
		void rotateX(										// rotate vertex around X axis 
			const double & angle);						//  degrees
		void rotateY(										// rotate vertex around Y axis
			const double & angle);						//  degrees
		void rotateZ(										// rotate vertex around Z axis
			const double & angle);						//  degrees
		static bool Compare_vertex3D_xplus(			// compares 2 vertex according to their x value (returns true if P1x > P2x) 
			const Vertex3D & P1,							// vertex P1
			const Vertex3D & P2 );						// vertex P2
		static bool Compare_vertex3D_xminus(		// compares 2 vertex according to their x value (returns true if P1x < P2x)
			const Vertex3D & P1, 						// vertex P1
			const Vertex3D & P2 );						// vertex P2
		static bool Compare_vertex3D_yplus(			// compares 2 vertex according to their y value (returns true if P1y > P2y)
			const Vertex3D & P1, 						// vertex P1
			const Vertex3D & P2 );						// vertex P2
		static bool Compare_vertex3D_yminus(		// compares 2 vertex according to their y value (returns true if P1y < P2y)
			const Vertex3D & P1,							// vertex P1
			const Vertex3D & P2 );						// vertex P2
		static bool Compare_vertex3D_zplus(			// compares 2 vertex according to their y value (returns true if P1y > P2y)
			const Vertex3D & P1,							// vertex P1 
			const Vertex3D & P2 );						// vertex P2 
		static bool Compare_vertex3D_zminus(		// compares 2 vertex according to their y value (returns true if P1y < P2y)
			const Vertex3D & P1, 						// vertex P1
			const Vertex3D & P2 );						// vertex P2
		double Calculate_distance(						// Calculates the distance between current vertex and vertex P1
			const Vertex3D & P1) const;

/*		DECLARE_SERIAL(Vertex3D)
		void Serialize(CArchive& ar);
        virtual TiXmlElement* GetXML();
        virtual void FromXML(TiXmlElement* element);
        virtual CString GetTagName() { return "vertex3d"; };
*/
};

// -------------------------------------------- // Line3D class

class Line3D : public Vertex3D
{
	protected:
		Vertex3D Start;
		Vertex3D End;

	public:
		Line3D();
		Line3D(												// Creates a 3D line starting at Vertex3D P and ending at Vertex3D Q
			const Vertex3D & P, 
			const Vertex3D & Q );	
		void setLine(										// Sets current Line
			const Vertex3D & S,
			const Vertex3D & E);
		void setStart(										// Sets starting vertex at S
			const Vertex3D & S );
		void setStart(										// Sets starting vertex at Sx,Sy,Sz
			const double & Sx,
			const double & Sy,
			const double & Sz );
		void setEnd(										// Sets end vertex at E
			const Vertex3D & E );
		void setEnd(										// Sets end vertex at Ex,Ey,Ez
			const double & Ex,
			const double & Ey,
			const double & Ez );		
		Vertex3D getStart() const;						// Returns Starting Vertex3D
		Vertex3D getEnd() const;						// Returns Ending Vertex3D
		Vertex3D getMidPoint() const;					// Calculates & returns mid point
		double getLength() const;						// Calculates & returns lenght of the current line
		bool isLnParral(									// Returns true if L is || to current Line
			Line3D L ) const;
		bool doLineCross(									// Returns true if L crosses current Line
			const Line3D & L ) const;
		void getIntersection(								// Calculates & returns intersection between current line & line L  
			Line3D & L,
			Vertex3D & Int );
		static bool Compare_Length(					// compares lenght for 2 lines returns true if L1 < L2
			const Line3D & L1, 
			const Line3D & L2 );
		bool isVertexOnLine(								// calculates if vertex P is on current line (within limits)
			const Vertex3D & P,
			const double & ang1,							// rotation angles needed to bring line and vertex on a plane defined by X & Y
			const double & ang2 ) const;
		~Line3D();					
};

// -------------------------------------------- // SURFACE3D class

class Surface3D : public Vertex3D
{
	protected:
																// coefficients of the equation of a plane in the form Ax + By + Cz = D 
		double a;											// x coefficient in the equation of the plane
		double b;											// y coefficient in the equation of the plane
		double c;											// z coefficient in the equation of the plane
		double d;
		Vector3D Normal;									// surface Normal
		int Orient;											// surface orientation
	
	public:
		std::vector<Vertex3D> vVx;						// vector of vertices forming the surface
		Surface3D();										// constructor
		Surface3D(
			const vector<Vertex3D> & vSummits );	// constructor with arguments
																// advantage sets surface equations and normal
		Surface3D(											// copy constructor
			const Surface3D & S );						// surface S
		double GetA();									// Access function returns current surface equation coeff. a
		double GetB();									// Access function returns current surface equation coeff. b
		double GetC();									// Access function returns current surface equation coeff. c
		double GetD();									// Access function returns current surface equation coeff. d
		int GetOrient();								// Access function returns current surface orientation
		Vector3D GetSurfNormal() const;					// Access function returns current normal
		Surface3D & operator = (						// assignment operator
			const Surface3D & S );						// surface S
		bool operator == (								// compare S to current surface; returns true if same
			const Surface3D & S ) const;				// surface S
		bool operator != (								// compare S to current surface; returns true if different
			const Surface3D & S ) const;				// surface S
		void Calculate_eq_coeff(						// calculates coefficients a,b,c,d of the equation of a plane
			const Vector3D & V,							// vector V 
			const Vertex3D & T );						// vertex T
		void SetSurfEquation();							// calculates coefficients a,b,c,d of the equation of a plane
		void SetSurfEquation(							// calculates coefficients a,b,c,d of the equation of a plane when 2 points fo the surface and the surface slope are known
			vector<Vertex3D> &V,						// V is a list of base points
			int i,										// i is the point of origin
			double ag );								// ag is the surface slope		
		void copySurfEquation(							// copies coefficients a,b,c,d of the equation of a plane
			const double & eqa,
			const double & eqb,
			const double & eqc,
			const double & eqd,
			const Vector3D & No,
			const int & or );
		void CalcSurfNormal();							// calculates and returns surface normal
		Vertex3D Calculate_intersection(				// calculates and returns the intersection (Vertex3D) between 3 planes 
			const Surface3D & S2,							// surface S2
			const Surface3D & S3 );							// surface S3
		bool canSurfaceBeCut(							// Verifies if current Surface intersects with cutting plane oS 
			const Surface3D & oS);							// Limit surface
		bool doSurfacesIntersect(						// verifies if 2 surfaces have a valid intersection
			const Surface3D & oS);							// Limit surface	
		bool findValidIntersection(
			const Surface3D & sEdg1,
			const Surface3D & sEdg2,
			const Surface3D & oS);		
		bool doSurfacesIntersect(						// verifies if 2 surfaces have a valid intersection
			int iEdc1,
			int iEdc2,
			int iD,
			vector<Surface3D> & vsOs);							// Limit surface
		void cutSurface(								// divides current Surface according to intersection with non parrallel oS surface 
			const Surface3D & oS,							// Limit surface
			vector<Surface3D> & vSurfF );					// Resulting vector of Surface3D
		void multiCutSurface(
			vector<Surface3D> & vsEdges,
			vector<Surface3D> & vsRes);
		void divideSurfaceHoriz(						// divides a Surface horizontally
			double distFloor,								// distance from floor (m)
			vector<Surface3D> & vSurfF );				// surface(s) obtained by current subdivision
		void divideSurfaceVert(							// divides a Surface vertically
			double distLeft,								// distance from left surface edge (m)
			vector<Surface3D> & vSurfF );					// surface(s) obtained by current subdivision
		Vertex3D getEdgeIntersection(					// gets surface edge intersection with a surface
			int iA,											// index of edge 1
			int iB,											// index of edge 2
			const Surface3D & oS )	;
		Vertex3D getEdgeIntersection(					// gets surface edge intersection with a horizontal or vertical ray
			char ornt,										// orientation of ray "h" (horiz.) or "v" (vertical)
			int iA,											//
			int iB,											//
			double cutVal );								// distance from floor or from left corner
		void offsetVertex(								// calculate offset (horiz or vert) to move surface inside boundary
			char ornt,										// orientation of offset "h" (horiz.) or "v" (vertical)
			float dist,										// distance to offset											
			vector<Vertex3D> & vbox,					// 4 corners of original boundary 
			Vertex3D &PTest );							// resulting Vertex 		
		void offsetEdge(									// calculate offset (horiz or vert) to move surface inside boundary
			char ornt,										// orientation of offset "h" (horiz.) or "v" (vertical)
			float dist,										// distance to offset											
			vector<Vertex3D> &vbox,						// 4 corners of original boundary 
			Line3D &Loff );
		void moveSurface(									// move surface	
			double hr,										// horizontal distance 
			double vr);										// vertical distance
		void resizeSurface(								// resize surface	
			double NWidth,									// new surface widht (m)
			double NHeight );								// new surface height (m)
		void rotateX(										// rotate surface around X axis 
			double angle );								//  degrees
		void rotateY(										// rotate surface around Y axis
			double angle );								//  degrees
		void rotateZ(										// rotate surface around Z axis
			double angle );								//  degrees
		void scaleOr(										// Scale current surface (origin of scale = 0,0,0)
			double sX,										// x scale factor
			double sY,										// y scale factor
			double sZ );									// z scale factor
		void scaleUnifOr(									// Scale current surface (base of scale = 0,0,0)
			double sU );									// uniform scale factor
		void scale(											// Scale current surface (origin of scale = lower left corner of bounding box)
			double scX,										// x scale factor
			double scY,										// y scale factor
			double scZ );									// z scale factor
		void scaleUnif(									// Scale current surface (origin of scale = lower left corner of bounding box)
			double scU );									// uniform scale factor
		void translation(									// Apply translation to current surface
			double tX,										// x distance
			double tY,										// y distance
			double tZ );									// z distance
		int IsVertexInside(								// calculates if Vertex V is inside current surface Return 1 if inside, 0 if outside & 2 if on edge
			const Vertex3D & V ) const;						// vertex V
		int IsVertexInside(								// calculates if Vertex V is inside Polygon Poly Return 1 if inside, 0 if outside & 2 if on edge
			const vector<Vertex3D> & Poly,					// polygon
			const Vertex3D & V );						// vertex V
		bool isVertexInPlane(							// Verifies if V is in plane defined by current surface
			const Vertex3D & V );
		bool IsSurfaceInside(							// calculates if current surface contains surface oS
			const Surface3D & oS ) const;					// surface oS
		bool IsOneVertexInside(							// returns true if a vertex of Vl is inside current surface
			const vector<Vertex3D> & Vl);
		bool IsOneVertexOutside(							// returns true if a vertex of Vl is outside current surface
			const vector<Vertex3D> & Vl);
		float getAzimut() const;						// Calculates surface azimut
		float alignX() const;							// calculates angle needed to align surface baseline with x axis (i.e Normal with -Y)
		float getAltitude() const;						// Calculates surface altitude
		float alignZ() const;							// Returns angle needed to align surface Normal to Z
		float getRoll() const;							// Calculates surface roll
		int calcOrientation(								// Calculates surface orientation (Front, Back...)
			float azimut ) const;						// surface azimut
		int getOrientation() const;					// Returns surface orientation (Front, Back...)
		void setOrientation(							// Sets current orientation to Or value
			int Or);
		void createBoundingBox(							// creates bounding box around surface3D Bbox
			vector<Vertex3D> & Bbox );						
		void calculateBoxCorner(						// Calculate a given corner for current surface bounding box
			const Vertex3D & H,
			const Vertex3D & V,
			Vertex3D & Corner ) const;
		bool areSurfCoplanar(							// Verifies if surface oS and current Surface are coplanar
			const Surface3D & oS ) const;	
		bool areSurfParallel(							// Verifies if surface oS is parrallel to current Surface
			const Surface3D & oS ) const;
		void getIntSummits(								// Look through current surface summits and surface oS summits to find similar points
			const Surface3D & oS,
			vector<Vertex3D> & Int ) const;
		bool checkOverlap(								// Checks if there is an overlap between current surface and oS
			const Surface3D & oS ) const;
		bool checkTouchOne(								// Checks if current surface and oS share only one summit
			const Surface3D & oS ) const;
		bool checkTouching(								// Checks if current surface and oS edges are touching (at least 2 consecutive edges)
			const Surface3D & oS ) const;
		bool checkIncluded(								// Checks if oS is inside current without touching edges
			const Surface3D & oS ) const;
		bool checkIncludedTouch(						// Checks if oS is inside current and touching edges
			const Surface3D & oS ) const;
		int getSurfRelation(							// Returns 8 possible surface relation  
			const Surface3D & oS ) const;					// espR::NO_RELATION (501) -> non coplanar or parallel surfaces 
															// espR::PARALLEL (502) ->	parallel surfaces 
															// espR::COPLANAR (503) -> coplanar surfaces
															// espR::COPLSHAREONE (504) -> share one summit
															// espR::ADJACENT (505) -> coplanar & adjacent surfaces (share 2 or more consecutive summits)
															// espR::OVERLAPPING (506) -> coplanar & overlapping surfaces
															// espR::INCLUDED (507)-> Os is inside current surface without touching edges
															// espR::INCLUDEDTOUCH (508)-> Os is inside current surface and touching edges
		void calcComEdge(								// Calculates common egde for adjacent surfaces (Current surface & oS)
			Surface3D & sO,
			vector<Vertex3D> & vEdge);								
		void calcComSummits(							// Calculates common summits for 2 adjacent coplanar surfaces (Current surface & oS)
			Surface3D & oS );								// and adds them to both surfaces										
		void calcSurfInt(								// Detects intersection between current surface and surface oS (both surfaces must be coplanar)				
			Surface3D & oS,
			Surface3D & Int,								// intersection
			vector<Surface3D> & Res1,					// Resulting surfaces for current surface
			vector<Surface3D> & Res2 );				// Resulting surfaces for oS surface
		void getIntersection(							// Calculates intersection between current surface and surface oS 
			Surface3D & oS,
			Surface3D & Inter );
		void getCurrentMinusOS(							// Calculates resulting surfaces when we substract oS to current
			Surface3D & oS,
			vector<Surface3D> & ResCur );
		void getOSMinusCurrent(							// Calculates resulting surfaces when we substract current to oS 
			Surface3D & oS,
			vector<Surface3D> & ResOS );
		void mergeSurf(
			Surface3D & oS,
			Surface3D & SMerged );
		bool doSurfsFormValley(
			Surface3D & sO);
		double calcPerim() const;						// Calculates current surface perimeter
		double calcArea() const;						// Calculates current surface area
		double getWidth() const;						// Calculates current surface width (of bounding box)
		double getHeight() const;						// Calculates current surface height (of bounding box)
		void putLowLeftFirst();							// Puts lower left vertx first in current surface vertex list
		void putClockwise(								// puts current surface vertices clockwise in V
			vector<Vertex3D> & V ) const;
		void putClockwise();							// puts current surface vertices clockwise
		void punchApertures(								// Creates vertex list (Wall) for a surface including apertures Apert 
			vector<Surface3D> & Apert,
			vector<Vertex3D> & Wall );
		void resetX(										// resets Z-axis values
			double x );										// Z-axis value
		void resetY(										// resets Z-axis values
			double y );										// Z-axis value
		void resetZ(										// resets Z-axis values
			double z );										// Z-axis value
		double calcX(										// Using known x and y values, calculate z value using current surface equation
			double fy,
			double fz ) const;
		double calcY(										// Using known x and y values, calculate z value using current surface equation
			double fx,
			double fz ) const;
		double calcZ(										// Using known x and y values, calculate z value using current surface equation
			double fx,
			double fy ) const;
		bool bMirror(										// Returns true if S is exact mirror of current surface
			const Surface3D & S ) const;						// (potential) mirrored surface
		void elimWrongVertices();
		void elimColinearVertices();
		bool isSurfaceValid();								// returns true if surface has more than 3 points
		double putVertexinEquation(							// returns the result of ax+by+cz+d for V
			const Vertex3D & V );
		double GetHighestValue();							// calculates and returns the highest z coordinate in the list of vertext forming the current surface
		double GetLowestValue();							// calculates and returns the lowest z coordinate in the list of vertext forming the current surface
		void clearValues();
		
		friend void findSurfsWithUniqueVertices(
			vector<Surface3D> & vsS,
			vector<Surface3D> & vsOr,
			double dBvl); 
		friend void deleteSurfaces(
			vector<Surface3D> & vsS,
			vector<Surface3D> & vsOs);
		friend bool IsSurfInList(
			const vector<Surface3D> & vS, 
			const Surface3D & sS );
		friend bool IsVertexInList(					// checks if vertex P is already in the list V of vertex forming the current surface
			const vector<Vertex3D> & V, 
			const Vertex3D & P );
		friend int findVertexInList(					// checks if vertex P is already in the list V of vertex forming the current surface
			const vector<Vertex3D> & V, 
			const Vertex3D & P );
		friend bool isEdgeInSurface(
			const vector<Vertex3D> &V,
			const Vertex3D &P,
			const Vertex3D &Q);
		friend void mergeSurfList(
			vector<Surface3D> & vsS);

		void Print_surface_vertex();					// prints all the vertex forming the current surface
		~Surface3D();							// destructor
};

class Polyhedron3D : public Surface3D
{
	public:
		std::vector<Surface3D> vSx;						// vector of surfaces forming current polyhedron
														// IMPORTANT :	regular surfaces forming the polyhedron boundaries must be defined counter clockwise
														//				while surface that form a hole in the polyhedra must be defined clockqise 
		
		Polyhedron3D();									// constructor
		Polyhedron3D(
			const vector<Surface3D> & vSurfs );			// constructor with arguments
																
		Polyhedron3D(									// copy constructor
			const Polyhedron3D & P );					// Polyhedron P

		bool CheckValidity();							// checks polyhedron validity
		double CalcVol();								// Calculates volume of current polyhedron
		~Polyhedron3D();								// destructor
};

#endif // _ESPR3D_H