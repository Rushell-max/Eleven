#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include <iostream>

template<typename T>
class Queue
{
    private:
        Node<T>* pHead;
        Node<T>* pTail;
        int _size;
    public:
        Queue():pHead(nullptr),pTail(nullptr),_size(0){}
        ~Queue();
        bool isEmpty();
        void enqueue( T );
        void dequeue();
        T value();
        void print();
};

template<typename T>
Queue<T>::~Queue()
{
    while(!isEmpty()) dequeue();           
}

template<typename T>
bool Queue<T>::isEmpty()
{
    return (pHead==nullptr);
}

template<typename T>
void Queue<T>::enqueue( T value )
{
    Node<T>* pNuevo = new Node<T>(value);
    if(isEmpty()) 
    {
        pHead = pNuevo;
        pTail = pNuevo;
    }
    else
    {
        pTail->setAnt( pNuevo );
        pTail = pNuevo;
    }
    _size++;
}

template<typename T>
void Queue<T>::dequeue()
{
    if(!isEmpty())
    {
        Node<T>* aux = pHead->getAnt();
        delete pHead;
        pHead = aux;
        _size--;
    }
}

template<typename T>
T Queue<T>::value()
{
    return pHead->getValue();
}

template<typename T>
void Queue<T>::print()
{
    Node<T>* tmp = pHead;
    while(tmp)
    {
        std::cout<<tmp->getValue()<<' ';
        tmp = tmp->getAnt();
    }
    std::cout<<'\n';
}

#endif