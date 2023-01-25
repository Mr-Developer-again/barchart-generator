#include <headers/diagram.h>
#include <ui_diagram.h>

Arad::DiagramDrawing::Diagram::Diagram(QCustomPlot *ui)
    : _ui(ui)
{ /* constructor body */ }

Arad::DiagramDrawing::Diagram::~Diagram()
{
    delete _ui;
}

