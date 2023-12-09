#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"
#include "etiqueta.h"
template <class TYPE>
class Caminho
{
private:
    Grafo<TYPE> *grafo;
    Lista<Etiqueta<TYPE>> **etiqueta;
    int n_vertices;

public:
    Caminho(const Grafo<TYPE> *grafo) : grafo(grafo),
                                        etiqueta(0),
                                        n_vertices(0)
    {
        if (!grafo)
        {
            throw QString("Grafo nao inicializado");
        }
        try
        {
            n_vertices = grafo->getNVertices();
            etiqueta = new Lista<Etiqueta<TYPE>> *[n_vertices];
            for (int i = 0; i < n_vertices; ++i)
            {
                etiqueta[i] = new Lista<Etiqueta<TYPE>>;
            }
        }
        catch (std::bad_alloc &e)
        {
            throw QString("Erro ao alocar memoria");
        }
    }
    
    Etiqueta<TYPE> getEtiqueta(const int& indice, const int& posicao)const{
        if (indice < 0 || indice >= n_vertices){
            throw QString("Indice invalido");
        }
        return etiqueta[indice]->acessarPosicao(posicao);
    }

    Etiqueta<TYPE> getEtiquetaValida(const int &vertice)
    {
        if (!grafo)
        {
            throw QString("Grafo nao inicializado");
        }
        if (!etiqueta)
        {
            throw QString("Lista de etiqueta nao inicializada");
        }
        if (vertice <= 0 || vertice > n_vertices)
        {
            throw QString("Vertice invalido");
        }
        for (int i = 0; i < etiqueta[vertice - 1]->getTamanhoLista(); ++i)
        {
            Etiqueta<TYPE> temp = etiqueta[vertice - 1]->acessarPosicao(i);
            if (temp.getSituacaoVertice())
            {
                return temp;
            }
        }
        return Etiqueta<TYPE>();
    }

    Etiqueta<TYPE> getEtiquetaMenorCusto(const int& vertice){
        if (!grafo)
        {
            throw QString("Grafo nao inicializado");
        }
        if (!etiqueta)
        {
            throw QString("Lista de etiqueta nao inicializada");
        }
        if (vertice <= 0 || vertice > n_vertices)
        {
            throw QString("Vertice invalido");
        }
        Etiqueta<TYPE> resultado = etiqueta[vertice - 1]->acessarPosicao(0);
        for (int i = 1; i < etiqueta[vertice - 1]->getTamanhoLista(); ++i){
            Etiqueta<TYPE> etiqueta_temp = etiqueta[vertice - 1]->acessarPosicao(i);
            if (resultado.getCustoAcumulado() > etiqueta_temp.getCustoAcumulado()){
                resultado = etiqueta_temp;
            }
        }
        return resultado;
    }

    Etiqueta<TYPE> getEtiquetaMenorCusto(const int& vertice, int& posicao){
        if (!grafo)
        {
            throw QString("Grafo nao inicializado");
        }
        if (!etiqueta)
        {
            throw QString("Lista de etiqueta nao inicializada");
        }
        if (vertice <= 0 || vertice > n_vertices)
        {
            throw QString("Vertice invalido");
        }
        Etiqueta<TYPE> resultado = etiqueta[vertice - 1]->acessarPosicao(0);
        for (int i = 1; i < etiqueta[vertice - 1]->getTamanhoLista(); ++i){
            Etiqueta<TYPE> etiqueta_temp = etiqueta[vertice - 1]->acessarPosicao(i);
            if (resultado.getCustoAcumulado() > etiqueta_temp.getCustoAcumulado()){
                resultado = etiqueta_temp;
                posicao = i;
            }
        }
        return resultado;
    }

    void encontrarCaminho(int vertice)
    {
        if (!grafo)
        {
            throw QString("Grafo nao inicializado");
        }
        if (!etiqueta)
        {
            throw QString("Lista de etiqueta nao inicializada");
        }
        if (vertice <= 0 || vertice > n_vertices)
        {
            throw QString("Vertice invalido");
        }
        etiqueta[vertice - 1]->inserirInicio(Etiqueta<TYPE>(TYPE(), 0, 0, true));
        for (int i = 1; i < n_vertices; ++i)
        {
            int tamanho_lista = grafo->getTamanhoLista(vertice - 1);
            if (tamanho_lista == 1)
            {
                NOGrafo<TYPE> grafo_temp = grafo->getNOGrafo(vertice - 1, 0);
                Etiqueta<TYPE> item(grafo_temp.getPeso() + getEtiquetaValida(vertice).getCustoAcumulado(),
                                    vertice,
                                    getEtiquetaValida().getQuantidadeArestasVisitadas() + 1,
                                    true);
                vertice = grafo_temp.getVertice();
                etiqueta[vertice - 1]->inserirInicio(item);
            }else{
                for (int j = 0; j < tamanho_lista; ++j){
                    NOGrafo<TYPE> grafo_temp = grafo->getNOGrafo(vertice - 1, j);
                    Etiqueta<TYPE> item(grafo_temp.getPeso() + getEtiquetaValida(vertice).getCustoAcumulado(),
                                        vertice,
                                        getEtiquetaValida(vertice).getQuantidadeArestasVisitadas() + 1,
                                        false);
                    etiqueta[grafo_temp.getVertice() - 1]->inserirInicio(item);
                }
                int vertice_menor;
                for (int j = 0; j < tamanho_lista - 1; ++j){
                    NOGrafo<TYPE> grafo_temp = grafo->getNOGrafo(vertice - 1, j);
                    Etiqueta<TYPE> etiqueta_menor = getEtiquetaMenorCusto(grafo_temp.getVertice());
                    if (etiqueta_menor.getCustoAcumulado() > getEtiquetaMenorCusto(grafo->getNOGrafo(vertice - 1, j + 1))){
                        vertice_menor = grafo->getNOGrafo(vertice - 1, j).getVertice();
                    }
                }
                int posicao_vertice = 0;
                Etiqueta<TYPE> temp = getEtiquetaMenorCusto(vertice_menor - 1, posicao_vertice);
                temp.setSituacaoVertice(true);
                etiqueta[vertice_menor - 1]->retirarPosicao(posicao_vertice);
                etiqueta[vertice_menor - 1]->inserirPosicao(posicao_vertice);
                vertice = vertice_menor;
            }
        }
    }

    int getNVertices()const{
        return n_vertices;
    }

    ~Caminho()
    {
        if (etiqueta)
        {
            for (int i = 0; i < n_vertices; ++i)
            {
                if (etiqueta[i])
                {
                    delete etiqueta[i];
                    etiqueta[i] = 0;
                }
            }
            delete[] etiqueta;
            etiqueta = 0;
        }
    }
};

#endif // CAMINHO_H
