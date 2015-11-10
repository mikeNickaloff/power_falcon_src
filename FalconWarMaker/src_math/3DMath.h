#ifndef _3DMATH_H
#define _3DMATH_H

#define PI 3.1415926535897932					// This is our famous PI

#define BEHIND		0
#define INTERSECTS	1
#define FRONT		2

#include <QVector3D>
// This is our basic 3D point/vector class
struct CVector3
{
public:
	
	// A default constructor
	CVector3() {}

	// This is our constructor that allows us to initialize our data upon creating an instance
	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 vVector)
	{
		// Return the added vectors result.
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 vVector)
	{
		// Return the subtracted vectors result
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	CVector3 operator*(float num)
	{
		// Return the scaled vector
		return CVector3(x * num, y * num, z * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	CVector3 operator/(float num)
	{
		// Return the scale vector
		return CVector3(x / num, y / num, z / num);
	}

	float x, y, z;						
};


// This returns the absolute value of "num"
float Absolute(float num);

//	This returns a perpendicular vector from 2 given vectors by taking the cross product.
QVector3D Cross(QVector3D vVector1, QVector3D vVector2);

//	This returns the magnitude of a normal (or any other vector)
float Magnitude(QVector3D vNormal);

//	This returns a normalize vector (A vector exactly of length 1)
QVector3D Normalize(QVector3D vNormal);

//	This returns the normal of a polygon (The direction the polygon is facing)
QVector3D Normal(QVector3D vPolygon[]);

// This returns the distance between 2 3D points
float Distance(QVector3D vPoint1, QVector3D vPoint2);

// This returns the point on the line segment vA_vB that is closest to point vPoint
QVector3D ClosestPointOnLine(QVector3D vA, QVector3D vB, QVector3D vPoint);

// This returns the distance the plane is from the origin (0, 0, 0)
// It takes the normal to the plane, along with ANY point that lies on the plane (any corner)
float PlaneDistance(QVector3D Normal, QVector3D Point);

// This takes a triangle (plane) and line and returns true if they intersected
bool IntersectedPlane(QVector3D vPoly[], QVector3D vLine[], QVector3D &vNormal, float &originDistance);

// This returns the dot product between 2 vectors
float Dot(QVector3D vVector1, QVector3D vVector2);

// This returns the angle between 2 vectors
double AngleBetweenVectors(QVector3D Vector1, QVector3D Vector2);

// This returns an intersection point of a polygon and a line (assuming intersects the plane)
QVector3D IntersectionPoint(QVector3D vNormal, QVector3D vLine[], double distance);

#endif
