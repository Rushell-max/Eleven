#include<iostream>
#include<fstream>
#include<queue>
#include <utility>
#include <functional>
using namespace std;

template<class T>
class Nodo
{
    public:
       T m_Dato;
       Nodo<T> * m_pSon[3];
       int m_Height;
     // Add the Constructor; 
       Nodo(T d)
       {
           m_Dato = d;
           // Hijo Izquierdo
           m_pSon[0] = 0;
           // Hijo Derecho
           m_pSon[1] = 0;
           // Padre
           m_pSon[2] = 0;
           // Height
           m_Height = 1;
       } 
};

template<class T>
class AVL_Tree
{
    public:
       Nodo<T> * m_pRoot;
    public:
    
       void RDD(Nodo<T> * & p)
       {
           Nodo<T> *q = p->m_pSon[1];
           p->m_pSon[1] = q->m_pSon[0];
           q->m_pSon[0] = p;

           q->m_pSon[2] = p->m_pSon[2];
           p->m_pSon[2] = q;
           
           p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
           q->m_Height = 1 + max(height(q->m_pSon[0]), height(q->m_pSon[1]));
           
           p = q;
       }
       void RII(Nodo<T> * & p)
       {
           Nodo<T> *q = p->m_pSon[0];
           
           p->m_pSon[0] = q->m_pSon[1];
           q->m_pSon[1] = p;

           q->m_pSon[2] = p->m_pSon[2];
           p->m_pSon[2] = q;
           
           p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
           q->m_Height = 1 + max(height(q->m_pSon[0]), height(q->m_pSon[1]));
           
           p = q;
       }
       void RDI(Nodo<T> * & p)
       {
           Nodo<T> *q = p->m_pSon[1];
           Nodo<T> *r = q->m_pSon[0];

           p->m_pSon[1] = r->m_pSon[0];
           if(p->m_pSon[1]) (p->m_pSon[1])->m_pSon[2] = p; 

           q->m_pSon[0] = r->m_pSon[1];
           if(q->m_pSon[0]) (q->m_pSon[0])->m_pSon[2] = q; 

           r->m_pSon[1] = q;
           r->m_pSon[0] = p;
           
           r->m_pSon[2]= p->m_pSon[2];
           q->m_pSon[2] = p->m_pSon[2] = r;
           
           p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
           q->m_Height = 1 + max(height(q->m_pSon[0]), height(q->m_pSon[1]));
           r->m_Height = 1 + max(height(r->m_pSon[0]), height(r->m_pSon[1]));

           p = r;    
       }
       void RID(Nodo<T> * & p)
       {
           Nodo<T> *q = p->m_pSon[0];
           Nodo<T> *r = q->m_pSon[1];

           p->m_pSon[0] = r->m_pSon[1]; 
           if(p->m_pSon[0]) (p->m_pSon[0])->m_pSon[2] = p;

           q->m_pSon[1] = r->m_pSon[0];
           if(q->m_pSon[1]) (q->m_pSon[1])->m_pSon[2] = q; 

           r->m_pSon[0] = q;
           r->m_pSon[1] = p;
           
           r->m_pSon[2]= p->m_pSon[2];
           q->m_pSon[2] = p->m_pSon[2] = r;

           p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
           q->m_Height = 1 + max(height(q->m_pSon[0]), height(q->m_pSon[1]));
           r->m_Height = 1 + max(height(r->m_pSon[0]), height(r->m_pSon[1]));

           p = r;          
        }

       public:
       AVL_Tree() {m_pRoot = 0;}

