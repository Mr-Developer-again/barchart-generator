#include <headers/mainwindow.h>
#include <ui_mainwindow.h>
#include <headers/scoping.h>
#include <headers/heighttablewidget.h>
#include <headers/weighttablewidget.h>
#include <headers/histogramdiagram.h>

#include <../include/qcustomplot.h>

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <QMessageBox>

Arad::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    
    /// configuring MainWindow
    this->setFixedSize(this->geometry().width(), this->geometry().height()); /// fixing size of the form
    
    /// configuring pushButton
    _ui->pushButton->setText("Send All Information");
    
    /// configuring label_selectColumn (for selecting height/weight pushButtons)
    _ui->label_selectColumn->hide();

    /// configring combo-box
    _ui->comboBox_selectColumn->hide();

    /// connecting signals and slots
    QObject::connect(_ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_gettingInputInformation()));
    QObject::connect(_ui->comboBox_selectColumn, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_comboBoxTextChange(QString)));
    QObject::connect(_ui->lineEdit_filePath, SIGNAL(textChanged(QString)), this, SLOT(slot_lineEditTextChanged(QString)));
    QObject::connect(_ui->lineEdit_numberOfColumns, SIGNAL(textChanged(QString)), this, SLOT(slot_lineEditTextChanged(QString)));
}

bool Arad::MainWindow::onlyHasNumbers(QString const& input)
{
    for (auto const& ch : input)
        if (!ch.isDigit())
            return false;

    return true;
}

void Arad::MainWindow::setRange(QString const& range)
{
    if (Arad::MainWindow::onlyHasNumbers(range))
        this->_range = (range.toInt() >= 1) ? range.toInt() : throw std::invalid_argument("the input range must be >= 1");
    else
        throw std::invalid_argument("the range must only contains numbers");
}

uint32_t Arad::MainWindow::getRange() const
{ return this->_range; }

void Arad::MainWindow::setNumberOfColumns(QString const& number)
{
    if (Arad::MainWindow::onlyHasNumbers(number))
        this->_numberOfColumns = (number.toInt() >= 1) ? number.toInt() : throw std::invalid_argument("number of columns must be >= 1");
    else
        throw std::invalid_argument("the range must only cotains numbers");
}

uint32_t Arad::MainWindow::getNumberOfColumns() const
{ return this->_numberOfColumns; }

void Arad::MainWindow::setPath(QString const& inputPath)
{
    /// validating input path
    /// validate_1
    if (inputPath.size() == 0)
        throw std::invalid_argument("you forgot to fill in the \"file path\" section");

    /// validate_2
    std::ifstream file(inputPath.toStdString(), std::ios::in);
    if (!file.is_open())
        throw std::runtime_error("couldn't open the file");

    this->_csvFilePath = inputPath;

    file.close();
}

QString const& Arad::MainWindow::getPath() const
{ return this->_csvFilePath; }

QString const& Arad::MainWindow::getDelimiter() const
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

QVector<uint32_t> const& Arad::MainWindow::getSpamLines() const
{ return this->_spamLines; }

Arad::TableDrawing::TableWidget* Arad::MainWindow::createTableDrawer(QString const& type, Arad::Scoping::ScopingCls* scoper) const
{
    Arad::TableDrawing::TableWidget* tableDrawer = nullptr;
    
    QString loweredType = type.toLower();
    if (loweredType == "height")
        tableDrawer = new Arad::TableDrawing::HeightTableWidget(scoper);
    else if (loweredType == "weight")
        tableDrawer = new Arad::TableDrawing::WeightTableWidget(scoper);
    
    return tableDrawer;
}

void Arad::MainWindow::slot_gettingInputInformation()
{
    QMessageBox mesgBx;

    try
    {
        Arad::MainWindow::setPath(_ui->lineEdit_filePath->text());
        Arad::MainWindow::setNumberOfColumns(_ui->lineEdit_numberOfColumns->text());

        _ui->pushButton->setText("Data Entered");
        _ui->pushButton->setEnabled(false); /// disabling the pushButton (after getting user input information)

        /// showing label_selectColumn
        _ui->label_selectColumn->show();

        /// showing comboBox_selectColumn
        _ui->comboBox_selectColumn->show();
    }
    catch(std::invalid_argument const& ex)
    {
        mesgBx.setText(ex.what());
        mesgBx.exec();
    }
    catch(std::runtime_error const& ex)
    {
        mesgBx.setText(ex.what());
        mesgBx.exec();
    }
    catch(...)
    {
        mesgBx.setText("something went wrong!");
        mesgBx.exec();
    }
}

void Arad::MainWindow::slot_comboBoxTextChange(QString const& str)
{    
    ////////////////// FOR HEIGHT //////////////////
    this->_scoper = new Arad::Scoping::ScopingCls(
                Arad::MainWindow::getPath(),
                Arad::MainWindow::getDelimiter(),
                Arad::MainWindow::getSpamLines(),
                Arad::MainWindow::getHeightColumn(),
                Arad::MainWindow::getRange()
    );

    this->_tableDrawing = Arad::MainWindow::createTableDrawer("height", this->_scoper);
    this->_tableDrawing->draw();

    this->_diagram = new Arad::DiagramDrawing::HistogramDiagram(this->_scoper);
    this->_diagram->drawDiagram();
    this->_diagram->show();
    /////////////////////////////////////////////////
        
    ///////////////// FOR WEIGHT ////////////////////
    this->_scoper = new Arad::Scoping::ScopingCls(
                Arad::MainWindow::getPath(),
                Arad::MainWindow::getDelimiter(),
                Arad::MainWindow::getSpamLines(),
                Arad::MainWindow::getWeightColumn(),
                Arad::MainWindow::getRange()
    );

    this->_tableDrawing = Arad::MainWindow::createTableDrawer("weight", this->_scoper);
    this->_tableDrawing->draw();

    this->_diagram = new Arad::DiagramDrawing::HistogramDiagram(this->_scoper);
    this->_diagram->drawDiagram();
    this->_diagram->show();
    //////////////////////////////////////////////////
}

void Arad::MainWindow::slot_lineEditTextChanged(QString const& newTxt)
{
    _ui->pushButton->setText("Send All Information");
    _ui->pushButton->setEnabled(true); /// enabling the pushButton (after getting user input information)
}

Arad::MainWindow::~MainWindow()
{
    delete _ui;
    delete this->_scoper;
    delete this->_tableDrawing;
}
