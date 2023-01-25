#ifndef ARAD_DIAGRAMDRAWING_DIAGRAM_DIAGRAM_H
#define ARAD_DIAGRAMDRAWING_DIAGRAM_DIAGRAM_H

#include <headers/scoping.h>

#include <../include/qcustomplot.h>

namespace Ui
{
    class Diagram;
} // Ui namespace

namespace Arad
{

    namespace DiagramDrawing
    {

        class Diagram
        {
            
        public:
            explicit Diagram(QCustomPlot *parent = nullptr);
            virtual ~Diagram();

            virtual void drawDiagram() = 0;

            QCustomPlot *_ui = nullptr;
        protected:
        };
        
    } // DiagramDrawing namespace

} // Arad namespace

#endif // ARAD_DIAGRAMDRAWING_DIAGRAM_DIAGRAM_H
