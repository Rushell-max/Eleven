#include <iostream>
#include <list>
using namespace std;

class Grafo
{
    public:
        int m_NumVertices;
        list<list<int>> m_vertices;
    public:
        Grafo() 
        {
            m_NumVertices = 0;
        }
        void newGraph(int v)
        {
            m_NumVertices = v;
            list<int> m_aristas;
            for(int i=0; i<v; i++) {
                m_vertices.push_back(m_aristas);
            }
            int count=0;
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
            {
                (*it).push_back(count);
                count++;
            }
        }
        void addEdge(int v, int w)
        {
            bool existe = false;
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
                if((*it).front() == w)
                    existe = true;
            if(existe)
                for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
                    if((*it).front() == v) 
                        (*it).push_back(w);
        }
        list<int> adj(int v)
        {
            list<int>A;
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
                if((*it).front() == v) {
                    auto it1 = (*it).begin();
                    for(it1++; it1 != (*it).end(); ++it1)
                        A.push_back(*it1);
                }
                else if((*it).front() != v)
                    for(auto it1 = (*it).begin(); it1 != (*it).end(); ++it1)
                        if((*it1) == v) A.push_back((*it).front());
            return A;    
        }
        int outdegree(int v)
        {
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
                if((*it).front() == v)
                    return ((*it).size())-1;
            return 0;
        }
        int indegree(int v)
        {
            int num = 0;
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
                if((*it).front() != v)
                    for(auto it1 = (*it).begin(); it1 != (*it).end(); ++it1)
                        if((*it1) == v) num++; 
            return num;
        }
        Grafo reverse()
        {
            Grafo B;
            B.newGraph(m_NumVertices);
            int count = 0;
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it){
                auto it1 = (*it).begin()++; 
                for(it1++; it1 != (*it).end(); ++it1)
                    B.addEdge((*it1), (*it).front());
            }
            return B;
        }
        void print()
        {
            for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it){
                for(auto it1 = (*it).begin(); it1 != (*it).end(); ++it1)
                    cout<<" "<<(*it1)<<" ";
                cout<<"\n";
            }
        }
};

int main()
{
    Grafo A;
    A.newGraph(5);
    A.addEdge(1,2);
    A.addEdge(1,4);
    A.addEdge(2,3);
    A.addEdge(0,4);
    A.addEdge(0,1);
    A.addEdge(3,1);
    A.addEdge(3,4);
    A.addEdge(4,2);
    A.print();

    list<int> lista;
    lista = A.adj(4);
    for(auto it = lista.begin(); it!=lista.end(); ++it)
        cout<<*it<<"--";
    
    cout<<A.outdegree(4)<<"\n";
    cout<<A.indegree(4)<<"\n";
    cout<<A.outdegree(1)<<"\n";

    Grafo B;
    B = A.reverse();

    B.print();

}