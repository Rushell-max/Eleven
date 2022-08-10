#ifndef GRAFO_H
#define GRAFO_H
#include <list>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <stack>

template<class V,class E>class Vertex;

// grafo no dirigido
template <class V, class E>
class Grafo                     
{
private:
    std::list<Vertex<V, E>> m_grafo;    // lista de adyacencia
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

    // muestra lista de adyacencia
    void verAdyacencias();

    // grafica grafo
    void graficar(std::string);    

    // busqueda profundidad
    void DFS();   
    void DFS_visit(Vertex<V,E>* ,std::unordered_set<V>& ); 
    // busqueda en profundidad iterativo (pila)
    void DFS_I();
    // busqueda en anchura (cola)
    void BFS();
    
    std::map<V,int> Dijkstra(V);    
    void shortestPath(V, V);

    void Kruskal();
    bool formaCiclo( Grafo<V,E>&, V, V );  

    void Prim();
};

template<class V,class E>
Vertex<V, E> *Grafo<V,E>::find_Vertex(V v)
{
    Vertex<V, E> *p = nullptr;
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it )     // recorre lista adyacencia
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

    if (p && q) // si ambos vertices existen
    {
        p->m_Aristas.push_back(Edge<V, E>(Ar, q));
        q->m_Aristas.push_back(Edge<V, E>(Ar, p));
    }
}

template<class V,class E>
void Grafo<V,E>::delete_vertex(V dato)
{
    Vertex<V,E>* p = find_Vertex(dato);
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)        // recorre lista adyacencia
    {
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; )    // recorre lista de aristas
        {
            if(it2->m_pVertes->m_Dato == dato)
                it2 = it->m_Aristas.erase(it2);     // elimina puntero al vertice adyacente
            else
                ++it2;
        }
    }
    m_grafo.remove(*p);
}

template<class V,class E>
void Grafo<V,E>::delete_Arista(V v1, V v2, E dato)
{
    Vertex<V, E> *p = find_Vertex(v1);
    Vertex<V, E> *q = find_Vertex(v2);
    if(p && q)      // si ambos vertices existen
    {
        for( auto it = p->m_Aristas.begin() ; it!=p->m_Aristas.end() ; )    // busca en la lista de v1
        {
            if( it->m_Dato == dato && it->m_pVertes == q)            
                it = p->m_Aristas.erase(it);    // borra arista
            else
                ++it;
        }
        for( auto it = q->m_Aristas.begin() ; it!=q->m_Aristas.end() ; )    // busca en la lista de v2
        {
            if( it->m_Dato == dato && it->m_pVertes == p )
                it = q->m_Aristas.erase(it);    // borra arista
            else
                ++it;
        }
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
        for( auto it = p->m_Aristas.begin() ; it!=p->m_Aristas.end() ; ++it )   // busca en la lista de v1
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
    f<<"graph G{\n";
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        vertices.insert( it->m_Dato );
        f<<it->m_Dato<<";\n";
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
        {
            if( vertices.find( (it2->m_pVertes)->m_Dato ) == vertices.end() )
            {
                f<<it->m_Dato<<" -- ";
                f<<(it2->m_pVertes)->m_Dato<<"[label="<<it2->m_Dato<<"];\n";
            }
        }
    }
    f<<"}";
    f.close();

    std::stringstream dir1(dir);
    std::string name, ext, aux;
    std::getline(dir1,aux,'.');
    name = aux;
    std::getline(dir1,aux,'.');
    ext = aux;
    system(&(("dot "+ dir + " -o " + name + ".png -Tpng")[0]));
    system(&((name + ".png")[0]));
    // system("dot grafo.dot -o grafo.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("grafo.png");
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
            DFS_visit(&(*it),gray);             // agrega todos los vertices adyacentes
        }
    }
    std::cout<<'\n';
}

