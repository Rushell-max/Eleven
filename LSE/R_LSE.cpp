#include <iostream>
using namespace std;

template <class T>
class Nodo
{
    public:
        T m_Dato;
        Nodo<T> *m_pSig;

    public:
        Nodo(T d)
        {
            m_Dato = d;
            m_pSig = 0;
        }
};

template <class T>
class List
{
    private:
        Nodo<T> *m_pHead;
        Nodo<T> *pActual; // Iterador

    public:
        List()
        {
            m_pHead = 0;
        }

        void push_front(T d)
        {
            if (!m_pHead){ m_pHead = new Nodo<T>(d); return;}
            Nodo<T> *p_tmp = new Nodo<T>(d);
            p_tmp->m_pSig = m_pHead;
            m_pHead = p_tmp;
        }
        void push_back(T d)
        {
            if (!m_pHead){m_pHead = new Nodo<T>(d);return;}
            Nodo<T> *tmp = m_pHead;
            while (tmp->m_pSig) tmp = tmp->m_pSig;
            tmp->m_pSig = new Nodo<T>(d);
        }
        void Add(T d, Nodo<T> *&p)
        {
            if (!p){ p = new Nodo<T>(d); return;}
            Add(d, p->m_pSig);
        }
        void Add(T d){ Add(d, m_pHead);}

