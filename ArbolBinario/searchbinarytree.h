#ifndef SEARCHBINARYTREE_H
#define SEARCHBINARYTREE_H
#include "nodo.h"
#include <stack>
#include <iostream>
#include <fstream>

template <class T>
class SearchBinaryTree
{
	private:
		Nodo<T> *m_pRoot;
        int _size;
        void insert( T d , Nodo<T>*& , Nodo<T> * );     // funcion recursiva para insertar
        bool find( T d , Nodo<T> *);                    // funcion recursiva para buscar
        void preOrder( Nodo<T> * , std::string& );      // funcion recursiva preorden
        void inOrder( Nodo<T> * , std::string& );       // funcion recursiva inorden
        void postOrder( Nodo<T> * , std::string& );     // funcion recursiva postorden
        void graficar( Nodo<T>* , std::ofstream& );     // funcion recursiva para graficar
	public:
        // constructor, construye arbol vacio
		SearchBinaryTree() : m_pRoot(0),_size(0){}
        // destructor
        ~SearchBinaryTree();        
        int size(){ return _size; }
        // inserta un elemento
		void insert( T );                           
        // elimina un nodo
        bool remove( T );
        void guardarPila( Nodo<T> * , std::stack<Nodo<T>*> & );     // funcion auxiliar
        // busca un elemento
		bool find( T );
        // devuelve string con los elementos del arbol en preorden
		std::string preOrder();
        // devuelve string con los elementos del arbol en inorden
		std::string inOrder();
        // devuelve string con los elementos del arbol en postorden
        std::string postOrder();
        // vacia el arbol
        void clear();
        // grafica el arbol	
        void graficar( std::string );	
};

template<typename T>
SearchBinaryTree<T>::~SearchBinaryTree()
{
    m_pRoot->autoDestruir( m_pRoot );
    std::cout<<"\nse destruyo correctamente\n";
}

template<typename T>
void SearchBinaryTree<T>::insert(T d)                            
{
    insert( d , m_pRoot , nullptr );
}

template<typename T>
void SearchBinaryTree<T>::insert( T d, Nodo<T> *&p , Nodo<T> *padre )
{
    if (!p)         // si es null
    {
        p = new Nodo<T>(d);
        p->m_pSon[2] = padre;
        _size++;
        return;
    }
    if (p->m_Dato == d) // no inserta repetidos
        return;
    insert( d , p->m_pSon[p->m_Dato < d] , p );
}

template<typename T>
void SearchBinaryTree<T>::guardarPila( Nodo<T> *p, std::stack<Nodo<T> *> &pila )        // 45 40 56 70
{
    if (!p)
        return;
    pila.push(p);        
    guardarPila(p->m_pSon[0], pila);
    guardarPila(p->m_pSon[1], pila);
}

template<typename T>
bool SearchBinaryTree<T>::remove( T d )
{
    if (find(d))
    {
        Nodo<T> *q = m_pRoot;
        while ( q->m_Dato != d ) 
            q = q->m_pSon[q->m_Dato < d];
        std::stack<Nodo<T> *> pila;
        Nodo<T> *q2 = q;
        if( q == m_pRoot ) m_pRoot = nullptr;
        else
            q->m_pSon[2]->m_pSon[ q->m_pSon[2]->m_Dato < d ] = nullptr;
        guardarPila(q2, pila);
        _size = _size - pila.size(); 
        while (pila.size())
        {
            Nodo<T> *aux = pila.top();
            if (pila.size() != 1)
                insert(aux->m_Dato);
            pila.pop();
            delete aux;
        }
        return true;
    }
    return false;
}

template<typename T>
bool SearchBinaryTree<T>::find(T d, Nodo<T> *p)
{
    if (!p)
        return false;
    if (p->m_Dato == d)
    {
        return true;
    }
    return find( d , p->m_pSon[p->m_Dato < d] );
}

template<typename T>
bool SearchBinaryTree<T>::find( T d )
{
    return find( d, m_pRoot );
}

template<typename T>
std::string SearchBinaryTree<T>::preOrder()
{
    std::string cadena;
    preOrder( m_pRoot , cadena );
    return cadena;
}

template<typename T>
void SearchBinaryTree<T>::preOrder( Nodo<T> *r , std::string& s )
{
    if (!r)
        return;
    s += std::to_string(r->m_Dato) + ",";
    preOrder( r->m_pSon[0] , s );
    preOrder( r->m_pSon[1] , s );
}

template<typename T>
std::string SearchBinaryTree<T>::inOrder()
{
    std::string cadena;
    inOrder( m_pRoot,cadena );
    return cadena;
}

template<typename T>
void SearchBinaryTree<T>::inOrder( Nodo<T> *r , std::string& s)
{
    if (!r)
        return;
    inOrder( r->m_pSon[0] , s );
    s += std::to_string(r->m_Dato) + ",";
    inOrder( r->m_pSon[1] , s );
}

template<typename T>
std::string SearchBinaryTree<T>::postOrder()
{
    std::string cadena;
    postOrder( m_pRoot,cadena );
    return cadena;
}

template<typename T>
void SearchBinaryTree<T>::postOrder( Nodo<T> *r , std::string& s)
{
    if (!r)
        return;
    postOrder( r->m_pSon[0] , s );
    postOrder( r->m_pSon[1] , s );
    s += std::to_string(r->m_Dato) + ",";
}

template<typename T>
void SearchBinaryTree<T>::clear()
{
    m_pRoot->autoDestruir( m_pRoot );
    m_pRoot = nullptr;
    _size = 0;
}

template<typename T>
void SearchBinaryTree<T>::graficar( std::string dir )
{
    std::ofstream f;
    f.open(dir);
    f<<"graph A {\n";
    graficar( m_pRoot , f );
    f<<"}\n";
    f.close();
}

template<typename T>
void SearchBinaryTree<T>::graficar( Nodo<T>* p , std::ofstream& f )
{
    if( !p ) return;                    // si es null termina
    if( p->m_pSon[2] != nullptr )       // si el padre existe
        f<<p->m_pSon[2]->m_Dato<<" -- "<<p->m_Dato<<";\n";
    graficar( p->m_pSon[0] , f );
    graficar( p->m_pSon[1] , f );
}

#endif