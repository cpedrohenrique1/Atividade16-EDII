#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "grafodirecionado.h"
#include "caminho.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "grafoDesenho.h"
#include "arquivo.h"
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_criar_clicked();

    void on_pushButton_inserir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_excluir_clicked();

    void on_pushButton_abrir_arquivo_clicked();

    void on_pushButton_encontrar_caminho_clicked();

private:
    Ui::MainWindow *ui;
    GrafoDirecionado<int> *grafo;
    QGraphicsScene *cena;
    Lista<Vertice *> *vertices;
};
#endif // MAINWINDOW_H
