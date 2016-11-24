
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cmath>


int triangular(int number)
{
	assert(number >= 1);	//n has to be an element in positive natural numbers (per definition in formula)
	
	int sum = 0;
	for (int i=1; i <= number; i++) {
		sum += i;
	}

	return sum;
}

void pretty_print(int decimal)
{
	//use recursion to solve this (to flip output order)
	if (decimal > 1000) { 					//recursion end condition
		int BeforeDot = decimal/1000;
		int AfterDot = decimal % 1000;
		pretty_print(BeforeDot);
		std::cout << "." << AfterDot;
	}
	else {
		std::cout << decimal;
	}
}

int GetDomainMax(int CoDomainMax)
{
	//n*(n+1)/2 = y | * 2
	//n*(n+1) = 2y  | distributive law
	//n^2 + n = 2y  | - 2y
	//n^2 + n - 2y = 0 | p,q formula
	//n = -0.5 +/- sqrt(0.25 + 2y) | negative numbers are not accepted --> only use +
	//n = -0.5 + sqrt(0.25 + 2y)
	//making y dynamic (independent from assigned size to int using sizeof requires additional functionality from cmath (sqrt))
	double PreciseResult = -0.5 + sqrt(0.25 + 2*static_cast<int64_t>(CoDomainMax) );
	return ( static_cast<int>(PreciseResult) );   //cast is like floor

}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 


	const int CoDomainMin = 1;				//lowest possible value
	const int CoDomainMax = pow(2, sizeof(int) * 8 - 1) -1; //Max value for int
	const int DomainMin = 1;				//Defined in formula
	const int DomainMax = GetDomainMax(CoDomainMax);	//Calculate this value because sizeof(int) could change

	if ( (n > DomainMax) || (n < DomainMin) ) {
		std::cout << "domain = [";
		pretty_print(DomainMin); std::cout << ";"; pretty_print(DomainMax);
		std::cout << "], codomain = [";
		pretty_print(CoDomainMin); std::cout << ";"; pretty_print(CoDomainMax);
		std::cout << "]" << std::endl;
		return 2;
	}

	pretty_print(triangular(n)); std::cout << std::endl;
	//std::cout << "Hello World";

	return 0;
}
