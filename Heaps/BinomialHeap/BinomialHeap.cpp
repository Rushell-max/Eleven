#include<iostream>
#include<list>
#include<fstream>
using namespace std;

template<class T>
class NodoB
{
    public:
       int                  m_Grado;
       T                    m_Dato;
       NodoB<T>  *          m_Padre;
       list< NodoB<T> * >   m_Sons;

       NodoB(T d)
       {
           m_Dato = d;
           m_Grado = 0;
           m_Padre = 0;
       } 
};

template<class T>
class Binomial_Heap
{
     private:
       list< NodoB<T> * >  m_Roots;
       NodoB<T>         *  m_pMin;
     private:
       void Compactar(); // O(log(n))
       void Unir(NodoB<T> * p ,NodoB<T> * q );  // O(1)
     public:
      Binomial_Heap(){ m_pMin = 0; };
      ~Binomial_Heap(){};
      /**************************************/
      void Insert(T d); // O(log(n))
      void Extrac_Min(); // O(log(n))
      void Delete(NodoB<T> * e); // O(log(n))
      void Delete(T d); // O(log(n))
      void Decrease_Key(NodoB<T> * e, T val); // O(log(n))
      NodoB<T> * GetMin();// O(1)
      void Show_Dot(string filename);
      void Show_Sons_Dot(list< NodoB<T> * > , ostream &);
      /**************************************/
      NodoB<T> * BuscarNodosRaices(T d); // O(1)
      NodoB<T> * BuscarNodosHijos(list< NodoB<T> * >   m_Sons, T d);

};


template<class T>
void Binomial_Heap<T>::Insert(T d) // O(log(n))
{
    NodoB<T> * pNew = new NodoB<T>(d);
    m_Roots.push_front(pNew);
    if(!m_pMin || pNew->m_Dato < m_pMin) m_pMin = pNew;
    Compactar();
}

template<class T>
void Binomial_Heap<T>::Extrac_Min() // O(log(n))
{
    typename list<NodoB<T>*>::iterator it = m_pMin->m_Sons.begin();
    for(; it != m_pMin->m_Sons.end(); it++)
           m_Roots.push_front(*it);
    m_Roots.remove(m_pMin); // O(log(n))
    Compactar();  // O(logn)
    
    m_pMin = m_Roots.front();
    it = m_Roots.begin();
    for(; it != m_Roots.end(); it++) if((*it)->m_Dato < m_pMin->m_Dato) m_pMin = (*it);
}

template<class T>
void Binomial_Heap<T>::Delete(NodoB<T> * e) // O(log(n))
{
    Decrease_Key(e,m_pMin->m_Dato - 1);
    m_pMin = e;
    Extrac_Min();
}

template<class T>
void Binomial_Heap<T>::Delete(T d) 
{
    NodoB<T> *p_aux = BuscarNodosRaices(d);
    if(p_aux) Delete(p_aux);
}

template<class T>
NodoB<T>  *  Binomial_Heap<T>::BuscarNodosRaices(T d) // O(1)
{
    for(auto it = m_Roots.begin(); it != m_Roots.end(); it++)
    {
        if((*it)->m_Dato == d) return (*it);
        if(!(*it)->m_Sons.empty() && (*it)->m_Dato < d)
        {
            NodoB<T>* aux = BuscarNodosHijos((*it)->m_Sons, d); 
            if(aux) return aux;
        } 
    }
    return NULL;
}

template<class T>
NodoB<T> * Binomial_Heap<T>::BuscarNodosHijos(list<NodoB<T>*> m_Sons, T d) // O(1)
{
    typename list< NodoB< T>  * >::iterator it = m_Sons.begin();
    for(; it != m_Sons.end(); it++)
    {
        if((*it)->m_Dato == d) return (*it);
        if(!(*it)->m_Sons.empty()  && (*it)->m_Dato < d) {
            NodoB<T>* aux = BuscarNodosHijos((*it)->m_Sons , d);
            if(aux) return aux;    
        }
    }
    return NULL;
}

