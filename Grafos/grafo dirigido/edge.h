#ifndef EDGE_H
#define EDGE_H

template <class V, class E> class Vertex;

template <class V, class E>
class Edge
{
public:
    E m_Dato;
    Vertex<V, E> *m_pVertes;

public:
    Edge(E , Vertex<V, E> *);
    Edge(){}
};

template<class V,class E>
Edge<V,E>::Edge(E d, Vertex<V, E> *p)
{
    m_Dato = d;
    m_pVertes = p;
}

#endif