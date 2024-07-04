#include <iostream>
#include <stack>

template<class T, class Compare>
class BinaryTree {
public:
    BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);

    void Add(const T& key);
    bool Has(const T& key) const;
    void Delete(const T& key);
    void Dfs(void (*visit)(const T& key)) const;

private:
    struct Node {
        T Key;
        Node* Left;
        Node* Right;
        Node(const T& key) : Key(key), Left(nullptr), Right(nullptr) {}
    };
    Compare cmp;
    Node* root;

    void deleteNode(Node* node, Node* prev);
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
    if (!root) return;

    std::stack<Node*> nodeStack;
    nodeStack.push(root);
    while(!nodeStack.empty()) {
        Node* node = nodeStack.top();
        nodeStack.pop();
        if (node->Left)
            nodeStack.push(node->Left);
        if (node->Right)
            nodeStack.push(node->Right);

        delete node;
    }
}

template<class T, class Compare>
BinaryTree<T, Compare>::BinaryTree(const BinaryTree& other) {
    if (!other.root) return;

    std::stack<Node*> nodeStack;
    nodeStack.push(other.root);
    while(!nodeStack.empty()) {
        Node* node = nodeStack.top();
        nodeStack.pop();
        Add(node->Key);
        if (node->Right)
            nodeStack.push(node->Right);
        if (node->Left)
            nodeStack.push(node->Left);
    }
}

template<class T, class Compare>
BinaryTree<T, Compare>& BinaryTree<T, Compare>::operator=(const BinaryTree& other) {
    if (this != &other) {
        if (root) {
            std::stack<Node*> nodeStack;
            nodeStack.push(root);
            while(!nodeStack.empty()) {
                Node* node = nodeStack.top();
                nodeStack.pop();
                if (node->Left)
                    nodeStack.push(node->Left);
                if (node->Right)
                    nodeStack.push(node->Right);

                delete node;
            }
        }
        root = other.root;
        cmp = other.cmp;
        if (!root) return *this;
        
        std::stack<Node*> nodeStack;
        nodeStack.push(other.root);
        while(!nodeStack.empty()) {
            Node* node = nodeStack.top();
            nodeStack.pop();
            Add(node->Key);
            if (node->Right)
                nodeStack.push(node->Right);
            if (node->Left)
                nodeStack.push(node->Left);
        }
    }
    return *this;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T& key) {
    Node* curr = root;
    Node* newNode = new Node(key);
    if (!curr) {
        root = newNode;
        return;
    }
    while(true) {
        if (Compare()(key, curr->Key))
            if (curr->Left)
                curr = curr->Left;
            else {
                curr->Left = newNode;
                return;
            }
        else
            if (curr->Right)
                curr = curr->Right;
            else {
                curr->Right = newNode;
                return;
            }
    }
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T& key) const {
    Node* curr = root;
    while(curr) {
        if (Compare()(key, curr->Key))
            curr = curr->Left;
        else {
            if (curr->Key == key)
                return true;
            curr = curr->Right;
        }
    }
    return false;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Delete(const T& key) {
    Node* curr = root;
    // prev для случая, когда удаляется ветвь
    Node* prev = nullptr;
    while(curr) {
        if (Compare()(key, curr->Key)) {
            prev = curr;
            curr = curr->Left;
        }
        else {
            if (curr->Key == key)
                deleteNode(curr, prev);
            prev = curr;
            curr = curr->Right;
        }
    }
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Dfs(void (*visit)(const T& key)) const {
    if (!root) return;

    std::stack<Node*> nodeStack;
    nodeStack.push(root);
    while(!nodeStack.empty()) {
        Node* node = nodeStack.top();
        nodeStack.pop();
        visit(node->Key);
        if (node->Right)
            nodeStack.push(node->Right);
        if (node->Left)
            nodeStack.push(node->Left);
    }
}

template<class T, class Compare>
void BinaryTree<T, Compare>::deleteNode(Node* node, Node* prev) {
    //нет детей
    if (!node->Left && !node->Right) {
        if (prev->Left == node)
            prev->Left = nullptr;
        else
            prev->Right = nullptr;
        delete node;
        return;
    }

    // есть только правая ветвь
    if (!node->Left) {
        Node* right = node->Right;
        node->Key = right->Key;
        node->Right = right->Right;
        node->Left = right->Left;
        delete right;
        return;
    }

    //есть правая и левая ветвь
    //поиск максимального значения в левой ветви
    Node* maxLeft = node->Right;
    while(maxLeft->Right)
        maxLeft = maxLeft->Right;
    
    node->Key = maxLeft->Key;
    node->Left = maxLeft->Right;
    delete maxLeft;    
}

struct IntCmp {
    bool operator()(const int l, const int r) { return l < r; }
};

int main() {
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);
    int n, elem;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> elem;
        tree.Add(elem);
    }
    tree.Dfs([](const int& key) { std::cout << key << ' '; });
}