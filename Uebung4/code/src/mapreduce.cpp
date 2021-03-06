#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

// Calculates the distance between two points on earth specified by longitude/latitude. 
// Function taken and adapted from http://www.codeproject.com/Articles/22488/Distance-using-Longitiude-and-latitude-using-c 
float calculateDistanceBetween(float lat1, float long1, float lat2, float long2)
{
	//main code inside the class
	float dlat1 = lat1*((float)M_PI / 180.0f);

	float dlong1 = long1*((float)M_PI / 180.0f);
	float dlat2 = lat2*((float)M_PI / 180.0f);
	float dlong2 = long2*((float)M_PI / 180.0f);

	float dLong = dlong1 - dlong2;
	float dLat = dlat1 - dlat2;

	float aHarv = pow(sin(dLat / 2.0f), 2.0f) + cos(dlat1)*cos(dlat2)*pow(sin(dLong / 2), 2);
	float cHarv = 2 * atan2(sqrt(aHarv), sqrt(1.0f - aHarv));
	//earth's radius from wikipedia varies between 6,356.750 km � 6,378.135 km (�3,949.901 � 3,963.189 miles)
	//The IUGG value for the equatorial radius of the Earth is 6378.137 km (3963.19 mile)
	const float earth = 6378.137f;
	return earth*cHarv;
}

struct AirportInfo
{
	std::string m_name; 
	std::string m_city;
	std::string m_country;
	float pos[2]; // x: latitude, y: longitude

	std::vector<std::pair<int, int>> m_routes; // dest_id + numStops
	std::vector<float> m_routeLengths;
	float m_averageRouteLength;
};

void importAirportData(char* path, std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Importing airport data.." << std::endl;
	std::ifstream file(path);
	std::string field, line;
	
	int currentLineNum = 0;

	while (std::getline(file, line)) 
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		int currentID = -1;
		std::string result;
		currentLineNum++;
		
		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
				case 0: // id
					currentID = std::stoi(field);
					airportInfo.insert(std::make_pair(currentID, AirportInfo()));
					break;
				case 1: // name
					airportInfo[currentID].m_name = field;
					break;
				case 2: // city
					airportInfo[currentID].m_city = field;
					break;
				case 3: // country
					airportInfo[currentID].m_country = field;
					break;
				case 6: //latitude
					airportInfo[currentID].pos[0] = std::stof(field);
					break;
				case 7: // longitude
					airportInfo[currentID].pos[1] = std::stof(field);
					break;
				default:
					break;
				}
			}
			catch (const std::invalid_argument&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (invalid argument)!" << std::endl;
				//std::cout << field << std::endl;
			}
			catch (const std::out_of_range&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (out of range)!" << std::endl;
				//std::cout << field << std::endl;
			}

			fieldNum++;
		}
	}
}

void importRoutesData(char* path, std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Importing routes data.." << std::endl;
	std::ifstream file(path);
	std::string field, line;

	int currentLineNum = 0;

	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		int sourceID = -1;
		int destID = -1;
		int stops = -1;
		std::string result;
		currentLineNum++;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
				case 3: // source id
					sourceID = std::stoi(field);
					break;
				case 5: // dest id
					destID = std::stoi(field);
					break;
				case 7: // stops
					stops = std::stoi(field);
					break;
				default:
					break;
				}
			}
			catch (const std::invalid_argument&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (invalid argument)!" << std::endl;
				//std::cout << field << std::endl;
			}
			catch (const std::out_of_range&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (out of range)!" << std::endl;
				//std::cout << field << std::endl;
			}

			fieldNum++;
		}
		if (sourceID != -1 && destID != -1 && stops != -1)
		{
			try
			{
				airportInfo[sourceID].m_routes.push_back(std::make_pair(destID, stops));
			}
			catch (const std::out_of_range&)
			{
				std::cout << "Source airport with ID " << sourceID << " not present in airport dataset!" << std::endl;
			}
		}
	}
}

