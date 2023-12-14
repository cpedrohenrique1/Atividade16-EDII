#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try{
        // GrafoDirecionado<int> *grafo = new GrafoDirecionado<int>(5);
        // grafo->inserirAresta(1, 5, 100);
        // grafo->inserirAresta(5, 2, 120);
        // grafo->inserirAresta(5, 4, 200);
        // grafo->inserirAresta(2, 3, 90);
        // grafo->inserirAresta(2, 4, 330);
        // grafo->inserirAresta(4, 3, 180);
        // grafo->inserirAresta(3, 2, 110);

        GrafoNaoOrientado<int> *grafo = new GrafoNaoOrientado<int>(6);
        grafo->inserirAresta(1, 4, 5);
        grafo->inserirAresta(1, 3, 15);
        grafo->inserirAresta(1, 2, 10);
        grafo->inserirAresta(2, 4, 20);
        grafo->inserirAresta(2, 3, 10);
        grafo->inserirAresta(2, 6, 10);
        grafo->inserirAresta(3, 5, 5);
        grafo->inserirAresta(4, 5, 5);
        grafo->inserirAresta(4, 6, 25);
        Caminho<int> caminho(grafo);
        caminho.encontrarCaminho(1);
        for (int i = 0; i < 5; ++i){
            std::cout << "Vertice " << i + 1 << '\n';
            for (int j = 0; j < caminho.getTamanhoListaEtiqueta(i); ++j){
                std::cout << "Posicao " << j << '\n';
                Etiqueta<int> temp = caminho.getEtiqueta(i, j);
                std::cout << "Custo acumulado: " << temp.getCustoAcumulado() << '\n';
                std::cout << "Vertice Precedente: " << temp.getVerticePrecedente() << '\n';
                std::cout << "Quantidade arestas visitadas: " << temp.getQuantidadeArestasVisitadas() << '\n';
                std::cout << "Situacao Vertice: " << temp.getSituacaoVertice() << '\n';
            }
            std::cout << '\n';
        }
        std::cout << "Fim\n";
        if (grafo){
            delete grafo;
            grafo = 0;
        }
    }catch(std::bad_alloc& e){
        QMessageBox::critical(this, "Erro", "Nao foi possivel alocar memoria");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

