#include <headers/histogramdiagram.h>
#include <ui_diagram.h>

#include <headers/diagram.h>
#include <sources/diagram.cpp>

#include <QMap>
#include <QVector>

Arad::DiagramDrawing::HistogramDiagram::HistogramDiagram(Arad::Scoping::ScopingCls *scoper, QWidget* parent)
    : Arad::DiagramDrawing::Diagram(parent),
      _scoper(scoper)
{ /* constructor body */ }

void Arad::DiagramDrawing::HistogramDiagram::drawDiagram()
{
    QMap<double, QString> tempMap = this->_scoper->getMap();
    QVector<QVector<float>> tempVector = this->_scoper->getRangedVector();

    QSharedPointer<QCPAxisTickerText> qcpTextPtr(new QCPAxisTickerText);
    this->_ui->widget->xAxis->setTicker(qcpTextPtr);
    qcpTextPtr->setTicks(tempMap);
    
    this->_ui->widget->addGraph();
}