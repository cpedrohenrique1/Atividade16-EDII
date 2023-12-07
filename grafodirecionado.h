#ifndef GRAFODIRECIONADO_H
#define GRAFODIRECIONADO_H

#include "grafo.h"

template <class TYPE>
class GrafoDirecionado : public Grafo<TYPE>
{
protected:
    void inserir(const int &vertice1, const int &vertice2, const TYPE &peso) override
    {
        this->lista[vertice1 - 1]->inserirInicio(NOGrafo<TYPE>(vertice2, peso));
    }
    void set(const int &vertice1, const int &vertice2, const TYPE &peso) override
    {
        for (int i = 0; i < this->lista[vertice1 - 1]->getQuantidadeElementos(); ++i)
        {
            if (this->lista[vertice1 - 1]->acessarPosicao(i).getVertice() == vertice2)
            {
                this->lista[vertice1 - 1]->retirarPosicao(i);
                this->lista[vertice1 - 1]->inserirPosicao(i, NOGrafo<TYPE>(vertice2, peso));
                return;
            }
        }
    }
    void remover(const int &vertice1, const int &vertice2) override
    {
        for (int i = 0; i < this->lista[vertice1 - 1]->getQuantidadeElementos(); ++i)
        {
            if (this->lista[vertice1 - 1]->acessarPosicao(i).getVertice() == vertice2)
            {
                this->lista[vertice1 - 1]->retirarPosicao(i);
                return;
            }
        }
    }

public:
    GrafoDirecionado() : Grafo<TYPE>() {}
    GrafoDirecionado(const int &n_vertices) : Grafo<TYPE>(n_vertices) {}
};

#endif // GRAFODIRECIONADO_H
