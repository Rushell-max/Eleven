#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <set>
#include "bheap.h"

using namespace std;

int main(){
    ofstream os;
    os.open("antes.dot");
    srand(time(NULL));
    BHeaps<int> BH;
    set<int> norep;
    for(int i=0;i<50;++i){
        norep.insert(250+rand()%(421-250));
    }
    //Insercion de elementos unicos
    for(int i:norep){
        BH.Insert(i);
    }
    //Primer resultado del heap
    cout<< "Elemento minimo encontrado: "<<BH.GetMin()<<'\n'; // Dato min
    BH.Show_Dot(os);
    os.close();
    system("dot -Tjpg -O antes.dot");
    system("antes.dot.jpg");
    //Extraccion del minimo elemento
    BH.Extrac_Min();
    cout<< "Elemento minimo encontrado: " << BH.GetMin()<<'\n'; // Dato min
    ofstream os2;
    os2.open("despues.dot");
    //Segundo resultado despues de la aplicacion del Extrac_Min();
    BH.Show_Dot(os2);
    os2.close();
    system("dot -Tjpg -O despues.dot");
    system("despues.dot.jpg");
    return 1;
}