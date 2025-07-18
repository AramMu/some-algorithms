#ifndef EDGE
#define EDGE

class edge {
public:
    int u,v;
    edge ();
    edge (int u, int v);

    bool operator < (const edge& e);

    friend ostream& operator << (ostream& out, const edge& e);
};

class edge_s {
public:
    int u,w;
    edge_s ();
    edge_s (int u, int w);

    bool operator < (const edge_s& e);

    friend ostream& operator << (ostream& out, const edge_s& e);
};

class edge_d {
public:
    int u,v,w;
    edge_d ();// : u(-1), w(inf) {}
    edge_d (int u, int v, int w);// : u(u), w(w) {}

    bool operator < (const edge_d& e);

    friend ostream& operator << (ostream& out, const edge_d& e);
};

#endif // EDGE

