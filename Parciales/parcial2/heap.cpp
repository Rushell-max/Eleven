#include <iostream>
using namespace std;

void print(int *v, int n)
{

    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;
}

// Esta función permite arreglar un heap cuya valor en la posición i
// esta equivocado, mientras que ambos hijos son heaps correctos.
void heap_fy(int i, int *v, int n, int &c)
{
    if(i<n/2)
    {
        int l = (i*2)+1;
        int r = (i*2)+2;
        int m=i;
        if( l < n && v[l] > v[m] )
            m = l;
        if( r < n && v[r] > v[m] )
            m = r;
        if( m==i )
            return;
        std::swap(v[m],v[i]);
        heap_fy(m,v,n,c);
    }
}

// Esta función debe crear un binary masx heap es un tiempo O(nlogn)
void make_heap(int *v, int n)
{
    int c=0;
    for(int i=0;i<n;++i)
        heap_fy(i,v,n,c);
}

// Esta función debe sumar el número de valores que son hoja dentro del max heap
int sumar_hojas(int *v, int n)
{
    int sum=0;
    for(int i=n/2;i<n;++i)
        sum+=v[i];
    return sum;
}
void Test3()
{
    const int n = 1000;
    int v[n];
    int c = 0;
    for (int i = 0; i < n; i++)
        v[i] = rand() % 100;
    make_heap(v, n);
    cout << "The sum of all the sheets of the binary heap after creating the max_heap is : " << sumar_hojas(v, n) << endl;
}