       int max(int a,int b)
       {
           if(a>b) return a;
           return b;
       }
       int height(Nodo<T> *p)
       {
           if(!p) return 0;
           return p->m_Height;
       }
       void Add(T D)
       {
           Add(D, m_pRoot, NULL);
       }
       bool Add(T D, Nodo<T> *&p, Nodo<T> * padre)
       {
            if(!p) { p = new Nodo<T>(D); p->m_pSon[2] = padre; return true;}            
            if(D == p->m_Dato) return false;
            if ( Add(D, p->m_pSon[p->m_Dato < D], p))
            {
                p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
                int FE = height(p->m_pSon[1]) - height(p->m_pSon[0]);
                if(FE > 1)
                {
                    //print();
                    Nodo<T>* p_tmp = p->m_pSon[1];
                    FE = height(p_tmp->m_pSon[1]) - height(p_tmp->m_pSon[0]);
                    if(FE >= 1) { /**cout<<"\n EN RDD con "<<p->m_Dato<<"\n";**/ RDD(p);/** print();**/  return false; }
                    else if(FE <= 1) { /**cout<<"\n EN RDI con "<<p->m_Dato<<"\n";**/ RDI(p); /**print(); **/return false;}  
                }
                else if(FE < -1)
                {
                    //print();
                    Nodo<T>* p_tmp = p->m_pSon[0];
                    FE = height(p_tmp->m_pSon[1]) - height(p_tmp->m_pSon[0]);
                    if(FE >= 1) { /**cout<<"\n EN RID con "<<p->m_Dato<<"\n";**/ RID(p); /**print();**/ return false;}
                    else if(FE <= 1){/**cout<<"\n EN RII con "<<p->m_Dato<<"\n";**/ RII(p); /**print();**/ return false; }  
                }
                return true;
            }
            return false;
            
       }
       bool Remove(T D)
       {
           return Remove(D, &(m_pRoot));
       }
       bool Remove(T D, Nodo<T>**p_tmp)
       {
           if(!(*p_tmp)) return false;
           if ((*p_tmp)->m_Dato == D)
           {
               if ((*p_tmp)->m_pSon[0] && !(*p_tmp)->m_pSon[1])
               {
                   Nodo<T> *p_tmp1 = *p_tmp;
                   (*p_tmp) = (*p_tmp)->m_pSon[0];
                   (*p_tmp)->m_Height = 1 + max(height((*p_tmp)->m_pSon[0]), height((*p_tmp)->m_pSon[1]));
                   delete p_tmp1;
                   p_tmp1 = 0;
                   return true;
               }
               else if (!(*p_tmp)->m_pSon[0] && (*p_tmp)->m_pSon[1])
               {
                   Nodo<T> *p_tmp1 = *p_tmp;
                   (*p_tmp) = (*p_tmp)->m_pSon[1];
                   (*p_tmp)->m_Height = 1 + max(height((*p_tmp)->m_pSon[0]), height((*p_tmp)->m_pSon[1]));
                   delete p_tmp1;
                   p_tmp1 = 0;
                   return true;
               }
               else if ((*p_tmp)->m_pSon[0] && (*p_tmp)->m_pSon[1])
               {
                   Nodo<T> *p_tmp1 = *p_tmp;
                   Nodo<T> *p_tmp2 = (*p_tmp)->m_pSon[1], *p_tmp3 = (*p_tmp)->m_pSon[1], *p;
                   while (p_tmp2->m_pSon[0])
                   {
                       p = p_tmp2;
                       p_tmp2 = p_tmp2->m_pSon[0];
                   }
                   Nodo<T> *p_tmpSon = p_tmp2->m_pSon[1];
                   p_tmp2->m_pSon[0] = (*p_tmp)->m_pSon[0];
                   if (p_tmp2 != p_tmp3)
                   {
                       p_tmp2->m_pSon[1] = p_tmp3;
                       p->m_pSon[0] = p_tmpSon;
                   }

                   *p_tmp = p_tmp2;
                   (*p_tmp)->m_Height = 1 + max(height((*p_tmp)->m_pSon[0]), height((*p_tmp)->m_pSon[1]));
                   delete p_tmp1;
                   p_tmp1 = 0;
                   return true;
               }
               else
               {
                   delete *p_tmp;
                   *p_tmp = 0;
                   return true;
               }
           }
           if(Remove(D, &((*p_tmp)->m_pSon[(*p_tmp)->m_Dato < D])) )
           {
                (*p_tmp)->m_Height = 1 + max(height((*p_tmp)->m_pSon[0]), height((*p_tmp)->m_pSon[1]));
                int FE = height((*p_tmp)->m_pSon[1]) - height((*p_tmp)->m_pSon[0]);
                if(FE > 1)
                {
                    //print();
                    Nodo<T>* p_tmp1 = (*p_tmp)->m_pSon[1];
                    FE = height(p_tmp1->m_pSon[1]) - height(p_tmp1->m_pSon[0]);
                    if(FE >= 1) { /**cout<<"\n EN RDD con "<<p->m_Dato<<"\n";**/ RDD(*p_tmp);/** print();**/  return false; }
                    else if(FE <= 1) { /**cout<<"\n EN RDI con "<<p->m_Dato<<"\n";**/ RDI(*p_tmp); /**print(); **/return false;}  
                    else {RDD(*p_tmp); return false;}
                }
                else if(FE < -1)
                {
                    //print();
                    Nodo<T>* p_tmp1 = (*p_tmp)->m_pSon[0];
                    FE = height(p_tmp1->m_pSon[1]) - height(p_tmp1->m_pSon[0]);
                    if(FE >= 1) { /**cout<<"\n EN RID con "<<p->m_Dato<<"\n";**/ RID(*p_tmp); /**print();**/ return false;}
                    else if(FE <= 1){/**cout<<"\n EN RII con "<<p->m_Dato<<"\n";**/ RII(*p_tmp); /**print();**/ return false; }  
                    else {RII(*p_tmp); return false;}
                }
                return true;  
           }
           return false;
        }
       void calcularHeight()
       {
           calcularHeight(m_pRoot);
       }
       void calcularHeight(Nodo<T>*p)
       {
           if (!p) return;
           calcularHeight(p->m_pSon[0]);
           calcularHeight(p->m_pSon[1]);
           p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
       }
       void print()
       {
           print(m_pRoot);
       }
       void print(Nodo<T> *r)
       {
            if(!r) return;
            cout<<" HEIGHT> "<<r->m_Height<<" dir> "<<r<<" _ data> "<<r->m_Dato<<" _ dirdirLEFT> "<<&r->m_pSon[0]<<" _ dirdirRIGHT> "<<&r->m_pSon[1]<<" _ dirdirPADRE> "<<&r->m_pSon[2]<<" _ dirLEFT> "<<r->m_pSon[0]<<" _dirRIGHT> "<<r->m_pSon[1]<<" _dirPADRE> "<<r->m_pSon[2]<<"\n";
            print(r->m_pSon[0]);
            print(r->m_pSon[1]);           
       }
       void dibujar()
       {
           ofstream archivo;
           archivo.open("E:\\Projects\\First_Year\\Laboratorio_ED_II\\Graphviz\\bin\\AVL_HEIGHT.dot");
           archivo << "digraph B {\n";
           dibujar(m_pRoot, archivo);
           archivo << "\n}";
           archivo.close();
           //system("E: & cd Projects & cd First_Year & cd Laboratorio_ED_II & cd Graphviz & cd bin & dot AVL_HEIGHT.dot -o AVL_HEIGHT.png -Tpng & AVL_HEIGHT.png");
       }
       void dibujar(Nodo<T> *r, ofstream & archivo)
        {
            if(!r) return;
            archivo <<  r->m_Dato << "[label = \"" << r->m_Dato <<" | "<< r->m_Height <<"\" ]; \n";
            if(r->m_pSon[0]) archivo << r->m_Dato << " -> " << r->m_pSon[0]->m_Dato << ";\n";
            if(r->m_pSon[1]) archivo << r->m_Dato << " -> " << r->m_pSon[1]->m_Dato << ";\n";
            dibujar(r->m_pSon[0], archivo);
            dibujar(r->m_pSon[1], archivo);
        }
       
