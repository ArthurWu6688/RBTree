//
// Created by 93539 on 2023/8/3.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
using namespace std;

namespace wyp {
    template<class K, class V>
    struct AVLTreeNode {
        pair<K, V> _kv;
        int _bf;
        AVLTreeNode *_left;
        AVLTreeNode *_right;
        AVLTreeNode *_parent;

        AVLTreeNode(const pair<K, V> &kv)
                : _kv(kv), _bf(0), _left(nullptr), _right(nullptr), _parent(nullptr) {

        }
    };

    template<class K, class V>
    class AVLTree {
        typedef AVLTreeNode<K, V> Node;
    public:
        AVLTree()
                : _root(nullptr) {

        }

        bool insert(const pair<K, V> &kv) {
            if (_root == nullptr) {
                _root = new Node(kv);
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
            cur = new AVLTreeNode<K, V>(kv);
            if (kv.first < parent->_kv.first) {
                parent->_left = cur;
            } else {
                parent->_right = cur;
            }
            cur->_parent = parent;
            ////更新平衡因子
            while (parent) {
                if (cur == parent->_left) {
                    --parent->_bf;
                } else {
                    ++parent->_bf;
                }

                if (parent->_bf == 0) {
                    break;
                } else if (parent->_bf == 1 || parent->_bf == -1) {
                    cur = parent;
                    parent = parent->_parent;
                } else if (parent->_bf == 2 || parent->_bf == -2) {
                    if (cur->_bf == -1 && parent->_bf == -2) {
                        _RotateR(parent);
                    } else if (cur->_bf == 1 && parent->_bf == 2) {
                        _RotateL(parent);
                    } else if (cur->_bf == 1 && parent->_bf == -2) {
                        _RotateLR(parent);
                    } else if (cur->_bf == -1 && parent->_bf == 2) {
                        _RotateRL(parent);
                    }
                    break;
                } else {
                    assert(false);
                }
            }
            return true;
        }

        void InOrder() {
            _InOrder(_root);
        }

        int Height() {
            return _Height(_root);
        }

        bool InBalance() {
            return _InBalance(_root);
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
            subL->_bf = parent->_bf = 0;
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
            parent->_bf = subR->_bf = 0;
        }

        void _RotateLR(Node *parent) {
            Node *subL = parent->_left;
            Node *subLR = subL->_right;
            int bf = subLR->_bf;

            _RotateL(subL);
            _RotateR(parent);

            if (bf == -1) {
                parent->_bf = 1;
                subL->_bf = 0;
                subLR->_bf = 0;
            } else if (bf == 1) {
                parent->_bf = 0;
                subL->_bf = -1;
                subLR->_bf = 0;
            } else if (bf == 0) {
                parent->_bf = subL->_bf = subLR->_bf = 0;
            } else {
                assert(false);
            }
        }

        void _RotateRL(Node *parent) {
            Node *subR = parent->_right;
            Node *subRL = subR->_left;
            int bf = subRL->_bf;

            _RotateR(subR);
            _RotateL(parent);

            if (bf == -1) {
                parent->_bf = 0;
                subR->_bf = 1;
                subRL->_bf = 0;
            } else if (bf == 1) {
                parent->_bf = -1;
                subR->_bf = 0;
                subRL->_bf = 0;
            } else if (bf == 0) {
                parent->_bf = subR->_bf = subRL->_bf = 0;
            } else {
                assert(false);
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

        int _Height(Node *root) {
            if (root == nullptr) {
                return 0;
            }
            int leftHeight = _Height(root->_left);
            int rightHeight = _Height(root->_right);
            return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
        }

        bool _InBalance(Node *root) {
            if (root == nullptr) {
                return true;
            }

            int leftHeight = _Height(root->_left);
            int rightHeight = _Height(root->_right);

            if (rightHeight - leftHeight != root->_bf) {
                cout << root->_kv.first << "平衡因子异常" << endl;
                return false;
            }

            return abs(leftHeight - rightHeight) < 2
                   && _InBalance(root->_left)
                   && _InBalance(root->_right);
        }

    private:
        Node *_root;
    };
}

#endif //AVLTREE_AVLTREE_H