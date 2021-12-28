#include <iostream>
#include <list>
#include <ostream>
#include <unordered_set>
#include <queue>
#include <stack>

#include <limits>
#include <list>
#include <utility>
#define infinito std::numeric_limits<int>::max()

using namespace std;


template<class V,class E>
class Vertex;

template<class V, class E>
class Edge
{
    public:
        E               m_Dato;
        Vertex<V,E> *   m_pVertices;
    public:

        Edge(E d, Vertex<V,E> * p = 0)
        {
            m_Dato = d;
            m_pVertices = p;
        }
        Edge(){};
};

template<class V, class E>
class Vertex
{
    public:
        V                   m_Dato;
        list<Edge<V,E>>     m_Aristas;
        bool                m_Visit;
        int                 m_Distancia;
    public:
        Vertex(V d)
        {
            m_Dato = d;
            m_Visit = false;
            m_Distancia = 0;
        }
        Vertex(){};

        bool operator==(Vertex<V,E> v2)
        {
            if(m_Dato == v2.m_Dato)
                return true;
            return false;
        }
        bool operator!=( Vertex<V,E> v2 )
        {
            if( *this == v2 )
                return false;
            return true;
        }

};


template <class V, class E>
class Grafo
{
    public:
        int final;
        list<Vertex<V, E>> m_grafo;

    public:
        Grafo(){};
        Vertex<V, E> *find_Vertex(V v)
        {
            Vertex<V, E> *p = nullptr;
            for(auto it = m_grafo.begin(); it!= m_grafo.end(); ++it)
                if(it->m_Dato == v)
                    p = &(*it);
            return p;
        }
        void Insert_Vertex(V dato)
        {
            m_grafo.push_back(Vertex<V, E>(dato));
        }
        void Insert_Arista(V v1, V v2, E Ar)
        {
            Vertex<V, E> *p = find_Vertex(v1);
            Vertex<V, E> *q = find_Vertex(v2);

            if (p && q){
                p->m_Aristas.push_back(Edge<V, E>(Ar, q));
                //q->m_Aristas.push_back(Edge<V, E>(Ar, p));
            }
        }
        void Print(ostream & out)
        {
            cout<<"\n En PRINT \n";
            for(auto it = m_grafo.begin(); it!=m_grafo.end(); ++it){
                cout<<">> "<<it->m_Distancia<<" _ "<<it->m_Dato;
                for(auto it2 = it->m_Aristas.begin(); it2!=it->m_Aristas.end(); ++it2)
                    cout<<" --"<<it2->m_Dato<<"--> ("<<(it2->m_pVertices)->m_Dato<<") /";
                cout<<"\n";
            }
        }
        void not_visit()
        {
            for(auto it=m_grafo.begin(); it!=m_grafo.end(); ++it)
                it->m_Visit = 0;
        }
        void DFS(Vertex<V,E> *p)
        {
            cout<<"\n En DFS >> \n";
            not_visit();
            stack<Vertex<V,E> *> pila;
            pila.push(p);

            while(!pila.empty())
            {
                p = pila.top();
                cout<<" -> "<<p->m_Dato;
                pila.pop();
                for(auto it = p->m_Aristas.begin(); it!= p->m_Aristas.end(); ++it)
                    //cout<<" - "<<it->m_pVertices->m_Dato<<" "<<it->m_pVertices->visit;
                    if(!it->m_pVertices->m_Visit) {it->m_pVertices->m_Visit = true; pila.push(it->m_pVertices); }
            }
            // Cambiar todos los visit a 0
        }
        void BFS(Vertex<V,E> *p)
        {
            cout<<"\n En BFS >> \n";
            not_visit();
            queue<Vertex<V,E> *> cola;
            cola.push(p);
            p->m_Distancia = 0;
            while(!cola.empty())
            {
                p = cola.front();
                cout<<" -> "<<p->m_Dato;
                cola.pop();
                for(auto it = p->m_Aristas.begin(); it!= p->m_Aristas.end(); ++it)
                    //cout<<" - "<<it->m_pVertices->m_Dato<<" "<<it->m_pVertices->visit;
                    if(!it->m_pVertices->m_Visit) {it->m_pVertices->m_Visit = true; cola.push(it->m_pVertices); it->m_pVertices->m_Distancia = p->m_Distancia + 1; }
            }
        }
        void DFS()
        {
            cout<<"\n En DFS >> \n";
            std::unordered_set<V> black;
            for(auto it= m_grafo.begin(); it!=m_grafo.end(); ++it)
                if(black.find(it->m_Dato) == black.end())
                {
                    black.insert(it->m_Dato);
                    cout<<" -> "<<it->m_Dato;
                    DFS_visit(&(*it), black);
                }
        }
        void DFS_visit(Vertex<V,E>* _v, unordered_set<V>& _black)
        {
            for(auto it2 = _v->m_Aristas.begin(); it2!=_v->m_Aristas.end(); ++it2)
                if(_black.find((it2->m_pVertices)->m_Dato) == _black.end())
                {
                    _black.insert((it2->m_pVertices)->m_Dato);
                    cout<<" -> "<<it2->m_pVertices->m_Dato;            
                    DFS_visit(it2->m_pVertices, _black);
                }
        }
        void BFS()
        {
            cout<<"\n En BFS >> \n";
            std::queue<Vertex<V,E>*> cola;
            std::unordered_set<Vertex<V,E>*> visitados;
            cola.push(&m_grafo.front());
            m_grafo.front().m_Distancia = 0;
            while(!cola.empty())
            {
                for(auto it = cola.front()->m_Aristas.begin(); it!= cola.front()->m_Aristas.end(); ++it)
                {
                    if(visitados.find(it->m_pVertices) == visitados.end()){cola.push(it->m_pVertices); it->m_pVertices->m_Distancia = cola.front()->m_Distancia + 1; }
                }
                cout<<" -> "<<cola.front()->m_Dato;
                visitados.insert(cola.front());
                cola.pop();
            }
        }
        
