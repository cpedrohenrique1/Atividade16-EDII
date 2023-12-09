#ifndef GRAFONAOORIENTADO_H
#define GRAFONAOORIENTADO_H

#include "grafo.h"
template<class TYPE>
class GrafoNaoOrientado : public Grafo<TYPE>
{
protected:
    void inserir(const int &vertice1, const int &vertice2, const TYPE &peso) override
    {
        this->lista[vertice1 - 1]->inserirInicio(NOGrafo<TYPE>(vertice2, peso));
        this->lista[vertice2 - 1]->inserirInicio(NOGrafo<TYPE>(vertice1, peso));
    }
    void alterar(const int &vertice1, const int &vertice2, const TYPE &peso) override
    {
        int vertice1_temp = vertice1 - 1;
        int vertice2_temp = vertice2 - 1;
        for (int i = 0; i < this->lista[vertice1_temp]->getQuantidadeElementos(); ++i)
        {
            if (this->lista[vertice1_temp]->acessarPosicao(i).getVertice() == vertice2)
            {
                this->lista[vertice1_temp]->retirarPosicao(i);
                this->lista[vertice1_temp]->inserirPosicao(i, NOGrafo<TYPE>(vertice2, peso));
                break;
            }
        }
        for (int i = 0; i < this->lista[vertice2_temp]->getQuantidadeElementos(); ++i)
        {
            if (this->lista[vertice2_temp]->acessarPosicao(i).getVertice() == vertice1)
            {
                this->lista[vertice2_temp]->retirarPosicao(i);
                this->lista[vertice2_temp]->inserirPosicao(i, NOGrafo<TYPE>(vertice1, peso));
                return;
            }
        }
    }
    void remover(const int &vertice1, const int &vertice2) override
    {
        int vertice1_temp = vertice1 - 1;
        int vertice2_temp = vertice2 - 1;
        for (int i = 0; i < this->lista[vertice1_temp]->getQuantidadeElementos(); ++i)
        {
            if (this->lista[vertice1_temp]->acessarPosicao(i).getVertice() == vertice2)
            {
                this->lista[vertice1_temp]->retirarPosicao(i);
                break;
            }
        }
        for (int i = 0; i < this->lista[vertice2_temp]->getQuantidadeElementos(); ++i)
        {
            if (this->lista[vertice2_temp]->acessarPosicao(i).getVertice() == vertice1)
            {
                this->lista[vertice2_temp]->retirarPosicao(i);
                return;
            }
        }
    }
public:
    GrafoNaoOrientado(): Grafo<TYPE>() {}
    GrafoNaoOrientado(const int& n_vertices): Grafo<TYPE>(n_vertices) {}
};

#endif // GRAFONAOORIENTADO_H
