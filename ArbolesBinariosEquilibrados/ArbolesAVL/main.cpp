#include <bits/stdc++.h>
#include "binarytree.h"

using namespace std;

int main()
{
    srand(9);
    Binary_Tree<int> B;
    // B.insert(45);
    // B.insert(20);
    // B.insert(60);
    // B.inOrder();
    // B.preOrder();
    // B.postOrder();
    // B.print();
    // B.insert(50);
    // B.insert(70);
    // B.inOrder();
    // B.preOrder();
    // B.postOrder();
    // B.print();
    // B.insert(55);
    // B.inOrder();
    // B.preOrder();
    // B.postOrder();
    // B.print();
    // B.insert(75);
    // B.inOrder();
    // B.preOrder();
    // B.postOrder();
    // B.print();
    // B.insert(10);
    // B.inOrder();
    // B.preOrder();
    // B.postOrder();
    // B.print();
    // ejemplo 2
    B.insert(4);
    B.insert(80);
    B.insert(6);
    B.insert(11);
    B.insert(22);
    B.insert(52);
    B.insert(54);
    B.insert(34);
    B.insert(1);
    B.insert(21);
    B.insert(65);
    B.insert(5);
    B.insert(2);
    B.insert(12);
    B.insert(23);
    B.print();
    cout<<B.size()<<'\n';
    B.graficar("arbolAVL.dot");
    system("dot arbolAVL.dot -o arbolAVL.png -Tpng");       // "dot arbolBinario.dot -o arbolBinario.png -Tpng"
    system("arbolAVL.png");
}