// ToDo 4.1a - remove all routes from AirportInfo::m_routes with at least one stop (so that only direct flights remain). Use std::remove_if().

bool remove_flight(const std::pair<int,int> &da){
if (da.second == 1) return 1;
return 0;
}

void removeNonDirectFlights(std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Remove non-direct flights (i.e., at least one stop)" << std::endl;
	for(auto & airport : airportInfo){
		for(auto it = airport.second.m_routes.begin();it != airport.second.m_routes.end();it++){
			std::remove_if(airport.second.m_routes.begin(),airport.second.m_routes.end(),remove_flight);
			//std::cout << it->second;
		}
	}	
}

// ToDo 4.1b - For each route in AirportInfo::m_routes, calculate the distance between start and destination. Store the results in AirportInfo::m_routeLengths. Use std::transform() and calculateDistanceBetween().
#define WITH_TRANSFORM 1
void calculateDistancePerRoute(std::map<int, AirportInfo>& airportInfo)
{
	float destPos[2];
	
	std::cout << "Calculate distance for each route" << std::endl;

	#if WITH_TRANSFORM
	for (auto it=airportInfo.begin(); it!=airportInfo.end(); it++) {
		auto &info = it->second;
	
		//prepare transform
		info.m_routeLengths.resize(info.m_routes.size());

		std::transform(info.m_routes.begin(), info.m_routes.end(), info.m_routeLengths.begin(), [&airportInfo, &info](std::pair<int,int> &route){
			float destPos[2];
			destPos[0] = airportInfo[route.first].pos[0];
			destPos[1] = airportInfo[route.first].pos[1];
			return calculateDistanceBetween(info.pos[0], info.pos[1], destPos[0], destPos[1]);
		});
	}
	#else
	
	for(auto & airport : airportInfo){
		for(auto & it : airport.second.m_routes){
			destPos[0] = airportInfo[it.first].pos[0];
			destPos[1] = airportInfo[it.first].pos[1];
			airport.second.m_routeLengths.push_back(calculateDistanceBetween(airport.second.pos[0], airport.second.pos[1],destPos[0],destPos[1]));

		}
	//std::cout << calculateDistanceBetween(airport.second.pos[0], airport.second.pos[1],destPos[0],destPos[1]) << std::endl;
	}
	#endif

}

// ToDo 4.1c - Based on AirportInfo::m_routeLengths, calculate for each airport the average distance of outgoing routes. Store the results in AirportInfo::m_averageRouteLength. Use std::accumulate().
void calculateAverageRouteDistances(std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Calculate average distance for each source airport" << std::endl;
	for(auto & airport : airportInfo){
		if(airport.second.m_routeLengths.size() != 0)
		airport.second.m_averageRouteLength = (std::accumulate(airport.second.m_routeLengths.begin(), airport.second.m_routeLengths.end(), 0))/airport.second.m_routeLengths.size();
	}
}

void printResults(std::map<int, AirportInfo>& airportInfo)
{
	for (auto & airport : airportInfo)
	{
		if (airport.second.m_routeLengths.size())
			std::cout << airport.second.m_name << " (" << airport.second.m_city << ", " << airport.second.m_country << "): " << airport.second.m_averageRouteLength << "km (" << airport.second.m_routeLengths.size() << " direct outgoing routes)" << std::endl;

	}
}

int main(int argc, char * argv[])
{
	if(argc != 3)
	{
		std::cout << "not enough arguments - USAGE: mapreduce [AIRPORT DATASET] [AIRLINE DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}

	static std::map<int, AirportInfo> airportInfo;

	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;
	std::cout << "Given path to routes.dat: " << argv[2] << std::endl;

	importAirportData(argv[1], airportInfo);
	importRoutesData(argv[2], airportInfo);

	removeNonDirectFlights(airportInfo);
	calculateDistancePerRoute(airportInfo);
	calculateAverageRouteDistances(airportInfo);
	printResults(airportInfo);


	return 0;
}
