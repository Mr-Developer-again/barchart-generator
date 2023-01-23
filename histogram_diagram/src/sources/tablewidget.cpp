#include <headers/tablewidget.h>

Arad::TableDrawing::TableWidget::TableWidget(Arad::Scoping::ScopingCls *scopingObj, QWidget* parent)
    : QDialog(parent),
      _tableWidget(new QTableWidget(parent)),
      _scopingObj(scopingObj)
{ /* constructor body */ }

void Arad::TableDrawing::TableWidget::setRowLabels(QList<QString> const& rowLabels)
{ this->_rowLabels = rowLabels; }

QList<QString> const& Arad::TableDrawing::TableWidget::getRowLabels() const
{ return this->_rowLabels; }

void Arad::TableDrawing::TableWidget::setColumnLabels(QList<QString> const& columnLabels)
{ this->_columnLabels = columnLabels; }

QList<QString> const& Arad::TableDrawing::TableWidget::getColumnLabels() const
{ return this->_columnLabels; }

void Arad::TableDrawing::TableWidget::draw()
{    
    QVector<QVector<double>> tempRangedVector = this->_scopingObj->getRangedVector();
    Arad::TableDrawing::TableWidget::setRowLabels(this->_scopingObj->getLabelList());
    Arad::TableDrawing::TableWidget::setColumnLabels(QList<QString>({"Count"}));
    
    uint32_t const numberOfRows = tempRangedVector.size();
    uint32_t const numberOfColumns = 1;
    
    this->_tableWidget->setRowCount(numberOfRows);
    this->_tableWidget->setColumnCount(numberOfColumns);
    this->_tableWidget->setVerticalHeaderLabels(Arad::TableDrawing::TableWidget::getRowLabels());
    this->_tableWidget->setHorizontalHeaderLabels(Arad::TableDrawing::TableWidget::getColumnLabels());
    
    QString tempStr = "";
    for (uint32_t i = 0; i < numberOfRows; ++i)
    {
        tempStr = tempStr.setNum(tempRangedVector[i].size());
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(tempStr);
        this->_tableWidget->setItem(i, 0, item);
    }
    
    this->_tableWidget->show();
}

Arad::TableDrawing::TableWidget::~TableWidget()
{
    delete this->_tableWidget;
    delete this->_scopingObj;
}
