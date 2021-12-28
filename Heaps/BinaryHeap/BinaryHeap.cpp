#include <iostream>
#include <fstream>

using namespace std;

void swap (int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

template<class T>
class MinHeap
{
    private:
      T *   m_Heap;
      int   m_size;
      int   m_capacity;
    
    private:
        int Get_Father(int i){ return (i-1)/2; }  // O(1) 
        int LS(int i) { return 2*i+1; } // O(1)
        int RS(int i) { return 2*i+2; } // O(1)

    public:
        MinHeap(int n)
        { 
            m_Heap = new T[n];
            m_size = 0;
            m_capacity = n;
        }
        ~MinHeap(){ delete m_Heap; }

        T Get_Min() { return m_Heap[0]; }

        void Insert(T d){
            if(m_size<m_capacity) { m_Heap[m_size]=d; m_size++; Decrease_Key(m_size,d);}
            else cout << "Se ha superado el limite maximo" << endl;
        }
        void Delete(int i)
        {
            if (i>m_size) return;
            Decrease_Key(i, Get_Min()-1);
            Extract_Min();
        }
        void Decrease_Key(int i, T value)
        {
            m_Heap[i] = value;
            while(i>=0 && m_Heap[Get_Father(i)] > m_Heap[i])
            {
                swap(m_Heap[i] , m_Heap[Get_Father(i)]);
                i = Get_Father(i);
            }
        }
        void Extract_Min()
        {
            if(m_size == 0) return;
            if(m_size == 1) { m_size--; m_Heap[0] = NULL; return;}
            //swap(m_Heap[0], m_Heap[m_size-1]);
            m_Heap[0] = m_Heap[m_size-1];
            m_size--;
            HeapFy(0);
        }

        void HeapFy(int i){
            int L = LS(i), R = RS(i);
            int menor = i;

            if(L < m_size && m_Heap[L] < m_Heap[i]) menor = L;
            if(R < m_size && m_Heap[R] < m_Heap[menor]) menor = R;
            
            //if(menor > m_size) return; //!!!!!!
            if (menor != i){
                swap(m_Heap[i], m_Heap[menor]);
                HeapFy(menor);
            }
        }

        void print(){
            for (int i = 0; i < m_size; i++)
                cout<<"\t"<<m_Heap[i];
            cout << endl;
        }
        void Show_Dot(int i, ostream & o)
        {
            if(m_size <= i) return;
            if( LS(i) < m_size) o<<"\t"<<i<<" -> "<<LS(i)<<"\t[label= 0]"<<";\n";
            if( RS(i) < m_size) o<<"\t"<<i<<" -> "<<RS(i)<<"\t[label= 1]"<<";\n";
            Show_Dot(LS(i), o);
            Show_Dot(RS(i), o);
        }
        void Show_Dot(ostream & o)
        {
            o<< "digraph B {"<<endl;
            o<< "node [shape=record];"<<endl;
            o<< "\t"<<0<< "[style=filled];" << endl;
            for (int i = 0; i < m_size; i++)
                o << "    " << i <<  " [label= \" " << i << " | " <<  m_Heap[i] <<  " \" ];" << endl;
            Show_Dot(0, o); 
            o<< "}"<<endl;
        }
};

int main(){
    MinHeap<int> A(200);
    for(int i = 1; i< 200; i ++) 
    {
        int a = rand()%1000;
        A.Insert(a);
    } 

    ofstream archivo;
    archivo.open("E:\\Projects\\S4\\EDA\\BinaryHeap.dot");
    A.Show_Dot(archivo);
    archivo.close();
    
    int x;
    cout<<"Eliminando "; cin>>x;
    A.Delete(x);

    archivo.open("E:\\Projects\\S4\\EDA\\BinaryHeap.dot");
    A.Show_Dot(archivo);
    archivo.close();
    return 0;
}