#include "headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Arad::MainWindow w(nullptr);
    w.show();
    return a.exec();
}
