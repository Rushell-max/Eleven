#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo
{
    public:
        T m_Dato;
        Nodo<T> *m_pSon[3];

        Nodo( T );
        void autoDestruir( Nodo<T>*& );
};

template<typename T>
Nodo<T>::Nodo( T d )
{
    m_Dato = d;
    // hijo izquierdo
    m_pSon[0] = 0;
    // hijo derecho
    m_pSon[1] = 0;
    // padre
    m_pSon[2] = 0;
}

template<typename T>
void Nodo<T>::autoDestruir( Nodo<T>*& p )
{
    if( !p ) return;
    autoDestruir( p->m_pSon[0] );
    autoDestruir( p->m_pSon[1] );
    delete p;
}

#endif