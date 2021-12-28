#include <iostream>
using namespace std;

template<class T>
class Nodo
{
   public:
       T  m_Dato;
       Nodo<T> * m_pAnt;
       
   public:
      Nodo(T d)
      { 
        m_Dato = d;
        m_pAnt = 0;
     }
};

template<class T>
class Pila
{
    private:
        Nodo<T> * m_pTop;
    public:
        
        Pila()
        {
           m_pTop = 0;
        }
        ~Pila()
        {
            while(!isEmpty()) { pop(); }
        }

        Pila(const Pila<T> &o){
            std::cout<<" EN CONSTRUCTOR COPIA ";
            this->m_pTop = 0;
            if( this != &o ){
                Nodo<T>* temp = o.m_pTop;
                while (temp){
                    this->push(temp->m_Dato);
                    temp = temp->m_pAnt;;
                }
            }
        }
        
        bool push(T d)
        {
            if(!m_pTop) { m_pTop = new Nodo<T>(d); return true; }
            Nodo<T> * p_tmp =  new Nodo<T>(d);          
            p_tmp->m_pAnt = m_pTop ;
            m_pTop = p_tmp;
            return true;
        }
        bool pop()
        {
            if(!m_pTop) return false;
            Nodo<T>* temp = m_pTop;
            m_pTop = m_pTop-> m_pAnt;
            delete temp;
            temp = nullptr;
            return true;
        }
        T top()
        {
            if(!m_pTop) return NULL;
            return m_pTop->m_Dato; 
        }


        void print(Nodo<T> * nod, int opc)
        {
            if(!nod) return;
            if(opc == 0) std::cout<<nod->m_Dato<<" "; // PRINT 
            print(nod->m_pAnt, opc);
            if (opc == 1)std::cout<<nod->m_Dato<<" "; // REVERSE PRINT
        }
        void print()
        {
            Nodo<T> *tmp= m_pTop;
            if(tmp) 
            { 
                int opc; cout<<" PRINT(0) O REVERSE_PRINT(1) ? ";cin>>opc; 
                print(tmp, opc); return;
            } 
            std:cout<<"Esta vacio \n";
        }

        void Print_Nuevo()
        {
            if(isEmpty()) { cout << endl; return; }
            Pila<T> copy(*this);
            while(copy.m_pTop)
            {
                cout<<copy.top()<<" ";
                copy.pop();
            }
        }

};
