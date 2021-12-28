
#include "heap.cpp"
#include "sparce.cpp"

int main()
{
    srand(777);

    Sparce<int, 500, 500> M;
    Set_Date(M);
    cout << "Lectura de Datos concluida ..." << endl;

    // Test1(M);
    Test2(M);
    Test3();

    return 1;
};