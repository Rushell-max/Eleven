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
};

template <class V, class E>
class Grafo
{
    public:
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

};
int main()
{

    /*Grafo<string, int> G;
    G.Insert_Vertex("Lima");
    G.Insert_Vertex("Arequipa");
    G.Insert_Vertex("Cuzco");
    G.Insert_Vertex("Puno");
    G.Insert_Vertex("Ica");

    G.Insert_Arista("Arequipa", "Cuzco", 250);
    G.Insert_Arista("Arequipa", "Puno", 200);
    G.Insert_Arista("Lima", "Arequipa", 160);
    G.Insert_Arista("Lima", "Ica", 100); */

    Grafo<int, int> G;
    G.Insert_Vertex(1);
    G.Insert_Vertex(2);
    G.Insert_Vertex(3);
    G.Insert_Vertex(4);
    G.Insert_Vertex(5);
    G.Insert_Vertex(6);

    G.Insert_Arista(5, 6, 0);
    G.Insert_Arista(1, 2, 0);
    G.Insert_Arista(1, 3, 0);
    G.Insert_Arista(2, 3, 0);
    G.Insert_Arista(2, 4, 0);
    G.Insert_Arista(3, 4, 0);
    G.Insert_Arista(3, 5, 0);
    
    G.Print(cout);
    G.DFS();
    G.BFS();
    G.Print(cout);
    G.DFS(&G.m_grafo.front());
    G.BFS(&G.m_grafo.front());
    G.Print(cout);

    return 1;
}