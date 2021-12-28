#include <iostream>
using namespace std;

template <class T>
class Nodo
{
    public:
        T m_Dato;
        Nodo<T> *m_pSig;
        Nodo<T> *m_pAnt;

    public:
        Nodo(T d)
        {
            m_Dato = d;
            m_pSig = 0;
            m_pAnt = 0;
        }
};

template <class T>
class List
{
    private:
        Nodo<T> *m_pHead;
        Nodo<T> *m_pTale;
        Nodo<T> *pActual;

    public:
        List()
        {
            m_pHead = 0;
            m_pTale = 0;
            pActual = 0;
        }

        // INSERTAR
        void push_front(T d)
        {
            if (!m_pHead){ m_pHead = new Nodo<T>(d);m_pTale = m_pHead;return; }
            Nodo<T> *p_tmp = new Nodo<T>(d);
            p_tmp->m_pSig = m_pHead;
            m_pHead->m_pAnt = p_tmp;
            m_pHead = p_tmp;
        }
        void push_back(T d)
        {
            if (!m_pHead){ m_pHead = new Nodo<T>(d);m_pTale = m_pHead; return;}
            Nodo<T> *newNodo = new Nodo<T>(d);
            newNodo->m_pAnt = m_pTale;
            m_pTale->m_pSig = newNodo;
            m_pTale = newNodo;
        }
        void Add(T d, Nodo<T> *&p)
        {
            if (!p){p = new Nodo<T>(d); return;}
            Add(d, p->m_pSig);
            p->m_pSig->m_pAnt = p;
        }
        void Add(T d){Add(d, m_pHead);}
        //BUSCAR
        // Iterativa
        bool find(T d)
        {
            Nodo<T> *tmp = m_pHead;
            while (tmp)
            {
                if (tmp->m_Dato == d)  return true;
                tmp = tmp->m_pSig;
            }
            return false;
        }
        // Recursiva
        bool Find(T d, Nodo<T> *p)
        {
            if (!p) return false;
            if (p->m_Dato == d) return true;
            return find(d, p->m_pSig);
        }
        bool Find(T d) {return Find(d, m_pHead); }
        // ELIMINAR
        void delete_front()
        {
            if (!m_pHead) return;
            Nodo<T> *tmp = m_pHead->m_pSig;
            m_pHead->m_pSig->m_pAnt = 0;
            delete m_pHead;
            m_pHead = 0;
            m_pHead = tmp;
        }
        void delete_back()
        {
            if (!m_pHead)  return;
            if (!m_pHead->m_pSig) { delete m_pHead; m_pHead = 0; return;  }
            // ACA SE PUEDE USAR TALE PERO TAMBIEN FUNCA :v
            Nodo<T> *tmp = m_pHead;
            for (; tmp->m_pSig->m_pSig; tmp = tmp->m_pSig) ;
            delete tmp->m_pSig;
            tmp->m_pSig = 0;
        }
        // IMPRIMIR
        // Iterativa
        void print()
        {
            if (!m_pHead)return;
            Nodo<T> *tmp = m_pHead;
            for (; tmp; tmp = tmp->m_pSig)
            {
                if (tmp->m_pAnt && tmp->m_pSig)
                    cout << tmp->m_pAnt->m_Dato << " - " << tmp->m_Dato << " - " << tmp->m_pSig->m_Dato << "\n";
            }
        }
        // Recursiva
        void Print(Nodo<T> *p)
        {
            if (!p){ cout << endl; return;}
            cout << p->m_Dato << " "; // Inicio a Fin
            Print(p->m_pSig);
            //cout<<p->m_Dato<<" "; // Fin a Inicio
        }
        void Print() {Print(m_pHead); }

