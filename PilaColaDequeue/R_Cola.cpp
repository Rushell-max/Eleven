#include <iostream>
using namespace std;

template<class T>
class Nodo
{
   public:
       T  m_Dato;
       Nodo<T> * m_pSig;
       
   public:
      Nodo(T d)
      { 
        m_Dato = d;
        m_pSig = 0;
     }
};

template<class T>
class Cola
{
    private:
        Nodo<T> * m_pFirst;
        Nodo<T> * m_pLast;
    public:
        Cola()
        {
            m_pFirst = 0;
            m_pLast = 0;
        }

        bool push(T valor)
        {
            if(!m_pFirst) { m_pFirst = new Nodo<T>(d); m_pLast = m_pFirst; return true; }     
            m_pLast->m_pSig = new Nodo<T>(d); 
            m_pLast = m_pLast->m_pSig;
            return true;
        }
        bool pop()
        {
            if(!m_pFirst) return false;
            if(m_pFirst == m_pLast) 
            { 
                delete m_pFirst; 
                m_pFirst = nullptr;
                return true;
            }
            Nodo<T>* temp = m_pFirst;
            m_pFirst = m_pFirst-> m_pSig;
            delete temp;
            return true;
        }
        T top()
        {
            if(!m_pFirst) return NULL;
            return m_pFirst->m_Dato;
        }
};
