#ifndef ETIQUETA_H
#define ETIQUETA_H

template <class TYPE>
class Etiqueta
{
private:
    TYPE CustoAcumulado;
    int VerticePrecedente;
    int QuantidadeArestasVisitavas;
    bool SituacaoVertice;
public:
    Etiqueta(TYPE valorInicial = TYPE()):   CustoAcumulado(valorInicial),
                                            VerticePrecedente(0),
                                            QuantidadeArestasVisitavas(0),
                                            SituacaoVertice(false)
    {}
};

#endif // ETIQUETA_H
