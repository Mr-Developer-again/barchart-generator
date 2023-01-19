#ifndef ARAD_DIAGRAMDRAWING_HISTOGRAMDIAGRAM_HISTOGRAMDIAGRAM_H
#define ARAD_DIAGRAMDRAWING_HISTOGRAMDIAGRAM_HISTOGRAMDIAGRAM_H

#include <headers/diagram.h>
#include <headers/scoping.h>

#include <QWidget>

namespace Arad
{

    namespace DiagramDrawing
    {
    
        class HistogramDiagram : public Arad::DiagramDrawing::Diagram
        {
        public:
            explicit HistogramDiagram(Arad::Scoping::ScopingCls *scoper, QWidget* parent = nullptr);

            void drawDiagram() override;
            
        private:
            Arad::Scoping::ScopingCls *_scoper = nullptr;
        };
    
    } // DiagramDrawing namespace

} // Arad namespace

#endif // ARAD_DIAGRAMDRAWING_HISTOGRAMDIAGRAM_HISTOGRAMDIAGRAM_H
