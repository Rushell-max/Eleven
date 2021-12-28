#include<iostream>
#include<stack>
#include<fstream>
using namespace std;


template<class T>
class Nodo
{
    public:
       T m_Dato;
       Nodo<T> * m_pSon[2];
       int m_Height;
     // Add the Constructor; 
       Nodo(T d)
       {
           m_Dato = d;
           // Hijo Izquierdo
           m_pSon[0] = 0;
           // Hijo Derecho
           m_pSon[1] = 0;
           // Height
           m_Height = 1;
       } 
};


template<class T>
class ArbolBinario
{
    private:
       Nodo<T> * m_pRoot;

    public:
        ArbolBinario()
        {
            m_pRoot = 0;
        }
        
        void insert(T d)
        {
            return insert(m_pRoot, d);
        }
        void insert(Nodo<T> *&p, T d)
        {
            if(!p) {p = new Nodo<T>(d); return;}
            if(d == p->m_Dato) return;
            insert(p->m_pSon[p->m_Dato < d], d);
            p->m_Height = 1 + max(height(p->m_pSon[0]), height(p->m_pSon[1]));
        }
        int max(int a, int b)
        {
            if(a>b) return a;
            return b;
        }
        int height(Nodo<T> *p)
        {
            if(!p) return 0;
            return p->m_Height;
        }
        int height()
        {
            return m_pRoot->m_Height;
        }
        bool remove(T d)
        {
            if(!m_pRoot) return false;
            Nodo<T> **p_tmp = &m_pRoot;
            while(*p_tmp)
            {
                if((*p_tmp)->m_Dato == d) 
                {
                    if((*p_tmp)->m_pSon[0] && !(*p_tmp)->m_pSon[1])
                    {
                        Nodo<T> *p_tmp1 = *p_tmp;
                        (*p_tmp) = (*p_tmp)->m_pSon[0];
                        delete p_tmp1; p_tmp1 = 0; 
                        return true; 
                    }
                    else if(!(*p_tmp)->m_pSon[0] && (*p_tmp)->m_pSon[1])
                    {
                        Nodo<T> *p_tmp1 = *p_tmp;
                        (*p_tmp) = (*p_tmp)->m_pSon[1];
                        delete p_tmp1; p_tmp1 = 0; 
                        return true; 
                    }
                    else if((*p_tmp)->m_pSon[0] && (*p_tmp)->m_pSon[1])
                    {
                        Nodo<T> *p_tmp1 = *p_tmp;
                        Nodo<T> *p_tmp2 = (*p_tmp)->m_pSon[1], *p_tmp3 = (*p_tmp)->m_pSon[1], *p;
                        while(p_tmp2->m_pSon[0])
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
                        delete p_tmp1; p_tmp1 = 0; 
                        return true;                         
                    }
                    else{
                        delete *p_tmp; *p_tmp=0; return true;
                    }
                }
                p_tmp = &((*p_tmp)->m_pSon[(*p_tmp)->m_Dato < d]);
            }
            return false;           
        }
        void inOrder()
        {
            cout<<"\n IMMPRIMIENDO EN INORDER >> \n";
            inOrder(m_pRoot);
        }
        void inOrder(Nodo<T> *p)
        {
            if(!p) return;
            inOrder(p->m_pSon[0]);
            cout<<p->m_Dato<<" ";
            inOrder(p->m_pSon[1]);
        }
        void inOrderIT()
        {
            cout<<"\n IMMPRIMIENDO EN INORDER ITERATIVO >> \n";
            if(!m_pRoot) return;
            stack<Nodo<T>*> stack;
            Nodo<T> *p_tmp = m_pRoot;

            while(!stack.empty() || p_tmp)
            {
                while(p_tmp)
                {
                    stack.push(p_tmp);
                    p_tmp = p_tmp->m_pSon[0];
                }
                p_tmp = stack.top();
                cout<<p_tmp->m_Dato<<" ";
                stack.pop();

                p_tmp = p_tmp->m_pSon[1];
            }
        }
        void preOrder()
        {
            cout<<"\n IMMPRIMIENDO EN PREORDER >> \n";
            preOrder(m_pRoot);
        }
        void preOrder(Nodo<T> *p)
        {
            if(!p) return;
            cout<<p->m_Dato<<" ";
            preOrder(p->m_pSon[0]);
            preOrder(p->m_pSon[1]);
        }
        void preOrdenIT()
        {
            cout<<"\n IMMPRIMIENDO EN PREORDER ITERARIVO >> \n";
            if(!m_pRoot) return;
            stack<Nodo<T>*> stack;
            Nodo<T> *p_tmp = m_pRoot;

            while(!stack.empty() || p_tmp)
            {
                while(p_tmp)
                {
                    cout<<p_tmp->m_Dato<<" ";

                    if(p_tmp->m_pSon[1]) stack.push(p_tmp->m_pSon[1]);

                    p_tmp = p_tmp->m_pSon[0];
                }
                
                if(!stack.empty())
                {
                    p_tmp = stack.top();
                    stack.pop();
                }
            }
        }
        void postOrder()
        {
            cout<<"\n IMMPRIMIENDO EN POSTORDER >> \n";
            postOrder(m_pRoot);
        }
        void postOrder(Nodo<T> *p)
        {
            if(!p) return;
            postOrder(p->m_pSon[0]);
            postOrder(p->m_pSon[1]);
            cout<<p->m_Dato<<" ";
        }
        void postOrdenIT()
        {
            cout<<"\n IMMPRIMIENDO EN POSTORDER ITERATIVO >> \n";
            if(!m_pRoot) return;
            stack<Nodo<T>*> stack, stack1;
            stack.push(m_pRoot);

            Nodo<T> *p_tmp = m_pRoot;
            while(!stack.empty())
            {
                p_tmp = stack.top();
                stack.pop();
                stack1.push(p_tmp);
                if(p_tmp->m_pSon[0]) stack.push(p_tmp->m_pSon[0]);
                if(p_tmp->m_pSon[1]) stack.push(p_tmp->m_pSon[1]);
            }

            while(!stack1.empty())
            {
                p_tmp = stack1.top();
                stack1.pop();
                cout<<p_tmp->m_Dato<<" ";
            }
        }
        bool isBST() // ESTA FUNCION NO ESTA DEL TODO BIEN TIENE BUGS
        {
            Nodo<T>* anterior = 0;
            return isBST(m_pRoot, anterior);
        }
        bool isBST(Nodo<T> *p, Nodo<T>*&anterior) // X2
        {
            if(!p) return true;
            if(!isBST(p->m_pSon[0], anterior)) return false;
            if(anterior && p->m_Dato <= anterior->m_Dato) return false;
            anterior = p;
            return isBST(p->m_pSon[1], anterior);
        }
        void dibujar()
        {
            ofstream archivo;
            archivo.open("E:\\Projects\\First_Year\\Laboratorio_ED_II\\Graphviz\\bin\\ArbolBinario.dot");
            archivo << "graph B {\n";
            dibujar(m_pRoot, archivo);
            archivo << "\n}";
            archivo.close();
            //system("cd E: & cd Projects & cd First_Year & cd Laboratorio_ED_II & cd Graphviz & cd bin & dot ArbolBinario.dot -o ArbolBinario.png -Tpng & ArbolBinario.png");
        }
        void dibujar(Nodo<T> *r, ofstream &archivo)
        {
            if (!r) return;
            archivo << r->m_Dato << ";\n ";
            if (r->m_pSon[0]) archivo << r->m_Dato << " -- " << r->m_pSon[0]->m_Dato << ";\n";
            if (r->m_pSon[1]) archivo << r->m_Dato << " -- " << r->m_pSon[1]->m_Dato << ";\n";
            dibujar(r->m_pSon[0], archivo);
            dibujar(r->m_pSon[1], archivo);
        }
};

int main()
{
    ArbolBinario<int> A;
    srand(10); 
    for(int i=0;i<100;i++)
    {
        // Insert the correct includes 
        int a=rand()%100;
        cout<<"\n INSERTANDO "<<a<<endl;
        A.insert(a);
    }


    A.inOrder();
    A.inOrderIT();

    A.preOrder();
    A.preOrdenIT();

    A.postOrder();
    A.postOrdenIT();

    A.dibujar();

    cout<<"\n IS BST? > "<<A.isBST();
    cout<<"\n ALTURA ARBOL >> "<<A.height();

    int valor;
    cout<<"\n Ingrese valor a remover >> "; cin>>valor;
    A.remove(valor);
    A.inOrder();
    A.dibujar();
}