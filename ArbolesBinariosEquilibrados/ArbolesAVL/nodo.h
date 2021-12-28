#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo
{
    public:
        Nodo<T>* pSon[3];
        int FE;
        T value;
    public:
        Nodo( T );
        void autoDestruir( Nodo<T>*& );
};

template<typename T>
Nodo<T>::Nodo( T value )
{
    pSon[0]=0;        // hij izq
    pSon[1]=0;        // hij der
    pSon[2]=0;        // padre
    FE = 0;
    this->value = value;
}

template<typename T>
void Nodo<T>::autoDestruir( Nodo<T>*& p )
{
    if( !p ) return;
    autoDestruir( p->pSon[0] );
    autoDestruir( p->pSon[1] );
    delete p;
}

#endif