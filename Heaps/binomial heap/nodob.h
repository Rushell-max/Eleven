#ifndef NODOB_H
#define NODOB_H
#include <list>

template <class T>
class NodoB
{
public:
    std::list<NodoB<T> *> m_pSons;
    int m_Grado;
    T m_Dato;
    NodoB<T> *m_Padre;

public:
    NodoB(T);
    void autodestruir(NodoB<T>*&);
};

template <class T>
NodoB<T>::NodoB(T d){
    m_Grado = 0;
    m_Dato = d;
    m_Padre = 0;
}

template <class T>
void NodoB<T>::autodestruir(NodoB<T>*&p)
{
    if(!p)
        return;
    if(p->m_pSons.size()==0)
        delete p;
    else
    {
        typename std::list<NodoB<T>*>::iterator it = m_pSons.begin();
        for(;it!=m_pSons.end();++it)
            (*it)->autodestruir(*it);
    }

}

#endif