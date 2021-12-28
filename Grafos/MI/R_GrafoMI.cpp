#include <iostream>
#include <list>
using namespace std;

class Grafo
{
    public:
        int m_vertices;
        int m_aristas;
        int count;
        int ** m_MatrizIncidencia;
        list<pair<int, int>> m_enlaces;
    public:
        Grafo() 
        {
            m_MatrizIncidencia = 0;
            m_vertices = 0;
            m_aristas = 0;
            count = 0;
        }
        void newGraph(int v, int a)
        {
            m_vertices = v;
            m_aristas = a;
            m_MatrizIncidencia = new int *[v]; 
            for(int i=0; i<v;i++)
                m_MatrizIncidencia[i]=new int[a];

            for(int i = 0; i<v; i++)
                for(int j = 0; j<a; j++)
                    m_MatrizIncidencia[i][j] = 0;
        }
        void addEdge(int v, int w)
        {
            m_enlaces.push_back(make_pair(v,w));
            m_MatrizIncidencia[v][count] = -1;
            m_MatrizIncidencia[w][count] = +1;
            count++;
        }
        list<int> adj(int v)
        {
            list<int> A;
            for(auto it = m_enlaces.begin(); it!= m_enlaces.end(); ++it)
                if((*it).first == v) A.push_back((*it).second);
                else if((*it).second == v)A.push_back((*it).first);
        }
        int outdegree(int v)
        {
            int num = 0;
            for(auto it = m_enlaces.begin(); it!= m_enlaces.end(); ++it)
                if((*it).first == v) 
                    num++;
            return num;       
        }
        int indegree(int v)
        {
            int num = 0;
            for(auto it = m_enlaces.begin(); it!= m_enlaces.end(); ++it)
                if((*it).second == v) 
                    num++;
            return num;   
        }
};

int main()
{

}