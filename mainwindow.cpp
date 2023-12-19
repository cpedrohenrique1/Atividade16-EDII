#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      grafo(0), cena(0)
{
    srand(time(0));
    ui->setupUi(this);
}

void MainWindow::on_pushButton_criar_clicked()
{
    try
    {
        if (ui->lineEdit_tamanho_grafo->text().isEmpty())
        {
            throw QString("Informe o tamanho do grafo");
        }
        if (grafo)
        {
            delete grafo;
            grafo = 0;
        }
        if (cena)
        {
            delete cena;
            cena = 0;
        }
        grafo = new GrafoDirecionado<int>(ui->lineEdit_tamanho_grafo->text().toInt());
        vertices = new Lista<Vertice *>;
        cena = new QGraphicsScene();
        int x = 0;
        int tamanho_grafo = grafo->getNVertices();
        // Criacao vertices
        for (int i = 0; i < tamanho_grafo; ++i)
        {
            if (i % 3 == 0)
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
            else if (i % 3 == 1)
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
            else
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
        }
        ui->graphicsView->setScene(cena);

    }
    catch (std::bad_alloc &e)
    {
        QMessageBox::critical(this, "ERRO", "Erro ao alocar memoria");
    }
    catch (QString &erro)
    {
        QMessageBox::critical(this, "ERRO", erro);
    }
    catch (...)
    {
        QMessageBox::critical(this, "ERRO", "Erro desconhecido");
    }
}

void MainWindow::on_pushButton_inserir_clicked()
{
    try
    {
        
    }
    catch (QString &erro)
    {
        QMessageBox::critical(this, "ERRO", erro);
    }
    catch (...)
    {
        QMessageBox::critical(this, "ERRO", "Erro desconhecido");
    }
}

void MainWindow::on_pushButton_alterar_clicked()
{
    try
    {
    }
    catch (QString &erro)
    {
        QMessageBox::critical(this, "ERRO", erro);
    }
    catch (...)
    {
        QMessageBox::critical(this, "ERRO", "Erro desconhecido");
    }
}

void MainWindow::on_pushButton_excluir_clicked()
{
    try
    {
        if (!grafo){
            throw QString("grafo nao foi criado");
        }
        if (!vertices){
            throw QString("nao foi possivel achar os vertices");
        }
        
    }
    catch (QString &erro)
    {
        QMessageBox::critical(this, "ERRO", erro);
    }
    catch (...)
    {
        QMessageBox::critical(this, "ERRO", "Erro desconhecido");
    }
}

void MainWindow::on_pushButton_abrir_arquivo_clicked()
{
    try
    {
        Arquivo arquivo(this);
        arquivo.abrir();
        if (grafo)
        {
            delete grafo;
            grafo = 0;
        }
        if (vertices)
        {
            delete vertices;
            vertices = 0;
        }
        grafo = new GrafoDirecionado<int>(arquivo.getTamanhoGrafo());
        vertices = new Lista<Vertice *>;
        for (int i = 0; i < arquivo.getTamanhoGrafo(); ++i)
        {
            for (int j = 0; j < arquivo.getTamanhoListaGrafo(i); ++j)
            {
                NOGrafo<int> no_grafo = arquivo.getVetor(i, j);
                grafo->inserirAresta(i + 1, no_grafo.getVertice(), no_grafo.getPeso());
            }
        }
        cena = new QGraphicsScene();
        int x = 0;
        int tamanho_grafo = grafo->getNVertices();
        // Criacao vertices
        for (int i = 0; i < tamanho_grafo; ++i)
        {
            if (i % 3 == 0)
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
            else if (i % 3 == 1)
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
            else
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
        }
        // Criacao arestas
        for (int i = 0; i < grafo->getNVertices(); ++i)
        {
            for (int j = 0; j < grafo->getTamanhoListaGrafo(i); ++j)
            {
                NOGrafo<int> no_grafo = grafo->getNOGrafo(i, j);
                for (int k = 0; k < vertices->getQuantidadeElementos(); ++k)
                {
                    if (vertices->acessarPosicao(k)->getId() == i + 1)
                    {
                        for (int l = 0; l < vertices->getQuantidadeElementos(); ++l)
                        {
                            if (vertices->acessarPosicao(l)->getId() == no_grafo.getVertice())
                            {
                                Aresta *aresta = new Aresta(vertices->acessarPosicao(k),
                                                            vertices->acessarPosicao(l),
                                                            no_grafo.getPeso());
                                cena->addItem(aresta->getPeso());
                                cena->addItem(aresta);
                            }
                        }
                    }
                }
            }
        }
        ui->graphicsView->setScene(cena);
    }
    catch (std::bad_alloc &e)
    {
        QMessageBox::critical(this, "ERRO", "Erro ao alocar memoria");
    }
    catch (QString &erro)
    {
        QMessageBox::critical(this, "ERRO", erro);
    }
    catch (...)
    {
        QMessageBox::critical(this, "ERRO", "Erro desconhecido");
    }
}

