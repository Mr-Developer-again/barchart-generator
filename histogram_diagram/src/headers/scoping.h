#ifndef ARAD_SCOPING_SCOPINGCLS_SCOPING_H
#define ARAD_SCOPING_SCOPINGCLS_SCOPING_H

#include <QTextStream>
#include <QVector>
#include <QMap>

namespace Arad
{

    namespace Scoping
    {

        class ScopingCls
        {
        public:
            ScopingCls(QString const& filePath, QString const& delimiter, QVector<uint32_t> const& spamLines,
                    int columnNumber, uint32_t range /* range of scopes in histogram diagram */ );
            
            ScopingCls() = delete;
            virtual ~ScopingCls() = default;

            QVector<QVector<float>> const& getRangedVector() const;
            QMap<uint32_t, QString> const& getMap() const;
//            QList<QString> const& getLabelList() const;
    
        private:        
            /// the following nested vector will store ranged information
            QVector<QVector<float>> _rangedVector;
            
            
            /// the following map stores index number of the _rangedVector
            /// and the related text to it 
            /// (e.g. index: 1, related text: 64-73 (this text shows the range))
            QMap<uint32_t, QString> _mapper;
            
            /// this variable stores 
//            QList<QString> _labelList;
        };
    
    } // Scoping namespace

} // Arad namespace

#endif  // ARAD_SCOPING_SCOPINGCLS_SCOPING_H