        void Print_Camino(V v1, V v2)
        {
            Vertex<V, E> *p = find_Vertex(v1);
            Vertex<V, E> *q = find_Vertex(v2);

            if (p && q){
                //cout<<"\n En DFS >> \n";
                std::unordered_set<V> black;
                //std::queue<V> camino;
                for(auto it= m_grafo.begin(); it!=m_grafo.end(); ++it )
                    if(black.find(it->m_Dato) == black.end())
                    {
                        std::queue<V> camino;
                        black.insert(it->m_Dato);
                        //cout<<" -> "<<it->m_Dato;
                        camino.push(it->m_Dato);
                        //Print_Camino(camino);
                        Print_Camino(&(*it), (q), black, camino);
                    }
                
            }   
        }
        void Print_Camino(Vertex<V,E>* _v, Vertex<V,E>* _v2, unordered_set<V>& _black, queue<V> _camino)
        {
            for(auto it2 = _v->m_Aristas.begin(); it2!=_v->m_Aristas.end(); ++it2)
                if(_black.find((it2->m_pVertices)->m_Dato) == _black.end())
                {
                    std::queue<V> camino = _camino;
                    _black.insert((it2->m_pVertices)->m_Dato);
                    //cout<<" -> "<<it2->m_pVertices->m_Dato;            
                    camino.push((it2->m_pVertices)->m_Dato);
                    if(it2->m_pVertices == _v2) Print_Camino(camino);
                    //Print_Camino(camino);
                    Print_Camino(it2->m_pVertices, _v2, _black, camino);
                }
        }
        void Print_Camino(queue<V> _camino)
        {
            cout<<"\n Print_Camino "<<endl;
            while(!_camino.empty())
            {
                cout<<" -> "<<_camino.front();
                _camino.pop();
            }
        }

