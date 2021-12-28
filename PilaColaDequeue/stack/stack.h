#ifndef STACK_H
#define STACK_H
#include "node.h"
#include <iostream>

template<typename T>
class Stack
{
    private:
        Node<T>* pEnd;
        int _size;
    public:
        Stack():pEnd(nullptr),_size(0){}
        ~Stack();
        int size(){ return _size; }
        bool isEmpty();
        void push( T );
        void pop();
        T top();
        void print();
};

template<typename T>
Stack<T>::~Stack()
{
    while(!isEmpty()) pop();
    std::cout<<"\npila destruida\n";
}

template<typename T>
bool Stack<T>::isEmpty()
{
    return (pEnd==nullptr);
}

template<typename T>
void Stack<T>::push( T value )
{
    Node<T>* pNuevo = new Node<T>(value);
    if(isEmpty()) pEnd = pNuevo;
    else
    {
        pNuevo->setAnt( pEnd );
        pEnd = pNuevo;
    }
    _size++;
}

template<typename T>
void Stack<T>::pop()
{
    if(!isEmpty())
    {
        Node<T>* aux = pEnd->getAnt();
        delete pEnd;
        pEnd = aux;
        _size--;
    }
}

template<typename T>
T Stack<T>::top()
{
    return pEnd->getValue();
}

template<typename T>
void Stack<T>::print()
{
    Node<T>* aux=pEnd;
    while(pEnd)
    {
        std::cout<<pEnd->getValue()<<' ';
        pEnd = pEnd->getAnt();
    }
    std::cout<<'\n';
}

#endif