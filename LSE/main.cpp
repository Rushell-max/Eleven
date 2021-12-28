#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;
int main()
{
    LinkedList<int> L1;
    int n = 5;
    while (n--) L1.insert(n);
    L1.print();
    L1.insert(0);
    L1.insert(4);
    L1.print();
    L1.remove(0);
    L1.print();
    cout<<"tamanio: "<<L1.size()<<'\n';
    LinkedList<int> L2 ;
    L2.insert(25);
    L2.push_back(5);
    L2.print();
    L2 = L1;
    L1.print();
    L2.print();
    cout<<"tamanio: "<<L2.size()<<'\n';
    if (L1==L2)
        cout<<"iguales"<<'\n';
}