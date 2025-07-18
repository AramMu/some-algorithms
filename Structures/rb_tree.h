#ifndef RB_TREE_H
#define RB_TREE_H
#include "basic_structs.h"
#include <iostream>
//#include <vector>
#define BLACK 0
#define RED 1

template <class T>
class Node {
public:
    Node ();
    Node (T& data);
    int l,r,p;
    int color;
    T data;
};

template <class T>
class RBTree {
public:
    RBTree ();// : root(-1){}
    int search (T& data);
    void insert (T& data);
    void erase (T& data);
    Vector <T> getArray ();
    //friend ostream& operator << (ostream& out, RBTree<T>& tree);
private:
    int root;
    vector <Node<T> > arr;
    int normalInsert (T& data);
    int color (int ind);
    bool isLeft (int ind);
    bool isRight (int ind);
    void lrot (int x);
    void rrot (int x);
    void _getArray (int x, vector <T>& res);
    int successor (int x);
    void _erase (int x);
    void remove (int x);
};

template <class T>
Node<T>::Node () : l(-1),r(-1),p(-1),color(BLACK) {}

template <class T>
Node<T>::Node (T& data) : l(-1),r(-1),p(-1),color(BLACK),data(data) {}

template <class T>
RBTree<T>::RBTree () : root(-1) {}

template <class T>
int RBTree<T>::search(T& data){
    if (root < 0) return -1;
    int r = root;
    while (true) {
        if (data == arr[r].data) {
            return r;
        } else if (data < arr[r].data) {
            r = arr[r].l;
        } else {
            r = arr[r].r;
        }
        if (r < 0) return -1;
    }
}
template <class T>
int RBTree<T>::color (int ind) {
    if (ind < 0 || ind >= arr.size()) return BLACK;
    return arr[ind].color;
}

template <class T>
bool RBTree<T>::isLeft (int ind) {
    if (arr[ind].p < 0) return false;
    return ind == arr[arr[ind].p].l;
}

template <class T>
bool RBTree<T>::isRight (int ind) {
    if (arr[ind].p < 0) return false;
    return ind == arr[arr[ind].p].r;
}

template <class T>
int RBTree<T>::normalInsert (T& data){
    if (root < 0) {
        arr.push_back (Node<T> (data));
        root = 0;
        return 0;
    }
    int x = root;
    while (true) {
        if (data == arr[x].data) {
            return -1;
        } else if (data < arr[x].data) {
            if (arr[x].l < 0) {
                arr.push_back (Node<T> (data));
                arr.back().p = x;
                arr[x].l = arr.size()-1;
                return arr[x].l;
            }
            x = arr[x].l;
        } else {
            if (arr[x].r < 0) {
                arr.push_back (Node<T> (data));
                arr.back().p = x;
                arr[x].r = arr.size()-1;
                return arr[x].r;
            }
            x = arr[x].r;
        }
    }
}
template <class T>
void RBTree<T>::lrot (int x) {
    int y = arr[x].r;
    if (y < 0) {
        cout << "Error in lrot" << endl;
        return;
    }
    arr[y].p = arr[x].p;
    if (arr[x].p < 0) {
        root = y;
    } else {
        if (isLeft (x)) {
            arr[arr[x].p].l = y;
        } else {
            arr[arr[x].p].r = y;
        }
    }
    arr[x].r = arr[y].l;
    arr[y].l = x;
    if (arr[x].r >= 0) {
        arr[arr[x].r].p = x;
    }
    arr[x].p = y;
    return;
}

template <class T>
void RBTree<T>::rrot (int x) {
    int y = arr[x].l;
    if (y < 0) {
        cout << "Error in rrot" << endl;
        return;
    }
    arr[y].p = arr[x].p;
    if (arr[x].p < 0) {
        root = y;
    } else {
        if (isLeft (x)) {
            arr[arr[x].p].l = y;
        } else {
            arr[arr[x].p].r = y;
        }
    }
    arr[x].l = arr[y].r;
    arr[y].r = x;
    if (arr[x].l >= 0) {
        arr[arr[x].l].p = x;
    }
    arr[x].p = y;
    return;
}

