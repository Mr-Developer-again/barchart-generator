#include <headers/mainwindow.h>
#include <ui_mainwindow.h>
#include <headers/scoping.h>

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
      _ui(new Ui::MainWindow),
      _scoper(new Arad::Scoping::ScopingCls)
{
    _ui->setupUi(this);
    
    /// configuring pushButton
    _ui->pushButton->setText("Send All Information");

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

void Arad::MainWindow::setSpamLines(QString const& spamLines)
{
    if (spamLines.size() != 0)
    {
        std::vector<std::string> seperatedSpamLines = Arad::CsvParser::split(spamLines.toStdString(), SPAM_LINES_DELIMITER);

        /// converting seperatedSpamLines item to uint32_t
        for (std::string const& item : seperatedSpamLines)
            this->_spamLines.push_back(std::stoi(item));
    }
    else
        this->_spamLines.push_back(0);
    
    this->_spamLines.shrink_to_fit();
}

QVector<uint32_t> Arad::MainWindow::getSpamLines() const
{ return this->_spamLines; }

void Arad::MainWindow::slotGettingInputInformation()
{
    Arad::MainWindow::setPath(_ui->lineEdit_filePath->text());
    Arad::MainWindow::setDelimiter(_ui->lineEdit_delimiter->text());
    Arad::MainWindow::setHeightColumn(_ui->lineEdit_heightColumn->text());
    Arad::MainWindow::setWeightColumn(_ui->lineEdit_weightColumn->text());
    Arad::MainWindow::setRange(_ui->lineEdit_range->text());
    Arad::MainWindow::setSpamLines(_ui->lineEdit_spamLines->text());

    QFont pushButtonFont("Consolas", -1, 50, true);
    _ui->pushButton->setFont(pushButtonFont);
    _ui->pushButton->setText("OK");

    /// configuring this->heightWeightLabel
    this->_heightWeightLabel = new QLabel(this);
    this->_heightWeightLabel->setGeometry(300, 370, 151, 17);
    this->_heightWeightLabel->setText("Select one of these:");
    this->_heightWeightLabel->show();

    /// configuring this->_heightPushButton
    this->_heightPushButton = new QPushButton("Height", this);
    this->_heightPushButton->setGeometry(300, 400, 151, 25);
    this->_heightPushButton->show();

    /// configuraing this->_weightPushButton
    this->_weightPushButton = new QPushButton("Weight", this);
    this->_weightPushButton->setGeometry(300, 430, 151, 25);
    this->_weightPushButton->show();
}

Arad::MainWindow::~MainWindow()
{
    delete _ui;
    delete this->_heightPushButton;
    delete this->_weightPushButton;
    delete this->_heightWeightLabel;
}