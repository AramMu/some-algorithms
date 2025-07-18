#include <sorting.h>
#include <vector>

void swap (int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

vector <int> bubbleSort (vector <int> x) {
    int n = x.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (x[j] < x[j+1]) {
                swap (x[i], x[j]);
            }
        }
    }
    return x;
}

vector <int> insertSort (vector <int> x) {
    int n = x.size();
    for (int i = 1; i < n; i++) {
        int tmp = x[i];
        int j = i;
        while (j > 0 && tmp < x[j-1]) {
            x[j] = x[j-1];
            j--;
        }
        x[j+1] = tmp;
    }
    return x;
}

vector <int> selectionSort (vector <int> x) {
    int n = x.size();
    for (int i = 0; i < n-1; i++) {
        int m = x[i];
        int ind = i;
        for (int j = i+1; j < n; j++) {
            if (x[j] < m) {
                m = x[j];
                ind = j;
            }
        }
        swap (x[i], x[ind]);
    }
    return x;
}

vector <int> mergeSort (vector <int> x) {
    int n = x.size();
    vector <int> tmp(n);
    for (int k = 2; k < n; k*=2) {
        for (int i = 0; i < n; i+=k) {
            int b = i;
            int e = i+k < n ? i+k : n;
            int m = (b+e)/2;
            int l=b, r=m;
            for (int i = b; i < e; i++) {
                if (l < m && (r >= e || x[l] < x[r])) {
                    tmp[i] = x[l];
                    l++;
                } else {
                    tmp[i] = x[r];
                    r++;
                }
            }
            for (int i = b; i < e; i++) {
                x[i] = tmp[i];
            }
        }
    }
    return x;
}

void heapify (vector <int>& x, int k, int n) {
    while (2*k+1 < n) {
        if (x[2*k+1] > x[k] && (2*k+2 >= n || x[2*k+1] >= x[2*k+2])) {
            swap (x[k], x[2*k+1]);
            k = 2*k+1;
        } else if (2*k+2 < n && x[2*k+2] > x[k] && x[2*k+2] >= x[2*k+1]) {
            swap (x[k], x[2*k+2]);
            k = 2*k+2;
        } else {
            break;
        }
    }
}

vector <int> heapSort (vector <int> x) {
    int n = x.size();
    for (int i = n/2-1; i >= 0; i-- ) {
         heapify (x, i, n);
    }
    for (int i = n-1; i > 0; i--) {
        swap (x[i], x[0]);
        heapify (x, 0, i);
    }
    return x;
}

vector <int> treeSort (vector <int> x);
vector <int> quickSort (vector <int> x);