template <class T>
void RBTree<T>::insert (T& data){
    int x = normalInsert (data);
    if (x < 0) return;
    arr[x].color = RED;
    arr[root].color = BLACK;
    while (x != root && color (x) == RED && color (arr[x].p) == RED) {
        int y = arr[arr[x].p].p;
        if (color (arr[y].l) == RED && color (arr[y].r) == RED) {
            arr[arr[y].l].color = arr[arr[y].r].color = BLACK;
            arr[y].color = RED;
            x = y;
            continue;
        }
        if ( isLeft (arr[x].p) && isRight (x) ) {
            x = arr[x].p;
            lrot (x);
        } else if ( isRight (arr[x].p) && isLeft (x) ) {
            x = arr[x].p;
            rrot (x);
        }
        if (isLeft (x)) {
            arr[y].color = RED;
            arr[arr[x].p].color = BLACK;
            rrot (y);
        } else {
            arr[y].color = RED;
            arr[arr[x].p].color = BLACK;
            lrot (y);
        }
        break;
    }
    arr[root].color = BLACK;
}



































template <class T>
void RBTree<T>::remove (int x) {
    //cout << "before removal, x " << x << endl << *this << endl;
    int n = arr.size();
    if (n==1) {
        arr.pop_back();
        root = -1;
        return;
    }
    if (root == n-1) root = x;

    bool b1,b2,b3,b4;
    b1 = isLeft(n-1);
    b2 = isRight(n-1);
    b3 = isLeft(x);
    b4 = isRight(x);
    if (b1) {
        arr[arr[n-1].p].l=x;
    } else if (b2) {
        arr[arr[n-1].p].r=x;
    }
    if (arr[n-1].l >= 0) {
        arr[arr[n-1].l].p = x;
    }
    if (arr[n-1].r >= 0) {
        arr[arr[n-1].r].p = x;
    }
    /*
    if (b3) {
        arr[arr[x].p].l = -1;
    } else if (b4) {
        arr[arr[x].p].r = -1;
    }
    */
    /*
    if (isLeft(n-1)) {
        arr[arr[n-1].p].l=x;
    } else if (isRight(x)) {
        arr[arr[n-1].p].r=x;
    }
    if (isLeft(x)) {
        arr[arr[x].p].l = -1;
    } else if (isRight(x)) {
        arr[arr[x].p].r = -1;
    }R
    */
    Node<T> tmp = arr[x];
    arr[x] = arr[n-1];
    arr[n-1] = tmp;
    arr.pop_back();
    if (arr.empty()) root = -1;
    /*
    cout << "after removal"<< endl;// << *this << endl;
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i].data << " ";
    }
    cout << endl;
    */
}

template <class T>
int RBTree<T>::successor (int x) {
    if (arr[x].r < 0) {
        return -1;
    }
    x = arr[x].r;
    while (arr[x].l >= 0) {
        x = arr[x].l;
    }
    return x;
}

