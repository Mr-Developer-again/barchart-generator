#include <headers/scoping.h>

#include <headers/csvparser.h>

Arad::Scoping::ScopingCls::ScopingCls(QString const& filePath, QString const& delimiter,
                                      QVector<uint32_t> const& spamLines, int columnNumber, uint32_t range)
{ 
    /// this vector stores the returned vector by Arad::CsvParser::extracter
    QVector<float> container = Arad::CsvParser::extracter(filePath, delimiter, spamLines, columnNumber);
    int startData = static_cast<int>(container[0]);
    int stopData = static_cast<int>(container[container.size() - 1]) + 1;
    int startRange = startData;
    int stopRange = startRange + range;
    QVector<float> temporaryVector;
    
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
        
        this->_mapper.insert(i, static_cast<QString>(startRange) + "-" + static_cast<QString>(stopRange));
        startRange = stopRange + 1; stopRange = startRange + range; 
    }
    
    this->_rangedVector.shrink_to_fit();
}

QVector<QVector<float>> const& Arad::Scoping::ScopingCls::getRangedVector() const
{ return this->_rangedVector; }

QMap<uint32_t, QString> const& Arad::Scoping::ScopingCls::getMap() const
{ return this->_mapper; }
