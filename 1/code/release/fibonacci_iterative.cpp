
#include <cstdlib>
#include <iostream>


int fibonacci(int number, unsigned int *CalculationSteps)
{
	*CalculationSteps = 0;

	if (number < 1) { //if number isn't a positive natural number return 0
		return 0;
	}

	if (number <= 2) {
		return 1;
	}

	//set intial values for first loop iteration (n=3)
	int FibN;		//no initial value needed
	int FibNSub1 = 1;
	int FibNSub2 = 1;

	for (int n=3; n<=number; n++) {
		FibN = FibNSub1 + FibNSub2;	//calculate fib(n) for current n (current loop iteration)
		(*CalculationSteps)++;		//task and example for this are inconsistent (see comment in fibonacci_recursive.cpp) --> used number of summations here
						//with unsigned int no overflow for CalculationSteps should ever occur here
		if (FibN < FibNSub1) {
			//is overflow! (overflow = fib(n-1) + x; overflow <= 0; fib(n-2) >= x > 0; result = overlow + fib(n-2)-x
			//overflow <= 0 && fib(n-2)-x < fib(n-1) --> result < fib(n-1) )
			return 0;
		}

		FibNSub2 = FibNSub1;		//set fib(n-2) for next n (next loop iteration)
		FibNSub1 = FibN;		//set fib(n-1) for next n (next loop iteration)
	}

	return FibN;	
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	unsigned int steps;
	std::cout << n << " : " << fibonacci(n, &steps);
	std::cout << " : #" << steps << std::endl;

	return 0;
}
