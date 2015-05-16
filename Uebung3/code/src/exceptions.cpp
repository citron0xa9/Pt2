#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <ctime>
#include <stdexcept>

// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date)
{
    std::tm t;
#if defined(__GNUC__) && (__GNUC__ < 5)
	strptime(date.c_str(), "%d.%m.%Y", &t);
#else
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%d.%m.%Y");
#endif
    
    if(t.tm_year < 105 || t.tm_year > 115)
        throw std::logic_error("Year should be between 2005 and 2015");
    
    return t;
}

struct FormatException
{
    int m_actLine;
    std::string m_actFields;
};

void parseLine(std::string line, int lineNum)
{
    const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };
	const char delim = ';';
    
	std::string token;
	int index = 0;

	std::istringstream iline(line);

	while (std::getline(iline, token, delim)) {
		try {
			switch (index) {
				case 0:
					stringToTime(token);
					break;
				case 1:
				case 2:
					std::stof(token);
					break;
				default:
					throw std::logic_error("Invalid Token index");	//e.g. caused by to much tokens in one line
					break; //not necessarry
			}
		} catch (const std::exception & e) { //catch any logic or runtime error
			FormatException ex;
			ex.m_actLine = lineNum;
			ex.m_actFields = fieldNames[index];
			throw ex;
		}

		index++;
	}
    // todo 3.2b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof. Catch all exceptions thrown by these methods. If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.
    
}

// todo 3.2c..
void writeOutFormatException(const FormatException & e)
{
	static const char* logfilePath = "exceptions.log";
	std::ofstream log;
	log.exceptions(~std::ofstream::goodbit);

	try {
		log.open(logfilePath, std::ios::out | std::ios::app);

		log << "Format Exception in line " << e.m_actLine << ": ";
		log << "Field '" << e.m_actFields << "' is incorrect" << std::endl;
		
		log.close();
	} catch (const std::ios_base::failure & e) {
		std::cerr << "Error logging format exception. File IO error." << std::endl;
	}
		
    // todo 3.2d: export information (i.e., line number + invalid data fields) about exception to a logfile.
    // todo 3.2d: catch ios_base::failure
}

void checkData(std::string path)
{
	int validLines = 0;
    int invalidLines = 0;
	int lineNum;

	std::string line;

    std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(path);

		lineNum = 1;
		while (!file.eof()) {
			std::getline(file, line);
			try {
				parseLine(line, lineNum);
				validLines++;	//this part is only reached if no exception is thrown --> valid line
			} catch (const FormatException & e) {
				writeOutFormatException(e);
				invalidLines++;
			}
			
			lineNum++;
		}

		file.close();
	} catch (const std::ifstream::failure & e) {
		std::cerr << "Error operating on file" << std::endl;
	}
    
    // todo 3.2c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines
    
    std::cout << "valid lines: " << validLines << " - invalid lines: " << invalidLines << std::endl;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
        return -1;
    }
    
    checkData(argv[1]);

	return 0;
}
