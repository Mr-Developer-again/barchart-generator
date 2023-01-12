#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <../include/qcustomplot.h>

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Arad::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    /// configuring pushButton
    ui->pushButton->setText("Send All Information");

    /// connecting signals and slots
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotGettingInputInformation()));
}

void Arad::MainWindow::setRange(uint32_t range)
{
    this->_range = range;
}

uint32_t Arad::MainWindow::getRange() const
{ return this->_range; }

void Arad::MainWindow::setPath(QString const& inputPath)
{
    this->_csvFilePath = inputPath;
}

QString Arad::MainWindow::getPath() const
{ return this->_csvFilePath; }

void Arad::MainWindow::setDelimiter(QString const& delimiter)
{
    this->_csvContentsDelimiter = delimiter;
}

QString Arad::MainWindow::getDelimiter() const
{ return this->_csvContentsDelimiter; }

void Arad::MainWindow::slotGettingInputInformation()
{
    Arad::MainWindow::setRange(ui->lineEdit->text().toInt());
    Arad::MainWindow::setPath(ui->lineEdit_2->text());
    Arad::MainWindow::setDelimiter(ui->lineEdit_3->text());
}

Arad::MainWindow::~MainWindow()
{
    delete ui;
}
