#include <headers/csvparser.h>

#include <fstream>
#include <algorithm>

template<typename T>
bool Arad::csvParser::in(T const& item, std::vector<T> const& container)
{
    return (std::find(container.begin(), container.end(), item) == container.end()) ? false : true;
}

/// for string delimiter
std::vector<std::string> Arad::csvParser::split(std::string const& string, std::string const& delimiter)
{    
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> result;

    while ((pos_end = string.find(delimiter, pos_start)) != std::string::npos)
	{
        token = string.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }

	result.push_back(string.substr(pos_start));
    return result;
}

std::vector<float> Arad::csvParser::Extracter(QString const& filePath, QString const& delimiter,
                                                    std::vector<uint32_t> const& spamLines, int columnNumber)
{
	--columnNumber;

	std::ifstream fin(filePath.toStdString(), std::ios::in);
	if (!fin.is_open())
		throw std::invalid_argument("couldn't open the file");

	std::vector<std::string> splitedLine;
	std::vector<float> result;
	std::string readLine = "";
	uint32_t lineCounter = 0;

	while (std::getline(fin, readLine))
	{
		++lineCounter;

		if (!in(lineCounter, spamLines))
		{
			splitedLine = split(readLine, delimiter.toStdString());

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
