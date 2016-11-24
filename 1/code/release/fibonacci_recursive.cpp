
#include <cstdlib>
#include <iostream>


int FibonacciIntern(int number, unsigned int *CalculationSteps)
{
	(*CalculationSteps)++;	//task an example are inconsistent with the position of this statement
				//task says number of summations (position see below) but this position is number of calls
				//however the example shows a value which indicates this position
				//I decided to stick with the example


	if (CalculationSteps == 0) {
		//overflow (normally steps is 2*fib(n) - 1 so uint should be big enough but if fib(n) overflows maybe steps also overflows)
		CalculationSteps--;	//decrease to print last step count
		std::cerr << "OVERFLOW: CalculationSteps, StepCount Before: " << CalculationSteps << std::endl;
		CalculationSteps++;	//back to original
	}
	
	if (number < 1) {	//if n isn't a element in positive natural numbers return 0
		return 0;
	}
	if (number > 2) {
		int FibNSub1 = FibonacciIntern(number - 1, CalculationSteps);
		int FibNSub2 = FibonacciIntern(number - 2, CalculationSteps);
		int FibN = FibNSub1 + FibNSub2;
		//(*CalculationSteps)++;	//Position for number of summations

		if ( (FibNSub2 == 0) ||			//is bad argument for fib(n-2)
		     (FibNSub1 == 0) ||			//is bad argument for fib(n-1)
		     (FibN < FibNSub1) )		//is overflow ( overlow = fib(n-1) + x; fib(n-2) >= x > 0; overflow <= 0; result = overflow + fib(n-2)-x
		{					//fib(n-2)-x < fib(n-1) && overflow <= 0 --> result < fib(n-1) )
			return 0;
		}
		else
		{
			return FibN;
		}
	}
	else
	{
		return 1;
	}	
	return 0;	//should never get here
}

int fibonacci(int number, unsigned int *CalculationSteps)
{
	*CalculationSteps = 0;		//take care that CalculationSteps is set to zero
	return FibonacciIntern(number, CalculationSteps);
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
