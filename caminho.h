#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"
#include "etiqueta.h"
template <class TYPE>
class Caminho
{
private:
    const Grafo<TYPE> *grafo;
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

    void verificacaoPadrao(const int& vertice_indice) const{
        if (!grafo || n_vertices == 0){
            throw QString("Grafo nao inicializado");
        }
        if (!etiqueta){
            throw QString("Etiqueta nao iniciada");
        }
        if (vertice_indice < 0 || vertice_indice >= n_vertices){
            throw QString("Vertice invalido");
        }
    }

    Etiqueta<TYPE> getEtiqueta(const int& vertice_indice, const int& posicao) const{
        verificacaoPadrao(vertice_indice);
        return etiqueta[vertice_indice]->acessarPosicao(posicao);
    }

    int getTamanhoListaEtiqueta(const int& vertice_indice) const{
        verificacaoPadrao(vertice_indice);
        return etiqueta[vertice_indice]->getQuantidadeElementos();
    }

    Etiqueta<TYPE> getEtiquetaValida(const int& vertice_indice)
    {
        for (int i = 0; i < getTamanhoListaEtiqueta(vertice_indice); ++i)
        {
            Etiqueta<TYPE> temp = getEtiqueta(vertice_indice, i);
            if (temp.getSituacaoVertice())
            {
                return temp;
            }
        }
        return Etiqueta<TYPE>();
    }

    int getPosicaoMenorCusto(const int& vertice_indice){
        int posicao = 0;
        int menor_custo = getEtiqueta(vertice_indice, 0).getCustoAcumulado();
        for (int i = 1; i < getTamanhoListaEtiqueta(vertice_indice); ++i){
            int custo_aux = getEtiqueta(vertice_indice, i).getCustoAcumulado();
            if (custo_aux < menor_custo){
                menor_custo = custo_aux;
                posicao = i;
            }
        }
        return posicao;
    }

    Etiqueta<TYPE> getEtiquetaMenorCusto(const int& vertice_indice){
        return getEtiqueta(vertice_indice, getPosicaoMenorCusto(vertice_indice));
    }

    void inserirEtiqueta(const int& vertice_indice, const Etiqueta<TYPE>& item){
        verificacaoPadrao(vertice_indice);
        etiqueta[vertice_indice]->inserirInicio(item);
    }

    void inserirEtiquetaPosicao(const int& vertice_indice, const int& posicao, const Etiqueta<TYPE>& item){
        verificacaoPadrao(vertice_indice);
        etiqueta[vertice_indice]->inserirPosicao(posicao, item);
    }

    Etiqueta<TYPE> retirarEtiquetaPosicao(const int& vertice_indice, const int& posicao){
        verificacaoPadrao(vertice_indice);
        return etiqueta[vertice_indice]->retirarPosicao(posicao);
    }

    int criarEtiquetaTrue(const int& vertice_indice){
        verificacaoPadrao(vertice_indice);
        NOGrafo<TYPE> grafo_temp = grafo->getNOGrafo(vertice_indice, 0);
        int vertice = grafo_temp.getVertice();
        Etiqueta<TYPE> etiqueta_valida = getEtiquetaValida(vertice_indice);
        Etiqueta<TYPE> item(grafo_temp.getPeso() + etiqueta_valida.getCustoAcumulado(),
                            vertice,
                            etiqueta_valida.getQuantidadeArestasVisitadas() + 1,
                            true);
        inserirEtiqueta(vertice - 1, item);
        return vertice;
    }

    void criarEtiquetaFalse(const int& vertice_indice){
        verificacaoPadrao(vertice_indice);
        Etiqueta<TYPE> etiqueta_valida = getEtiquetaValida(vertice_indice);
        for (int i = 0; i < grafo->getTamanhoListaGrafo(vertice_indice); ++i){
            NOGrafo<TYPE> grafo_temp = grafo->getNOGrafo(vertice_indice, i);
            Etiqueta<TYPE> item(grafo_temp.getPeso() + etiqueta_valida.getCustoAcumulado(),
                                vertice_indice + 1,
                                etiqueta_valida.getQuantidadeArestasVisitadas() + 1,
                                false);
            inserirEtiqueta(grafo_temp.getVertice() - 1, item);
        }
    }

    int getVerticeMenorCusto(const int& vertice_indice){
        verificacaoPadrao(vertice_indice);
        NOGrafo<TYPE> grafo_menor = grafo->getNOGrafo(vertice_indice, 0);
        Etiqueta<TYPE> etiqueta_menor = getEtiquetaMenorCusto(grafo_menor.getVertice() - 1);
        int vertice_menor = grafo_menor.getVertice();
        for (int i = 1; i < grafo->getTamanhoListaGrafo(vertice_indice); ++i){
            int vertice_temp = grafo->getNOGrafo(vertice_indice, i).getVertice();
            Etiqueta<TYPE> etiqueta_temp = getEtiquetaMenorCusto(vertice_temp - 1);
            if (etiqueta_temp.getCustoAcumulado() < etiqueta_menor.getCustoAcumulado()){
                etiqueta_menor = etiqueta_temp;
                vertice_menor = vertice_temp;
            }
        }
        return vertice_menor;
    }

    void encontrarCaminho(int vertice){
        Etiqueta<TYPE> primeira_etiqueta(TYPE(), 0, 0, true);
        inserirEtiqueta(vertice - 1, primeira_etiqueta);
        for (int i = 1; i < n_vertices; ++i)
        {
            int vertice_indice = vertice - 1;
            int tamanho_lista_grafo = grafo->getTamanhoListaGrafo(vertice_indice);
            if (tamanho_lista_grafo == 1 && getTamanhoListaEtiqueta(grafo->getNOGrafo(vertice_indice, 0).getVertice() - 1) == 0)
            {
                vertice = criarEtiquetaTrue(vertice_indice);
            }else{
                criarEtiquetaFalse(vertice_indice);
                vertice = getVerticeMenorCusto(vertice_indice);
                Etiqueta<TYPE> etiqueta_menor = retirarEtiquetaPosicao(vertice - 1, getPosicaoMenorCusto(vertice - 1));
                etiqueta_menor.setSituacaoVertice(true);
                inserirEtiqueta(vertice - 1, etiqueta_menor);
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
