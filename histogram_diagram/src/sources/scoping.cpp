#include <headers/scoping.h>

Arad::Scoping::ScopingCls::ScopingCls(QString const& filePath, uint32_t columnNumber, uint32_t numberOfColumns,
                                                            QString const& delimiter, QVector<uint32_t> const& spamLines)
    : _csvParser(new Arad::CsvParser::CsvParserCls(filePath, delimiter, spamLines))
{
    QVector<double> container = this->_csvParser->extracter(columnNumber);
    this->_minData = container[0];
    this->_maxData = container[container.size() - 1] + 1;
    this->_numberOfColumns = numberOfColumns;
    this->_range = Arad::Scoping::ScopingCls::calculateRange();
    Arad::Scoping::ScopingCls::doScoping(numberOfColumns);
}

void Arad::Scoping::ScopingCls::doScoping(uint32_t columnNumber)
{
    QVector<QVector<double>> result;
    QVector<double> tempVector = this->_csvParser->extracter(columnNumber);
    QList<QString> ranges; /// this list stores ranges of each column (data scope) in a human-readable format

    double startRange = this->_minData;
    double stopRange = startRange + this->_range;


    QString startRangeStr = "";
    QString stopRangeStr = "";
    bool isEnd = false;
    for (uint32_t  i = 0; i < this->_numberOfColumns; ++i)
    {
        for (auto const& number : tempVector)
        {
            if (i == (this->_numberOfColumns - 1))
            {
                if (number >= startRange and number <= stopRange)
                    tempVector.push_back(number);

                isEnd = true;
            }
            else
            {
                if (number >= startRange and number < stopRange)
                {
                    tempVector.push_back(number);
                    startRangeStr = startRangeStr.setNum(startRange);
                    stopRangeStr = stopRangeStr.setNum(stopRange);
                }
            }
        }

        startRangeStr = startRangeStr.setNum(startRange);
        stopRangeStr = stopRangeStr.setNum(stopRange);
        if (isEnd)
            ranges.push_back("[" + startRangeStr + ", " + stopRangeStr + "]");
        else
            ranges.push_back("[" + startRangeStr + ", " + stopRangeStr + ")");

        tempVector.shrink_to_fit();
        result.push_back(tempVector);
        result.shrink_to_fit();
        tempVector.clear();

        startRange = stopRange;
        stopRange += this->_range;
    }

    this->_rangedVector = result;
    Arad::Scoping::ScopingCls::setLabelList(ranges);
}

double Arad::Scoping::ScopingCls::calculateRange()
{
    return ((this->_maxData - this->_minData) / this->_numberOfColumns);
}

double Arad::Scoping::ScopingCls::getRange() const
{ return this->_range; }

void Arad::Scoping::ScopingCls::setLabelList(QList<QString> const& labelList)
{
    this->_labelList = labelList;
}

QList<QString> const& Arad::Scoping::ScopingCls::getLabelList() const
{ return this->_labelList; }

QVector<QVector<double>> const& Arad::Scoping::ScopingCls::getRangedVector() const
{ return this->_rangedVector; }
