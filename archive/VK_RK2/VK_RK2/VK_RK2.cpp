#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        if (!root) return;

        std::stack<Node*> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty()) {
            Node* node = nodeStack.top();
            nodeStack.pop();
            if (node->Left)
                nodeStack.push(node->Left);
            if (node->Right)
                nodeStack.push(node->Right);

            delete node;
        }
    }

    void Add(const int& key) {
        Node* curr = root;
        Node* newNode = new Node(key);
        if (!curr) {
            root = newNode;
            return;
        }
        while (true) {
            if (key < curr->Key)
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

    int minDistance() const {
        int min = 999999;
        int k = 0;
        bool haveChildrens;
        struct Two{
            Node* node;
            int k;
        };
        std::stack<Two> nodeStack;
        Two two{ root, 0 };
        nodeStack.push(two);
        while (!nodeStack.empty()) {
            haveChildrens = false;
            Two curr = nodeStack.top();
            Node* node = curr.node;
            k = curr.k;
            nodeStack.pop();
            ++k;

            if (node->Right) {
                Two two{ node->Right , k };
                nodeStack.push(two);
                haveChildrens = true;
            }
            if (node->Left) {
                Two two{ node->Left , k };
                nodeStack.push(two);
                haveChildrens = true;
            }
            if (!haveChildrens && k < min) {
                min = k;
            }
        }
        return min;
    }

private:
    struct Node {
        int Key;
        Node* Left;
        Node* Right;
        Node(const int& key) : Key(key), Left(nullptr), Right(nullptr) {}
    };
    Node* root;
};

int main()
{
    BinaryTree tree;
    std::string str;
    std::getline(std::cin, str);
    std::istringstream ss(str);
    int key;
    while (ss >> key) {
        tree.Add(key);
    }
    std::cout << tree.minDistance();
}
