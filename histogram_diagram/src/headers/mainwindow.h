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
#include <QList>

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

        void setNumberOfColumns(QString const&);
        uint32_t getNumberOfColumns() const;
        
        /// sets user input path
        void setPath(QString const&);
        
        /// gets user input path
        QString const& getPath() const;
        
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
        
        /// gets user input spam lines
        QVector<uint32_t> const& getSpamLines() const;

        /// set comboBox items
        void setComboBoxItems(QList<QString> const&);

        /// get comboBox items
        QList<QString> const& getComboBoxItems() const;

    private:
        /// number of columns (user must enter)
        uint32_t _numberOfColumns = 0;

        /// CSV file path
        QString _csvFilePath = "";

        /// delimiter between CSV line contents
        QString const _csvContentsDelimiter = ", ";

        /// column number of height information
        uint32_t _heightColumn = 0;

        /// column number of weight information
        uint32_t _weightColumn = 0;

        /// spam lines string
        QVector<uint32_t> const _spamLines { 1 };

        /// comboBox items
        QList<QString> _comboBoxItems;
        
        /// pointer to ui
        Ui::MainWindow *_ui;

        /// defining an object for Arad::CsvParser::ScopingCls class
        Arad::CsvParser::CsvParserCls *_csvParser = nullptr;

        /// defining an object for Arad::Scoping::ScopingCls class
        Arad::Scoping::ScopingCls *_scoper = nullptr;

        /// defining an polymorphic object pointer
        Arad::TableDrawing::TableWidget *_tableDrawing = nullptr;
        
        /// creating an polymorphic object pointer for Arad::DiagramDrawing::Diagram
        Arad::DiagramDrawing::Diagram *_diagram = nullptr;

        /// a method for checking input (for numbers)
        /// this method checks the input QString only has numbers or not?
        bool onlyHasNumbers(QString const&);

        /// the following method finds index of an item inside the given container
        template<typename itemType>
        int32_t indexFinder(QList<itemType> const& container, itemType item);

    private slots:
        /// this slot fill some variables with input lines (in lineEdit sections)
        void slot_gettingInputInformation();

        /// this slot is used for responding to clicking _ui->pushButton_height and _ui->pushButton_weight
        void slot_comboBoxTextChange(QString const&);

        /// when text of lineEdits changed, this slot is called
        void slot_lineEditTextChanged(QString const&);

    };

} // Arad namespace


#endif // MAINWINDOW_H
