#ifndef ARAD_CSVPARSER_CSVPARSER_H
#define ARAD_CSVPARSER_CSVPARSER_H

#include <vector>

#include <QTextStream>
#include <QVector>

namespace Arad
{

    namespace csvParser
    {
    
        /// spliter ; this function gets a string and split it with some specified delimiter
        std::vector<std::string> split(std::string const& the_string, std::string const& the_delimiter);
    
        /// this function gets all contents of a column 
        ///     in arguments:
        ///         delimiter -> delimiter between line contents in the given file
        ///         spamLines -> the lines that aren't information to extract and have been written
        ///                      only for human-readablity reasons
        ///         columnNumber -> do you want to extract contents of which column? (a number from 0)
        QVector<float> Extracter(QString const& filePath, QString const& delimiter,
                                                            QVector<uint32_t> const& spamLines, int columnNumber);
        
        /// this function checks whether the given item exists inside the container(vector) or not
        template<typename T>
        bool in(T const& item, QVector<T> const& container);

    } // csvParser namespace

} // Arad namespace


#endif  // ARAD_CSVPARSER_CSVPARSER_H