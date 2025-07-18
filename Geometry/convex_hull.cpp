#include <vector>
#include "geometry_alg.h"
#include "geometry_struct.h"
#include "convex_hull.h"

Polygon _convexXY (vector <Point>& pg) {
    Polygon r1,r2;
    int n = pg.size();
    for (int i = 0; i < n; i++) {
        if (r1.size() >= 2) {
            Point p1, p2;
            p2 = r1[ r1.size()-1 ];
            p1 = r1[ r1.size()-2 ];
            while (r1.size() >= 2 && cross (Vector(p1,p2), Vector (p2, pg[i])) < 0) {
                r1.pop_back();
                if (r1.size() < 2) {
                    break;
                }
                p2 = r1[ r1.size()-1 ];
                p1 = r1[ r1.size()-2 ];
            }
        }
        r1.push_back (pg[i]);
    }
    r1.pop_back();
    for (int i = n-1; i >= 0; i--) {
        if (r2.size() >= 2) {
            Point p1, p2;
            p2 = r2[ r2.size()-1 ];
            p1 = r2[ r2.size()-2 ];
            while (r2.size() >= 2 && cross (Vector(p1,p2), Vector (p2, pg[i])) < 0) {
                r2.pop_back();
                if (r2.size() < 2) {
                    break;
                }
                p2 = r2[ r2.size()-1 ];
                p1 = r2[ r2.size()-2 ];
            }
        }
        r2.push_back (pg[i]);
    }
    r2.pop_back();
    Polygon res = r1;
    for (int i = 0; i < r2.size(); i++) {
        res.push_back (r2[i]);
    }
    return res;
}

int pos (Line line, Point p) {
    if (abs (line.b) < eps) {
        if  (p.x > -line.c/line.a) {
            return 1;
        } else if (p.x < -line.c/line.a) {
            return -1;
        } else {
            return 0;
        }
    }
    double y = -(line.a*p.x - line.c) / line.b;
    if (p.y > y) {
        return 1;
    } else if (p.y < y) {
        return -1;
    } else {
        return 0;
    }
}

int orientation (Point& p1, Point& p2, Point& p3) {
    Vector v1(p1,p2);
    Vector v2(p2,p3);
    return cross (v1,v2);
}

void lower_support (Polygon& p1, Polygon& p2, int& res1, int& res2) {
    int max = p1[0].x;
    int min = p2[0].x;
    int ls=0, rs=0;
    int n1 = p1.size(), n2 = p2.size();
    for (int i = 0; i < n1; i++) {
        if (p1[i].x > max) {
            max = p1[i].x;
            ls = i;
        }
    }
    for (int i = 0; i < n2; i++) {
        if (p2[i].x < min) {
            min = p2[i].x;
            rs = i;
        }
    }
    //cout << "n1, n2, ls, rs " << n1 << " " << n2 << " " << ls << " " << rs << endl;
    while (true) {
        //cout << "a";
        if (n2 > 1 && orientation (p1[ls], p2[rs], p2[(rs+1)%n2]) <= 0 ) {//pos ( Line (p1[ls], p2[rs], 0), p2[(rs+1)%n2]) <= 0) {
            rs = (rs+1)%n2;
        } else if (n1 > 1 && orientation (p2[rs], p1[ls], p1[(ls-1+n1)%n1]) >= 0 ) {
            ls = (ls-1+n1)%n1;
        } else {
            break;
        }
    }
    res1 = ls;
    res2 = rs;
    //cout << "res1, res2 " << res1 << " " << res2 << endl;
    return;
}

void upper_support (Polygon& p1, Polygon& p2, int& res1, int& res2) {
    int max = p1[0].x;
    int min = p2[0].x;
    int ls=0, rs=0;
    int n1 = p1.size(), n2 = p2.size();
    for (int i = 0; i < n1; i++) {
        if (p1[i].x > max) {
            max = p1[i].x;
            ls = i;
        }
    }
    for (int i = 0; i < n2; i++) {
        if (p2[i].x < min) {
            min = p2[i].x;
            rs = i;
        }
    }
    //cout << "n1, n2, ls, rs " << n1 << " " << n2 << " " << ls << " " << rs << endl;
    while (true) {
        //cout << "a";
        if (n2 > 1 && orientation (p1[ls], p2[rs], p2[(rs-1+n2)%n2]) >= 0 ) {//pos ( Line (p1[ls], p2[rs], 0), p2[(rs+1)%n2]) <= 0) {
            rs = (rs-1+n2)%n2;
        } else if (n1 > 1 && orientation (p2[rs], p1[ls], p1[(ls+1)%n1]) <= 0 ) {
            ls = (ls+1)%n1;
        } else {
            break;
        }
    }
    res1 = ls;
    res2 = rs;
    //cout << "res1, res2 " << res1 << " " << res2 << endl;
    return;
}

Polygon _convexDiv (vector <Point>& p, int b, int e) {
    if (e-b <= 1) {
        return Polygon(1, p[b]);
    }
    int m = (e+b)/2;
    //cout << "start" << endl;
    Polygon p1 = _convexDiv (p, b, m);
    Polygon p2 = _convexDiv (p, m, e);
    //cout << "end" << endl;
    int l1,l2,u1,u2;
    lower_support (p1, p2, l1, l2);
    //cout << "lower" << endl;
    upper_support (p1, p2, u1, u2);
    //cout << "upper" << endl;
        //cout << "l1, u1, l2, u2 " << l1 << " " << u1 << " " << l2 << " " << u2 << endl;
    Polygon res;
    //cout << "aaa" << endl;
    int n1=p1.size(), n2 = p2.size();
    for (int i = u1; i != l1; i = (i+1)%n1) {
        res.push_back(p1[i]);
    }
    //if (! (p1[l1] == p1[u1])) {
        res.push_back(p1[l1]);
    //}

    for (int i = l2; i != u2; i = (i+1)%n2) {
        res.push_back(p2[i]);
    }
    //if (! (p2[l2] == p2[u2])) {
        res.push_back(p2[u2]);
    //}
    //cout << "bbb" << endl;
    return res;
}

Polygon convexHull (vector<Point> p, int sorttype) {
    if (sorttype == 1) {
        return _convexXY (p);
    } else if (sorttype == 2) {
        return Polygon();
        //return _convexAngle (p);
    } else {
        sort (p.begin(), p.end(), compXY());
        return _convexDiv (p, 0, p.size());
    }
}
