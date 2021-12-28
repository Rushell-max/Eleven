#include <iostream>
using namespace std;
 
template<class T>
class Nodo
{
   public:
       T  m_Dato;
       Nodo<T> * m_pSig;
       Nodo<T> * m_pAnt;
       
   public:
      Nodo(T d)
      {
         m_Dato = d;
         m_pSig = nullptr;
         m_pAnt = nullptr;
      }
};

template<class T>
class Dequeue
{
    private:
         Nodo<T> * m_pHead;
         Nodo<T> * m_pTale;
    
    public:  

        bool pushFront(T d)
        {
            if(!m_pHead) { m_pHead = new Nodo<T> (d); m_pTale = m_pHead; return true;}
            Nodo<T> * p_tmp = new Nodo<T> (d);
            p_tmp->m_pSig = m_pHead;
            m_pHead->m_pAnt = p_tmp;
            m_pHead = p_tmp;
            return true;
        }
        bool pushBack(T d)
        {
            if(!m_pHead) { m_pHead = new Nodo<T> (d); m_pTale = m_pHead; return true;}
            m_pTale->m_pSig = new Nodo<T> (d);
            m_pTale = m_pTale->m_pSig;
            return true;
        }
        T popFront()
        {
            if(!m_pHead) return NULL;
            Nodo<T>* p_tmp = m_pHead->m_pSig;
            p_tmp->m_pAnt = nullptr;
            T value = m_pHead->m_Dato;
            delete m_pHead;
            m_pHead = nullptr;
            m_pHead = p_tmp;
            return value;
        }
        T popBack()
        {
            if(!m_pHead) return NULL;
            T value;
            if(!m_pHead->m_pSig) { value = m_pHead->m_Dato; delete m_pHead; m_pHead = 0; return value;}
            Nodo<T> * p_tmp = m_pTale->m_pAnt;
            value = m_pTale->m_Dato;
            delete m_pTale;
            m_pTale = nullptr;
            m_pTale = p_tmp;
            p_tmp->m_pSig = nullptr;
            return value; 
        }
};