#include <bits/stdc++.h>
#include "queue.h"

using namespace std;

int main()
{
    Queue<int> Q;
    Q.enqueue(15);
    Q.enqueue(1);
    Q.enqueue(5);
    Q.print();

    Q.dequeue();
    Q.dequeue();
    Q.dequeue();
    Q.enqueue(14);
    Q.enqueue(14);
    Q.enqueue(14);
    Q.print();

}