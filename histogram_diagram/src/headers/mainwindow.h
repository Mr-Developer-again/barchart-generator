#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <../include/qcustomplot.h>

#include <vector>

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Arad
{

    class MainWindow : public QMainWindow
    {

        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        virtual ~MainWindow();

        /// sets range of scopes in histogram diagram
        void setRange(uint32_t);
        
        /// gets range of scopes in historgram diagram
        uint32_t getRange() const;
        
        /// sets user input path
        void setPath(QString const&);
        
        /// gets user input path
        QString getPath() const;
        
        /// sets user input delimiter
        void setDelimiter(QString const&);
        
        /// gets user input delimiter
        QString getDelimiter() const;
        
    private:
        Ui::MainWindow *ui;

        /// range of scopes in histogram diagram
        uint32_t _range = 0;
        
        /// CSV file path
        QString _csvFilePath = "";
        
        /// delimiter between CSV line contents
        QString _csvContentsDelimiter = "";
        
    private slots:
        /// this slot fill some variables with input lines (in lineEdit sections)
        void slotGettingInputInformation();
    };
    
} // Arad namespace


#endif // MAINWINDOW_H
