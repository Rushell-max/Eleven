#include <iostream>

template <typename T>
class Node
{
    private:
        T value;
        Node<T> *next;

    public:
        Node(T);
        void setValue(T);
        T getValue();
        void setNext(Node<T>*);
        Node<T>* getNext();
};

template <typename T>
Node<T>::Node(T value)
{
    this->value = value;
    next = nullptr;
}

template<typename T>
void Node<T>::setValue( T value )
{
    this->value = value;
}

template<typename T>
T Node<T>::getValue()
{
    return value;
}

template<typename T>
void Node<T>::setNext( Node<T>* node )
{   
    next = node;
}

template<typename T>
Node<T>* Node<T>::getNext()
{
    return next;
}