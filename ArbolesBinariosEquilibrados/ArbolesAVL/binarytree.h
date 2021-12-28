#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "nodo.h"
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>

template<typename T>
class Binary_Tree
{
    private:
        Nodo<T>* pRoot;
        int _size;

        void inOrder( Nodo<T>*& );
        void preOrder( Nodo<T>*& );
        void postOrder( Nodo<T>*& );
        void print( Nodo<T>* );
        void RD( Nodo<T>*& , bool );
        void RS( Nodo<T>*& , bool );
        void guardarCola( Nodo<T> * , std::stack<Nodo<T>*> & );     // funcion auxiliar
        bool find( T d , Nodo<T> *);                                // funcion recursiva para buscar
        void graficar( Nodo<T>* , std::ofstream& );                 // funcion recursiva para graficar
    public:
        Binary_Tree():pRoot(nullptr),_size(0){}
        ~Binary_Tree();
        void insert( T );
        int size(){ return _size; }
        void inOrder();                 // inorden recursivo
        void preOrder();                // preorden recursivo
        void postOrder();               // postorden recursivo
        void print();
        bool remove( T );               // elimina un nodo     
        bool find( T );                 // busca un nodo recursivo
        void clear();                   // vacia el arbol
        void graficar( std::string );   // grafica el arbol
};

template<typename T>
Binary_Tree<T>::~Binary_Tree()
{
    // pRoot->autoDestruir( pRoot );    // destructor recursivo, usa una funcion del nodo
    std::stack< Nodo<T>* > p;           // destructor iterativo, usa una pila
    Nodo<T>* current = pRoot;           // current inicia en pRoot
    while( pRoot )                      // si pRoot es null, termina
    {
        // std::cout<<"a\n";
        if( !current )                                          // si current es null
        {
            Nodo<T>* tmp = p.top();                             // saca el ultimo de la pila
            current = tmp->pSon[1];                             // current = hijo derecho
            if( !current )                                      // si current sigue null
            {                                                   // se prepara para eliminar tmp
                if( !tmp->pSon[2] )                             // si tmp no tiene padre
                    pRoot = nullptr;                            // pRoot null
                else if( tmp->pSon[2]->pSon[0] == tmp )         // si tmp es el hijo izq
                    tmp->pSon[2]->pSon[0] = nullptr;            // tmp->izq = null
                else                                            // si tmp es el hijo der
                    tmp->pSon[2]->pSon[1] = nullptr;            // tmp->der = null
                p.pop();                                        // elimina el ultimo elemento de la pila
                // std::cout<<"eliminando: "<<tmp->value<<'\n';
                // std::cout<<"valor de pRoot: "<<pRoot<<'\n';
                delete tmp;                                     // borra tmp
                continue;                                       // salta iteracion
            }
        }
        p.push( current );                      // inserta current a la pila
        current = current->pSon[0];             // avanza al hijo izq
    }
    std::cout<<"se destruyo sin errores\n";
}

template<typename T>
void Binary_Tree<T>::insert( T value )                    
{
    Nodo<T>* pNuevo = new Nodo<T>(value);               // nuevo nodo
    Nodo<T>* tmp = pRoot;                               // tmp avanza por el arbol
    if( !pRoot ) pRoot = pNuevo;                        // si pRoot null, primer elemento
    else
    {
        while( tmp->pSon[ tmp->value < value ] )        // mientras exista un hijo
            tmp = tmp->pSon[ tmp->value < value ];      // avanza
        if( tmp->value == value ) return;               // si el valor se repite, termina
        tmp->pSon[ tmp->value < value ] = pNuevo;       // nuevo hijo
        pNuevo->pSon[2] = tmp;                          // agrega el padre
    }
    _size++;
    while( tmp )
    {
        if( value < tmp->value )
            tmp->FE--;
        else
            tmp->FE++;
        // std::cout<<tmp->FE<<'\n';
        if( tmp->FE == 2 )                              // rotacion der
        {
            if( tmp->pSon[1]->FE == -1 )                // si tmp->der->FE == -1, rotacion DI
            {
                std::cout<<"ROTACION DI"<<'\n';
                if( tmp==pRoot ) RD( pRoot , 1 );       // si tmp es la raiz, pasa una referencia a la raiz
                else RD( tmp->pSon[2]->pSon[ tmp->pSon[2]->value < tmp->value ] , 1 );   // si tmp no es la raiz, pasa un referencia a tmp->padre->der
            }
            else                                        // sino tmp->der->FE == 1, rotacion DD
            {
                std::cout<<"ROTACION DD"<<'\n';
                if( tmp==pRoot ) RS( pRoot , 1 );       // si tmp es la raiz, pasa una referencia a la raiz
                else RS( tmp->pSon[2]->pSon[ tmp->pSon[2]->value < tmp->value ] , 1 );   // si tmp no es la raiz, pasa un referencia a tmp->padre->der
            }
            break;
        }
        else if( tmp->FE == -2 )                        // rotacion izq
        {
            if( tmp->pSon[0]->FE == 1 )                 // si tmp->izq->FE == 1, rotacion ID
            {
                std::cout<<"ROTACION ID"<<'\n';
                if( tmp==pRoot ) RD( pRoot , 0 );       // si tmp es la raiz, pasa una referencia a la raiz
                else RD( tmp->pSon[2]->pSon[ tmp->pSon[2]->value < tmp->value ] , 0 );   // si tmp no es la raiz, pasa un referencia a tmp->padre->izq
            }
            else                                        // sino tmp->izq->FE == -1, rotacion II
            {
                std::cout<<"ROTACION II"<<'\n';
                if( tmp==pRoot ) RS( pRoot , 0 );       // si tmp es la raiz, pasa una referencia a la raiz
                else RS( tmp->pSon[2]->pSon[ tmp->pSon[2]->value < tmp->value ] , 0 );   // si tmp no es la raiz, pasa un referencia a tmp->padre->izq
            }
            break;
        }
        else if( tmp->FE == 0 ) break;                  // si FE es 0, todas las ramas hijas equilibradas
        value = tmp->value;                             // guarda el valor del padre
        tmp = tmp->pSon[2];                             // apunta al padre
    }
}

