#ifndef ARAD_DIAGRAMDRAWING_DIAGRAM_DIAGRAM_H
#define ARAD_DIAGRAMDRAWING_DIAGRAM_DIAGRAM_H

#include <../include/qcustomplot.h>

#include <QDialog>

namespace Ui
{
    class Diagram;
} // Ui namespace

namespace Arad
{

    namespace DiagramDrawing
    {

        class Diagram : public QDialog
        {
            Q_OBJECT
            
        public:
            explicit Diagram(QWidget *parent = nullptr);
            virtual ~Diagram();
            
            virtual void drawDiagram() = 0;
            
        protected:
            Ui::Diagram *_ui;
        };
        
    } // DiagramDrawing namespace

} // Arad namespace

#endif // ARAD_DIAGRAMDRAWING_DIAGRAM_DIAGRAM_H
