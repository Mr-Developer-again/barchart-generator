#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <../include/qcustomplot.h>

Arad::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Arad::MainWindow::~MainWindow()
{
    delete ui;
}

