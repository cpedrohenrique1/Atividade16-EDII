#include "tabela.h"

Tabela::Tabela() : tabela(0),
                   grafo(0)
{
}

Tabela::Tabela(QTableWidget *parent, const int &tamanho) : tabela(0),
                                                           grafo(0)
{
    if (!parent)
        throw QString("tabela nao criada");
    if (tamanho <= 0)
        throw QString("tamanho invalido");
    this->tabela = parent;
    try
    {
        grafo = new Grafo<int>(tamanho);
    }
    catch (const std::bad_alloc &e)
    {
        throw QString("Nao foi possivel alocar memoria");
    }
}

Tabela::~Tabela()
{
    if (grafo)
        delete grafo;
}

void Tabela::start()
{
    if (!grafo){
        throw QString("Grafo nao criado");
    }
    if (!tabela)
        throw QString("tabela nao localizada {start}");
    tabela->setRowCount(grafo->getNVertices());
    tabela->setColumnCount(grafo->getNVertices());
    tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabela->horizontalHeader()->setVisible(false);
}

void Tabela::limpar()
{
    if (!tabela)
        throw QString("tabela nao localizada, {limpartabela}");
    tabela->setColumnCount(0);
    tabela->setRowCount(0);
    tabela->clearContents();
    start();
}

void Tabela::atualizar()
{
    if (!tabela)
        throw QString("tabela nao localizada {atualizar}");

    if (!grafo)
        throw QString("grafo nao localizado {atualizar}");

    limpar();
    for (int i = 0; i < grafo->getNVertices(); ++i){
        for (int j = 0; j < grafo->getTamanhoLista(i); ++j){
            NOGrafo<int> no = grafo->getNOGrafo(i, j);
            tabela->setItem(i, j, new QTableWidgetItem(QString::number(no.getVertice()) + " | " + QString::number(no.getPeso())));
        }
    }
}

void Tabela::inserirAresta(const int &vertice1, const int& vertice2, const int &peso){
    if (!grafo){
        throw QString("Grafo nao criado");
    }
    grafo->inserirAresta(vertice1, vertice2, peso);
    atualizar();
}
void Tabela::alterarAresta(const int &vertice1, const int& vertice2, const int &peso){
    if (!grafo){
        throw QString("Grafo nao criado");
    }
    grafo->setAresta(vertice1, vertice2, peso);
    atualizar();
}
void Tabela::removerAresta(const int &vertice1, const int& vertice2){
    if (!grafo){
        throw QString("Grafo nao criado");
    }
    grafo->removerAresta(vertice1, vertice2);
    atualizar();
}