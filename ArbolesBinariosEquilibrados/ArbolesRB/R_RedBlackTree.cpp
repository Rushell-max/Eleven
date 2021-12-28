#include<iostream>
#include <fstream>
using namespace std;

template<class T>
class Nodo
{
    public:
       T m_Dato;
       Nodo<T> * m_pSon[3];
       int m_Color;


       Nodo(T d)
       {
           m_Dato = d;
           // Hijo Izquierdo
           m_pSon[0] = 0;
           // Hijo Derecho
           m_pSon[1] = 0;
           // Padre
           m_pSon[2] = 0;
           // Color 0 = N ; 1 = R 
           m_Color = 0;
       } 
};

template<class T>
class RedBlack_Tree
{
    private:
       Nodo<T> * m_pRoot;
    public:
		RedBlack_Tree() {m_pRoot = 0;}

		Nodo<T>* abuelo(Nodo<T> *p)
		{
			if(p && p->m_pSon[2]) return p->m_pSon[2]->m_pSon[2];
			return NULL;
		}
		Nodo<T>* tio(Nodo<T> *p)
		{
			Nodo<T>* a = abuelo(p);
			if(p->m_pSon[2] == a->m_pSon[0]) return a->m_pSon[1];
			return a->m_pSon[0];
		}
		Nodo<T>* hermano(Nodo<T> *p)
		{
			if(p == p->m_pSon[2]->m_pSon[0]) return p->m_pSon[2]->m_pSon[1];
			return p->m_pSon[2]->m_pSon[0];
		}

		void insercion_caso1(Nodo<T>* p)
		{
			if(!p->m_pSon[2]) p->m_Color = 0;
			else insercion_caso2(p);
		}

		void insercion_caso2(Nodo<T>* p)
		{
			if(p->m_pSon[2]->m_Color == 0) return;
			else insercion_caso3(p);
		}
		void insercion_caso3(Nodo<T>* p)
		{
			Nodo<T>* t = tio(p), *a;
			if(t && t->m_Color == 1) // CASO 1: PAPA Y TIO SON ROJOS
			{
				p->m_pSon[2]->m_Color = 0;
				t->m_Color = 0;
				a = abuelo(p);
				a->m_Color = 1;
				insercion_caso1(a); // p = abuelo;
			}else insercion_caso4(p);
		}

		void insercion_caso4(Nodo<T>* p)
		{
			Nodo<T> *a = abuelo(p);
			// CASO 2: PAPA ES ROJO, TIO NEGRO Y ADEMAS P ES HIJO DERECHO Y PADRE DE P ES HIJO IZQUIERDO
			if (p == p->m_pSon[2]->m_pSon[1] && p->m_pSon[2] == a->m_pSon[0]) 
			{
				rotar_izda(p->m_pSon[2]);
				p = p->m_pSon[0];
			} else if (p == p->m_pSon[2]->m_pSon[0] && p->m_pSon[2] == a->m_pSon[1]) { // CASO 3: PAPA ES ROJO, TIO NEGRO Y P ES HIJO IZQUIERDO
				rotar_dcha(p->m_pSon[2]);
				p = p->m_pSon[1];
			}
			insercion_caso5(p);
		}
		void insercion_caso5(Nodo<T>* p)
		{
			Nodo<T> *a = abuelo(p);

			p->m_pSon[2]->m_Color = 0;
			a->m_Color = 1;
			if (p == p->m_pSon[2]->m_pSon[0] && p->m_pSon[2] == a->m_pSon[0]) {
				rotar_dcha(a);
			} else {
				/*
				* En este caso, (n == n->padre->dcho) && (n->padre == a->dcho).
				*/
				rotar_izda(a);
			}
		}
		void rotar_izda(Nodo<T>* p)
		{
			Nodo<T> **aux = &m_pRoot;
			if(p->m_pSon[2] && p->m_pSon[2]->m_pSon[1] == p)
				aux = &(p->m_pSon[2]->m_pSon[1]);
			else if(p->m_pSon[2] && p->m_pSon[2]->m_pSon[0] == p)
				aux = &(p->m_pSon[2]->m_pSon[0]);
			
			*aux = p->m_pSon[1];
			(*aux)->m_pSon[2] = p->m_pSon[2];
			p->m_pSon[2] = *aux;
			p->m_pSon[1] = (*aux)->m_pSon[0];
			(*aux)->m_pSon[0] = p;

			if(p->m_pSon[1]) p->m_pSon[1]->m_pSon[2] = p;
		}
		void rotar_dcha(Nodo<T>* p)
		{
			Nodo<T> **aux = &m_pRoot;
			if(p->m_pSon[2] && p->m_pSon[2]->m_pSon[1] == p)
				aux = &(p->m_pSon[2]->m_pSon[1]);
			else if(p->m_pSon[2] && p->m_pSon[2]->m_pSon[0] == p)
				aux = &(p->m_pSon[2]->m_pSon[0]);
			
			*aux = p->m_pSon[0];
			(*aux)->m_pSon[2] = p->m_pSon[2];
			p->m_pSon[2] = *aux;
			p->m_pSon[0] = (*aux)->m_pSon[1];
			(*aux)->m_pSon[1] = p;

			if(p->m_pSon[0]) p->m_pSon[0]->m_pSon[2] = p;
		}

};

int main()
{
	RedBlack_Tree <int> A;
	
}