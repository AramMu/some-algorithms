#include "disjoint_set.h"

Disjoint::Disjoint (int n) {
    p.resize(n);
    width.resize(n, 0);
    count = n;
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
}

int Disjoint::_get (int x, int deep) {
    if (x == p[x]) {
        width[x] += (deep-1 > 0 ? deep-1: 0);
        return x;
    }
    return x = _get(p[x], deep+1);
}

int Disjoint::get (int x) {
    return _get(x, 0);
}

bool Disjoint::merge (int u, int v) {
    int x = get(u);
    int y = get(v);
    if (x == y) {
        return false;
    }
    if (width[x] <= width[y]) {
        p[x] = y;
        width[y]++;
        width[x] = 0;
    } else {
        p[y] = x;
        width[x]++;
        width[y] = 0;
    }
    count--;
    return true;
}

Matrix Disjoint::getComp() {
    int n = p.size();
    Matrix m(n);
    for (int i = 0; i < n; i++) {
        m [get (i)].push_back(i);
    }
    Matrix res;
    for (int i = 0; i < m.size(); i++) {
        if (m[i].size() > 0) {
            res.push_back(m[i]);
        }
    }
    return res;
}

ostream& operator << (ostream& out, Disjoint& d) {
    for (int i = 0; i < d.p.size(); i++) {
        out << d.p[i] << " ";
    }
    out << endl;
    for (int i = 0; i < d.width.size(); i++) {
        out << d.width[i] << " ";
    }
    out << endl;
    return out;
}