        /*template<class V,class E>
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
        bool formaCiclo( V v1, V v2)                             // comprueba si no existe un ciclo en el grafo
        {                                                                                   // usa una busqueda en profundidad
            std::stack< Vertex<V,E>* > vertices;
            std::unordered_set< V > visitados;
            Vertex<V,E>* ver = &(*G.m_grafo.begin());
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
                        if( (it2->m_pVertes)->m_Dato == v2 )                                // si hay un camino hhacia v2
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
            std::multimap<E, std::pair<V,V> > aristas;                      // guarda todas las aristas del grafo en orden no decreciente
            Grafo<V,E> MST;                                                 // arbol de expansion minima
            for( auto it = m_grafo.begin() ; it != m_grafo.end() ; ++it )   // recorre cadad vertice
            {   
                MST.Insert_Vertex( it->m_Dato );                                                                        // inserta vertice
                for( auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2 )                              // recorre cada arista
                    if( !existeArista( aristas, it->m_Dato, (it2->m_pVertes)->m_Dato) )                                 // comprueba si no se añadio antes la arista
                        aristas.insert( make_pair( it2->m_Dato, make_pair( it->m_Dato, (it2->m_pVertes)->m_Dato ) ) );  // guarda la arista
                        // std::cout<<"INSERTANDO "<<it->m_Dato<<" "<<(it2->m_pVertes)->m_Dato <<'\n';
            }

            // for( auto it = aristas.begin() ; it!=aristas.end() ; ++it )
            //     std::cout<<"( "<<it->second.first<<", "<<it->second.second<<" )[ "<< it->first <<" ]\n";

            for( auto it = aristas.begin() ; it!=aristas.end() ; ++it )                                     // recorre todas las arista
                if( !formaCiclo( MST, (it->second).first, (it->second).second ) )                           // si no se forma un ciclo en el arbol
                    MST.Insert_Arista( (it->second).first, (it->second).second , it->first );               // inserta la arista

            MST.graficar("kruskal.dot");
            system("dot kruskal.dot -o kruskal.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
            system("kruskal.png");
        }
*/
};

void GrafoLE()
{
    Grafo<string, int> G;
    G.Insert_Vertex("Lima");
    G.Insert_Vertex("Arequipa");
    G.Insert_Vertex("Cuzco");
    G.Insert_Vertex("Puno");
    G.Insert_Vertex("Ica");
    G.Insert_Vertex("Juliaca");
    G.Insert_Vertex("Ilo");
    G.Insert_Vertex("Tacna");

    G.Insert_Arista("Arequipa", "Cuzco", 250);
    G.Insert_Arista("Arequipa", "Puno", 200);
    G.Insert_Arista("Lima", "Arequipa", 160);
    G.Insert_Arista("Lima", "Ica", 100);
    G.Insert_Arista("Cuzco", "Juliaca", 150);
    G.Insert_Arista("Juliaca", "Lima", 150);
    G.Insert_Arista("Juliaca", "Ilo", 400);
    G.Insert_Arista("Ica", "Ilo", 400);
    //G.Insert_Arista("Tacna", "Ilo", 400);

    G.Print(cout);
    G.DFS();
    G.BFS();
    G.Print(cout);
    G.DFS(&G.m_grafo.front());
    G.BFS(&G.m_grafo.front());
    G.Print(cout);

    G.Print_Camino("Lima", "Puno");

}

#include <iostream>
#include <list>
#include <unordered_set>
#include <queue>
using namespace std;

class GrafoMA
{
    public:
        int m_vertices;
        int ** MA;
    public:
        GrafoMA() 
        {
            MA = 0;
            m_vertices = 0;
        }
        void newGraph(int v)
        {
            m_vertices = v;
            MA = new int *[v]; 
            for(int i=0; i<v;i++)
                MA[i]=new int[v];

            for(int i = 0; i<v; i++)
                for(int j = 0; j<v; j++)
                    MA[i][j] = 0;
        }
        void addEdge(int v, int w)
        {
            MA[v][w] = 1;
        }
        list<int> adj(int v)
        {
            list<int> A;
            for(int i=0; i<m_vertices; i++)
                if(MA[v][i] == 1 || MA[i][v] == 1) A.push_back(i);
            return A;
        }
        int outdegree(int v)
        {
            int num = 0;
            for(int i=0; i<m_vertices; i++)
                if(MA[v][i] == 1) num++;
            return num;       
        }
        int indegree(int v)
        {
            int num = 0;
            for(int i=0; i<m_vertices; i++)
                if(MA[i][v] == 1) num++;
            return num;     
        }
        void reverse()
        {
            for(int i= 0; i<m_vertices; i++)
                for(int j=0; j<i; j++){
                    int aux = MA[j][i];
                    MA[j][i] = MA[i][j];
                    MA[i][j] = aux;
                }
        }

