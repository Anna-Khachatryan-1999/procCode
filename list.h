class List
{
private:
    struct Node
    {
        int data;
        Node* next;
    };

public:
    void push_back (const int&);
    void push_front (const int&);
    void insert (const int&, int);
    void print();
private:
    Node* head = nullptr;
};

#include "list.hpp"
