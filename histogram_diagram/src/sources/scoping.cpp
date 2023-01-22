#include <headers/scoping.h>

Arad::Scoping::ScopingCls::ScopingCls(QString const& filePath, QString const& delimiter,
                                      QVector<uint32_t> const& spamLines, int columnNumber, uint32_t range)
{
    this->_csvParser = new Arad::CsvParser::CsvParserCls(filePath);

    /// this vector stores the returned vector by Arad::CsvParser::extracter
    QVector<float> container = this->_csvParser->extracter(columnNumber);
    int startData = static_cast<int>(container[0]);
    int stopData = static_cast<int>(container[container.size() - 1]) + 1;
    int startRange = startData;
    int stopRange = startRange + range;
    QVector<float> temporaryVector;
    QList<QString> tempList;
    
    QString startRangeStr = "";
    QString stopRangeStr = "";
    
    for (uint32_t i = 0; startRange < stopData; ++i)
    {
        for (float const& item : container)
        {
            if ((item >= startRange) and (item <= stopRange))
                temporaryVector.push_back(item);
        }
        
        temporaryVector.shrink_to_fit();
        this->_rangedVector.push_back(temporaryVector);
        temporaryVector.clear();

        startRangeStr = startRangeStr.setNum(startRange);
        stopRangeStr = stopRangeStr.setNum(stopRange);
        tempList.push_back("[" + startRangeStr + ", " + stopRangeStr + "]");
        startRange = stopRange + 1;
        stopRange = startRange + range;
    }
    
    Arad::Scoping::ScopingCls::setLabelList(tempList);
    this->_rangedVector.shrink_to_fit();
}

void Arad::Scoping::ScopingCls::setLabelList(QList<QString> const& labelList)
{
    this->_labelList = labelList;
}

QList<QString> const& Arad::Scoping::ScopingCls::getLabelList() const
{ return this->_labelList; }

QVector<QVector<float>> const& Arad::Scoping::ScopingCls::getRangedVector() const
{ return this->_rangedVector; }
