#include <iostream>
#include <list>
#include <unordered_set>
#include <queue>
using namespace std;

class Grafo
{
    public:
        int m_vertices;
        int ** m_MatrizAdyacencia;
    public:
        Grafo() 
        {
            m_MatrizAdyacencia = 0;
            m_vertices = 0;
        }
        void newGraph(int v)
        {
            m_vertices = v;
            m_MatrizAdyacencia = new int *[v]; 
            for(int i=0; i<v;i++)
                m_MatrizAdyacencia[i]=new int[v];

            for(int i = 0; i<v; i++)
                for(int j = 0; j<v; j++)
                    m_MatrizAdyacencia[i][j] = 0;
        }
        void addEdge(int v, int w)
        {
            m_MatrizAdyacencia[v][w] = 1;
        }
        list<int> adj(int v)
        {
            list<int> A;
            for(int i=0; i<m_vertices; i++)
                if(m_MatrizAdyacencia[v][i] == 1 || m_MatrizAdyacencia[i][v] == 1) A.push_back(i);
            return A;
        }
        int outdegree(int v)
        {
            int num = 0;
            for(int i=0; i<m_vertices; i++)
                if(m_MatrizAdyacencia[v][i] == 1) num++;
            return num;       
        }
        int indegree(int v)
        {
            int num = 0;
            for(int i=0; i<m_vertices; i++)
                if(m_MatrizAdyacencia[i][v] == 1) num++;
            return num;     
        }
        void reverse()
        {
            for(int i= 0; i<m_vertices; i++)
                for(int j=0; j<i; j++){
                    int aux = m_MatrizAdyacencia[j][i];
                    m_MatrizAdyacencia[j][i] = m_MatrizAdyacencia[i][j];
                    m_MatrizAdyacencia[i][j] = aux;
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
                if( m_MatrizAdyacencia[_v][i] == 1 /**&& i != _v**/ && _black.find(i) == _black.end())
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
                    if( m_MatrizAdyacencia[show(cont, black)][i] == 1 && /** i != show(cont, black) && **/ !find(i, black))
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
                    cout<<" "<<m_MatrizAdyacencia[i][j];
                }
                cout<<endl;
            }
        }
};

int main()
{
    Grafo A;
    A.newGraph(5);

    A.addEdge(0,1);
    A.addEdge(1,1);
    A.addEdge(1,3);
    A.addEdge(3,1);
    A.addEdge(3,2);
    A.addEdge(3,3);
    A.addEdge(4,3);

    A.Print();
    A.BFS();
    A.DFS();
}