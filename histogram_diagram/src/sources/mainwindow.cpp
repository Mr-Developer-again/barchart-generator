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

#include <QFont>

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
    QObject::connect(_ui->pushButton, SIGNAL(clicked()), this, SLOT(slotGettingInputInformation()));
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

QString const& Arad::MainWindow::getPath() const
{ return this->_csvFilePath; }

void Arad::MainWindow::setDelimiter(QString const& delimiter)
{
    this->_csvContentsDelimiter = (delimiter.size() > 0) ? delimiter : throw std::invalid_argument("you forgot to fill in the \"delimiter\" section");
}

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

void Arad::MainWindow::setSpamLines(QString const& spamLines)
{
    if (spamLines.size() != 0)
    {
        std::vector<std::string> seperatedSpamLines = this->_csvParser->split(spamLines.toStdString());

        /// converting seperatedSpamLines item to uint32_t
        for (std::string const& item : seperatedSpamLines)
            this->_spamLines.push_back(std::stoi(item));
    }
    else
        this->_spamLines.push_back(0);
    
    this->_spamLines.shrink_to_fit();
}

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
    Arad::MainWindow::setPath(_ui->lineEdit_filePath->text());
    _ui->lineEdit_filePath->setEnabled(false);

    QFont pushButtonFont("Consolas", -1, 50, true);
    _ui->pushButton->setFont(pushButtonFont);
    _ui->pushButton->setText("Data Entered");
    _ui->pushButton->setEnabled(false); /// disabling the pushButton (after getting user input information) 

    /// showing label_selectColumn
    _ui->label_selectColumn->show();

    /// showing comboBox_selectColumn
    _ui->comboBox_selectColumn->show();
}

void Arad::MainWindow::slot_comboBoxIndexChange()
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
    ///////////////////////////////////////////////
        
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

Arad::MainWindow::~MainWindow()
{
    delete _ui;
    delete this->_scoper;
    delete this->_tableDrawing;
}
