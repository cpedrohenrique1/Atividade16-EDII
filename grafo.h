#ifndef GRAFO_H
#define GRAFO_H

#include <QString>
#include "lista.h"
#include "nografo.h"

template <class TYPE>
class Grafo
{
protected:
    Lista<NOGrafo<TYPE>> **lista;
    int n_vertices;
    virtual void inserir(const int& vertice1, const int& vertice2, const TYPE& peso) = 0;
    virtual void alterar(const int& vertice1, const int& vertice2, const TYPE& peso) = 0;
    virtual void remover(const int& vertice1, const int& vertice2) = 0;
    
public:
    Grafo() : lista(0),
              n_vertices(0)
    {}
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
    
    void inserirAresta(const int& vertice1, const int& vertice2, const TYPE& peso)
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
        int vertice1_temp = vertice1 - 1;
        for (int i = 0; i < lista[vertice1_temp]->getQuantidadeElementos(); ++i)
        {
            if (lista[vertice1_temp]->acessarPosicao(i).getVertice() == vertice2)
            {
                throw QString("Aresta ja existe");
            }
        }
        inserir(vertice1, vertice2, peso);
    }

    void alterarAresta(const int &vertice1, const int &vertice2, const TYPE &peso)
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
        alterar(vertice1, vertice2, peso);
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
        remover(vertice1, vertice2);
    }
    NOGrafo<TYPE> getNOGrafo(const int &indice, const int &posicao) const
    {
        if (indice < 0 || indice >= n_vertices)
        {
            throw QString("indice invalido");
        }
        return lista[indice]->acessarPosicao(posicao);
    }
    int getTamanhoLista(const int &indice) const
    {
        if (indice < 0 || indice >= n_vertices)
        {
            throw QString("indice invalido");
        }
        return lista[indice]->getQuantidadeElementos();
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
