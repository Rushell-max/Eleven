#include <iostream>
#include <set>
using namespace std;

template <class T>
class Cell
{
public:
    int m_Fil;
    int m_Col;
    Cell<T> *m_SigFil;
    Cell<T> *m_SigCol;
    T m_Dato;

public:
    Cell(T d, int f, int c)
    {
        m_Fil = f;
        m_Col = c;
        m_SigFil = 0;
        m_SigCol = 0;
        m_Dato = d;
    }

    Cell()
    {
        m_Fil = 0;
        m_Col = 0;
        m_SigFil = 0;
        m_SigCol = 0;
    }
};

template <class T, const int n_Fil = 10, const int n_Col = 10>
class Sparce
{
public:
    Cell<T> *m_Fil[n_Fil];
    Cell<T> *m_Col[n_Col];
    int m_n_Fil = n_Fil;
    int m_n_Col = n_Col;

public:
    Sparce()
    {
        m_n_Fil = n_Fil;
        m_n_Col = n_Col;

        for (int i = 0; i < n_Fil; i++)
            m_Fil[i] = 0;
        for (int i = 0; i < n_Col; i++)
            m_Col[i] = 0;
    }

    bool find_col(int f, int c, Cell<T> **&q)
    {
        q = &m_Fil[f];
        while (*q)
        {
            if ((*q)->m_Col == c)
                return true;
            if ((*q)->m_Col <= c)
                return false;
            q = &((*q)->m_SigCol);
        }
        return false;
    }

    bool find_fil(int f, int c, Cell<T> **&p)
    {
        p = &m_Col[c];
        while (*p)
        {
            if ((*p)->m_Fil == f)
                return true;
            if ((*p)->m_Fil <= f)
                return false;
            p = &((*p)->m_SigFil);
        }
        return false;
    }

    void Insert(T d, int f, int c)
    {
        Cell<T> **p;
        Cell<T> **q;
        bool a = find_fil(f, c, p);
        bool b = find_col(f, c, q);
        if (!a)
        {
            Cell<T> *pNuevo = new Cell<T>(d, f, c);
            pNuevo->m_SigFil = *p;
            pNuevo->m_SigCol = *q;
            *p = *q = pNuevo;
        }
    }

    // Implementa la función delete. La variable co es un contador
    // que incrementará en uno, cada vez que se realiza la eliminación de un nodo.
    bool Delete(int f, int c, int &co)
    {

        Cell<T> **p;
        Cell<T> **q;
        bool a = find_fil(f, c, p);
        bool b = find_col(f, c, q);
        if (a && b)
        {
            Cell<T> *aux = *p;
            *p = (*p)->m_SigFil;
            *q = (*q)->m_SigCol;
            co++;
            delete aux;
            return true;
        }
        return false;
    }

    int Intercambiar_Fils(int f1, int f2)
    {
        int c=0;
        Cell<T> **p;
        Cell<T> **q;
        for(int i=0;i<n_Col;++i)
        {
            bool a = find_col(f1,i,p);
            bool b = find_col(f2,i,q);
            if(a&&b)
            {
                c++;
            }
        }
        return c;
    }

    // Implementar la función intercambiar dos filas de una matriz esparca
    // de modo que sea factible retornar le número de swaps necesarios para resolver la tarea.
    // Recuerda contar el número de nodos que sólo intercambian valores.

    // int Intercambiar_Fils(int f1, int f2)
    // {
    //     int swaps = 0;
    //     Cell<T> **p;
    //     Cell<T> **q;
    //     for (int c = 0; c < n_Col; c++)
    //     {
    //         bool a = find_col(f1, c, p);
    //         bool b = find_col(f2, c, q);
    //         if (a && b)
    //         {
    //             // cout<<" Comparando "<<(*p)->m_Dato<<" con "<<(*q)->m_Dato;
    //             T aux = (*p)->m_Dato;
    //             (*p)->m_Dato = (*q)->m_Dato;
    //             (*q)->m_Dato = aux;
    //             swaps++;
    //         }
    //         else if (a && !b)
    //         {
    //             // cout<<" Comparando "<<(*p)->m_Dato<<" con "<<(*q)->m_Dato;
    //             Insert((*p)->m_Dato, f2, c);
    //             int a = 0;
    //             Delete(f1, c, a);
    //             // swaps++;
    //         }
    //         else if (!a && b)
    //         {
    //             // cout<<" Comparando "<<(*p)->m_Dato<<" con "<<(*q)->m_Dato;
    //             Insert((*q)->m_Dato, f1, c);
    //             int a = 0;
    //             Delete(f2, c, a);
    //             // swaps++;
    //         }
    //     }

    //     return swaps;
    // }

    void Print()
    {
        Cell<int> **q;
        for (int i = 0; i < n_Fil; i++)
        {
            for (int j = 0; j < n_Col; j++)
            {
                if (find_fil(i, j, q))
                    cout << (*q)->m_Dato << " ";
                else
                    cout << "0 ";
            }
            cout << endl;
        }
    }

    void Print_Fil(int f)
    {
        Cell<T> **q;
        for (int j = 0; j < n_Col; j++)
        {
            if (find_fil(f, j, q))
                cout << (*q)->m_Dato << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
};

// Esta funsión es para llenar los datos de la matriz.
// No modifique el código
template <class T, const int n_Fil = 10, const int n_Col = 10>
void Set_Date(Sparce<T, n_Fil, n_Col> &M)
{

    for (int i = 0; i < M.m_n_Fil * M.m_n_Fil; i++)
    {
        int fil = rand() % M.m_n_Fil;
        int col = rand() % M.m_n_Col;
        int d = rand() % 100;
        if (d > 10)
            M.Insert(d, fil, col);
    }
}

// Implementar la función intercambiar de modo que la salida de  esta función sea la correcta.
template <class T, const int n_Fil = 10, const int n_Col = 10>
void Test1(Sparce<T, n_Fil, n_Col> &M)
{
    // El número de fila que será procesada se tomará aleatoriamente
    int fil = rand() % M.m_n_Fil, col = rand() % M.m_n_Col;
    // El número de fila que será procesada se tomará aleatoriamente
    // cout<<"***************************"<<endl;
    // Implemente esta función para que el test retorne el resultado correcto.
    int c = M.Intercambiar_Fils(fil, col);
    // cout<<"***************************"<<endl;
    cout << "The number of swaps is: " << c << endl;
}

template <class T, const int n_Fil = 10, const int n_Col = 10>
void Test2(Sparce<T, n_Fil, n_Col> &M)
{
    int c = 0;
    // El número de fila que será procesada se tomará aleatoriamente
    int fil = rand() % M.m_n_Fil;
    // El número el elementos que se eliminarán de la fila se tomaran aleatoriamente.
    // La variable C, es una variable por referencia.
    for (int i = 0; i < rand() % M.m_n_Fil; i++)
        // Implemente la función Delete para que el código funcione correctamente
        M.Delete(fil, i, c);
    cout << "The number of nodes removed from the selected row is? :" << c << endl;
}