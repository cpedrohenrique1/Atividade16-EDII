#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <QFile>
#include <QTextStream>
#include "grafo.h"

class Arquivo
{
private:
    Grafo *vetor;
    int n_vertices;
public:
    Arquivo();
    void abrir();
    void carregar_elementos(QTextStream &in);
    int getVertices()const;
    Grafo* getVetor()const;
};

#endif // ARQUIVO_H