template<class V,class E>
void Grafo<V,E>::DFS_visit(Vertex<V,E>* vertice,std::unordered_set<V>& gray)
{
    for( auto it2=vertice->m_Aristas.begin() ; it2!=vertice->m_Aristas.end() ; ++it2 )  // recorre aristas de un vertice
    {
        if( gray.find((it2->m_pVertes)->m_Dato) == gray.end() )     // si el vertice adyacente no esta en gray
        {
            gray.insert((it2->m_pVertes)->m_Dato);
            std::cout<<it2->m_pVertes->m_Dato<<"->";
            DFS_visit(it2->m_pVertes,gray);             // agrega vertices adyacentes
        }
    }
}

template<class V,class E>
void Grafo<V,E>::DFS_I()            // DFS -> pila
{
    std::stack< Vertex<V,E>* > vertices;        // pila de punteros a vertices
    std::unordered_set< V > visitados;          // hash table guarda visitados
    Vertex<V,E>* ver = &(*m_grafo.begin());
    vertices.push( ver );
    visitados.insert(ver->m_Dato);
    std::cout<<ver->m_Dato<<"->";
    while( !vertices.empty() )
    {
        ver = vertices.top();
        vertices.pop();
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )   // recorre lista de aristas
        {
            if( visitados.find( ( it2->m_pVertes)->m_Dato ) == visitados.end() )    // si no fue visitado
            {
                vertices.push(it2->m_pVertes);                  // agrega a la pila
                visitados.insert((it2->m_pVertes)->m_Dato);     // ahora esta visitado
                std::cout<<( it2->m_pVertes)->m_Dato <<"->";
            }
        }            
    }
    std::cout<<'\n';
}

template<class V,class E>
void Grafo<V,E>::BFS()          // BFS -> cola
{
    std::queue< Vertex<V,E>* > vertices;            // cola punteros a vertice
    std::unordered_set< V > visitados;              // hash table guarda vertices
    Vertex<V,E>* ver = &(*m_grafo.begin());
    vertices.push( ver );
    visitados.insert(ver->m_Dato);
    std::cout<<ver->m_Dato<<"->";
    while( !vertices.empty() )
    {
        ver = vertices.front();
        vertices.pop();
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )   // recorre lista de aristas
        {
            if( visitados.find( ( it2->m_pVertes)->m_Dato ) == visitados.end() )    // si no fue visitado
            {
                vertices.push(it2->m_pVertes);                  // agrega a la cola
                visitados.insert((it2->m_pVertes)->m_Dato);     // ahora esta visitado
                std::cout<<( it2->m_pVertes)->m_Dato <<"->";
            }
        }
    }
    std::cout<<'\n';
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
    // guarda los caminos mas cortos desde el vertice v
    std::map<V,int> S;                                  // <v, dist min>                   
    // guarda todos los vertices con sus caminos
    std::map<V,std::pair< int,Vertex<V,E>* >> Q;        // <v1 <dist min, v2>>
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
bool Grafo<V,E>::formaCiclo( Grafo<V,E>& G, V v1, V v2)                             // comprueba si no existe un ciclo en el grafo
{                                                                                   // usa una busqueda en profundidad
    std::stack< Vertex<V,E>* > vertices;
    std::unordered_set< V > visitados;
    Vertex<V,E>* ver = G.find_Vertex(v1);
    vertices.push( ver );
    visitados.insert(ver->m_Dato);
    while( !vertices.empty() )
    {
        ver = vertices.top();
        vertices.pop();
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )
        {
            if( visitados.find( (it2->m_pVertes)->m_Dato ) == visitados.end() )
            {
                if( (it2->m_pVertes)->m_Dato == v2 )                                // si hay un camino hacia v2
                    return true;                                                    // si se puede formar un ciclo
                vertices.push(it2->m_pVertes);
                visitados.insert((it2->m_pVertes)->m_Dato);
            }
        }            
    }
    return false;
}