       Nodo<T>* Find (T D)
       {
            if(!m_pRoot) return false;
            Nodo<T> *p_tmp = m_pRoot;
            while(p_tmp)
            {
                if(p_tmp->m_Dato == D) return p_tmp;
                p_tmp = p_tmp->m_pSon[p_tmp->m_Dato < D];
            }
            return NULL;
       }
       Nodo<T>* Minimun(AVL_Tree<T> y)
       {
           if(!y.m_pRoot) return NULL;
           Nodo<T> *p_tmp = y.m_pRoot;
           while(p_tmp->m_pSon[0])
           {
               p_tmp = p_tmp->m_pSon[0];
           }

           return p_tmp;
       }
};


template<class O, class K,  int (*fd)(string ,int), const int size = 1 >
class Hash
{
   public:
      AVL_Tree<O>  m_list[size];
   public:
       Hash(){};
       void Add(O obj, K key) 
       { 
           int pos = fd(key,size);
           //cout<<"Se insertó elemento en la posición:"<<pos<<endl;
           m_list[pos].Add(obj);     
       }
       void Delete(K key)
       {
           int pos = fd(key,size);
           for(auto it = m_list[pos].begin(); it != m_list[pos].end(); ++it) 
           {
               if((*it).codigo == key) 
               { 
                   cout<<" Eliminando - pos> "<<pos<<" Codigo> "<<(*it).codigo<<" Nombre> "<<(*it).Nombre<<endl;
                   m_list[pos].Remove();
                   return;
               }
           }
       }
       O find(K key)
       {
           int pos = fd(key,size);
           for(auto n : m_list[pos]) 
               if(n.codigo == key) { cout<<" Encontré - pos> "<<pos<<" Codigo> "<<n.codigo<<" Nombre> "<<n.Nombre<<endl; return n; }
           return NULL;
       }
       void print()
       {
           for(int i=0; i<size; i++)
               for(auto n : m_list[i]) cout<<" Posicion> "<<i<<" Codigo> "<<n.codigo<<" Nombre> "<<n.Nombre<<endl;
       }
};

