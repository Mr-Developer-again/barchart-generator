#ifndef ARAD_DIAGRAMDRAWING_HISTOGRAMDIAGRAM_HISTOGRAMDIAGRAM_H
#define ARAD_DIAGRAMDRAWING_HISTOGRAMDIAGRAM_HISTOGRAMDIAGRAM_H

#include <headers/diagram.h>

#include <QWidget>

namespace Arad
{

    namespace DiagramDrawing
    {
    
        class HistogramDiagram : public Arad::DiagramDrawing::Diagram
        {
        public:
            explicit HistogramDiagram(QWidget* parent = nullptr);

            void drawDiagram() override;
        };
    
    } // DiagramDrawing namespace

} // Arad namespace

#endif // ARAD_DIAGRAMDRAWING_HISTOGRAMDIAGRAM_HISTOGRAMDIAGRAM_H
