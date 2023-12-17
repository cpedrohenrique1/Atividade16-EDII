#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <QFile>
#include <QTextStream>
#include "grafodirecionado.h"
#include <QFileDialog>
#include <QWidget>

class Arquivo
{
private:
    GrafoDirecionado<int> *vetor;
    QString endereco_arquivo;
public:
    Arquivo(QWidget *parent = nullptr);
    void abrir();
    void carregar_elementos(QTextStream &in);
    NOGrafo<int> getVetor(const int& linha, const int& coluna)const;
    int getTamanhoGrafo()const;
    int getTamanhoListaGrafo(const int& indice)const;
    ~Arquivo();
};

#endif // ARQUIVO_H