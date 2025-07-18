#ifndef DISJOINT_SET
#define DISJOINT_SET
#include <vector>
#include "basic_structs.h"

class Disjoint {
public:
    int count;
    Vector <int> p;
    //vector <int> rank;
    Vector <int> width;
    Disjoint (int n);
    int _get (int x, int deep);
    int get (int x);
    bool merge (int u, int v);
    Matrix <int> getComp();
    friend ostream& operator << (ostream& out, Disjoint& d);
};

#endif // DISJOINT_SET

