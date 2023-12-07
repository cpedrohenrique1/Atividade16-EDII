#ifndef ETIQUETA_H
#define ETIQUETA_H

template <class TYPE>
class Etiqueta
{
private:
    TYPE CustoAcumulado;
    int VerticePrecedente;
    int QuantidadeArestasVisitadas;
    bool SituacaoVertice;
public:
    Etiqueta(TYPE valorInicial = TYPE()):   CustoAcumulado(valorInicial),
                                            VerticePrecedente(0),
                                            QuantidadeArestasVisitavas(0),
                                            SituacaoVertice(false)
    {}
    void setCustoAcumulado(TYPE custo_acumulado);
    TYPE getCustoAcumulado()const;
    void setVerticePrecedente(int vertice_precedente);
    int getVerticePrecedente()const;
    void setQuantidadeArestasVisitadas(int quantidade_arestas_visitadas);
    int getQuantidadeArestasVisitadas() const;
    void setSituacaoVertice(bool situacao_vertice);
    bool getSituacaoVertice() const;
};

#endif // ETIQUETA_H
