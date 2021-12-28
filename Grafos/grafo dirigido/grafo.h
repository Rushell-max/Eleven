#ifndef GRAFO_H
#define GRAFO_H
#include <list>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <map>
#include <set>
#include <stack>

template<class V,class E>class Vertex;

template <class V, class E>
class Grafo                     // dirigido
{
private:
    std::list<Vertex<V, E>> m_grafo;
public:
    Grafo(){}
    Vertex<V, E> *find_Vertex(V);
    void Insert_Vertex(V);
    void Insert_Arista(V , V , E );

    void delete_vertex(V);                
    void delete_Arista(V , V , E );      
    bool esVacio();             
    bool existeVertex(V);       
    bool sonAdyacentes(V ,V);   

    void verAdyacencias();

    void graficar(std::string);    

    void DFS();   
    void DFS_visit(Vertex<V,E>* ,std::unordered_set<V>& ); 
    void DFS_I();
    void BFS();
    void solve(std::pair<int,int>&);

    std::map<V,int> Dijkstra(V);
    void shortestPath(V, V);    

    void topologicalSort();
    void visit( Vertex<V,E>*, std::unordered_set<V>&, std::stack<V>& );
};

template<class V,class E>
Vertex<V, E> *Grafo<V,E>::find_Vertex(V v)
{
    Vertex<V, E> *p = nullptr;
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it )
        if ( it->m_Dato == v )
            p = &(*it);
    return p;
}

template<class V,class E>
void Grafo<V,E>::Insert_Vertex(V dato)
{
    m_grafo.push_back(Vertex<V, E>(dato));
}

template<class V,class E>
void Grafo<V,E>::Insert_Arista(V v1, V v2, E Ar)
{
    Vertex<V, E> *p = find_Vertex(v1);
    Vertex<V, E> *q = find_Vertex(v2);

    if (p && q)
    {
        p->m_Aristas.push_back(Edge<V, E>(Ar, q));
        // q->m_Aristas.push_back(Edge<V, E>(Ar, p));
    }
}

template<class V,class E>
void Grafo<V,E>::delete_vertex(V dato)
{
    Vertex<V,E>* p = find_Vertex(dato);
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
        {
            if(it2->m_pVertes->m_Dato == dato)
                it->m_Aristas.erase(it2);
        }
    }
    m_grafo.remove(*p);
}

template<class V,class E>
void Grafo<V,E>::delete_Arista(V v1, V v2, E dato)
{
    Vertex<V, E> *p = find_Vertex(v1);
    Vertex<V, E> *q = find_Vertex(v2);
    if(p && q)
    {
        for( auto it = p->m_Aristas.begin() ; it!=p->m_Aristas.end() ; ++it )
            if( it->m_Dato == dato )
                p->m_Aristas.erase(it);
        for( auto it = q->m_Aristas.begin() ; it!=q->m_Aristas.end() ; ++it )
            if( it->m_Dato == dato )
                q->m_Aristas.erase(it);
    }
}

template<class V,class E>
bool Grafo<V,E>::esVacio()
{   
    if( m_grafo.size() == 0 )
        return true;
    return false;
}

template<class V,class E>
bool Grafo<V,E>::existeVertex(V v)
{
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it)
        if( it->m_Dato == v )
            return true;
    return false;
}

template<class V,class E>
bool Grafo<V,E>::sonAdyacentes(V v1,V v2)
{
    Vertex<V,E>* p = find_Vertex(v1);
    Vertex<V,E>* q = find_Vertex(v2);
    if( p && q )
    {
        for( auto it = p->m_Aristas.begin() ; it!=p->m_Aristas.end() ; ++it )
        {
            if( it->m_pVertes == q )
                return true;
        }
    }
    return false;
}

template<class V,class E>
void Grafo<V,E>::verAdyacencias()
{
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        std::cout<<it->m_Dato<<" -> ";
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
            std::cout<<"("<<(it2->m_pVertes)->m_Dato<<", "<<it2->m_Dato<<") -> ";
        std::cout<<"\n";
    }
}

