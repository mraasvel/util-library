#include <string>

namespace util {

std::size_t findLimit(const std::string& x, const std::string& to_find, std::size_t limit) {

	std::size_t i = 0;
	while (i  + to_find.size() <= x.size() && i + to_find.size() <= limit) {
		if (x.compare(i, to_find.size(), to_find) == 0) {
			return i;
		}
		++i;
	}

	return std::string::npos;
}

}
