#include <headers/mainwindow.h>
#include <ui_mainwindow.h>
#include <headers/scoping.h>
#include <headers/heightweighttablewidget.h>
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

void Arad::MainWindow::setComboBoxItems(QList<QString> const& list)
{
    this->_comboBoxItems = (list.size() != 0) ? list : throw std::runtime_error("size of comboBox items is 0 (invalid)");
}

QList<QString> const& Arad::MainWindow::getComboBoxItems() const
{ return this->_comboBoxItems; }

template<typename itemType>
int32_t Arad::MainWindow::indexFinder(QList<itemType> const& container, itemType item)
{
    uint32_t indexCounter = 0;
    for (typename QList<itemType>::ConstIterator it = container.begin(); it != container.end(); std::advance(it, 1), indexCounter++)
        if (*it == item)
            return indexCounter;

    return -1;
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

        this->_csvParser = new Arad::CsvParser::CsvParserCls(this->_csvFilePath);

        Arad::MainWindow::setComboBoxItems(this->_csvParser->getColumnNames());

        /// removing items of the comboBox
        _ui->comboBox_selectColumn->clear();

        /// adding items to the _ui->comboBox_selectColumn
        _ui->comboBox_selectColumn->addItems(this->_comboBoxItems);
    }
    catch(std::invalid_argument const& ex)
    {
        mesgBx.setWindowTitle("Invalid Argument Error");
        mesgBx.setText(ex.what());
        mesgBx.exec();
    }
    catch(std::runtime_error const& ex)
    {
        mesgBx.setWindowTitle("Runtime Error");
        mesgBx.setText(ex.what());
        mesgBx.exec();
    }
    catch(std::out_of_range const& ex)
    {
        mesgBx.setWindowTitle("Out Of Range Error");
        mesgBx.setText(ex.what());
        mesgBx.exec();
    }
    catch(...)
    {
        mesgBx.setWindowTitle("Error!!");
        mesgBx.setText("something went wrong!");
        mesgBx.exec();
    }
}

void Arad::MainWindow::slot_comboBoxTextChange(QString const& str)
{
    QMessageBox mesgBx;

    int32_t indexNumber = Arad::MainWindow::indexFinder<QString>(this->_comboBoxItems, str);

    if (indexNumber >= 1)
    {
        try
        {
            this->_scoper = new Arad::Scoping::ScopingCls(
                        this->_csvFilePath,
                        (indexNumber + 1),
                        this->_numberOfColumns
            );

            this->_diagram = new Arad::DiagramDrawing::HistogramDiagram(this->_scoper);
            this->_diagram->drawDiagram();
            this->_diagram->show();

            this->_tableDrawing = new Arad::TableDrawing::HeightWeightTableWidget(this->_scoper);
            this->_tableDrawing = new Arad::TableDrawing::HeightWeightTableWidget(this->_scoper);
            this->_tableDrawing->draw();
        }
        catch(std::invalid_argument const& ex)
        {
            mesgBx.setWindowTitle("Invalid Argument Error");
            mesgBx.setText(ex.what());
            mesgBx.exec();
        }
        catch(std::runtime_error const& ex)
        {
            mesgBx.setWindowTitle("Runtime Error");
            mesgBx.setText(ex.what());
            mesgBx.exec();
        }
        catch(std::out_of_range const& ex)
        {
            mesgBx.setWindowTitle("Out Of Range Error");
            mesgBx.setText(ex.what());
            mesgBx.exec();
        }
        catch(...)
        {
            mesgBx.setWindowTitle("Error!!");
            mesgBx.setText("something went wrong!");
            mesgBx.exec();
        }

    }
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
    delete this->_csvParser;
    delete this->_diagram;
}
