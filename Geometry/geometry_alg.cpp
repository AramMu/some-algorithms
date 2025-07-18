#include "geometry_alg.h"
#include "geometry_struct.h"


Vector3D cross (const Vector3D& v1, const Vector3D& v2) {
    return Vector3D (
        v1.y*v2.z - v1.z*v2.y,
        v1.z*v2.x - v1.x*v2.z,
        v1.x*v2.y - v1.y*v2.x
    );
}

double scalar (const Point& p1, const Point& p2) {
    return p1.x*p2.x + p1.y*p2.y;
}

double scalar (const Point3D& p1, const Point3D& p2) {
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

double cross (double a1, double b1, double a2, double b2) {
    return a1*b2 - a2*b1;
}

double cross (const Vector &v1, const Vector &v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

double cross (Point p1, Point p2) {
    return p1.x*p2.y - p1.y*p2.x;
}

bool intersect (const Line& l1, const Line& l2, Point& res) {
    double det = cross (l1.a, l1.b, l2.a, l2.b);
    if (det == 0) {
        return false;
    }
    res.x = cross (-l1.c, l1.b, -l2.c, l2.b) / det;
    res.y = cross (l1.a, -l1.c, l2.a, -l2.c) / det;
    return true;
}

bool contains (const Circle& c, const Point& p) {
    return  abs (c.r * c.r - pow (p.x - c.x, 2) + pow (p.y - c.y, 2) ) < eps;
}

bool contains (const Plane& plane, const Point3D& p) {
    return abs (plane.a*p.x + plane.b*p.y + plane.c*p.z + plane.d) < eps;
}

double closest (vector <Point> p) {
    sort (p.begin(), p.end(), compXY());
    set <Point, compYX> s;
    int left = 0;
    int n = p.size();
    double best = inf;
    for (int i = 0; i < n; i++) {
        while (left < i && p[left].x < p[i].x-best) {
            s.erase (p[left]);
            left++;
        }

        set <Point, compYX>::iterator it = s.lower_bound( Point (p[i].x, p[i].y-best));
        while (it != s.end() && it->y < p[i].y+best) {
            double tmp = sqrt (pow (it->x - p[i].x, 2) + pow (it->y - p[i].y, 2) );
            if (tmp < best) best = tmp;
            it++;
        }
        s.insert (p[i]);
        //cout << "left, best = " << left << " " << best << endl;
    }
    //cout << "size = " << p.size() << endl;
    return best;
}

double _closest (vector <Point>& p, int b, int e) {
    if (e-b <= 1) {
        return inf;
    }
    int m = (e+b)/2;
    double med = (p[m].x + p[m-1].x)/2;
    double d =_closest (p, b, m);
    d = min (d, _closest (p, m, e));
    vector <Point> p1,p2;
    for (int i = b; i < m; i++) {
        if (med - p[i].x < d) {
            p1.push_back(p[i]);
        }
    }
    for (int i = m; i < e; i++) {
        if (p[i].x - med < d) {
            p2.push_back(p[i]);
        }
    }

    int r=0;
    int lm = p1.size(), rm = p2.size();
    for (int i = 0; i < lm; i++) {
        while (r < rm && p2[r].y - p1[i].y < d) {
            double tmp = sqrt (pow (p1[i].x - p2[r].x, 2) + pow (p1[i].y - p2[r].y, 2));
            if (tmp < d) d = tmp;
            r++;
        }
        r = r-6;
        if (r < 0) r=0;
    }
    int n = e-b;
    int l=b;
    r=m;
    vector <Point> tmp (n);
    for (int i = 0; i < n; i++) {
        if (l < m && (r >= e || p[l].y < p[r].y)) {
            tmp[i] = p[l];
            l++;
        } else {
            tmp[i] = p[r];
            r++;
        }
    }
    for (int i = 0; i < n; i++) {
        p[b+i] = tmp[i];
    }
    return d;
}


double closestRec (vector <Point> p) {
    sort (p.begin(), p.end(), compXY());
    return _closest (p, 0, p.size());
}

