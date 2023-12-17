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

        for (int i = 0; i < grafo->getNVertices(); ++i){
            for (int j = 0; j < grafo->getTamanhoListaGrafo(i); ++j){
                NOGrafo<int> no_grafo = grafo->getNOGrafo(i, j);
                Aresta *aresta = new Aresta(vertices.acessarPosicao(i),
                                            vertices.acessarPosicao(no_grafo.getVertice() - 1),
                                            no_grafo.getPeso());
                arestas.inserirInicio(aresta);
                scene->addItem(aresta);
            }
        }
        ui->graphicsView->setScene(scene);
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