template<class V,class E>
bool existeArista( std::multimap<E,std::pair<V,V>>& aristas, V v1, V v2 )           // comprueba si la arista ya esta guardada, evita duplicados
{
    for( auto it = aristas.begin() ; it!= aristas.end() ; ++it )
    {
        if ( (it->second).first == v1 && (it->second).second == v2 )
            return true;
        if ( (it->second).second == v1 && (it->second).first == v2 )
            return true;
    }
    return false;
}

template<class V,class E>
void Grafo<V,E>::Kruskal()
{
    // guarda todas las aristas del grafo en orden no decreciente
    std::multimap<E, std::pair<V,V> > aristas;                      // <arista, <v1, v2>>
    Grafo<V,E> MST;                                                 // arbol de expansion minima
    for( auto it = m_grafo.begin() ; it != m_grafo.end() ; ++it )   // recorre cada vertice
    {   
        MST.Insert_Vertex( it->m_Dato );                                                                        // inserta vertice
        for( auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2 )                              // recorre cada arista
            if( !existeArista( aristas, it->m_Dato, (it2->m_pVertes)->m_Dato) )                                 // comprueba si no se añadio antes la arista
                aristas.insert( make_pair( it2->m_Dato, make_pair( it->m_Dato, (it2->m_pVertes)->m_Dato ) ) );  // guarda la arista
                // std::cout<<"INSERTANDO "<<it->m_Dato<<" "<<(it2->m_pVertes)->m_Dato <<'\n';
    }

    for( auto it = aristas.begin() ; it!=aristas.end() ; ++it )
        std::cout<<"( "<<it->second.first<<", "<<it->second.second<<" )[ "<< it->first <<" ]\n";

    for( auto it = aristas.begin() ; it!=aristas.end() ; ++it )      
    {                               // recorre todas las arista
        if( !formaCiclo( MST, (it->second).first, (it->second).second ) )                           // si no se forma un ciclo en el arbol
            MST.Insert_Arista( (it->second).first, (it->second).second , it->first );               // inserta la arista
        // else if( !formaCiclo( MST, (it->second).second, (it->second).first ) )                           // si no se forma un ciclo en el arbol
        //     MST.Insert_Arista( (it->second).first, (it->second).second , it->first );               // inserta la arista   
    }
    MST.graficar("kruskal.dot");
    // system("dot kruskal.dot -o kruskal.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("kruskal.png");
}

template<class V,class E>
void Grafo<V,E>::Prim()
{
    Grafo<V,E> MST;
    std::set<Vertex<V,E>*> vertices;                // vertices que ya tienen su camino mas corto
    std::unordered_set<V> Q;                        // vertices que aun no tienen su camino mas corto
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it ) 
    {
        Q.insert( it->m_Dato );
        MST.Insert_Vertex( it->m_Dato );
    }
    vertices.insert( &(*(m_grafo.begin())) );
    Q.erase( (m_grafo.begin())->m_Dato );
    while( !Q.empty() )
    {
        int min = INT_MAX;
        V v;
        Vertex<V,E>* vMin = nullptr;
        for( auto it = vertices.begin() ; it != vertices.end() ; ++it )         // busca en los vertices que ya tienen camino mas corto
        {
            for( auto it2 = (*it)->m_Aristas.begin() ; it2!=(*it)->m_Aristas.end() ; ++it2 )    // busca en los vertices adyacentes
            {
                if( Q.find( it2->m_pVertes->m_Dato ) != Q.end() )               // si esta en Q, aun no tiene su camino mas corto
                {
                    if( it2->m_Dato < min )         // peso de la arista menor
                    {
                        min = it2->m_Dato;          // dist min
                        v = (*it)->m_Dato;          // v1
                        vMin = it2->m_pVertes;      // v2
                    }
                }
            }
        }
        MST.Insert_Arista( v, vMin->m_Dato, min );      // inserta arista con menos peso
        Q.erase( vMin->m_Dato );                        // elimina v2
        vertices.insert( vMin );                        // inserta v2
    }

    MST.graficar("Prim.dot");
    // system("dot Prim.dot -o Prim.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("Prim.png");
}

#endif