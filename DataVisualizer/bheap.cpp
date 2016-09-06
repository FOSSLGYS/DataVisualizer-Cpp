#include "bheap.h"
#include "ui_bheap.h"
#include <QGraphicsEllipseItem>
#include "math.h"
#include "stdio.h"

Bheap::Bheap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bheap)
{
    ui->setupUi(this);
    QPixmap bkgnd(":files/images/bckgnd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QRectF scene_coords;

    scene_coords.setX(-250); scene_coords.setY(-250);
    scene_coords.setWidth(500); scene_coords.setHeight(500);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    bTree = new Ui::binaryTree(ui->graphicsView, scene, scene_coords);

    v = new QIntValidator(0, 65535, this);
    ui->lineEdit->setValidator(v);
}

Bheap::~Bheap()
{
    delete scene;
    delete bTree;
    delete ui;
}

// HeapDown. Move the last element
// to its right position.
void Bheap::heapDown()
{
    int pos, minPos;

    pos = 1;
    while ((pos<bTree->getNumEntries()) &&
           (bTree->getData(pos-1) != 0)) {
        // Get the array position for the minimum
        if (((2*pos-1)<bTree->getNumEntries()) &&
            (bTree->getData(2*pos) > bTree->getData(2*pos-1))) {
            minPos = 2*pos;
        } else if ((2*pos) < bTree->getNumEntries()) {
            minPos = 2*pos+1;
        } else {
            minPos = pos;
        }
        if (bTree->getData(pos-1) > bTree->getData(minPos-1)) {
            QString tmp;
            tmp = bTree->getDataStr(pos-1);
            bTree->setData((pos-1), bTree->getDataStr(minPos-1));
            bTree->setData((minPos-1), tmp);
            pos = minPos;
        } else {
            break;
        }
    }
}

// Heapify. Place the newly
// inserted element in its right place.
void Bheap::heapUp()
{
    int pos;

    pos = bTree->getNumEntries();
    while (pos>1) {
        if (bTree->getData(pos-1) < bTree->getData(pos/2-1)) {
            QString tmp;
            tmp = bTree->getDataStr(pos-1);
            bTree->setData((pos-1), bTree->getDataStr(pos/2-1));
            bTree->setData((pos/2-1), tmp);
        }
        pos = pos/2;
    }
}

// This API is to draw the node for the
// element inserted and link it to the parent
// Most of the logic deals with adjusting the
// parent node positions to make room for the
// ones.
void Bheap::insertElem(QString val)
{

    bTree->incrEntries(1);
    bTree->setData((bTree->getNumEntries()-1), val);

    //Adjust the heap
    heapUp();

    bTree->insertNode();


}

// This API deals with removing a node
// and readjusting the parent nodes back
// to the previous position if there is
// a height change.
void Bheap::removeElem(int idx)
{
    bTree->setData((idx-1), bTree->getDataStr(bTree->getNumEntries()-1));
    bTree->setData((bTree->getNumEntries()-1), QString::number(INVALID_DATA));
    bTree->decrEntries(1);

    // Adjust the heap
    heapDown();

    bTree->removeNode();
}

// Insert element to Heap
void Bheap::on_pushButton_2_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    insertElem(val);
}

// Remove Element from Heap
void Bheap::on_pushButton_clicked()
{
    removeElem(1);
}

//Clear Heap
void Bheap::on_pushButton_3_clicked()
{
    bTree->clearTree();
}

void Bheap::on_pushButton_4_clicked()
{
    int randNum[10];

    Ui::genRand(randNum, 10);
    for (int i=0; i<10; i++) {
        insertElem(QString::number(randNum[i]));
    }
}
