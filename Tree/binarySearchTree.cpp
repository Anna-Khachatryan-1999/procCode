#include <iostream>

template <typename T>
class Tree
{
public:
    Tree(){};
    ~Tree(){};

public:
    void insert(T elem);
    T getData();
    //void print();

public:
    struct Node
    {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* getLeft(){ return left;}
    };

private:
    Node* root = nullptr;
};

template <typename T>
void Tree<T>::insert(T elem) {
    if (root == nullptr) {
        root = new Node();
        root->data = elem;
        return;
    }
    Node* tmp = root;
    while (tmp) {
        if (tmp->data < elem) {
            if (tmp->right) {
                tmp = tmp->right;
            } else {
                tmp = new Node;
                tmp->data = elem;
                return;
            }
        } else if (tmp->data > elem) {
            if (tmp->left) {
                tmp = tmp->left;
            } else {
                tmp = new Node;
                tmp->data = elem;
                return;
            }
        } else {
            throw std::invalid_argument("dublicate value");
        }
    }
}

template <typename T>
T Tree<T>::getData()
{
    return root->data;
}



void print(Tree<int>* root)
{
    std::cout << root->getData() << std::endl;
    root = root->left;
    print(root);
    root = root->right;
    print(root);
}

int main()
{
    Tree<int> tree;
    tree.insert(12);
    tree.insert(6);
    tree.insert(4);
    tree.insert(24);
    tree.insert(10);
    print(&tree);
}
