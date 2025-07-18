#ifndef GEOMETRY_ALG_H
#define GEOMETRY_ALG_H

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <cmath>
#include "geometry_struct.h"

using namespace std;
typedef vector <Point> Polygon;

Vector3D cross (const Vector3D& v1, const Vector3D& v2);
double cross (const Vector &v1, const Vector &v2);
double scalar (const Point& p1, const Point& p2);
double scalar (const Point3D& p1, const Point3D& p2);
double cross (double a1, double b1, double a2, double b2);
double cross (Point p1, Point p2);
bool intersect (const Line& l1, const Line& l2, Point& res);
bool contains (const Circle& c, const Point& p);
bool contains (const Plane& p1ane, const Point3D& p);


double closest (vector <Point>);
double closestRec (vector <Point>);

#endif // GEOMETRY_ALG_H