        void DFS()
        {
            cout<<"\n En DFS >> \n";
            std::unordered_set<int> black;
            for(int i = 0; i<m_vertices; i++)
                if(black.find(i) == black.end())
                {
                    black.insert(i);
                    cout<<" -> "<<i;
                    DFS_visit(i, black);
                }
        }
        void DFS_visit(int _v, unordered_set<int>& _black)
        {
            for(int i = 0; i<m_vertices; i++)
                if( MA[_v][i] == 1 /**&& i != _v**/ && _black.find(i) == _black.end())
                {
                    _black.insert(i);
                    cout<<" -> "<<i;            
                    DFS_visit(i, _black);
                }
        }
        bool find(int i, list<int> A)
        {
            for(auto it = A.begin(); it!= A.end(); ++it)
                if(i == *it) return true;
            return false;
        }
        int show(int _pos, list<int> A)
        {
            int cont = 0;
            auto it = A.begin();
            while(cont != _pos && it != A.end())
            {
                ++it;
                cont++;
            }
            return *it;
        }
        void BFS()
        {
            cout<<"\n En BFS >> \n";
            std::list<int> black;
            int cont = 0;
            black.push_back(0);
            while(cont != m_vertices)
            {
                //cout<<" Buscando en "<<show(cont, black)<<endl;
                for(int i = 0; i<m_vertices; i++)
                {
                    if( MA[show(cont, black)][i] == 1 && /** i != show(cont, black) && **/ !find(i, black))
                    {
                        //cout<<" Insertando > "<<i<<"\n"; 
                        black.push_back(i);
                    }
                }
                //cout<<" imprimiendo en black con pos "<<cont<<"\n";
                cout<<" -> "<<show(cont, black);
                cont++;
            }           

        }
        void Print()
        {
            for(int i = 0; i<m_vertices; i++)
            {
                for(int j = 0; j<m_vertices; j++)
                {
                    cout<<" "<<MA[i][j];
                }
                cout<<endl;
            }
        }
        void Dijskstra()
        {
            if(INT_MAX + 3 > INT_MAX) cout<<"AA";
            else cout<<" NEL";
        }

        void Warshall()
        {
            for(int i=0;i<m_vertices;i++) {
                for(int j=0;j<m_vertices;j++) {
                    for(int k=0; k<m_vertices; k++) {
                        if (MA[i][j] != INT_MAX && MA[k][j] != INT_MAX && MA[i][k] != INT_MAX)
                            MA[i][j] = min(MA[i][j], (MA[i][k] + MA[k][j]));
                    }
                }
            }
        }
        void Floyd()
        {
            for(int i=0;i<m_vertices;i++) {
                for(int j=0;j<m_vertices;j++) {
                    for(int k=0; k<m_vertices; k++) {
                        if (MA[i][j] != INT_MAX || (MA[i][k] != INT_MAX && MA[k][j] != INT_MAX))
                            MA[i][j] = 1;
                    }
                }
            }
        }
};

void GrafoMAA()
{
    GrafoMA A;
    A.newGraph(5);

    A.addEdge(0,1);
    A.addEdge(1,1);
    A.addEdge(1,3);
    A.addEdge(3,1);
    A.addEdge(3,2);
    A.addEdge(3,3);
    A.addEdge(4,3);

    //A.Print();
    //A.BFS();
    //A.DFS();
    A.Dijskstra();
}

int main()
{
    //GrafoLE();
    GrafoMAA();
}