#include "queue.h"
#include "ui_queue.h"

Queue::Queue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Queue)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap bkgnd(":files/images/bckgnd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QRectF coords;
    coords.setX(-500); coords.setY(-500);
    coords.setWidth(1000); coords.setHeight(1000);
    rPoint.setX(-500);
    rPoint.setY(-387);
    rLineCoords.setLine(-480, -387, -480, -410);
    qList = new Ui::List(ui->graphicsView, scene, coords, rPoint, rLineCoords, "Rear");

    // Set the position for front
    // and rear labels
    QFont font;
    fPoint.setX(-500);
    fPoint.setY(-500);
    fLineCoords.setLine(-480, -480, -480, -460);
    fLabel = ui->graphicsView->scene()->addText("Front", font);
    fLabel->setPos(fPoint);
    fLine = ui->graphicsView->scene()->addLine(fLineCoords);
    v = new QIntValidator(0, 65535, this);
    ui->lineEdit->setValidator(v);
}


Queue::~Queue()
{
    delete ui;
}

// Insert an element into the
// Queue
void Queue::insertElem(QString val)
{
    qList->incrEntries(1);
    qList->setData(qList->getNumEntries()-1, val);

    qList->insertNode();
}

// Remove the element from Queue
void Queue::removeElem(int idx)
{
    //Remove the first and adjust
    for (int i=idx; i<qList->getNumEntries(); i++) {
        qList->setData(i, qList->getDataStr(i+1));
    }

    qList->setData(qList->getNumEntries(), "0");
    qList->decrEntries(1);

    qList->removeNode();
}

// Inserting a new element to the
// front of the queue.
void Queue::on_pushButton_2_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //No value -- No-op!
    }
    ui->lineEdit->setText("");

    insertElem(val);
}

// Delete an element from the
// queue and clean up.
void Queue::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, Ui::RectElement>::iterator it, it2;

    if (!qList->getNumEntries()) {
        return;
    }

    // Remove the first element
    removeElem(0);
}

// Clear queue
void Queue::on_pushButton_3_clicked()
{
   qList->clearList();
}

// Add 10 random numbers to Queue
void Queue::on_pushButton_4_clicked()
{
    int randNum[10];

    Ui::genRand(randNum, 10);
    for (int i=0; i<10; i++) {
        insertElem(QString::number(randNum[i]));
    }
}
