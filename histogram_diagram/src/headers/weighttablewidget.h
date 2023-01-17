#ifndef ARAD_TABLEDRAWING_WEIGHTTABLEWIDGET_WEIGHTTABLEWIDGET_H
#define ARAD_TABLEDRAWING_WEIGHTTABLEWIDGET_WEIGHTTABLEWIDGET_H

#include <headers/scoping.h>
#include <headers/tablewidget.h>

#include <QWidget>

namespace Arad
{

    namespace TableDrawing
    {
    
        class WeightTableWidget : public Arad::TableDrawing::TableWidget
        {
        public:
            explicit WeightTableWidget(Arad::Scoping::ScopingCls *scopingObj, QWidget* parent = nullptr);
            WeightTableWidget() = delete;
            virtual ~WeightTableWidget() = default;
        };
    
    } // TableDrawing namespace

} // Arad namespace

#endif // ARAD_TABLEDRAWING_WEIGHTTABLEWIDGET_WEIGHTTABLEWIDGET_H
