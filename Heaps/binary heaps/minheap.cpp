#include <iostream>
#include <vector>
using namespace std;

class MinHeap
{
    private:
        int* harr;
        int capacity;
        int heap_size;
    public:
        MinHeap(int);               // constructor crea el arreglo con la capacidad indicada
        MinHeap(int*,int);          // constructor que copia un arreglo pasado como parametro, y lo convierte en un minheap
        ~MinHeap();                 // destructor libera memoria
        int getMin(){ return harr[0]; }         // devuelve el menor
        int parent(int i){ return (i-1)/2; }    // devuelve el indice del padre
        int HD(int i){ return (i*2)+2; }        // devuelve el indice del hijo derecho
        int HI(int i){ return (i*2)+1; }        // devuelve el indice del hijo izquierdo
        void heapFy(int);           // logn, compara valores del padre y sus hijos, ayuda a mantener la propiedad de un binary heap
        void makeHeap();            // (n/2)logn = nlogn, vuelve el arreglo guardado como un minheap
        int deleteMin();            // logn, borra el menor valor
        void heapsort();    
        void insert(int);           // logn, insert un valor al final del array y lo acomoda
        void deleteKey(int);        // logn, borra un valor indicado por la posicion
        void decreaseKey(int,int);  // cambia el tamaño de un dato

        void print();
};

MinHeap::MinHeap( int c )
{
    capacity = c;
    harr = new int[capacity];
    heap_size = 0;
}

MinHeap::MinHeap(int *arr,int n)
{
    capacity = 2*n;
    harr = new int(capacity);
    heap_size = n;
    for(int i=0;i<heap_size;++i)
        harr[i]=arr[i];
    makeHeap();
}

MinHeap::~MinHeap()
{
    delete []harr;
    cout<<"\nse destruyo\n";
}

void MinHeap::heapFy(int i)             // va hasta un nodo hoja, recorre en el peor caso la altura del arbol
{                                       // h = log2(n+1)-1 = log2n
    if( i<heap_size/2 )                             // si i no es un valor en una hoja
    {
        int l = HI(i);                              // guarda hijo izquierdo
        int r = HD(i);                              // guarda hijo derecho
        int m = i;                                  // guarda i
        if( l < heap_size && harr[l] < harr[m] )    // si hijo izquierdo es menor al padre
            m=l;                                    // guarda indice del menor
        if( r < heap_size && harr[r] < harr[m] )    // si hijo derecho es menor a los otros dos
            m=r;                                    // guarda indice del menor
        if( m==i )                                  // si m sigue siendo i
            return;                                 // termina, no viola la propiedad de un binary heap
        swap(harr[m],harr[i]);                      // si m != i, intercambia valores
        heapFy(m);                                  // baja al hijo a arreglar posible error
    }
}

void MinHeap::makeHeap()                    // nlogn
{
    for(int i=heap_size/2;i>=0;--i)         // n/2 iteraciones
        heapFy(i);                          // logn iteraciones
}                                           // total = n/2 * logn = (n/2)logn = nlogn:

int MinHeap::deleteMin()                    // logn
{
    if( heap_size<=0 )                      // si no hay elementos
        return INT_MAX;
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

void MinHeap::heapsort()
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

void MinHeap::insert( int d )                       // logn
{   
    if( heap_size == capacity )                     // si ya se ocupo todo el array
    {
        cout<<"OverFlow: could not insert\n";           
        return;
    }
    int i=heap_size++;                              // incrementa valor que representa la cantidad actual de valores
    harr[i] = d;                                    // inserta nuevo elemento al final
    while( i!=0 && harr[parent(i)] > harr[i] )      // hasta que se llegue a la raiz y cada padre sea mayor    
    {                                               
        swap( harr[parent(i)] , harr[i] );          // intercambia padre con hijo 
        i = parent(i);                              // guarda indice del padre
    }
}                                                   // peor caso se recorre de la ultima hoja a la raiz
                                                    // recorre la altura del arbol, h = logn

void MinHeap::deleteKey( int i )                    // 2logn = logn
{
    decreaseKey( i , INT_MIN );                     // vuelve el harr[i] el menor valor posible, se vuelve el primer valor del heap
    deleteMin();                                    // elimina el valor del heap
}

void MinHeap::decreaseKey( int i, int newD )        // peor caso se recorre de la hoja de mayor nivel a la raiz
{                                                   // logn
    harr[i] = newD;                                 // reemplaza el nuevo valor
    while( i!=0 && harr[parent(i)] > harr[i] )      // hasta que se llegue a la raiz y cada padre sea mayor
    {
        swap( harr[parent(i)] , harr[i] );          // intercambia padre con hijo
        i = parent(i);                              // guarda indice del padre
    }
}

void MinHeap::print()
{
    for(int i=0;i<heap_size;++i)
        cout<<harr[i]<<' ';
    cout<<'\n';
}

int main()
{
    int arr[]={57,98,39,12,1,15,19,13,21,14,27,31,9};
    MinHeap h(arr,13);
    h.print();
    h.decreaseKey(11,10);
    h.deleteMin();
    h.print();
    h.insert(2);
    h.print();
    h.heapsort();
    h.print();
    h.makeHeap();
    h.print();
    
    h.deleteKey(3);
    h.print();
    cout<<"array 2\n";
    int arr2[]={1,8,6,20,10,9,7};
    MinHeap h2(arr2,7);
    h2.deleteMin();
    h2.print();
    h2.deleteKey(4);
    h2.print();
    
    cout<<"array 3\n";
    MinHeap h3(10);
    h3.insert(20);
    h3.insert(10);
    h3.insert(4);
    h3.insert(80);
    h3.print();

    cout<<"\ntermino \n";
}