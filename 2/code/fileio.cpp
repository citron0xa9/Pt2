#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

enum class Index {
		Airport_Id = 0,
		Name = 1,
		City = 2,
		Country = 3,
		IATA_FAA = 4,
		ICAO = 5,
		Latitude = 6,
		Longitude = 7,
		Altitude = 8,
		Timezone = 9,
		DST = 10,
		DatabaseTimeZone = 11
};
const char* IndexAsString[] = {"Airport ID", "Name", "City", "Country", "IATA/FAA", "ICAO", "Latitude", "Longitude", "Altitude", "Timezone", "DST", "Database Time Zone"};


//@param column: first column has value of 0
bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;
	
	switch (column)
	{

        	case static_cast<int>(Index::ICAO):
            		regExp = "\"([A-Z]{4})?\"";
            		break;
		case static_cast<int>(Index::Altitude):
			regExp = "[0-9]{1,6}";
			break;
		case static_cast<int>(Index::DST):
			regExp = "\"(E|A|S|O|Z|N|U)\"";
			break;

		default:
			regExp = ".*";
			break;
	}
	
	return std::regex_match(teststring, regExp);
}


void readTokensAndLines(char* path)
{
	const char* LogPath = "fileio.log";	

	std::ifstream file(path);
	std::ofstream log(LogPath, std::ios::out | std::ios::trunc);

	std::string parsed, line;
	const char delim = ',';

	int LineNr = 1;
	while (std::getline(file, line)) {
		std::cout << "\"[NAME]\" - \"[DATABASE TIME ZONE]\" -> ";

		std::istringstream linestream(line);
		
		int index = 0;
		std::string substring;
		
		//used to handle formats where one part contains a ',' e.g. "Potsdam, Berlin"
		std::string AppendStr;
		bool AppendTo = false;

		while (std::getline(linestream, substring, delim)) {
			//handle commas in one part
			if (AppendTo) {
				substring = AppendStr + substring;
				AppendTo = false;
			}

			if ( (substring.front() == '"') && !(substring.back() == '"') ) {
				AppendTo = true;
				AppendStr = substring;
				continue;
			}

			switch (index) {
				case static_cast<int>(Index::Name):
					std::cout << substring << " - ";
					break;
				case static_cast<int>(Index::DatabaseTimeZone):
					std::cout << substring;
					break;
				default:
					break;
			}
			
			//2.2b Check parts with isValueCorrect
			if (!isValueCorrect(substring, index)) {
				log << "ERROR (in line " << LineNr << ", index: " << index << "): " << line << std::endl;
				log << IndexAsString[index] << " is not valid" << std::endl;
			}

			index++;
		}
		std::cout << std::endl;

		LineNr++;
		// ToDo: Exercise 2.2a - Split line and write result to std::cout
		// ToDo: Exercise 2.2b - Check each part of line with isValueCorrect and log if values are not supported. Use and extend isValueCorrect function for this.
		
	}
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}
	
	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;

	// ToDO: Exercise 2.2a - Parse the stream by lines and every line by its delimiter
	//					   - Print the name of the airport and the timeZone for each airport
	readTokensAndLines(argv[1]);

	return 0;
}
