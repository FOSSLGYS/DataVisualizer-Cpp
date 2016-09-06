#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imgview.h"
#include "stack.h"
#include "bheap.h"
#include "queue.h"
#include "bst.h"
#include "visualizer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    imgview imgui;
    stack stackui;
    Queue queueui;
    Bheap  bheapui;
    Bst bstui;
};

#endif // MAINWINDOW_H
