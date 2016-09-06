#include "mainwindow.h"
#include <QApplication>
#include "stdlib.h"
#include "time.h"

#define MAX 500

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void Ui::genRand(int *list, int count)
{
    int numRand = 0;

    //seed the random number generator
    srand(time(0));

    while (numRand < count) {
        list[numRand] = rand()%MAX;
        numRand++;
    }

}