#include<vector>
int levenshtein(const string &s1, const string &s2)
{
   int N1 = s1.size();
   int N2 = s2.size();
   int i, j;
   vector<int> T(N2+1);

   for ( i = 0; i <= N2; i++ )
      T[i] = i;

   for ( i = 0; i < N1; i++ ) 
   {
      T[0] = i+1;
      int corner = i;
      for ( j = 0; j < N2; j++ ) 
      {
         int upper = T[j+1];
         if ( s1[i] == s2[j] )
            T[j+1] = corner;
         else
            T[j+1] = min(T[j], min(upper, corner)) + 1;
         corner = upper;
      }
   }
   return T[N2];
}

int fd1(string key, int n)
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

unsigned int edit_distance(const std::string& s1, const std::string& s2)
{
	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector <std::vector <unsigned int> > d(len1 + 1, std::vector <unsigned int >(len2 + 1));
	
	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;
	for(unsigned int i = 1; i <= len1; ++i)
	for(unsigned int j = 1; j <= len2; ++j)
	// note that std::min({arg1 , arg2 , arg3}) works only in C++11 ,
	// for C++98 use std::min(std::min(arg1 , arg2), arg3)
	d[i][j] = std::min(std::min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
	return d[len1][len2];
}

void RecorrerDict(Nodo<string> *inp, Nodo<string> *dicc, queue<pair<string, int>>& parecidas)
{
    if(!dicc) return;
    unsigned int dist = edit_distance(dicc->m_Dato, inp->m_Dato);
    if(parecidas.front().second == dist ) parecidas.push(make_pair(dicc->m_Dato, dist));
    if(dist < parecidas.front().second) 
    {
        while(!parecidas.empty()) parecidas.pop();
        parecidas.push(make_pair(dicc->m_Dato, dist));
    }
    RecorrerDict(inp, dicc->m_pSon[0], parecidas);
    RecorrerDict(inp, dicc->m_pSon[1], parecidas);
}

void recorrerInput(Nodo<string> *inp,  Hash<string, string, fd1>& dict, queue<pair<string, int>>& parecidas)
{
    if(!inp) return;
    Nodo<string>* dicc = dict.m_list[0].m_pRoot;
    unsigned int dist = edit_distance(inp->m_Dato, dicc->m_Dato);
    parecidas.push(make_pair(dicc->m_Dato, dist));

    for(int i=0; i<1; i++) RecorrerDict(inp, dict.m_list[i].m_pRoot, parecidas);

    int opcion;
    if (parecidas.size()>1)
    {
        queue<pair<string, int>> aux = parecidas;
        cout<<"\n OPCIONES \n"; int i=1;
        while(!aux.empty()) {cout<<" Opcion "<<i<<" - "<<aux.front().first<<" "<<aux.front().second<<endl; aux.pop(); i++;}
        cout<<" Opcion> ";cin>>opcion;
        i = 1;
        while(i!=opcion)
        {
            parecidas.pop();
            i++;
        }
    }
    cout<<"\n Corregida por "<<parecidas.front().first<<endl;

    while(!parecidas.empty()) { parecidas.pop();}
    
    recorrerInput(inp->m_pSon[0], dict, parecidas);
    recorrerInput(inp->m_pSon[1], dict, parecidas);
}

void Output(Hash<string, string, fd1>& input, Hash<string, string, fd1>& dict) 
{
    for(int i=0; i<1; i++) 
    {
        Nodo<string>* inp = input.m_list[i].m_pRoot; 
        queue <pair<string, int>> parecidas; 
        recorrerInput(inp, dict, parecidas);
    } 
}


int main()
{
    Hash<string, string, fd1> Diccionario;
    Hash<string, string, fd1> Input;

    char palabra[100];
    ifstream diccionario("engmix.txt");
    int i=0;
    while(!diccionario.eof())
    {
        diccionario>>palabra;
        Diccionario.Add(palabra, palabra);
        //if(i!=100) cout<<"Numero de palabras procesadas :"<<i<<endl;
        i++;
    }
    Diccionario.m_list[0].dibujar();
    diccionario.close();

    int a; cin>>a;
    ifstream input("input.txt");
    while(!input.eof())
    {
        input>>palabra;
        Input.Add(palabra, palabra);
    }
    input.close();
    Input.m_list[0].dibujar();

    Output(Input, Diccionario);

    return 1;
};
