#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":files/images/bckgnd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ui->pushButton->setToolTip("<img src=':files/images/queue.png'/> QUEUE");
    ui->pushButton_2->setToolTip("<img src=':files/images/stack.png'/> STACK");
    ui->pushButton_3->setToolTip("<img src=':files/images/minheap.png'/> MINHEAP");
    ui->pushButton_4->setToolTip("<img src=':files/images/bst.png'/> BST");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    queueui.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    stackui.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    bheapui.show();
}

void MainWindow::on_pushButton_4_clicked()
{
    bstui.show();
}
