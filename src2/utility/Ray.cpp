/* Ray.cpp */

#include "Ray.h"
using namespace std;

Ray::Ray(VecPoint a, VecPoint b)
{
    this->origin = a;
    this->vector = b;
}

VecPoint Ray::intersectTriangle(Triangle triangle)
{
    VecPoint vertex1 = triangle.getV1();
    VecPoint vertex2 = triangle.getV2();
    VecPoint vertex3 = triangle.getV3();
    VecPoint rayOrigin = this->getOrigin();
    VecPoint rayDirection = this->getVector();
    VecPoint P;

    // Compute the normal
    VecPoint a, b;
    a = vertex2.subtract(vertex1);
    b = vertex3.subtract(vertex1);
    VecPoint normal = a.crossProduct(b);

    // Find P
    double nDotRay = normal.dotProduct(rayDirection);
    if (nDotRay == 0) {
        return VecPoint(0,0,0,0); // Parallel: no intersection
    }
    double d = normal.dotProduct(vertex1); // Ax + By + Cz + D = 0
    double t = -(normal.dotProduct(rayOrigin) + d) / nDotRay;

    // Check if triangle behind ray
    if (t < 0) {
        return VecPoint(0,0,0,0);
    }
    P = rayOrigin.add(rayDirection.scale(t));

    // Inside Outside Test
    VecPoint C; // Vector perpendicular to plane of triangle

    // Edge 1
    VecPoint edge1 = vertex2.subtract(vertex1);
    VecPoint pv1 = P.subtract(vertex1);
    C = edge1.crossProduct(pv1);
    if (normal.dotProduct(C) < 0) {
        return VecPoint(0,0,0,0); // P is on the right side
    }

    // Edge 2
    VecPoint edge2 = vertex3.subtract(vertex2);
    VecPoint pv2 = P.subtract(vertex2);
    C = edge2.crossProduct(pv2);
    if (normal.dotProduct(C) < 0) {
        return VecPoint(0,0,0,0);
    }

    // Edge 3
    VecPoint edge3 = vertex1.subtract(vertex3);
    VecPoint pv3 = P.subtract(vertex3);
    C = edge3.crossProduct(pv3);
    if (normal.dotProduct(C) < 0) {
        return VecPoint(0,0,0,0);
    }

    return P; // P is in the triangle
}

VecPoint Ray::intersectSphere(Sphere s)
{
    double A, B, C, t0, t1;
    double discriminant;
    VecPoint intersection;

    double sphereX = s.getX();
    double sphereY = s.getY();
    double sphereZ = s.getZ();
    double radius = s.getRadius();

    VecPoint vector = this->getVector();
    double vectorX = vector.getX();
    double vectorY = vector.getY();
    double vectorZ = vector.getZ();

    VecPoint origin = this->getOrigin();
    double originX = origin.getX();
    double originY = origin.getY();
    double originZ = origin.getZ();

    A = pow(vectorX, 2) + pow(vectorY, 2) + pow(vectorZ, 2);
    B = 2 * (vectorX*originX - vectorX*sphereX + vectorY*originY - vectorY*sphereY + vectorZ*originZ - vectorZ*sphereZ);
    C = pow(originX,2) - 2*originX*sphereX + pow(sphereX,2) + pow(originY,2) - 2*originY*sphereY + pow(sphereY,2) + pow(originZ,2) - 2*originZ*sphereZ + pow(sphereZ,2) - pow(radius,2);
    discriminant = pow(B, 2) - 4 * A * C;
    t0 = (-B - sqrt(pow(B, 2) - 4 * A * C)) / (2*A);
    t1 = (-B + sqrt(pow(B, 2) - 4 * A * C)) / (2*A);
    if (discriminant < 0)
    {
        intersection = VecPoint(0,0,0,0);
    }
    else if (A == 0) {
        intersection = VecPoint(0,0,0,0);
    }
    else if (discriminant == 0)
    {
        intersection = origin.add(vector.scale(t1));
    }
    else
    {
        if (t0 < 0 and t1 > 0)
        {
            intersection = origin.add(vector.scale(t1));
        }
        else if (t0 > 0 and t1 < 0)
        {
            intersection = origin.add(vector.scale(t0));
        } 
        else if (t0 > 0 and t1 > 0)
        {   
            double s = min(t0,t1);
            intersection = origin.add(vector.scale(s));
        }
        else {
            intersection = VecPoint(0,0,0,0);
        }
    }
    return intersection;
}

void Ray::display()
{
    cout << "origin: ";
    this->getOrigin().display();
    cout << "\nvector: ";
    this->getVector().display();
}