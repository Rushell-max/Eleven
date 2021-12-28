/*//////////////   GUIA ARBOLES  //////////////////////////////

    -RUSHELL VANESSA ZAVALAGA OROZCO    */

/*////////////////          ACTIVIDADES           /////////////////////

    1. Un problema común para los compiladores y editores de texto es determinar si los paréntesis (corchetes) en una 
        cadena están balanceados y correctamente anidados. Por ejemplo. La cadena “((())())()” contiene pares 
        apropiadamente anidados de paréntesis; pero la cadena “)()(” no, y la cadena “())” no contiene paréntesis 
        apropiadamente emparejados. 
        
        Implemente un algoritmo que retorne true si una cadena contiene parentesis apropiedamente balanceados y anidados. 
        Y false caso contrario. Hint: Usa una pila.

    2. Implementar la estructura pila. Operaciones:
        
        -push(x): inserta x en la pila
        -pop(): elimina el último elemento agregado en la pila.
        -top(): retorna el último elemento agregado a la pila.
        -min(): retorna el menor de todos los elementos de la pila en O(1).

*/

#include <iostream>
#include <stack>

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
        T mini;
    public:
        
        Pila()
        {
           m_pTop = 0;
           mini = null;
        }
        ~Pila()
        {
            while(!m_pTop) { pop(); }
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
        bool isEmpty()
        {
            if(!m_pTop) return true;
            return false;
        }

        // 2 push(d)
        bool push(T d)
        {
            if(!m_pTop) { m_pTop = new Nodo<T>(d); mini = d; return true; }
            Nodo<T> * p_tmp =  new Nodo<T>(d);  
            if(d < mini) mini = d;        
            p_tmp->m_pAnt = m_pTop ;
            m_pTop = p_tmp;
            return true;
        }
        // 2 pop()
        bool pop()
        {
            if(!m_pTop) return false;
            Nodo<T>* temp = m_pTop;
            m_pTop = m_pTop-> m_pAnt;
            delete temp;
            temp = nullptr;
            return true;
        }
        // 2 top()
        T top()
        {
            if(!m_pTop) return 0;
            return m_pTop->m_Dato; 
        }

        // 2 min()
        T min()
        {
            Stack <pair<int, int>> S;

            if(S.isEmpty())
            {
                S.push(make_pair(x,x));
            }else {
                int y = S.top().second;
                S.push(make_pair(x, min(x,y)));
            }

            S.pop();
            return S.top().second;
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
            if(!m_pTop) { cout << endl; return; }
            Pila<T> copy(*this);
            while(copy.m_pTop)
            {
                cout<<copy.top()<<" ";
                copy.pop();
            }
        }

};

// EJERCICIO 1
bool balanceados(string cadena,Pila<char>& pila){
    int i=0;
    while(i!=cadena.length()){

        if(cadena[i] == ')' && i!=0)
        {
            if(pila.isEmpty()) return false;
            pila.pop();

        }else{
            pila.push(cadena[i]);
        }
        i++;
    }
    if(pila.isEmpty()) return true;
    return false;
}

void ejercicio1() {
    Pila<char> pila;
    string cadena;

    cout<<"Ingrese cadena >> ";cin>>cadena;
    if(balanceados(cadena,pila))  {cout<<" BALANCEADO "; return;}
    cout<<" NO BALANCEADO "; return;
    
}

void ejercicio2()
{
    Pila<int> A;
    srand(10); 
    for(int i=0;i<100;i++)
    {
        int a=rand()%1000;
        A.push(a);
    }
    cout<<"Eliminando el ultimo elemento agregado a la pila \n";
    cout<<"Primer elemento de la pila "<<A.top()<<"\n";
    cout<<"Minimo > "<<A.min();
}

////////////
int main()
{
    ejercicio1();
    ejercicio2();

}