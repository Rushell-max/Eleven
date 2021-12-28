#ifndef CELL_H
#define CELL_H

template <class T>
class Cell
{
public:
   int m_Fil;
   int m_Col;
   Cell<T> *m_SigFil;
   Cell<T> *m_SigCol;
   T m_Dato;

public:
   Cell(T d, int f, int c);
   Cell();
};

template<typename T>
Cell<T>::Cell(T d, int f, int c)
{
    m_Fil = f;
    m_Col = c;
    m_SigFil = 0;
    m_SigCol = 0;
    m_Dato = d;
}

template<typename T>
Cell<T>::Cell()
{
    m_Fil = 0;
    m_Col = 0;
    m_SigFil = 0;
    m_SigCol = 0;
}

#endif