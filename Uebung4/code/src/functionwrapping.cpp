#include <functional>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <stdexcept>

struct CommandLineParameter
{
	CommandLineParameter(int argc, char* argv[])
		: m_fibonacci(false)
		, m_centeredTriangular(false)
		, m_powSum(false)
	{
		for (int i = 1; i < argc; i++)
		{
			if (!strcmp(argv[i], "-fib"))
			{
				m_fibonacci = true;
			}
			else if (!strcmp(argv[i], "-ct"))
			{
				m_centeredTriangular = true;
			}
			else if (!strcmp(argv[i], "-pow"))
			{
				m_powSum = true;
			}
		}
	}

	bool m_fibonacci;
	bool m_centeredTriangular;
	bool m_powSum;
};

// ToDo 4.2a - Calculate and return the fibonacci number for the given input value
int fibonacci(int number)
{
	if (number < 1) { //if number isn't a positive natural number throw exception
		throw std::out_of_range("Number has to be >= 1");
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

		if (FibN < FibNSub1) {
			//is overflow! (overflow = fib(n-1) + x; overflow <= 0; fib(n-2) >= x > 0; result = overlow + fib(n-2)-x
			//overflow <= 0 && fib(n-2)-x < fib(n-1) --> result < fib(n-1) )
			throw std::overflow_error("Overflow calculating fibonacci");
		}

		FibNSub2 = FibNSub1;		//set fib(n-2) for next n (next loop iteration)
		FibNSub1 = FibN;		//set fib(n-1) for next n (next loop iteration)
	}

	return FibN;
}

// ToDo 4.2a - Calculate and return the centered triangular number for the given input value
int centeredTriangular(int number)
{
	return ((3*pow(number, 2) + 3*number + 2) / 2);
}

// ToDo 4.2a - Calculate and return the sum of i^exp for all i in [1..number]
int powSum(int number, int exp)
{
	int sum {0};
	for (int i=1; i<=number; i++) {
		sum += pow(i, exp);
	}
	return sum;
}

// ToDo 4.2c - Call each function inside the functions vector. Print the results via std::cout
void applyFuntions(std::vector<std::function<int(int)>> & functions, int number)
{
	int FuncNr = 0;
	for (const auto &func : functions) {
		std::cout << "Result of function " << FuncNr << ": " << func(number) << std::endl;
		FuncNr++;
	}
}

int main(int argc, char * argv[])
{
	std::vector<std::function<int(int)>> functions;
	CommandLineParameter cmd(argc, argv);
	
	if (cmd.m_fibonacci)
	{
		functions.push_back(fibonacci);
		// ToDo 4.2b - Add the fibonacci function directly to the functions vector
	}
	if (cmd.m_centeredTriangular)
	{
		functions.push_back([](int n){ return centeredTriangular(n); });
		// ToDo 4.2b - Add a lambda expression that calls the centeredTriangular function to the functions vector
	}
	if (cmd.m_powSum)
	{
		auto func = std::bind(powSum, std::placeholders::_1, 2);	//use 2 as exponent
		functions.push_back(func);
		// ToDo 4.2b - Add the powSum function using a std::bind expression to the functions vector. Use a constant value (e.g., 2) for the exp argument 
	}

	for (int i = 1; i < 45; i++)
	{
		applyFuntions(functions, i);
	}
}