template<typename T>
void Binary_Tree<T>::inOrder()
{
    inOrder( pRoot );
    std::cout<<'\n';
}

template<typename T>
void Binary_Tree<T>::inOrder( Nodo<T>*& p )
{
    if( !p ) return;
    inOrder( p->pSon[0] );
    std::cout<<p->value<<' ';
    inOrder( p->pSon[1] );
}

template<typename T>
void Binary_Tree<T>::preOrder()
{
    preOrder( pRoot );
    std::cout<<'\n';
}

template<typename T>
void Binary_Tree<T>::preOrder( Nodo<T>*& p )
{
    if( !p ) return;
    std::cout<<p->value<<' ';
    preOrder( p->pSon[0] );
    preOrder( p->pSon[1] );
}

template<typename T>
void Binary_Tree<T>::postOrder()
{
    postOrder( pRoot );
    std::cout<<'\n';
}

template<typename T>
void Binary_Tree<T>::postOrder( Nodo<T>*& p )
{
    if( !p ) return;
    postOrder( p->pSon[0] );
    postOrder( p->pSon[1] );
    std::cout<<p->value<<' ';
}

template<typename T>
void Binary_Tree<T>::print()
{
    print( pRoot );
}

template<typename T>
void Binary_Tree<T>::print( Nodo<T>* p )
{
    if( !p ) return;
    print( p->pSon[0] );
    std::cout<<p->value<<" FE: "<<p->FE<<'\n';
    print( p->pSon[1] );
}

template<typename T>
void Binary_Tree<T>::RD( Nodo<T>*& p , bool t )    // 1 para RDI, 0 para RID
{
    // std::cout<<"p: "<<p->value<<'\n';
    Nodo<T>* q = p->pSon[t];                        // guarda hijo de p en q
    // std::cout<<"q: "<<p->pSon[t]->value<<'\n';
    Nodo<T>* r = q->pSon[!t];                       // guarda hijo q en r
    // std::cout<<"r: "<<q->pSon[!t]->value<<'\n';
    q->pSon[!t] = r->pSon[t];                       // guarda hijo de r en q
    p->pSon[t] = r->pSon[!t];                       // guarda hijo de r en p

    r->pSon[!t] = p;                                // actualiza hijo de r
    r->pSon[t] = q;                                 // actualiza hijo de r

    r->pSon[2] = p->pSon[2];                        // r->padre apunta al padre de p
    p->pSon[2] = q->pSon[2] = r;                    // p,q->padre apuntan a r
    if( r->FE == 0 )                                // si FE (factor equilibrio) es 0, r no tenia hijos
    {
        p->FE = q->FE = 0;                          // todo balanceado
    }
    else if( r->FE == 1 )                           // si FE es 1, r tenia un hijo derecho
    {
        r->pSon[1]->pSon[0]->pSon[2] = r->pSon[1];  // r->der->izq->padre apunta a r->der
        r->pSon[0]->FE = 0;                         // FE del hijo derecho es 0 
        r->pSon[1]->FE = -1;                        // FE del hijo izquierdo es -1
    }
    else if( r->FE == -1 )
    {
        r->pSon[0]->pSon[1]->pSon[2] = r->pSon[0];  // r->izq->der->padre apunta a r->izq           
        r->pSon[0]->FE = 1;                         // FE del hijo izquiero es 1
        r->pSon[1]->FE = 0;                         // FE del hijo der es 0
    }
    if( p->pSon[!t] )                               // si p tiene hijo izq o der, disminuye o aumenta el FE (depende de la rotacion)
        p->FE += ( t? -1 : 1);                      // ( t = 0, ID)
    if( q->pSon[t] )                                // si q tiene hijo der o izq, aumenta o disminuye el FE (depende de la rotacion)
        q->FE += ( t? 1 : -1);                     // ( t = 1, DI)
    r->FE += p->FE + q->FE;                         // FE de r se acumula de sus ramas
    
    p = r;                                          // actualiza p
}

