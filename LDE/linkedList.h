#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.h"
#include <iostream>

template<typename T>
class LinkedList
{
    private:
        Node<T>* pNill;
        int _size;
    public:
        LinkedList();                                   //const. por defecto
        LinkedList( const LinkedList<T>& );             //const. copia
        LinkedList( LinkedList<T>&& );                  //const. mov
        ~LinkedList();                                  //dest.
        int size(){ return _size; }                 
        void push_back( const T );                      //inserta al final
        void push_front( const T );                     //inserta al inicio
        LinkedList<T>& operator=( const LinkedList<T>& );   //operador asignacion copia
        LinkedList<T>& operator=( LinkedList<T>&& );        //operador asignacion mov

        //tarea
        void insert( const T );                         //inserta por valor
        bool find( const T ) const;                     //busca por valor
        void remove( const T );                         //elimina por valor
        void print() const;                             //imprime inicio a fin
        void reversePrint() const;                      //imprime fin a inicio
        void Union( const LinkedList<T>& );             //union de los listas
};

template<typename T>
LinkedList<T>::LinkedList()
{
    pNill = new Node<T>();          // inicializa pNill
    pNill->setNext(pNill);          // next apunta a pNill
    pNill->setPrev(pNill);          // prev apunta a pNill
    _size = 0;
}

template<typename T>
LinkedList<T>::LinkedList( const LinkedList<T>& L )
{
    _size = 0;
    pNill = new Node<T>();                  // inicializa pNill
    pNill->setNext(pNill);                  // next apunta a pNill
    pNill->setPrev(pNill);                  // prev apunta a pNill
    Node<T>*tmp = L.pNill->getNext();
    while( tmp != L.pNill )                 // hasta llegar al final de L
    {
        push_back( tmp->getValue() );       // inserta elemento
        tmp = tmp->getNext();               // avanza al sig
    }
}

template<typename T>
LinkedList<T>::LinkedList( LinkedList<T>&& L )
{
    _size = 0;
    pNill = new Node<T>();                  // inicializa pNill
    pNill->setNext(pNill);                  // next apunta a pNill
    pNill->setPrev(pNill);                  // prev apunta a pNill
    std::swap( _size, L._size );            // intercambia tamaños
    std::swap( pNill, L.pNill );            // intercambia punteros
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* tmp = pNill->getNext();        // tmp avanza por la lista
    Node<T>* aux = pNill->getNext();        // aux guarda el actual
    while( tmp != pNill )                   // mientras no se llegue al final
    {
        tmp = tmp->getNext();               // tmp avanza
        delete aux;                         // borra actual
        aux = tmp;                          // actual avanza
    }
    delete pNill;                           // borra pNill
}

template<typename T>
void LinkedList<T>::push_back( const T value )
{
    Node<T>* nodo = new Node<T>(value);     // inicializa nodo
    nodo->setPrev( pNill->getPrev() );      // nodo->prev apunta a pNill->prev
    nodo->setNext( pNill );                 // nodo->next apunta pNill
    pNill->getPrev()->setNext( nodo );      // pNill->prev->next apunta nodo
    pNill->setPrev( nodo );                 // pNill->prev apunta anodo
    _size++;
}

template<typename T>
void LinkedList<T>::push_front( const T value )
{
    Node<T>* nodo = new Node<T>(value);     // inicializa nodo
    nodo->setNext( pNill->getNext() );      // nodo->next apunta a pNill->next
    nodo->setPrev( pNill );                 // nodo->prev apunta pNill
    pNill->getNext()->setPrev( nodo );      // pNill->next->prev apunta nodo
    pNill->setNext( nodo );                 // pNill->next apunta anodo
    _size++;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=( const LinkedList<T>& L )
{
    if ( this != &L )                           // si no es el mismo objeto
    {
        Node<T>*tmp = L.pNill->getNext();       // tmp avanza por L
        while( tmp != L.pNill )                 // mientras no se llegue al final de L
        {
            push_back( tmp->getValue() );       // inserta al final
            tmp = tmp->getNext();               // tmp avanza
        }
    }
    return *this;                               // devuelve una referencia 
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=( LinkedList<T>&& L )
{
    if ( this != * L )                          // si no es el mismo objeto
    {
        std::swap(_size,L._size);               // intercambia tamaños
        std::swap(pNill,L.pNill);               // intercambia punteros
    }
    return *this;                               // devuelve una referencia 
}

// tarea
template<typename T>
void LinkedList<T>::insert( const T value )
{
    Node<T>* nodo = new Node<T>(value);     // inicializa nodo
    nodo->setNext( pNill->getNext() );      // nodo->next apunta a pNill->next
    nodo->setPrev( pNill );                 // nodo->prev apunta pNill
    pNill->getNext()->setPrev( nodo );      // pNill->next->prev apunta nodo
    pNill->setNext( nodo );                 // pNill->next apunta anodo
    _size++;
}

template<typename T>
bool LinkedList<T>::find( const T value ) const
{
    Node<T>* tmp = pNill->getNext();                    // tmp avanza por la lista
    while( tmp != pNill )                               // mientras no se llegue al final
    {
        if( tmp->getValue() == value ) return true;     // true si encuentra el valor 
        tmp = tmp->getNext();                           // avanza
    }   
    return false;                                       // false si no encuentra
}

template<typename T>
void LinkedList<T>::remove( const T value )
{
    Node<T>* tmp = pNill->getNext();                    // tmp avanza por la lista
    while( tmp!=pNill )                                 // mientras no se llegue al final
    {
        if ( tmp->getValue() == value )                 // si concuerda el valor
        {   
            tmp->getPrev()->setNext( tmp->getNext() );  // tmp->prev->next apunta a tmp->next
            tmp->getNext()->setPrev( tmp->getPrev() );  // tmp->next->prev apunta a tmp->prev
            _size--;
            return;                                     // termina, solo elimina una ocurrencia
        }
        tmp = tmp->getNext();                           // avanza
    }
}

template<typename T>
void LinkedList<T>::print() const           
{   
    Node<T>* tmp = pNill->getNext();                    // tmp avanza por la lista
    while( tmp != pNill )                               // mientras no se llegue al final
    {
        std::cout<<tmp->getValue()<<' ';                // muestra dato
        tmp = tmp->getNext();                           // avanza
    }
    std::cout<<'\n';
}

template<typename T>
void LinkedList<T>::reversePrint() const
{
    Node<T>* tmp = pNill->getPrev();                    // tmp retrocede por la lista
    while( tmp != pNill )                               // mientras no se llegue al comienzo
    {
        std::cout<<tmp->getValue()<<' ';                // muestra dato
        tmp = tmp->getPrev();                           // retrocede
    }
    std::cout<<'\n';
}

template<typename T>
void LinkedList<T>::Union( const LinkedList<T>& L )
{
    Node<T>* tmp = L.pNill->getNext();                                  // tmp avanza por la lista
    while( tmp != L.pNill )                                             // mientras no se llegue al final
    {
        if ( !find( tmp->getValue() ) ) push_back( tmp->getValue() );   // busca dato en la lista, si no encuentra, inserta al final
        tmp = tmp->getNext();                                           // avanza
    }
}

#endif 