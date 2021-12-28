#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include "hash.h"
   
using namespace std;

int fd1(string key, int n)          // prueba
{
    int s=0;
    char * k = (char*)key.c_str();
    while(*k)
    {
      s+=int(*k);
      k++;   
    }
    return s%n;
}

int FHash( string key, int n )      // funcion que transforma el genoma en una posicion
{
    int pos=0;
    int primo=31;
    for( int i=0 ; i<key.size() ; ++i )
    {
        pos = (primo*pos + (int)key[i]) %n;
    }
    return pos;
}

string leer( string dir )          // leer archivo y retorna cadena
{
    ifstream lee;                   //variable para abrir el archivo y leer
    stringstream contenido;         //variable que guarda todo el texto del archivo

    lee.open(dir);                  //abre el archivo

    contenido<<lee.rdbuf();         //contenido guarda todo el texto
    string texto(contenido.str());          //el texto se pasa de contenido a la variable string texto

    lee.close();    //cierra el archivo
    return texto;
}

int main()
{
    Hash<int,string, FHash> Tabla;         // almacena string (clave) y int (valor)
    cout<<"INSERTANDO TODAS LAS CADENAS DE AMINOACIDOS...\n";
    string genoma = leer("sequence.fasta");
    for( int i=0 ; i<genoma.size() ; i+=7 )
        Tabla.Add( i , genoma.substr(i,7) );
    // for( int i=0,j=0 ; j<15 ; i+=7 ,j++)
    //     Tabla.Add( i , genoma.substr(i,7) );
    
    Tabla.Add(4,"AGGTAAC");
    Tabla.Add(7,"AGGTAAC");
    Tabla.Add(8,"AGGTAAC");
    Tabla.Add(14,"AGGTACA");
    cout<<"\nBUSCANDO \"AGGTAAC\"...\n";
    Tabla.find("AGGTAAC");          // existe
    cout<<"\nBUSCANDO \"ATTAAAG\"...\n";
    Tabla.find("ATTAAAG");          // existe
    cout<<"\nBUSCANDO \"GTCCGGG\"...\n";
    Tabla.find("GTCCGGG");          // no existe

    cout<<"\nBORRANDO \"AGGTAAC\"...\n";
    Tabla.Delete("AGGTAAC");        // elimina
    cout<<"\nBORRANDO \"AGGTAAC\"...\n";
    Tabla.find("AGGTAAC");          // no existe
    cout<<"\nBORRANDO \"GTCCGGG\"...\n";
    Tabla.Delete("GTCCGGG");        // no existe

    return 1;
};


