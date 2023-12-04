#ifndef GRAFO_H
#define GRAFO_H

#include <QString>
#include "lista.h"
#include "nografo.h"

template <class TYPE>
class Grafo
{
private:
    Lista<NOGrafo<TYPE>> **lista;
    int n_vertices;

public:
    Grafo() : lista(0),
              n_vertices(0)

    {
    }
    Grafo(const int &n_vertices) : lista(0),
                                   n_vertices(0)
    {
        if (n_vertices <= 0)
        {
            throw QString("vertice nao pode ser <= 0");
        }
        this->n_vertices = n_vertices;
        try
        {
            lista = new Lista<NOGrafo<TYPE>> *[n_vertices];
            for (int i = 0; i < n_vertices; ++i)
            {
                lista[i] = new Lista<NOGrafo<TYPE>>;
            }
        }
        catch (std::bad_alloc &e)
        {
            throw QString("Nao foi possivel alocar memoria");
        }
    }
    void inserirAresta(const int &vertice1, const int &vertice2, const TYPE &peso)
    {
        if ((vertice1 <= 0 || vertice1 > n_vertices) || (vertice2 <= 0 || vertice2 > n_vertices))
        {
            throw QString("Vertice nao existe");
        }
        if (vertice1 == vertice2)
        {
            throw QString("Vertice nao pode ser igual");
        }
        if (!lista)
        {
            throw QString("Lista nao criada");
        }
        for (int i = 0; i < lista[vertice1 - 1]->getQuantidadeElementos(); ++i)
        {
            if (lista[vertice1 - 1]->acessarPosicao(i).getVertice() == vertice2)
            {
                throw QString("Aresta ja existe");
            }
        }
        lista[vertice1 - 1]->inserirInicio(NOGrafo<TYPE>(vertice2, peso));
        lista[vertice2 - 1]->inserirInicio(NOGrafo<TYPE>(vertice1, peso));
    }
    void setAresta(const int &vertice1, const int &vertice2, const TYPE &peso)
    {
        if ((vertice1 <= 0 || vertice1 > n_vertices) || (vertice2 <= 0 || vertice2 > n_vertices))
        {
            throw QString("Vertice nao existe");
        }
        if (vertice1 == vertice2)
        {
            throw QString("Vertice nao pode ser igual");
        }
        if (!lista)
        {
            throw QString("Lista nao criada");
        }
        for (int i = 0; i < lista[vertice1 - 1]->getQuantidadeElementos(); ++i)
        {
            if (lista[vertice1 - 1]->acessarPosicao(i).getVertice() == vertice2)
            {
                lista[vertice1 - 1]->retirarPosicao(i);
                lista[vertice1 - 1]->inserirPosicao(i, NOGrafo<TYPE>(vertice2, peso));
                break;
            }
        }
        for (int i = 0; i < lista[vertice2 - 1]->getQuantidadeElementos(); ++i)
        {
            if (lista[vertice2 - 1]->acessarPosicao(i).getVertice() == vertice1)
            {
                lista[vertice2 - 1]->retirarPosicao(i);
                lista[vertice2 - 1]->inserirPosicao(i, NOGrafo<TYPE>(vertice1, peso));
                break;
            }
        }
    }
    int getNVertices() const
    {
        return n_vertices;
    }
    void removerAresta(const int &vertice1, const int &vertice2)
    {
        if ((vertice1 <= 0 || vertice1 > n_vertices) || (vertice2 <= 0 || vertice2 > n_vertices))
        {
            throw QString("Vertice nao existe");
        }
        if (vertice1 == vertice2)
        {
            throw QString("Vertice nao pode ser igual");
        }
        if (!lista)
        {
            throw QString("Lista nao criada");
        }
        for (int i = 0; i < lista[vertice1 - 1]->getQuantidadeElementos(); ++i)
        {
            if (lista[vertice1 - 1]->acessarPosicao(i).getVertice() == vertice2)
            {
                lista[vertice1 - 1]->retirarPosicao(i);
                break;
            }
        }
        for (int i = 0; i < lista[vertice2 - 1]->getQuantidadeElementos(); ++i)
        {
            if (lista[vertice2 - 1]->acessarPosicao(i).getVertice() == vertice1)
            {
                lista[vertice2 - 1]->retirarPosicao(i);
                break;
            }
        }
    }
    NOGrafo<TYPE> getNOGrafo(const int &indice, const int &j) const
    {
        if (indice < 0 || indice >= n_vertices)
        {
            throw QString("indice invalido");
        }
        return lista[indice]->acessarPosicao(j);
    }
    int getTamanhoLista(const int &vertice) const
    {
        if (vertice < 0 || vertice >= n_vertices)
        {
            throw QString("indice invalido");
        }
        return lista[vertice]->getQuantidadeElementos();
    }
    ~Grafo()
    {
        if (lista)
        {
            for (int i = 0; i < n_vertices; ++i)
            {
                if (lista[i])
                {
                    delete lista[i];
                    lista[i] = 0;
                }
            }
            delete[] lista;
            lista = 0;
        }
    }
};

#endif // GRAFO_H
