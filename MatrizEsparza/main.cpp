#include <iostream>
#include "sparsematrix.h"

using namespace std;

int main()
{
    cout<<"CREANDO MATRIZ POCO DENSA\n";
    SparseMatrix<int> M;
    cout<<"MOSTRANDO ELEMENTOS INSERTADOS EN LA MATRIZ\n\n";
    for (int i = 0; i < 10; i++)
        M.insert(i, i, i);
    M.mostrar();
    cout<<"\nINSERTANDO NUMERO 9 en la posicion 2,9n\n";
    M.insert(9 ,1 , 9);
    M.insert(8 ,2 , 9);
    M.mostrar();
    cout<<"\nELIMINANDO NUMERO en la posicion 2,9\n\n";
    M.eliminar(1 , 9);
    M.mostrar();
    std::cout<<"\nEl mayor es: "<<M.buscarMayor(0)<<'\n';
    std::cout<<"\nEl menor es: "<<M.buscarMenor(10)<<'\n';
    // cout<<"filas intercambiadas: "<<M.Intercambiar_Fils(1,2)<<'\n';
    // M.mostrar();
    return 1;
};