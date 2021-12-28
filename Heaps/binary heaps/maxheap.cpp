#include <iostream>
#include <vector>
using namespace std;

class MaxHeap
{
    private:
        int* harr;
        int capacity;
        int heap_size;
    public:
        MaxHeap(int);               // constructor crea el arreglo con la capacidad indicada
        MaxHeap(int*,int);          // constructor que copia un arreglo pasado como parametro, y lo convierte en un MaxHeap
        ~MaxHeap();                 // destructor libera memoria
        int getMax(){ return harr[0]; }         // devuelve el mayor
        int parent(int i){ return (i-1)/2; }    // devuelve el indice del padre
        int HD(int i){ return (i*2)+2; }        // devuelve el indice del hijo derecho
        int HI(int i){ return (i*2)+1; }        // devuelve el indice del hijo izquierdo
        void heapFy(int);           // logn, compara valores del padre y sus hijos, ayuda a mantener la propiedad de un binary heap
        void makeHeap();            // (n/2)logn = nlogn, vuelve el arreglo guardado como un MaxHeap
        int deleteMax();            // logn, borra el mayor valor
        void heapsort();    
        void insert(int);           // logn, insert un valor al final del array y lo acomoda
        void deleteKey(int);        // logn, borra un valor indicado por la posicion
        void decreaseKey(int,int);  // cambia el tamaño de un dato

        void print();
        int sumar_hojas();
};

MaxHeap::MaxHeap( int c )
{
    capacity = c;
    harr = new int[capacity];
    heap_size = 0;
}

MaxHeap::MaxHeap(int *arr,int n)
{
    capacity = 2*n;
    harr = new int(capacity);
    heap_size = n;
    for(int i=0;i<heap_size;++i)
        harr[i]=arr[i];
    makeHeap();
}

MaxHeap::~MaxHeap()
{
    delete []harr;
    cout<<"\nse destruyo\n";
}

void MaxHeap::heapFy(int i)             // va hasta un nodo hoja, recorre en el peor caso la altura del arbol
{                                       // h = log2(n+1)-1 = log2n
    if( i<heap_size/2 )                             // si i no es un valor en una hoja
    {
        int l = HI(i);                              // guarda hijo izquierdo
        int r = HD(i);                              // guarda hijo derecho
        int m = i;                                  // guarda i
        if( l < heap_size && harr[l] > harr[m] )    // si hijo izquierdo es mayor al padre
            m=l;                                    // guarda indice del mayor
        if( r < heap_size && harr[r] > harr[m] )    // si hijo derecho es mayor a los otros dos
            m=r;                                    // guarda indice del mayor
        if( m==i )                                  // si m sigue siendo i
            return;                                 // termina, no viola la propiedad de un binary heap
        swap(harr[m],harr[i]);                      // si m != i, intercambia valores
        heapFy(m);                                  // baja al hijo a arreglar posible error
    }
}

void MaxHeap::makeHeap()                    // nlogn
{
    for(int i=heap_size/2;i>=0;--i)         // n/2 iteraciones
        heapFy(i);                          // logn iteraciones
}                                           // total = n/2 * logn = (n/2)logn = nlogn:

int MaxHeap::deleteMax()                    // logn
{
    if( heap_size<=0 )                      // si no hay elementos
        return INT_MIN;
    if( heap_size==1 )                      // si hay un elemento
    {
        heap_size--;                        // reduce el tamaño
        return harr[0];                     // devuelve el primero
    }   
    int ini = harr[0];                      // guarda primer elemento
    harr[0] = harr[heap_size-1];            // copia ultimo dato al inicio
    heap_size--;                            // borra el ultimo dato
    heapFy(0);                              // logn, arregla posible error
    return ini;                             // devuelve menor valor
}

void MaxHeap::heapsort()
{
    int n = heap_size;
    for(int i=0;i<n;i++)
    {
        swap( harr[0] , harr[heap_size-1] );
        heap_size--;
        heapFy(0); 
    }
    heap_size = n;
}

void MaxHeap::insert( int d )                       // logn
{   
    if( heap_size == capacity )                     // si ya se ocupo todo el array
    {
        cout<<"OverFlow: could not insert\n";           
        return;
    }
    int i=heap_size++;                              // incrementa valor que representa la cantidad actual de valores
    harr[i] = d;                                    // inserta nuevo elemento al final
    while( i!=0 && harr[parent(i)] < harr[i] )      // hasta que se llegue a la raiz y cada padre sea menor    
    {                                               
        swap( harr[parent(i)] , harr[i] );          // intercambia padre con hijo 
        i = parent(i);                              // guarda indice del padre
    }
}                                                   // peor caso se recorre de la ultima hoja a la raiz
                                                    // recorre la altura del arbol, h = logn

void MaxHeap::deleteKey( int i )                    // 2logn = logn
{
    decreaseKey( i , INT_MAX );                     // vuelve el harr[i] el mayor valor posible, se vuelve el primer valor del heap
    deleteMax();                                    // elimina el valor del heap
}

void MaxHeap::decreaseKey( int i, int newD )        // peor caso se recorre de la hoja de mayor nivel a la raiz
{                                                   // logn
    harr[i] = newD;                                 // reemplaza el nuevo valor
    while( i!=0 && harr[parent(i)] < harr[i] )      // hasta que se llegue a la raiz y cada padre sea menor
    {
        swap( harr[parent(i)] , harr[i] );          // intercambia padre con hijo
        i = parent(i);                              // guarda indice del padre
    }
}

void MaxHeap::print()
{
    for(int i=0;i<heap_size;++i)
        cout<<harr[i]<<' ';
    cout<<'\n';
}

int MaxHeap::sumar_hojas()
{
    int sum=0;
    for(int i=heap_size/2;i<heap_size;++i)
        sum+=harr[i];
    return sum;
}

int main()
{
    // int arr[]={57,98,39,12,1,15,19,13,21,14,27,31,9};
    // MaxHeap h(arr,13);
    // h.print();
    // h.decreaseKey(11,10);
    // h.deleteMax();
    // h.print();
    // h.insert(2);
    // h.print();
    // h.heapsort();
    // h.print();
    // h.makeHeap();
    // h.print();
    
    // h.deleteKey(3);
    // h.print();
    cout<<"array 2\n";
    int arr2[]={1,8,6,20,10,9,7};
    MaxHeap h2(arr2,7);
    h2.print();
    // h2.decreaseKey(4,25);
    // h2.print();
    // h2.deleteMax();
    // h2.print();
    // h2.deleteKey(4);
    // h2.print();
    cout<<"\nla suma es: "<<h2.sumar_hojas();
    
    // cout<<"array 3\n";
    // MaxHeap h3(10);
    // h3.insert(20);
    // h3.insert(10);
    // h3.insert(4);
    // h3.insert(80);
    // h3.print();

    // cout<<"\ntermino \n";
}