        bool find(T d)
        {
            Nodo<T> *tmp = m_pHead;
            while (tmp)
            {
                if (tmp->m_Dato == d) return true;
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
        bool Find(T d){return Find(d, m_pHead);}
        // ELIMINAR
        void delete_front()
        {
            if (!m_pHead) return;
            Nodo<T> *tmp = m_pHead->m_pSig;
            delete m_pHead;
            m_pHead = tmp;
        }
        void delete_back()
        {
            if (!m_pHead) return;
            if (!m_pHead->m_pSig){delete m_pHead; m_pHead = 0; return;}
            Nodo<T> *tmp = m_pHead;
            for (; tmp->m_pSig->m_pSig; tmp = tmp->m_pSig);
            delete tmp->m_pSig;
            tmp->m_pSig = 0;
        }
        void delete_this(Nodo<T> *p)
        {
            if (!m_pHead || !p) return;
            Nodo<T> **p_tmp = &m_pHead;
            while (p != (*p_tmp)){ p_tmp = &((*p_tmp)->m_pSig);}
            Nodo<T> *p_tmp2 = *(p_tmp);
            *p_tmp = (*p_tmp)->m_pSig;
            delete p_tmp2;
            p_tmp2 = 0;
        }
        // 2b remover siguiente (dado el puntero)
        void delete_next(Nodo<T> *p)
        {
            if (!m_pHead || !p) return;
            Nodo<T> *p_tmp = m_pHead;
            while (p != p_tmp) p_tmp = p_tmp->m_pSig;
            if (!p_tmp->m_pSig) return;
            Nodo<T> *p_tmp2 = p_tmp->m_pSig;
            p_tmp->m_pSig = p_tmp->m_pSig->m_pSig;
            delete p_tmp2;
            p_tmp2 = 0;
        }
        // 3 elimine el i-ésimo elemento de la lista
        void delet_iesimo(int i)
        {
            if (!m_pHead || i > this->size() || i == 0) return;
            Nodo<T> **p_tmp = &m_pHead;
            int count = 1;
            while (count < i && (*p_tmp))
            {
                p_tmp = &(*p_tmp)->m_pSig;
                count++;
            }
            Nodo<T> *p_tmp2 = *(p_tmp);
            *p_tmp = (*p_tmp)->m_pSig;
            delete p_tmp2;
            p_tmp2 = 0;
        }
        // 5 elimine las posiciones impares/pares de una lista.
        void elim_impa() { for (int i = 1; i <= this->size(); i++) delet_iesimo(i);}
        void elim_pa(){for (int i = 2; i <= this->size(); i++) delet_iesimo(i);}
        // 6 dado el puntero a una celda(nodo) de una lista elimine su predecesor
        void elimina_pred(Nodo<T> *p)
        {
            if (!m_pHead || !p) return;
            if (m_pHead == p) return;
            Nodo<T> **p_tmp = &m_pHead;
            while (p != (*p_tmp)->m_pSig && (*p_tmp)->m_pSig) { p_tmp = &((*p_tmp)->m_pSig);}
            Nodo<T> *p_tmp2 = *(p_tmp);
            *p_tmp = (*p_tmp)->m_pSig;
            delete p_tmp2;
            p_tmp2 = 0;
        }

        // 4 retorne el puntero al elemento máximo de la lista.
        Nodo<T> *elem_max()
        {
            Nodo<T> *p_tmp = m_pHead;
            Nodo<T> *p_tmp_ret = m_pHead;
            while (p_tmp)
            {
                if (p_tmp_ret->m_Dato <= p_tmp->m_Dato) p_tmp_ret = p_tmp;
                p_tmp = p_tmp->m_pSig;
            }
            return p_tmp_ret;
        }

        // IMPRIMIR
        // Iterativa
        void print()
        {
            if (!m_pHead){cout << "\n Lista Vacia ! \n"; return;}
            Nodo<T> *tmp = m_pHead;
            cout << "\n Lista tam> " << this->size() << ": \n";
            for (; tmp; tmp = tmp->m_pSig)
                cout << " dir> " << tmp << " _ data> " << tmp->m_Dato << " _ dirdirSig> " << &tmp->m_pSig << " _ dirSig> " << tmp->m_pSig << "\n";
        }
        // Recursiva
        void Print(Nodo<T> *p)
        {
            if (!p){ cout << endl;return;}
            cout << p->m_Dato << " "; // Inicio a Fin
            Print(p->m_pSig);
            //cout<<p->m_Dato<<" "; // Fin a Inicio
        }
        void Print(){Print(m_pHead);}

        int size()
        {
            Nodo<T> *p_tmp = m_pHead;
            int c = 0;
            while (p_tmp)
            {
                c++;
                p_tmp = p_tmp->m_pSig;
            }
            return c;
        }

        // 7 invierta una lista
        List<T> invertir()
        {
            if (!m_pHead) return *this;
            List<T> Invertida;
            this->Last();
            while (pActual)
            {
                Invertida.Add(pActual->m_Dato);
                this->Previous();
            }
            return Invertida;
            //Invertida.print();
        }

        // 8 determine si una lista de caracteres es palíndromo.
        bool es_palindromo()
        {
            List<T> L2 = *this;
            L2 = L2.invertir();
            Nodo<T> *p_tmp = L2.m_pHead, *p_tmp2 = this->m_pHead;
            while (p_tmp && p_tmp2)
            {
                if (p_tmp->m_Dato != p_tmp2->m_Dato) return false;
                p_tmp = p_tmp->m_pSig;
                p_tmp2 = p_tmp2->m_pSig;
            }
            return true;
        }

        // 9 entrada dos listas y las concatene.
        List<T> Concatenar(List L2)
        {
            List<T> Concatenacion;
            Nodo<T> *tmp = m_pHead;
            while (tmp)
            {
                Concatenacion.Add(tmp->m_Dato);
                tmp = tmp->m_pSig;
            }
            tmp = L2.m_pHead;
            while (tmp)
            {
                Concatenacion.Add(tmp->m_Dato);
                tmp = tmp->m_pSig;
            }
            return Concatenacion;
            //Concatenacion.print();
        }

        // 10 elimine todos los elementos repetidos de una lista.
        bool es_repetido(Nodo<T> *p) ////////// !!!!!!!!!!1 ESTO CREO QUE ESTA MAL
        {
            Nodo<T> *p_tmp = m_pHead;
            while (p_tmp != p)
            {
                if (p_tmp->m_Dato == p->m_Dato) return true;
                p_tmp = p_tmp->m_pSig;
            }
            return false;
        }
        void elim_repetido() ////////// !!!!!!!!!!1 ESTO CREO QUE ESTA MAL X2
        {
            if (!m_pHead) return;
            Nodo<T> **tmp = &m_pHead;
            Nodo<T> **tmp2 = &m_pHead;
            while (*tmp)
            {
                if (es_repetido(*tmp)) delete_this(*tmp);
                else tmp = &((*tmp)->m_pSig);
                
            }
        }
        // 10 elimine todos los elementos repetidos de una lista.
        List<T> elim_repetido1()
        {
            if (!m_pHead) return *this;
            Nodo<T> *p_tmp = m_pHead;
            List<T> ListaLimpia;

            while (p_tmp)
            {
                if (!ListaLimpia.find(p_tmp->m_Dato)) ListaLimpia.Add(p_tmp->m_Dato);
                p_tmp = p_tmp->m_pSig;
            }
            return ListaLimpia;
        }

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
                if (!Union.find(tmp2->m_Dato)) Union.Add(tmp2->m_Dato);
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
            if (!m_pHead) return 0;
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
        T MaxRe(){ return MaxRe(0, m_pHead);}
        // Nro de Pares
        int Pares()
        {
            if (!m_pHead) return 0;
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
            if (!m_pHead ) return;
            Nodo<T> *tmp = m_pHead;
            while (tmp->m_pSig)
            {
                tmp = tmp->m_pSig;
            }
            pActual = tmp;
        }
        void Next()
        {
            if (!pActual) return;
            pActual = pActual->m_pSig;
        }
        void Previous()
        {
            if (!m_pHead || !pActual) return;
            Nodo<T> *tmp = m_pHead, *ant = 0;
            while (tmp != pActual)
            {
                ant = tmp;
                tmp = tmp->m_pSig;
            }
            pActual = ant;
        }
        T getDato() {return pActual->m_Dato;}
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
            if (!m_pHead) return;
            this->Last();
            while (pActual)
            {
                cout << pActual->m_Dato << " ";
                this->Previous();
            }
        }
};

int main()
{
    List<int> A;

    A.push_back(13);
    A.push_back(25);
    A.push_back(154);
    A.push_back(13);
    A.push_back(25);
    A.push_back(111);
    A.print();

    cout << "\n 2a >> Insertar (al inicio) ";
    A.push_front(11);
    A.print();

    cout << "\n 2b >> Remover siguiente (dado el puntero) ";
    A.delete_next(A.elem_max());
    A.print();

    int opc;
    cout << "\n 2c >> Buscar _ Ingrese elemento >> ";
    cin >> opc;
    cout << " Esta " << opc << " ? " << A.find(opc) << endl;

    cout << "\n 3 >> DELETE I-ÉSIMO _ Ingrese i> salir(0) >> ";
    cin >> opc;
    A.delet_iesimo(opc);
    A.print();

    cout << "\n 4 >> Puntero al elemento maximo > " << A.elem_max() << "\n";

    cout << "\n 5 >> Eliminar posiciones pares (1) o impares(2) ? salir(0) >> ";
    cin >> opc;
    if (opc == 1)
        A.elim_pa();
    if (opc == 2)
        A.elim_impa();

    cout << "\n 6 >> Función que dado el puntero a una celda(nodo) de una lista elimine su predecesor. ";
    A.elimina_pred(A.elem_max());
    A.print();

    cout << "\n 7 >> Invertir lista ";
    A = A.invertir();
    A.print();

    cout << "\n 8 >> Es palindromo? " << A.es_palindromo() << "\n";

    cout << "\n 9 >> Función que reciba como entrada dos listas y las concatene ";
    cout << "\n CREANDO NUEVA LISTA . . . \n";
    List<int> B;
    B.push_back(25);
    B.push_back(14);
    B.push_back(11);
    B.push_back(45);
    B.push_back(111);
    B.print();
    A = A.Concatenar(B);

    cout << "\n 10 >> Lista sin elementos repetidos > ";
    A.print();
    A.elim_repetido(); // Primera opcion
    //A = A.elim_repetido1(); // Segunda opcion
    A.print();

    /**
   A.Union(B);
   A.Inter(B);
   cout<<" MAX "<<A.Max();
   cout<<" MAXRE "<<A.MaxRe();
   A.Print();
   A.PrintIT();
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
