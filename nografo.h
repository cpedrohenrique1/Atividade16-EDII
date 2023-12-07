#ifndef NOGrafo_H
#define NOGrafo_H

#include <QString>

template <class TYPE>
class NOGrafo
{
private:
    int vertice;
    TYPE peso;

public:
    NOGrafo() : vertice(0),
                peso(TYPE())
    {
    }
    NOGrafo(const int &vertice, const TYPE &peso = TYPE()) : vertice(0),
                                                             peso(peso)
    {
        if (vertice <= 0)
        {
            throw QString("Vertice invalido");
        }
        this->peso = peso;
        this->vertice = vertice;
    }
    TYPE getPeso() const
    {
        return peso;
    }
    void setPeso(const TYPE &peso)
    {
        this->peso = peso;
    }
    int getVertice() const
    {
        return vertice;
    }
    void setVertice(const int &vertice)
    {
        if (vertice <= 0)
        {
            throw QString("Vertice negativo");
        }
        this->vertice = vertice;
    }
};

#endif // NOGrafo_H
