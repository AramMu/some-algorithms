#ifndef GRAPH_ALG
#define GRAPH_ALG
#include "basic_structs.h"

vector <int> shortest (Graph& g, int st=0);
vector <int> shortestPos (GraphW& g, int st=0);
vector <int> shortestNeg (GraphW& g, int st=0);
Graph allPair (Graph& g);
vector <vector <int> > getComp (Graph& g);
vector <vector <int> > getComp (GraphW& g);
vector <vector <int> > getCompRegion (Graph& g);
vector <vector <int> > getCompRegion (GraphW& g, vector <edge_d>& e, int limit);
int mst (vector <edge_d>& e, int n, vector <edge>& res);
int mst (Graph& g, vector <edge>& res);
vector <edge> bridge (Graph& g);

#endif // GRAPH_ALG

