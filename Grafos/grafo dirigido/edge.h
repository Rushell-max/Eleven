#ifndef EDGE_H
#define EDGE_H

template <class V, class E> class Vertex;

// arista
template <class V, class E>
class Edge
{
public:
    // peso de la arista
    E m_Dato;
    // puntero a vertice adyacente
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