template<typename T>
void Binary_Tree<T>::RS( Nodo<T>*& p , bool t )     // 1 para RDD, 0 para RII
{
    // std::cout<<"p: "<<p->value<<'\n';
    Nodo<T>* q = p->pSon[t];                        // guarda hijo en q
    // std::cout<<"q: "<<p->pSon[t]->value<<'\n';
    p->pSon[t] = q->pSon[!t];                       // guarda hijo de q en p
    
    q->pSon[!t] = p;                                // actualiza hijo de q
    
    q->pSon[2] = p->pSon[2];                        // q->padre apunta al padre de p
    p->pSon[2] = q;                                 // p->padre apunta a q
    if( p->pSon[t] )                                // si q tenia un hijo que ahora esta en p
        p->pSon[t]->pSon[2] = p;                    // actualiza padre
    if( q->FE == 1 || q->FE == -1 )                 // si FE (factor de equuilibrio) es 1 o -1
        q->FE = p->FE = 0;                          // todo balanceado
    // else if( q->FE == 0 )                           // si FE es 0
    // {
    //     p->pSon[t]->pSon[2] = p;                    // p->hijo->padreapunta a p
    //     p->FE = -1*( t? -1 : 1 );                   // FE de p depende si fue RDD o RII
    //     q->FE = 1*( t? -1 : 1);                     // FE de q depende si fue RDD o RII
    // }
    p = q;                                          // actualiza p
} 

template<typename T>
void Binary_Tree<T>::guardarCola( Nodo<T> *p, std::stack<Nodo<T> *> &cola )
{
    if (!p)
        return;
    cola.push(p);
    guardarCola(p->pSon[0], cola);
    guardarCola(p->pSon[1], cola);
}

template<typename T>
bool Binary_Tree<T>::remove( T d )
{
    if (find(d))
    {
        Nodo<T> *q = pRoot;
        while ( q->value != d ) 
            q = q->pSon[q->value < d];
        std::queue<Nodo<T> *> cola;
        Nodo<T> *q2 = q;
        if( q == pRoot ) pRoot = nullptr;
        else
            q->pSon[2]->pSon[ q->pSon[2]->value < d ] = nullptr;
        guardarCola(q2, cola);
        _size = _size - cola.size(); 
        Nodo<T> *aux = cola.front();
        cola.pop();
        delete aux;
        while (cola.size())
        {
            aux = cola.front();
            insert(aux->value);
            cola.pop();
            delete aux;
        }
        return true;
    }
    return false;
}

template<typename T>
bool Binary_Tree<T>::find(T d, Nodo<T> *p)
{
    if (!p)
        return false;
    if (p->value == d)
    {
        return true;
    }
    return find( d , p->pSon[p->value < d] );
}

template<typename T>
bool Binary_Tree<T>::find( T d )
{
    return find( d, pRoot );
}

template<typename T>
void Binary_Tree<T>::clear()
{
    pRoot->autoDestruir( pRoot );
    pRoot = nullptr;
    _size = 0;
}

template<typename T>
void Binary_Tree<T>::graficar( std::string dir )
{
    std::ofstream f;
    f.open(dir);
    f<<"graph A {\n";
    graficar( pRoot , f );
    f<<"}\n";
    f.close();
}

template<typename T>
void Binary_Tree<T>::graficar( Nodo<T>* p , std::ofstream& f )
{
    if( !p ) return;
    if( p->pSon[2] != nullptr)
        f<<p->pSon[2]->value<<" -- "<<p->value<<";\n";
    graficar( p->pSon[0] , f );
    graficar( p->pSon[1] , f );
}

#endif