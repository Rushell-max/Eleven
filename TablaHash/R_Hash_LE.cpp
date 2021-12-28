#include<iostream>
#include<list>
   
using namespace std;


template<class O, class K,  int (*hash)(string ,int), int size >
class Hash
{
   private:
      list<O*>  m_list[size];
   public:
       Hash(){};
       void Insert(O* obj, K key)
       { 
           int pos = hash(key,size);
           cout<<"Se inserto elemento en la posicion:"<<pos<<endl;
           m_list[pos].push_back(obj);     
       }
       void Remove(K key)
       {
           int pos = hash(key,size);
           for(auto it = m_list[pos].begin(); it != m_list[pos].end(); ++it) 
           {
               if((*it)->codigo == key) 
               { 
                   cout<<" Eliminando - pos> "<<pos<<" Codigo> "<<(*it)->codigo<<" Nombre> "<<(*it)->Nombre<<endl;
                   m_list[pos].erase(it);
                   return;
               }
           }
           cout<<" No se encontró para eliminar "; 
       }
       O* Search(K key)
       {
           int pos = hash(key,size);
           for(auto n : m_list[pos]) 
               if(n->codigo == key) { cout<<" Encontré - pos> "<<pos<<" Codigo> "<<n->codigo<<" Nombre> "<<n->Nombre<<endl; return n; }
           cout<<" No encontré "<<endl;
           return NULL;
       }
       void print()
       {
           for(int i=0; i<size; i++)
               for(auto n : m_list[i]) cout<<" Posicion> "<<i<<" Codigo> "<<n->codigo<<" Nombre> "<<n->Nombre<<endl;
       }
};

int hash1(string key, int n)
{
    int s = 0; // s = suma // k = iterador // n = size 
    char *k = (char*)key.c_str();
    while(*k)
    {
      s+=int(*k);
      k++;   
    }
    return s%n;
}

class Persona
{
    public:
        string codigo;
        string Nombre;
    public:    
        Persona(string n, string c)
        {
            Nombre = n;
            codigo = c;
        };
};

int main()
{
    Hash<Persona, string, hash1, 15> Tabla;

    Persona *A1, *A2, *A3, *A4, *A5;
    
    A1 = new Persona("Juan", "2312");
    A2 = new Persona("Luis", "2712");
    A3 = new Persona("Carlos", "1372");
    A4 = new Persona("Maria", "2381");
    A5 = new Persona("Lucy", "1832");
    
    // Insert
    Tabla.Insert(A1, A1->codigo);
    Tabla.Insert(A2, A2->codigo);
    Tabla.Insert(A3, A3->codigo);
    Tabla.Insert(A4, A4->codigo);
    Tabla.Insert(A5, A5->codigo);

    Tabla.print();

    // Remove
    Tabla.Remove("2312");
    Tabla.Remove("1832");

    Tabla.print();

    // Search
    Tabla.Search("2312");
    Tabla.Search("2712");

    return 1;
};
