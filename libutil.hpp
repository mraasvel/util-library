#ifdef LIBUTIL_HPP
# define LIBUTIL_HPP
#ifndef TIMER_HPP
# define TIMER_HPP

/*
NOTE: Min C++11 for chrono
*/

# include <chrono>

namespace util {

class Timer {
private:
	typedef std::chrono::steady_clock clock_type;
	typedef std::chrono::duration<double, std::ratio<1> > second_type;

public:
	Timer();

	void reset();
	double elapsed() const;

private:

	std::chrono::time_point<clock_type> start_time;
};

}

#endif /* TIMER_HPP */
#ifndef UTIL_HPP
# define UTIL_HPP

#include <vector>
#include <string>

namespace util {

std::vector<std::string> splitString(const std::string& input, const std::string& delim_set);
std::vector<std::string> splitString(const std::string& input, char delim);

std::string itoa(unsigned long n, unsigned int base = 10);
std::string itoa(unsigned int n, unsigned int base = 10);
std::string itoa(long n, unsigned int base = 10);
std::string itoa(int n, unsigned int base = 10);

/*
x -- string to search
to_find -- substring to search for
limit -- max characters to traverse in x
*/
std::size_t findLimit(const std::string& x, const std::string& to_find, std::size_t limit);

/*
Random Number Generation
	Prefer: randomRangeMersenne
*/
double randomFraction();
int randomRange(int min, int max);
int randomRangeMersenne(int min, int max);

}

#endif /* UTIL_HPP */
#endif /* LIBUTIL_HPP */
