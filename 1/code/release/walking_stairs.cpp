
#include <cstdlib>
#include <iostream>


// ToDo: Exercise 2.d - adapt and implement combinations

uint64_t combinations(int number)
{
	if (number < 1) {
		return 0;
	}
	if (number == 1) {
		return 1;
	}
	if (number == 2) {
		return 2;
	}

	//create and initialize vars for loop
	uint64_t CombN;	//not needed to initialize
	uint64_t CombNSub1 = 2;
	uint64_t CombNSub2 = 1;
	for (uint64_t n=3; n<=number; n++) {
		CombN = CombNSub1 + CombNSub2;	//calculate combinations for current n (current loop iteration)
		if ( (CombN <= CombNSub1) || (CombN <= CombNSub2) ) {
			//handling overflow
			std::cerr << "Overflow at n = " << n << std::endl;
			return 0;
		}
		
		CombNSub2 = CombNSub1;	//set combinations(n-2) for next n (next loop iteration)
		CombNSub1 = CombN;	//set combinations(n-1) for next n (next loop iteration)
	}
	return CombN;
}


int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	std::cout << combinations(n) << std::endl;

	return 0;
}
