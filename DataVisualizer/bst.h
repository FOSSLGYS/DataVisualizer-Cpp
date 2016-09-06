#ifndef BST_H
#define BST_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPointF>
#include "visualizer.h"

namespace Ui {
class Bst;
}

class Bst : public QWidget
{
    Q_OBJECT

public:
    explicit Bst(QWidget *parent = 0);
    ~Bst();
    void insertElem(QString val);
    void removeElem(QString val);
    void cleanupElem(Ui::EllipseElement *node);
    int insertBst(int idx, QString val);
    int removeBst(int idx, QString val);

private slots:
    void on_pushButton_2_clicked();
    
    void on_pushButton_clicked();
    
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Bst *ui;
    QGraphicsScene *scene;
    QValidator *v;
    Ui::binaryTree *bTree;
};

#endif // BST_H
