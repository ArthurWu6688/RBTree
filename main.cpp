#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "AVLTree.h"

void test_AVLTree_RotateR() {
    wyp::AVLTree<int, int> t;
    int a[] = {60, 30, 20};
    for (auto &e: a) {
        t.insert(make_pair(e, e));
    }
    t.InOrder();
    cout << "height:" << t.Height() << endl;
    if (t.InBalance()) {
        cout << "is balance" << endl;
    } else {
        cout << "is not balance" << endl;
    }
}

void test_VALTree_RotateL() {
    wyp::AVLTree<int, int> t;
    int a[] = {30, 40, 50};
    for (auto &e: a) {
        t.insert(make_pair(e, e));
    }
    t.InOrder();
    cout << "height:" << t.Height() << endl;
    if (t.InBalance()) {
        cout << "is balance" << endl;
    } else {
        cout << "is not balance" << endl;
    }
}

void test_AVLTree_RotateLR() {
    wyp::AVLTree<int, int> t;
    int a[] = {20, 10, 15};
    for (auto &e: a) {
        t.insert(make_pair(e, e));
    }
    t.InOrder();
    cout << "height:" << t.Height() << endl;
    if (t.InBalance()) {
        cout << "is balance" << endl;
    } else {
        cout << "is not balance" << endl;
    }
}

void test_AVLTree_RotateRL() {
    wyp::AVLTree<int, int> t;
    int a[] = {20, 40, 30};
    for (auto &e: a) {
        t.insert(make_pair(e, e));
    }
    t.InOrder();
    cout << "height:" << t.Height() << endl;
    if (t.InBalance()) {
        cout << "is balance" << endl;
    } else {
        cout << "is not balance" << endl;
    }
}

void test_AVLTree() {
    srand(time(NULL));
    const size_t N = 100000;
    wyp::AVLTree<int, int> t;
    for (size_t i = 0; i < N; ++i) {
        size_t x = rand();
        t.insert(make_pair(x, x));
    }

    t.InOrder();
    cout << "height:" << t.Height() << endl;
    if (t.InBalance()) {
        cout << "is balance" << endl;
    } else {
        cout << "is not balance" << endl;
    }
}

int main() {
    cout << "test_AVLTree_RotateR" << endl;
    test_AVLTree_RotateR();
    cout << "------------------------------" << endl;
    cout << "test_AVLTree_RotateL" << endl;
    test_VALTree_RotateL();
    cout << "------------------------------" << endl;
    cout << "test_AVLTree_RotateLR" << endl;
    test_AVLTree_RotateLR();
    cout << "------------------------------" << endl;
    cout << "test_AVLTree_RotateRL" << endl;
    test_AVLTree_RotateRL();

    //test_AVLTree();
    srand(time(NULL));
    int ret = rand();
    cout << ret << endl;

    return 0;
}