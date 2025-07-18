#ifndef GEOMETRY_STRUCT_H
#define GEOMETRY_STRUCT_H

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <cmath>
#define eps 0.000001
#define inf 1000000000
#define pi 3.1415

using namespace std;

class Point;
class Point3D;
class Vector;
class Vector3D;
class Line;
class Line3D;
class Plane;
class Circle;

class Point
{
public:
    double x;
    double y;
    Point ();
    Point (const Point&);
    Point (double, double);

    friend istream& operator >> (istream&, Point&);
    friend ostream& operator << (ostream&, const Point&);

    bool operator == (const Point& p) {
        return x == p.x && y == p.y;
    }
};

class Point3D {
public:
    double x;
    double y;
    double z;
    Point3D ();
    Point3D (const Point3D& p);
    Point3D (double, double, double);

    friend istream& operator >> (istream &in, Point3D& p);
    friend ostream& operator << (ostream &out, const Point3D& p);
};

class Vector {
public:
    double x;
    double y;
    Vector ();
    Vector (const Vector& p);
    Vector (double x, double y);
    Vector (const Point& p1, const Point& p2);
    friend istream& operator >> (istream &in, Vector& p);
    friend ostream& operator << (ostream &out, const Vector& p);
};

class Vector3D {
public:
    double x;
    double y;
    double z;
    Vector3D ();
    Vector3D (const Vector3D& p);
    Vector3D (double x, double y, double z);
    Vector3D (const Point3D& p1, const Point3D& p2);
    friend istream& operator >> (istream &in, Vector3D& p);
    friend ostream& operator << (ostream &out, const Vector3D& p);
};


class Line {
public:
    double a;
    double b;
    double c;
    Line ();
    Line (double a, double b, double c);
    Line (const Line& line);
    Line (const Point& p1, const Point& p2);
    Line (const Point& p1, const Point& p2, int isvec);
    friend istream& operator >> (istream &in, Line& line);
    friend ostream& operator << (ostream &out, const Line& line);
};

class Circle {
public:
    double x;
    double y;
    double r;
    Circle ();
    Circle (const Circle& c);
    Circle (double x, double y, double r);
    Circle (Point p, double r);
    Circle (Point p1, Point p2, Point p3);
    friend istream& operator >> (istream &in, Circle& c);
    friend ostream& operator << (ostream &out, const Circle& c);
};

class Plane {
public:
    double a;
    double b;
    double c;
    double d;
    Plane ();
    Plane (double a, double b, double c);
    Plane (const Plane& plane);
    Plane (const Point3D& p1, const Point3D& p2);
    Plane (const Point3D& p1, const Point3D& p2, const Point3D& p3);
    Vector3D normal () {
        return Vector3D (a,b,c);
    }
    friend istream& operator >> (istream &in, Plane& plane);
    friend ostream& operator << (ostream &out, const Plane& plane);
};

class compXY {
public:
    bool operator () (const Point& p1, const Point& p2) const {
        if (p1.x == p2.x) {
            return p1.y < p2.y;
        }
        return p1.x < p2.x;
    }
};

class compYX {
public:
    bool operator () (const Point& p1, const Point& p2) const {
        if (p1.y == p2.y) {
            return p1.x < p2.x;
        }
        return p1.y < p2.y;
    }
};









//typedef vector <Point> Polygon;


#endif // GEOMETRY_STRUCT_H

