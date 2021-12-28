#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
    private:
        Node<T>* next;
        Node<T>* prev;
        T value;
    public:
        Node( ):next(nullptr),prev(nullptr){}
        Node( T _value ):value( _value ),next(nullptr),prev(nullptr){}
        void setNext( Node<T>* );
        Node<T>* getNext();
        void setPrev( Node<T>* );
        Node<T>* getPrev();
        void setValue( T );
        T getValue();
};

template<typename T>
void Node<T>::setNext( Node<T>* nodo )
{
    next = nodo;
}

template<typename T>
Node<T>* Node<T>::getNext()
{
    return next;
}

template<typename T>
void Node<T>::setPrev( Node<T>* nodo )
{
    prev = nodo;
}

template<typename T>
Node<T>* Node<T>::getPrev()
{
    return prev;
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

#endif