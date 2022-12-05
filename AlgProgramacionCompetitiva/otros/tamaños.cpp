#include <bits/stdc++.h>
using namespace std;
int main(){
    int n=2147483647;   //(2^31)-1 -> numero que ocupa 31 bits + 1 (4 bytes) del signo
                        //este es el max numero que puede guardar un entero
                        //tiene 10 digitos
    cout<<n<<'\n';
    cout<<sizeof(n);
}