#include <iostream>
#include <stack>

template<class T>
class IsLessDefault {
public:
    bool operator()(const T& left, const T& right) { return left < right; }
};

template <class T, class IsLess = IsLessDefault<T>>
class AvlTree {
public:
    AvlTree() : root(nullptr) {}
    ~AvlTree();
    AvlTree(const AvlTree& other);
    AvlTree& operator=(const AvlTree& other);

    void Add(const T& data);
    int FindPosition(const T& data);
    T FindData(const T& position);
    void Delete(const T& data);
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        size_t height;
        size_t count;
        Node(const T &data) : data(data), left(nullptr), right(nullptr), height(1), count(1) {}  
    };
    Node* root;

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;        
        }
    }

    Node* deleteInternal(Node* node, const T& data) {
        if (!node)
            return nullptr;
        if (IsLess()(node->data, data))
            node->right = deleteInternal(node->right, data);
        else if (IsLess()(data, node->data))
            node->left = deleteInternal(node->left, data);
        else {
            Node* left = node->left;
            Node* right = node->right;
            delete node;
            if (!right)
                return left;
            Node* min = findAndRemoveMin(right);
            min->left = left;            
            return doBalance(min);
        }   
        return doBalance(node);
    }

    Node* findAndRemoveMin(Node* node) {
        if (!node->left) {
           return node;
        }
        std::stack<Node*> stack;
        Node* start = node;
        while (node->left) {
            stack.push(node);
            node = node->left;
        }
        stack.top()->left = node->right;
        Node* top = nullptr;
        while (!stack.empty()) {
            top = stack.top();
            stack.pop();
            bool flag = (top != start);
            top = doBalance(top);
            if (flag) {
                stack.top()->left = top;
            }
        }
        node->right = top;
        return node;
    }

    Node* addInternal(Node* node, const T& data) {
        if (!node)
            return new Node(data);
        if (!IsLess()(data, node->data))
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);    
        return doBalance(node);
    }

    size_t getHeight(Node* node) {
        return node ? node->height : 0;
    }

    size_t getCount(Node* node) {
        return node ? node->count : 0;
    }

    void fixHeight(Node* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void fixCount(Node* node) {
        node->count = getCount(node->left) + getCount(node->right) + 1;
    }

    int getBalance(Node* node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node* rotateLeft(Node* node) {
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixCount(node);
        fixHeight(tmp);
        fixCount(tmp);
        return tmp;
    }

    Node* rotateRight(Node* node) {
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixCount(node);
        fixHeight(tmp);
        fixCount(tmp);
        return tmp;
    }

    Node* doBalance(Node* node) {
        fixHeight(node);
        fixCount(node);
        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
        Node* root;
    }

    Node* copyTree(const Node* src, Node* dest) {
        if (src->left) {
            dest->left = new Node(src->left->data);
            copyTree(src->left, dest->left);
        }
        if (src->right) {
            dest->right = new Node(src->right->data);
            copyTree(src->right, dest->right);
        }
        return dest;
    }
};

template <class T, class IsLess>
AvlTree<T, IsLess>::~AvlTree() {
    destroyTree(root);
}

template <class T, class IsLess>
AvlTree<T, IsLess>::AvlTree(const AvlTree& other) {
    root = nullptr;
    if (other.root) {
        root = new Node(other.root->data);
        root = copyTree(other.root, root);
    }
}

template <class T, class IsLess>
AvlTree<T, IsLess>& AvlTree<T, IsLess>::operator=(const AvlTree& other) {
    if (this != &other) {
        destroyTree(root);
        root = new Node(other.root->data);
        root = copyTree(other.root, root);
    }
    return *this;
}

template <class T, class IsLess>  
void AvlTree<T, IsLess>::Add(const T& data) {
    root = addInternal(root, data);
}

template <class T, class IsLess>   
int AvlTree<T, IsLess>::FindPosition(const T& data) {
    Node* tmp = root;
    int count = 0;
    while (tmp) {
        if (tmp->data == data)
            return count + getCount(tmp->right);
        else if (IsLess()(tmp->data, data))
            tmp = tmp->right;
        else {
            count += getCount(tmp->right) + 1;
            tmp = tmp->left;
        }
    }
}

template <class T, class IsLess>   
T AvlTree<T, IsLess>::FindData(const T& position) {
    Node* tmp = root;
    int count = 0;
    while (tmp) {
        if (count + getCount(tmp->right) == position)
            return tmp->data;
        else if (IsLess()(position, count + getCount(tmp->right)))
            tmp = tmp->right;
        else {
            count += getCount(tmp->right) + 1;
            tmp = tmp->left;
        }
    }
}

template <class T, class IsLess>
void AvlTree<T, IsLess>::Delete(const T& data) {
    root = deleteInternal(root, data);
}

int main() {
    AvlTree<int> tree;
    int n, data;
    char operation = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> operation >> data;
        switch (operation)
        {
        case '1':
            tree.Add(data);
            std::cout << tree.FindPosition(data) << std::endl;
            break;
        case '2':
            data = tree.FindData(data);
            tree.Delete(data);
            break;
        }
    }
    return 0;
}