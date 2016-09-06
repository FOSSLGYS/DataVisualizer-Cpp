#ifndef QUEUE_H
#define QUEUE_H

#include <QWidget>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QLineF>
#include "visualizer.h"

namespace Ui {
class Queue;
}

class Queue : public QWidget
{
    Q_OBJECT

public:
    explicit Queue(QWidget *parent = 0);
    ~Queue();
    void insertElem(QString val);
    void removeElem(int idx);
    void cleanupElem(Ui::RectElement *elem);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Queue *ui;
    QPointF fPoint, rPoint;
    QLineF  fLineCoords, rLineCoords;
    Ui::List *qList;
    QGraphicsTextItem *fLabel;
    QGraphicsLineItem *fLine;
    QValidator *v;
};

#endif // QUEUE_H
