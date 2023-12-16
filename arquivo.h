#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <QFile>
#include <QTextStream>
#include "grafodirecionado.h"

class Arquivo
{
private:
    GrafoDirecionado<int> *vetor;
    int n_vertices;
public:
    Arquivo();
    void abrir();
    void carregar_elementos(QTextStream &in);
    int getVertices()const;
    NOGrafo<int> getVetor(const int& linha, const int& coluna)const;
};

#endif // ARQUIVO_H