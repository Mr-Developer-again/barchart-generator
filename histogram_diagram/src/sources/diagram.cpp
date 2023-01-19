#include <headers/diagram.h>
#include <ui_diagram.h>

Arad::DiagramDrawing::Diagram::Diagram(QWidget *parent)
    : QDialog(parent),
      _ui(new Ui::Diagram)
{
    _ui->setupUi(this);
}

Arad::DiagramDrawing::Diagram::~Diagram()
{
    delete _ui;
}