template<class T>
void Binomial_Heap<T>::Decrease_Key(NodoB<T> * e, T val) // O(log(n))
{
    e->m_Dato = val;
    while(e->m_Padre && e->m_Padre->m_Dato  >  e->m_Dato)
    {
        swap( e->m_Dato,e->m_Padre->m_Dato);
        e = e->m_Padre;
    }
}

template<class T>
NodoB<T> * Binomial_Heap<T>::GetMin()// O(1)
{
    return m_pMin;
}

// Log(n)
template<class T>
void Binomial_Heap<T>::Compactar() // O(log(n)) //!!!!!!!!!!!!!!!!
{
    if(m_Roots.size() == 1) return;
    typename list< NodoB< T>  * >::iterator it1 = m_Roots.begin();
    typename list< NodoB< T>  * >::iterator it2 = m_Roots.begin();
    typename list< NodoB< T>  * >::iterator it3 = m_Roots.end();
    NodoB<T> * tmp, * tmp2;
    it3--;
    for(; it1!=m_Roots.end(); it1++)
    {
        tmp2 = *it2;
        tmp = *it1;
        if(tmp->m_Grado == tmp2->m_Grado && tmp!=tmp2){
            Unir(tmp, tmp2);
            it1=m_Roots.begin();
            it2=m_Roots.begin();
            it3=m_Roots.end();
            it3--;
            tmp=*it1;
            tmp2=*it2;
        }
        if(it2!=it3 && it3==it1){
            it2++;
            it1=m_Roots.begin();
        }
    }
    it3=m_Roots.begin();
    m_pMin=*it3;
    for(;it3!=m_Roots.end();++it3){
        tmp=*it3;
        tmp->m_Padre=0;
        if(m_pMin->m_Dato>tmp->m_Dato){
            m_pMin=tmp;
        }
    }
}

// O(1)
template<class T>
void Binomial_Heap<T>::Unir(NodoB<T> * p ,NodoB<T> * q ) // O(1) ///!!!!! 
{
    if(p->m_Dato < q->m_Dato) {p->m_Sons.push_front(q); p->m_Grado++; q->m_Padre = p; m_Roots.remove(q); }
    else { q->m_Sons.push_front(p); q->m_Grado++; p->m_Padre = q; m_Roots.remove(p); }
}

template<class T>
void Binomial_Heap<T>::Show_Sons_Dot(list< NodoB<T> * >   m_Sons, ostream &o)
{
    typename list< NodoB< T>  * >::iterator it = m_Sons.begin();
    for(; it != m_Sons.end(); it++)
    {
        o<<(*it)->m_Dato<<";"<<endl;
        o<<(*it)->m_Padre->m_Dato<<" -> "<<(*it)->m_Dato<<";"<<endl;
        if(!(*it)->m_Sons.empty()) Show_Sons_Dot((*it)->m_Sons, o);
    }
}

template<class T>
void Binomial_Heap<T>::Show_Dot(string filename)
{
    ofstream file;
    file.open(filename);
    file<<" digraph G {"<<endl;
    typename list< NodoB< T>  * >::iterator it = m_Roots.begin();
    for(; it != m_Roots.end(); it++)
    {
        file<<(*it)->m_Dato<<";"<<endl;
        if(!(*it)->m_Sons.empty()) Show_Sons_Dot((*it)->m_Sons, file);
    }
    file<<"}"<<endl;
    file.close();
}

int main()
{
    Binomial_Heap<int> A;
    int a;
    for(int i=0; i<13; i++)
    {
        cout<<" Insertando > "; cin>>a;
        A.Insert(a);
    }
    string filename ("...");
    A.Show_Dot(filename);

    A.Extrac_Min();

    A.Show_Dot(filename);
    return 1;
}