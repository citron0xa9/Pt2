
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>


struct Interval
{
    Interval(const int i, const int start, const int length) 
    : index(i)
    , start(start)
    , end(start + length)
    { 
    }

    int index;
    int start;
    int end;
};

const static int MaxEnd = 74;
const static int MaxDuration = 10;

const static int N = 20;

std::ostream & operator<<(std::ostream & os, const std::vector<Interval> & I) 
{
	os << I.size() << std::endl;
    
	//TODO 6.3 
	//Implement a nice print function
	const size_t MaxIdLen = std::floor(log10(N))+1;		//could be N-1 but if someday index start with 1 this version is safer
	for (auto & i : I) {
		size_t IdLen = (i.index != 0) ? std::floor(log10(i.index))+1 : 1;	//prevent logarithm of 0 with condition
		const char dot = '.';
		const char IntervalChar = '#';

		std::string fill(MaxIdLen-IdLen, ' ');
		std::string beforeI(i.start, dot);
		std::string atI(i.end-i.start, IntervalChar);	//format of an interval: [start;end) --> end isn't printed like belonging to the interval
		std::string afterI((MaxEnd-i.end)+1, dot);

		os << "#" << i.index << fill << " |" << beforeI << atI << afterI << "|" << std::endl;
	}


	return os;
}

bool operator<(const Interval & a, const Interval & b)
{
	return (a.end < b.end);
}

//creates data
void randomize(std::vector<Interval> & intervals)
{
    intervals.clear();
    srand(time(0));

    for (int i = 0; i < N; i++)
    {
        int duration = rand() % MaxDuration + 1;
        int start = rand() % (MaxEnd - duration);

        intervals.push_back(Interval(i, start, duration));
    }
}


void schedule(const std::vector<Interval> & intervals)
{
    // unsorted

    std::cout << std::endl << "intervals (randomized):" << std::endl << intervals;

    // ToDo: Exercise 6.3 - sort and schedule intervals

	auto sorted = intervals;
    // sort intervals
	std::sort(sorted.begin(), sorted.end());

    std::cout << std::endl << "intervals (sorted):" << std::endl << sorted;

    // scheduled
    
    auto scheduled = std::vector<Interval>();
    
    //ToDo 6.3
	//implement greedy scheduling
	int lastEnd = 0;
	for (auto & interval : sorted) {
		if (interval.start >= lastEnd) {	//assuming intervals are defined like [start;end) if it would be [start;end] then the compare operator would be >
			//interval can be choosen and because sorted is sorted the choosen interval is the one with the earliest end time of all the intervals that could be choosen
			//choose that interval
			scheduled.push_back(interval);
			lastEnd = interval.end;
		}
		//if intervall cant be choosen do nothing
	}

    std::cout << std::endl << "intervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)" 
        << std::endl << scheduled << std::endl;
}

int main(int argc, char** argv) {

    auto intervals = std::vector<Interval>();

    randomize(intervals);
    schedule(intervals);

    return 0;
}
