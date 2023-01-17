#ifndef ARAD_HEIGHTTABLEWIDGET_HEIGHTTABLEWIDGET_H
#define ARAD_HEIGHTTABLEWIDGET_HEIGHTTABLEWIDGET_H

#include <headers/tablewidget.h>
#include <headers/scoping.h>

#include <QDialog>
#include <QTableWidget>
#include <QWidget>

namespace Arad
{

    namespace TableDrawing
    {

        class HeightTableWidget : public Arad::TableDrawing::TableWidget
        {
        public:
            explicit HeightTableWidget(Arad::Scoping::ScopingCls *scopingObj, QWidget* parent = nullptr);
            HeightTableWidget() = delete;
            virtual ~HeightTableWidget() = default;
        };
        
    } // TableDrawing namespace

} // Arad namespace

#endif // ARAD_HEIGHTTABLEWIDGET_HEIGHTTABLEWIDGET_H
