#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
    private:
        Node<T>* pAnt;
        T value;
    public:
        Node( ):pAnt(nullptr){}
        Node( T _value ):value( _value ),pAnt(nullptr){}
        void setAnt( Node<T>* );
        Node<T>* getAnt();
        void setValue( T );
        T getValue();
};

template<typename T>
void Node<T>::setAnt( Node<T>* nodo )
{
    pAnt = nodo;
}

template<typename T>
Node<T>* Node<T>::getAnt()
{
    return pAnt;
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