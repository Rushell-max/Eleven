#include "node.h"

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int _size;

public:
    LinkedList() : head(nullptr), _size(0) {}
    LinkedList(T);
    LinkedList(T, int);
    LinkedList(LinkedList<T> &);
    LinkedList(LinkedList<T> &&);
    ~LinkedList();
    int size() { return _size; }
    void insert(T);
    void push_back(T);
    bool find(T);
    void remove(T);
    void print();
    LinkedList<T>& operator=(const LinkedList<T> &);
    LinkedList<T>& operator=( LinkedList<T> &&);
    bool operator==( const LinkedList<T>& );
    bool operator!=( const LinkedList<T>& );
};

template <typename T>
LinkedList<T>::LinkedList(T value)
{
    head = new Node<T>(value);
    _size = 1;
}

template <typename T>
LinkedList<T>::LinkedList(T value, int size)
{
    head = nullptr;
    _size = 0;
    while (size--) insert(value);
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &L)
{
    head = nullptr;
    _size = 0;
    Node<T> *tmp = L.head;
    while (tmp)
    {
        push_back(tmp->getValue());
        tmp = tmp->getNext();
    }
    std::cout << "constructor copia\n";
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&L)
{
    head = nullptr;
    _size = 0;
    std::swap(head, L.head);
    std::swap(_size, L._size);
    std::cout << "constructor mov\n";
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T> *tmp = head;
    while (tmp)
    {
        tmp = head->getNext();
        delete head;
        head = tmp;
    }
}

template <typename T>
void LinkedList<T>::insert(T value)
{
    if (!head)
        head = new Node<T>(value); //si esta vacio, crea uno nuevo
    else
    {
        Node<T> *nodo = new Node<T>(value); //nuevo nodo
        Node<T> *tmp = head;                //guarda head actual
        head = nodo;                        //nuevo head
        head->setNext(tmp);                 //head-next apunta a tmp
    }
    _size++;
}

template <typename T>
void LinkedList<T>::push_back(T value){
    Node<T>* tmp = head;
    Node<T>* nodo = new Node<T>(value);
    if(!tmp) head = nodo;
    else
    {
        while(tmp->getNext())
        {
            tmp = tmp->getNext();
        }
        tmp->setNext(nodo);
    }
    _size++;
}

template <typename T>
bool LinkedList<T>::find(T value)
{
    Node<T> *tmp = head;
    while (tmp)                         //mientras no se llegue al final
    {
        if (tmp->getValue() == value)
            return true;                //si valor coincide, devuelve true
        tmp = tmp->getNext();           //avanza
    }
    return false;
}

template <typename T>
void LinkedList<T>::remove(T value)
{
    if (!head)
        return; //si esta vacio, termina
    else
    {
        Node<T> *tmp = head; //tmp apunta al actual
        Node<T> *aux = head; //aux guarda el anterior
        while (tmp)          //mientras no se llegue al final
        {
            if (tmp->getValue() == value) //si el valor coincide
            {
                if (tmp == head) //si tmp es head
                {
                    head = head->getNext(); //head ahora es el sig
                    delete tmp;             //borra tmp
                    _size--;
                    tmp = head; //tmp apunta al nuevo head
                }
                else //si no es head
                {
                    aux->setNext(tmp->getNext()); //aux-next apunta a tmp-next
                    delete tmp;                   //borra tmp
                    _size--;
                    tmp = aux->getNext(); //tmp apunta a aux-sig
                }
            }
            else //si no coincide el valor
            {
                aux = tmp;            //aux apunta a tmp
                tmp = tmp->getNext(); //tmp avanza
            }
        }
    }
}

template <typename T>
void LinkedList<T>::print()
{
    Node<T> *tmp = head;
    while (tmp)
    {
        std::cout << tmp->getValue() << ' ';
        tmp = tmp->getNext();
    }
    std::cout << '\n';
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &L)
{
    if (this != &L)
    {
        Node<T> *aux = head;
        while(aux)
        {
            aux = head->getNext();
            delete head;
            head = aux;
        }
        head = nullptr;
        _size = 0;
        Node<T> *tmp = L.head;
        while (tmp)
        {
            push_back(tmp->getValue());
            tmp = tmp->getNext();
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> &&L)
{
    if (this != &L)
    {
        std::swap(head, L.head);
        std::swap(_size, L._size);
    }
    return *this;
}

template <typename T>
bool LinkedList<T>::operator==( const LinkedList<T>& L )
{
    if ( _size != L._size ) return false;
    else
    {   
        Node<T>* tmp1 = head;
        Node<T>* tmp2 = L.head;
        while( tmp1 )
        {
            if ( tmp1->getValue() != tmp2->getValue() ) return false;
            tmp1 = tmp1->getNext();
            tmp2 = tmp2->getNext();
        }
    }
    return true;
}

template <typename T>
bool LinkedList<T>::operator!=( const LinkedList<T>& L )
{
    return !( this==&L );
}
