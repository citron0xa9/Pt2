#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

struct Route
{
	int airlineId;
	int sourceId;
	int destinationId;
};

bool operator<(const Route& r1, const Route& r2) {
	return r1.destinationId < r2.destinationId;
}

void importRoutesData(char* path, std::vector<Route>& routes)
{
	std::cout << "Importing routes data.." << std::endl;
	std::ifstream file(path);
	std::string field, line;
	
	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		Route route;
		route.airlineId = route.sourceId = route.destinationId = -1;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
					case 1: // airline id
						route.airlineId = std::stoi(field);
						break;
					case 3: // source id
						route.sourceId = std::stoi(field);
						break;
					case 5: // dest id
						route.destinationId = std::stoi(field);
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

		if (route.airlineId > -1 && route.sourceId > -1 && route.destinationId > -1)
			routes.push_back(route);
	}
}

// ToDo 5.2a - Return the number of routes for the given destination id based on a linear search. Count the number of lookups.
int linearSearch(int destID, std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;
	numLookups = 0;

	for(auto it=routes.begin(); it!=routes.end(); it++) {
		if ( it->destinationId == destID) {
			numRoutes++;
		}
		numLookups++;
	}

	return numRoutes;
}

// ToDo 5.2a - Evaluate the linearSearch function by calling it for every possible destination id (1..9541). 
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
std::pair<long long, long long> evaluateLinearSearch(std::vector<Route>& routes)
{
	long long numLookups = 0;
	long long duration = 0;


	for (int i=1; i<=9541; i++) {
		long long tmpLookups = 0;

		auto start = std::chrono::high_resolution_clock::now();		//get start time
		//perform search
		linearSearch(i, routes, tmpLookups);
		//get end time
		auto end = std::chrono::high_resolution_clock::now();

		//calculate duration
		auto tmpDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
		duration += tmpDuration.count();

		//add lookups
		numLookups += tmpLookups;
	}
	
	return std::make_pair(numLookups, duration);
}

// ToDo 5.2b - Return the number of routes for the given destination id based on a binary search. Count the number of lookups.
// The vector should have been sorted before calling this function.
int binarySearch(int destID, std::vector<Route>& routes, long long& numLookups)
{
	numLookups = 0;
	int numRoutes = 0;

	auto leftBound = routes.begin();
	auto rightBound = routes.end();

	auto mid = leftBound + std::distance(leftBound, rightBound)/2;	

	while ( (mid->destinationId != destID) && !(std::distance(leftBound, rightBound) < 2) ) {
		numLookups++;
		//adjust intervall -> mid element doesn't have to be included because it is not the value we search for
		numLookups++;
		if (destID < mid->destinationId) {
			rightBound = mid;
		} else {
			leftBound = mid+1;
		}
		mid = leftBound + std::distance(leftBound, rightBound)/2;
	}

	numLookups++;
	if (mid->destinationId != destID) {
		//nothing found....
		return 0;
	}

	//step back and forth in vector, until the elements are no longer equal destID
	leftBound = rightBound = mid;
	while ( (leftBound != (routes.begin()-1)) && (rightBound != routes.end()) ) {

		bool updated = false;	//check whether adjustments are still made

		//move iterators if their value is still equal destID and they did not reach the end/begin of the vector

		if (leftBound != (routes.begin()-1)) {	//2 if's to counter dereferencing an "invalid" iterator
			numLookups++;
			if (leftBound->destinationId == destID) {
				leftBound--;
				updated = true;
			}
		}
		if (rightBound != routes.end()) {	//again counter dereferencing -"-
			numLookups++;
			if (rightBound->destinationId == destID) {
				rightBound++;
				updated = true;
			}
		}
		
		//stop if nothing changes anymore
		if (!updated) {
			break;
		}
	}

	numRoutes = std::distance(leftBound, rightBound) - 1;	//both iterators point to next not equal element --> for rightBound this is ok (see std::distance) but
								//left bound has to be adjusted/distance is one too big
	
	return numRoutes;
}

// ToDo 5.2b - Evaluate the binarySearch function by calling it for every possible destination id (1..9541). 
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
// Attention: sorting is *not* part of the evaluation and should be conducted beforehand.
std::pair<long long, long long> evaluateBinarySearch(std::vector<Route>& routes)
{
	long long numLookups = 0;
	long long duration = 0;

	//fist sort the vector
	std::sort(routes.begin(), routes.end());

	for (int i=1; i<=9541; i++) {
		long long tmpLookups = 0;

		auto start = std::chrono::high_resolution_clock::now();		//get start time
		//perform search
		binarySearch(i, routes, tmpLookups);
		//get end time
		auto end = std::chrono::high_resolution_clock::now();

		//calculate duration
		auto tmpDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
		duration += tmpDuration.count();

		//add lookups
		numLookups += tmpLookups;
	}
	
	return std::make_pair(numLookups, duration);
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: sort [ROUTE DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}

	static std::vector<Route> routes;

	std::cout << "Given path to routes.csv: " << argv[1] << std::endl;

	importRoutesData(argv[1], routes);

	const int evaluationRunCount = 10;
	double ratioLookupsAvg = 0;
	double ratioTimeAvg = 0;
	for (int i=0; i<evaluationRunCount; i++) {
		std::cout << "Evaluation run number: " << i << std::endl;

		auto resultLin = evaluateLinearSearch(routes);
		std::cout << "Lookups: " << resultLin.first << " - " << "Nanoseconds: " << resultLin.second << std::endl;
		auto resultBin = evaluateBinarySearch(routes);	
		std::cout << "Lookups: " << resultBin.first << " - " << "Nanoseconds: " << resultBin.second << std::endl;

		double ratioLookups = static_cast<double>(resultLin.first)/resultBin.first;
		double ratioTime = static_cast<double>(resultLin.second)/resultBin.second;

		std::cout << "Ratio Lookups: " << ratioLookups << " - Ratio Time: " << ratioTime << std::endl;

		ratioLookupsAvg += ratioLookups;
		ratioTimeAvg += ratioTime;
	}

	ratioLookupsAvg /= evaluationRunCount;
	ratioTimeAvg /= evaluationRunCount;

	std::cout << "--------------------------" << std::endl;
	std::cout << "Ratio Lookups Avg: " << ratioLookupsAvg << std::endl;
	std::cout << "Ratio Time Avg: " << ratioTimeAvg << std::endl;
	
	return 0;
}
