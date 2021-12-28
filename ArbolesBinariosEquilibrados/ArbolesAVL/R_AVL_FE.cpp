// AVL CON Factor de equilibrio (FE) 
#include<iostream>
#include <cmath>
#include <fstream>
using namespace std;

template<class T>
class Nodo
{
    public:
       T m_Dato;
       Nodo<T> * m_pSon[3];
       int FE;
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
           // FE
           FE = 0;
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
           
           if(q->FE == 1) p->FE = q->FE = 0;
           else if(q->FE == 0) p->FE = 1;
           
           p = q;
       }
       void RII(Nodo<T> * & p)
       {
           Nodo<T> *q = p->m_pSon[0];
           
           p->m_pSon[0] = q->m_pSon[1];
           q->m_pSon[1] = p;

           q->m_pSon[2] = p->m_pSon[2];
           p->m_pSon[2] = q;
           
           if(q->FE == -1) p->FE = q->FE = 0;
           else if(q->FE == 0) p->FE = -1;
           
           p = q;
       }
       // RII = 0 Y RDD = 1
       void RS(Nodo<T> * &p, bool l)
       {
           Nodo<T> * q = p->m_pSon[l];
           p->m_pSon[l] = q->m_pSon[!l];
           q->m_pSon[!l] = p;

           q->m_pSon[2] = p->m_pSon[2];
           p->m_pSon[2] = q;
           
           if(q->FE == 1 || q->FE == -1) p->FE = q->FE = 0;
           else if(q->FE == 0 && !l) p->FE = -1;
           else if(q->FE == 0 && l) p->FE = 1;

           p=q; 
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

           if (q->m_pSon[0] && p->m_pSon[1]){
               if (q->m_pSon[1]) q->FE = 0;
               else q->FE = -1;
               if (p->m_pSon[0]) p->FE = 0;
               else p->FE = 1;
               r->FE = 0;
           } else if (q->m_pSon[0]){
               if (q->m_pSon[1]) q->FE = 0;
               else q->FE = -1;
               if (p->m_pSon[0]) { p->FE = -1; r->FE = 0; }
               else p->FE = 0;
           } else if (p->m_pSon[1]){
               if (q->m_pSon[1]) { q->FE = 1; r->FE = 0; }
               else q->FE = 0;
               if (p->m_pSon[0]) p->FE = 0;
               else p->FE = 1;
           } else p->FE = q->FE = 0;

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
           
           if (q->m_pSon[1] && p->m_pSon[0]) {
               if(q->m_pSon[0]) q->FE = 0; 
               else q->FE = 1;
               if(p->m_pSon[1]) p->FE = 0;
               else p->FE = -1;
               r->FE = 0;
           } else if(q->m_pSon[1]){
               if(q->m_pSon[0]) q->FE = 0; 
               else q->FE = 1;
               if(p->m_pSon[1]) { p->FE = 1; r->FE = 0; }
               else p->FE = 0;
           } else if (p->m_pSon[0]){
               if(q->m_pSon[0]){ q->FE = -1; r->FE = 0; }
               else q->FE = 0;
               if(p->m_pSon[1]) p->FE = 0;
               else p->FE = -1;
           } else p->FE = q->FE = 0;

           p = r;          
       }
        // RID = 0 Y RDI = 1
        void RD(Nodo<T> * &p, bool l)
        {
            Nodo<T> * q =  p->m_pSon[l];
            Nodo<T> * r =  q->m_pSon[!l];
            
            p->m_pSon[l] = r->m_pSon[!l];
            if(p->m_pSon[l]) (p->m_pSon[l])->m_pSon[2] = p;

            q->m_pSon[!l] = r->m_pSon[l];
            if(p->m_pSon[!l]) (p->m_pSon[!l])->m_pSon[2] = p;
            
            r->m_pSon[l] = q;
            r->m_pSon[!l] = p;
            
            r->m_pSon[2]= p->m_pSon[2];
            q->m_pSon[2] = p->m_pSon[2] = r;
            
            if(p->FE == 2) {
                if (q->m_pSon[0] && p->m_pSon[1]){
                    if (q->m_pSon[1]) q->FE = 0;
                    else q->FE = -1;
                    if (p->m_pSon[0]) p->FE = 0;
                    else p->FE = 1;
                    r->FE = 0;
                } else if (q->m_pSon[0]){
                    if (q->m_pSon[1]) q->FE = 0;
                    else q->FE = -1;
                    if (p->m_pSon[0]) { p->FE = -1; r->FE = 0; }
                    else p->FE = 0;
                } else if (p->m_pSon[1]){
                    if (q->m_pSon[1]) { q->FE = 1; r->FE = 0; }
                    else q->FE = 0;
                    if (p->m_pSon[0]) p->FE = 0;
                    else p->FE = 1;
                } else p->FE = q->FE = 0;
            }else {
                if (q->m_pSon[1] && p->m_pSon[0]) {
                    if(q->m_pSon[0]) q->FE = 0; 
                    else q->FE = 1;
                    if(p->m_pSon[1]) p->FE = 0;
                    else p->FE = -1;
                    r->FE = 0;
                } else if(q->m_pSon[1]){
                    if(q->m_pSon[0]) q->FE = 0; 
                    else q->FE = 1;
                    if(p->m_pSon[1]) { p->FE = 1; r->FE = 0; }
                    else p->FE = 0;
                } else if (p->m_pSon[0]){
                    if(q->m_pSon[0]){ q->FE = -1; r->FE = 0; }
                    else q->FE = 0;
                    if(p->m_pSon[1]) p->FE = 0;
                    else p->FE = -1;                    
                } else p->FE = q->FE = 0;
            }
            
            p = r;        
        }


       public:
       AVL_Tree() {m_pRoot = 0;}
            
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
                if(p->m_Dato < D == 0) {p->FE -= 1;}
                else if(p->m_Dato < D == 1){ p->FE += 1;}
                if(p->FE == 0) return false;
                if(p->FE > 1)
                {
                    //Print();
                    Nodo<T>* p_tmp = p->m_pSon[1];
                    if(p_tmp->FE >= 1) { /**cout<<"\n EN RDD con "<<p->m_Dato<<"\n";**/ RS(p,1);/**RDD(p);/** Print();**/ return false; }
                    else if(p_tmp->FE <= 1) { /**cout<<"\n EN RDI con "<<p->m_Dato<<"\n";**/ RD(p,1);/**RDI(p);/**Print(); **/ return false;}  
                }
                else if( p->FE < -1)
                {
                    //Print();
                    Nodo<T>* p_tmp = p->m_pSon[0];
                    if(p_tmp->FE >= 1) {/**cout<<"\n EN RID con "<<p->m_Dato<<"\n";**/ RD(p,0); /**RID(p); /**Print();**/ return false;}
                    else if(p_tmp->FE <= 1){/**cout<<"\n EN RII con "<<p->m_Dato<<"\n";**/ RS(p,0);/**RII(p);/**Print();**/ return false; }  
                }
                return true;
            }
            return false;
            
       }
       void Print()
       {
           Print(m_pRoot);
       }
       void Print(Nodo<T> *r)
       {
           if (!r) return;
           cout << " FE> " << r->FE << " dir> " << r << " _ data> " << r->m_Dato << " _ dirdirLEFT> " << &r->m_pSon[0] << " _ dirdirRIGHT> " << &r->m_pSon[1] << " _ dirdirPADRE> " << &r->m_pSon[2] << " _ dirLEFT> " << r->m_pSon[0] << " _dirRIGHT> " << r->m_pSon[1] << " _dirPADRE> " << r->m_pSon[2] << "\n";
           Print(r->m_pSon[0]);
           Print(r->m_pSon[1]);
       }

       void Print(Nodo<T> *r, ostream &os)
       {
           if (!r) return;
           os << r->m_Dato << "[label = \"" << r->m_Dato << " | " << r->FE << "\" ]; \n";
           if (r->m_pSon[0]) os << r->m_Dato << "--" << r->m_pSon[0]->m_Dato << ";" << endl;
           if (r->m_pSon[1]) os << r->m_Dato << "--" << r->m_pSon[1]->m_Dato << ";" << endl;
           Print(r->m_pSon[0], os);
           Print(r->m_pSon[1], os);
       }
       void Print(ostream &os) { Print(m_pRoot, os); }

       void dibujar()
       {
           ofstream archivo;
           archivo.open("E:\\Projects\\First_Year\\Laboratorio_ED_II\\Graphviz\\bin\\AVL_HEIGHT.dot");
           archivo << "graph B {\n";
           dibujar(m_pRoot, archivo);
           archivo << "\n}";
           archivo.close();
           //system("E: & cd Graphviz & cd bin & dot AVL_HEIGHT.dot -o AVL_HEIGHT.png -Tpng & AVL_HEIGHT.png");
       }
       void dibujar(Nodo<T> *r, ofstream &archivo)
       {
           if (!r) return;
           archivo << r->m_Dato << "[label = \"" << r->m_Dato << " | " << r->FE << "\" ]; \n";
           if (r->m_pSon[0]) archivo << r->m_Dato << " -- " << r->m_pSon[0]->m_Dato << ";\n";
           if (r->m_pSon[1]) archivo << r->m_Dato << " -- " << r->m_pSon[1]->m_Dato << ";\n";
           dibujar(r->m_pSon[0], archivo);
           dibujar(r->m_pSon[1], archivo);
       }
       bool Find(T D)
       {
           if (!m_pRoot) return false;
           Nodo<T> *p_tmp = m_pRoot;
           while (p_tmp)
           {
               if (p_tmp->m_Dato == D) return true;
               p_tmp = p_tmp->m_pSon[p_tmp->m_Dato < D];
           }
           return NULL;
       }
};


// RDD
int test1()
{
    AVL_Tree<int> A; 
    A.Add(4);   A.Print();
    A.Add(14);  A.Print();
    A.Add(24);  A.Print();
    cout<<"The test1 work perfectly. Nice work :)"<<endl;
   
    return 1;
}
// RII
int test2()
{
    AVL_Tree<int> A; 
    A.Add(24);   A.Print();
    A.Add(14);   A.Print();
    A.Add(2);    A.Print();
    cout<<"The test2 work perfectly. Good Work :)"<<endl;
    return 1;
}
// RDI
int test3()
{
    AVL_Tree<int> A; 
    A.Add(4);   A.Print();
    A.Add(14);  A.Print();
    A.Add(10);  A.Print();
    cout<<"The test3 work perfectly. Good Work :)"<<endl;
    return 1;
}
// RID
int test4()
{
    AVL_Tree<int> A; 
    A.Add(24);  A.Print();
    A.Add(14);  A.Print();
    A.Add(18);  A.Print();
    cout<<"The test4 work perfectly. Good Work :)"<<endl;
    return 1;
}

// FINAL
int test6()
{
    //ofstream s("salida.dot");
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

    cout<<"Dibujando";
    A.Print(cout);
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

    test6();
    
    
    return 1;
}
