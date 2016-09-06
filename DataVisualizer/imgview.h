#ifndef IMGVIEW_H
#define IMGVIEW_H

#include <QWidget>
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "visualizer.h"

namespace Ui {
class imgview;
}

class imgview : public QWidget
{
    Q_OBJECT

public:
    explicit imgview(QWidget *parent = 0);
    ~imgview();
    void setimg(Ui::dataType type);

private:
    Ui::imgview *ui;
    QGraphicsPixmapItem *item;
};

#endif // IMGVIEW_H