void MainWindow::on_pushButton_encontrar_caminho_clicked()
{
    try{
        if (!grafo){
            throw QString("Grafo nao encontrado");
        }
        if (!cena){
            throw QString("Cena nao encontrada (vertices desenhados na tela)");
        }
        if (!vertices){
            throw QString("Lista de vertices nao encontrado");
        }
        if (ui->lineEdit_vertice_caminho->text().isEmpty()){
            throw QString("vertice caminho nao pode estar vazio");
        }
        delete cena;
        cena = 0;
        cena = new QGraphicsScene();
        int x = 0;
        int tamanho_grafo = grafo->getNVertices();
        // Criacao vertices
        for (int i = 0; i < tamanho_grafo; ++i)
        {
            if (i % 3 == 0)
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
            else if (i % 3 == 1)
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
            else
            {
                Vertice *vertice = new Vertice(x, 150 * (i % 3), 20, i + 1);
                cena->addItem(vertice);
                x += 150;
                vertices->inserirInicio(vertice);
            }
        }
        // Criacao arestas
        for (int i = 0; i < grafo->getNVertices(); ++i)
        {
            for (int j = 0; j < grafo->getTamanhoListaGrafo(i); ++j)
            {
                NOGrafo<int> no_grafo = grafo->getNOGrafo(i, j);
                for (int k = 0; k < vertices->getQuantidadeElementos(); ++k)
                {
                    if (vertices->acessarPosicao(k)->getId() == i + 1)
                    {
                        for (int l = 0; l < vertices->getQuantidadeElementos(); ++l)
                        {
                            if (vertices->acessarPosicao(l)->getId() == no_grafo.getVertice())
                            {
                                Aresta *aresta = new Aresta(vertices->acessarPosicao(k),
                                                            vertices->acessarPosicao(l),
                                                            no_grafo.getPeso());
                                cena->addItem(aresta->getPeso());
                                cena->addItem(aresta);
                            }
                        }
                    }
                }
            }
        }
        Caminho caminho(grafo);
        caminho.encontrarCaminho(ui->lineEdit_vertice_caminho->text().toInt());
        // Criacao arestas
        for (int i = 0; i < grafo->getNVertices(); ++i)
        {
            for (int j = 0; j < grafo->getTamanhoListaGrafo(i); ++j)
            {
                NOGrafo<int> no_grafo = grafo->getNOGrafo(i, j);
                for (int k = 0; k < vertices->getQuantidadeElementos(); ++k)
                {
                    if (vertices->acessarPosicao(k)->getId() == i + 1)
                    {
                        for (int l = 0; l < vertices->getQuantidadeElementos(); ++l)
                        {
                            if (vertices->acessarPosicao(l)->getId() == no_grafo.getVertice())
                            {
                                Aresta *aresta = new Aresta(vertices->acessarPosicao(k),
                                                            vertices->acessarPosicao(l),
                                                            no_grafo.getPeso());
                                cena->addItem(aresta);
                            }
                        }
                    }
                }
            }
        }
        // Criacao Etiquetas
        x = 0;
        for (int i = 0; i < grafo->getNVertices(); ++i)
        {
            Etiqueta<int> etiqueta_temp = caminho.getEtiquetaValida(i);
            EtiquetaDesenho *etiqueta = new EtiquetaDesenho(25 + x,
                                                            (150 * (i % 3)) - 30,
                                                            250,
                                                            80,
                                                            etiqueta_temp.getCustoAcumulado(),
                                                            true,
                                                            etiqueta_temp.getVerticePrecedente(),
                                                            etiqueta_temp.getQuantidadeArestasVisitadas());
            etiqueta->setBrush(QBrush(Qt::white));
            etiqueta->setOpacity(0.5);
            cena->addItem(etiqueta);
            x += 150;
        }
        ui->graphicsView->setScene(cena);
    }catch (QString& e){
        QMessageBox::critical(this, "erro", e);
    }
}


MainWindow::~MainWindow()
{
    if (grafo)
    {
        delete grafo;
    }
    if (cena)
    {
        delete cena;
    }
    if (vertices)
    {
        delete vertices;
    }
    delete ui;
}
