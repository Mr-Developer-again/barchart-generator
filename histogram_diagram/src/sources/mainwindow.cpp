#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <../include/qcustomplot.h>

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <QFont>

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

void Arad::MainWindow::setRange(QString const& range)
{
    this->_range = (range.toInt() >= 1) ? range.toInt() : throw std::invalid_argument("the input range must be >= 1");
}

uint32_t Arad::MainWindow::getRange() const
{ return this->_range; }

void Arad::MainWindow::setPath(QString const& inputPath)
{
    this->_csvFilePath = (inputPath.size() > 0) ? inputPath : throw std::invalid_argument("you forgot to fill in the \"file path\" section");
}

QString Arad::MainWindow::getPath() const
{ return this->_csvFilePath; }

void Arad::MainWindow::setDelimiter(QString const& delimiter)
{
    this->_csvContentsDelimiter = (delimiter.size() > 0) ? delimiter : throw std::invalid_argument("you forgot to fill in the \"delimiter\" section");
}

QString Arad::MainWindow::getDelimiter() const
{ return this->_csvContentsDelimiter; }

void Arad::MainWindow::setHeightColumn(QString const& heightColumn)
{
    this->_heightColumn = (heightColumn.toInt() >= 1) ? heightColumn.toInt() : throw std::invalid_argument("the height column number must be >= 1");
}

uint32_t Arad::MainWindow::getHeightColumn() const
{ return this->_heightColumn; }

void Arad::MainWindow::setWeightColumn(QString const& weightColumn)
{
    this->_weightColumn = (weightColumn.toInt() >= 1) ? weightColumn.toInt() : throw std::invalid_argument("the weight column number must be >= 1");
}

uint32_t Arad::MainWindow::getWeightColumn() const
{ return this->_weightColumn; }

void Arad::MainWindow::slotGettingInputInformation()
{
    Arad::MainWindow::setRange(ui->lineEdit->text());
    Arad::MainWindow::setPath(ui->lineEdit_2->text());
    Arad::MainWindow::setDelimiter(ui->lineEdit_3->text());
    Arad::MainWindow::setHeightColumn(ui->lineEdit_4->text());
    Arad::MainWindow::setWeightColumn(ui->lineEdit_5->text());

    QFont pushButtonFont("Consolas", -1, 50, true);
    ui->pushButton->setFont(pushButtonFont);
    ui->pushButton->setText("OK");
}

Arad::MainWindow::~MainWindow()
{
    delete ui;
}
