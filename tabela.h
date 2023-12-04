#ifndef TABELA_H
#define TABELA_H

#include "QTableWidget"
#include "QHeaderView"
#include "grafo.h"

class Tabela
{
private:
    QTableWidget *tabela;
    Grafo<int> *grafo;

public:
    Tabela();
    Tabela(QTableWidget *parent, const int &tamanho);
    ~Tabela();
    void start();
    void limpar();
    void atualizar();
    void inserirAresta(const int &vertice1, const int& vertice2, const int &peso);
    void alterarAresta(const int &vertice1, const int& vertice2, const int &peso);
    void removerAresta(const int &vertice1, const int& vertice2);
};

#endif // TABELA_H