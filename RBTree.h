//
// Created by 93539 on 2023/8/6.
//

#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H

using namespace std;

namespace wyp {
    enum Colour {
        RED,
        BLACK,
    };

    template<class K, class V>
    struct RBTreeNode {
        pair<K, V> _kv;
        RBTreeNode<K, V> *_left;
        RBTreeNode<K, V> *_right;
        RBTreeNode<K, V> *_parent;
        Colour _col;

        RBTreeNode(const pair<K, V> &kv)
                : _kv(kv),
                  _left(nullptr),
                  _right(nullptr),
                  _parent(nullptr),
                  _col(RED) {

        }
    };

    template<class K, class V>
    class RBTree {
        typedef RBTreeNode<K, V> Node;
    public:
        RBTree()
                : _root(nullptr) {

        }

        bool insert(const pair<K, V> &kv) {
            if (_root == nullptr) {
                _root = new Node(kv);
                _root->_col = BLACK;
                return true;
            }
            Node *parent = nullptr;
            Node *cur = _root;
            while (cur != nullptr) {
                if (kv.first < cur->_kv.first) {
                    parent = cur;
                    cur = cur->_left;
                } else if (kv.first > cur->_kv.first) {
                    parent = cur;
                    cur = cur->_right;
                } else {
                    return false;
                }
            }
            cur = new Node(kv);
            cur->_col = RED;
            if (cur->_kv.first < parent->_kv.first) {
                parent->_left = cur;
            } else {
                parent->_right = cur;
            }
            cur->_parent = parent;

            while (parent != nullptr && parent->_col == RED) {
                Node *grandfather = parent->_parent;
                if (parent == grandfather->_left) { //parent为grandfather左孩子
                    Node *uncle = grandfather->_right;
                    if (uncle != nullptr && uncle->_col == RED) { //情况一 cur为红，p为红，g为黑，u存在且为红
                        parent->_col = uncle->_col = BLACK;
                        grandfather->_col = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    } else { // 其他情况
                        if (cur == parent->_left) { //情况二 cur为红，p为红，g为黑，u不存在/u为黑，gpc在同一侧
                            _RotateR(grandfather);
                            parent->_col = BLACK;
                            grandfather->_col = RED;
                        } else { //情况三 cur为红，p为红，g为黑，u不存在/u为黑，gpc不在同一侧
                            _RotateL(parent);
                            _RotateR(grandfather);
                            cur->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        break;
                    }
                } else if (parent == grandfather->_right) { //parent为grandfather右孩子
                    Node *uncle = grandfather->_left;
                    if (uncle != nullptr && uncle->_col == RED) { //情况一 cur为红，p为红，g为黑，u存在且为红
                        parent->_col = uncle->_col = BLACK;
                        grandfather->_col = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    } else { // 其他情况 情况二 或者 情况三
                        if (cur == parent->_right) { //cur为红，p为红，g为黑，u不存在/u为黑，gpc在同一侧
                            _RotateL(grandfather);
                            grandfather->_col = RED;
                            parent->_col = BLACK;
                        } else { //情况三 cur为红，p为红，g为黑，u不存在/u为黑，gpc不在同一侧
                            _RotateR(parent);
                            _RotateL(grandfather);
                            cur->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        break;
                    }
                }
            }
            //根节点变为黑色
            _root->_col = BLACK;
            return true;
        }

        void InOrder() {
            _InOrder(_root);
        }

        bool IsBalance() {
            return _IsBalance();
        }

    private:
        void _RotateR(Node *parent) {
            Node *subL = parent->_left;
            Node *subLR = subL->_right;
            parent->_left = subLR;
            if (subLR) {
                subLR->_parent = parent;
            }
            Node *ppNode = parent->_parent;
            subL->_right = parent;
            parent->_parent = subL;
            if (ppNode == nullptr) {
                _root = subL;
                _root->_parent = nullptr;
            } else {
                if (ppNode->_left == parent) {
                    ppNode->_left = subL;
                } else {
                    ppNode->_right = subL;
                }
                subL->_parent = ppNode;
            }
        }

        void _RotateL(Node *parent) {
            Node *subR = parent->_right;
            Node *subRL = subR->_left;

            parent->_right = subRL;
            if (subRL != nullptr) {
                subRL->_parent = parent;
            }

            Node *ppNode = parent->_parent;
            subR->_left = parent;
            parent->_parent = subR;
            if (ppNode == nullptr) {
                _root = subR;
                _root->_parent = nullptr;
            } else {
                if (ppNode->_left == parent) {
                    ppNode->_left = subR;
                } else {
                    ppNode->_right = subR;
                }
                subR->_parent = ppNode;
            }
        }

        void _InOrder(Node *root) {
            if (root == nullptr) {
                return;
            }
            _InOrder(root->_left);
            cout << root->_kv.first << ":" << root->_kv.second << endl;
            _InOrder(root->_right);
        }

        bool _IsBalance() {
            if (_root == nullptr) {
                return true;
            }
            if (_root->_col != BLACK) {
                return false;
            }
            int ref = 0;
            Node *left = _root;
            while (left) {
                if (left->_col == BLACK) {
                    ++ref;
                }
                left = left->_left;
            }
            return check(_root, 0, ref);
        }

        bool check(Node *root, int blackNum, const int ref) {
            if (root == nullptr) {
                if (blackNum != ref) {
                    cout << "违反规则：本条路径出现黑色节点的数量跟最左路径不相等" << endl;
                    return false;
                }
                return true;
            }
            if (root->_col == RED && root->_parent->_col == RED) {
                cout << "违反规则：出现连续红色节点" << endl;
                return false;
            }
            if (root->_col == BLACK) {
                ++blackNum;
            }
            return check(root->_left, blackNum, ref)
                   && check(root->_right, blackNum, ref);
        }

    private:
        Node *_root;
    };
}
#endif //RBTREE_RBTREE_H


