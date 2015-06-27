#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for (auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}

// ToDo 5.3 - Merge the given lists [leftIt..midIt) and [midIt..rightIt)
template<class T>
void merge(T leftIt, T midIt, T rightIt)
{
	assert(leftIt <= midIt && midIt <= rightIt);

	std::vector<typename T::value_type> mergedValues;

	auto rightStartIt = midIt;
	while ( (leftIt < midIt) && (rightIt > rightStartIt) ) {
		if (*leftIt < *rightStartIt) {
			mergedValues.push_back(*leftIt);
			leftIt++;
		} else {
			mergedValues.push_back(*rightStartIt);
			rightStartIt++;
		}
	}
	//insert rest of other vec
	while (leftIt < midIt) {
		mergedValues.push_back(*leftIt);
		leftIt++;
	}
	while (rightIt > rightStartIt) {
		mergedValues.push_back(*rightStartIt);
		rightStartIt++;
	}

	//copy sorted vector back
	std::copy(mergedValues.begin(), mergedValues.end(), leftIt);
}

// ToDo 5.3 - Sort the given container using merge sort.
template<class T>
void mergeSort(T leftIt, T rightIt)
{
	assert(leftIt < rightIt);
	
	if (std::distance(leftIt, rightIt) == 1) {
		//do nothing if list only contains one element
		return;
	}

	auto midIt = leftIt + std::distance(leftIt, rightIt)/2;

	mergeSort(leftIt, midIt);
	mergeSort(midIt, rightIt);

	merge(leftIt, midIt, rightIt);
}

int main(int argc, char** argv)
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 1, 12, 33, 24, 5, 6, -7, -2, 19 };
	std::vector<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	printContainer(sampleDataInt);
	mergeSort(sampleDataInt.begin(), sampleDataInt.end());
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	mergeSort(sampleDataString.begin(), sampleDataString.end());
	printContainer(sampleDataString);

	return 0;
}
