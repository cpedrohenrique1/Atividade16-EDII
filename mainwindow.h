#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "grafodirecionado.h"
#include "grafonaoorientado.h"
#include "caminho.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "grafoDesenho.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GrafoDirecionado<int> *grafo;
};
#endif // MAINWINDOW_H
