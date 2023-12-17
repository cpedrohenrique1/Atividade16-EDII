#ifndef GRAFODESENHO_H
#define GRAFODESENHO_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <cmath>
#include <QGraphicsScene>
#include "lista.h"
#include "grafo.h"
#include <ctime>

class Vertice : public QGraphicsEllipseItem
{
private:
    QGraphicsTextItem *text;
    int id;

public:
    Vertice(int x, int y, int radius, int id) : QGraphicsEllipseItem(x - radius, y - radius, 2 * radius, 2 * radius)
    {
        text = new QGraphicsTextItem(QString::number(id), this);
        text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);
        this->id = id;
    }

    int getId()
    {
        return id;
    }

    ~Vertice()
    {
        delete text;
    }
};

class Aresta : public QGraphicsLineItem
{
private:
    QGraphicsTextItem *peso;
    static const int arrowSize = 10;

public:
    Aresta(Vertice* start, Vertice* end, int peso) : QGraphicsLineItem(),
        peso(0)
    {
        QLineF line(start->rect().center(), end->rect().center());
        double angle = std::atan2(-line.dy(), line.dx());
        QPointF edgeOffset(cos(angle) * start->rect().width() / 2, sin(angle) * start->rect().width() / 2);
        line.setP1(line.p1() + edgeOffset);
        line.setP2(line.p2() - edgeOffset);
        setLine(line);
        this->peso = new QGraphicsTextItem(QString::number(peso));
        QPointF midPoint = (start->rect().center() + end->rect().center()) / 2;
        int offsetX = 0;
        int offsetY = 0;
        if (rand() % 2 == 0){
            offsetX = (rand() % 100) - 50;
        }else{
            offsetY = (rand() % 100) - 50;
        }
        this->peso->setPos(midPoint + QPointF(offsetX, offsetY));
    }

    QGraphicsTextItem *getPeso()
    {
        return peso;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override
    {
        painter->drawLine(line());
        double angle = std::atan2(-line().dy(), line().dx());
        QPointF arrowP1 = line().p2() - QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line().p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPolygonF arrowHead;
        arrowHead << line().p2() << arrowP1 << arrowP2;
        painter->drawPolygon(arrowHead);
    }

    ~Aresta()
    {
        if (peso){
            delete peso;
        }
    }
};

class EtiquetaDesenho : public QGraphicsRectItem
{
private:
    int custoAcumulado;
    bool situacaoVertice;
    int verticePrecedente;
    int quantidadeArestasVisitadas;
    QGraphicsTextItem *text;

public:
    EtiquetaDesenho(int x, int y, int width, int height, int custoAcumulado, bool situacaoVertice, int verticePrecedente, int quantidadeArestasVisitadas)
        : QGraphicsRectItem(x, y, width, height),
          custoAcumulado(custoAcumulado),
          situacaoVertice(situacaoVertice),
          verticePrecedente(verticePrecedente),
          quantidadeArestasVisitadas(quantidadeArestasVisitadas)
    {
        text = new QGraphicsTextItem(this);
        text->setPos(x, y);
        updateText();
    }

    void updateText()
    {
        QString labelText = QString("Custo acumulado: %1\nSituacao Vertice: %2\nVertice Precedente: %3\nQuantidade arestas visitadas: %4")
                                .arg(custoAcumulado)
                                .arg(situacaoVertice ? "True" : "False")
                                .arg(verticePrecedente)
                                .arg(quantidadeArestasVisitadas);
        text->setPlainText(labelText);
    }

    ~EtiquetaDesenho()
    {
        delete text;
    }
};

#endif // GRAFODESENHO_H
