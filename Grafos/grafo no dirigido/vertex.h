#ifndef VERTEX_H
#define VERTEX_H

#include <list>

template <class V, class E>class Edge;

// vertice 
template <class V, class E>
class Vertex
{
public:
    // nombre del vertice
    V m_Dato;
    // lista de vertices adyacentes
    std::list<Edge<V, E>> m_Aristas;

public:
    Vertex(V);
    Vertex(){};
    bool operator==( Vertex<V,E> );
    bool operator!=( Vertex<V,E> );
};

template<class V,class E>
Vertex<V,E>::Vertex(V d)
{
    m_Dato = d;
}

template<class V,class E>
bool Vertex<V,E>::operator==( Vertex<V,E> v2 )
{
    if( m_Dato == v2.m_Dato )
        return true;
    return false;
}

template<class V,class E>
bool Vertex<V,E>::operator!=( Vertex<V,E> v2 )
{
    if( *this == v2 )
        return false;
    return true;
}

#endif