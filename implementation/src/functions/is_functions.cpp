#include "util.hpp"
#include <string>
#include <sys/stat.h>

namespace util {

bool isDirectory(const std::string& dirname) {
	struct stat st;
	if (stat(dirname.c_str(), &st) == 0) {
		return S_ISDIR(st.st_mode);
	}
	return false;
}

}
