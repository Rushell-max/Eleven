
// UNSA - Ciencia de la Computación
// Algoritmos y Estructura de Datos
// Martes 12 de Octubre del 2021
// 7 : 15 de la mañana
// Primer examen parcial
// NOMBRES: RUSHELL VANESSA
// APELLIDOS: ZAVALAGA OROZCO
// Link de Respuetas: https://docs.google.com/forms/d/e/1FAIpQLSdQkwgHGmSo_4BSOgXAjOojj8MgK41pqCQCwWjTL7dkw8Yy1w/viewform

#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

template<class T>
class Nodo
{
public:
    T m_Dato;
    Nodo<T> * m_pSon[3];
    
    
    Nodo(T d)
    {
        m_Dato = d;
        // Hijo Izquierdo
        m_pSon[0] = 0;
        // Hijo Derecho
        m_pSon[1] = 0;
        // Padre
        m_pSon[2] = 0;
        
    }
    
};

template<class T>
class Binary_Tree
{
public:
      Nodo<T> * m_pRoot;
public:
    Binary_Tree():m_pRoot(0){};
    
    bool insert(T d) 
    {
        return insert(d, m_pRoot, NULL);
    }
    bool insert(T d, Nodo<T> *&p, Nodo<T> *padre)
    {
        if(!p) { p = new Nodo<T>(d); p->m_pSon[2] = padre; return true;}
        if(d == p->m_Dato) return false;
        return insert(d, p->m_pSon[p->m_Dato > d], p);
    }
    int get_Nivel(T d) 
    {
        if(!m_pRoot) return -1;
        Nodo<T> * p_tmp = m_pRoot;
        int nivel = 0;
        while (p_tmp)
        {
            if(p_tmp->m_Dato == d)return nivel;
            p_tmp = p_tmp->m_pSon[p_tmp->m_Dato > d];
            nivel++;
        }
        return -1;
    }
    Nodo<T>* findIT(T d)
    {
        if(!m_pRoot) return NULL;
        Nodo<T> *p_tmp = m_pRoot;
        while(p_tmp)
        {
            if(p_tmp->m_Dato == d) return p_tmp;
            p_tmp = p_tmp->m_pSon[p_tmp->m_Dato > d];
        }
        return NULL;
    }
    Nodo<T> * get_Ancestro(T d, int k)
    {
        return get_Ancestro(d, findIT(d), k, 0);
    }
    Nodo<T> * get_Ancestro(T d, Nodo<T>*p, int nivel, int count)
    {
        if(!p) return NULL;
        if(nivel == count) { return p;}
        count++;
        return get_Ancestro(d, p->m_pSon[2], nivel, count);
    }
    void Pila()
    {
        stack<T> pila;
        insertarPila(m_pRoot, pila);
        while (!pila.empty()) {
            cout<<pila.top()<<" ";
            pila.pop();
        }
    }
    void insertarPila(Nodo<T> *r, stack<T>& pila)
    {
        if(!r) return;
        insertarPila(r->m_pSon[1], pila);
        pila.push(r->m_Dato);
        insertarPila(r->m_pSon[0], pila);
    }
    void Print_Hojas()
    {
        Print_Hojas(m_pRoot);
    }
    void Print_Hojas(Nodo<T> * r)
    {
        if(!r) return;
        if(!r->m_pSon[0] && !r->m_pSon[1]) cout<<r->m_Dato<<" "; 
        Print_Hojas(r->m_pSon[0]);
        Print_Hojas(r->m_pSon[1]);
    }

    int Get_Altura(Nodo<T>*p)
    {
        return Get_Altura(p, 0);
    }
    int Get_Altura(Nodo<T>*p, int nivel)
    {
        if(!p){return nivel;}
        nivel++;
        if(Get_Altura(p->m_pSon[0], nivel) > Get_Altura(p->m_pSon[1], nivel)) return Get_Altura(p->m_pSon[0], nivel);
        return Get_Altura(p->m_pSon[1], nivel);
    }

