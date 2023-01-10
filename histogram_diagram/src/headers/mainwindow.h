#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// ========== My Headers ============ //
#include <../include/qcustomplot.h>

// =========== C++ Libraries =========== //
#include <vector>

// ======== Qt Libraries ========== //
#include <QMainWindow>

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
        ~MainWindow();
        
        std::vector<float> csvContents;
    private:
        Ui::MainWindow *ui;
    };
    
} // Arad namespace


#endif // MAINWINDOW_H
