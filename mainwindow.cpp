#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try
    {
        grafo = new GrafoDirecionado<int>(5);
        grafo->inserirAresta(1, 5, 100);
        grafo->inserirAresta(5, 2, 120);
        grafo->inserirAresta(5, 4, 200);
        grafo->inserirAresta(2, 3, 90);
        grafo->inserirAresta(2, 4, 330);
        grafo->inserirAresta(4, 3, 180);
        grafo->inserirAresta(3, 2, 110);
        Lista<Vertice *> vertices;
        Lista<Aresta *> arestas;
        QGraphicsScene *scene = new QGraphicsScene();
        Caminho<int> caminho(grafo);
        caminho.encontrarCaminho(1);
        int x = 0;
        for (int i = 0; i < grafo->getNVertices(); ++i)
        {
            Etiqueta<int> etiqueta_temp = caminho.getEtiquetaValida(i);
            if (i % 3 == 0)
            {
                Vertice *vertice = new Vertice(x + 100 * (i % 3), 150 * (i % 3), 20, i + 1);
                EtiquetaDesenho *etiqueta = new EtiquetaDesenho(25 + (x + 100 * (i % 3)),
                                                                (150 * (i % 3)) - 30,
                                                                250,
                                                                80,
                                                                etiqueta_temp.getCustoAcumulado(),
                                                                true,
                                                                etiqueta_temp.getVerticePrecedente(),
                                                                etiqueta_temp.getQuantidadeArestasVisitadas());
                scene->addItem(etiqueta);
                x = x + 150;
                vertices.inserirInicio(vertice);
                scene->addItem(vertice);
            }
            else if (i % 3 == 1)
            {
                Vertice *vertice = new Vertice(x + 100 * (i % 3), 150 * (i % 3), 20, i + 1);
                EtiquetaDesenho *etiqueta = new EtiquetaDesenho(25 + (x + 100 * (i % 3)),
                                                                (150 * (i % 3)) - 30,
                                                                250,
                                                                80,
                                                                etiqueta_temp.getCustoAcumulado(),
                                                                true,
                                                                etiqueta_temp.getVerticePrecedente(),
                                                                etiqueta_temp.getQuantidadeArestasVisitadas());
                scene->addItem(etiqueta);
                x = x + 150;
                vertices.inserirInicio(vertice);
                scene->addItem(vertice);
            }
            else
            {
                Vertice *vertice = new Vertice(x + 100 * (i % 3), 150 * (i % 3), 20, i + 1);
                EtiquetaDesenho *etiqueta = new EtiquetaDesenho(25 + (x + 100 * (i % 3)),
                                                                (150 * (i % 3)) - 30,
                                                                250,
                                                                80,
                                                                etiqueta_temp.getCustoAcumulado(),
                                                                true,
                                                                etiqueta_temp.getVerticePrecedente(),
                                                                etiqueta_temp.getQuantidadeArestasVisitadas());
                scene->addItem(etiqueta);
                x = x + 150;
                vertices.inserirInicio(vertice);
                scene->addItem(vertice);
            }
        }
        // Vertice *vertice1 = new Vertice(100, 100, 20, 1);
        // vertices.inserirInicio(vertice1);
        // Vertice *vertice2 = new Vertice(200, 100, 20, 2);
        // vertices.inserirInicio(vertice2);
        // Aresta *aresta1 = new Aresta(vertice1, vertice2, 10);
        // arestas.inserirInicio(aresta1);
        // scene->addItem(vertice1);
        // scene->addItem(vertice2);
        // scene->addItem(aresta1);
        ui->graphicsView->setScene(scene);
        // GrafoNaoOrientado<int> *grafo = new GrafoNaoOrientado<int>(6);
        // grafo->inserirAresta(1, 4, 5);
        // grafo->inserirAresta(1, 3, 15);
        // grafo->inserirAresta(1, 2, 10);
        // grafo->inserirAresta(2, 4, 20);
        // grafo->inserirAresta(2, 3, 10);
        // grafo->inserirAresta(2, 6, 10);
        // grafo->inserirAresta(3, 5, 5);
        // grafo->inserirAresta(4, 5, 5);
        // grafo->inserirAresta(4, 6, 25);

        // Caminho<int> caminho(grafo);
        // caminho.encontrarCaminho(1);
        // for (int i = 0; i < 5; ++i){
        //     std::cout << "Vertice " << i + 1 << '\n';
        //     for (int j = 0; j < caminho.getTamanhoListaEtiqueta(i); ++j){
        //         std::cout << "Posicao " << j << '\n';
        //         Etiqueta<int> temp = caminho.getEtiqueta(i, j);
        //         std::cout << "Custo acumulado: " << temp.getCustoAcumulado() << '\n';
        //         std::cout << "Vertice Precedente: " << temp.getVerticePrecedente() << '\n';
        //         std::cout << "Quantidade arestas visitadas: " << temp.getQuantidadeArestasVisitadas() << '\n';
        //         std::cout << "Situacao Vertice: " << temp.getSituacaoVertice() << '\n';
        //     }
        //     std::cout << '\n';
        // }
        // std::cout << "Fim\n";
        // if (grafo){
        //     delete grafo;
        //     grafo = 0;
        // }
    }
    catch (std::bad_alloc &e)
    {
        QMessageBox::critical(this, "Erro", "Nao foi possivel alocar memoria");
    }
}

MainWindow::~MainWindow()
{
    if (grafo)
    {
        delete grafo;
    }
    delete ui;
}