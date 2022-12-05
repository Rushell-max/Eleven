#include <iostream>
#include <sstream>
using namespace std;
int main()
{
    string a;getline(cin,a);
    stringstream linea(a);
    cout<<a<<'\n';
    string palabra;
    getline(linea,palabra,' ');
    cout<<palabra<<'\n';
    getline(linea,palabra,' ');
    cout<<palabra<<'\n';
    getline(linea,palabra,' ');
    cout<<palabra<<'\n';
}