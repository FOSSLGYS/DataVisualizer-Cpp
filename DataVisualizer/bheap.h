#ifndef BHEAP_H
#define BHEAP_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPointF>
#include "visualizer.h"

namespace Ui {
class Bheap;
};

class Bheap : public QWidget
{
    Q_OBJECT

public:
    explicit Bheap(QWidget *parent = 0);
    ~Bheap();
    void insertElem(QString val);
    void removeElem(int idx);
    void cleanupElem(Ui::EllipseElement *node);
    void heapUp();
    void heapDown();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Bheap *ui;
    QGraphicsScene *scene;
    QValidator *v;
    Ui::binaryTree *bTree;
};

#endif // BHEAP_H