    void Print()
    {
        Print(m_pRoot);
    }
    void Print(Nodo<T> *r)
    {
        if(!r) return;
        cout<<" dir> "<<r<<" _ data> "<<r->m_Dato<<" _ dirdirLEFT> "<<&r->m_pSon[0]<<" _ dirdirRIGHT> "<<&r->m_pSon[1]<<" _ dirdirPADRE> "<<&r->m_pSon[2]<<" _ dirLEFT> "<<r->m_pSon[0]<<" _dirRIGHT> "<<r->m_pSon[1]<<" _dirPADRE> "<<r->m_pSon[2]<<"\n";
        Print(r->m_pSon[0]);
        Print(r->m_pSon[1]);
    }


    void RDI(Nodo<T>*&p)
    {
        Nodo<T> * q = p->m_pSon[1];
        Nodo<T> * r = q->m_pSon[0];

        p->m_pSon[1] = r->m_pSon[0];
        q->m_pSon[0] = r->m_pSon[1];

        r->m_pSon[1] = q;
        r->m_pSon[0] = p;

        if(r->FE == 0) p->FE = q->FE = 0;
        else if(r->FE == 1) {q->FE = 1; p->FE = 0;}
        else if(r->FE == -1) {q->FE = 0; p->FE = 1;}
    }
    void RID(Nodo<T>*&p)
    {
        Nodo<T> * q = p->m_pSon[0];
        Nodo<T> * r = q->m_pSon[1];

        p->m_pSon[0] = r->m_pSon[1];
        q->m_pSon[1] = r->m_pSon[0];

        r->m_pSon[0] = q;
        r->m_pSon[1] = p;

        
        if(r->FE == 0 && !p->m_pSon[0]) p->FE = q->FE = 0;
        else if(r->FE == 1) {q->FE = 0; p->FE = -1;}
        else if(r->FE == -1) {q->FE = 1; p->FE = 0;}
        else if(r->FE == 0) {q->FE = 1; p->FE = -1;}

        p = r;
    }
    void RDD(Nodo<T>*&p, bool t) // t RDI _ !T RID
    {
        Nodo<T> * q = p->m_pSon[t];
        Nodo<T> * r = q->m_pSon[!t];

        p->m_pSon[!t] = r->m_pSon[t];
        q->m_pSon[t] = r->m_pSon[!t];

        r->m_pSon[t] = q;
        r->m_pSon[!t] = p;
        
        if(r->FE == 0) p->FE = q->FE = 0;
        else if(r->FE == 1) {q->FE = t; p->FE = !t;}
        else if(r->FE == -1) {q->FE = !t; p->FE = t;}
        p = r;
    }
    void RS(Nodo<T>*&p, bool t) // t RDI _ !T RID
    {
        Nodo<T> * q = p->m_pSon[t];

        p->m_pSon[t] = q->m_pSon[!t];
        q->m_pSon[!t] = p; 
        
        if(q->FE == 0) p->FE = 0;
        else if(r->FE == 1) {q->FE = t; p->FE = !t;}
        else if(r->FE == -1) {q->FE = !t; p->FE = t;}
    }
};

int main()
{
    srand(9); 
    Binary_Tree<int> A;
    
    for(int i=0;i<1000;i++)
        A.insert(rand()%1000);
   
    cout<<"La raiz es :"<<A.m_pRoot->m_Dato<<endl;

    A.Print();

    cout<<"Imprimiendo niveles " <<endl;
    cout<<"Nivel : " << (A.get_Nivel(980))<<endl;
    cout<<"Nivel : " << (A.get_Nivel(141))<<endl;
    cout<<"Nivel : " << (A.get_Nivel(63))<<endl;
    cout<<"Nivel : " << (A.get_Nivel(120))<<endl;
    
    cout<<"Imprimiendo Ancestros " <<endl;
    cout<<"Ansertro :" << A.get_Ancestro(728,3)->m_Dato<<endl;
    cout<<"Ansertro :" << A.get_Ancestro(277,3)->m_Dato<<endl;
    cout<<"Ansertro :" << A.get_Ancestro(126,3)->m_Dato<<endl;
    cout<<"Ansertro :" << A.get_Ancestro(133,3)->m_Dato<<endl;

    cout<<"Print hojas "<<endl;
    A.Print_Hojas();
    cout<<"La Altura de la raiz es :"<<A.Get_Altura(A.m_pRoot)<<endl;
    

    cout<<"La Raiz es  "<<A.m_pRoot->m_Dato<<endl;
    
    return 1;
}