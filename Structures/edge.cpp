#include "edge.h"

edge::edge () : u(-1), v(-1) {}
edge::edge (int u, int v) : u(u), v(v) {}

bool edge::operator < (const edge& e) {
    return this->u < e.u;
}

ostream& operator << (ostream& out, const edge& e) {
    out << e.u << " " << e.v << endl;
    return out;
}



edge_s::edge_s () : u(-1), w(inf) {}
edge_s::edge_s (int u, int w) : u(u), w(w) {}

bool edge_s::operator < (const edge_s& e) {
    return this->w < e.w;
}

ostream& operator << (ostream& out, const edge_s& e) {
    out << e.u << " " << e.w << endl;
    return out;
}




edge_d::edge_d () : u(-1), v(-1), w(inf) {}
edge_d::edge_d (int u, int v, int w) : u(u), v(v), w(w) {}

bool edge_d::operator < (const edge_d& e) {
    return this->w < e.w;
}

ostream& operator << (ostream& out, const edge_d& e) {
    out << e.u << " " << e.v << " " << e.w << endl;
    return out;
}
