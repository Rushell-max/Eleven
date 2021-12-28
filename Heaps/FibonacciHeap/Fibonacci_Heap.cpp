#include<iostream>
#include<list>
#include <math.h>
#include<fstream>
using namespace std;

template<class T>
class NodoF
{
    public:
       int                  m_Grado;
       T                    m_Dato;
       NodoF<T>  *          m_Padre;
       list< NodoF<T> * >   m_Sons;
       bool                 m_Color;

       NodoF(T d)
       {
           m_Color = false;
           m_Dato = d;
           m_Padre = 0;
           m_Grado = 0;
       }
};

template<class T>
class Fibonaci_Heap
{
     public:
     //private:
       list< NodoF<T> * >  m_Roots;
       NodoF<T>         *  m_pMin;
     private:
       void Compactar(); // O(log(n))
       NodoF<T>  * Unir(NodoF<T> * p ,NodoF<T> * q );  // O(1)
     public:
      Fibonaci_Heap(){ m_pMin = 0; };
      ~Fibonaci_Heap(){};
      /**************************************/
      void Insert(T d); // O(1))
      void Extrac_Min(); // O(log(n))
      void Delete(NodoF<T> * e); // O(log(n))
      void Decrease_Key(NodoF<T> * e, T val); // O(1)
      NodoF<T> * GetMin();// O(1)
      void showList();
      void ShowDot(NodoF<T>* actual, ostream& out);
      void ShowDot(string filename);
      /**************************************/
};

template<class T>
void Fibonaci_Heap<T>::showList()
{
    typename list <NodoF<T>*>::iterator it = m_Roots.begin();
    while(it != m_Roots.end()) {
        cout << (*it)->m_Dato << "[" << (*it)->m_Grado << "]";
        //for(auto it=(*it)->m_Sons.begin(); it!=(*it)->m_Sons.end(); ++it)
          //  cout<<
        cout << " -> ";
        it++;
    }
    cout << "END";
    cout << endl;
}

template<class T>
void Fibonaci_Heap<T>::Insert(T d) // O(1)
{
    NodoF<T> * pNew = new NodoF<T>(d);
    if (!m_pMin || d < m_pMin->m_Dato) m_pMin = pNew;
    m_Roots.push_back(pNew);
}

template<class T>
void Fibonaci_Heap<T>::Extrac_Min() // O(log(n))
{
    if(!m_pMin) return;
    for(auto it = m_pMin->m_Sons.begin(); it!=m_pMin->m_Sons.end(); ++it)
    {
        (*it)->m_Color = false; 
        (*it)->m_Padre = 0;
        m_Roots.push_back(*it);
    }

    m_Roots.remove(m_pMin);
    Compactar();

    m_pMin = m_Roots.front();
    for(auto it = m_Roots.begin(); it!=m_Roots.end(); ++it)
        if ((*it)->m_Dato < m_pMin->m_Dato)  m_pMin = (*it);
}

template<class T>
void Fibonaci_Heap<T>::Delete(NodoF<T> * e) // O(log(n))
{
   Decrease_Key(e, m_pMin->m_Dato-1);
   m_pMin = e; //!
   Extrac_Min();
}

template<class T>
void Fibonaci_Heap<T>::Decrease_Key(NodoF<T> * e, T val) // O(1)
{
    e->m_Dato = val; 
    if (e->m_Dato < m_pMin->m_Dato && !e->m_Padre) m_pMin = e; //!!
    if (e->m_Padre && e->m_Padre->m_Dato > val) {
        do{
            e->m_Color = false;
            e->m_Padre->m_Sons.remove(e);
            e->m_Padre->m_Grado--;
            m_Roots.push_front(e);
            e = e->m_Padre;
        }while(e->m_Padre->m_Color);

        if(e->m_Padre) e->m_Color = true;
        else e->m_Color = false;
    } 
}

template<class T>
NodoF<T> * Fibonaci_Heap<T>::GetMin()// O(1)
{
    return m_pMin;
}


// Log(n)
template<class T>
void Fibonaci_Heap<T>::Compactar() // O(log(n))
{
    int size = 10000;
    NodoF<T> * vec[size];
    for (int i = 0; i < size; i++)  vec[i] = 0;

    auto it = m_Roots.begin();
    while (it != m_Roots.end())
    {
        int grado = (*it)->m_Grado;

        if (!vec[grado]) { vec[grado] = *it; it++; }
        else
        {
            NodoF<T> * r = Unir(*it,vec[grado]);
            m_Roots.remove(vec[grado]);
            it = this->m_Roots.erase(it);
            m_Roots.push_back(r);
            vec[grado] = 0;
        }
    }
}

// O(1)
template<class T>
NodoF<T>  * Fibonaci_Heap<T>::Unir(NodoF<T>* p ,NodoF<T>* q ) // O(1)
{
    if (p->m_Dato > q->m_Dato)
        swap(p, q);
    p->m_Sons.push_back(q);
    q->m_Padre = p;
    p->m_Grado++;
    return p;
}

template <class T>
void Fibonaci_Heap<T>::ShowDot(NodoF<T>* actual, ostream &out) {
    if (!actual) return;
    out << actual->m_Dato << "[label = \"{ {Grado: " << actual->m_Grado << "} | <f1> " << actual->m_Dato << "} \"];" << endl;
    for(auto it = actual->m_Sons.begin(); it != actual->m_Sons.end(); ++it)
    {
        out << actual->m_Dato << " -> " << (*it)->m_Dato << ";" << endl;
        ShowDot((*it), out);
    }
}

template<class T>
void Fibonaci_Heap<T>::ShowDot(string filename) {
    ofstream out (filename);
    out << "digraph G {" << endl;
    out << "label= \"Binomial Heap\";" << endl;
    out << "node [shape = record];" << endl;
    for(auto it = m_Roots.begin(); it != m_Roots.end(); ++it) ShowDot((*it), out);
    out << "}";
    out.close();

    //system("cd .. && cd .. && cd .. && cd .. && dot -Tjpg -O fibo_heap.dot && fibo_heap.dot.jpg");
}

int main()
{
    Fibonaci_Heap<int>heap_f;
    for(long i = 1; i<=10000; i++) {
        heap_f.Insert(i);
    }
    for(int i=0; i<9999; i++)
    {
        cout<<heap_f.GetMin()->m_Dato<<" ";
        heap_f.Extrac_Min();
    }
    heap_f.ShowDot("...");
    return 1;
}
