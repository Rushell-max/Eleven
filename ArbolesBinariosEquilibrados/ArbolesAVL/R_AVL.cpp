#include<iostream>
#include <fstream>
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
    private:
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
           archivo << "graph B {\n";
           dibujar(m_pRoot, archivo);
           archivo << "\n}";
           archivo.close();
           //system("E: & cd Projects & cd First_Year & cd Laboratorio_ED_II & cd Graphviz & cd bin & dot AVL_HEIGHT.dot -o AVL_HEIGHT.png -Tpng & AVL_HEIGHT.png");
       }
       void dibujar(Nodo<T> *r, ofstream & archivo)
        {
            if(!r) return;
            archivo <<  r->m_Dato << "[label = \"" << r->m_Dato <<" | "<< r->m_Height <<"\" ]; \n";
            if(r->m_pSon[0]) archivo << r->m_Dato << " -- " << r->m_pSon[0]->m_Dato << ";\n";
            if(r->m_pSon[1]) archivo << r->m_Dato << " -- " << r->m_pSon[1]->m_Dato << ";\n";
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

// RDD
int test1()
{
    AVL_Tree<int> A; 
    A.Add(4);   A.print();
    A.Add(14);  A.print();
    A.Add(24);  A.print();
    cout<<"The test1 work perfectly. Nice work :)"<<endl;
   
    return 1;
}
// RII
int test2()
{
    AVL_Tree<int> A; 
    A.Add(24);   A.print();
    A.Add(14);   A.print();
    A.Add(2);    A.print();
    cout<<"The test2 work perfectly. Good Work :)"<<endl;
    return 1;
}
// RDI
int test3()
{
    AVL_Tree<int> A; 
    A.Add(4);   A.print();
    A.Add(14);  A.print();
    A.Add(10);  A.print();
    cout<<"The test3 work perfectly. Good Work :)"<<endl;
    return 1;
}
// RID
int test4()
{
    AVL_Tree<int> A; 
    A.Add(24);  A.print();
    A.Add(14);  A.print();
    A.Add(18);  A.print();
    cout<<"The test4 work perfectly. Good Work :)"<<endl;
    return 1;
}

int test5()
{
    AVL_Tree<int> A; 
    A.Add(100);
    A.Add(50);
    A.Add(200);
    A.Add(80);
    A.Add(150);
    A.Add(400);
    A.Add(125);
    A.Add(600);

    A.dibujar();

    A.Remove(80);
    A.dibujar();

    return 1;
}

// FINAL
int test6()
{
    AVL_Tree<int> A; 
    // Insert the correct includes
    srand(10); 
    for(int i=0;i<13;i++)
    {
        // Insert the correct includes 
        int a;//=rand()%1000;
        cout<<"\n INSERTANDO ";cin>>a;
        
        A.Add(a);
    }


    A.print();
    A.dibujar();

    int a;
    cout<<" El menor elemento del arbol es > "<<A.Minimun(A)->m_Dato;
    //cout<<" Eliminando> ";cin>>a;
    //A.Remove(a);

    A.dibujar();
    return 1;
}

 
int main()
{
    cout<<"Begin test "<<endl;
    //test1();
    //test2();
    //test3();
    //test4();
    
    //test5();

    test6();
    
    
    return 1;
}