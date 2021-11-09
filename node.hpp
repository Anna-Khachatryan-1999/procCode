#include "node.h"

void Node::setData(int data)
{
    m_data = data;
}

void Node::setNext(Node* node)
{
    m_next = node;
}

int Node::data() const
{
    return m_data;
}

Node* Node::next() const
{
    return this->m_next;
}

