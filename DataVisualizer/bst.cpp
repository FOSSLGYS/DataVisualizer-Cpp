#include "bst.h"
#include "ui_bst.h"

Bst::Bst(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bst)
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

Bst::~Bst()
{
    delete scene;
    delete bTree;
    delete ui;
}

int Bst::removeBst(int idx, QString val)
{
    int insertIdx = MAX_ENTRIES+1;

    if ((bTree->getData(idx-1) == INVALID_DATA) ||
        (bTree->getData(idx-1) == val.toInt())) {
        insertIdx = idx;
    } else if (bTree->getData(idx-1) < val.toInt()) {
        insertIdx = insertBst((2*idx+1), val);
    } else if (bTree->getData(idx-1) > val.toInt()) {
        insertIdx = insertBst((2*idx), val);
    }

    return insertIdx;
 }

int Bst::insertBst(int idx, QString val)
{
    int insertIdx = 0;

    if ((bTree->getData(idx-1) == INVALID_DATA) ||
        (bTree->getData(idx-1) == val.toInt())) {
        bTree->setData((idx-1), val);
        insertIdx = idx;
    } else if (bTree->getData(idx-1) < val.toInt()) {
        insertIdx = insertBst((2*idx+1), val);
    } else if (bTree->getData(idx-1) > val.toInt()) {
        insertIdx = insertBst((2*idx), val);
    }

    return insertIdx;
 }

// This API is to draw the node for the
// element inserted and link it to the parent
// Most of the logic deals with adjusting the
// parent node positions to make room for the
// ones.
void Bst::insertElem(QString val)
{ 
    //Inser to BST
    int idx = insertBst(1, val);

    int newEntries = (idx-(bTree->getNumEntries()));
    bTree->incrEntries(newEntries);

    bTree->insertNode();
}

// This API deals with removing a node
// and readjusting the parent nodes back
// to the previous position if there is
// a height change.
void Bst::removeElem(QString val)
{

    int idx = removeBst(1, val);

    if (idx == MAX_ENTRIES+1) {
        // Entry not found -- do nothing
        return;
    }

    bTree->decrEntries(bTree->getNumEntries()-idx);
}

void Bst::on_pushButton_2_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    insertElem(val);
}

void Bst::on_pushButton_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    removeElem(val);
}

void Bst::on_pushButton_4_clicked()
{
    int randNum[10];

    Ui::genRand(randNum, 10);
    for (int i=0; i<10; i++) {
        insertElem(QString::number(randNum[i]));
    }
}

void Bst::on_pushButton_3_clicked()
{
    //Clear all
}
