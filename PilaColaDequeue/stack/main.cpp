#include <bits/stdc++.h>
#include "stack.h"

using namespace std;

int main()
{
    Stack<int> S;
    S.push(10);
    S.push(5);
    S.push(20);
    S.push(14);
    S.print();
    S.pop();
    S.pop();
    S.pop();
    S.pop();
    S.push(140);
    S.push(54);
    S.push(240);
    S.push(144);
    S.print();

}