#include <headers/csvparser.h>

#include <fstream>
#include <algorithm>

Arad::CsvParser::CsvParserCls::CsvParserCls(QString const& filePath, QString const& delimiter,
                                            QVector<uint32_t> spamLines)
{
    Arad::CsvParser::CsvParserCls::setFilePath(filePath);
    Arad::CsvParser::CsvParserCls::setDelimiter(delimiter);
    Arad::CsvParser::CsvParserCls::setSpamLines(spamLines);
}

void Arad::CsvParser::CsvParserCls::setFilePath(QString const& filePath)
{
    if (filePath.isEmpty())
        std::invalid_argument("you must enter file path");

    this->_filePath = filePath;
}

QString Arad::CsvParser::CsvParserCls::getFilePath() const
{ return this->_filePath; }

void Arad::CsvParser::CsvParserCls::setDelimiter(QString const& delimiter)
{
    this->_delimiter = delimiter;
}

QString Arad::CsvParser::CsvParserCls::getDelimiter() const
{ return this->_delimiter; }

void Arad::CsvParser::CsvParserCls::setSpamLines(QVector<uint32_t> const& spamLines)
{
    this->_spamLines = spamLines;
}

QVector<uint32_t> Arad::CsvParser::CsvParserCls::getSpamLines() const
{ return this->_spamLines; }

template<typename T>
bool Arad::CsvParser::CsvParserCls::in(T const& item, QVector<T> const& container)
{
    return (std::find(container.begin(), container.end(), item) == container.end()) ? false : true;
}

/// for string delimiter
std::vector<std::string> Arad::CsvParser::CsvParserCls::split(std::string const& string)
{
    size_t pos_start = 0, pos_end, delim_len = this->_delimiter.length();
    std::string token;
    std::vector<std::string> result;

    while ((pos_end = string.find(this->_delimiter.toStdString(), pos_start)) != std::string::npos)
	{
        token = string.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }

	result.push_back(string.substr(pos_start));
    return result;
}

QVector<float> Arad::CsvParser::CsvParserCls::extracter(int columnNumber)
{
	--columnNumber;

    std::ifstream fin(this->_filePath.toStdString(), std::ios::in);
	if (!fin.is_open())
		throw std::invalid_argument("couldn't open the file");

	std::vector<std::string> splitedLine;
	QVector<float> result;
	std::string readLine = "";
    uint32_t lineCounter = 0;

	while (std::getline(fin, readLine))
	{
		++lineCounter;

        if (!in(lineCounter, this->_spamLines))
		{
            splitedLine = split(readLine);

			/// evaluating columnNumber
			if (static_cast<int>(splitedLine.size()) < (columnNumber + 1))
				throw std::invalid_argument("input column number is not valid");

			result.push_back(std::stof(splitedLine.at(columnNumber)));
		}
	}

	fin.close();

    /// sorting result vector
    std::sort(result.begin(), result.end());

	return result;
}

QList<QString> Arad::CsvParser::CsvParserCls::getColumnNames()
{
    QList<QString> output;
    std::string firstLine = "";
    std::ifstream fileInput(this->_filePath.toStdString(), std::ios::in);

    if (fileInput.is_open())
        std::getline(fileInput, firstLine);
    else
        throw std::runtime_error("couldn't open the file");

    std::vector<std::string> splited = Arad::CsvParser::CsvParserCls::split(firstLine);

    for (auto &item : splited)
        item = Arad::CsvParser::CsvParserCls::doubleQuoteRemover(item);

    for (auto const& item : splited)
        output.push_back(item.c_str());

    fileInput.close();
    return output;
}

std::string Arad::CsvParser::CsvParserCls::doubleQuoteRemover(std::string const& str)
{
    std::string result = "";

    for (auto const& ch : str)
        result = (ch != '"') ? result + ch : result;

    return result;
}
