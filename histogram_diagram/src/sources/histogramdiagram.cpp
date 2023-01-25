#include <headers/histogramdiagram.h>
#include <ui_diagram.h>

#include <headers/diagram.h>
#include <sources/diagram.cpp>

#include <QVector>

Arad::DiagramDrawing::HistogramDiagram::HistogramDiagram(Arad::Scoping::ScopingCls *scoper, QCustomPlot* parent)
    : Arad::DiagramDrawing::Diagram(parent),
      _scoper(scoper)
{ /* constructor body */ }

void Arad::DiagramDrawing::HistogramDiagram::drawDiagram()
{
    QVector<QString> labels;
    QVector<double> positions;
    
    /// filling labels vector by the taken list
    labels = QVector<QString>::fromList(this->_scoper->getLabelList());

    /// filling positions vector according to the number of labels vector items
    double position = 1.0f;
    for (QVector<QString>::Iterator it = labels.begin(); it != labels.end(); std::advance(it, 1), position++)
        positions.push_back(position);

    labels.shrink_to_fit();
    positions.shrink_to_fit();


    QVector<QVector<double>> tempVector;
    tempVector = this->_scoper->getRangedVector();
    QVector<double> sizeVector;
    std::for_each(tempVector.begin(), tempVector.end(), [&](QVector<double> innerVec) {
        sizeVector.push_back(static_cast<double>(innerVec.size()));
    });

    /// calculating maximum size of ranges (for setting range for diagram)
    uint32_t maxSize = 0;
    maxSize = static_cast<uint32_t>(*(std::max_element(sizeVector.begin(), sizeVector.end())));

    //////////////////// Now, working on the QCustomPlot object ///////////////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->setTicks(positions, labels);
    textTicker->setTickStepStrategy(QCPAxisTickerText::TickStepStrategy::tssReadability);
    this->_ui->xAxis->setTicker(textTicker);
    this->_ui->xAxis->setTickLabelRotation(60);
    this->_ui->xAxis->setTickLength(0, 4);

    this->_ui->xAxis->setLabel("Ranges");
    this->_ui->yAxis->setLabel("Count");

    this->_ui->yAxis->setRange(0, maxSize);

    QCPBars *bar = new QCPBars(this->_ui->xAxis, this->_ui->yAxis);
    bar->setAntialiased(false);
    bar->setBrush(QColor(0, 0, 255, 50));
    bar->setPen(QColor(0, 0, 255));
    bar->setWidth(0.9f);
    bar->setData(positions, sizeVector);

    bar->rescaleAxes(true);
    bar->rescaleKeyAxis(true);
    this->_ui->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    this->_ui->replot();
}

Arad::DiagramDrawing::HistogramDiagram::~HistogramDiagram()
{
    delete this->_scoper;
}
