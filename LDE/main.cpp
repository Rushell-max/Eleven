#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;
int main()
{
    LinkedList<int> L1;
    L1.push_front(5);
    L1.push_front(10);
    L1.push_front(4);
    L1.push_front(1);
    L1.push_front(0);
    L1.push_back(1);
    cout<<"\n###########################LISTA 1###########################\n";
    L1.print();
    L1.reversePrint();
    cout<<"TAMANIO LSITA 1: "<<L1.size()<<'\n';
    L1.remove(1);
    cout<<"\n###########################LISTA 1###########################\n";
    L1.print();
    L1.reversePrint();

    LinkedList<int> L2;
    L2.push_back(24);
    L2.push_back(4);
    L2.push_back(1);
    L2.push_back(7);
    L2.push_back(10);
    cout<<"\n###########################LISTA 2###########################\n";
    L2.print();
    L2.reversePrint();
    cout<<"\n###########################UNION LISTA 1 CON LISTA 2###########################\n";
    L1.Union(L2);
    L1.print();
    L1.reversePrint();
    cout<<"TAMANIO LISTA 2: "<<L1.size()<<'\n';

    LinkedList<int> L3;
    L3 = L1;
    cout<<"\n###########################LISTA 3###########################\n";
    L3.print();
    L3.reversePrint();
}