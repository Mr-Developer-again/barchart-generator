#ifndef ARAD_TRABLEDRAWING_HEIGHTWEIGHTTABLEWIDGET_HEIGHTWEIGHTTABLEWIDGET_H
#define ARAD_TRABLEDRAWING_HEIGHTWEIGHTTABLEWIDGET_HEIGHTWEIGHTTABLEWIDGET_H

#include <headers/tablewidget.h>

namespace Arad
{

    namespace TableDrawing
    {

        class HeightWeightTableWidget : public Arad::TableDrawing::TableWidget
        {
        public:
            explicit HeightWeightTableWidget(Arad::Scoping::ScopingCls *scopingObj, QWidget* parent = nullptr);
            HeightWeightTableWidget() = delete;
            virtual ~HeightWeightTableWidget() = default;
        };

    } // TableDrawing namespace

} // Arad namespace

#endif // ARAD_TRABLEDRAWING_HEIGHTWEIGHTTABLEWIDGET_HEIGHTWEIGHTTABLEWIDGET_H
