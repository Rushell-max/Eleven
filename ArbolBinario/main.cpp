#include <iostream>
#include "searchbinarytree.h"
using namespace std;

int main()
{
	cout<<"\nCREACION DE ARBOL BINARIO DE BUSQUEDA VACIO\n";
	SearchBinaryTree<int> A;
	cout<<"\nINSERTANDO ELEMENTOS\n";
	cout<<"INSERTANDO 30, 20, 45, 25, 40, 56, 15, 70, 5, 2, 10\n";
	A.insert(30);
	A.insert(20);
	A.insert(45);
	A.insert(25);
	A.insert(40);
	A.insert(56);
	A.insert(15);
	A.insert(70);
	A.insert(5);
	A.insert(2);
	A.insert(10);
	cout<<"\nTAMANIO DEL ARBOL: "<<A.size()<<'\n';
	cout<<"\nMOSTRANDO ARBOL PREORDEN\n";
	cout<<A.preOrder();
	cout<<"\nMOSTRANDO ARBOL INORDEN\n";
	cout<<A.inOrder();
	cout<<"\nMOSTRANDO ARBOL POSTORDEN\n";
	cout<<A.postOrder();

	cout<<"\n\nGRAFICANDO ARBOL\n";
	A.graficar("antes_de_eliminar.dot");
	system("dot antes_de_eliminar.dot -o antes_de_eliminar.png -Tpng");             // "dot arbolBinario.dot -o arbolBinario.png -Tpng"
    system("antes_de_eliminar.png");

	cout<<"\nELIMINANDO NODO 45\n";
	if( A.remove(45) )
	{
		cout<<"\nTAMANIO DEL ARBOL: "<<A.size()<<'\n';
		cout<<"\nMOSTRANDO ARBOL PREORDEN\n";
		cout<<A.preOrder();
		cout<<"\nMOSTRANDO ARBOL INORDEN\n";
		cout<<A.inOrder();
		cout<<"\nMOSTRANDO ARBOL POSTORDEN\n";
		cout<<A.postOrder();
	}
	cout<<"\n\nBUSCANDO ELEMENTO 25: ";
	if( A.find( 25 ) )
		cout<<"se encontro\n";
	else cout<<"no se encontro\n";
	cout<<"\nBUSCANDO ELEMENTO 45: ";
	if( A.find( 45 ) )
		cout<<"se encontro\n";
	else cout<<"no se encontro\n";

	cout<<"\nGRAFICANDO ARBOL\n";
	A.graficar("despues_de_eliminar.dot");
	system("dot despues_de_eliminar.dot -o despues_de_eliminar.png -Tpng");             // "dot arbolBinario.dot -o arbolBinario.png -Tpng"
    system("despues_de_eliminar.png");

	cout<<"\nVACIANDO ARBOL\n";
	A.clear();
	cout<<"\nTAMANIO DEL ARBOL: "<<A.size()<<'\n';
	cout<<"\nBUSCANDO ELEMENTO 25: ";
	if( A.find( 25 ) )
		cout<<"se encontro\n";
	else cout<<"no se encontro\n";
	cout<<"\nBUSCANDO ELEMENTO 30: ";
	if( A.find( 30 ) )
		cout<<"se encontro\n";
	else cout<<"no se encontro\n";
	cout<<"\nBUSCANDO ELEMENTO 40: ";
	if( A.find( 40 ) )
		cout<<"se encontro\n";
	else cout<<"no se encontro\n";

	cout<<"\nGRAFICANDO ARBOL\n";
	A.graficar("arbol_vacio.dot");
	system("dot arbol_vacio.dot -o arbol_vacio.png -Tpng");             // "dot arbolBinario.dot -o arbolBinario.png -Tpng"
    system("arbol_vacio.png");
}