template<class V,class E>
void Grafo<V,E>::graficar(std::string dir)
{
    std::ofstream f;
    std::unordered_set<V> vertices;
    f.open(dir);
    f<<"digraph G{\n";
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        vertices.insert( it->m_Dato );
        f<<it->m_Dato<<";\n";
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
        {
            // if( vertices.find( (it2->m_pVertes)->m_Dato ) == vertices.end() )
            // {
                f<<it->m_Dato<<" -> ";
                f<<(it2->m_pVertes)->m_Dato<<"[label="<<it2->m_Dato<<"];\n";
            // }
        }
    }
    f<<"}";
    f.close();
}

template<class V,class E>
void Grafo<V,E>::DFS()
{
    std::unordered_set< V > gray;
    for( auto it=m_grafo.begin() ; it!=m_grafo.end() ; ++it )
    {
        if( gray.find(it->m_Dato) == gray.end() )
        {
            gray.insert(it->m_Dato);
            std::cout<<it->m_Dato<<"->";
            DFS_visit(&(*it),gray);
        }
    }
    std::cout<<'\n';
}

template<class V,class E>
void Grafo<V,E>::DFS_visit(Vertex<V,E>* vertice,std::unordered_set<V>& gray)
{
    for( auto it2=vertice->m_Aristas.begin() ; it2!=vertice->m_Aristas.end() ; ++it2 )
    {
        if( gray.find((it2->m_pVertes)->m_Dato) == gray.end() )
        {
            gray.insert((it2->m_pVertes)->m_Dato);
            std::cout<<it2->m_pVertes->m_Dato<<"->";
            DFS_visit(it2->m_pVertes,gray);
        }
    }
}

template<class V,class E>
void Grafo<V,E>::DFS_I()            // DFS -> pila
{
    std::stack< Vertex<V,E>* > vertices;
    std::unordered_set< V > visitados;
    Vertex<V,E>* ver = &(*m_grafo.begin());
    vertices.push( ver );
    visitados.insert(ver->m_Dato);
    std::cout<<ver->m_Dato<<"->";
    while( !vertices.empty() )
    {
        ver = vertices.top();
        vertices.pop();
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )
        {
            if( visitados.find( ( it2->m_pVertes)->m_Dato ) == visitados.end() )
            {
                vertices.push(it2->m_pVertes);
                visitados.insert((it2->m_pVertes)->m_Dato);
                std::cout<<( it2->m_pVertes)->m_Dato <<"->";
            }
        }            
    }
    std::cout<<'\n';
}

template<class V,class E>
void Grafo<V,E>::BFS()          // BFS -> cola
{
    std::queue< Vertex<V,E>* > vertices;
    std::unordered_set< V > visitados;
    Vertex<V,E>* ver = &(*m_grafo.begin());
    vertices.push( ver );
    visitados.insert(ver->m_Dato);
    std::cout<<ver->m_Dato<<"->";
    while( !vertices.empty() )
    {
        ver = vertices.front();
        vertices.pop();
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )
        {
            if( visitados.find( ( it2->m_pVertes)->m_Dato ) == visitados.end() )
            {
                vertices.push(it2->m_pVertes);
                visitados.insert((it2->m_pVertes)->m_Dato);
                std::cout<<( it2->m_pVertes)->m_Dato <<"->";
            }
        }
    }
    std::cout<<'\n';
}   

template<class V,class E>
void Grafo<V,E>::solve(std::pair<int,int>& v)
{
    std::queue< Vertex<V,E>* > vertices;
    std::unordered_set< V* > enCola;
    std::unordered_set< V* > visitados;
    Vertex<V,E>* ver = find_Vertex(v);
    vertices.push( ver );
    enCola.insert( &(ver->m_Dato) );
    while( !vertices.empty() )
    {
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )
        {
            if( enCola.find( ( &(it2->m_pVertes)->m_Dato) ) == enCola.end() && visitados.find( &(( it2->m_pVertes)->m_Dato) ) == visitados.end() )
            {
                if( it2->m_Dato == 't' )
                {
                    std::cout<<"yes\n";
                    return;
                }
                vertices.push(it2->m_pVertes);
                enCola.insert( &((it2->m_pVertes)->m_Dato) );
            }
        }
        vertices.pop();
        enCola.erase( &(ver->m_Dato) );
        visitados.insert( &(ver->m_Dato) );
        // std::cout<<ver->m_Dato.first<<' '<<ver->m_Dato.second<<"->";
        if(!vertices.empty())
            ver = vertices.front();
    }
    std::cout<<"no\n";
}   

