#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
    std::cout << "{"; 
    for(auto element : container)
        std::cout << element << " ";
    std::cout << "}" << std::endl; 
}


// ToDo 5.1a - Merge front-back pairings of elements of inContainer into outContainer. Do *not* use the []-operator.
template<class T>
void front_back_pairing(T& inContainer, T& outContainer)
{
	int size = inContainer.size();
	int j=size-1;
	int i=0;
	int pos=0;

	//std::vector<T> v;//{ inContainer.begin(), inContainer.end() };
	//std::copy(inContainer.begin(), inContainer.end(), v.begin());
	while(i<size){
		for(auto elem : inContainer){
			//std::cout << elem;
			if((i%2)==0){	
				if(pos*2 != i){pos ++; continue;}
					outContainer.push_back(elem);
			}
			else{ //std::cout << j << " : " << pos << std::endl;
				if(pos != j){pos++; continue;}
					outContainer.push_back(elem);
					j--;
			}
			pos++;
		}	
	i++;
	//std::cout << i;
	pos=0;
	}
}

// ToDo 5.1b - Remove all duplicates from the given container. Do *not* use the []-operator.
template<class T>
void remove_duplicates(T& container)
{
	int i=0;
	int count=0;

	for(auto &elem: container){
		for(auto &inner: container){
			if(elem == inner){
				count++;
				if(count >= 2) container.erase(container.begin()+i);
			}
			i++;
		}
	count=0;
	i=0;
	}
}

// ToDo 5.1c - Expand the given container by inserting the numerical differences of each element to its neighbors. Do *not* use the []-operator.
template<class T>
void insert_differences(T& container)
{
	#if 0
	std::vector<T*>vec;
	std::copy(container.begin(),container.end(),vec.begin());

	int size = container.size();
	int i=0;
	int pos=0;

	for(auto elem: container){
		i++;
	}
	#endif
	T tmpVec;	//create temporary vector for insertion
	for (auto it=container.begin(); it!=container.end(); it++) {
		//get neighbor positions
		auto leftNeighbor = (it != container.begin()) ? it-1 : container.end()-1;
		auto rightNeighbor = (it != (container.end()-1) ) ? it+1 : container.begin();

		//calc differences
		auto leftVal = *leftNeighbor - *it;
		auto rightVal = *rightNeighbor - *it;

		//do insertion
		tmpVec.push_back(leftVal);
		tmpVec.push_back(*it);
		tmpVec.push_back(rightVal);
	}

	//copy tmpVec into to transforming vec
	//first resize container to correct size
	container.resize(tmpVec.size());
	std::copy(tmpVec.begin(), tmpVec.end(), container.begin());
}

void testFrontBackPairingFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,12,13,14,15,16,17,18,19 };
    std::list<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };
    
    // test for integer vector
    std::vector<int> helpIntVector;
    front_back_pairing(sampleDataInt, helpIntVector);
    printContainer(sampleDataInt);
    printContainer(helpIntVector);
    
    // test for string list
    std::list<std::string> helpStringList;
    front_back_pairing(sampleDataString, helpStringList);
    printContainer(sampleDataString);
    printContainer(helpStringList);
}

void testRemoveDuplicateFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,10,13,14,15,15,15,18,19,12,11,17 };
    std::vector<std::string> sampleDataString = { "Die", "___", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung", "Die", "ist", "blabla" };
    
    // test for integer vector
    printContainer(sampleDataInt);
    //remove_duplicates(sampleDataInt, std::less<int>() );
    remove_duplicates(sampleDataInt);
    printContainer(sampleDataInt);
    
    // test for string vector
    printContainer(sampleDataString);
    remove_duplicates(sampleDataString);
    printContainer(sampleDataString);
}

void testAddDifferenceFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,14,16,1,18 };
    
    // test for integer vector
    printContainer(sampleDataInt);
    insert_differences(sampleDataInt);
    printContainer(sampleDataInt);
}

int main(int argc, char** argv)
{
    testFrontBackPairingFunctionality();
    testRemoveDuplicateFunctionality();
    testAddDifferenceFunctionality();

    return 0;
}
