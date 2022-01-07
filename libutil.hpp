#ifndef LIBUTIL_HPP
# define LIBUTIL_HPP
#ifndef MRLOG_HPP
#define MRLOG_HPP

#include <iostream>

namespace mrlog {

enum class LogLevel : uint16_t {
	OFF,
	FATAL,
	ERROR,
	WARN,
	INFO,
	DEBUG
};

	namespace Detail {

	void processFormat(const char* format);

	template<typename T, typename... Args>
	void processFormat(const char* format, const T& value, Args&&...args) {
		while (*format != '\0') {
			if (*format == '{') {
				while (*format != '}') {
					if (*format == '\0') {
						throw std::runtime_error("mrlog: expected '}'");
					}
					++format;
				}
				std::cout << value;
				processFormat(format + 1, std::forward<Args>(args)...);
				return;
			} else {
				std::cout << *format++;
			}
		}
	}

	void log(LogLevel level, const char* s);
	template <typename T, typename... Args>
	void log(LogLevel level, const char* format, const T& value, Args&&...args) {
		log(level, "");
		processFormat(format, value, std::forward<Args>(args)...);
	}

	}

template <typename... Args>
void log(const char* format, Args&&...args) {
	Detail::log(LogLevel::OFF, format, std::forward<Args>(args)...);
}

template <typename... Args>
void fatal(const char* format, Args&&...args) {
	Detail::log(LogLevel::FATAL, format, std::forward<Args>(args)...);
}

template <typename... Args>
void error(const char* format, Args&&...args) {
	Detail::log(LogLevel::ERROR, format, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const char* format, Args&&...args) {
	Detail::log(LogLevel::WARN, format, std::forward<Args>(args)...);
}

template <typename... Args>
void info(const char* format, Args&&...args) {
	Detail::log(LogLevel::INFO, format, std::forward<Args>(args)...);
}

template <typename... Args>
void debug(const char* format, Args&&...args) {
	Detail::log(LogLevel::DEBUG, format, std::forward<Args>(args)...);
}

};

#endif /* MRLOG_HPP */
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

/*
Directory, filesystem
*/
bool isDirectory(const std::string& dirname);
std::vector<std::string> directorySearch(const std::string& dirname);

/*
String manipulation
*/
std::vector<std::string> stringSplit(const std::string& input, const std::string& delim_set);
std::vector<std::string> stringSplit(const std::string& input, char delim);

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
