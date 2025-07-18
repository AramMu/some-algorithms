#include "geometry_alg.h"
#include "geometry_struct.h"

Point::Point () {}
Point::Point (const Point& p) : x(p.x), y(p.y) {}
Point::Point (double x, double y) : x(x), y(y) {}

istream& operator >> (istream &in, Point& p) {
    in >> p.x;
    in >> p.y;
    return in;
}
ostream& operator << (ostream &out, const Point& p) {
    out << p.x << " ";
    out << p.y << "\n";
    return out;
}



Point3D::Point3D () {}
Point3D::Point3D (const Point3D& p) : x(p.x), y(p.y), z(p.z) {}
Point3D::Point3D (double x, double y, double z) : x(x), y(y), z(z) {}

istream& operator >> (istream &in, Point3D& p) {
    in >> p.x;
    in >> p.y;
    in >> p.z;
    return in;
}
ostream& operator << (ostream &out, const Point3D& p) {
    out << p.x << " ";
    out << p.y << " ";
    out << p.z << "\n";
    return out;
}



Vector::Vector () {}
Vector::Vector (const Vector& p) : x(p.x), y(p.y) {}
Vector::Vector (double x, double y) : x(x), y(y) {}
Vector::Vector (const Point& p1, const Point& p2) : x(p2.x-p1.x), y(p2.y-p1.y) {}
istream&  operator >> (istream &in, Vector& p) {
    in >> p.x;
    in >> p.y;
    return in;
}
ostream&  operator << (ostream &out, const Vector& p) {
    out << p.x << " ";
    out << p.y << "\n";
    return out;
}



Vector3D::Vector3D () {}
Vector3D::Vector3D (const Vector3D& p) : x(p.x), y(p.y), z(p.z) {}
Vector3D::Vector3D (double x, double y, double z) : x(x), y(y), z(z) {}
Vector3D::Vector3D (const Point3D& p1, const Point3D& p2) : x(p2.x-p1.x), y(p2.y-p1.y), z(p2.z-p1.z) {}
istream& operator >> (istream &in, Vector3D& p) {
    in >> p.x;
    in >> p.y;
    in >> p.z;
    return in;
}
ostream& operator << (ostream &out, const Vector3D& p) {
    out << p.x << " ";
    out << p.y << " ";
    out << p.z << "\n";
    return out;
}


Line::Line () {}
Line::Line (double a, double b, double c) : a(a), b(b), c(c) {}
Line::Line (const Line& line) : a(line.a), b(line.b), c(line.c) {}
Line::Line (const Point& p1, const Point& p2) :
    a(p2.y-p1.y), b(p1.x-p2.x), c((p2.x-p1.x)*p1.y - (p2.y-p1.y)*p1.x) {}
Line::Line (const Point& p1, const Point& p2, int isvec) {
    switch (isvec) {
    case 0:
        a = (p2.y-p1.y);
        b = (p1.x-p2.x);
        c = ((p2.x-p1.x)*p1.y - (p2.y-p1.y)*p1.x);
        break;
    case 1:
        a = p1.x;
        b = p1.y;
        c = -p1.x * p2.x - p1.y * p2.y;
        break;
    case 2:
        a = p2.x;
        b = p2.y;
        c = -p1.x * p2.x - p1.y * p2.y;
        break;

    default:
        cout << "ERROR in line constructor p1,p2,isvec = "
             << p1 << " " << p2 << " " << isvec << "\n";
    }
}
istream& operator >> (istream &in, Line& line) {
    in >> line.a;
    in >> line.b;
    in >> line.c;
    return in;
}
ostream& operator << (ostream &out, const Line& line) {
    out << line.a << " ";
    out << line.b << " ";
    out << line.c << "\n";
    return out;
}


Circle::Circle () {}
Circle::Circle (const Circle& c) : x(c.x), y(c.y), r(c.r) {}
Circle::Circle (double x, double y, double r) : x(x), y(y), r(r) {}
Circle::Circle (Point p, double r) : x(p.x), y(p.y), r(r) {}
Circle::Circle (Point p1, Point p2, Point p3) {
    Line l1(p1, p2), l2(p1, p3);
    l1 = Line (Point (p2.x-p1.x, p2.y-p1.y), Point((p1.x+p2.x)/2, (p1.y+p2.y)/2 ), 1);
    l2 = Line (Point (p3.x-p1.x, p3.y-p1.y), Point((p1.x+p3.x)/2, (p1.y+p3.y)/2 ), 1);
    Point p;
    if (intersect (l1,l2, p) ) {
        x = p.x;
        y = p.y;
        r = sqrt (pow(p1.x-x, 2) + pow(p1.y-y, 2) );
    } else {
        x = 0;
        y = 0;
        r = -1;
    }
}
istream& operator >> (istream &in, Circle& c) {
    in >> c.x;
    in >> c.y;
    in >> c.r;
    return in;
}
ostream& operator << (ostream &out, const Circle& c) {
    out << c.x << " ";
    out << c.y << " ";
    out << c.r << "\n";
    return out;
}

Plane::Plane () {}
Plane::Plane (double a, double b, double c) : a(a), b(b), c(c) {}
Plane::Plane (const Plane& plane) : a(plane.a), b(plane.b), c(plane.c) {}
Plane::Plane (const Point3D& p1, const Point3D& p2) :
    a(p2.y-p1.y), b(p1.x-p2.x), c((p2.x-p1.x)*p1.y - (p2.y-p1.y)*p1.x) {}
Plane::Plane (const Point3D& p1, const Point3D& p2, const Point3D& p3) {
    Vector3D v1(p1,p2);
    Vector3D v2(p1,p3);
    Vector3D norm (cross (v1,v2));
    a = norm.x;
    b = norm.y;
    c = norm.z;
    d = -(a*p1.x + b*p1.y + c*p1.z);
}
istream& operator >> (istream &in, Plane& plane) {
    in >> plane.a;
    in >> plane.b;
    in >> plane.c;
    in >> plane.d;
    return in;
}
ostream& operator << (ostream &out, const Plane& plane) {
    out << plane.a << " ";
    out << plane.b << " ";
    out << plane.c << " ";
    out << plane.d << "\n";
    return out;
}



typedef vector <Point> Polygon;
