#include <iostream>
#include <list>
#include <ostream>
#include "vertex.h"
#include "edge.h"
#include "grafo.h"
using namespace std;

int main()
{
    cout<<"CREANDO GRAFO VACIO\n";
    Grafo<string, int> G;

    cout<<"\nNSERTANDO VERTICES\n";
    G.Insert_Vertex("Arequipa");
    G.Insert_Vertex("Lima");
    G.Insert_Vertex("Cuzco");
    G.Insert_Vertex("Puno");
    G.Insert_Vertex("Ica");
    G.Insert_Vertex("Tacna");
    G.Insert_Vertex("Moquegua");

    cout<<"\nINSERTANDO ARISTAS\n";
    G.Insert_Arista("Arequipa", "Cuzco", 250);
    G.Insert_Arista("Arequipa", "Puno", 20);
    G.Insert_Arista("Ica", "Lima", 10);
    G.Insert_Arista("Lima", "Arequipa", 160);
    G.Insert_Arista("Lima", "Tacna", 15);
    G.Insert_Arista("Puno", "Cuzco", 160);
    G.Insert_Arista("Cuzco", "Moquegua", 160);
    G.Insert_Arista("Tacna", "Moquegua", 160);
    G.Insert_Arista("Moquegua", "Arequipa", 160);
    G.Insert_Arista("Moquegua", "Puno", 160);
    G.Insert_Arista("Moquegua", "Ica", 160);
    G.Insert_Arista("Ica", "Tacna", 160);
    G.Insert_Arista("Puno", "Tacna", 50);

    cout<<"\nMOSTRANDO LISTA DE ADYACENCIA\n";
    G.verAdyacencias();

    cout<<"\nBUSCANDO VERTICE AREQUIPA\n";
    cout<<G.existeVertex("Arequipa");
    cout<<"\nBUSCANDO VERTICE PIURA\n";
    cout<<G.existeVertex("Piura");

    cout<<"\nCOMPROBANDO SI AREQUIPA Y LIMA SON ADYACENTES\n";
    cout<<G.sonAdyacentes("Lima","Arequipa");
    cout<<"\nCOMPROBANDO SI LIMA Y PUNO SON ADYACENTES\n";
    cout<<G.sonAdyacentes("Lima","Puno");


    // cout<<"\nELIMINANDO ARISTA (Arequipa, Lima, 160)\n";
    // G.delete_Arista("Arequipa","Lima",160);

    // cout<<"\nMOSTRANDO LISTA DE ADYACENCIA\n";
    // G.verAdyacencias();

    // cout<<"\nELIMINANDO VERTICE Arequipa\n";
    // G.delete_vertex("Arequipa");

    // cout<<"\nMOSTRANDO LISTA DE ADYACENCIA\n";
    // G.verAdyacencias();

    cout<<"\nGRAFICANDO GRAFO INICIAL\n";
    G.graficar("grafoAntes1.dot");
    system("dot grafoAntes1.dot -o grafoAntes1.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    system("grafoAntes1.png");

    cout<<"\nMOSTRANDO RECORRIDO EN ANCHURA\n";
    G.BFS();

    cout<<"\nMOSTRANDO RECORRIDO EN PROFUNDIDAD\n";
    G.DFS();

    cout<<"\nMOSTRANDO RECORRIDO EN PROFUNDIDAD ITERATIVO\n";
    G.DFS_I();

    cout<<"\nMOSTRANDO RECORRIDO MINIMO ENTRE Arequipa y Lima\n";
    G.shortestPath("Arequipa","Lima");

    cout<<"\nGRAFICANDO EL ARBOL DE EXPANCION MINIMA - KRUSKAL\n";
    G.Kruskal();

    cout<<"\nGRAFICANDO EL ARBOL DE EXPANCION MINIMA - PRIM\n";
    G.Prim();

    return 1;
}