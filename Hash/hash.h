#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

template <class O, class K, int (*fd)(std::string, int), const int size = 11>
class Hash
{
private:
    std::vector<std::list<std::pair<O,K>>> m_List;          // vector de listas, cada lista contiene un par (string y su posicion)
    float lF;                   // load factor
    float n;                    // cantidad de elementos
    float m;                    // cantidad de celdas
public:
    Hash();
    int cantElementos(){ return n; }
    int cantCeldas(){ return m; }
    void Add(O, K);             // O = pos del genoma, clave string
    void rHash();               // reconstruye la tabla hash
    int sigPrimo(int);          

    void find(K);               // busca genoma 
    void Delete(K);             // ingresa string del genoma a eliminar
};

template <class O, class K, int (*fd)(std::string, int), const int size>
Hash<O, K, fd, size>::Hash()
{
    n = 0;
    lF = 0.75;              // factor de carga recomendado
    m = size;
    std::vector<std::list<std::pair<O,K>>> hash(size);                  // crea tabla hash auxiliar
    m_List = hash;                                                      // inicializa tabla hash
}

template <class O, class K, int (*fd)(std::string, int), const int size>
void Hash<O, K, fd, size>::Add(O obj, K key)
{
    int pos = fd(key, m);                                           // obtiene la posicion mediante el string (clave) y la cantidad de celdas
    // std::cout << "indice:" << pos << '\n';
    std::pair<O,K> gen;                                             // crea un par de elementos
    gen.first = obj;                                                // guarda el string que genera la posicion
    gen.second = key;                                               // guarda el indice del string en el genoma
    m_List[pos].push_back(gen);                                     // guarda en alguna posicion de la tabla hash
    n++;                                                            // aumenta la cantidad de datos
    if( n/m >= lF )                                                 // si el factor de carga actual es mayor a 0.75
    {
        std::cout<<"FACTOR DE CARGA EXCEDIDO ("<<n/m<<")\n";
        std::cout<<"REDIMENSIONANDO...\n";
        rHash();                                                    // reconstruye la tabla
        std::cout<<"cantidad de datos: "<<n<<'\n';
        std::cout<<"cantidad de celdas: "<<m<<'\n';
        std::cout<<"factor de carga actual "<<n/m<<"\n\n";
    }
}

template <class O, class K, int (*fd)(std::string, int), const int size>
void Hash<O, K, fd, size>::rHash()                                          // funcion que reconstruye la tabla
{
    int newN = sigPrimo(m);                                                 // nueva cantidad de celdas sera un numero primo
    std::vector<std::list<std::pair<O,K>>> aux = m_List;                    // guarda los valores anteriores en un auxiliar
    m_List.clear();                                                         // borra todos los datos
    m_List.resize(newN);                                                    // agranda el vector
    n=0;                                                                    // cantidad de datos 0
    m = newN;                                                               // nueva cantidad de celdas 
    for( int i=0 ; i<aux.size() ; ++i )                                      
    {
        typename std::list<std::pair<O,K>>::iterator it = aux[i].begin();
        for( ; it != aux[i].end() ; ++it )
            Add( it->first , it->second );              // reinserta los valores con sus nuevos indices
    }
}

bool esPrimo( int n )
{
    for( int i=2 ; i<sqrt(n) ; ++i )
        if( n%i == 0 )
            return false;
    return true;
}

template <class O, class K, int (*fd)(std::string, int), const int size>
int Hash<O, K, fd, size>::sigPrimo( int n )
{
    int primo = 2*n;
    for( ; ; primo++ )
    {
        if( esPrimo(primo) )
            break;
    }
    return primo;
}

template <class O, class K, int (*fd)(std::string, int), const int size>
void Hash< O ,K ,fd,size >::find( K key )
{
    int pos = fd( key , m );
    bool c = 0;
    if( m_List[pos].size() > 0 )
    {
        typename std::list<std::pair<O,K>>::iterator it = m_List[pos].begin();
        for( ; it!=m_List[pos].end() ; ++it )
        {
            if( it->second == key )
            {
                std::cout<<it->first<<' ';
                c=1;
            }
        }
        if( !c )
            std::cout<<"NO HAY REGISTROS GUARDADOS CON ESA CLAVE";
        std::cout<<'\n';
    }
    else
        std::cout<<"NO HAY REGISTROS GUARDADOS CON ESA CLAVE\n";
}

template <class O, class K, int (*fd)(std::string, int), const int size>
void Hash< O ,K ,fd,size >::Delete(  K key )
{
    int pos = fd( key , m );
    bool c = 0;
    if( m_List[pos].size() > 0 )
    {
        typename std::list<std::pair<O,K>>::iterator it = m_List[pos].begin();
        for( ; it!=m_List[pos].end() ; ++it )
        {
            if( it->second == key )
            {
                m_List[pos].remove(*it);
                c=1;
            }
        }
        if( !c )
            std::cout<<"NO HAY REGISTROS GUARDADOS CON ESA CLAVE";
        else    
            std::cout<<"SE ELIMINARON LOS REGISTROS";
        std::cout<<'\n';
    }
    else
        std::cout<<"NO HAY REGISTROS GUARDADOS CON ESA CLAVE\n";
}

#endif