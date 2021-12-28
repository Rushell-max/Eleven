#include <iostream>
#include <list>
#include <ostream>
#include <unordered_set>
#include <queue>
#include <stack>

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
        void newGraphLaberinto(int n, int m, vector<string> & M) // n = filas, m = columnas 
        {
            int ver;
            for(int i=0; i<n; i++)
                for(int j=0; j<m; j++){
                    ver = i*10 + j;
                    Insert_Vertex(ver);
                }
        

            // for(int i=0; i<n; i++){
            //     for(int j=0; j<m; j++)
            //         cout<<M[i][j]<<" ";
            //     cout<<endl;
            // }

            final = m*n;

            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {
                    if( M[i][j] == '0' )
                    {
                        if( i!=0 && M[i-1][j] == '0') Insert_Arista( (i-1)*10 + j , i*10 + j, 0);
                        if( j!=0 && M[i][j-1] == '0') Insert_Arista( i*10 + (j-1) , i*10 + j, 0);
                    }
                }
            }  
        }
        void newGraphFloodFill(int n, int m, vector<string> & M)
        {
            // for(int i=0; i<n; i++){
            //     for(int j=0; j<m; j++)
            //         cout<<M[i][j]<<" ";
            //     cout<<endl;
            // }

            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {
                    if( M[i][j] == '1' )
                    {
                        Insert_Vertex(i*10 + j);
                        if( i!=0 && M[i-1][j] == '1') Insert_Arista( (i-1)*10 + j , i*10 + j, 0);
                        if( j!=0 && M[i][j-1] == '1') Insert_Arista( i*10 + (j-1) , i*10 + j, 0);
                        if( j!=m-1 && M[i][j+1] == '1') Insert_Arista( i*10 + (j+1) , i*10 + j, 0);
                        if( i!=n-1 && M[i+1][j] == '1') Insert_Arista( (i+1)*10 + j , i*10 + j, 0);
                        if( i!=n-1 && j!=m-1 && M[i+1][j+1] == '1') Insert_Arista( (i+1)*10 + (j+1) , i*10 + j, 0);
                        if( i!=0 && j!=0 && M[i-1][j-1] == '1') Insert_Arista( (i-1)*10 + (j-1) , i*10 + j, 0);
                        if( i!=0 && j!=m-1 && M[i-1][j+1] == '1') Insert_Arista( (i-1)*10 + (j+1) , i*10 + j, 0);
                        if( i!=n-1 && j!=0 && M[i+1][j-1] == '1') Insert_Arista( (i+1)*10 + (j-1) , i*10 + j, 0);
                    }
                }
            }     
        }
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
        int islas()
        {
            not_visit();
            int islas = 0;
            for(auto it= m_grafo.begin(); it!=m_grafo.end(); ++it)
            {
                if(!it->m_Visit) { BFS(&(*it)); islas++; } 
            }
            return islas;
        }
        void BFS(Vertex<V,E> *p)
        {
            //cout<<"\n En BFS >> \n";
            //not_visit();
            queue<Vertex<V,E> *> cola;
            cola.push(p);
            p->m_Distancia = 0;
            while(!cola.empty())
            {
                p = cola.front();
                //cout<<" -> "<<p->m_Dato;
                cola.pop();
                for(auto it = p->m_Aristas.begin(); it!= p->m_Aristas.end(); ++it)
                    //cout<<" - "<<it->m_pVertices->m_Dato<<" "<<it->m_pVertices->visit;
                    if(!it->m_pVertices->m_Visit) {it->m_pVertices->m_Visit = true; cola.push(it->m_pVertices); it->m_pVertices->m_Distancia = p->m_Distancia + 1; }
            }
        }
        int pair_int(pair<int,int> _p)
        {
            int entero = _p.first*10 + _p.second;
            return entero;
        }
        pair<int,int> int_pair(int a)
        {
            pair<int,int> pairA;
            pairA = make_pair(a/10, a%10); 
            return pairA;
        }
        bool find(int n, list<V> B)
        {
            
            for(auto it= B.begin(); it!= B.end(); ++it)
                if(pair_int(*it) == n) return true;
            return false;
        }
        bool DFS()
        {
            cout<<"\n En DFS >> \n";
            std::unordered_set<V> black;
            std::queue<int> camino;
            for(auto it= m_grafo.begin(); it!=m_grafo.end(); ++it)
                if(black.find(it->m_Dato) == black.end())
                {
                    black.insert(it->m_Dato);
                    cout<<" -> "<<it->m_Dato;
                    camino.push(it->m_Dato);
                    return DFS_visit(&(*it), black, camino);
                }
            return false;
        }
        bool DFS_visit(Vertex<V,E>* _v, unordered_set<V>& _black, queue<V> _camino)
        {
            for(auto it2 = _v->m_Aristas.begin(); it2!=_v->m_Aristas.end(); ++it2)
                if(_black.find((it2->m_pVertices)->m_Dato) == _black.end())
                {
                    _black.insert((it2->m_pVertices)->m_Dato);
                    cout<<" -> "<<it2->m_pVertices->m_Dato;  
                    _camino.push(it2->m_pVertices->m_Dato);     
                    if(it2->m_pVertices->m_Dato == final) return true;     
                    return DFS_visit(it2->m_pVertices, _black, _camino);
                }
            return false;
        }
        void BFS()
        {
            cout<<"\n En BFS >> \n";
            int islas = 0;
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

};

int main()
{
    int n, m;
    cout<<" FILAS > ";cin>>n;
    cout<<" COLUMNAS > ";cin>>m;

    vector<string> Matriz(n);
    for(int i=0; i<n;i++)
        cin>>Matriz[i];

    /** EJERCICIO 1 **/
    Grafo<int, int> Caminos;
    Caminos.newGraphLaberinto(n,m,Matriz);
    
    Caminos.DFS();
    

    /** EJERCICIO 2 **/
    Grafo<int, int> Islas;
    Islas.newGraphFloodFill(n,m, Matriz);
    //Islas.Print(cout);

    cout<<"\n Islas> "<<Islas.islas();
}

