#include <iostream>
using namespace std;
long long TC, N;
long long S[200001];
long long T[200001];
long long T2[200001];
long long seed = 1987152371;
long long mod = 1000000007;
long long salt = 101;
long long ans;
const long long NONE = -1987654321;
int rnd() {
    seed *= seed;
    seed %= mod;
    seed += salt;
    seed %= mod;
    return (int)seed;
}
inline long long max(long long a, long long b) {
    return a < b ? b : a;
}
 
 
struct Node {
    long long interval;
    long long minArrivalTime;
    int size, priority;
    long long lazyForInterval;
    Node *lazyNode;
    Node *left, *right;
    Node(long long _interval, long long _minTime) : interval(_interval), minArrivalTime(_minTime), size(1), priority(rnd()),
        lazyForInterval(0), lazyNode(nullptr), left(nullptr), right(nullptr) {}
    void setLeft(Node *newNode) {
        left = newNode;
        calcSize();
    }
    void setRight(Node* newNode) {
        right = newNode;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) {
            size += left->size;
        }
        if (right) {
            size += right->size;
        }
    }
};
 
struct NodePair {
    Node *left, *right;
};
 
void updateNode(Node* root) {
    if (root == nullptr) {
        return;
    }
    if (root->right) {
        root->right->lazyForInterval += root->lazyForInterval;
        if (root->lazyNode != nullptr) {
            if (root->right->lazyNode == nullptr) {
                root->right->lazyNode = root->lazyNode;
            } else {
                if (root->right->interval - root->right->lazyNode->interval + root->right->lazyNode->minArrivalTime < root->right->interval - root->lazyNode->interval + root->lazyNode->minArrivalTime) {
                    root->right->lazyNode = root->lazyNode;
                }
            }
        }
    }
    if (root->left) {
        root->left->lazyForInterval += root->lazyForInterval;
        if (root->lazyNode != nullptr) {
            if (root->left->lazyNode == nullptr) {
                root->left->lazyNode = root->lazyNode;
            } else {
                if (root->left->interval - root->left->lazyNode->interval + root->left->lazyNode->minArrivalTime < root->left->interval - root->lazyNode->interval + root->lazyNode->minArrivalTime) {
                    root->left->lazyNode = root->lazyNode;
                }
            }
        }
    }
    root->interval += root->lazyForInterval;
    root->lazyForInterval = 0;
    if (root->lazyNode != nullptr) {
        root->minArrivalTime = max(root->minArrivalTime, root->interval - root->lazyNode->interval + root->lazyNode->minArrivalTime);
        root->lazyNode = nullptr;
    }
}
 
NodePair split(Node* node, long long baseKey) {
    updateNode(node);
    NodePair ret;
    if (node == nullptr) {
        ret.left = nullptr;
        ret.right = nullptr;
        return ret;
    } else {
        if (node->interval < baseKey) {
            NodePair splited = split(node->right, baseKey);
            node->setRight(splited.left);
            ret.left = node;
            ret.right = splited.right;
            return ret;
        } else {
            NodePair splited = split(node->left, baseKey);
            node->setLeft(splited.right);
            ret.left = splited.left;
            ret.right = node;
            return ret;
        }
    }
}
Node* insert(Node* root, Node* node) {
    updateNode(root);
    if (root == nullptr) {
        return node;
    } else {
        if (root->priority < node->priority) {
            NodePair splited = split(root, node->interval);
            node->setLeft(splited.left);
            node->setRight(splited.right);
            return node;
        } else {
            if (root->interval < node->interval) {
                root->setRight(insert(root->right, node));
                return root;
            } else {
                root->setLeft(insert(root->left, node));
                return root;
            }
        }
    }
}
 
Node* merge(Node* leftSide, Node* rightSide) {
    updateNode(leftSide);
    updateNode(rightSide);
    if (leftSide == nullptr) {
        return rightSide;
    }
    if (rightSide == nullptr) {
        return leftSide;
    }
    if (leftSide->priority < rightSide->priority) {
        rightSide->setLeft(merge(leftSide, rightSide->left));
        return rightSide;
    } else {
        leftSide->setRight(merge(leftSide->right, rightSide));
        return leftSide;
    }
}
 
Node* erase(Node* root, long long baseKey) {
    updateNode(root);
    if (root == nullptr) {
        return nullptr;
    } else {
        if (root->interval == baseKey) {
            Node* newNode = merge(root->left, root->right);
            return newNode;
        } else {
            if (root->interval < baseKey) {
                root->setRight(erase(root->right, baseKey));
                return root;
            } else {
                root->setLeft(erase(root->left, baseKey));
                return root;
            }
        }
    }
}
 
Node* findNode(Node* root, long long baseKey) {
    updateNode(root);
    if (root == nullptr) {
        return nullptr;
    } else {
        if (root->interval == baseKey) {
            return root;
        } else {
            if (root->interval < baseKey) {
                return findNode(root->right, baseKey);
            } else {
                return findNode(root->left, baseKey);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> TC;
    for (int test = 1; test <= TC; ++test) {
        cin >> N;
        for (long long i = 1; i <= N; ++i) {
            cin >> S[i] >> T[i];
            T2[i] = T[i];
        }
        Node *BST = nullptr;
        ans = 0;
        for (long long i = 1; i <= N; ++i) {
            BST = insert(BST, new Node(i, i));
        }
        Node* tmpNode;
        Node* tmpNode3;
        for (long long i = N; 1 <= i; --i) {
            tmpNode = findNode(BST, S[i]);
            tmpNode3 = new Node(tmpNode->interval - 1, tmpNode->minArrivalTime);
            ans = max(ans, tmpNode->minArrivalTime + T[i]);
            BST = erase(BST, tmpNode->interval);
            tmpNode->minArrivalTime += T[i] + 1;
            if (BST != nullptr) {
                tmpNode->priority = BST->priority + 1;
            }
            BST = insert(BST, tmpNode);
            if (BST->right) {
                updateNode(BST->right);
                BST->right->lazyNode = BST;
            }
            if (BST->left) {
                BST->left->lazyForInterval += -1;
                tmpNode->priority = BST->left->priority + 1;
            }
            BST = insert(BST, tmpNode3);
        }
        cout << "#" << test << " " << ans << "\n";
    }
}
