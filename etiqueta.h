#ifndef ETIQUETA_H
#define ETIQUETA_H

#include "QString"

template <class TYPE>
class Etiqueta
{
private:
    TYPE custo_acumulado;
    int vertice_precedente;
    int quantidade_arestas_visitadas;
    bool situacao_vertice;
public:
    Etiqueta(TYPE valorInicial = TYPE()):   custo_acumulado(valorInicial),
                                            vertice_precedente(0),
                                            QuantidadeArestasVisitavas(0),
                                            situacao_vertice(false)
    {}
    void setCustoAcumulado(TYPE custo_acumulado){
        this->custo_acumulado = custo_acumulado;
    }
    TYPE getCustoAcumulado()const{
        return custo_acumulado;
    }
    void setVerticePrecedente(int vertice_precedente){
        if (vertice_precedente < 0){
            throw QString("Vertice precedente invalido");
        }
        this->vertice_precedente = vertice_precedente;
    }
    int getVerticePrecedente()const{
        return vertice_precedente;
    }
    void setQuantidadeArestasVisitadas(int quantidade_arestas_visitadas){
        if (quantidade_arestas_visitadas < 0){
            throw QString("Quantidade de arestas invalida");
        }
        this->getQuantidadeArestasVisitadas = quantidade_arestas_visitadas;
    }
    int getQuantidadeArestasVisitadas() const{
        return quantidade_arestas_visitadas;
    }
    void setSituacaoVertice(bool situacao_vertice){
        this->getSituacaoVertice = situacao_vertice;
    }
    bool getSituacaoVertice() const{
        return situacao_vertice;
    }
};

#endif // ETIQUETA_H
