#ifndef BHEAP_H
#define BHEAP_H
#include "nodob.h"
#include <list>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std; 
template <class T>
class BHeaps
{
    private:
        std::list<NodoB<T> *> m_Roots;
        NodoB<T> *m_Min;

    private:
        NodoB<T> *Unir(NodoB<T> *p, NodoB<T> *q);       // falta julio
        void Compactar();                               // falta alejandro

    public:
        BHeaps(){}
        ~BHeaps();
        void Insert(T d);                       // O(log(n))
        void Delete(NodoB<T> *e);               // O(log(n))
        void Decrease_key(NodoB<T> *&p, T val); // O(log(n))
        void Extrac_Min();                      // O(log(n))
        void recorrer(ostream &, NodoB<T>*);
        void Show_Dot(ostream &);                                // falta samuel
        T GetMin(); // O(1)

        void print();
};

template <class T>
BHeaps<T>::~BHeaps(){
    typename std::list<NodoB<T>*>::iterator it=m_Roots.begin();
    for(;it!=m_Roots.end();++it)
        (*it)->autodestruir(*it);
    std::cout<<"se destruyo correctamente\n";
}

template <class T>
NodoB<T>* BHeaps<T>::Unir(NodoB<T> *p, NodoB<T> *q){
    // Unir dos arboles binomiales de grado k-1, en un arbol binomial de grado k
    // Asegurar que el puntero al padre se actualize
    if(q -> m_Dato > p -> m_Dato) {
		q -> m_Padre = p;
		(p -> m_pSons).push_front(q);
		p -> m_Grado ++;
		return p;
    }
    p -> m_Padre = q;
    (q -> m_pSons).push_front(p);
    q -> m_Grado ++;
    return q;
}

template <class T>
void BHeaps<T>::Compactar(){
    // Verificar que todos los nodos de la raiz tengan un grado distinto.
    // En caso tengan el mimo grado, entonces llama  a Unir
    // Colocar el puntero al menor en el menor de los nodos raiz
    if( m_Roots.size() == 1 )
        m_Min = *(m_Roots.begin());
    else if( m_Roots.size() > 1 ){
        typename std::list<NodoB<T>* >::iterator last = --(m_Roots.end());
        std::vector<NodoB<T>* > grades(20,nullptr);
        typename std::list<NodoB<T>* >::iterator p = m_Roots.begin();
        for( ; p!=m_Roots.end() ; ++p )
        {
            if( grades[(*p)->m_Grado] == nullptr )
                grades[(*p)->m_Grado] = *p;
            else
            {
                while( grades[(*p)->m_Grado] != nullptr )
                {
                    NodoB<T>* q = grades[(*p)->m_Grado];
                    grades[(*p)->m_Grado] = 0;
                    NodoB<T>* u = Unir(*p,q);
                    m_Roots.remove(q);
                    *p = u;
                }
                grades[(*p)->m_Grado] = *p;
            }
        }
        typename std::list<NodoB<T>* >::iterator it = m_Roots.begin();
        m_Min = *it;
        for( ; it!=m_Roots.end() ; ++it )
            if( (*it)->m_Dato < m_Min->m_Dato )
                m_Min = *it;
    }
}

template <class T>
void BHeaps<T>::Insert(T d){
    NodoB<T> *pNew = new NodoB<T>(d); // O(1)
    m_Roots.push_front(pNew);         // O(1)
    Compactar();                      // O(log(n))
    cout<<"-------ELEMENTO " << d << " INSERTADO CORRECTAMENTE-------\n";
}

template <class T>
void BHeaps<T>::Delete(NodoB<T> *e){
    Decrease_key(e, m_Min->dato - 1);
    m_Min = e;                       
    Extrac_Min();                   
}

template <class T>
void BHeaps<T>::Decrease_key(NodoB<T> *&p, T val){
    p->m_Dato = val; // O(1)
    while (p->m_Padre && p->m_Dato < p->m_Padre->m_Dato)
    {
        swap(p->m_Dato, p->m_Padre->m_Dato);
        p = p->m_Padre;
    } // O(log(n))

    // Nota: En caso que val sea menor que el mínimo, actualizar el puntero al mínimo
    if( p->m_Dato < m_Min->m_Dato )
        m_Min = p;
}

template <class T>
T BHeaps<T>::GetMin(){
    return m_Min->m_Dato; // O(1)
}

template <class T>
void BHeaps<T>::Extrac_Min(){
    typename std::list<NodoB<T> *>::iterator it;
    it = m_Min->m_pSons.begin();
    for (; it != m_Min->m_pSons.end(); ++it)
        m_Roots.push_front(*it); 
    m_Roots.remove(m_Min); 
    Compactar();   
}

template<class T>
void BHeaps<T>::recorrer(ostream &os, NodoB<T>* node){
    os << node->m_Dato << "[color = white fontcolor = white label = \"<f0> | {{<f1> " << node->m_Dato << "} | G=" << node->m_Grado << "} | <f2> \" style = filled fillcolor = \"#AE2115\" ]";
    for(NodoB<T>*raiz : node->m_pSons){
        os << node->m_Dato << ":f0 -> " << raiz->m_Dato << ":f1 [color = \"#AE2115\"];\n";
        recorrer(os,raiz);
    }
    return;
}

template <typename T>
void BHeaps<T>::Show_Dot(ostream &os){
    os << "digraph G {\n";
    os << "rankdir=\"TB\"\n";
    os << "label= \"Binary Heap\";\n";
    os << "fontcolor = white\n";
    os << "bgcolor = \"black\"\n";
    os << "node [shape = record];\n";
    for(NodoB<T>* raiz:m_Roots)
        recorrer(os,raiz);
    os << "}" << endl;
    cout << "-------ARCHIVO .DOT GENERADO-------\n";
}

#endif