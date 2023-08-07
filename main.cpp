#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RBTree.h"

void test_RBTree1() {
    wyp::RBTree<int, int> t;
//    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
//    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for (auto &e: a) {
        t.insert(make_pair(e, e));
    }
    t.InOrder();
    cout << t.IsBalance() << endl;
}

void test_RBTree2() {
    const int N = 100000;
    wyp::RBTree<int, int> t;
    srand(time(nullptr));
    for (int i = 0; i < N; ++i) {
        int x = rand();
        t.insert(make_pair(x, x));
    }
    t.InOrder();
    cout << t.IsBalance() << endl;
}

int main() {
    test_RBTree2();

    return 0;
}
