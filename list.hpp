#include <iostream>

void List::push_back (const int& data)
{
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;
    if (head == nullptr) {
        head = node;
        return;
    }

    Node* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = node;
}

void List::push_front (const int& data)
{
    Node* node = new Node();
    node->data = data;
    node->next = head;
    head = node;
}


void List::insert (const int& data, int pos)
{
    Node* node = new Node();
    node->data = data;

    if (!head) {
        head = node;
        node = nullptr;
        return;
    }

    if (!head->next) {
        head->next = node;
        node = nullptr;
        return;
    }

    Node* cur = head;
    while (pos != 0) {
        cur = cur->next;
        --pos;
    }
    node->next = cur->next;
    cur->next = node;
}

void List::print()
{
    Node* cur = head;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}