        // EXTRAS
        void Union(List l2)
        {
            List<T> Union;
            Nodo<T> *tmp = m_pHead;
            Nodo<T> *tmp2 = l2.m_pHead;
            while (tmp)
            {
                Union.Add(tmp->m_Dato);
                tmp = tmp->m_pSig;
            }
            while (tmp2)
            {
                if (!Union.find(tmp2->m_Dato))  Union.Add(tmp2->m_Dato);
                tmp2 = tmp2->m_pSig;
            }
            Union.Print();
        }
        void Inter(List l2)
        {
            List<T> Inter;
            Nodo<T> *tmp = m_pHead;
            while (tmp)
            {
                if (l2.find(tmp->m_Dato)) Inter.Add(tmp->m_Dato);
                tmp = tmp->m_pSig;
            }
            Inter.Print();
        }
        // Mayor dato
        // Iterativa
        T Max()
        {
            if (!m_pHead)  return 0;
            int max = 0;
            Nodo<T> *tmp = m_pHead;
            while (tmp)
            {
                if (tmp->m_Dato > max) max = tmp->m_Dato;
                tmp = tmp->m_pSig;
            }
            return max;
        }
        // Recursiva
        T MaxRe(int max, Nodo<T> *p)
        {
            if (!p) return max;
            if (p->m_Dato > max) max = p->m_Dato;
            return MaxRe(max, p->m_pSig);
        }
        T MaxRe()
        {
            return MaxRe(0, m_pHead);
        }
        // Nro de Pares
        int Pares()
        {
            if (!m_pHead)return 0;
            int c = 0;
            Nodo<T> *tmp = m_pHead;
            while (tmp)
            {
                if (tmp->m_dato % 2 == 0) c++;
                tmp = tmp->m_sig;
            }
            return c;
        }
        // Iterador
        void Begin()
        {
            pActual = m_pHead;
        }
        void Last()
        {
            if (!m_pHead) return;
            // ACA TAMBIEN SE PUEDE CON TALE
            Nodo<T> *tmp = m_pHead;
            while (tmp->m_pSig)
            {
                tmp = tmp->m_pSig;
            }
            pActual = tmp;
        }
        void Next()
        {
            if (!pActual)  return;
            pActual = pActual->m_pSig;
        }
        void Previous()
        {
            if (!pActual) return;
            pActual = pActual->m_pAnt;
        }
        T getDato()
        {
            return pActual->m_Dato;
        }
        // Print con Begin y Next
        void PrintIT()
        {
            if (!m_pHead) return;
            this->Begin();
            while (pActual)
            {
                cout << pActual->m_Dato << " ";
                this->Next();
            }
        }
        // Print con Last y Previous
        void PrintIT2()
        {
            if (!m_pHead)  return;
            this->Last();
            while (pActual)
            {
                cout << pActual->m_Dato << " ";
                this->Previous();
            }
        }
        bool dobleFind(T d) // NO SE CUAL ES LA IDEA DE ESTE ALGORITMO PERO CREO QUE TAMPOCO FUNIONA
        {
            if (!m_pHead || !m_pTale) return false;
            Nodo<T> *tmp = m_pHead;
            Nodo<T> *tmp2 = m_pTale;
            while (tmp != tmp2 || tmp != m_pTale)
            {
                if (tmp->m_Dato == d || tmp2->m_Dato == d)  return true;
                tmp = tmp->m_pSig;
                tmp2 = tmp2->m_pSig; // SIGUIENTE? NO DEBERIA SER ANT?
            }
            if (tmp->m_Dato == d) return true;
            return false;
        }
};

int main()
{

    /*Nodo<int> A(666);
  cout<<"Dirección del objeto "<<&A<<endl;
  cout<<"Dirección donde vive el dato" << &(A.m_Dato)<<endl;
  cout<<"Dirección donde vide la variable siguiente "<<&(A.m_pSig)<<endl;*/
    List<int> A;

    A.push_back(34);
    A.push_back(14);
    A.push_back(434);
    A.push_back(634);
    A.push_back(734);
    A.push_front(1);
    A.push_front(-5);
    A.Add(875);
    A.Add(975);
    A.Print();
    A.delete_front();
    A.Print();
    A.delete_back();
    A.Print();
    A.print();

    List<int> B;
    B.push_back(5);
    B.push_back(14);
    B.push_back(1);
    B.push_back(45);
    B.push_back(734);
    B.print();

    A.Union(B);
    A.Inter(B);
    cout << " MAX " << A.Max();
    cout << " MAXRE " << A.MaxRe();
    cout << " PRINT ";
    A.Print();
    cout << " PRINT ";
    A.PrintIT();
    cout << " PRINT ";
    A.PrintIT2();

    /* cout<<A.find(34)<<endl;
   cout<<A.find(14)<<endl;
   cout<<A.find(434)<<endl;
   cout<<A.find(634)<<endl;
   cout<<A.find(734)<<endl;
   cout<<A.find(0)<<endl;
   cout<<A.find(734)<<endl;
   */

    return 1;
}