template<class V,class E>
Vertex<V,E>* extractMin( std::map<V,std::pair< int,Vertex<V,E>* >>& Q ){
    int min = (Q.begin())->second.first;
    Vertex<V,E>* vertice = (Q.begin())->second.second;
    for( auto it = Q.begin() ; it!=Q.end() ; ++it )
    {
        // std::cout<<it->first<<" "<<it->second.first<<'\n';
        if( it->second.first < min )
        {
            min = it->second.first;
            vertice = it->second.second;
        }
    }
    // std::cout<<'\n';
    return vertice;
}

template<class V,class E>
std::map<V,int> Grafo<V,E>::Dijkstra( V v_actual )
{
    std::map<V,int> S;                                  // guarda los caminos mas cortos desde el vertice v
    std::map<V,std::pair< int,Vertex<V,E>* >> Q;        // guarda todos los vertices con sus caminos 
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it )     // llena Q con cada vertice
    {
        if( it->m_Dato != v_actual )                                
            Q[it->m_Dato] = make_pair(INT_MAX, &(*it));             // todos los vertices con distancia max
        else                                                
            Q[it->m_Dato] = make_pair(0, &(*it));                   // vertice inicial distancia 0
    }
    while( !Q.empty() ){                                            // mientras Q tenga elementos
        Vertex<V,E>* vertice = extractMin( Q );                     // extraer el vertice con menor distancia
        // std::cout<<v_actual<<" -> "<<S[v_actual]<<'\n';
        v_actual = vertice->m_Dato;                                 // vertice de donde parte la arista
        S[v_actual] = Q[v_actual].first;                            // inserta en S la distancia minima al vertice
        // std::cout<<v_actual<<" "<<Q[v_actual].first<<'\n';
        for( auto it = vertice->m_Aristas.begin() ; it!=vertice->m_Aristas.end() ; ++it )   // recorre cada arista del vertice
        {
            if( Q.find((it->m_pVertes)->m_Dato) != Q.end() )                                // si el vertice aun no ha sido extraido de Q
            {
                if( Q[v_actual].first + it->m_Dato < Q[(it->m_pVertes)->m_Dato].first )     // si el peso es menor al peso actual del vertice
                {
                    // std::cout<< Q[(it->m_pVertes)->m_Dato].first <<" = "<< Q[v_actual].first <<" + " << it->m_Dato<<'\n';
                    Q[(it->m_pVertes)->m_Dato].first = Q[v_actual].first + it->m_Dato;      // actualiza peso minimo
                }
            }
        }
        Q.erase(v_actual);                  // elimina el vertice actual de Q
    }
    return S;
}

template<class V,class E>
void Grafo<V,E>::shortestPath( V v1, V v2 )
{
    std::map<V,int> min = Dijkstra( v1 );
    for( auto it = min.begin() ; it!=min.end() ; ++it )
        // std::cout<<v1<<" -> "<<it->first<<" = "<<it->second<<'\n';
        if( it->first == v2 )
            std::cout<<v1<<" -> "<<v2<<" : "<<it->second<<'\n';
}

template<class V,class E>
void Grafo<V,E>::visit( Vertex<V,E>* vertice, std::unordered_set<V>& visitados, std::stack<V>& sort)
{
    for( auto it = vertice->m_Aristas.begin() ; it!=vertice->m_Aristas.end() ; ++it )
    {
        if( visitados.find( it->m_pVertes->m_Dato ) == visitados.end() )
        {
            visitados.insert( it->m_pVertes->m_Dato );
            visit( it->m_pVertes, visitados, sort );
            sort.push( it->m_pVertes->m_Dato );
        }
    }
}

template<class V,class E>
void Grafo<V,E>::topologicalSort()
{
    std::stack<V> sort;
    std::unordered_set<V> visitados;
    for( auto it=m_grafo.begin() ; it!=m_grafo.end() ; ++it )
    {
        if( visitados.find( it->m_Dato ) == visitados.end() )
        {
            visitados.insert( it->m_Dato );
            visit( &(*it), visitados, sort );
            sort.push( it->m_Dato );
        }
    }

    while( !sort.empty() )
    {
        std::cout<<sort.top()<<'\n';
        sort.pop();
    }
    std::cout<<'\n';
}

#endif