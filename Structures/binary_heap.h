#ifndef BINARY_HEAP
#define BINARY_HEAP
//#include <vector>
#include "basic_structs.h"

class Heap {
public:
    int n;
    Vector <edge_s> h;
    Vector <int> id;
    Heap (int n, int ind=0);

    void swap (int k, int t);

    void heapup (int k);

    void heapdown (int k);

    edge_s top ();
    void pop ();
    bool decrease (edge_s e);
    bool empty ();

    friend std::ostream& operator << (std::ostream& out, Heap& hp);
};

#endif // BINARY_HEAP

