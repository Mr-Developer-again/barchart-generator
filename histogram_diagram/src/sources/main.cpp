#include "headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Arad::MainWindow w;
    w.show();
    return a.exec();
}
