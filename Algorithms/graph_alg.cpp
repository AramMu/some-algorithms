#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include "graph_alg.h"
#include "structures.h"


vector <int> shortest (Graph& g, int st) {
    int n = g.size();
    vector <int> dist (n, -1);
    queue <int> q;
    q.push(st);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = 0; i < g[t].size(); i++) {
            int x = g[t][i];
            if (dist[x] < 0) {
                dist[x] = dist[t]+1;
                q.push (x);
            }
        }
    }
    return dist;
}

vector <int> shortestPos (GraphW& g, int st) {
    int n = g.size();
    vector <int> dist (n, -1);
    Heap h (n);
    while (!h.empty()) {
        edge_s t = h.top();
        h.pop();
        dist[t.u] = t.w;
        for (int i = 0; i < g[t.u].size(); i++) {
            edge_s x = g[t.u][i];
            h.decrease(edge_s (x.u, dist[t.u] + x.w));
            //if (dist[x.u] < 0) {
            //    dist[x.u] = dist[t.u] + x.w;
            //}
        }
    }
    return dist;
}

vector <int> shortestNeg (GraphW& g, int st) {
    int n = g.size();
    vector <int> dist (n, inf);
    dist[st] = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                edge_s x = g[i][j];
                dist[x.u] = min (dist[x.u], dist[i] + x.w);
            }
        }
    }
    return dist;
}

Graph allPair (Graph g) {
    int n = g.size();
    //Graph r = g;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = min (g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    return g;
}

vector <int> bfs (Graph& g, int st, vector <bool>& used) {
    int n = g.size();
    queue <int> q;
    used[st] = true;
    q.push (st);
    vector <int> res;
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        res.push_back (t);
        for (int i = 0; i < n; i++) {
            int x = g[t][i];
            if (!used[x]) {
                used[x] = true;
                q.push (x);
            }
        }
    }
    return res;
}

vector <vector <int> > getComp (Graph& g) {
    int n = g.size();
    vector <bool> used (n, false);
    vector <vector <int> > res;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            res.push_back (bfs (g, i, used));
        }
    }
    return res;
}

vector <vector <int> > getComp (GraphW& g);
vector <vector <int> > getCompRegion (Graph& g);
vector <vector <int> > getCompRegion (GraphW& g, vector <edge_d>& e, int limit) {
    int n = g.size();
    Disjoint disj (n);
    for (int i = 0; i < e.size(); i++) {
        if (disj.count < limit) {
            break;
        }
        disj.merge(e[i].u, e[i].v);
    }
    return disj.getComp();
}

int mst (vector <edge_d>& e, int n, vector <edge>& res) {
    sort (e.begin(), e.end());
    Disjoint f(n);
    res = vector<edge>();
    int sum=0;
    for (int i = 0; i < e.size(); i++) {
        if (f.count == 1) {
            break;
        }
        if (f.merge(e[i].u, e[i].v)) {
            res.push_back ( edge (e[i].u, e[i].v));
            sum += e[i].w;
        }
    }
    return sum;
}

int mst (GraphW & g, vector <edge>& res) {
    int n = g.size();
    Heap h(n, 0);
    vector <int> dist(n, inf);
    dist[0] = 0;
    while (!h.empty()) {
        edge_s t = h.top();
        h.pop();
        for (int i = 0; i < g[t.u].size(); i++) {
            edge_s x = g[t.u][i];
            h.decrease(edge_s (x.u, dist[t.u] + x.w));
        }
    }
}

void _bridge (Graph& g, int st, vector <int> d, vector <int> m, vector <edge>& res, int& t) {
    d[st] = t;
    m[st] = d[st];
    t++;
    for (int i = 0; i < g[st].size(); i++) {
        int x = g[st][i];
        if (d[x] >= inf) {
            _bridge (g, x, d, m, res, t);
            if (m[x] >= d[st]) {
                res.push_back (edge (st, x));
            }
        }
        m[st] = min (m[st], m[x]);

        //else {
        //    m[st] = min (m[st], m[x]);
        //}
    }
}

vector <edge> bridge (Graph& g) {
    vector <edge> e;
    vector <int> d(inf), m(inf);
    int t=0;
    _bridge(g, 0, d, m, e, t);
    return e;
}





