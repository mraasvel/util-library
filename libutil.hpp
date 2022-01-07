#ifndef LIBUTIL_HPP
# define LIBUTIL_HPP
#ifndef MRLOG_HPP
#define MRLOG_HPP

#include <iostream>
#include <fstream>

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

	const char* parseFormat(const char* format);

	template <typename OutStream>
	void processFormat(OutStream& out, const char* format) {
		out << format << std::endl;
	}

	template<typename OutStream, typename T, typename... Args>
	void processFormat(OutStream& out, const char* format, const T& value, Args&&...args) {
		while (*format != '\0') {
			if (*format == '{') {
				format = parseFormat(format);
				out << value;
				processFormat(out, format + 1, std::forward<Args>(args)...);
				return;
			} else {
				out << *format++;
			}
		}
		out << std::endl;
	}

	}

template <typename...Args>
void cout(const char* format, Args&&...args) {
	Detail::processFormat(std::cout, format, std::forward<Args>(args)...);
}

template <typename...Args>
void cerr(const char* format, Args&&...args) {
	Detail::processFormat(std::cerr, format, std::forward<Args>(args)...);
}

	namespace Detail {

	extern std::string logfile;
	std::string generateDate();

	template <typename OutStream>
	void printLevel(OutStream& out, LogLevel level) {
		static const std::string levels[] = {
			"OFF",
			"fatal",
			"error",
			"warn",
			"info",
			"debug"
		};

		if (level != LogLevel::OFF) {
			out << "[" << levels[static_cast<uint16_t>(level)] << "] ";
		}
	}

	template <typename... Args>
	void log(LogLevel level, const char* format, Args&&...args) {
		std::ofstream ofs(logfile, std::ios_base::app);
		if (!ofs.is_open()) {
			mrlog::cerr("mrlog: cannot open logfile: {}", logfile);
			return;
		}
		ofs << generateDate() << ' ';
		printLevel(ofs, level);
		processFormat(ofs, format, std::forward<Args>(args)...);
		ofs.close();
	}

	}

void clearLog();
void setLogFile(std::string&& file);

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
