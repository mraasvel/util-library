#ifndef LIBUTIL_HPP
# define LIBUTIL_HPP
#ifndef ITERATOR_SFINAE
#define ITERATOR_SFINAE

#include <type_traits>
#include <iterator>

namespace util {

template <typename Iterator, typename Tag>
using RequireIterator = typename std::enable_if<std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category, Tag>::value, bool>::type;

template <typename InputIterator>
using RequireInputIterator = RequireIterator<InputIterator, std::input_iterator_tag>;

template <typename RandomAccessIterator>
using RequireRandomAccessIterator = RequireIterator<RandomAccessIterator, std::random_access_iterator_tag>;

}

#endif /* ITERATOR_SFINAE */
#ifndef PERMUTATIONS_HPP
#define PERMUTATIONS_HPP

#include <vector>
#include <algorithm>

namespace util {

template <typename T, typename PermutationGenerator>
class PermutationIterator {
public:
	using value_type = typename PermutationGenerator::permutation_type;
public:
	PermutationIterator(PermutationGenerator* x)
	: generator(x) {}

	const value_type& operator*() {
		return generator->getPermutation();
	}

	PermutationIterator& operator++() {
		generator->nextPermutation();
		return *this;
	}

	/*
	Hacky comparison for range-based for loop syntax */
	friend bool operator==(const PermutationIterator& lhs, const PermutationIterator& rhs) {
		return lhs.generator->isEnd() && rhs.generator->isEnd();
	}

	friend bool operator!=(const PermutationIterator& lhs, const PermutationIterator& rhs) {
		return !(lhs == rhs);
	}

private:
	PermutationGenerator* generator;
};

/*
Generate list of n permutations of [start, end]
With/without replacement? https://web.ma.utexas.edu/users/parker/sampling/repl.htm
Complexity: O(distance(first, last)^n) */

/*
Iterator like object, that generates the next permutation */
template <typename T>
class ReplacementPermutations {
public:
	using value_type = T;
	using permutation_type = std::vector<T>;
	using iterator = PermutationIterator<T, ReplacementPermutations>;
public:
	ReplacementPermutations(std::size_t n, const T& first, const T& last)
	: permutation(n, first), first(first), last(last), done(false) {}

	iterator begin() {
		return iterator(this);
	}

	iterator end() {
		return iterator(this);
	}

	const permutation_type& getPermutation() const {
		return permutation;
	}

	void nextPermutation() {
		for (auto rit = permutation.rbegin(); rit != permutation.rend(); ++rit) {
			if (*rit != last) {
				++(*rit);
				return;
			} else {
				*rit = first;
			}
		}
		done = true;
	}

	bool isEnd() const {
		return done;
	}

	void reset() {
		done = false;
	}

private:
	permutation_type permutation;
	T first;
	T last;
	bool done;
};

template <typename T>
class Permutations {
public:
	using value_type = T;
	using permutation_type = std::vector<T>;
	using iterator = PermutationIterator<T, Permutations>;
public:
	Permutations(T first, const T& last)
	: done(false) {
		while (first != last) {
			permutation.emplace_back(first);
			++first;
		}
		permutation.emplace_back(last);
	}

	iterator begin() {
		return iterator(this);
	}

	iterator end() {
		return iterator(this);
	}

	const permutation_type& getPermutation() const {
		return permutation;
	}

	void nextPermutation() {
		if (!std::next_permutation(permutation.begin(), permutation.end())) {
			done = true;
		}
	}

	bool isEnd() const {
		return done;
	}

	void reset() {
		done = false;
	}

private:
	permutation_type permutation;
	bool done;
};

}

#endif /* PERMUTATIONS_HPP */
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
#define TIMER_HPP

/*
NOTE: Min C++11 for chrono
*/

#include <chrono>

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
#define UTIL_HPP

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
#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <iostream> // REMOVE

namespace util {

	namespace Detail {

	template <typename InputIterator, typename OutputIterator, typename Compare>
	void merge(InputIterator first1, InputIterator last1, 
				InputIterator first2, InputIterator last2,
				OutputIterator out, Compare comp) {
		while (first1 != last1 || first2 != last2) {
			if (first1 == last1) {
				*out++ = *first2++;
			} else if (first2 == last2) {
				*out++ = *first1++;
			} else if (comp(*first1, *first2)) {
				*out++ = *first1++;
			} else {
				*out++ = *first2++;
			}
		}
	}

	}

template <typename RandomAcessIterator,
	RequireRandomAccessIterator<RandomAcessIterator> = true>
void mergesort(RandomAcessIterator first, RandomAcessIterator last) {
	mergesort(first, last, std::less<typename RandomAcessIterator::value_type>());
}

template <typename RandomAcessIterator, typename Compare,
	RequireRandomAccessIterator<RandomAcessIterator> = true>
void mergesort(RandomAcessIterator first, RandomAcessIterator last, Compare comp) {
	auto dist = std::distance(first, last);
	if (dist == 1) {
		return;
	}
	RandomAcessIterator midpoint = first + dist / 2;

	// 2 branches
	mergesort(first, midpoint, comp);
	mergesort(midpoint, last, comp);

	std::vector<typename RandomAcessIterator::value_type> v;
	v.reserve(dist);
	// Merging = linear in dist(first, last)
	Detail::merge(first, midpoint, midpoint, last, std::back_inserter(v), comp);
	// Copying = linear in dist(first, last)
	std::copy(v.begin(), v.end(), first);
}

}

#endif /* MERGESORT_HPP */
#endif /* LIBUTIL_HPP */
