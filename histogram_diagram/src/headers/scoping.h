#ifndef ARAD_SCOPING_SCOPINGCLS_SCOPING_H
#define ARAD_SCOPING_SCOPINGCLS_SCOPING_H

#include <headers/csvparser.h>

#include <QTextStream>
#include <QVector>
#include <QList>

namespace Arad
{

    namespace Scoping
    {

        class ScopingCls
        {
        public:
            ScopingCls(QString const& filePath, uint32_t columnNumber, uint32_t numberOfColumns,
                       QString const& delimiter = ", ", QVector<uint32_t> const& spamLines = { 1 });

            ScopingCls() = delete;
            virtual ~ScopingCls() = default;

            QVector<QVector<double>> const& getRangedVector() const;

            void setLabelList(QList<QString> const& labelList);
            QList<QString> const& getLabelList() const;

            double getRange() const;

        private:
            /// this method does scoping operation (this is called by constructor)
            void doScoping(uint32_t columnNumber);

            /// this method calculate range (according to the input numberOfColumns)
            double calculateRange();

            /// maximum/minimum data from the extracted column
            double _maxData, _minData;

            uint32_t _numberOfColumns = 0;

            /// the distance between columns (scopes of information)
            double _range;

            /// the following nested vector will store ranged information
            QVector<QVector<double>> _rangedVector;

            /// this variable list stores range string (like _mapper but only stores
            /// range string and doesn't stores any index for the range string)
            QList<QString> _labelList;

            Arad::CsvParser::CsvParserCls *_csvParser = nullptr;
        };
    
    } // Scoping namespace

} // Arad namespace

#endif  // ARAD_SCOPING_SCOPINGCLS_SCOPING_H
