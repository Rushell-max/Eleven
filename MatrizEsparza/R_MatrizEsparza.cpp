#include <iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

template<class T>
class Cell
{
    public:
        T m_Dato;
        int m_Fil, m_Col;
        Cell<T> *m_pSigFil;
        Cell<T> *m_pSigCol;

    public:
        
        Cell(int f, int c, T d)
        {
            m_Dato = d;
            m_Fil = f;
            m_Col = c;
            m_pSigFil = m_pSigCol = 0;
        }
        Cell()
        {
            m_Dato = 0;
            m_Fil = m_Col = 0;
            m_pSigFil = m_pSigCol = 0;            
        }

        ~Cell()
        {
            m_Dato = 0; 
            m_Fil = m_Col = 0;
            delete m_pSigFil, m_pSigCol;
            m_pSigFil = m_pSigCol = 0;  
        }
};

template<class T,int const n_Fil, int const n_Col>
class Sparse
{
    private:
        Cell<T>* m_Fil[n_Fil];
        Cell<T>* m_Col[n_Col];
    public:
        
        Sparse()
        {
            for(int i = 0; i<n_Fil; i++) m_Fil[i] = 0;
            for(int j = 0; j<n_Col; j++) m_Col[j] = 0;
        }

        bool find_col(int f, int c, Cell<T>**&q)
        {
            q = &m_Fil[f];
            while(*q)
            {
                if((*q)->m_Col == c) return true;
                if((*q)->m_Col > c) return false;
                q = &((*q)->m_pSigCol);
            }
            return false;
        }
        bool find_fil(int f, int c, Cell<T>**&p)
        {
            p = &m_Col[c];
            while(*p)
            {
                if((*p)->m_Fil == f) return true;
                if((*p)->m_Fil > f) return false;
                p = &((*p)->m_pSigFil);
            }
            return false;
        }
        void insert(T d, int f, int c) 
        {
            Cell<T> **p;
            Cell<T> **q;
            if(!find_col(f, c, q) && !find_fil(f, c, p))
            {
                Cell<T> *pNuevo = new Cell<T> (f, c, d);
                pNuevo->m_pSigFil = *p;
                pNuevo->m_pSigCol = *q;
                *p = *q = pNuevo;
            }
        }
        void Print()
        {
            Cell<T> **q;
            for(int j = 0; j<n_Col; j++) cout<<"\t"<<&m_Col[j]<<" ["<<m_Col[j]<<"] ";
            cout<<endl;
            for(int i = 0; i<n_Fil; i++) {
                cout<<&m_Fil[i]<<" ["<<m_Fil[i]<<"] ";
                for(int j = 0; j<n_Col; j++) {
                    if(find_col(i, j, q)) cout<<"|"<<*q<<" "<<(*q)->m_Dato<<"|\t";
                    else cout<<"- \t";
                }cout<<endl;
            }
        }

        Sparse<T, n_Fil, n_Col> * init(T ** A, int fi, int col)
        {
            Sparse<T, fi, col> B;
            for(int i=0; i<fi; i++)
                for(int j=0; j<col, j++)
                    if(A[i][j] != 0) B.insert(A[i][j], i, j);

            return B;  
        }
        Sparse<T, n_Fil, n_Col> * init()
        T get(int i, int j)
        {
            Cell<T> **p;
            if(find_fil(i, j, p))
            {
                return (*p)->m_Dato;
            }
            return NULL;
        }
        void set(int i, int j, T x)
        {
            Cell<T> **p, **q;
            if(find_col(i, j, q) && find_fil(i, j, p) && (x!=0))
            {
                (*q)->m_Dato = x;
            }
        }
        Sparse<T, n_Fil, n_Col> * transpose()
        {
            Sparse<int, n_Col, n_Fil> B;
            Cell<T> **q;
            for(int i = 0; i<n_Fil; i++)
                for(int j=0; j<n_Col; j++)
                    if(find_col(i, j, q)) B.insert((*q)->m_Dato, i, j);
            return B;
        }
        void multiply(int k)
        {
            Cell<T> **p, **q;
            for(int i=0; i<n_Fil; i++)
                if(find_col(i, k, p)) 
                    for(int j=0; j<n_Col; j++)
                        if(find_col(i, j, q)) (*q)->m_Dato *= (*p)->m_Dato;
        }
};


int main()
{
    /**Sparse<int,10,10> A;
    A.Print();
    for(int i=0; i<10; i++)
        A.insert(1, i, i);
    **/
	
    int fi, col;
    cout<<" Filas matriz> ";cin>>fi;
    cout<<" Columnas matriz> ";cin>>col;

	int **M=new int *[fi]; 
	for(int i=0; i<fi;i++)
		M[i]=new int[col];

	srand(time(NULL));
   	for(int i=0; i<fi;i++)
		for(int j=0; j<col;j++)
            M[i][j]=rand() % 2;

 	for(int i=0;i<fi;i++){
		delete [] M[i];
	}

	delete [] M;
}