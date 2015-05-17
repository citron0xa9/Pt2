#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


/**************************
vector operations happen here
**************************/
int getTime(int searchValue, const std::vector<int> &boxes, bool reverse = false)
{
	int time {0};

	bool found {false};

	if (reverse) {
		for (auto it=boxes.rbegin(); it != boxes.rend(); it++) {
			//first dogs sniffs on box
			time++;
			if (*it == searchValue) {
				found = true;
				break;
			}
		}
	} else {
		for (auto it=boxes.begin(); it != boxes.end(); it++) {
			//first dogs sniffs on box
			time++;
			if (*it == searchValue) {
				found = true;
				break;
			}
		}
	}

	if (!found) {
		throw std::logic_error("Gegenstand in keiner Box vorhanden");
	}

	return time;
}

inline int getTimeL(int searchValue, const std::vector<int> &boxes)
{
	return getTime(searchValue, boxes, false);
}

inline int getTimeR(int searchValue, const std::vector<int> &boxes)
{
	return getTime(searchValue, boxes, true);
}



/************************
Logical operations happen here
************************/
inline int getTimeLR(int searchValueX, int searchValueY, const std::vector<int> &boxes)
{
	return std::max(getTimeL(searchValueX, boxes), getTimeR(searchValueY, boxes));
}

inline int getTimeL(int searchValueX, int searchValueY, const std::vector<int> &boxes)
{
	return std::max(getTimeL(searchValueX, boxes), getTimeL(searchValueY, boxes));
}

inline int getTimeR(int searchValueX, int searchValueY, const std::vector<int> &boxes)
{
	return std::max(getTimeR(searchValueX, boxes), getTimeR(searchValueY, boxes));
}

// todo 3.3: Calculate minimum time needed for both dogs to return 
int minTimeDogTraining(int searchValueX, int searchValueY, const std::vector<int> &boxes)
{
	/*
	* Laut Aufgabenstellung kommen die Hunde einfach ohne Box zurueck, wenn der Gegenstand in keiner Box vorhanden ist.
	* Es gibt aber trotzdem, auch wenn der Gegenstand in keiner Box ist, eine minimale Suchzeit die dann einfach der Zeit
	* zum absuchen aller Boxen entspricht.
	* Der Code in main legt nahe dass aber in einem solchen Fall -1 zurueckgegeben werden soll --> Annahme Trainer soll damit gewarnt werden.
	* Ansonsten muesste einfach nur keine Exception in der Funktion getTime geworfen werden.
	*/
	//catch impossible combinations
	if ( (searchValueX == searchValueY) || (boxes.size() < 1)) {
		return -2;
	}

	try {

		//There are 4 possible start combinations:
		//1. Start from left and right (X left, Y right)
		int TimeStartLR = getTimeLR(searchValueX, searchValueY, boxes);

		//2. Start from left and right (X right, Y left)
		int TimeStartRL = getTimeLR(searchValueY, searchValueX, boxes);

		//3. Start both dogs from left
		int TimeStartL = getTimeL(searchValueX, searchValueY, boxes);

		//4. Start both dogs from right
		int TimeStartR = getTimeR(searchValueX, searchValueY, boxes);

		//get minimum of these 4 possibilities
		return std::min({TimeStartLR, TimeStartRL, TimeStartL, TimeStartR});
	} catch (const std::logic_error &e) {
		//Gegenstand in keiner Box
		return -1;
	}
}

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cout << "Missing parameters. Usage: <searchValue1> <searchValue2> [box1] [box2] [...]" << std::endl;
		return 0;
	}

	const int searchValueX = std::atoi(argv[1]);
	const int searchValueY = std::atoi(argv[2]);
	if(searchValueX < 1 || searchValueY < 1)
	{
		std::cerr << "Search values must be greater than zero!";
	}
	
	if (searchValueX == searchValueY)
	{
		std::cerr << "Search values must be different!";
		return 1;
	}

	std::vector<int> boxes;
	for (int i = 3; i < argc; i++)
	{
		int value = std::atoi(argv[i]);
		if (value < 1)
		{
			std::cerr << "Box value must be greater than zero!";
			return 2;
		}

		boxes.push_back(std::atoi(argv[i]));
	}

	int minTime = minTimeDogTraining(searchValueX, searchValueY, boxes);
	if (minTime == -1)
	{
		std::cout << "There exists no two boxes with the given search values!" << std::endl;
	}
	else
	{
		std::cout << "The coach will have to wait at least " << minTime << " seconds!" << std::endl;
	}
	
	return 0;
}
