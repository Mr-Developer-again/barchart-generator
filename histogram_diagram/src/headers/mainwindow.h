#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <../include/qcustomplot.h>
#include <headers/csvparser.h>
#include <headers/scoping.h>
#include <headers/tablewidget.h>
#include <headers/diagram.h>

#include <vector>

#include <QMainWindow>
#include <QTextStream>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Arad
{

    class MainWindow : public QMainWindow
    {

        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        MainWindow() = default;
        virtual ~MainWindow();

        /// sets range of scopes in histogram diagram
        void setRange(QString const&);
        
        /// gets range of scopes in historgram diagram
        uint32_t getRange() const;
        
        /// sets user input path
        void setPath(QString const&);
        
        /// gets user input path
        QString const& getPath() const;
        
        /// sets user input delimiter
        void setDelimiter(QString const&);
        
        /// gets user input delimiter
        QString const& getDelimiter() const;
        
        /// sets user input height column
        void setHeightColumn(QString const&);
        
        /// gets user input height column
        uint32_t getHeightColumn() const;
        
        /// sets user input weight column
        void setWeightColumn(QString const&);
        
        /// gets user input weight column
        uint32_t getWeightColumn() const;
        
        /// sets user input spam lines
        void setSpamLines(QString const&);
        
        /// gets user input spam lines
        QVector<uint32_t> const& getSpamLines() const;
        
    private:
        Ui::MainWindow *_ui;

        /// range of scopes in histogram diagram
        uint32_t _range = 0;
        
        /// CSV file path
        QString _csvFilePath = "";
        
        /// delimiter between CSV line contents
        QString _csvContentsDelimiter = "";
        
        /// column number of height information
        uint32_t _heightColumn = 0;

        /// column number of weight information
        uint32_t _weightColumn = 0;
        
        /// spam lines string
        QVector<uint32_t> _spamLines;
        
        /// defining an object for Arad::CsvParser::ScopingCls class
        Arad::CsvParser::CsvParserCls *_csvParser = nullptr;

        /// defining an object for Arad::Scoping::ScopingCls class
        Arad::Scoping::ScopingCls *_scoper = nullptr;

        /// defining an polymorphic object pointer
        Arad::TableDrawing::TableWidget *_tableDrawing = nullptr;
        
        /// creating a method for controling creating object
        Arad::TableDrawing::TableWidget* createTableDrawer(QString const& type, Arad::Scoping::ScopingCls* scoper) const;
        
        /// creating an polymorphic object pointer for Arad::DiagramDrawing::Diagram
        Arad::DiagramDrawing::Diagram *_diagram = nullptr;
        
    private slots:
        /// this slot fill some variables with input lines (in lineEdit sections)
        void slot_gettingInputInformation();
        
        /// this slot is used for responding to clicking _ui->pushButton_height and _ui->pushButton_weight
        void slot_comboBoxIndexChange();
    };

} // Arad namespace


#endif // MAINWINDOW_H