template <class T>
void RBTree<T>::_erase(int x) {
    if (x == root) {
        /*
        int y = arr[x].l>=0 ? arr[x].l : arr[x].r;
        if (y>=0) {
            arr[y].p = -1;
        }
        root = y;
        //if (root>=1&&root == arr.size()-1) {
        //    root = x;
        //}

        cout << "before removal, type root x " << x << endl;
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i].data << " ";
        }
        cout << endl;
        remove (x);
        */
        int y;
        if (arr[x].l>=0) {
            y = arr[x].l;
            arr[x].data = arr[y].data;
            arr[x].l=-1;
            arr[y].p=-1;
            remove(y);
        } else if (arr[x].r>=0) {
            y = arr[x].r;
            arr[x].data = arr[y].data;
            arr[x].r=-1;
            arr[y].p=-1;
            remove(y);
        } else {
            root = -1;
            remove(x);
        }
        return;
    }
    if (arr[x].l>=0 || arr[x].r>=0) {
        int y;// = (x->l ? x->l : x->r);
        if (arr[x].l>=0) {
            y = arr[x].l;
            arr[x].l=-1;
            arr[y].p = -1;
        } else if (arr[x].r>=0) {
            y = arr[x].r;
            arr[x].r=-1;
            arr[y].p = -1;
        }
        arr[x].data = arr[y].data;
        arr[x].color = BLACK;

//        cout << "before removal, type leftright x " << y << endl;
//        for (int i = 0; i < arr.size(); ++i) {
//            cout << arr[i].data << " ";
//        }
//        cout << endl;
        remove(y);
        return;
    }
    if (color(x) == RED) {
        if (isLeft(x)) {
            arr[arr[x].p].l = -1;
        } else {
            arr[arr[x].p].r = -1;
        }
        arr[x].p = -1;
//        cout << "before removal, type red x " << x << endl;
//        cout << *this << endl;
//        for (int i = 0; i < arr.size(); ++i) {
//            cout << arr[i].data << " ";
//        }
//        cout << endl;
        remove (x);
        return;
    }
    int del = x;
    int lv=0;
    bool flag=true;
    while (x != root && color(x) == BLACK) {
        lv++;
        int y = (isLeft(x) ? arr[arr[x].p].r : arr[arr[x].p].l);
        if (y<0) {
            cout << "error y is null, level " << lv << " " << flag << endl;
            break;
        }
        if (color(y) == BLACK && (color(arr[y].l)==BLACK) && (color(arr[y].l)==BLACK)) {
            flag=false;
            arr[y].color = RED;
            x = arr[x].p;
            if (color(x) == RED) {
                arr[x].color = BLACK;
                break;
            }
            continue;
        }
        if (color(y) == RED) {
            arr[arr[x].p].color = RED;
            arr[y].color = BLACK;
            if (isLeft(x)) {
                lrot (arr[x].p);
            } else {
                rrot (arr[x].p);
            }
            continue;
        }
        if (isRight(y) && color(arr[y].l)==RED && color(arr[y].r) == BLACK) {
            arr[y].color = RED;
            arr[arr[y].l].color = BLACK;
            y = arr[y].l;
            rrot (arr[y].p);
        } else if (isLeft(y) && color(arr[y].r)==RED && color(arr[y].l)==BLACK) {
            arr[y].color = RED;
            arr[arr[y].r].color = BLACK;
            y = arr[y].r;
            lrot (arr[y].p);
        }
        if (isLeft(x)) {
            arr[y].color = arr[arr[x].p].color;
            arr[arr[x].p].color = BLACK;
            arr[arr[y].r].color = BLACK;
            lrot (arr[x].p);
        } else {
            arr[y].color = arr[arr[x].p].color;
            arr[arr[x].p].color = BLACK;
            arr[arr[y].l].color = BLACK;
            rrot (arr[x].p);
        }
        break;
    }
    if (isLeft(del)) {
        arr[arr[del].p].l = -1;
    } else {
        arr[arr[del].p].r = -1;
    }
    arr[del].p = -1;

//    cout << "before removal, type black x " << del << endl;
//    for (int i = 0; i < arr.size(); ++i) {
//        cout << arr[i].data << " ";
//    }
//    cout << endl;
    remove (del);
}

template <class T>
void RBTree<T>::erase(T& data) {
    int x = search(data);
    if (x < 0) return;
    if (arr[x].l>=0 && arr[x].r>=0) {
        int y = successor (x);
        arr[x].data = arr[y].data;
        //int tmp = arr[y].data;
        _erase (y);
        return;
    } else {
        _erase (x);
    }
}



























template <class T>
void RBTree<T>::_getArray (int x, vector <T>& res){
    if (arr[x].l >= 0) {
        _getArray(arr[x].l, res);
    }
    res.push_back(arr[x].data);
    if (arr[x].r >= 0) {
        _getArray (arr[x].r, res);
    }
}

template <class T>
Vector<T> RBTree<T>::getArray(){
    vector <T> res;
    if (root < 0) {
        return res;
    }
    _getArray (root, res);
    return res;
}


template <class T>
ostream& operator << (ostream& out, RBTree<T>& tree){
    vector <T> res = tree.getArray();
    for (int i = 0; i < res.size(); ++i) {
        out << res[i] << " ";
    }
    out << endl;
    return out;
}


#undef RED
#undef BLACK
#endif // RB_TREE_H

