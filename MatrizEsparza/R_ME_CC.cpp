// RUSHELL VANESSA ZAVALAGA OROZCO
/** 
  
   Implemente la estructura Matriz Esparza usando la representación de columnas comprimidas (compressed columns). 
   Con las siguientes operaciones:
  
        init(A): Que reciba como entrada una matriz 2D A y la convierta en una matriz esparza.
        init(T): Que reciba como entrada un arreglo de triplas (posición fila, posición columna y valor) y 
            que la transforme en una matriz esparza. Asuman que están ordenados por el índice de la columna, 
            y para desempatar utiliza el índice de las fila.
        get(i,j): Recupera el valor de la posición (i,j).
        set(i,j,x): Asigna el valor x en la posición (i,j). Asuman que la posición (i,j) si está en la matriz esparza y que x != 0.
        transpose: Obtiene la transpuesta de la matriz esparza, la transpuesta también debe ser esparza.
        multiply(x): multiplica la matriz esparza con el vector columna x.

**/
#include <iostream>

using namespace std;

class SparseMatrix_AT
{
    public:
        int m; // número de filas
        int n; // número de columnas
        int nz ; // número de entradas
        int * row ; // indices de las filas
        int * col ; // indices de las columnas
        double * val ; // valores almacenados

};

class SparseMatrix
{
    public:
        int m; // número de filas
        int n; // número de columnas
        int nz; // número de entradas
        int *p;  // columnas (n + 1)
        int *idx; // indices de las filas
        double *val; // valores numéricos
    
    public:

        SparseMatrix(int _m, int _n)
        {
            m=_m;
            n=_n;
        }
        SparseMatrix(){}

        void init(double **A, int fi, int col)
        {
            m = fi; n = col; nz=0;
            p = new int [col+1];

            for(int j=0; j<col; j++)
                for(int i=0; i<fi ;i++) {if(A[i][j]!=0) nz++;}

            idx = new int [nz];
            val = new double [nz];

            nz=0;
            for(int j=0; j<col; j++)
            {
                p[j] = nz;
                for(int i=0; i<fi ;i++)
                {
                    if(A[i][j]!=0) 
                    {
                        idx[nz] = i;
                        val[nz] = A[i][j];
                        nz++;
                    }
                }
            }
            p[col] = nz;
        }
        void init(SparseMatrix_AT * r)
        {
            m = r->m;
            n = r->n;
            nz = r->nz;
            p = new int [m+1];
            idx = new int [nz];
            val = new double [nz];   

            int count=0;
            for(int i=0; i<nz; i++) // Asumiendo que están ordenados por el índice de la columna, y para desempatar utiliza el índice de las fila ORDENADAMENTE.
            {
                if(r->col[i]==count) {p[count] = nz;count++;}
                idx[i] = r->row[i];
                val[i] = r->val[i];
            }
            p[count]= nz;
        }
        double get(int i, int j) //O(nz) // i = fila / j = columna
        {
            //for(int itP = p[j]; itP < p[j+1]; itP++) 
            //    if(idx[itP] == i) return val[itP];
            int ini = p[j];
            int fin = p[j+1] - 1;
            while(ini <= fin)
            {
                int mid = (ini+fin)/2;
                if(i == idx[mid]) return val[mid];
                else if(i>mid) ini = mid + 1;
                else fin = mid - 1;
            }
            return 0;
        }
        void set(int i, int j, double x) //O(nz)
        {
            if(x == 0) return;
            for(int itP = p[j]; itP < p[j+1]; itP++) 
                if(idx[itP] == i) {val[itP] = x; return;}
        }
        SparseMatrix transpose() 
        {
            SparseMatrix B(n, m);
            B.p = new int [m+1];
            B.idx = new int [nz];
            B.val = new double [nz];
            
            double * auxVal = new double[m*n];
            int * auxCol = new int[m*n];
            int * auxFilas = new int[m*n];

            for(int i=0; i<m*n ; i++){ auxVal[i] = -1; auxCol[i] = -1; auxFilas[i] = -1;}

            for(int j=0; j<n; j++) 
                for(int itP = p[j]; itP < p[j+1]; itP++){
                    int pos = idx[itP]*n + j;
                    auxVal[pos] = val[itP];
                    auxCol[pos] = j;
                    auxFilas[pos] = idx[itP];
                }

            B.nz= 0; int count = 0;
            for(int i=0; i<m*n; i++)
            {
                if(auxFilas[i] == count) {B.p[count]= B.nz; count++;}
                if(auxCol[i] != -1)
                {
                    B.val[B.nz] = auxVal[i];
                    B.idx[B.nz] = auxCol[i];
                    B.nz++;
                }
            }
            B.p[count] = B.nz;

            delete [] auxVal, auxCol, auxFilas;

            return B;
        }
        void multiply(double *x, double *y)
        {
            for(int j=0; j<n; j++)
                for(int itP = p[j]; itP < p[j+1]; itP++) 
                    y[ idx[itP]] += val[itP]*x[j]; 
        }
        void print()
        {
            cout<<" Info de Matriz Esparsa: ";
            cout<<" > Filas (m = "<<m<<") >  Columnas (n = "<<n<<") > NZ = "<<nz<<endl;

            cout<<"\n Valores p \n";
            for(int j=0; j<n+1; j++)
                cout<<p[j]<<" ";
            
            cout<<"\n Valores idx y su valor \n";
            for(int i=0; i<nz; i++)
                cout<<i<<" > "<<idx[i]<<" > "<<val[i]<<"\n";

            for(int j=0; j<n; j++) 
                for(int itP = p[j]; itP < p[j+1]; itP++)
                    cout<<" itp> "<<itP<<" Columna> "<<j<<" _ Fila> "<<idx[itP]<<" _ Valor> "<<val[itP]<<endl; 
        }   

};

int main()
{
    int fi, col;
    cout<<" Ingrese numero de filas> ";cin>>fi;
    cout<<" Y columnas> "; cin>>col;

	double **matriz=new double *[fi]; //puntero que apunta a un array de punteros
	for(int i=0; i<fi;i++)
		matriz[i]=new double[col];

    int n=1;
    for(int i=0; i<fi; i++)
        for(int j=0; j<col; j++) { cin>>matriz[i][j];}

    for(int i=0; i<fi; i++)
        for(int j=0; j<col; j++)  cout<<matriz[i][j]<<" ";

    SparseMatrix A;
    A.init(matriz, fi, col);

    A.print();

    int i, j;
    cout<<" GET i = ";cin>>i; cout<<" j = ";cin>>j;
    cout<<" GET I("<<i<<")"<<" J("<<j<<")"<<" > "<<A.get(i, j);

    double x;
    cout<<" SET i = ";cin>>i; cout<<" j = ";cin>>j;cout<<" x = ";cin>>x; A.set(i, j, x);
    A.print();

    cout<<" La transpuesta es: ";
    SparseMatrix B;
    B = A.transpose();

    B.print();

    for(int i=0;i<fi;i++){
		delete [] matriz[i];
	}

	delete [] matriz;
    
    return 1;
}