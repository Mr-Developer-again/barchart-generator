#ifndef ARAD_CSVPARSER_CSVPARSER_H
#define ARAD_CSVPARSER_CSVPARSER_H

#include <vector>
#include <string>
#include <QTextStream>
#include <QVector>

namespace Arad
{

    namespace CsvParser
    {

        class CsvParserCls
        {
        public:
            CsvParserCls(QString const& filePath, QString const& delimiter = " ,",
                         QVector<uint32_t> spamLines = QVector<uint32_t>(1));

            CsvParserCls() = delete;


            /// this function gets all contents of a column
            ///     in arguments:
            ///         delimiter -> delimiter between line contents in the given file
            ///         spamLines -> the lines that aren't information to extract and have been written
            ///                      only for human-readablity reasons
            ///         columnNumber -> do you want to extract contents of which column? (a number from 0)
            QVector<float> extracter(int columnNumber);

            /// spliter ; this function gets a string and split it with some specified delimiter
            std::vector<std::string> split(std::string const& string);

            /// this function checks whether the given item exists inside the container(vector) or not
            template<typename T>
            bool in(T const& item, QVector<T> const& container);

            /// this function parse first line of the csv file and
            /// extract column names (from the line) and finally
            /// returns the column names in a QList<QString>
            QList<QString> getColumnNames();

        protected:
            void setFilePath(QString const& filePath);
            QString getFilePath() const;

            void setDelimiter(QString const& delimiter);
            QString getDelimiter() const;

            void setSpamLines(QVector<uint32_t> const& spamLines);
            QVector<uint32_t> getSpamLines() const;

        private:
            std::string doubleQuoteRemover(std::string const& str);

            QString _filePath = "";
            QString _delimiter;
            QVector<uint32_t> _spamLines;

        };

    } // CscParser namespace

} // Arad namespace


#endif  // ARAD_CSVPARSER_CSVPARSER_H
