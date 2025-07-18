#include "binary_heap.h"

Heap::Heap (int n, int ind) {
    this->n = n;
    h.resize(n);
    id.resize(n);
    for (int i = 0; i < n; i++) {
        h[i] = edge_s (i, inf);
        id[i] = i;
    }
    h[ind].w = 0;
    swap (0, ind);
}

void Heap::swap (int k, int t) {
    id [h[k].u] = t;
    id [h[t].u] = k;
    edge_s tmp = h[k];
    h[k] = h[t];
    h[t] = tmp;
}

void Heap::heapup (int k) {
    while (k > 0 && h[k] < h[(k-1)/2]) {
        swap (k, (k-1)/2);
        k = (k-1)/2;
    }
}

void Heap::heapdown (int k) {
    while (2*k+1 < n) {
        if (2*k+2 < n && h[2*k+2] < h[k] && h[2*k+2] < h[2*k+1]) {
            swap (k, 2*k+2);
            k = 2*k+2;
        } else if (h[2*k+1] < h[k] && (2*k+2 >= n || h[2*k+1] < h[2*k+2])) {
            swap (k, 2*k+1);
            k = 2*k+1;
        } else {
            break;
        }
    }
}

edge_s Heap::top () {
    return h[0];
}
void Heap::pop () {
    swap (0,n-1);
    id [h[n-1].u] = -1;
    n--;
    heapdown (0);
}
bool Heap::decrease (edge_s e) {
    int u = e.u;
    int w = e.w;
    if (h[id[u]].w < w) {
        return false;
    }
    h[id[u]].w = w;
    heapup (id[u]);
    return true;
}

bool Heap::empty() {
    return n <= 0;
}
ostream& operator << (ostream& out, Heap& hp) {
    for (int i = 0; i < hp.id.size(); i++) {
        out << hp.id[i] << " ";
    }
    out << endl;
    for (int i = 0; i < hp.h.size(); i++) {
        out << hp.h[i];
    }
    //out << endl;
    return out;
}
