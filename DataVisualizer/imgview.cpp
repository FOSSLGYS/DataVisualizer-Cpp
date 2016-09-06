
#include "imgview.h"
#include "ui_imgview.h"

imgview::imgview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imgview)
{
    item = NULL;
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

imgview::~imgview()
{
    delete ui;
}

void imgview::setimg(Ui::dataType type)
{
    switch (type) {
        case Ui::QUEUE:
            if (item != NULL) {
                ui->graphicsView->scene()->removeItem(item);
                delete item;
                item = NULL;
            }
            item = new QGraphicsPixmapItem;
            item->setPixmap(QPixmap("queue.png"));
            ui->graphicsView->scene()->addItem(item);
            break;
        case Ui::STACK:
            break;
        case Ui::MINHEAP:
            break;
        case Ui::BST:
            break;
        default:
            break;
    }
}

